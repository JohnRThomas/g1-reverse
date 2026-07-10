# Ghidra headless postScript (Jython): export the reliable reference graph.
# For every function: outbound CALL refs (to functions) and DATA refs (to
# data/rodata addresses), plus inbound callers. Uses Ghidra's ReferenceManager
# (authoritative), not decompilation parsing.
# Usage: analyzeHeadless <proj> <name> -process <prog> -readOnly -noanalysis
#          -scriptPath tools -postScript ghidra_refgraph.py <out.json>
import json
from ghidra.program.model.symbol import RefType

out_path = getScriptArgs()[0] if getScriptArgs() else "/tmp/refgraph.json"
prog = currentProgram
fm = prog.getFunctionManager()
refmgr = prog.getReferenceManager()
listing = prog.getListing()

# map: address -> function entry it belongs to
def fn_at(addr):
    f = fm.getFunctionContaining(addr)
    return int(f.getEntryPoint().getOffset()) if f else None

funcs = {}
for fn in fm.getFunctions(True):
    ep = int(fn.getEntryPoint().getOffset())
    funcs[ep] = {"name": fn.getName(), "size": int(fn.getBody().getNumAddresses()),
                 "calls": set(), "data_refs": set(), "callers": set()}

for fn in fm.getFunctions(True):
    ep = int(fn.getEntryPoint().getOffset())
    body = fn.getBody()
    it = listing.getInstructions(body, True)
    while it.hasNext():
        insn = it.next()
        for ref in insn.getReferencesFrom():
            rt = ref.getReferenceType()
            to = ref.getToAddress()
            if to is None:
                continue
            toff = int(to.getOffset())
            if rt.isCall():
                tgt = fn_at(to)
                if tgt is not None:
                    funcs[ep]["calls"].add(tgt)
                    if tgt in funcs:
                        funcs[tgt]["callers"].add(ep)
            elif rt.isData() or rt.isRead() or rt.isWrite():
                funcs[ep]["data_refs"].add(toff)

res = {}
for ep, d in funcs.items():
    res["0x%x" % ep] = {"name": d["name"], "size": d["size"],
                        "calls": ["0x%x" % x for x in sorted(d["calls"])],
                        "data_refs": ["0x%x" % x for x in sorted(d["data_refs"])],
                        "callers": ["0x%x" % x for x in sorted(d["callers"])]}
with open(out_path, "w") as f:
    json.dump({"program": prog.getName(), "count": len(res), "functions": res}, f)
print("REFGRAPH DONE: %d functions -> %s" % (len(res), out_path))
