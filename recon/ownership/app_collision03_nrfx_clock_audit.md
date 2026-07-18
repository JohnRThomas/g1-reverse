# COLLISION-03: `nrfx_clock` ownership audit

Decision: **retain the firmware implementations under namespaced symbols; do not adopt either configured SDK collision.** This file is report-only and authorizes no manifest or retained-source change.

The two collision names hide three firmware functions:

| Firmware VA | Actual identity | Firmware / configured size | Finding |
|---|---|---:|---|
| `0x65000` | private `clock_stop(domain)` | 384 / 354 bytes | Incorrectly named `nrfx_clock_stop`; it is the private implementation and is not relocation-masked exact. |
| `0x65190` | checked `nrfx_clock_init(handler)` | 48 / 32 bytes | Same non-null state semantics, but firmware asserts on a null handler and uses pinned state at `0x2000b31c`. |
| `0x65324` | checked public `nrfx_clock_stop(domain)` | 56 / 4 bytes | Firmware asserts `module_initialized`; configured SDK wrapper is only a tail branch to private `clock_stop`. |

The configured Zephyr/NCS object deliberately compiles `NRFX_ASSERT` as an empty macro. Its local eight-byte `.bss.m_clock_cb` has the same handler/initialized layout as firmware state, but it is different link storage. Consequently, binding firmware callers to the configured object would remove observable assertion calls and split clock state.

Authoritative CFG verification passes for the retained firmware bodies: `0x65000` covers nine cases and domains 0–4, `0x65190` covers the null/non-null selector, and `0x65324` covers its initialized-state branch. The exact all-image call-site closure is recorded in the JSON audit, including the three domain veneers at `0x83874`, `0x8387a`, and `0x83880`.

Recommended implementation closure:

1. Rename `0x65000` to a private non-colliding identity such as `g1_clock_stop_impl`.
2. Rename `0x65190` and `0x65324` to checked G1-specific public identities and correct both prototypes to their one-argument NRFX ABIs.
3. Retarget every recorded firmware call site to those namespaced owners.
4. Leave configured `nrfx_clock.c` present for SDK consumers, but do not exclude any of these three firmware bodies or redirect firmware callers to its no-assert globals.

Machine-readable digests, opcode/shape scores, relocations, state layout, CFG results, and caller closure are in `app_collision03_nrfx_clock_audit.json`.
