# COLLISION-06 fail-closed report: NRFX NVMC

Decision: **retain and namespace both firmware reconstructions; do not adopt the configured SDK owner**.

Both machine ABIs agree with NRFX (`page_erase(uint32_t)` and `word_write(uint32_t, uint32_t)`), and their valid paths use the expected NVMC CONFIGNS/CONFIG/READY registers. The decisive mismatch is configuration-dependent assertion behavior: the firmware contains active address/alignment assertion calls, while the configured NCS object expands `NRFX_ASSERT` to nothing.

| Function | Firmware / SDK bytes | Opcode / shape | Retained CFG | SDK-semantic negative control | Caller |
|---|---:|---:|---:|---:|---|
| `nrfx_nvmc_page_erase` | 76 / 60 | 0.666667 / 0.588235 | PASS 3 | FAIL 2/3 | `0x6125c` at `0x000612d8` (missing) |
| `nrfx_nvmc_word_write` | 94 / 32 | 0.333333 / 0.333333 | PASS 3 | FAIL 3/3 | `0x61310` at `0x000613a8` (missing) |

The two callers exist in the firmware reference graph but currently have no canonical reconstruction, so namespace implementation must include their recovery; renaming the definitions alone would leave the recovered call closure incomplete.

## Implementation closure

1. recover and CFG-verify caller FUN_0006125c, rewriting its 0x000612d8 call to g1_recon_nrfx_nvmc_page_erase
2. recover and CFG-verify caller FUN_00061310, rewriting its 0x000613a8 call to g1_recon_nrfx_nvmc_word_write
3. namespace both retained definitions while preserving raw address back-maps; do not add an adoption authorization or exclusion
4. regenerate readable/symbolized/retained metadata and require an exact collision delta of -2 with no new undefined symbols
5. keep the configured SDK public nrfx_nvmc.c owner intact; a future adoption would require rebuilding it with the firmware assertion glue and proving the complete source unit
