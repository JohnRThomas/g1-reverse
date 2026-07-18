# COLLISION-08 fail-closed report: NRFX QSPI

Decision: **retain and namespace all three firmware owners; do not adopt the configured SDK source unit**.

The immutable collision baseline contains two swapped identities. `0x000669f4` is the custom-instruction transfer owner, not erase; `0x00066bc4` is erase, not read. Signature scores were therefore recomputed against the corrected SDK sections.

| VA | Baseline label | Corrected identity | Firmware bytes/insns | SDK bytes/insns | Opcode | Shape | Exact |
|---|---|---|---:|---:|---:|---:|---|
| `0x00066994` | `nrfx_qspi_init` | `nrfx_qspi_init` | 70 / 25 | 64 / 26 | 0.431373 | 0.431373 | no |
| `0x000669f4` | `nrfx_qspi_erase` | `nrfx_qspi_cinstr_xfer` | 200 / 72 | 172 / 65 | 0.700730 | 0.671533 | no |
| `0x00066bc4` | `nrfx_qspi_read` | `nrfx_qspi_erase` | 158 / 56 | 156 / 59 | 0.782609 | 0.765217 | no |

## Required closure

`FUN_00066ae0` (`nrfx_qspi_mem_busy_check`) is a hidden missing reconstruction. It is called at `0x00060a7e` and `0x00060b86`, and calls the corrected `nrfx_qspi_cinstr_xfer` at `0x00066af8`. The already reconstructed `FUN_0008520c` chip-erase wrapper tail-calls the corrected erase owner at `0x00085210`.

Measured normal-link collision delta after namespace integration: **87 -> 84 (-3)**. No collision was added and the actionable unresolved set remains the two embedded SVC continuations. The immutable baseline remains unchanged.

## Implementation requirements

1. recover and CFG-verify FUN_00066ae0 as nrfx_qspi_mem_busy_check before namespace integration
2. namespace all three retained collision owners using corrected identities and preserve VA/raw back-maps
3. retarget the complete direct and transitive caller closure, including the FUN_0008520c tail call
4. retain the configured SDK public nrfx_qspi.c owner; do not create adoption authorization
5. prove an exact normal-link collision delta of -3 with no new collision or undefined symbol
