"""Symbolization engine: turn symbol_map.json into (a) definition headers and
(b) rewritten sources where absolute addresses become named symbols / string
literals. DRY-RUN by default (reports coverage, writes nothing to sources).

Substitution rules per map entry:
  string       -> replace the address literal with a C string "..."  (inline)
  ram_global   -> replace with &NAME (address-of the extern global)
  kobject      -> replace with &NAME
  rodata_ref   -> replace with NAME (extern const symbol at that VA)
  partition_off-> replace with NAME (#define)
  mmio_reg     -> replace with NAME (#define register address)
  const        -> left as literal (no name)

Correctness gate is NOT per-function emulation (symbols float); it is the whole-
image byte-match at assembly. This tool only prepares/reports; it never claims a
proof. Use --write to emit into recon/symbolized/<core>/ (copies, originals kept).
"""
import sys, os, re, json, glob, collections

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
BASE = "/Users/freedomcoder/Projects/G1disasm2"

CORE = "app"
WRITE = False
for a in sys.argv[1:]:
    if a == "--write": WRITE = True
    else: CORE = a

if CORE == "app":
    NAMED = BASE + "/recon/named"; MAP = SCR + "/symbol_map.json"
else:
    NAMED = BASE + "/recon/net/src"; MAP = SCR + "/symbol_map_net.json"
OUTSRC = BASE + "/recon/symbolized/" + CORE
HDR = BASE + "/recon/symbols"

smap = json.load(open(MAP))

def c_string(s):
    out = '"'
    for ch in s:
        if ch == '\\': out += '\\\\'
        elif ch == '"': out += '\\"'
        elif ch == '\n': out += '\\n'
        elif ch == '\r': out += '\\r'
        elif ch == '\t': out += '\\t'
        elif 32 <= ord(ch) < 127: out += ch
        else: out += '\\x%02x' % ord(ch)
    return out + '"'

# how to render each address at a use-site
def repl_for(rec):
    k = rec.get("kind")
    n = rec.get("name")
    if k == "string":
        return "((unsigned long)&%s)" % n
    offset = int(rec.get("symbol_offset", 0))
    suffix = (" + 0x%x" % offset if offset > 0 else
              " - 0x%x" % -offset if offset < 0 else "")
    if k in ("ram_global", "kobject"):
        if rec.get("is_buffer"):
            return "((unsigned long)%s%s)" % (n, suffix)
        return "((unsigned long)&%s%s)" % (n, suffix)
    if k == "rodata_ref":
        return "((unsigned long)&%s%s)" % (n, suffix)
    if k in ("partition_off", "mmio_reg"):
        return n
    if k == "function_addr":
        return n
    return None  # const: keep literal

ADDRRE = re.compile(
    r'(?<![A-Za-z0-9_])0x[0-9a-fA-F]{4,8}(?:UL|ul|U|u|L|l)?(?![A-Za-z0-9_])')

# comments and string/char literals — spans where addresses must NOT be touched
# (substituting inside a /*...*/ block would inject a nested */ and break it;
# inside a string it would corrupt data).
_SKIP = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.DOTALL)

def substitute(txt):
    used = collections.Counter()
    def apply(segment):
        def rep(m):
            raw = m.group(0)
            # UINT*_C pastes an integer suffix onto its token argument.  A
            # symbolic expression or already-suffixed macro is invalid there;
            # preserve the numeric literal at that use site.
            if re.search(r'UINT(?:8|16|32|64)_C\(\s*$', segment[:m.start()]):
                return raw
            v = int(re.sub(r'[ULul]+$', '', raw), 16)
            rec = smap.get(hex(v))
            if not rec: return raw
            r = repl_for(rec)
            if r is None: return raw
            used[rec.get("kind")] += 1
            # keep the ORIGINAL address inline so a wrong/coincidental substitution
            # is always auditable and the real value is recoverable at review time.
            return "%s /*=%s*/" % (r, hex(v))
        return ADDRRE.sub(rep, segment)
    # walk the text, copying skip-spans (comments/strings) verbatim and only
    # applying the address substitution to the code in between.
    out = []
    pos = 0
    for m in _SKIP.finditer(txt):
        out.append(apply(txt[pos:m.start()]))
        out.append(m.group(0))
        pos = m.end()
    out.append(apply(txt[pos:]))
    return "".join(out), used

