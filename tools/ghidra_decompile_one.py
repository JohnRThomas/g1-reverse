from ghidra.app.decompiler import DecompInterface, DecompileOptions
from ghidra.util.task import ConsoleTaskMonitor

args = getScriptArgs()
entry = toAddr(args[0])
out_path = args[1]
fn = currentProgram.getFunctionManager().getFunctionAt(entry)
decomp = DecompInterface()
opts = DecompileOptions()
opts.setMaxPayloadMBytes(256)
opts.setMaxInstructions(200000)
decomp.setOptions(opts)
decomp.openProgram(currentProgram)
res = decomp.decompileFunction(fn, 900, ConsoleTaskMonitor())
with open(out_path, "w") as out:
    out.write("body_ranges=%s\n" % ",".join("%s-%s" % (r.getMinAddress(), r.getMaxAddress()) for r in fn.getBody().getAddressRanges()))
    out.write("completed=%s message=%s\n" % (res.decompileCompleted(), res.getErrorMessage()))
    if res.decompileCompleted():
        out.write(res.getDecompiledFunction().getC())
