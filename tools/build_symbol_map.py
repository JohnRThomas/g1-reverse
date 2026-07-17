"""Build the address->symbol map for the symbolization pass.

Reads every distinct absolute address actually USED in recon/named/*.c, classifies
it, and assigns a name + C type + home section + evidence. Rodata pointers are
resolved to real string literals by reading the image bytes. RAM globals get their
width/signedness from the cast context in the code and names from the WS2 kernel-
object inventory + data clusters. Output: scratchpad/symbol_map.json (deterministic
core) + a human-readable summary. NON-DESTRUCTIVE: reads only, writes only the map.
"""
import sys, os, re, json, glob, collections
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"

CORE = sys.argv[1] if len(sys.argv) > 1 else "app"
if CORE == "app":
    import extract as ax
    NAMED = "/Users/freedomcoder/Projects/G1disasm2/recon/named"
    REFGRAPH = SCR + "/refgraph_app.json"
    OUT = SCR + "/symbol_map.json"; STROUT = SCR + "/symbol_strings.json"
    def classify(v):
        if 0x20000000 <= v < 0x21000000: return "ram"
        if 0x50000000 <= v < 0x50100000: return "mmio"
        if 0x00100000 <= v < 0x00160000: return "flash_part"
        if 0x0000C200 <= v < 0x00100000: return "rodata"
        return "const"
else:  # net
    import net_extract as ax
    NAMED = "/Users/freedomcoder/Projects/G1disasm2/recon/net/src"
    REFGRAPH = SCR + "/refgraph_net.json"
    OUT = SCR + "/symbol_map_net.json"; STROUT = SCR + "/symbol_strings_net.json"
    def classify(v):
        if 0x20000000 <= v < 0x21010000: return "ram"      # shared + net-core SRAM
        if 0x40000000 <= v < 0x42000000: return "mmio"      # net-core APB peripherals
        if 0x50000000 <= v < 0x50100000: return "mmio"
        if 0x01008000 <= v < 0x01040000: return "rodata"    # net image
        return "const"

# Ghidra's reference graph distinguishes literal values that are actual
# addresses from numerically-similar scalars.  This prevents masks such as
# 0xffff and magic words such as 0x20222022 from becoming fake symbols.
try:
    _ref_functions = json.load(open(REFGRAPH)).get("functions", {})
except (OSError, ValueError, TypeError):
    _ref_functions = {}
FUNCTION_ENTRIES = {int(address, 16) & ~1 for address in _ref_functions}
DATA_REFERENCES = set()
for _function in _ref_functions.values():
    for _address in _function.get("data_refs", ()):
        try:
            _value = int(_address, 16) if isinstance(_address, str) else int(_address)
        except (TypeError, ValueError):
            continue
        if _value >= 0:
            DATA_REFERENCES.add(_value)

_base_classify = classify
def classify(v):
    if (v & ~1) in FUNCTION_ENTRIES:
        return "function"
    if v not in DATA_REFERENCES:
        return "const"
    return _base_classify(v)

ADDR = re.compile(
    r'(?<![A-Za-z0-9_])0x[0-9a-fA-F]{4,8}(?:UL|ul|U|u|L|l)?(?![A-Za-z0-9_])')
SKIP = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                  re.DOTALL)

def code_only(text):
    """Blank comments/string/char literals without shifting source offsets."""
    return SKIP.sub(lambda match: " " * len(match.group(0)), text)

# --- read a rodata pointer as a possible C string ------------------------------
def read_string(va, maxlen=160):
    try:
        b = ax.read(va, maxlen)
    except Exception:
        return None
    out = bytearray()
    for c in b:
        if c == 0:
            break
        out.append(c)
    if len(out) < 2 or len(out) == maxlen:
        return None
    # printable ASCII (allow \n \r \t)
    if all(32 <= c < 127 or c in (9, 10, 13) for c in out):
        return out.decode("latin1")
    return None

# --- infer C type from how the address is cast/used in the named sources -------
CAST = re.compile(r'\*\(\s*volatile\s+([a-z0-9_ ]+?)\s*\*\s*\)\s*(0x[0-9a-fA-F]+)')
def scan_usage():
    """addr -> Counter of C types it is cast to; also note memcpy/memset buffer use."""
    types = collections.defaultdict(collections.Counter)
    buffer_use = set()
    for f in glob.glob(NAMED + "/*.c"):
        txt = code_only(open(f).read())
        for m in CAST.finditer(txt):
            t = m.group(1).strip()
            v = int(m.group(2), 16)
            types[v][t] += 1
        # memcpy/memset first-arg buffers => arrays
        for m in re.finditer(r'mem(?:cpy|set)\w*\(\s*(0x[0-9a-fA-F]+)', txt):
            buffer_use.add(int(m.group(1), 16))
    return types, buffer_use