# types the compat header + stdint make legal; anything else in a decompiler-
# derived ctype is a guess we must not emit verbatim or it breaks the whole header.
_OK_TYPES = set("""void char short int long float double signed unsigned
uint8_t uint16_t uint32_t uint64_t int8_t int16_t int32_t int64_t
u8 u16 u32 u64 s8 s16 s32 s64 uchar byte uint ushort ulong bool size_t uintptr_t
undefined undefined1 undefined2 undefined4 undefined8 uint3""".split())

# normalize every decompiler/short spelling to a standard stdint type so the
# generated HEADER never emits a name a self-contained source might redefine.
_NORM = {
    "u8": "uint8_t", "u16": "uint16_t", "u32": "uint32_t", "u64": "uint64_t",
    "s8": "int8_t", "s16": "int16_t", "s32": "int32_t", "s64": "int64_t",
    "i8": "int8_t", "i16": "int16_t", "i32": "int32_t", "i64": "int64_t",
    "uchar": "uint8_t", "byte": "uint8_t", "uint": "unsigned int",
    "ushort": "unsigned short", "ulong": "unsigned long",
    "undefined": "uint8_t", "undefined1": "uint8_t", "undefined2": "uint16_t",
    "undefined4": "uint32_t", "undefined8": "uint64_t", "uint3": "uint32_t",
}
_BUILTIN = {
    "uint8_t": "unsigned char", "int8_t": "signed char",
    "uint16_t": "unsigned short", "int16_t": "signed short",
    "uint32_t": "unsigned int", "int32_t": "signed int",
    "uint64_t": "unsigned long long", "int64_t": "signed long long",
    "uintptr_t": "unsigned long", "size_t": "unsigned int",
}
def builtin_type(value):
    for old, new in _BUILTIN.items():
        value = re.sub(r'\b%s\b' % re.escape(old), new, value)
    return value

def san_ctype(ct):
    """Return a STANDARD compilable type for a decompiler-derived ctype string.
    Pointers/callbacks -> void*; struct/union kept; short names normalized to
    stdint; unknown scalar -> uintptr_t."""
    if not ct:
        return "uint32_t"
    ct = ct.strip()
    if "*" in ct or ct.endswith("_cb") or ct.endswith("_cb_t") or ct.endswith("_fn") \
       or (ct.endswith("_t") and ("cb" in ct or "fp" in ct or "func" in ct)):
        return "void *"
    if ct.startswith("struct") or ct.startswith("union") or ct.startswith("enum"):
        return ct
    quals = " ".join(w for w in ct.split() if w in ("volatile", "const"))
    base = ct.replace("volatile", "").replace("const", "").replace("[]", "").strip()
    norm = _NORM.get(base)
    if norm:
        return builtin_type((quals + " " + norm).strip())
    if all(b in _OK_TYPES or b in ("volatile", "const") for b in ct.replace("[]","").split()):
        # already standard/stdint (u8 etc. handled above); keep as-is
        normalized = " ".join(_NORM.get(w, w) for w in ct.replace("[]","").split())
        return builtin_type(normalized)
    return "unsigned long"

