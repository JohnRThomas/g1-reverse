# CPUAPP SDK/config residue ownership

Report-only resolution of the 173 SDK/config rows from the retain-all link.
A local (`t`) symbol is evidence for its translation unit, not a public
link target; these rows explicitly require whole-source-unit ownership.

## Summary

| Action | Symbols |
|---|---:|
| `adopt_complete_source_unit` | 91 |
| `enable_or_adopt_public_owner` | 19 |
| `identity_collision_review` | 2 |
| `link_compiler_runtime_public_symbol` | 8 |
| `manual_owner_review` | 1 |
| `reclassify_application_owner` | 7 |
| `reconcile_inline_at_callsite` | 46 |

Public safe candidates: **27**. Source-unit/inline cases: **137**.

## Public link/adoption candidates (27)

These have public archive exports. Exact signature hits can be adopted
directly; approximate hits retain an explicit ABI-check gate.

`FUN_0000de58`, `FUN_0000ec34`, `FUN_0004cc50`, `FUN_000638dc`, `FUN_00070f1c`, `FUN_0007e212`, `FUN_0007f570`, `FUN_0007f6b6`, `FUN_00080ed8`, `FUN_000813e8`, `FUN_000817ea`, `FUN_000823fa`, `FUN_00082e24`, `FUN_00082ec8`, `FUN_00083370`, `FUN_00083634`, `FUN_0008557c`, `FUN_00085900`, `FUN_00085bf6`, `FUN_0008673e`, `FUN_00086be4`, `FUN_00086c44`, `FUN_00086fbe`, `FUN_00086ffe`, `FUN_00087036`, `FUN_000870be`, `k_timer_start`

## Deliberate exclusions

Application-owner classifier false positives (7): `adc_nfc_init`, `adc_nfc_run`, `bt_start`, `flash_settings_read`, `flash_settings_write_and_verify`, `get_display_atomic_state`, `log_message`.

`nrf_cc3xx_platform_abort` at `0x00050af8` is not satisfied by
the same-named local CC312 archive function already adopted at
`0x00079590`; it remains an identity-collision review item.

## Per-symbol action

