# CPUNET private SDC/MPSL recovery worklist

Fail-closed backlog: archive identities are provenance only. Each entry must retain C and pass `cfg_verify`; no blobs or archive replacement are authorized.

- Unique functions: **92** (84 catalogued, 8 catalog-missed)
- Current providers absent: **92**
- Dependency components: **74**

## Suggested dependency-closed shards

| Shard | Functions | True extent | Addresses |
|---|---:|---:|---|
| `net-private-1` | 1 | 4488 | `0x01014b18` |
| `net-private-2` | 16 | 2894 | `0x01022a30`, `0x01022ea8`, `0x01022f0c`, `0x010231c8`, `0x01023d38`, `0x01023e88`, `0x01024440`, `0x0102445c`, `0x010245d8`, `0x01024c6c`, `0x0102524c`, `0x010256dc`, `0x010257e4`, `0x0102583c`, `0x01025c44`, `0x01025c9c` |
| `net-private-3` | 13 | 1000 | `0x01012ad4`, `0x01016170`, `0x0101d890`, `0x0101f624`, `0x01023ac4`, `0x01025a84`, `0x01025cc8`, `0x01025cf0`, `0x0102693a`, `0x01026a7e`, `0x01026acc`, `0x010273c6`, `0x01028256` |
| `net-private-4` | 12 | 1000 | `0x0100d6e8`, `0x010126c8`, `0x01012714`, `0x010129b8`, `0x0101618c`, `0x010199f4`, `0x0101df84`, `0x01020820`, `0x01021ac0`, `0x01026b58`, `0x01027846`, `0x01027ef2` |
| `net-private-5` | 12 | 1012 | `0x01012150`, `0x01013da8`, `0x01019eb4`, `0x01019ef8`, `0x0101e090`, `0x01022a50`, `0x0102590c`, `0x010269ce`, `0x01026dae`, `0x01027ed4`, `0x010280d8`, `0x0102a208` |
| `net-private-6` | 12 | 1010 | `0x0101dda8`, `0x0101ded0`, `0x0101e2fc`, `0x010207cc`, `0x01021940`, `0x01025998`, `0x01026d16`, `0x010280be`, `0x010282fc`, `0x0102894a`, `0x0102941c`, `0x010298a8` |
| `net-private-7` | 13 | 1000 | `0x01010890`, `0x01011664`, `0x01018df8`, `0x01021634`, `0x01025d0c`, `0x01026bfe`, `0x010270e8`, `0x01027a4a`, `0x01027a94`, `0x0102961a`, `0x0102971e`, `0x010297b4`, `0x01029882` |
| `net-private-8` | 13 | 1000 | `0x0100ef08`, `0x0100f86c`, `0x0101233c`, `0x01012694`, `0x0101e1e4`, `0x01022e34`, `0x0102665c`, `0x01027044`, `0x01027302`, `0x010292ec`, `0x01029b38`, `0x0102a1e0`, `0x0102a1ea` |

## Functions