def gen_headers():
    os.makedirs(HDR, exist_ok=True)
    globs, parts, regs, rodata, functions = [], [], [], [], []
    for a, rec in sorted(smap.items(), key=lambda kv: int(kv[0], 16)):
        k = rec.get("kind"); n = rec.get("name"); v = int(a, 16)
        if rec.get("symbol_offset", 0):
            continue
        if k in ("ram_global",):
            ct = san_ctype(rec.get("ctype", "uint32_t"))
            if rec.get("is_buffer"): globs.append("extern unsigned char %s[]; /* @%s */" % (n, a))
            else: globs.append("extern volatile %s %s; /* @%s */" % (ct.replace("[]",""), n, a))
        elif k == "kobject":
            globs.append("extern struct k_%s_placeholder %s; /* %s @%s conf=%s */"
                         % (rec.get("kobj_type","obj"), n, rec.get("kobj_type"), a, rec.get("kobj_conf")))
        elif k == "partition_off":
            parts.append("#define %-20s %sUL" % (n, a))
        elif k == "mmio_reg":
            regs.append("#define %-16s %sUL" % (n, a))
        elif k in ("rodata_ref", "string"):
            rodata.append("extern const unsigned char %s[]; /* @%s */" % (n, a))
        elif k == "function_addr":
            functions.append("#define %-36s %s /* %s */" %
                             (n, a, rec.get("function_name", "function")))
    guard = "G1_%s_SYMBOLS_H" % CORE.upper()
    lines = ["#ifndef %s" % guard, "#define %s" % guard,
             "#ifndef bool", "#define bool _Bool", "#define true 1", "#define false 0", "#endif", "",
             "/* ---- flash partitions ---- */", *sorted(set(parts)), "",
             "/* ---- MMIO registers ---- */", *sorted(set(regs)), "",
             "/* ---- function addresses ---- */", *sorted(set(functions)), "",
             "/* ---- RAM globals / kernel objects (%d) ---- */" % len(globs), *globs, "",
             "/* ---- rodata table externs (%d) ---- */" % len(set(rodata)), *sorted(set(rodata)), "",
             "#endif"]
    path = HDR + "/g1_%s_symbols.h" % CORE
    if WRITE:
        open(path, "w").write("\n".join(lines) + "\n")
    return path, len(globs), len(parts), len(regs), len(set(rodata)), len(set(functions))

def main():
    files = glob.glob(NAMED + "/*.c")
    expected = {os.path.basename(path) for path in files}
    total = collections.Counter()
    remain_addr = collections.Counter()
    if WRITE: os.makedirs(OUTSRC, exist_ok=True)
    for f in files:
        txt = open(f).read()
        new, used = substitute(txt)
        new = re.sub(r'(\bextern\s+[^;\n()]+\b[A-Za-z_$][\w$]*)\s*\(\s*\.\.\.\s*\)\s*;',
                     r'\1();', new)
        total.update(used)
        # count residual absolute addrs that stayed literal (const-class / unmapped)
        for m in ADDRRE.findall(new):
            v = int(re.sub(r'[ULul]+$', '', m), 16)
            if v >= 0x1000 and hex(v) in smap and smap[hex(v)].get("kind") == "const":
                remain_addr["const_kept"] += 1
        if WRITE:
            hdr_inc = '#include "g1_%s_symbols.h"\n' % CORE
            rendered = hdr_inc + new
            rendered = "\n".join(line.rstrip() for line in rendered.splitlines()).rstrip() + "\n"
            open(os.path.join(OUTSRC, os.path.basename(f)), "w").write(rendered)
    if WRITE:
        for path in glob.glob(OUTSRC + "/*.c"):
            if os.path.basename(path) not in expected:
                os.unlink(path)
    path, ng, npart, nreg, nrod, nfunc = gen_headers()
    print("[%s] files: %d  | substitutions by kind:" % (CORE, len(files)))
    for k, n in total.most_common():
        print("   %-14s %6d" % (k, n))
    print("   header:", path, "(%swritten)" % ("" if WRITE else "DRY-not-"))
    print("   header symbols: globals=%d partitions=%d regs=%d rodata=%d functions=%d" %
          (ng, npart, nreg, nrod, nfunc))
    print("   const literals intentionally kept:", remain_addr["const_kept"])
    print("   mode:", "WROTE recon/symbolized/%s/" % CORE if WRITE else "DRY-RUN (no source files written)")

if __name__ == "__main__":
    main()
