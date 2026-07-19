"""Part A/A1: authoritative struct access-footprint extraction from Ghidra output.

The stable source is Ghidra's own decompilation (recon/catalogs/app_funcs.json.gz,
one record per function with the decompiled C, Ghidra type inference, signature,
and callees). We parse it — not the reconstructed sources — so the footprint is
grounded in the disassembler, per the plan.

For every function we collect, per *base object*, the set of member accesses of
the forms Ghidra emits:
    *(T *)(BASE + 0xNN)        member load/store at constant offset
    *(T *)BASE                 offset 0
    BASE[k]                    (typed pointer index -> offset k*sizeof(T))
where BASE is param_N (pointer parameter), a DAT_/hex global, or a stack local
(local_/aStack_/auStack_). Output: recon/structs/footprints_app.json.
"""
import gzip, json, os, re, sys

BASE = "/Users/freedomcoder/Projects/G1disasm2"
OUT = BASE + "/recon/structs"
SRC = BASE + "/recon/catalogs/app_funcs.json.gz"

# access size by Ghidra type token
SIZE = {
    "undefined1": 1, "byte": 1, "char": 1, "uchar": 1, "int8_t": 1, "uint8_t": 1, "bool": 1,
    "undefined2": 2, "short": 2, "ushort": 2, "int16_t": 2, "uint16_t": 2, "wchar_t": 2,
    "undefined4": 4, "int": 4, "uint": 4, "int32_t": 4, "uint32_t": 4, "float": 4,
    "undefined": 4,  # bare undefined in pointer context is word-ish; treat as 4
    "code": 4, "pointer": 4,
    "undefined8": 8, "longlong": 8, "ulonglong": 8, "int64_t": 8, "uint64_t": 8, "double": 8,
}


def tsize(tok):
    tok = tok.strip()
    # pointer types (T *) are 4 bytes on this target
    if tok.endswith("*"):
        return 4, "ptr"
    base = tok.split()[-1] if " " in tok else tok
    return SIZE.get(base, None), base


# *(T *)(BASE + 0xNN)  and  *(T *)(BASE - 0xNN)  and  *(T *)BASE
ACCESS = re.compile(
    r'\*\(\s*([A-Za-z_][\w ]*?\**)\s*\*\)\s*'
    r'(?:\(\s*(?:\(int\)\s*)?([A-Za-z_]\w*)\s*([+\-])\s*(0x[0-9a-fA-F]+|\d+)\s*\)'
    r'|([A-Za-z_]\w*)\b)')
# BASE[k] indexing (numeric literal index only, so offset is knowable)
INDEX = re.compile(r'\b([A-Za-z_]\w*)\s*\[\s*(0x[0-9a-fA-F]+|\d+)\s*\]')
# declared local pointer types, to know element size for BASE[k]
DECL = re.compile(r'^\s*([A-Za-z_][\w ]*?\**)\s+([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*;', re.M)
IS_GLOBAL = re.compile(r'^(?:DAT_|_?DAT_|PTR_|__)?[0-9a-fA-F]{4,8}$')


def classify_base(tok, decls):
    if re.match(r'^param_\d+$', tok):
        return ("param", tok)
    if re.match(r'^(?:DAT|PTR|UNK|_DAT|__DAT)_[0-9a-fA-F]+$', tok) or re.match(r'^[0-9a-fA-F]{5,8}$', tok):
        m = re.search(r'([0-9a-fA-F]{4,8})$', tok)
        return ("global", "0x" + m.group(1).lower()) if m else (None, None)
    if re.match(r'^(?:a|au|puStack|apuStack|local|aStack|auStack|afStack|uStack|iStack|acStack|asStack)[\w]*$', tok) \
       and re.search(r'(?:Stack_|local_)', tok):
        return ("stack", tok)
    return (None, None)


def main():
    os.makedirs(OUT, exist_ok=True)
    data = json.load(gzip.open(SRC))
    image_base = data.get("image_base", 0)
    foot = {}  # key -> {kind, func, base, size, accesses:{off:{sizes:set, rw:set, types:set}}}
    stats = {"funcs": 0, "param": 0, "global": 0, "stack": 0}

    for fn in data["functions"]:
        if fn.get("is_thunk") or fn.get("is_external"):
            continue
        dc = fn.get("decompiled") or ""
        if not dc:
            continue
        stats["funcs"] += 1
        name = fn["name"]
        entry = fn.get("entry_hex") or ("0x%x" % fn.get("entry", 0))
        # local pointer element sizes for BASE[k]
        decls = {}
        for m in DECL.finditer(dc):
            t, var = m.group(1), m.group(2)
            sz, _ = tsize(t)
            decls[var] = sz or 4

        def record(kind, base, off, sz, typ, rw):
            if kind == "param":
                key = "param:%s:%s" % (entry, base)
            elif kind == "global":
                key = "global:%s" % base
            else:
                key = "stack:%s:%s" % (entry, base)
            rec = foot.setdefault(key, {"kind": kind, "func": name, "entry": entry,
                                        "base": base, "accesses": {}})
            a = rec["accesses"].setdefault("0x%x" % off, {"sizes": set(), "rw": set(), "types": set()})
            a["sizes"].add(sz)
            a["rw"].add(rw)
            a["types"].add(typ)

        # detect store context: "*(...) = " on the left
        for m in ACCESS.finditer(dc):
            typ = m.group(1)
            sz, tbase = tsize(typ)
            if sz is None:
                continue
            tail = dc[m.end():m.end()+3]
            rw = "w" if tail.lstrip().startswith("=") and not tail.lstrip().startswith("==") else "r"
            if m.group(2):  # (BASE +/- OFF)
                tok, sign, offs = m.group(2), m.group(3), m.group(4)
                off = int(offs, 16) if offs.startswith("0x") else int(offs)
                if sign == "-":
                    continue  # negative -> below object, skip (frame-pointer arithmetic)
            else:  # *(T *)BASE  -> offset 0
                tok, off = m.group(5), 0
            kind, base = classify_base(tok, decls)
            if kind:
                record(kind, base, off, sz, tbase, rw)
                stats[kind] += 1

        for m in INDEX.finditer(dc):
            tok, idxs = m.group(1), m.group(2)
            idx = int(idxs, 16) if idxs.startswith("0x") else int(idxs)
            kind, base = classify_base(tok, decls)
            if not kind:
                continue
            esz = decls.get(tok, 4)
            record(kind, base, idx * esz, esz, "idx%d" % esz, "r")
            stats[kind] += 1

    # serialize (sets -> sorted lists)
    out = {}
    for key, rec in foot.items():
        acc = {}
        for off, a in rec["accesses"].items():
            acc[off] = {"sizes": sorted(a["sizes"]), "rw": sorted(a["rw"]),
                        "types": sorted(a["types"])}
        rec["accesses"] = dict(sorted(acc.items(), key=lambda kv: int(kv[0], 16)))
        rec["n_offsets"] = len(acc)
        out[key] = rec

    json.dump({"image_base": image_base, "footprints": out, "stats": stats},
              open(OUT + "/footprints_app.json", "w"), indent=1)
    # summary
    from collections import Counter
    bykind = Counter(r["kind"] for r in out.values())
    multi = {k: sum(1 for r in out.values() if r["kind"] == k and r["n_offsets"] >= 2)
             for k in ("param", "global", "stack")}
    print("functions parsed:", stats["funcs"])
    print("access hits:", {k: stats[k] for k in ("param", "global", "stack")})
    print("distinct base objects:", dict(bykind))
    print("bases with >=2 offsets (real struct candidates):", multi)


if __name__ == "__main__":
    main()
