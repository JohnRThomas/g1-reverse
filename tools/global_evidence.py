"""Stage A+B of global naming: build an evidence packet per unnamed global and
auto-name the easy ones by rule. NON-DESTRUCTIVE (writes only evidence + a
proposed-names file in scratchpad). Output feeds the agent batch (Stage C) and
the canonical global_names.json (Stage D).

Evidence per global: ctype, kind, referencing functions (reverse index from the
Ghidra refgraph), read/write disposition, owning module, and the recovered
strings referenced by the same functions (the naming signal).
"""

# Resolvable pipeline scratchpad (tools/g1_paths.py).  This used to be one
# literal /private/tmp path belonging to a finished agent session; see that
# module for the resolution order and the fail-closed catalog fallback.
import os as _g1_os, sys as _g1_sys
_G1_TOOLS = _g1_os.path.dirname(_g1_os.path.abspath(__file__))
if _g1_os.path.basename(_G1_TOOLS) != "tools":
    _G1_TOOLS = _g1_os.path.dirname(_G1_TOOLS)
if _G1_TOOLS not in _g1_sys.path:
    _g1_sys.path.insert(0, _G1_TOOLS)
import g1_paths as _g1_paths
import sys, os, re, json, glob, collections
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")

SCR = _g1_paths.scratchpad()
BASE = "/Users/freedomcoder/Projects/G1disasm2"
CORE = sys.argv[1] if len(sys.argv) > 1 else "app"
if CORE == "app":
    NAMED = BASE + "/recon/named"; MAP = SCR + "/symbol_map.json"
    REFG = SCR + "/refgraph_app.json"; STR = SCR + "/symbol_strings.json"
    MODU = SCR + "/module_units.json"
else:
    NAMED = BASE + "/recon/net/src"; MAP = SCR + "/symbol_map_net.json"
    REFG = SCR + "/refgraph_net.json"; STR = SCR + "/symbol_strings_net.json"
    MODU = None

smap = json.load(open(MAP))
strings = json.load(open(STR))
refg = json.load(open(REFG))["functions"]

# addr -> HUMAN function name from the verified-file headers
# ("/* Reconstructed <name> @ 0xADDR ... */"); falls back to FUN_ where unnamed.
VSRC = BASE + ("/recon/verified/src" if CORE == "app" else "/recon/net/src")
ent2name = {}
_hdr = re.compile(r'Reconstructed\s+(\w+)\s+@\s+(0x[0-9a-fA-F]+)')
_hdr2 = re.compile(r'net-core\s+(\w+)\s+@\s+(0x[0-9a-fA-F]+)')
for f in glob.glob(VSRC + "/*.c"):
    h = open(f).readline()
    m = _hdr.search(h) or _hdr2.search(h)
    if m:
        ent2name[int(m.group(2), 16)] = m.group(1)
# fill any gaps from refgraph
for e, v in refg.items():
    ent2name.setdefault(int(e, 16), v["name"])

# addr -> owning module, inverted from topic_groups.json
fn_addr2mod = {}
_tg = SCR + "/topic_groups.json"
if os.path.exists(_tg):
    for mod, members in json.load(open(_tg)).items():
        for it in (members if isinstance(members, list) else []):
            a = it.get("addr") if isinstance(it, dict) else None
            if isinstance(a, str):
                try: fn_addr2mod[int(a, 16)] = mod
                except Exception: pass

# reverse data_ref index: addr(int) -> set(func entry addrs)
readers = collections.defaultdict(set)
func_datarefs = {}  # entry addr -> [data ref addrs]
for e, v in refg.items():
    ea = int(e, 16)
    drs = []
    for d in v.get("data_refs", []):
        try:
            a = int(d, 16)
        except Exception:
            continue
        if a < 0:  # stack offsets like 0x-38
            continue
        drs.append(a)
        readers[a].add(ea)
    func_datarefs[ea] = drs

# textual read/write disposition from the source (approx)
def disposition(v):
    """Return (written, nreads) by scanning named sources for the address."""
    written = False
    reads = 0
    hexs = hex(v)
    wpat = re.compile(re.escape(hexs) + r'(?:UL|ul|U|u)?\s*(?:\)?\s*)?=[^=]')
    for f in glob.glob(NAMED + "/*.c"):
        t = open(f).read()
        if hexs not in t:
            continue
        reads += t.count(hexs)
        # crude: "...)0xADDR = x" or "*(...*)0xADDR = "
        if re.search(r'\*\s*\(\s*volatile[^)]*\)\s*' + re.escape(hexs) + r'(?:UL|ul)?\s*=', t):
            written = True
    return written, reads

