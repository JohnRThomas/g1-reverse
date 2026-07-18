# CPUAPP SDK/config residue ownership

Report-only resolution of the 173 SDK/config rows from the retain-all link.
A local (`t`) symbol is evidence for its translation unit, not a public
link target; these rows explicitly require whole-source-unit ownership.

## Summary

| Action | Symbols |
|---|---:|
| `adopt_complete_source_unit` | 9 |
| `manual_owner_review` | 1 |
| `reconcile_inline_at_callsite` | 3 |

Public safe candidates: **0**. Source-unit/inline cases: **12**.

## Public link/adoption candidates (0)

These have public archive exports. Exact signature hits can be adopted
directly; approximate hits retain an explicit ABI-check gate.



## Deliberate exclusions

Application-owner classifier false positives (7): .

`nrf_cc3xx_platform_abort` at `0x00050af8` is not satisfied by
the same-named local CC312 archive function already adopted at
`0x00079590`; it remains an identity-collision review item.

## Per-symbol action

| Symbol | Owner | Kind | Source/archive | Action |
|---|---|---|---|---|
| `FUN_0007def6` | `free_list_remove` | `archive_local` | `zephyr/lib/os/heap.c` | `adopt_complete_source_unit` |
| `FUN_00080fd2` | `hci_id_add` | `archive_local` | `zephyr/subsys/bluetooth/host/id.c` | `adopt_complete_source_unit` |
| `__nrfy_internal_spim_event_handle` | `__nrfy_internal_spim_event_handle` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c` | `adopt_complete_source_unit` |
| `buffer_write` | `buffer_write` | `archive_local` | `zephyr/subsys/logging/log_output.c` | `adopt_complete_source_unit` |
| `compare_int_lock` | `compare_int_lock` | `archive_local` | `zephyr/drivers/timer/nrf_rtc_timer.c` | `adopt_complete_source_unit` |
| `event_clear` | `event_clear` | `archive_local` | `zephyr/drivers/timer/nrf_rtc_timer.c` | `adopt_complete_source_unit` |
| `flag_test_and_clear` | `flag_test_and_clear` | `archive_local` | `zephyr/kernel/work.c` | `adopt_complete_source_unit` |
| `free_list_remove_bidx` | `free_list_remove_bidx` | `archive_local` | `zephyr/lib/os/heap.c` | `adopt_complete_source_unit` |
| `k_uptime_get_0` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_4` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_7` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `merge_chunks` | `merge_chunks` | `archive_local` | `zephyr/lib/os/heap.c` | `adopt_complete_source_unit` |
| `net_buf_tailroom` | `net_buf_tailroom` | `unresolved` | `unresolved` | `manual_owner_review` |
