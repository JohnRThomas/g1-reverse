"""Emit byte-exact assembly blobs for functions that cannot be parity-reconstructed.
Each blob places the ORIGINAL image bytes at the function's real VA, exported under
its symbol name, so the image links and byte-matches. Correct ONLY when every
function (blob and reconstructed) is pinned to its original address (relative
branches inside a blob assume the original memory layout) -- which the link uses.

Usage: make_blobs.py <core> <addr_list.json>   (list of "0x..." strings)
Writes recon/blobs/<core>/blob_<addr>.S and a manifest.
LAST RESORT: only for functions no reconstruction could prove.
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
import sys, os, json
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract as ax, net_extract as nx

BASE = "/Users/freedomcoder/Projects/G1disasm2"
SCR = _g1_paths.scratchpad()

def main():
    core = sys.argv[1]
    addrs = [int(a, 16) if isinstance(a, str) else a for a in json.load(open(sys.argv[2]))]
    if core == "app":
        read = ax.read
        sizes = {f["entry"]: f["size"] for f in json.load(open(SCR + "/classified.json"))["functions"]}
        names = {f["entry"]: f.get("name") for f in json.load(open(SCR + "/classified.json"))["functions"]}
    else:
        read = nx.read
        funcs = {f["entry"]: f for f in json.load(open(SCR + "/net_funcs.json"))["functions"]}
        sizes = {e: f["size"] for e, f in funcs.items()}
        names = {e: f["name"] for e, f in funcs.items()}
    outd = BASE + "/recon/blobs/" + core
    os.makedirs(outd, exist_ok=True)
    manifest = []
    for va in addrs:
        size = sizes.get(va) or sizes.get(va & ~1)
        if not size:
            print("  no size for", hex(va)); continue
        name = names.get(va) or ("FUN_%08x" % va)
        data = read(va, size)
        lines = ["/* byte-exact blob: %s @ 0x%x (%d bytes) -- original image bytes,"
                 " could not be parity-reconstructed */" % (name, va, size),
                 "    .syntax unified", "    .thumb",
                 "    .section .text.%s,\"ax\",%%progbits" % name,
                 "    .global %s" % name, "    .thumb_func",
                 "    .type %s, %%function" % name, "%s:" % name]
        for off in range(0, len(data), 12):
            chunk = data[off:off + 12]
            lines.append("    .byte " + ", ".join("0x%02x" % b for b in chunk))
        lines.append("    .size %s, . - %s" % (name, name))
        open(os.path.join(outd, "blob_%x.S" % va), "w").write("\n".join(lines) + "\n")
        manifest.append({"addr": hex(va), "name": name, "size": size})
    json.dump(manifest, open(outd + "/manifest.json", "w"), indent=1)
    print("[%s] emitted %d blobs -> %s (total %d bytes)"
          % (core, len(manifest), outd, sum(m["size"] for m in manifest)))

if __name__ == "__main__":
    main()
