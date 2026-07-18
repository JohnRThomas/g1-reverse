# COLLISION-03 + COLLISION-06 namespace integration

The ordered CPUAPP regeneration isolates four non-exact retained firmware owners while leaving the configured NRFX public owners intact.

- Retain-all strong collisions: **105 → 101**.
- Removed exactly: `nrfx_clock_init`, `nrfx_clock_stop`, `nrfx_nvmc_page_erase`, and `nrfx_nvmc_word_write`.
- No new collision symbol was introduced.
- The unresolved set is unchanged: `FUN_0005463e` and `FUN_00054688` remain the two separately tracked interior raw targets.
- Independent full-link probe: **3104/3104 compiled**, `link rc=0`.

This is namespace isolation, not SDK adoption. Raw address back-maps remain authoritative and no adoption overlay or retained-source exclusion is used for either batch.