| Address | Primary | Family | Declared / true | Dependencies | Shard |
|---|---|---|---:|---|---|
| `0x0100d6e8` | `sdc_conn_recovery_window_update` | `softdevice_controller` | 42 / 42 |  | `net-private-4` |
| `0x0100ef08` | `FUN_0100ef08` | `softdevice_controller` | None / 60 |  | `net-private-8` |
| `0x0100f86c` | `FUN_0100f86c` | `softdevice_controller` | 50 / 50 |  | `net-private-8` |
| `0x01010890` | `FUN_01010890` | `softdevice_controller` | 40 / 40 |  | `net-private-7` |
| `0x01011664` | `FUN_01011664` | `softdevice_controller` | None / 186 |  | `net-private-7` |
| `0x01012150` | `FUN_01012150` | `softdevice_controller` | 38 / 38 |  | `net-private-5` |
| `0x0101233c` | `FUN_0101233c` | `softdevice_controller` | 230 / 230 |  | `net-private-8` |
| `0x01012694` | `FUN_01012694` | `softdevice_controller` | 18 / 18 |  | `net-private-8` |
| `0x010126c8` | `FUN_010126c8` | `softdevice_controller` | 32 / 32 |  | `net-private-4` |
| `0x01012714` | `FUN_01012714` | `softdevice_controller` | 24 / 24 |  | `net-private-4` |
| `0x010129b8` | `FUN_010129b8` | `softdevice_controller` | 48 / 48 |  | `net-private-4` |
| `0x01012ad4` | `FUN_01012ad4` | `softdevice_controller` | 78 / 78 |  | `net-private-3` |
| `0x01013da8` | `FUN_01013da8` | `softdevice_controller` | 238 / 238 |  | `net-private-5` |
| `0x01014b18` | `sdc_conn_event_process` | `softdevice_controller` | None / 4488 |  | `net-private-1` |
| `0x01016170` | `FUN_01016170` | `softdevice_controller` | 28 / 28 |  | `net-private-3` |
| `0x0101618c` | `sdc_conn_recovery_state_restore` | `softdevice_controller` | 88 / 88 |  | `net-private-4` |
| `0x01018df8` | `FUN_01018df8` | `softdevice_controller` | None / 50 |  | `net-private-7` |
| `0x010199f4` | `FUN_010199f4` | `softdevice_controller` | 170 / 170 |  | `net-private-4` |
| `0x01019eb4` | `FUN_01019eb4` | `softdevice_controller` | 68 / 68 |  | `net-private-5` |
| `0x01019ef8` | `FUN_01019ef8` | `softdevice_controller` | 58 / 58 |  | `net-private-5` |
| `0x0101d890` | `FUN_0101d890` | `softdevice_controller` | None / 82 |  | `net-private-3` |
| `0x0101dda8` | `schedule_node_tail_get` | `softdevice_controller` | 20 / 20 |  | `net-private-6` |
| `0x0101ded0` | `FUN_0101ded0` | `softdevice_controller` | 176 / 176 |  | `net-private-6` |
| `0x0101df84` | `controller_entry_links_release` | `softdevice_controller` | 242 / 242 |  | `net-private-4` |
| `0x0101e090` | `FUN_0101e090` | `softdevice_controller` | 20 / 20 |  | `net-private-5` |
| `0x0101e1e4` | `controller_timing_defaults_apply` | `softdevice_controller` | 144 / 144 |  | `net-private-8` |
| `0x0101e2fc` | `FUN_0101e2fc` | `softdevice_controller` | 156 / 156 |  | `net-private-6` |
| `0x0101f624` | `FUN_0101f624` | `softdevice_controller` | 40 / 40 |  | `net-private-3` |
| `0x010207cc` | `FUN_010207cc` | `softdevice_controller` | 72 / 72 |  | `net-private-6` |
| `0x01020820` | `FUN_01020820` | `softdevice_controller` | 60 / 60 |  | `net-private-4` |
| `0x01021634` | `controller_radio_time_mode2_to_mode2` | `softdevice_controller` | 28 / 28 |  | `net-private-7` |
| `0x01021940` | `FUN_01021940` | `mpsl` | 48 / 48 |  | `net-private-6` |
| `0x01021ac0` | `FUN_01021ac0` | `mpsl` | 20 / 20 |  | `net-private-4` |
| `0x01022a30` | `FUN_01022a30` | `mpsl` | 28 / 28 | `0x010256dc` | `net-private-2` |
| `0x01022a50` | `FUN_01022a50` | `mpsl` | 48 / 48 |  | `net-private-5` |
| `0x01022e34` | `FUN_01022e34` | `mpsl` | 80 / 80 |  | `net-private-8` |
| `0x01022ea8` | `FUN_01022ea8` | `mpsl` | 18 / 18 | `0x01024440`, `0x010245d8` | `net-private-2` |
| `0x01022f0c` | `FUN_01022f0c` | `mpsl` | 44 / 44 | `0x0102445c` | `net-private-2` |
| `0x010231c8` | `sdc_conn_window_admit` | `mpsl` | 1474 / 1474 | `0x01024440`, `0x010256dc`, `0x0102583c` | `net-private-2` |
| `0x01023ac4` | `FUN_01023ac4` | `mpsl` | 18 / 18 |  | `net-private-3` |
| `0x01023d38` | `FUN_01023d38` | `mpsl` | 172 / 172 | `0x0102445c`, `0x010256dc` | `net-private-2` |
| `0x01023e88` | `FUN_01023e88` | `mpsl` | 28 / 28 | `0x010256dc` | `net-private-2` |
| `0x01024440` | `FUN_01024440` | `mpsl` | 28 / 28 |  | `net-private-2` |
| `0x0102445c` | `FUN_0102445c` | `mpsl` | 112 / 112 |  | `net-private-2` |
| `0x010245d8` | `FUN_010245d8` | `mpsl` | 48 / 48 |  | `net-private-2` |
| `0x01024c6c` | `FUN_01024c6c` | `mpsl` | 408 / 408 | `0x010256dc` | `net-private-2` |
| `0x0102524c` | `FUN_0102524c` | `mpsl` | 222 / 222 | `0x010256dc` | `net-private-2` |
| `0x010256dc` | `FUN_010256dc` | `mpsl` | 84 / 84 |  | `net-private-2` |
| `0x010257e4` | `FUN_010257e4` | `mpsl` | 52 / 52 | `0x010256dc` | `net-private-2` |
| `0x0102583c` | `controller_deferred_event_raise` | `mpsl` | 52 / 52 | `0x010256dc` | `net-private-2` |
| `0x0102590c` | `FUN_0102590c` | `mpsl` | 138 / 138 |  | `net-private-5` |
| `0x01025998` | `FUN_01025998` | `mpsl` | 236 / 236 |  | `net-private-6` |
| `0x01025a84` | `FUN_01025a84` | `mpsl` | 214 / 214 |  | `net-private-3` |
| `0x01025c44` | `FUN_01025c44` | `mpsl` | 84 / 84 | `0x010256dc` | `net-private-2` |
| `0x01025c9c` | `FUN_01025c9c` | `mpsl` | 40 / 40 | `0x010256dc` | `net-private-2` |
| `0x01025cc8` | `FUN_01025cc8` | `mpsl` | 36 / 36 |  | `net-private-3` |
| `0x01025cf0` | `controller_transition_pending_check` | `mpsl` | 24 / 24 |  | `net-private-3` |
| `0x01025d0c` | `FUN_01025d0c` | `mpsl` | 24 / 24 |  | `net-private-7` |
| `0x0102665c` | `FUN_0102665c` | `softdevice_controller` | None / 32 |  | `net-private-8` |
| `0x0102693a` | `FUN_0102693a` | `softdevice_controller` | 148 / 148 | `0x01025a84`, `0x01026a7e` | `net-private-3` |
| `0x010269ce` | `FUN_010269ce` | `softdevice_controller` | 176 / 176 |  | `net-private-5` |
| `0x01026a7e` | `FUN_01026a7e` | `softdevice_controller` | 78 / 78 |  | `net-private-3` |
| `0x01026acc` | `FUN_01026acc` | `softdevice_controller` | 140 / 140 |  | `net-private-3` |
| `0x01026b58` | `FUN_01026b58` | `softdevice_controller` | 166 / 166 |  | `net-private-4` |
| `0x01026bfe` | `FUN_01026bfe` | `softdevice_controller` | 150 / 150 |  | `net-private-7` |
| `0x01026d16` | `FUN_01026d16` | `softdevice_controller` | 40 / 40 |  | `net-private-6` |
| `0x01026dae` | `FUN_01026dae` | `softdevice_controller` | 154 / 154 |  | `net-private-5` |
| `0x01027044` | `FUN_01027044` | `softdevice_controller` | 90 / 90 |  | `net-private-8` |
| `0x010270e8` | `FUN_010270e8` | `softdevice_controller` | 98 / 98 |  | `net-private-7` |
| `0x01027302` | `FUN_01027302` | `softdevice_controller` | 196 / 196 |  | `net-private-8` |
| `0x010273c6` | `FUN_010273c6` | `softdevice_controller` | 50 / 50 |  | `net-private-3` |
| `0x01027846` | `FUN_01027846` | `softdevice_controller` | 78 / 78 |  | `net-private-4` |
| `0x01027a4a` | `FUN_01027a4a` | `softdevice_controller` | 74 / 74 |  | `net-private-7` |
| `0x01027a94` | `FUN_01027a94` | `softdevice_controller` | 62 / 62 |  | `net-private-7` |
| `0x01027ed4` | `FUN_01027ed4` | `softdevice_controller` | 30 / 30 |  | `net-private-5` |
| `0x01027ef2` | `FUN_01027ef2` | `softdevice_controller` | 30 / 30 |  | `net-private-4` |
| `0x010280be` | `FUN_010280be` | `softdevice_controller` | 26 / 26 |  | `net-private-6` |
| `0x010280d8` | `FUN_010280d8` | `softdevice_controller` | 26 / 26 |  | `net-private-5` |
| `0x01028256` | `FUN_01028256` | `softdevice_controller` | 64 / 64 |  | `net-private-3` |
| `0x010282fc` | `controller_default_bounds_build` | `softdevice_controller` | 126 / 126 |  | `net-private-6` |
| `0x0102894a` | `FUN_0102894a` | `softdevice_controller` | 60 / 60 |  | `net-private-6` |
| `0x010292ec` | `FUN_010292ec` | `softdevice_controller` | None / 46 |  | `net-private-8` |
| `0x0102941c` | `FUN_0102941c` | `softdevice_controller` | 32 / 32 |  | `net-private-6` |
| `0x0102961a` | `FUN_0102961a` | `softdevice_controller` | 18 / 18 |  | `net-private-7` |
| `0x0102971e` | `FUN_0102971e` | `softdevice_controller` | 26 / 26 |  | `net-private-7` |
| `0x010297b4` | `FUN_010297b4` | `softdevice_controller` | 206 / 206 | `0x0102971e` | `net-private-7` |
| `0x01029882` | `FUN_01029882` | `softdevice_controller` | 38 / 38 |  | `net-private-7` |
| `0x010298a8` | `FUN_010298a8` | `softdevice_controller` | 18 / 18 |  | `net-private-6` |
| `0x01029b38` | `FUN_01029b38` | `softdevice_controller` | 22 / 22 |  | `net-private-8` |
| `0x0102a1e0` | `FUN_0102a1e0` | `softdevice_controller` | None / 2 |  | `net-private-8` |
| `0x0102a1ea` | `sdc_byte_lock_try_acquire` | `mpsl` | 30 / 30 |  | `net-private-8` |
| `0x0102a208` | `sdc_byte_lock_release` | `mpsl` | 18 / 18 |  | `net-private-5` |
