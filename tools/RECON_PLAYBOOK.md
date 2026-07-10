# Reconstruction playbook (read fully before starting)

You reconstruct C source for functions of a smart-glasses firmware (nRF5340 app
core, ARM Cortex-M33 Thumb) whose owner lost the sources — a legitimate recovery
of the owner's own application code. A differential-emulation harness PROVES each
reconstruction is semantically identical to the original bytes.

## Hard rules
- **DO NOT spawn sub-agents / do not use the Agent tool.** Do every function
  YOURSELF in this session, sequentially. Delegating fragments the work.
- Run Python ONLY as: `PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python ...`
  (PYTHONSAFEPATH=1 is mandatory — a local struct.py otherwise shadows stdlib.)
- Working dir: /Users/freedomcoder/Projects/G1disasm2
- Use the RECON_LEDGER path given in your task prompt.

## Per function
1. `PYTHONSAFEPATH=1 .venv/bin/python tools/recon_kit.py info 0xADDR`
   → name, size, callees, Ghidra decompilation, annotated Thumb disasm.
   `ldr rX,[pc,#imm]` lines show `; [0xLITADDR] = 0xVALUE` — VALUE is the real
   global address / constant the code uses.
2. Write faithful C:
   - GLOBALS → fixed absolute-address pointers using the literal VALUE, and mark
     EVERY such pointer **`volatile`** (this forces one memory access per
     original instruction so the write/read trace matches — required).
     e.g. decomp `*DAT_00032eec` + `; [0x32eec] = 0x20019ef3`
        → `*(volatile uint8_t*)0x20019ef3UL`.
     Match width to the load/store: ldrb→uint8_t, ldrh→uint16_t, ldr→uint32_t;
     preserve signedness (ldrsb/ldrsh → int8_t/int16_t).
   - CALLEES → declare each `extern` (any prototype; they are modeled as
     identical order-keyed oracles for both versions — exact args/return type
     don't matter). Call them in the SAME ORDER under the SAME branch conditions.
     Use the callee name from `info`.
   - Match arithmetic, masks, shifts, comparisons, branches, loops EXACTLY.
   - The C function name MUST equal the `info` name. A size-2 `bx lr`/"nullsub"
     → `void name(void){}`.
3. Prove:
```
PYTHONSAFEPATH=1 RECON_LEDGER=$RECON_LEDGER .venv/bin/python -c '
import sys; sys.path.insert(0,"/Users/freedomcoder/Projects/G1disasm2/tools")
import recon_kit
src = r"""<C source>"""
print(recon_kit.prove(0xADDR, SIZE, "NAME", src, nptr=NPTR, trials=300))'
```
   - SIZE from info. NPTR = count of leading POINTER params. If unsure try 2,
     then 1, then 0 (0 for scalar/no params).
   - `'pass': True` = PROVEN (auto-saves recon/app/src/NAME.c).
   - `'pass': False, mismatches>0` → fix logic: wrong width, signed vs unsigned
     compare, wrong mask/shift/constant, missing/extra callee, wrong branch,
     forgot `volatile`, or GCC merged adjacent stores (add volatile).
   - `'stage':'compile'` → fix C syntax shown in the error.
4. Iterate to pass. After ~6 real attempts, mark UNPROVEN with a one-line reason
   (e.g. 64-bit return, callee-dependent loop termination, jump table, computed
   tail-call) and MOVE ON. Cover ALL functions in your batch; breadth first.

## Report back (concise)
total attempted, number PROVEN, and a list of UNPROVEN with one-line reasons.
Do NOT paste source.

> HARNESS IS FROZEN: do NOT edit tools/parity/*.py, tools/recon_kit.py, or tools/extract.py. If the harness seems buggy, report it in your summary — do not modify it.

> IMPORTANT: even for a function you expect to be UNPROVEN, still call recon_kit.prove(...) once with your best attempt so it records a ledger entry — otherwise the work-queue will keep re-assigning it.