def nearby_strings(entry_addrs, limit=6):
    """Strings referenced by the functions that touch this global."""
    hits = collections.Counter()
    for ea in entry_addrs:
        for a in func_datarefs.get(ea, []):
            s = strings.get(hex(a))
            if s:
                hits[s] += 1
    return [s for s, _ in hits.most_common(limit)]

def ident(s):
    s = re.sub(r'[^A-Za-z0-9]+', '_', s.strip().lower()).strip('_')
    return s[:40]

ACCESSOR = re.compile(r'^(?:get|set|is|has|read|write|update|clr|clear|reset)_?(.+)', re.I)

def rule_name(funcs, strs, written):
    """Only HIGH-confidence rules auto-apply. Strings stay as agent evidence
    (the same string sits near several globals, so it can't name one uniquely)."""
    fl = [f for f in funcs if not f.startswith("FUN_")]  # human-named accessors
    # R1: dedicated accessor get_X/set_X/is_X and few total readers
    if len(fl) <= 3 and fl:
        for f in fl:
            m = ACCESSOR.match(f)
            if m and 2 < len(m.group(1)) < 30:
                return "g_" + ident(m.group(1)), "accessor:%s" % f, "high"
    return None

def main():
    targets = [(int(a, 16), r) for a, r in smap.items()
               if r.get("kind") in ("ram_global", "kobject") and not r.get("name_source")]
    print("[%s] unnamed globals to investigate: %d" % (CORE, len(targets)))
    packets = []
    auto = {}
    for v, rec in targets:
        entry_addrs = sorted(readers.get(v, set()))
        funcs = [ent2name.get(ea, hex(ea)) for ea in entry_addrs]
        written, nreads = disposition(v)
        strs = nearby_strings(entry_addrs)
        mods = collections.Counter(fn_addr2mod.get(ea) for ea in entry_addrs if fn_addr2mod.get(ea))
        module = mods.most_common(1)[0][0] if mods else None
        pkt = {"addr": hex(v), "ctype": rec.get("ctype"), "is_buffer": rec.get("is_buffer"),
               "kind": rec.get("kind"), "written": written, "n_source_reads": nreads,
               "n_ref_funcs": len(funcs), "ref_funcs": funcs[:20],
               "module": module, "nearby_strings": strs}
        rn = rule_name(funcs, strs, written)
        if rn:
            pkt["auto_name"], pkt["auto_reason"], pkt["auto_conf"] = rn
            auto[hex(v)] = {"name": rn[0], "reason": rn[1], "conf": rn[2]}
        packets.append(pkt)
    # dedupe auto names (append addr suffix on collision)
    seen = collections.Counter()
    for a, d in auto.items():
        seen[d["name"]] += 1
        if seen[d["name"]] > 1:
            d["name"] = "%s_%s" % (d["name"], a[-4:])
    json.dump(packets, open(SCR + "/global_evidence_%s.json" % CORE, "w"), indent=1)
    json.dump(auto, open(SCR + "/global_auto_%s.json" % CORE, "w"), indent=1)
    byconf = collections.Counter(d["conf"] for d in auto.values())
    withstr = sum(1 for p in packets if p["nearby_strings"])
    withmod = sum(1 for p in packets if p["module"])
    print("  auto-named by rule: %d  (%s)" % (len(auto), dict(byconf)))
    print("  have a nearby string signal: %d / %d" % (withstr, len(packets)))
    print("  mapped to an owning module: %d / %d" % (withmod, len(packets)))
    print("  remaining for agent pass: %d" % (len(packets) - len(auto)))
    # show a few examples
    for p in packets[:6]:
        print("   %s ctype=%s reads=%d funcs=%d mod=%s auto=%s str=%s"
              % (p["addr"], p["ctype"], p["n_source_reads"], p["n_ref_funcs"], p["module"],
                 p.get("auto_name"), (p["nearby_strings"][:1] or [""])[0][:30]))

if __name__ == "__main__":
    main()
