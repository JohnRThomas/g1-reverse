"""Part A/A3+A4+A5: candidate layout, library hints, and evidence bundles.

For every cluster with >=2 offsets we synthesize the mechanical candidate layout
(fields at observed offsets, widest observed access width, explicit padding for
gaps, overlap/union flags) and emit one self-contained markdown bundle: the
provisional C struct, the member functions (readable names) and which param they
are, the merged access table, and a library hint. Bundles are sharded into N.
Output: recon/structs/bundles/** and shard index.
"""
import gzip, json, os, re, sys

BASE = "/Users/freedomcoder/Projects/G1disasm2"
OUT = BASE + "/recon/structs/bundles"
NSHARD = int(sys.argv[1]) if len(sys.argv) > 1 else 20

LIB_PREFIX = ("bt_", "k_", "z_", "zephyr", "nrfx_", "nrf_", "lc3_", "cjson", "cJSON",
              "mbedtls", "tc_", "sys_", "log_", "net_buf", "settings_", "mpsl",
              "sdc_", "hci_", "gatt_", "att_", "l2cap", "smp_", "__aeabi", "__")
CTYPE = {1: "uint8_t", 2: "uint16_t", 4: "uint32_t", 8: "uint64_t"}


def rep_type(types, size):
    """Return (c_type, array_len). array_len is None for a scalar field, or a
    byte count when the (clamped) width isn't a natural scalar size."""
    if size == 4:
        if "ptr" in types:
            return "void *", None
        if "float" in types:
            return "float", None
    if size == 8 and "double" in types:
        return "double", None
    if size in CTYPE:
        return CTYPE[size], None
    return "uint8_t", size  # odd width -> byte array


def candidate_layout(acc, total):
    """Delimit each field by the NEXT observed offset so fields never overlap:
    a field's width is min(widest observed access, gap to next field). When the
    observed access is wider than the gap, the object is being read at a coarser
    granularity than its sub-field boundaries (union/overlap) -- we keep the
    non-overlapping decomposition and flag it."""
    offs = sorted(int(o, 16) for o in acc)
    fields = []
    notes = []
    prev_end = 0
    for i, off in enumerate(offs):
        a = acc["0x%x" % off]
        obs = max(a["sizes"])
        nxt = offs[i + 1] if i + 1 < len(offs) else off + obs
        gap = nxt - off
        size = min(obs, gap) if gap > 0 else obs
        if obs > gap and gap > 0:
            notes.append("0x%x: access width %d exceeds gap %d to next field (overlap/union)" %
                         (off, obs, gap))
        if off > prev_end:
            fields.append(("_pad_0x%x" % prev_end, "uint8_t", off - prev_end, prev_end, None))
        typ, arrlen = rep_type(a["types"], size)
        fields.append(("field_0x%x" % off, typ, arrlen, off, a))
        prev_end = off + size
    if total > prev_end:
        fields.append(("_pad_0x%x" % prev_end, "uint8_t", total - prev_end, prev_end, None))
    return fields, notes


def render_struct(cid, fields):
    lines = ["struct %s {" % cid]
    for name, typ, arrlen, off, a in fields:
        if arrlen is not None:
            lines.append("    %-10s %s[0x%x];   /* +0x%x pad */" % (typ, name, arrlen, off))
        else:
            meta = "sz=%s rw=%s types=%s" % (",".join(map(str, a["sizes"])),
                                             "".join(a["rw"]), ",".join(a["types"]))
            lines.append("    %-10s %s;   /* +0x%x  %s */" % (typ, name, off, meta))
    lines.append("};")
    return "\n".join(lines)


def main():
    os.makedirs(OUT, exist_ok=True)
    clusters = json.load(open(BASE + "/recon/structs/clusters_app.json"))["clusters"]
    fns = json.load(gzip.open(BASE + "/recon/catalogs/classified.json.gz"))["functions"]
    cls = {f["entry_hex"]: f["class"] for f in fns}
    amap = json.load(open(BASE + "/recon/catalogs/function_names_app.json"))["by_address"]

    def human(entry):
        rec = amap.get("0x%08x" % (int(entry, 16) & ~1))
        return rec["name"] if rec else entry

    items = [(cid, c) for cid, c in clusters.items() if c["n_offsets"] >= 2]
    manifest = []
    for i, (cid, c) in enumerate(sorted(items)):
        fields, notes = candidate_layout(c["accesses"], c["min_size_bytes"])
        # library hint
        libmembers = 0
        prefixes = set()
        for m in c["members"]:
            if cls.get(m["entry"]) == "LIBRARY":
                libmembers += 1
            hn = human(m["entry"])
            for p in LIB_PREFIX:
                if hn.startswith(p):
                    prefixes.add(p.rstrip("_"))
        lib_hint = libmembers > 0 or bool(prefixes)

        b = []
        b.append("### cluster %s  (%s, %d members, %d fields, size>=0x%x)" %
                 (cid, c["kind"], c["n_members_total"], c["n_offsets"], c["min_size_bytes"]))
        b.append("")
        if c["kind"] == "param":
            b.append("Shared pointer-parameter object unified across call-argument flow.")
        elif c["kind"] == "global":
            b.append("Global object at fixed address %s." % c["members"][0]["base"])
        else:
            b.append("Stack-frame local %s in %s (not shared across functions)." %
                     (c["members"][0]["base"], human(c["members"][0]["entry"])))
        b.append("")
        b.append("library hint: %s%s" % (
            "LIKELY LIBRARY" if lib_hint else "likely G1-original",
            (" (prefixes: %s; %d/%d members are LIBRARY-class)" % (
                ",".join(sorted(prefixes)) or "-", libmembers, c["n_members_total"]))
            if lib_hint else ""))
        b.append("")
        b.append("members (%d shown of %d):" % (len(c["members"]), c["n_members_total"]))
        for m in c["members"][:24]:
            b.append("  - %s @ %s  as %s  [%s]" % (human(m["entry"]), m["entry"], m["base"],
                                                   cls.get(m["entry"], "?")))
        b.append("")
        if notes:
            b.append("layout notes: " + "; ".join(notes))
            b.append("")
        b.append("candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):")
        b.append("```c")
        b.append(render_struct(cid, fields))
        b.append("```")
        bundle = "\n".join(b)
        with open(OUT + "/%s.md" % cid, "w") as fh:
            fh.write(bundle)
        manifest.append({"cid": cid, "kind": c["kind"], "shard": i % NSHARD,
                         "lib_hint": lib_hint, "n_fields": c["n_offsets"],
                         "n_members": c["n_members_total"]})

    shards = {}
    for m in manifest:
        shards.setdefault(m["shard"], []).append(m["cid"])
    for si, cids in shards.items():
        json.dump(cids, open(OUT + "/shard_%02d.json" % si, "w"), indent=1)
    json.dump(manifest, open(OUT + "/manifest.json", "w"), indent=1)

    from collections import Counter
    print("bundles:", len(manifest), "| shards:", len(shards))
    print("by kind:", dict(Counter(m["kind"] for m in manifest)))
    print("library-hinted:", sum(1 for m in manifest if m["lib_hint"]),
          "| G1-original-hinted:", sum(1 for m in manifest if not m["lib_hint"]))


if __name__ == "__main__":
    main()
