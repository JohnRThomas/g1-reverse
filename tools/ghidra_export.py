# Ghidra headless postScript (Jython)
# Exports every function: name, entry, size, bytes(hex), decompiled C, callees, flags.
# Usage: analyzeHeadless <proj_dir> <proj_name> -process <prog> -noanalysis \
#           -scriptPath tools -postScript ghidra_export.py <out.json>
import json
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

out_path = getScriptArgs()[0] if getScriptArgs() else "/tmp/ghidra_functions.json"

prog = currentProgram
fm = prog.getFunctionManager()
listing = prog.getListing()
mem = prog.getMemory()
monitor = ConsoleTaskMonitor()

decomp = DecompInterface()
decomp.openProgram(prog)

def func_bytes(fn):
    # Concatenate bytes across the function body address ranges.
    data = bytearray()
    body = fn.getBody()
    for rng in body.getAddressRanges():
        start = rng.getMinAddress()
        n = int(rng.getLength())
        buf = bytearray(n)
        try:
            got = mem.getBytes(start, buf)
            data += bytearray(buf[:got])
        except:
            pass
    return data

results = []
count = 0
for fn in fm.getFunctions(True):
    count += 1
    ep = fn.getEntryPoint()
    entry = int(ep.getOffset())
    body = fn.getBody()
    size = int(body.getNumAddresses())
    callees = []
    try:
        for c in fn.getCalledFunctions(monitor):
            callees.append(c.getName())
    except:
        pass
    # Decompile (skip huge / thunk for speed but still record metadata)
    ccode = ""
    if not fn.isThunk() and not fn.isExternal():
        try:
            res = decomp.decompileFunction(fn, 60, monitor)
            if res and res.decompileCompleted():
                ccode = res.getDecompiledFunction().getC()
        except:
            ccode = ""
    b = func_bytes(fn)
    results.append({
        "name": fn.getName(),
        "entry": entry,
        "entry_hex": "0x%x" % entry,
        "size": size,
        "bytes": b.encode("hex") if hasattr(b, "encode") else "".join("%02x" % x for x in b),
        "thumb": True,
        "is_thunk": bool(fn.isThunk()),
        "is_external": bool(fn.isExternal()),
        "calling_convention": str(fn.getCallingConventionName()),
        "signature": fn.getPrototypeString(True, False),
        "callees": sorted(set(callees)),
        "decompiled": ccode,
    })
    if count % 200 == 0:
        print("...exported %d functions" % count)

with open(out_path, "w") as f:
    json.dump({"program": prog.getName(),
               "image_base": int(prog.getImageBase().getOffset()),
               "count": len(results),
               "functions": results}, f)
print("EXPORT DONE: %d functions -> %s" % (len(results), out_path))
