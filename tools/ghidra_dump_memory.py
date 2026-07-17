"""Ghidra headless post-script: report memory blocks and dump requested ranges."""

import json


args = getScriptArgs()
out_path = args[0]
ranges = []
for spec in args[1:]:
    start_s, size_s = spec.split(":", 1)
    ranges.append((int(start_s, 0), int(size_s, 0)))

memory = currentProgram.getMemory()
result = {"blocks": [], "ranges": []}
for block in memory.getBlocks():
    result["blocks"].append({
        "name": block.getName(),
        "start": "0x%x" % block.getStart().getOffset(),
        "end": "0x%x" % block.getEnd().getOffset(),
        "initialized": bool(block.isInitialized()),
        "loaded": bool(block.isLoaded()),
    })

for start, size in ranges:
    address = toAddr(start)
    buf = bytearray(size)
    got = 0
    error = None
    block = memory.getBlock(address)
    if block is None:
        error = "unmapped"
    elif not block.isInitialized():
        error = "uninitialized block %s" % block.getName()
    else:
        got = memory.getBytes(address, buf)
    result["ranges"].append({
        "start": "0x%x" % start,
        "size": size,
        "read": got,
        "bytes": "".join("%02x" % value for value in buf[:got]),
        "error": error,
    })

with open(out_path, "w") as out:
    json.dump(result, out, indent=2, sort_keys=True)