def width_type(counter):
    if not counter:
        return None
    t = counter.most_common(1)[0][0]
    return t

# harvest semantic names the naming agents recorded in per-file comment tables
# ('//   0xADDR  name'); consistent across files (verified 0 conflicts).
CMT = re.compile(r'^//\s+(0x[0-9a-fA-F]{4,8})\s+([A-Za-z_][A-Za-z0-9_]*)\s*$')
PLACEHOLDER_NAME = re.compile(
    r'^(?:g_(?:buf_)?[0-9a-f]+|rodata_[0-9a-f]+|str_[0-9a-f]+|'
    r'tbl_[0-9a-f]+|REG_[0-9a-f]+|FLASH_OFF_[0-9a-f]+)$', re.I)

def semantic_name(name):
    return bool(name and not PLACEHOLDER_NAME.match(name))

def harvest_names():
    a2n = collections.defaultdict(collections.Counter)
    for f in glob.glob(NAMED + "/*.c"):
        for ln in open(f):
            if ln.startswith("//"):
                m = CMT.match(ln.strip())
                if m and semantic_name(m.group(2)):
                    a2n[int(m.group(1), 16)][m.group(2)] += 1
    names = {a: c.most_common(1)[0][0] for a, c in a2n.items()}
    # canonical global_names table (Stage D agent+rule naming) overrides comments
    gnp = SCR + "/global_names_%s.json" % CORE
    if os.path.exists(gnp):
        for a, d in json.load(open(gnp)).items():
            try: names[int(a, 16)] = d["name"]
            except Exception: pass
    # Durable committed semantic names win over ephemeral scratch proposals.
    # Placeholder names are regenerated from current classification instead.
    durable = ("/Users/freedomcoder/Projects/G1disasm2/recon/catalogs/"
               "address_names_%s.json" % CORE)
    if os.path.exists(durable):
        for a, d in json.load(open(durable)).get("by_address", {}).items():
            if semantic_name(d.get("name")):
                names[int(a, 16)] = d["name"]
    return names

