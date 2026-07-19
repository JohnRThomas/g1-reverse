# CPUAPP boot-emulation blockers

Status: 2026-07-19. Emulator: `tools/g1_boot_emulator.py` (Unicorn Cortex-M33).
Image: `app_update.bin` (sha `e0614feb…`). Budget 3,000,000 instructions.

## Milestone chain reached (strict model)

The original image now boots through, in order:

```
reset (0x50a98) → .bss/.data init (memset/memcpy)
→ region_init → arm_core_mpu_configure → MPU dynamic-region marking
→ nordicsemi_nrf53_init   [pinned milestone]
→ clock_control_nrf_init  [pinned milestone]
→ Zephyr kernel: log_msg, sys_heap (chunk_set/free_list_add)
→ nrfx_gpiote_init / arch_irq_enable
→ nrf_cc3xx_platform_init → CC_LibInit → CC_PalInit
→ RndStartupTest → LLF_RND_RunTrngStartupTest → startTrngHW   ← BLOCKED HERE
```

45 unique functions entered, no unmapped-memory or CPU fault. This establishes
boot evidence to ~E2/E3 (SoC + pre-kernel + kernel + early driver init).

## Blockers found and resolved (in order)

1. **FICR/UICR zero-fill** — boot scans a FICR table (`0xff0300+n*8`) and stores
   through a pointer unless the entry reads `0xffffffff`. Fix: seed the FICR/UICR
   window to `0xff` (flash-erased default) and pin INFO.PART/RAM/FLASH. Real HW
   behaviour, not a bypass.
2. **`arm_mpu.c` DREGION assert** — asserts `MPU_TYPE.DREGION == 8`. Fix: model
   the Cortex-M33 SCB/MPU core registers (`CPUID=0x410fd214`, `MPU_TYPE=0x800`).
3. **MPU register indirection** — dynamic-region marking reads regions back via
   RNR-selected `RBAR/RLAR` (+A1–A3 aliases). Fix: a stateful 8-region ARMv8-M
   MPU model.
4. **CMSE `TT` instruction** — `arm_cmse_mpu_region_get` uses `tt r3, r0`, which
   Unicorn does not implement (returned "no region" → `arm_mpu.c:299` "Marking
   areas for dynamic regions failed" assert loop). Fix: a **runtime intrinsic
   override** (plan pref #4) that emulates `TT` against the modeled MPU regions
   and resumes Thumb-safely (stop + restart at pc+4). Image is not altered.

## Current blocker

**CC312 (CryptoCell) TRNG hardware startup test.** `startTrngHW` /
`LLF_RND_GetRoscSampleCnt` busy-poll CryptoCell registers around `0x5084_xxxx`
(e.g. `0x50845130`, `0x50845910`, `0x50846e30`) waiting for ring-oscillator
entropy that the unmodeled peripheral never supplies → infinite poll.

Resolution options, in plan preference order:
1. Model the CC312 TRNG: return an EHR/valid flag and deterministic (seeded)
   entropy words so the startup test completes and RNG init proceeds.
2. If full modeling is impractical, a labelled runtime override of the TRNG
   startup-test result (documented, seed-recorded) — never a blanket
   "all crypto succeeds".

## Model assumptions currently in effect

- `intrinsic:TT emulated vs modeled MPU`
- unmodeled peripheral reads → 0 (recorded): CC312 space `0x5084_xxxx`,
  `0x5000d170`. These are the next model targets.

## Reproduce

```sh
cd /tmp && PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/tools/g1_boot_emulator.py \
  boot /Users/freedomcoder/Projects/G1disasm2/app_update.bin \
  --budget 3000000 --report recon/emulator/reports/original_boot.json
```
