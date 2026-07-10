export const meta = {
  name: 'g1-known-false-redo',
  description: 'Fable agents properly reconstruct the confirmed false-proof functions',
  phases: [{ title: 'redo', detail: '3 Fable agents, 1 hard dispatcher each' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const BASE = '/Users/freedomcoder/Projects/G1disasm2'
const NB = 3
function prompt(i) {
  return `You reconstruct ONE Even G1 firmware function that is a CONFIRMED FALSE PROOF: its saved reconstruction passes the OLD harness but FAILS the fixed one (its switch/dispatch cases were never tested). Reconstruct it CORRECTLY. Do the work yourself; do NOT spawn sub-agents; do NOT edit tools/.

export RECON_LEDGER=${SCR}/knownfalse_ledger_${i}.json

Your target = element ${i}[0] of ${SCR}/known_false_redo.json {addr,name,core}:
  PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python -c "import json;print(json.load(open('${SCR}/known_false_redo.json'))[${i}][0])"

Env: PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python ; workdir ${BASE}. Use recon_kit for core=app, net_recon_kit for core=net (net base 0x01008000, bytes via net_extract).

1. Inspect: PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python tools/<kit>.py info 0xADDR
2. The existing reconstruction is WRONG on the switch cases. Find the dispatch: tbb/tbh [pc,rN] or ldr pc,[pc,...] or a chain of cmp-arg,#k branches. Read the jump-table bytes straight from the image (extract.read/read_u32 or net_extract) and decode EVERY case target. Reconstruct EACH case's real logic (not a placeholder), plus the default path. Match globals (absolute-address volatile ptrs w/ literal values, correct width/signedness), callee order, masks, loops exactly.
3. If Ghidra's size includes a trailing DATA table (little reachable code vs size), reconstruct ONLY the true code and prove at that size; emit the data table as a byte-exact rodata file (recon/data or recon/net/data).
4. Prove (fixed harness now exercises the cases):
   PYTHONSAFEPATH=1 RECON_LEDGER=$RECON_LEDGER ${BASE}/.venv/bin/python -c '
   import sys; sys.path.insert(0,"${BASE}/tools")
   import recon_kit   # or net_recon_kit
   src = r"""<C source>"""
   print(recon_kit.prove(0xADDR, SIZE, "NAME", src, nptr=NPTR, trials=300))'
   pass:True overwrites the false proof (auto-saves). Iterate up to ~15 times.
5. VERIFY your fix is stable: after a pass, re-run prove once more (fresh trials) to confirm it still passes. If it flaps, your case coverage is incomplete — keep fixing.
6. If genuinely unprovable (huge/pathological), report UNPROVEN with the exact structural reason — do NOT leave a knowingly-wrong reconstruction.

Report: PROVEN(trials, stable?) or UNPROVEN(reason).`
}
phase('redo')
const todo = (args && args.todo) || Array.from({ length: NB }, (_, i) => i)
const results = await parallel(todo.map((i) => () =>
  agent(prompt(i), { label: `kf:${i}`, phase: 'redo', agentType: 'general-purpose', model: 'fable' })))
log(`known-false redo: ${results.filter(Boolean).length}/${results.length}`)
return { agents: results.length, returned: results.filter(Boolean).length }
