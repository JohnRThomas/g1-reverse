# CPUAPP retain-all undefined-function residue

This is a report-only classification of the real post-pin link log; it does not
change function semantics or authorize automatic source removal.

## Summary

| Category | Unique symbols | Next action |
|---|---:|---|
| `interior_or_tail_alias` | 69 | materialize a safe veneer/alias after overlap review |
| `sdk_or_config_symbol` | 131 | enable/pin the owning NCS unit or reconcile static linkage |

Total: **200** unique symbols. True missing reconstructed entries: **0**.

## Action queues

### `interior_or_tail_alias` (69)

`FUN_000179f8`, `FUN_00024e60`, `FUN_00026100`, `FUN_00033554`, `FUN_00033730`, `FUN_0003603c`, `FUN_00036b3c`, `FUN_0003f410`, `FUN_0003fecc`, `FUN_0004372c`, `FUN_0004b3c8`, `FUN_0004c254`, `FUN_0004d44c`, `FUN_0004d468`, `FUN_0004d8b8`, `FUN_0004de68`, `FUN_0004e3e8`, `FUN_0004e474`, `FUN_0004e8c0`, `FUN_0004f500`, `FUN_000534a8`, `FUN_0005463e`, `FUN_00054688`, `FUN_00054ea8`, `FUN_00055aac`, `FUN_000564cc`, `FUN_000573c8`, `FUN_00058568`, `FUN_0005a954`, `FUN_0005ad38`, `FUN_0005c310`, `FUN_0005c76c`, `FUN_0005c9a4`, `FUN_0005ce6c`, `FUN_0006446c`, `FUN_0006447c`, `FUN_00065000`, `FUN_000680f8`, `FUN_00068298`, `FUN_00071560`, `FUN_000715b8`, `FUN_00071b2c`, `FUN_00074184`, `FUN_000748b8`, `FUN_00075864`, `FUN_000758cc`, `FUN_00075e14`, `FUN_00076bc0`, `FUN_00077b24`, `FUN_00077b38`, `FUN_00077c4c`, `FUN_0007e12a`, `FUN_0007ef56`, `FUN_0008131c`, `FUN_00083a2c`, `FUN_00084e44`, `FUN_00084f06`, `FUN_00085c86`, `FUN_00085ef0`, `FUN_00086228`, `FUN_00086360`, `FUN_0008664c`, `ext5c6c8`, `ext77c8c`, `k_sem_take`, `tail_54d88`, `tail_61200`, `tail_77d30`, `thunk_FUN_0007f7d2`

### `sdk_or_config_symbol` (131)

`DEBUG_PRINT`, `FUN_0004d2d0`, `FUN_00055534`, `FUN_00057038`, `FUN_00066e70`, `FUN_0007df24`, `FUN_0007e022`, `FUN_0007e18e`, `FUN_0007e390`, `FUN_0007e3ce`, `FUN_00081050`, `FUN_00081e2a`, `FUN_00082030`, `FUN_000820ae`, `FUN_00082f3a`, `FUN_0008323a`, `FUN_00086596`, `FUN_00086778`, `FUN_000867da`, `__nrfy_internal_spim_events_process`, `__nrfy_internal_twim_events_process`, `adc_nfc_init`, `adc_nfc_run`, `adv_is_directed`, `atomic_and`, `atomic_and_0`, `atomic_and_1`, `atomic_and_2`, `atomic_and_3`, `atomic_and_4`, `atomic_clear_bit`, `atomic_clear_bit_0`, `atomic_clear_bit_1`, `atomic_get_3`, `atomic_get_3_0`, `atomic_inc`, `atomic_or`, `atomic_or_0`, `atomic_set`, `atomic_set_bit`, `atomic_test_and_clear_bit`, `atomic_test_and_set_bit`, `atomic_test_and_set_bit_0`, `atomic_test_bit`, `att_op_get_type`, `bt_addr_le_eq`, `bt_addr_le_eq_0`, `bt_gatt_foreach_attr`, `bt_gatt_foreach_attr_0`, `bt_hci_evt_get_flags`, `bt_start`, `cancel_sync_locked`, `chunk_field`, `chunk_set`, `chunk_size`, `compare_set`, `flash_settings_read`, `flash_settings_write_and_verify`, `free_chunk`, `gatt_discover_next`, `gatt_req_send`, `gatt_write_ccc`, `get_adv_channel_map`, `get_display_atomic_state`, `get_pin_idx`, `is_regular_addr_valid`, `is_tx_ready`, `k_msleep_ticks32768_a`, `k_timer_start`, `k_uptime_get_0`, `k_uptime_get_1`, `k_uptime_get_10`, `k_uptime_get_2`, `k_uptime_get_3`, `k_uptime_get_32`, `k_uptime_get_4`, `k_uptime_get_5`, `k_uptime_get_6`, `k_uptime_get_8`, `k_uptime_get_9`, `log_message`, `mem_to_chunkid`, `net_buf_frags_len`, `net_buf_frags_len_0`, `next_timeout`, `notify_one`, `nrf_cc3xx_platform_abort`, `nrf_gpio_cfg_sense_set`, `nrf_qspi_cinstrdata_get`, `nrf_qspi_cinstrdata_set`, `nrf_qspi_pins_set`, `nvmc_readonly_mode_set`, `nvmc_word_write`, `pin_in_use_by_te`, `pin_is_output`, `pin_te_get`, `print_formatted`, `process_queue`, `qspi_activate`, `qspi_deactivate`, `qspi_get_zephyr_ret_code`, `qspi_nor_write_protection_set`, `qspi_rdsr`, `qspi_ready_wait`, `qspi_workaround_apply`, `region_init`, `remove_timeout`, `set_chunk_used`, `shm_size`, `smp_create_pdu`, `spim_abort`, `spim_pin_uninit`, `split_chunks`, `strtoll_internal`, `sys_put_le64`, `sys_slist_find_and_remove`, `sys_slist_find_and_remove_0`, `sys_slist_find_and_remove_2`, `sys_slist_get`, `twim_configure`, `tx_notify`, `uarte_nrfx_configure`, `unpair`, `unready_thread`, `unschedule_locked`, `update_sec_level`, `validate_args`, `ver_str`, `xfer_completeness_check`, `z_fdtable_call_ioctl`, `z_log_dropped_read_and_clear_0`

