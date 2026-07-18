# CPUAPP address-taken root ledger

The shipped image was scanned at aligned words outside capped true function intervals. Only odd Thumb pointers to exact catalog entries were accepted. Original identities absent from the normal-GC ELF remain explicit; only human-readable symbols with one retained definition are emitted as roots. Ambiguous aliases, raw addresses, and unnamed functions are report-only.

- Address-taken identities: **303**
- Unmaterialized original identities: **198 / 38076 capped bytes**
- Pre-init-only identities: **69**
- Post-init pointer identities: **129**; post-init-or-collision review set: **130**
- Emitted unique named roots: **83**
- Existing reviewed stock aliases: **11**
- Ambiguous aliases rejected: **2**
- Original union call closure: **1608 identities / 228062 capped bytes**

| Original | Current / stock alias | Pointer owner classes | Resolution | Source |
|---|---|---|---|---|
| `0x0000fe88` handle_attitude_trigger | `imu_fusion_thread` | pre_init_gap | emitted_unique_recovered_root | recon/symbolized/app/imu_fusion_thread.c |
| `0x00010fc8` FUN_00010fc8 | `get_lux_info` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/get_lux_info.c |
| `0x00017e3c` FUN_00017e3c | `bt_send_enabled` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/bt_send_enabled.c |
| `0x00017e84` FUN_00017e84 | `notify_config_change_if_connected` | pre_init_gap | emitted_unique_recovered_root | recon/symbolized/app/notify_config_change_if_connected.c |
| `0x00017f70` FUN_00017f70 | `random` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/random.c |
| `0x00018300` FUN_00018300 | `FUN_00018300` | post_init_gap | unresolved_report_only | — |
| `0x000183ac` FUN_000183ac | `bond_deleted_cb` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/bond_deleted_cb.c |
| `0x000183e4` check_bonded_addr | `check_bonded_addr` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/check_bonded_addr.c |
| `0x00018444` pairing_failed | `pairing_failed` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/pairing_failed.c |
| `0x0001849c` auth_cancel | `auth_cancel` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/auth_cancel.c |
| `0x000184f0` FUN_000184f0 | `ancs_security_changed` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/ancs_security_changed.c |
| `0x0001861c` FUN_0001861c | `ancs_connected` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/ancs_connected.c |
| `0x00018730` FUN_00018730 | `pairing_complete` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/pairing_complete.c |
| `0x00018894` FUN_00018894 | `discovery_error_found_cb_gatt` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/discovery_error_found_cb_gatt.c |
| `0x000188b0` FUN_000188b0 | `discovery_error_found_cb_ancs` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/discovery_error_found_cb_ancs.c |
| `0x000188d8` FUN_000188d8 | `discovery_completed_cb_ancs` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/discovery_completed_cb_ancs.c |
| `0x00018978` FUN_00018978 | `discovery_service_not_found_cb_ancs` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/discovery_service_not_found_cb_ancs.c |
| `0x000189a0` FUN_000189a0 | `discovery_completed_cb_gatt` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/discovery_completed_cb_gatt.c |
| `0x00018a1c` FUN_00018a1c | `discovery_service_not_found_cb_gatt` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/discovery_service_not_found_cb_gatt.c |
| `0x00018a38` indicate_sc_cb | `indicate_sc_cb` | pre_init_gap | emitted_unique_recovered_root | recon/symbolized/app/indicate_sc_cb.c |
| `0x00018adc` FUN_00018adc | `ancs_disconnected` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/ancs_disconnected.c |
| `0x00018c48` FUN_00018c48 | `bt_ancs_data_source_handler` | pre_init_gap | emitted_unique_recovered_root | recon/symbolized/app/bt_ancs_data_source_handler.c |
| `0x00021da8` FUN_00021da8 | `FUN_00021da8` | dynamic_thread_reference | unresolved_report_only | — |
| `0x0002201c` FUN_0002201c | `init_ble_work_thread` | pre_init_gap | emitted_unique_recovered_root | recon/symbolized/app/init_ble_work_thread.c |
| `0x00022168` FUN_00022168 | `local_store_write` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/local_store_write.c |
| `0x00022218` FUN_00022218 | `ble_whitelist_app` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/ble_whitelist_app.c |
| `0x00023844` FUN_00023844 | `FUN_00023844` | dynamic_thread_reference | unresolved_report_only | — |
| `0x00025a48` FUN_00025a48 | `ipc0_ept_recv` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/ipc0_ept_recv.c |
| `0x000262ac` spi_master_trans_data_tx_rx | `spi_master_trans_data_tx_rx` | pre_init_gap | emitted_unique_recovered_root | recon/symbolized/app/spi_master_trans_data_tx_rx.c |
| `0x00026338` FUN_00026338 | `FUN_00026338` | pre_init_gap | unresolved_report_only | — |
| `0x00026418` spi_master_init | `spi_master_init` | pre_init_gap | emitted_unique_recovered_root | recon/symbolized/app/spi_master_init.c |
| `0x0002a8d8` FUN_0002a8d8 | `FUN_0002a8d8` | dynamic_thread_reference | unresolved_report_only | — |
| `0x0002e398` FUN_0002e398 | `ext_flash_read` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/ext_flash_read.c |
| `0x0002e440` FUN_0002e440 | `ext_flash_write` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/ext_flash_write.c |
| `0x0002e67c` FUN_0002e67c | `opt3007_chip_init` | pre_init_gap | emitted_unique_recovered_root | recon/symbolized/app/opt3007_chip_init.c |
| `0x00030c24` FUN_00030c24 | `FUN_00030c24` | post_init_gap | unresolved_report_only | — |
| `0x00031b60` FUN_00031b60 | `FUN_00031b60` | verified_pointer_table | unresolved_report_only | — |
| `0x00031bd8` FUN_00031bd8 | `FUN_00031bd8` | post_init_gap | unresolved_report_only | — |
| `0x00031cbc` FUN_00031cbc | `set_brightness_lum_base` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/set_brightness_lum_base.c |
| `0x00031dd8` FUN_00031dd8 | `FUN_00031dd8` | post_init_gap | unresolved_report_only | — |
| `0x00031ee8` set_glasses_sn_info | `set_glasses_sn_info` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/set_glasses_sn_info.c |
| `0x00031fd8` FUN_00031fd8 | `get_assign_channel_info` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/get_assign_channel_info.c |
| `0x00032164` set_device_sn_info | `set_device_sn_info` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/set_device_sn_info.c |
| `0x00032254` FUN_00032254 | `set_display_brightness` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/set_display_brightness.c |
| `0x00032308` FUN_00032308 | `FUN_00032308` | post_init_gap | unresolved_report_only | — |
| `0x00032628` FUN_00032628 | `get_flash_info` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/get_flash_info.c |
| `0x00033384` FUN_00033384 | `uart_callback` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/uart_callback.c |
| `0x00036164` FUN_00036164 | `dump_template_gyro_info` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/dump_template_gyro_info.c |
| `0x000361d8` FUN_000361d8 | `FUN_000361d8` | post_init_gap | unresolved_report_only | — |
| `0x000362e8` FUN_000362e8 | `FUN_000362e8` | post_init_gap | unresolved_report_only | — |
| `0x0003fd44` FUN_0003fd44 | `draw_template_translate_screen` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/draw_template_translate_screen.c |
| `0x00046d2c` FUN_00046d2c | `panel_off` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/panel_off.c |
| `0x00046dd8` FUN_00046dd8 | `panel_on` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/panel_on.c |
| `0x00046fc0` jdb_panel_init | `jdb_panel_init` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/jdb_panel_init.c |
| `0x0004c2d4` FUN_0004c2d4 | `nrf53_sync_rtc_init / sync_rtc_setup` | init_entry | resolved_existing_stock_alias | zephyr/soc/arm/nordic_nrf/nrf53/sync_rtc.c |
| `0x0004c418` FUN_0004c418 | `FUN_0004c418` | verified_pointer_table | unresolved_report_only | — |
| `0x0004cd4c` FUN_0004cd4c | `FUN_0004cd4c` | verified_pointer_table | unresolved_report_only | — |
| `0x0004cf78` FUN_0004cf78 | `FUN_0004cf78` | verified_pointer_table | unresolved_report_only | — |
| `0x0004d6ec` FUN_0004d6ec | `FUN_0004d6ec` | pre_init_gap | unresolved_report_only | — |
| `0x0004df88` FUN_0004df88 | `FUN_0004df88` | verified_pointer_table | unresolved_report_only | — |
| `0x0004ea78` FUN_0004ea78 | `discovery_callback` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/discovery_callback.c |
| `0x0004f5b0` FUN_0004f5b0 | `FUN_0004f5b0` | post_init_gap | unresolved_report_only | — |
| `0x0004f860` FUN_0004f860 | `FUN_0004f860` | post_init_gap | unresolved_report_only | — |
| `0x0004f92c` FUN_0004f92c | `FUN_0004f92c` | post_init_gap | unresolved_report_only | — |
| `0x00052854` FUN_00052854 | `FUN_00052854` | post_init_gap | unresolved_report_only | — |
| `0x00052d58` FUN_00052d58 | `FUN_00052d58` | verified_pointer_table | unresolved_report_only | — |
| `0x00052f68` FUN_00052f68 | `FUN_00052f68` | post_init_gap | unresolved_report_only | — |
| `0x000530c4` FUN_000530c4 | `FUN_000530c4` | verified_pointer_table | unresolved_report_only | — |
| `0x000536b8` FUN_000536b8 | `bt_hci_core_recv_event` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/bt_hci_core_recv_event.c |
| `0x00053bd8` FUN_00053bd8 | `FUN_00053bd8` | post_init_gap | unresolved_report_only | — |
| `0x00054260` FUN_00054260 | `bt_conn_encrypt_change_handle_le` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/bt_conn_encrypt_change_handle_le.c |
| `0x00054308` FUN_00054308 | `bt_conn_encrypt_change_handle_generic` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/bt_conn_encrypt_change_handle_generic.c |
| `0x00054444` FUN_00054444 | `FUN_00054444` | post_init_gap | unresolved_report_only | — |
| `0x00054528` FUN_00054528 | `FUN_00054528` | post_init_gap | unresolved_report_only | — |
| `0x000545f0` FUN_000545f0 | `hci_tx_thread` | dynamic_thread_reference | unresolved_report_only | /private/tmp/g1-bt-custom-notls-main16k-evidence/zephyr/subsys/bluetooth/host/CMakeFiles/subsys__bluetooth__host.dir/hci_core.c.obj |
| `0x00054dd8` FUN_00054dd8 | `FUN_00054dd8` | verified_pointer_table | unresolved_report_only | — |
| `0x000570a0` FUN_000570a0 | `ble_conn_process_complete_or_disconnect` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/ble_conn_process_complete_or_disconnect.c |
| `0x00058808` FUN_00058808 | `FUN_00058808` | pre_init_gap | unresolved_report_only | — |
| `0x00058bfc` FUN_00058bfc | `FUN_00058bfc` | post_init_gap | unresolved_report_only | — |
| `0x00058f80` FUN_00058f80 | `FUN_00058f80` | post_init_gap | unresolved_report_only | — |
| `0x000590bc` FUN_000590bc | `FUN_000590bc` | post_init_gap | unresolved_report_only | — |
| `0x0005929c` FUN_0005929c | `FUN_0005929c` | post_init_gap | unresolved_report_only | — |
| `0x00059344` FUN_00059344 | `FUN_00059344` | post_init_gap | unresolved_report_only | — |
| `0x00059834` FUN_00059834 | `FUN_00059834` | post_init_gap | unresolved_report_only | — |
| `0x00059dec` FUN_00059dec | `FUN_00059dec` | verified_pointer_table | unresolved_report_only | — |
| `0x0005a28c` FUN_0005a28c | `gatt_hash_settings_set` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/gatt_hash_settings_set.c |
| `0x0005a3c4` FUN_0005a3c4 | `gatt_remove_peer_from_attr` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/gatt_remove_peer_from_attr.c |
| `0x0005a464` FUN_0005a464 | `gatt_ccc_write` | post_init_gap, pre_init_gap, verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/gatt_ccc_write.c |
| `0x0005a5bc` FUN_0005a5bc | `gatt_cf_write` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/gatt_cf_write.c |
| `0x0005a724` FUN_0005a724 | `gatt_cf_settings_set` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/gatt_cf_settings_set.c |
| `0x0005ac30` FUN_0005ac30 | `gatt_db_hash_process` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/gatt_db_hash_process.c |
| `0x0005af8c` FUN_0005af8c | `gatt_ccc_settings_set` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/gatt_ccc_settings_set.c |
| `0x0005b554` FUN_0005b554 | `sc_restore` | pre_init_gap, verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/sc_restore.c |
| `0x0005b890` FUN_0005b890 | `gatt_send_ccc_update` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/gatt_send_ccc_update.c |
| `0x0005bbf4` FUN_0005bbf4 | `gatt_parse_find_by_type_rsp` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/gatt_parse_find_by_type_rsp.c |
| `0x0005bd18` FUN_0005bd18 | `gatt_parse_read_by_type_rsp` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/gatt_parse_read_by_type_rsp.c |
| `0x0005c004` FUN_0005c004 | `gatt_parse_read_by_type_rsp_128` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/gatt_parse_read_by_type_rsp_128.c |
| `0x0005c0bc` FUN_0005c0bc | `gatt_parse_find_info_rsp` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/gatt_parse_find_info_rsp.c |
| `0x0005c87c` FUN_0005c87c | `gatt_disconnected` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/gatt_disconnected.c |
| `0x0005cff0` FUN_0005cff0 | `FUN_0005cff0` | post_init_gap | unresolved_report_only | — |
| `0x0005d5c0` FUN_0005d5c0 | `FUN_0005d5c0` | post_init_gap | unresolved_report_only | — |
| `0x0005e130` FUN_0005e130 | `FUN_0005e130` | post_init_gap | unresolved_report_only | — |
| `0x0005e1a8` FUN_0005e1a8 | `bt_smp_distribute_keys` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/bt_smp_distribute_keys.c |
| `0x0005ea64` FUN_0005ea64 | `FUN_0005ea64` | post_init_gap | unresolved_report_only | — |
| `0x0005f654` FUN_0005f654 | `FUN_0005f654` | verified_pointer_table | unresolved_report_only | — |
| `0x0005f760` FUN_0005f760 | `FUN_0005f760` | verified_pointer_table | unresolved_report_only | — |
| `0x0005fa94` FUN_0005fa94 | `FUN_0005fa94` | verified_pointer_table | unresolved_report_only | — |
| `0x0005fb8c` FUN_0005fb8c | `FUN_0005fb8c` | verified_pointer_table | unresolved_report_only | — |
| `0x0005fc7c` FUN_0005fc7c | `FUN_0005fc7c` | verified_pointer_table | unresolved_report_only | — |
| `0x0005ffa4` FUN_0005ffa4 | `FUN_0005ffa4` | post_init_gap | unresolved_report_only | — |
| `0x00060564` FUN_00060564 | `FUN_00060564` | post_init_gap | unresolved_report_only | — |
| `0x0006058c` FUN_0006058c | `FUN_0006058c / clock_control_nrf_init` | init_entry | unresolved_report_only | — |
| `0x00060c00` FUN_00060c00 | `qspi_nor_configure / qspi_nor_init` | init_entry | resolved_existing_stock_alias | zephyr/drivers/flash/flash_nrf_qspi_nor.c |
| `0x00061070` FUN_00061070 | `storage_read_with_word_cache` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/storage_read_with_word_cache.c |
| `0x000613c4` FUN_000613c4 | `gpio_manage_callback` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/gpio_manage_callback.c |
| `0x00061ba0` FUN_00061ba0 | `FUN_00061ba0` | verified_pointer_table | unresolved_report_only | — |
| `0x00061c40` FUN_00061c40 | `FUN_00061c40` | post_init_gap | unresolved_report_only | — |
| `0x00062070` FUN_00062070 | `FUN_00062070` | post_init_gap | unresolved_report_only | — |
| `0x000620cc` FUN_000620cc | `FUN_000620cc / regulator_npm1300_common_init` | init_entry | resolved_existing_stock_alias | zephyr/drivers/regulator/regulator_npm1300.c |
| `0x00062930` FUN_00062930 | `FUN_00062930 / opt3001_init` | init_entry | resolved_existing_stock_alias | zephyr/drivers/sensor/opt3001/opt3001.c |
| `0x00062c54` FUN_00062c54 | `FUN_00062c54` | post_init_gap | unresolved_report_only | — |
| `0x00062d9c` FUN_00062d9c | `FUN_00062d9c / uarte_0_init` | init_entry | resolved_existing_stock_alias | zephyr/drivers/serial/uart_nrfx_uarte.c |
| `0x00062f28` FUN_00062f28 | `FUN_00062f28` | post_init_gap | unresolved_report_only | — |
| `0x00062fe8` FUN_00062fe8 | `FUN_00062fe8` | post_init_gap | unresolved_report_only | — |
| `0x0006312c` FUN_0006312c | `uarte_nrfx_isr / uarte_nrfx_isr_int` | sw_isr_entry | resolved_existing_stock_alias | — |
| `0x00063984` FUN_00063984 | `FUN_00063984` | verified_pointer_table | unresolved_report_only | — |
| `0x000639d4` FUN_000639d4 | `FUN_000639d4 / wdt_npm1300_init` | init_entry | resolved_existing_stock_alias | zephyr/drivers/watchdog/wdt_npm1300.c |
| `0x00063b40` wdt_event_handler | `wdt_event_handler` | verified_pointer_table | unresolved_report_only | — |
| `0x00065b9c` FUN_00065b9c | `gpiote_irq_handler / nrfx_gpiote_irq_handler` | sw_isr_entry | resolved_existing_stock_alias | — |
| `0x00068d2c` FUN_00068d2c | `lc3_load_s24_3le / load_s24_3le` | verified_pointer_table | unresolved_report_only | /Users/freedomcoder/ncs251/modules/lib/liblc3/src/lc3.c |
| `0x00068d90` FUN_00068d90 | `lc3_load_s24 / load_s24` | verified_pointer_table | unresolved_report_only | /Users/freedomcoder/ncs251/modules/lib/liblc3/src/lc3.c |
| `0x00068de8` FUN_00068de8 | `lc3_load_float / load_float` | verified_pointer_table | unresolved_report_only | /Users/freedomcoder/ncs251/modules/lib/liblc3/src/lc3.c |
| `0x0006a700` FUN_0006a700 | `lc3_ltpf_arm_resample_24k_12k8 / arm_resample_24k_12k8` | verified_pointer_table | unresolved_report_only | /Users/freedomcoder/ncs251/modules/lib/liblc3/src/ltpf.c |
| `0x0006aa98` FUN_0006aa98 | `lc3_ltpf_arm_resample_8k_12k8 / arm_resample_8k_12k8` | verified_pointer_table | unresolved_report_only | /Users/freedomcoder/ncs251/modules/lib/liblc3/src/ltpf.c |
| `0x000710b4` FUN_000710b4 | `FUN_000710b4` | pre_init_gap | unresolved_report_only | — |
| `0x0007118c` FUN_0007118c | `FUN_0007118c` | pre_init_gap | unresolved_report_only | — |
| `0x00071294` FUN_00071294 | `FUN_00071294` | pre_init_gap | unresolved_report_only | — |
| `0x00079760` mutex_init | `mutex_init` | post_init_gap | ambiguous_live_owner_rejected | nrf_cc3xx_platform_mutex.c.obj |
| `0x0007dd7e` out | `out` | pre_init_gap | emitted_unique_recovered_root | recon/symbolized/app/out.c |
| `0x0007ea64` FUN_0007ea64 | `FUN_0007ea64` | verified_pointer_table | unresolved_report_only | — |
| `0x0007eb5c` FUN_0007eb5c | `FUN_0007eb5c / ipc_static_vrings_init` | init_entry | resolved_existing_stock_alias | zephyr/subsys/ipc/ipc_service/backends/ipc_rpmsg_static_vrings.c |
| `0x0007eb7e` FUN_0007eb7e | `FUN_0007eb7e` | pre_init_gap | unresolved_report_only | — |
| `0x0007ec0e` FUN_0007ec0e | `FUN_0007ec0e` | verified_pointer_table | unresolved_report_only | — |
| `0x0007ecf2` FUN_0007ecf2 | `FUN_0007ecf2` | verified_pointer_table | unresolved_report_only | — |
| `0x0007eec0` FUN_0007eec0 | `FUN_0007eec0` | verified_pointer_table | unresolved_report_only | — |
| `0x0007f228` FUN_0007f228 | `FUN_0007f228` | post_init_gap | unresolved_report_only | — |
| `0x0007f634` FUN_0007f634 | `FUN_0007f634` | verified_pointer_table | unresolved_report_only | — |
| `0x0007f894` FUN_0007f894 | `FUN_0007f894` | verified_pointer_table | unresolved_report_only | — |
| `0x00080c8c` FUN_00080c8c | `z_impl_net_if_ipv6_addr_rm_by_index` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/z_impl_net_if_ipv6_addr_rm_by_index.c |
| `0x00081080` FUN_00081080 | `bt_le_adv_clear_pending_flag` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/bt_le_adv_clear_pending_flag.c |
| `0x0008142c` FUN_0008142c | `FUN_0008142c` | verified_pointer_table | unresolved_report_only | — |
| `0x000818dc` FUN_000818dc | `att_send_with_retry` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/att_send_with_retry.c |
| `0x00081a60` FUN_00081a60 | `FUN_00081a60` | verified_pointer_table | unresolved_report_only | — |
| `0x00081a76` FUN_00081a76 | `FUN_00081a76` | verified_pointer_table | unresolved_report_only | — |
| `0x00081c8c` FUN_00081c8c | `FUN_00081c8c` | pre_init_gap | unresolved_report_only | — |
| `0x00081fbe` FUN_00081fbe | `FUN_00081fbe` | pre_init_gap | unresolved_report_only | — |
| `0x00082282` FUN_00082282 | `FUN_00082282` | post_init_gap | unresolved_report_only | — |
| `0x000822bc` FUN_000822bc | `FUN_000822bc` | verified_pointer_table | unresolved_report_only | — |
| `0x00082326` FUN_00082326 | `FUN_00082326` | verified_pointer_table | unresolved_report_only | — |
| `0x00082396` FUN_00082396 | `FUN_00082396` | verified_pointer_table | unresolved_report_only | — |
| `0x00082c48` FUN_00082c48 | `FUN_00082c48` | post_init_gap, verified_pointer_table | unresolved_report_only | — |
| `0x00082d6a` FUN_00082d6a | `FUN_00082d6a` | verified_pointer_table | unresolved_report_only | — |
| `0x00082e04` FUN_00082e04 | `l2cap_reassemble_frag` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/l2cap_reassemble_frag.c |
| `0x00082fa6` FUN_00082fa6 | `FUN_00082fa6` | verified_pointer_table | unresolved_report_only | — |
| `0x000831e2` FUN_000831e2 | `convert_to_id_on_match` | verified_pointer_table | ambiguous_live_owner_rejected | — |
| `0x0008349c` FUN_0008349c | `FUN_0008349c` | verified_pointer_table | unresolved_report_only | — |
| `0x0008352c` FUN_0008352c | `FUN_0008352c` | post_init_gap | unresolved_report_only | — |
| `0x00083778` FUN_00083778 | `FUN_00083778` | post_init_gap | unresolved_report_only | — |
| `0x000839fe` FUN_000839fe | `FUN_000839fe` | verified_pointer_table | unresolved_report_only | — |
| `0x00083b62` FUN_00083b62 | `dev_write_bits5_diff` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/dev_write_bits5_diff.c |
| `0x00083ba6` FUN_00083ba6 | `dev_read_bits5` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/dev_read_bits5.c |
| `0x00083bca` FUN_00083bca | `dev_update_bits5` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/dev_update_bits5.c |
| `0x00083bf0` FUN_00083bf0 | `dev_write_config_word` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/dev_write_config_word.c |
| `0x00083cb4` FUN_00083cb4 | `flash_area_has_driver / gpio_npm1300_init` | init_entry | resolved_existing_stock_alias | zephyr/drivers/gpio/gpio_npm1300.c |
| `0x00083cfc` FUN_00083cfc | `FUN_00083cfc` | post_init_gap | unresolved_report_only | — |
| `0x00084348` FUN_00084348 | `regulator_set_voltage_dispatch` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/regulator_set_voltage_dispatch.c |
| `0x00084418` FUN_00084418 | `dev_configure_channel / regulator_npm1300_init` | init_entry | resolved_existing_stock_alias | zephyr/drivers/regulator/regulator_npm1300.c |
| `0x000844a8` FUN_000844a8 | `FUN_000844a8` | post_init_gap | unresolved_report_only | — |
| `0x000844e0` FUN_000844e0 | `FUN_000844e0` | post_init_gap | unresolved_report_only | — |
| `0x00084516` FUN_00084516 | `FUN_00084516` | post_init_gap | unresolved_report_only | — |
| `0x000848d2` FUN_000848d2 | `driver_register_callback_locked` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/driver_register_callback_locked.c |
| `0x0008493a` FUN_0008493a | `FUN_0008493a` | post_init_gap | unresolved_report_only | — |
| `0x000849da` FUN_000849da | `nvs_timer_arm_and_mark_dirty` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/nvs_timer_arm_and_mark_dirty.c |
| `0x00084b86` FUN_00084b86 | `flowctl_schedule_next_send` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/flowctl_schedule_next_send.c |
| `0x00084c2c` FUN_00084c2c | `driver_stop_active_timer` | post_init_gap | emitted_unique_recovered_root | recon/symbolized/app/driver_stop_active_timer.c |
| `0x00084c7e` FUN_00084c7e | `FUN_00084c7e` | verified_pointer_table | unresolved_report_only | — |
| `0x00084c94` FUN_00084c94 | `FUN_00084c94` | verified_pointer_table | unresolved_report_only | — |
| `0x00084cb0` FUN_00084cb0 | `FUN_00084cb0` | verified_pointer_table | unresolved_report_only | — |
| `0x00084d36` FUN_00084d36 | `reset_state_and_stop_timer` | pre_init_gap | emitted_unique_recovered_root | recon/symbolized/app/reset_state_and_stop_timer.c |
| `0x000859c2` FUN_000859c2 | `FUN_000859c2` | pre_init_gap | unresolved_report_only | — |
| `0x00085a04` FUN_00085a04 | `FUN_00085a04` | pre_init_gap | unresolved_report_only | — |
| `0x00085a9c` FUN_00085a9c | `FUN_00085a9c` | pre_init_gap | unresolved_report_only | — |
| `0x00085b0c` FUN_00085b0c | `FUN_00085b0c` | pre_init_gap | unresolved_report_only | — |
| `0x00085f9c` FUN_00085f9c | `cbor_decode_tstr` | pre_init_gap | emitted_unique_recovered_root | recon/symbolized/app/cbor_decode_tstr.c |
| `0x00086006` FUN_00086006 | `cbor_decode_bool` | pre_init_gap, verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/cbor_decode_bool.c |
| `0x00086f5a` FUN_00086f5a | `libc_stream_write_syscall` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/libc_stream_write_syscall.c |
| `0x00086f92` FUN_00086f92 | `FUN_00086f92` | verified_pointer_table | unresolved_report_only | — |
| `0x00087862` FUN_00087862 | `stdio_reset_ungetc_buffer` | verified_pointer_table | emitted_unique_recovered_root | recon/symbolized/app/stdio_reset_ungetc_buffer.c |
