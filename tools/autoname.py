"""
Auto-name unnamed application functions.

Primary signal (from the binary itself): the firmware's logging idiom passes the
CALLER's own function name as a string literal, e.g. LOG("%s(): ...", "foo_bar").
So a function that references a bare C-identifier string — especially alongside
a "%s()"/"():"-style format string — is almost certainly named by that
identifier. We resolve each DAT_xxxx literal in the Ghidra decompilation to its
pointer value, read the C-string at that flash address, and infer the name.

Secondary signal (open-source): the evenRealities-openCFW service-handler index
gives service-ID -> handler-name conventions (Dashboard_common_data_handler,
MessageNotify_common_data_handler, ...) used to label the BLE dispatch handlers.

Output: autonames.json  { "0xADDR": {"name":..., "source":"selfstr|opencfw",
                                     "evidence":...}, ... }
"""
import sys, re, json, string
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]{3,63}$")
DAT = re.compile(r"DAT_([0-9a-fA-F]{4,8})")
PRINTABLE = set(bytes(string.printable, "ascii")) - {0}

# words that are identifiers but not function names
STOP = {"NULL", "true", "false", "null", "None", "size", "public", "private",
        "Infinity", "index", "value", "data", "count", "buffer", "length",
        "status", "error", "result", "enable", "disable", "unknown", "default",
        "string", "number", "object", "array", "type", "name", "state"}

def read_cstr(va, maxlen=96):
    try:
        b = extract.read(va, maxlen)
    except Exception:
        return None
    out = bytearray()
    for ch in b:
        if ch == 0:
            break
        if ch not in PRINTABLE:
            return None
        out.append(ch)
    if not out:
        return None
    return out.decode("ascii", "ignore")

def strings_of(decomp):
    """Resolve every DAT_xxxx in the decompilation to the C-string it points to."""
    strs = []
    for m in DAT.finditer(decomp):
        dat_addr = int(m.group(1), 16)
        try:
            ptr = extract.read_u32(dat_addr)
        except Exception:
            continue
        s = read_cstr(ptr)
        if s:
            strs.append(s)
    return strs

def infer_name(decomp):
    strs = strings_of(decomp)
    if not strs:
        return None, None
    has_fmt = any(("%s()" in s) or ("():" in s) or ("%s(" in s) for s in strs)
    idents = [s for s in strs if IDENT.match(s) and s not in STOP
              and not s.startswith(("0x",))]
    # Require the logging idiom (a "%s()" / "():" format string) to be present —
    # that is the reliable self-name signal. Pick the identifier that is not a
    # format string and not a generic stop-word.
    uniq = [s for s in dict.fromkeys(idents)
            if "%" not in s and "(" not in s]
    if has_fmt and uniq:
        return uniq[0], ("selfstr+fmt: %r" % strs[:4])
    return None, None

def main():
    fw = {f["entry"]: f for f in json.load(open(SCR + "/app_funcs.json"))["functions"]}
    cls = {c["entry"]: c for c in json.load(open(SCR + "/classified.json"))["functions"]}
    out = {}
    taken = set()
    for e, c in cls.items():
        if c["class"] != "APPLICATION" or c["is_thunk"]:
            continue
        if c["ida_name"]:
            continue  # already named by the user
        f = fw[e]
        if not f["decompiled"]:
            continue
        nm, ev = infer_name(f["decompiled"])
        if nm:
            key = nm
            if key in taken:
                key = "%s_%x" % (nm, e)
            taken.add(key)
            out["0x%x" % e] = {"name": key, "source": "selfstr", "evidence": ev}
    json.dump(out, open(SCR + "/autonames.json", "w"), indent=1)
    print("auto-named (self-name strings):", len(out), "of the unnamed application funcs")
    for a, d in list(out.items())[:30]:
        print("  %s -> %s" % (a, d["name"]))

if __name__ == "__main__":
    main()
