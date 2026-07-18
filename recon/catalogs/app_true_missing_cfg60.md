# CPUAPP true-missing CFG proof ledger

Deterministic, fail-closed receipt for the 60 reconstructed entries from `app_interior_alias_audit.json`; `0x00086228` is excluded because the audit marks it as an already-owned strong reconstruction.

- Functions: 60
- Authoritative CFG PASS: 60
- Reviewed cases: 192

- Executed checks: 1032

| VA | Raw identity | Readable name | Extent | Cases | Checked | SHA-256 |
|---|---|---|---:|---:|---:|---|
| `0x000179f8` | `FUN_000179f8` | `subsystem_enable_gpio_pin_set_adapter` | 12 | 0 | 40 | `6cb5673f56ca13656ad07fa8d27d399f24c923b823b62ce9d7d1722c225bfef4` |
| `0x00026100` | `FUN_00026100` | `update_imu_mode` | 336 | 4 | 4 | `718e8e975d9e263f7644fb6e0606bc23d5101b03cac4f3ebf1c115d97e88272e` |
| `0x00033554` | `FUN_00033554` | `framed_serial_receive_parser` | 332 | 6 | 6 | `00808621605ccc0e1f8b219fabc4cc64393187a2c18c60c8de4a1fa20d9087a5` |
| `0x00033730` | `FUN_00033730` | `send_notification_app_whitelist` | 284 | 0 | 40 | `7249981ea13bbcc6418aff3f047d26b7572db192255960321ced53906cb11195` |
| `0x0003603c` | `FUN_0003603c` | `ui_ancs_notification_task` | 296 | 3 | 3 | `eaf41f32b156a03fee9cea73f3ab2a560c330cb5da66a04f813b58e3c5f6f4b2` |
| `0x00036b3c` | `FUN_00036b3c` | `ui_new_message_task` | 508 | 4 | 4 | `b57ac1e9076deb1adb2265df343bf3fd43f5efdbbdff298fa7a0bbe1a77f5392` |
| `0x0003f410` | `FUN_0003f410` | `ui_navigation_task` | 2356 | 16 | 16 | `f60e4bd83c01f42deff82d4d93c7e83ba6148502380693e6118a37044673ade7` |
| `0x0003fecc` | `FUN_0003fecc` | `ui_translate_task` | 2072 | 3 | 3 | `ac29b3b6cc8189af3cb664bd5e1324bb67c76d20e34d9bfc5bffddb060b3f11d` |
| `0x0004b3c8` | `FUN_0004b3c8` | `sys_heap_init` | 284 | 6 | 6 | `43fcf8c0c56d08e664b514d8957b1d0741c53283dbc1ad41003068ec818cd46d` |
| `0x0004c254` | `FUN_0004c254` | `delay_scaled_busy_wait` | 24 | 2 | 2 | `5c4d2da005af9781fe5fc8c7c2de326292390dab72b4673337a6b06730c78f91` |
| `0x0004d44c` | `FUN_0004d44c` | `z_log_notify_backend_enabled` | 20 | 0 | 40 | `f6c832cdc30ecad490a96776ff377979a0d314ca546664c8fbe8cccc9ea97dcd` |
| `0x0004d468` | `FUN_0004d468` | `z_log_dropped` | 30 | 2 | 2 | `f37d43a34af224060ac8850fe3d745bbcb7ef52358e6372050eec262d8a3ceb0` |
| `0x0004d8b8` | `FUN_0004d8b8` | `z_log_msg_commit` | 28 | 0 | 40 | `a55f9c0aee0ae3dc9570c0ee6b14fc12335b2aaa0a89ce13affc07867fce19dc` |
| `0x0004de68` | `FUN_0004de68` | `log_output_dropped_process` | 74 | 0 | 40 | `3b53bc1d05a09340d9e2731ba84ccdda9c6b94ac312761062447ab85733c82ef` |
| `0x0004e3e8` | `FUN_0004e3e8` | `settings_load_subtree` | 68 | 1 | 1 | `2b9efd77c10058d6fac842175f7496b66e4ae3dba0df9c36ef5e655397c14ee3` |
| `0x0004e474` | `FUN_0004e474` | `settings_store_init` | 10 | 0 | 40 | `b03a3b089914380db7236ff736e820daea4d51a64aee465c68ea00426137f62c` |
| `0x0004e8c0` | `FUN_0004e8c0` | `settings_invalid_index_log` | 30 | 0 | 40 | `d28ffc377c2a70662bc1749285b86d9607684d0b360c8154b24136a1eeed0bf6` |
| `0x0004f500` | `FUN_0004f500` | `ANCS GATT client callback configuration setter` | 20 | 2 | 2 | `ab4c155971045739451c57881726b8805c174991ebbc0639c9c7e4a10d1ab606` |
| `0x000534a8` | `FUN_000534a8` | `hci_cmd_alloc_failure_log` | 28 | 0 | 40 | `bfa64349556e52573452cf345cbcb258a92c0991707ddf78862af6cb872350e1` |
| `0x00054d88` | `tail_54d88` | `set_random_address` | 76 | 0 | 40 | `c4a1697c9d6f43bedbf4c72b6f6d6a842a029f0316373c2d0eaca28cf4fd5f44` |
| `0x00054ea8` | `FUN_00054ea8` | `bt_id_add` | 316 | 0 | 40 | `5357d59b1ee66f796758d3918e97c999f448c64dfcb84a1f90fdd6dc01b2fbe3` |
| `0x00055aac` | `FUN_00055aac` | `legacy_advertising_connection_restart` | 226 | 0 | 40 | `12b58aae3919596f9b86277ef38ed239c979412ab7a6fa3a00fba68f0b90bdbf` |
| `0x000564cc` | `FUN_000564cc` | `bt_conn_send_cb` | 222 | 0 | 40 | `bc83eccc3f99028259e095fdd49ecc3c97edc92c546194597c66e818871d0f04` |
| `0x000573c8` | `FUN_000573c8` | `Bluetooth buffer-allocation failure logger` | 36 | 0 | 40 | `0f57933da8a66b04dc5f3b0adc4ff46fc80e463eb08a14f108989f1954915de6` |
| `0x00058568` | `FUN_00058568` | `send_err_rsp_alloc_failure_log` | 28 | 0 | 40 | `0f9e017e0e83b00d797983c62e2fcfb1d035dc61b6f32262806aa55cb2a7be79` |
| `0x0005a954` | `FUN_0005a954` | `bt_gatt_init` | 88 | 0 | 40 | `a0d180aba4f6562059fdc1114febb78cf3b9a0bfaa27b76e340758c19a7fdb84` |
| `0x0005ad38` | `FUN_0005ad38` | `bt_gatt_service_register` | 540 | 7 | 7 | `c669599067c153f5b5335fd8308684f0ef5ac08a5ea228fc078585239158aad7` |
| `0x0005c310` | `FUN_0005c310` | `gatt_prepare_write_rsp` | 156 | 8 | 8 | `7aaf94309cb1610ccbbb74893a5a49abb4e82748fcc89cf71ba5916ebbcf2e84` |
| `0x0005c6c8` | `ext5c6c8` | `bt_gatt_connected` | 142 | 0 | 40 | `986bf1f5c5c7a0231aa1e2124d7408db8d5f5da39a080f203934130621566178` |
| `0x0005c76c` | `FUN_0005c76c` | `bt_gatt_att_max_mtu_changed` | 36 | 0 | 40 | `e27b5852cefe4837a940c9b5e4ee4a34ba04d5eea82b78438aa47b5e6dc8be66` |
| `0x0005c9a4` | `FUN_0005c9a4` | `bt_gatt_disconnected` | 246 | 0 | 40 | `13e37cda0c5a8cad908aed7747951e2cf22673255ae9e224cd945765f5a0e3da` |
| `0x0005ce6c` | `FUN_0005ce6c` | `smp_public_key_periph` | 368 | 11 | 11 | `0be426dace5837cee47b1f175e4014e104bbcee3407ed743b4260c39551c234a` |
| `0x00061200` | `tail_61200` | `flash_nrf_read_invalid_address` | 42 | 2 | 2 | `41f5e532aacbd6c92fac7709b5fd7e930512d5e697b1c7a4cfbb2eea62c0f5bc` |
| `0x0006447c` | `FUN_0006447c` | `cjson_get_object_item` | 120 | 10 | 10 | `acc10c37f2d063111d55bd7887407d871ee6394637610136fe2d14c79ef4a5ec` |
| `0x00065000` | `FUN_00065000` | `nrfx_clock_stop` | 384 | 9 | 9 | `9135d35af86abd7e78151a0f678dacec682cffc77c510f7104e65edb195b4d3b` |
| `0x000680f8` | `FUN_000680f8` | `metal_bus_unregister` | 52 | 5 | 5 | `583af7d8ecb37b6beb0b6cffda04627cfcefaf3f7dc3b3ab77fbc1024ccf3c1b` |
| `0x00068298` | `FUN_00068298` | `metal_sys_init (libmetal Zephyr system backend)` | 12 | 0 | 40 | `13e9191175f67b8fc90c3e6645389c9b386db7f9d7c4bfb1157d978c99054745` |
| `0x00071560` | `FUN_00071560` | `rpmsg_init_vdev` | 40 | 0 | 40 | `4120c21a53a5bcfd41b59f75ee81e1ea06dce51d1f781166ad87d031fb95a5ad` |
| `0x000715b8` | `FUN_000715b8` | `value_encode_len` | 118 | 7 | 7 | `8f640ab22211d89f17f460674a62cf201a72a2f3022d216f1c83884ef85f711a` |
| `0x00071b2c` | `FUN_00071b2c` | `k_heap_free` | 140 | 2 | 2 | `e51a27dc1841187c3cdb24bdb7a7292d0b6040eb319abc8f5aa9fd63bb8c4131` |
| `0x00074184` | `FUN_00074184` | `z_thread_priority_set` | 26 | 0 | 40 | `580f47b8284c4cefb660b040a5331232ab85297d7de017b58e1eb9ef8d1558f1` |
| `0x000748b8` | `FUN_000748b8` | `z_thread_abort` | 358 | 6 | 6 | `bcef78f3221e65f026d7a37778e2b7bdc41ce6e5f1fa74a46bb536973bb315c0` |
| `0x00075864` | `FUN_00075864` | `z_heap_aligned_alloc` | 88 | 2 | 2 | `6378ebf3ed6dc2d0e90a7e609899584e43044b4883b7bc14d580bf228a021bf1` |
| `0x000758cc` | `FUN_000758cc` | `k_aligned_alloc` | 78 | 3 | 3 | `8f64b16f0821d799387a0381a0c00146e2e982e173262ce2ae4a678b93e8c063` |
| `0x00075e14` | `FUN_00075e14` | `__ieee754_sqrt` | 368 | 10 | 10 | `022d3e3bc99235bdaed0246d17577fa0cc01e8ba71edb7c135447c2ce3fcb0fb` |
| `0x00076bc0` | `FUN_00076bc0` | `__sinit_lock_release` | 6 | 1 | 1 | `40d3d01bef7c17c75527ed5721cf70a4b119358c248740bbfdb3972537715880` |
| `0x00077b24` | `FUN_00077b24` | `strtol` | 14 | 2 | 2 | `ea761cd3f5d476fd3319ef497e60a4d54e1283221acbf94cae3880fe8e147346` |
| `0x00077b38` | `FUN_00077b38` | `_strtoul_r` | 224 | 6 | 6 | `4ac093dda7a9081668e78eabae6112f280ad6583fbeb7fc684b221349615112e` |
| `0x00077c4c` | `FUN_00077c4c` | `_vsprintf_r` | 38 | 1 | 1 | `fc68a2569fc251ac064a4a99c5d6a6b93bd2088010f80b622aaf37ea89089bb1` |
| `0x00077c8c` | `ext77c8c` | `__swbuf_r` | 152 | 8 | 8 | `7f849fb95c70a099a72f5525783f63f00c4e13dace124cb9e10a1924ab5991cf` |
| `0x00077d30` | `tail_77d30` | `_write_r` | 32 | 3 | 3 | `1a70ece5d7c0697825a4df78efaf895d686d2247ae31d41f6fe50fd3a89cfffc` |
| `0x0007e12a` | `FUN_0007e12a` | `sys_heap_alloc` | 100 | 5 | 5 | `d86c4bb50783adc5e249c02758c1b1724f051af4985ed676a9b6734fd39772ec` |
| `0x0007ef56` | `FUN_0007ef56` | `audio_hw_lock_release` | 24 | 2 | 2 | `d17a36d0c28759d20ffd135dee136f4197d52018e9f83c46125f690c10306de0` |
| `0x00083a2c` | `FUN_00083a2c` | `flash_get_page_info` | 102 | 7 | 7 | `ee6f8ef69b151fc9aca4347cdbc21fcad48ebfcac29786a4ce1bb8c86b8e019b` |
| `0x00084e44` | `FUN_00084e44` | `flash_write_close_ate_marker` | 20 | 3 | 3 | `41a2b2590d83a9b35300124d12ad9a84847e6961ffcfcebf937226b496595a19` |
| `0x00084f06` | `FUN_00084f06` | `linked_node_at_index` | 16 | 6 | 6 | `d147172893a66432206c63154342bee90f9c5369731c12a7f34a1af25d1a2c34` |
| `0x00085c86` | `FUN_00085c86` | `zcbor_process_backup` | 108 | 9 | 9 | `e9ff4fe53d06bd2bfbfadf552d28ebc4e4950b9cfcd4c191557cf2a9ab8234cd` |
| `0x00085ef0` | `FUN_00085ef0` | `zcbor_str_decode` | 22 | 3 | 3 | `101c9a1ae1e4955447650ca85af0c386c096d9e7f7856a2c5b372d366e26e858` |
| `0x00086360` | `FUN_00086360` | `zcbor_simple_put` | 24 | 4 | 4 | `1414887e81ab0cc62e523f8c935ddbac24d7e00f94fe2996fc4492f8b67775ee` |
| `0x0008664c` | `FUN_0008664c` | `z_reschedule_unlocked` | 20 | 1 | 1 | `d5a38ea9920bb98984d29a742b452d5435544eb0995b84324a9e4a1d6c77a768` |
