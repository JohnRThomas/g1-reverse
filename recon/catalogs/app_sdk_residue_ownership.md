# CPUAPP SDK/config residue ownership

Fail-closed ownership resolution of the pinned 13 SDK/config rows from
the retain-all link. Ownership is resolved for all 13; this does not
authorize weak aliases or duplicate standalone bodies.
A local (`t`) symbol is evidence for its translation unit, not a public
link target; these rows explicitly require whole-source-unit ownership.

## Summary

| Action | Symbols |
|---|---:|
| `adopt_complete_source_unit` | 8 |
| `link_public_owner` | 1 |
| `reconcile_inline_at_callsite` | 4 |

Public safe candidates: **1**. Source-unit/inline cases: **12**.

Resolved: **13**. Manual: **0**.

## Public link/adoption candidates (1)

These have public archive exports. Exact signature hits can be adopted
directly; approximate hits retain an explicit ABI-check gate.

`net_buf_tailroom`

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
| `__nrfy_internal_spim_event_handle` | `__nrfy_internal_spim_event_handle` | `header_inline` | `modules/hal/nordic/nrfx/haly/nrfy_spim.h` | `reconcile_inline_at_callsite` |
| `buffer_write` | `buffer_write` | `archive_local` | `zephyr/subsys/logging/log_output.c` | `adopt_complete_source_unit` |
| `compare_int_lock` | `compare_int_lock` | `archive_local` | `zephyr/drivers/timer/nrf_rtc_timer.c` | `adopt_complete_source_unit` |
| `event_clear` | `event_clear` | `archive_local` | `zephyr/drivers/timer/nrf_rtc_timer.c` | `adopt_complete_source_unit` |
| `flag_test_and_clear` | `flag_test_and_clear` | `archive_local` | `zephyr/kernel/work.c` | `adopt_complete_source_unit` |
| `free_list_remove_bidx` | `free_list_remove_bidx` | `archive_local` | `zephyr/lib/os/heap.c` | `adopt_complete_source_unit` |
| `k_uptime_get_0` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_4` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_7` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `merge_chunks` | `merge_chunks` | `archive_local` | `zephyr/lib/os/heap.c` | `adopt_complete_source_unit` |
| `net_buf_tailroom` | `net_buf_simple_tailroom` | `archive_public` | `zephyr/subsys/net/buf_simple.c` | `link_public_owner` |
