# Net-core reconstruction playbook

Reconstruct C for functions of the Even G1 net core (nRF5340 CPUNET, NCS 2.5.1).
A differential-emulation harness PROVES each reconstruction semantically identical
to the original bytes. Do the work YOURSELF; do NOT spawn sub-agents; do NOT edit
anything under tools/.

## Env
- Run: `PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python ...`
- workdir /Users/freedomcoder/Projects/G1disasm2 ; use the RECON_LEDGER given.
- Net core links at base 0x01008000 (this is handled for you).

## Per function
1. Inspect: `PYTHONSAFEPATH=1 .venv/bin/python tools/net_recon_kit.py info 0xADDR`
   → name, size, callees, Ghidra decompilation, annotated Thumb disasm
   (`ldr [pc,#imm]` lines show `; [0xLIT] = 0xVALUE` = the real global/const).
2. Write faithful C, SAME conventions as the app core:
   - globals → fixed absolute-address `volatile` pointers using the literal VALUE
     (match width to ldrb/ldrh/ldr; preserve signedness).
   - callees → `extern` (modeled as identical oracles); call in the same order.
   - match arithmetic/masks/branches/loops exactly; function name = the info name.
3. Prove:
```
PYTHONSAFEPATH=1 RECON_LEDGER=$RECON_LEDGER .venv/bin/python -c '
import sys; sys.path.insert(0,"/Users/freedomcoder/Projects/G1disasm2/tools")
import net_recon_kit
src = r"""<C source>"""
print(net_recon_kit.prove(0xADDR, SIZE, "NAME", src, nptr=NPTR, trials=300))'
```
   - `pass:True` = PROVEN (auto-saves recon/net/src/NAME.c). Supervisor loops that
     never return are auto-handled (trace-prefix compare). On mismatch fix logic;
     on compile error fix syntax. ALWAYS call prove once even for expected-UNPROVEN.
4. After ~6 attempts mark UNPROVEN with a one-line reason and move on.

## Report
total attempted, PROVEN count, UNPROVEN list with one-line reasons. No source pasted.
