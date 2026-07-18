# COLLISION-09: asserted GPPI closure

Decision: retain the recovered GPPI endpoint functions under `g1_recon_*` names. The pinned NCS 2.5.1 object compiles out `NRFX_ASSERT`; the firmware executes explicit null-endpoint diagnostics, so public SDK adoption is not semantics-faithful.

`FUN_000850dc` was incorrectly catalogued and excluded as `net_buf_simple_push_mem`. Its two calls are the recovered event- and task-endpoint setup functions, exactly matching `nrfx_gppi_channel_endpoints_setup`. A fail-closed retention override now revokes that stale exclusion without modifying the immutable baseline.

All five owners and all three direct callers pass CFG verification. Removing the task-endpoint null assertion fails the selected null path. The normal-link collision set moves exactly **84 → 82**, removing only `nrfx_gppi_task_endpoint_setup` and `nrfx_gppi_task_endpoint_clear`; no collision is added. The partial full link compiles **3106/3106** and links successfully. The actionable unresolved set remains the two embedded SVC continuations.