def main():
    # 0. agent-recovered semantic names (override placeholders where present)
    agent_names = harvest_names()
    durable_records = {}
    durable_path = ("/Users/freedomcoder/Projects/G1disasm2/recon/catalogs/"
                    "address_names_%s.json" % CORE)
    if os.path.exists(durable_path):
        durable_records = json.load(open(durable_path)).get("by_address", {})
    # A small reviewed catalog records RAM layouts that cannot be inferred from
    # a single address cast.  In particular, net 0x21000ea6 is a two-byte
    # object whose second byte is normally referenced as base+1.  Keeping the
    # scalar type override here prevents a later symbolization pass from
    # regressing its base declaration to the uint32_t fallback (which would
    # falsely overlap the independent object at 0x21000ea8).
    layout_types = {}
    layout_path = ("/Users/freedomcoder/Projects/G1disasm2/recon/catalogs/"
                   "%s_data_alias_resolutions.json" % CORE)
    if os.path.exists(layout_path):
        for resolution in json.load(open(layout_path)).get("resolutions", []):
            base = resolution.get("base_address")
            ctype = resolution.get("base_scalar_ctype")
            if base and ctype:
                layout_types[int(base, 16)] = ctype
    function_records = {}
    function_path = ("/Users/freedomcoder/Projects/G1disasm2/recon/catalogs/"
                     "function_names_%s.json" % CORE)
    if os.path.exists(function_path):
        function_records = json.load(open(function_path)).get("by_address", {})

    # 1. all distinct addresses actually used in named bodies
    used = collections.Counter()
    for f in glob.glob(NAMED + "/*.c"):
        for m in set(ADDR.findall(code_only(open(f).read()))):
            used[int(re.sub(r'[ULul]+$', '', m), 16)] += 1

    types, buffers = scan_usage()

    # 2. reference inventories (app-core only; net has few kernel objects)
    ws2_by_addr = {}
    if os.path.exists(SCR + "/ws2_reliable.json") and CORE == "app":
        for it in json.load(open(SCR + "/ws2_reliable.json")):
            b = it.get("base")
            if isinstance(b, str):
                try: b = int(b, 16)
                except: continue
            ws2_by_addr[b] = it
    du_bases = {}
    if os.path.exists(SCR + "/data_units.json") and CORE == "app":
        du_raw = json.load(open(SCR + "/data_units.json"))
        du_flat = []
        for batch in du_raw:
            du_flat.extend(batch if isinstance(batch, list) else [batch])
        for i, du in enumerate(du_flat):
            b = du.get("base")
            if isinstance(b, str):
                try: b = int(b, 16)
                except: continue
            if isinstance(b, int):
                du_bases[b] = (i, du)

    smap = {}
    counts = collections.Counter()
    strings = {}
    for v, occ in used.items():
        c = classify(v)
        counts[c] += 1
        rec = {"addr": hex(v), "class": c, "occ": occ}
        if c == "function":
            function = function_records.get("0x%08x" % (v & ~1), {})
            readable = function.get("name") or ("FUN_%08x" % (v & ~1))
            rec["kind"] = "function_addr"
            rec["name"] = "ADDR_%s%s" % (readable, "_THUMB" if v & 1 else "")
            rec["function_name"] = readable
            rec["thumb"] = bool(v & 1)
        elif c == "rodata":
            s = read_string(v)
            if s is not None:
                # Printable bytes alone do not prove a C-string use.  Keep the
                # address as pinned rodata and retain the decoded value only as
                # evidence; this is correct for typed loads and string args.
                rec["kind"] = "rodata_ref"
                rec["name"] = "rodata_%x" % v
                rec["value"] = s
                rec["is_c_string"] = True
                strings[hex(v)] = s
            else:
                # part of a known data cluster?
                home = None
                for b,(idx,du) in du_bases.items():
                    span = du.get("span",0)
                    if isinstance(span,str):
                        try: span=int(span,0)
                        except: span=0
                    if b <= v < b+span:
                        home = b; break
                rec["kind"] = "rodata_ref"
                rec["name"] = ("tbl_%x" % home) if home else ("rodata_%x" % v)
                if home:
                    rec["cluster_base"] = hex(home)
                    rec["symbol_base"] = hex(home)
                    rec["symbol_offset"] = v - home
        elif c == "ram":
            # WS2 object covering this addr (base <= v < base+span)?
            ws2hit = None
            for b, it in ws2_by_addr.items():
                span = it.get("span", 0) or it.get("guess_type_size", 0)
                if b <= v < b + max(span, 4):
                    ws2hit = (b, it); break
            if ws2hit:
                b, it = ws2hit
                g = it.get("guess") or ("obj_%x" % b)
                rec["kind"] = "kobject"
                rec["kobj_type"] = g
                rec["kobj_conf"] = it.get("conf")
                rec["name"] = ("%s" % g) if v == b else ("%s_p%x" % (g, v - b))
                rec["base"] = hex(b)
            else:
                t = width_type(types.get(v))
                rec["kind"] = "ram_global"
                rec["ctype"] = t or ("uint8_t[]" if v in buffers else "uint32_t")
                rec["is_buffer"] = v in buffers
                rec["name"] = ("g_buf_%x" % v) if v in buffers else ("g_%x" % v)
        elif c == "flash_part":
            rec["kind"] = "partition_off"
            rec["name"] = "FLASH_OFF_%x" % v
        elif c == "mmio":
            rec["kind"] = "mmio_reg"
            rec["name"] = "REG_%x" % v
        else:
            rec["kind"] = "const"
            rec["name"] = None  # leave literal unless promoted later
        # prefer an agent-recovered semantic name over the placeholder
        if v in agent_names and c not in ("const", "function"):
            rec["placeholder"] = rec.get("name")
            rec["name"] = agent_names[v]
            rec["name_source"] = "agent_comment_table"
        durable = durable_records.get("0x%08x" % v)
        if durable and rec.get("name") == durable.get("name"):
            rec["symbol_base"] = durable["base_address"]
            rec["symbol_offset"] = durable["offset"]
            rec["name_source"] = "durable_address_map"
        if c == "ram" and v in layout_types:
            rec["ctype"] = layout_types[v]
            rec["ctype_source"] = "reviewed_data_alias_catalog"
        smap[hex(v)] = rec

    json.dump(smap, open(OUT, "w"), indent=1)
    json.dump(strings, open(STROUT, "w"), indent=1)
    print("[%s] distinct addresses mapped:" % CORE, len(smap))
    for c, n in counts.most_common():
        print("  %-12s %5d" % (c, n))
    named_ram = sum(1 for r in smap.values() if r.get("kind")=="kobject")
    typed_ram = sum(1 for r in smap.values() if r.get("kind")=="ram_global" and r.get("ctype"))
    print("rodata strings recovered:", len(strings))
    print("RAM kobjects named from WS2:", named_ram, "| RAM globals typed from casts:", typed_ram)
    print("rodata cluster-linked:", sum(1 for r in smap.values() if r.get("cluster_base")))
    # sample the whitelist example addresses
    for a in (0xa842e,0xa8aa8,0xa8400,0x2001a22c,0x20007554,0x131000):
        r=smap.get(hex(a))
        if r: print("  e.g. %-10s -> %-14s %s" % (hex(a), r.get("name"), r.get("value","")[:40] if r.get("value") else r.get("kind")))

if __name__ == "__main__":
    main()