| Symbol | Owner | Kind | Source/archive | Action |
|---|---|---|---|---|
| `DEBUG_PRINT` | `DEBUG_PRINT` | `unresolved` | `unresolved` | `manual_owner_review` |
| `FUN_0000de58` | `__fixdfsi` | `archive_public` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/lib/gcc/arm-zephyr-eabi/12.2.0/thumb/v8-m.main+fp/hard/libgcc.a` | `link_compiler_runtime_public_symbol` |
| `FUN_0000ec34` | `__fixdfdi` | `archive_public` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/lib/gcc/arm-zephyr-eabi/12.2.0/thumb/v8-m.main+fp/hard/libgcc.a` | `link_compiler_runtime_public_symbol` |
| `FUN_0004c4e4` | `nvs_recover_last_ate` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `FUN_0004cc50` | `ipc_service_send` | `archive_public` | `zephyr/subsys/ipc/ipc_service/ipc_service.c` | `enable_or_adopt_public_owner` |
| `FUN_0004d2d0` | `activate_foreach_backend` | `archive_local` | `zephyr/subsys/logging/log_core.c` | `adopt_complete_source_unit` |
| `FUN_00055534` | `hci_set_ad` | `archive_local` | `zephyr/subsys/bluetooth/host/adv.c` | `adopt_complete_source_unit` |
| `FUN_00057038` | `send_conn_le_param_update` | `archive_local` | `zephyr/subsys/bluetooth/host/conn.c` | `adopt_complete_source_unit` |
| `FUN_000638dc` | `sys_clock_set_timeout` | `archive_public` | `zephyr/drivers/timer/nrf_rtc_timer.c` | `enable_or_adopt_public_owner` |
| `FUN_00066e70` | `pin_init` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c` | `adopt_complete_source_unit` |
| `FUN_00070f1c` | `rpmsg_send_offchannel_raw` | `archive_public` | `modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg.c` | `enable_or_adopt_public_owner` |
| `FUN_0007c18e` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `FUN_0007df24` | `alloc_chunk` | `archive_local` | `zephyr/lib/os/heap.c` | `adopt_complete_source_unit` |
| `FUN_0007e022` | `free_list_add` | `archive_local` | `zephyr/lib/os/heap.c` | `adopt_complete_source_unit` |
| `FUN_0007e18e` | `process_recheck` | `archive_local` | `zephyr/lib/os/onoff.c` | `adopt_complete_source_unit` |
| `FUN_0007e212` | `onoff_manager_init` | `archive_public` | `zephyr/lib/os/onoff.c` | `enable_or_adopt_public_owner` |
| `FUN_0007e390` | `add_skip_item` | `archive_local` | `zephyr/lib/os/mpsc_pbuf.c` | `adopt_complete_source_unit` |
| `FUN_0007e3ce` | `drop_item_locked` | `archive_local` | `zephyr/lib/os/mpsc_pbuf.c` | `adopt_complete_source_unit` |
| `FUN_0007e53e` | `nvs_flash_rd` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `FUN_0007e574` | `nvs_flash_block_cmp` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `FUN_0007e5da` | `nvs_flash_cmp_const` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `FUN_0007e624` | `nvs_flash_erase_sector` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `FUN_0007e672` | `nvs_ate_valid` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `FUN_0007e6e2` | `nvs_prev_ate` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `FUN_0007e776` | `nvs_flash_al_wrt` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `FUN_0007e7ea` | `nvs_flash_ate_wrt` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `FUN_0007e83a` | `nvs_gc` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `FUN_0007f570` | `bt_gatt_dm_desc_by_uuid` | `archive_public` | `nrf/subsys/bluetooth/gatt_dm.c` | `enable_or_adopt_public_owner` |
| `FUN_0007f6b6` | `bt_ancs_request_attrs` | `archive_public` | `nrf/subsys/bluetooth/services/ancs_client.c` | `enable_or_adopt_public_owner` |
| `FUN_00080ed8` | `bt_hci_disconnect` | `archive_public` | `zephyr/subsys/bluetooth/host/hci_core.c` | `enable_or_adopt_public_owner` |
| `FUN_00081050` | `addr_res_enable` | `archive_local` | `zephyr/subsys/bluetooth/host/id.c` | `adopt_complete_source_unit` |
| `FUN_000813e8` | `conn_lookup_handle` | `archive_public` | `zephyr/subsys/bluetooth/host/conn.c` | `enable_or_adopt_public_owner` |
| `FUN_000817ea` | `bt_l2cap_disconnected` | `archive_public` | `zephyr/subsys/bluetooth/host/l2cap.c` | `enable_or_adopt_public_owner` |
| `FUN_00081e2a` | `att_chan_read` | `archive_local` | `zephyr/subsys/bluetooth/host/att.c` | `adopt_complete_source_unit` |
| `FUN_00082030` | `chan_req_send` | `archive_local` | `zephyr/subsys/bluetooth/host/att.c` | `adopt_complete_source_unit` |
| `FUN_000820ae` | `att_req_send_process` | `archive_local` | `zephyr/subsys/bluetooth/host/att.c` | `adopt_complete_source_unit` |
| `FUN_000823fa` | `bt_att_get_mtu` | `archive_public` | `zephyr/subsys/bluetooth/host/att.c` | `enable_or_adopt_public_owner` |
| `FUN_00082e24` | `bt_gatt_cancel` | `archive_public` | `zephyr/subsys/bluetooth/host/gatt.c` | `enable_or_adopt_public_owner` |
| `FUN_00082ec8` | `bt_gatt_change_aware` | `archive_public` | `zephyr/subsys/bluetooth/host/gatt.c` | `enable_or_adopt_public_owner` |
| `FUN_00082f3a` | `gatt_store_ccc_cf` | `archive_local` | `zephyr/subsys/bluetooth/host/gatt.c` | `adopt_complete_source_unit` |
| `FUN_0008323a` | `smp_c1` | `archive_local` | `zephyr/subsys/bluetooth/host/smp.c` | `adopt_complete_source_unit` |
| `FUN_00083370` | `bt_smp_request_ltk` | `archive_public` | `zephyr/subsys/bluetooth/host/smp.c` | `enable_or_adopt_public_owner` |
| `FUN_00083634` | `bt_crypto_f6` | `archive_public` | `zephyr/subsys/bluetooth/crypto/bt_crypto.c` | `enable_or_adopt_public_owner` |
| `FUN_0008557c` | `metal_io_block_set` | `archive_public` | `modules/hal/libmetal/libmetal/lib/io.c` | `enable_or_adopt_public_owner` |
| `FUN_00085900` | `rpmsg_get_endpoint` | `archive_public` | `modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg.c` | `enable_or_adopt_public_owner` |
| `FUN_00085bf6` | `rpmsg_deinit_vdev` | `archive_public` | `modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg_virtio.c` | `enable_or_adopt_public_owner` |
| `FUN_00086596` | `cancel_async_locked` | `archive_local` | `zephyr/kernel/work.c` | `adopt_complete_source_unit` |
| `FUN_0008673e` | `z_impl_k_timer_stop` | `archive_public` | `zephyr/kernel/timer.c` | `enable_or_adopt_public_owner` |
| `FUN_00086778` | `add_event` | `archive_local` | `zephyr/kernel/poll.c` | `adopt_complete_source_unit` |
| `FUN_000867da` | `signal_poll_event` | `archive_local` | `zephyr/kernel/poll.c` | `adopt_complete_source_unit` |
| `FUN_00086be4` | `memcmp` | `archive_public` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a` | `link_compiler_runtime_public_symbol` |
| `FUN_00086c44` | `memmove` | `archive_public` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a` | `link_compiler_runtime_public_symbol` |
| `FUN_00086fbe` | `__strcat_chk` | `archive_public` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a` | `link_compiler_runtime_public_symbol` |
| `FUN_00086ffe` | `__strcpy_chk` | `archive_public` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a` | `link_compiler_runtime_public_symbol` |
| `FUN_00087036` | `strncmp` | `archive_public` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a` | `link_compiler_runtime_public_symbol` |
| `FUN_000870be` | `strstr` | `archive_public` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a` | `link_compiler_runtime_public_symbol` |
| `__nrfy_internal_spim_events_process` | `__nrfy_internal_spim_events_process` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c` | `adopt_complete_source_unit` |
| `__nrfy_internal_twim_events_process` | `__nrfy_internal_twim_events_process` | `source_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_twim.c` | `adopt_complete_source_unit` |
| `adc_nfc_init` | `adc_nfc_init` | `application_misclassified` | `firmware application identity 0x00024b98 (not an SDK source)` | `reclassify_application_owner` |
| `adc_nfc_run` | `adc_nfc_run` | `application_misclassified` | `firmware application identity 0x00024c14 (not an SDK source)` | `reclassify_application_owner` |
| `adv_is_directed` | `adv_is_directed` | `archive_local` | `zephyr/subsys/bluetooth/host/adv.c` | `adopt_complete_source_unit` |
| `atomic_and` | `atomic_and` | `header_inline` | `zephyr/include/zephyr/sys/atomic_builtin.h` | `reconcile_inline_at_callsite` |
| `atomic_and_0` | `atomic_and` | `header_inline` | `zephyr/include/zephyr/sys/atomic_builtin.h` | `reconcile_inline_at_callsite` |
| `atomic_and_1` | `atomic_and` | `header_inline` | `zephyr/include/zephyr/sys/atomic_builtin.h` | `reconcile_inline_at_callsite` |
| `atomic_and_2` | `atomic_and` | `header_inline` | `zephyr/include/zephyr/sys/atomic_builtin.h` | `reconcile_inline_at_callsite` |
| `atomic_and_3` | `atomic_and` | `header_inline` | `zephyr/include/zephyr/sys/atomic_builtin.h` | `reconcile_inline_at_callsite` |
| `atomic_and_4` | `atomic_and` | `header_inline` | `zephyr/include/zephyr/sys/atomic_builtin.h` | `reconcile_inline_at_callsite` |
| `atomic_clear_bit` | `atomic_clear_bit` | `header_inline` | `zephyr/include/zephyr/sys/atomic.h` | `reconcile_inline_at_callsite` |
| `atomic_clear_bit_0` | `atomic_clear_bit` | `header_inline` | `zephyr/include/zephyr/sys/atomic.h` | `reconcile_inline_at_callsite` |
| `atomic_clear_bit_1` | `atomic_clear_bit` | `header_inline` | `zephyr/include/zephyr/sys/atomic.h` | `reconcile_inline_at_callsite` |
| `atomic_get_3` | `atomic_get` | `header_inline` | `zephyr/include/zephyr/sys/atomic_builtin.h` | `reconcile_inline_at_callsite` |
| `atomic_get_3_0` | `atomic_get_3` | `header_inline` | `zephyr/include/zephyr/sys/atomic.h` | `reconcile_inline_at_callsite` |
| `atomic_inc` | `atomic_inc` | `header_inline` | `zephyr/include/zephyr/sys/atomic.h` | `reconcile_inline_at_callsite` |
| `atomic_or` | `atomic_or` | `header_inline` | `zephyr/include/zephyr/sys/atomic_builtin.h` | `reconcile_inline_at_callsite` |
| `atomic_or_0` | `atomic_or` | `header_inline` | `zephyr/include/zephyr/sys/atomic_builtin.h` | `reconcile_inline_at_callsite` |
| `atomic_set` | `atomic_set` | `header_inline` | `zephyr/include/zephyr/sys/atomic_builtin.h` | `reconcile_inline_at_callsite` |
| `atomic_set_bit` | `atomic_set_bit` | `header_inline` | `zephyr/include/zephyr/sys/atomic.h` | `reconcile_inline_at_callsite` |
| `atomic_test_and_clear_bit` | `atomic_test_and_clear_bit` | `header_inline` | `zephyr/include/zephyr/sys/atomic.h` | `reconcile_inline_at_callsite` |
| `atomic_test_and_set_bit` | `atomic_test_and_set_bit` | `header_inline` | `zephyr/include/zephyr/sys/atomic.h` | `reconcile_inline_at_callsite` |
| `atomic_test_and_set_bit_0` | `atomic_test_and_set_bit` | `header_inline` | `zephyr/include/zephyr/sys/atomic.h` | `reconcile_inline_at_callsite` |
| `atomic_test_bit` | `atomic_test_bit` | `header_inline` | `zephyr/include/zephyr/sys/atomic.h` | `reconcile_inline_at_callsite` |
| `att_op_get_type` | `att_op_get_type` | `archive_local` | `zephyr/subsys/bluetooth/host/att.c` | `adopt_complete_source_unit` |
| `bt_addr_le_eq` | `bt_addr_le_eq` | `header_inline` | `zephyr/include/zephyr/bluetooth/addr.h` | `reconcile_inline_at_callsite` |
| `bt_addr_le_eq_0` | `bt_addr_le_eq` | `header_inline` | `zephyr/include/zephyr/bluetooth/addr.h` | `reconcile_inline_at_callsite` |
| `bt_gatt_foreach_attr` | `bt_gatt_foreach_attr` | `header_inline` | `zephyr/include/zephyr/bluetooth/gatt.h` | `reconcile_inline_at_callsite` |
| `bt_gatt_foreach_attr_0` | `bt_gatt_foreach_attr` | `header_inline` | `zephyr/include/zephyr/bluetooth/gatt.h` | `reconcile_inline_at_callsite` |
| `bt_hci_evt_get_flags` | `bt_hci_evt_get_flags` | `archive_local` | `zephyr/subsys/bluetooth/host/hci_core.c` | `adopt_complete_source_unit` |
| `bt_start` | `bt_start` | `application_misclassified` | `firmware application identity 0x00019308 (not an SDK source)` | `reclassify_application_owner` |
| `cancel_sync_locked` | `cancel_sync_locked` | `archive_local` | `zephyr/kernel/work.c` | `adopt_complete_source_unit` |
| `chunk_field` | `chunk_field` | `archive_local` | `zephyr/lib/os/heap-validate.c` | `adopt_complete_source_unit` |
| `chunk_set` | `chunk_set` | `archive_local` | `zephyr/lib/os/heap.c` | `adopt_complete_source_unit` |
| `chunk_size` | `chunk_size` | `archive_local` | `zephyr/lib/os/heap-validate.c` | `adopt_complete_source_unit` |
| `compare_set` | `compare_set` | `archive_local` | `zephyr/drivers/timer/nrf_rtc_timer.c` | `adopt_complete_source_unit` |
| `encode_uint` | `encode_uint` | `archive_local` | `zephyr/lib/os/cbprintf_complete.c` | `adopt_complete_source_unit` |
| `flash_settings_read` | `flash_settings_read` | `application_misclassified` | `firmware application identity 0x000225b4 (not an SDK source)` | `reclassify_application_owner` |
| `flash_settings_write_and_verify` | `flash_settings_write_and_verify` | `application_misclassified` | `firmware application identity 0x00022658 (not an SDK source)` | `reclassify_application_owner` |
| `free_chunk` | `free_chunk` | `archive_local` | `zephyr/lib/os/heap.c` | `adopt_complete_source_unit` |
| `gatt_discover_next` | `gatt_discover_next` | `archive_local` | `zephyr/subsys/bluetooth/host/gatt.c` | `adopt_complete_source_unit` |
| `gatt_req_send` | `gatt_req_send` | `source_local` | `zephyr/subsys/bluetooth/host/gatt.c` | `adopt_complete_source_unit` |
| `gatt_write_ccc` | `gatt_write_ccc` | `archive_local` | `zephyr/subsys/bluetooth/host/gatt.c` | `adopt_complete_source_unit` |
| `get_adv_channel_map` | `get_adv_channel_map` | `archive_local` | `zephyr/subsys/bluetooth/host/adv.c` | `adopt_complete_source_unit` |
| `get_display_atomic_state` | `get_display_atomic_state` | `application_misclassified` | `firmware application identity 0x000431a8 (not an SDK source)` | `reclassify_application_owner` |
| `get_pin_idx` | `get_pin_idx` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c` | `adopt_complete_source_unit` |
| `is_regular_addr_valid` | `is_regular_addr_valid` | `archive_local` | `zephyr/drivers/flash/soc_flash_nrf.c` | `adopt_complete_source_unit` |
| `is_tx_ready` | `is_tx_ready` | `source_local` | `zephyr/drivers/serial/uart_nrfx_uarte.c` | `adopt_complete_source_unit` |
| `k_msleep_ticks32768_a` | `k_msleep` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_timer_start` | `z_impl_k_timer_start` | `archive_public` | `zephyr/kernel/timer.c` | `enable_or_adopt_public_owner` |
| `k_uptime_get_0` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_1` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_10` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_2` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_3` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_32` | `k_uptime_get_32` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_4` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_5` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_6` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_8` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `k_uptime_get_9` | `k_uptime_get` | `header_inline` | `zephyr/include/zephyr/kernel.h` | `reconcile_inline_at_callsite` |
| `log_message` | `log_message` | `application_misclassified` | `firmware application identity 0x0007dda4 (not an SDK source)` | `reclassify_application_owner` |
| `mem_to_chunkid` | `mem_to_chunkid` | `archive_local` | `zephyr/lib/os/heap.c` | `adopt_complete_source_unit` |
| `net_buf_frags_len` | `net_buf_frags_len` | `header_inline` | `zephyr/include/zephyr/net/buf.h` | `reconcile_inline_at_callsite` |
| `net_buf_frags_len_0` | `net_buf_frags_len` | `header_inline` | `zephyr/include/zephyr/net/buf.h` | `reconcile_inline_at_callsite` |
| `next_timeout` | `next_timeout` | `archive_local` | `zephyr/kernel/timeout.c` | `adopt_complete_source_unit` |
| `notify_one` | `notify_one` | `archive_local` | `zephyr/lib/os/onoff.c` | `adopt_complete_source_unit` |
| `nrf_cc3xx_platform_abort` | `nrf_cc3xx_platform_abort` | `archive_local` | `nrfxlib/crypto/nrf_cc312_platform/lib/cortex-m33/hard-float/libnrf_cc312_platform_0.9.18.a` | `identity_collision_review` |
| `nrf_gpio_cfg_sense_set` | `nrf_gpio_cfg_sense_set` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c` | `adopt_complete_source_unit` |
| `nrf_qspi_cinstrdata_get` | `nrf_qspi_cinstrdata_get` | `header_inline` | `modules/hal/nordic/nrfx/hal/nrf_qspi.h` | `reconcile_inline_at_callsite` |
| `nrf_qspi_cinstrdata_set` | `nrf_qspi_cinstrdata_set` | `header_inline` | `modules/hal/nordic/nrfx/hal/nrf_qspi.h` | `reconcile_inline_at_callsite` |
| `nrf_qspi_pins_set` | `nrf_qspi_pins_set` | `header_inline` | `modules/hal/nordic/nrfx/hal/nrf_qspi.h` | `reconcile_inline_at_callsite` |
| `nvmc_readonly_mode_set` | `nvmc_readonly_mode_set` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_nvmc.c` | `adopt_complete_source_unit` |
| `nvmc_word_write` | `nvmc_word_write` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_nvmc.c` | `adopt_complete_source_unit` |
| `nvs_add_gc_done_ate` | `nvs_add_gc_done_ate` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `nvs_al_size` | `nvs_al_size` | `source_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `nvs_ate_crc8_update` | `nvs_ate_crc8_update` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `nvs_sector_advance` | `nvs_sector_advance` | `archive_local` | `zephyr/subsys/fs/nvs/nvs.c` | `adopt_complete_source_unit` |
| `outs` | `outs` | `archive_local` | `zephyr/lib/os/cbprintf_complete.c` | `adopt_complete_source_unit` |
| `pin_in_use_by_te` | `pin_in_use_by_te` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c` | `adopt_complete_source_unit` |
| `pin_is_output` | `pin_is_output` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c` | `adopt_complete_source_unit` |
| `pin_te_get` | `pin_te_get` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c` | `adopt_complete_source_unit` |
| `print_formatted` | `print_formatted` | `archive_local` | `zephyr/subsys/logging/log_output.c` | `adopt_complete_source_unit` |
| `process_queue` | `process_queue` | `archive_local` | `zephyr/subsys/bluetooth/host/att.c` | `adopt_complete_source_unit` |
| `qspi_activate` | `qspi_activate` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c` | `adopt_complete_source_unit` |
| `qspi_deactivate` | `qspi_deactivate` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c` | `adopt_complete_source_unit` |
| `qspi_get_zephyr_ret_code` | `qspi_get_zephyr_ret_code` | `archive_local` | `zephyr/drivers/flash/nrf_qspi_nor.c` | `adopt_complete_source_unit` |
| `qspi_nor_write_protection_set` | `qspi_nor_write_protection_set` | `archive_local` | `zephyr/drivers/flash/nrf_qspi_nor.c` | `adopt_complete_source_unit` |
| `qspi_rdsr` | `qspi_rdsr` | `source_local` | `zephyr/drivers/flash/nrf_qspi_nor.c` | `adopt_complete_source_unit` |
| `qspi_ready_wait` | `qspi_ready_wait` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c` | `adopt_complete_source_unit` |
| `qspi_workaround_apply` | `qspi_workaround_apply` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c` | `adopt_complete_source_unit` |
| `region_init` | `region_init` | `archive_local` | `zephyr/arch/arm/core/aarch32/mpu/arm_mpu.c` | `adopt_complete_source_unit` |
| `remove_timeout` | `remove_timeout` | `archive_local` | `zephyr/kernel/timeout.c` | `adopt_complete_source_unit` |
| `set_chunk_used` | `set_chunk_used` | `archive_local` | `zephyr/lib/os/heap-validate.c` | `adopt_complete_source_unit` |
| `shm_size` | `shm_size` | `archive_local` | `zephyr/subsys/ipc/ipc_service/backends/ipc_rpmsg_static_vrings.c` | `adopt_complete_source_unit` |
| `smp_create_pdu` | `smp_create_pdu` | `source_local` | `zephyr/subsys/bluetooth/host/smp.c` | `adopt_complete_source_unit` |
| `spim_abort` | `spim_abort` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c` | `adopt_complete_source_unit` |
| `spim_pin_uninit` | `spim_pin_uninit` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c` | `adopt_complete_source_unit` |
| `split_chunks` | `split_chunks` | `archive_local` | `zephyr/lib/os/heap.c` | `adopt_complete_source_unit` |
| `strtoll_internal` | `_strtoll_l.constprop.0` | `archive_local` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a` | `adopt_complete_source_unit` |
| `sys_put_le64` | `sys_put_le64` | `archive_local` | `zephyr/subsys/bluetooth/host/hci_core.c` | `adopt_complete_source_unit` |
| `sys_slist_find_and_remove` | `sys_slist_find_and_remove` | `header_inline` | `zephyr/include/zephyr/sys/slist.h` | `reconcile_inline_at_callsite` |
| `sys_slist_find_and_remove_0` | `sys_slist_find_and_remove` | `header_inline` | `zephyr/include/zephyr/sys/slist.h` | `reconcile_inline_at_callsite` |
| `sys_slist_find_and_remove_2` | `sys_slist_find_and_remove` | `header_inline` | `zephyr/include/zephyr/sys/slist.h` | `reconcile_inline_at_callsite` |
| `sys_slist_get` | `sys_slist_get` | `archive_local` | `zephyr/subsys/bluetooth/host/att.c` | `adopt_complete_source_unit` |
| `twim_configure` | `twim_configure` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_twim.c` | `adopt_complete_source_unit` |
| `tx_notify` | `tx_notify` | `archive_local` | `zephyr/subsys/bluetooth/host/conn.c` | `adopt_complete_source_unit` |
| `uarte_nrfx_configure` | `uarte_nrfx_configure` | `archive_local` | `zephyr/drivers/serial/uart_nrfx_uarte.c` | `adopt_complete_source_unit` |
| `unpair` | `unpair` | `archive_local` | `zephyr/subsys/bluetooth/host/hci_core.c` | `adopt_complete_source_unit` |
| `unready_thread` | `unready_thread` | `archive_local` | `zephyr/kernel/sched.c` | `adopt_complete_source_unit` |
| `unschedule_locked` | `unschedule_locked` | `archive_local` | `zephyr/kernel/work.c` | `adopt_complete_source_unit` |
| `update_sec_level` | `update_sec_level` | `archive_local` | `zephyr/subsys/bluetooth/host/hci_core.c` | `adopt_complete_source_unit` |
| `validate_args` | `validate_args` | `archive_local` | `zephyr/lib/os/onoff.c` | `adopt_complete_source_unit` |
| `ver_str` | `ver_str` | `archive_local` | `zephyr/subsys/bluetooth/host/hci_core.c` | `adopt_complete_source_unit` |
| `xfer_completeness_check` | `xfer_completeness_check` | `archive_local` | `modules/hal/nordic/nrfx/drivers/src/nrfx_twim.c` | `adopt_complete_source_unit` |
| `z_fdtable_call_ioctl` | `z_fdtable_call_ioctl` | `header_inline` | `zephyr/include/zephyr/sys/fdtable.h` | `reconcile_inline_at_callsite` |
| `z_log_dropped_read_and_clear_0` | `z_log_dropped_read_and_clear` | `archive_public` | `zephyr/subsys/logging/log_core.c` | `identity_collision_review` |
