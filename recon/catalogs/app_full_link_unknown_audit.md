# CPUAPP full-link UNKNOWN audit

Pinned to `bc394c43`; report-only classification, no bodies or aliases.

| Symbol | Category | Retained callers | Evidence |
|---|---|---|---|
| `FUN_0004c4e4` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `FUN_0005463e` | `blocked_interior` | `FUN_000545f0` | app_interior_alias_audit:blocked_embedded_noreturn_svc_island |
| `FUN_00054688` | `blocked_interior` | `FUN_000545f0` | app_interior_alias_audit:blocked_embedded_noreturn_svc_island |
| `FUN_0007a3a4` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `FUN_0007e53e` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `FUN_0007e574` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `FUN_0007e5da` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `FUN_0007e624` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `FUN_0007e672` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `FUN_0007e6e2` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `FUN_0007e776` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `FUN_0007e7ea` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `FUN_0007e83a` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `__strcat_chk` | `genuine_sdk_library_external` | `local_store_write` | zephyr-sdk-0.16.5-1:newlib-nano/libm:v8-m.main+fp/hard |
| `__strcpy_chk` | `genuine_sdk_library_external` | `bt_start, spec_ble_command_hook` | zephyr-sdk-0.16.5-1:newlib-nano/libm:v8-m.main+fp/hard |
| `__swsetup_r` | `genuine_sdk_library_external` | `__swbuf_r` | zephyr-sdk-0.16.5-1:newlib-nano/libm:v8-m.main+fp/hard |
| `_ctype_` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `_double_byte` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `_strtod_l` | `genuine_sdk_library_external` | `FUN_00077a10` | zephyr-sdk-0.16.5-1:newlib-nano/libm:v8-m.main+fp/hard |
| `cbpprintf_external` | `genuine_sdk_library_external` | `FUN_0004db04` | NCS-2.5.1:zephyr/libzephyr.a |
| `cc_mbedtls_ctr_drbg_random_with_add` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `ceilf` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `conn_lookup_handle` | `genuine_sdk_library_external` | `ble_conn_lookup_masked` | NCS-2.5.1:subsys/bluetooth/host |
| `encode_uint` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `floorf` | `genuine_sdk_library_external` | `FUN_000868fc` | zephyr-sdk-0.16.5-1:newlib-nano/libm:v8-m.main+fp/hard |
| `fmaf` | `genuine_sdk_library_external` | `FUN_00075f88, curve_table_interp_201pt, log2f, logf_core` | zephyr-sdk-0.16.5-1:newlib-nano/libm:v8-m.main+fp/hard |
| `getTrngSource` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `get_adv_name_type_param` | `genuine_sdk_library_external` | `ble_conn_le_prepare_and_connect` | NCS-2.5.1:subsys/bluetooth/host |
| `hex2bin` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `ipc_service_send` | `genuine_sdk_library_external` | `global_ipc_service_send` | NCS-2.5.1:zephyr/libzephyr.a |
| `ipc_static_vrings_init` | `genuine_sdk_library_external` | `FUN_0004cd4c` | NCS-2.5.1:zephyr/libzephyr.a |
| `is_ptr` | `genuine_sdk_library_external` | `FUN_0004abc0` | NCS-2.5.1:zephyr/libzephyr.a |
| `mbedtls_zeroize_internal` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `metal_bus_find` | `genuine_sdk_library_external` | `FUN_00068170` | NCS-2.5.1:modules/libmetal |
| `metal_io_block_set` | `genuine_sdk_library_external` | `rpmsg_virtqueue_channel_init` | NCS-2.5.1:modules/libmetal |
| `metal_io_block_write` | `genuine_sdk_library_external` | `FUN_000710b4, FUN_00071294` | NCS-2.5.1:modules/libmetal |
| `mpsc_pbuf_is_pending` | `genuine_sdk_library_external` | `z_log_msg_pending` | NCS-2.5.1:zephyr/libzephyr.a |
| `onoff_manager_init` | `genuine_sdk_library_external` | `FUN_0006058c` | NCS-2.5.1:zephyr/libzephyr.a |
| `outs` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `pinctrl_lookup_state` | `genuine_sdk_library_external` | `FUN_000838dc, FUN_00083cde, FUN_00084b14` | NCS-2.5.1:drivers/pinctrl |
| `rpmsg_create_ept` | `genuine_sdk_library_external` | `FUN_0004d0c4` | NCS-2.5.1:modules/open-amp |
| `rpmsg_deinit_vdev` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `rpmsg_get_endpoint` | `genuine_sdk_library_external` | `FUN_0007118c` | NCS-2.5.1:modules/open-amp |
| `rpmsg_register_endpoint` | `genuine_sdk_library_external` | `rpmsg_virtqueue_channel_init` | NCS-2.5.1:modules/open-amp |
| `rpmsg_send_offchannel_raw` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `rpmsg_virtio_init_shm_pool` | `genuine_sdk_library_external` | `FUN_0004d100` | NCS-2.5.1:modules/open-amp |
| `rpmsg_virtio_shm_pool_get_buffer` | `genuine_sdk_library_external` | `FUN_00085b0c, rpmsg_virtqueue_channel_init` | NCS-2.5.1:modules/open-amp |
| `snprintk` | `genuine_sdk_library_external` | `att_timeout, bt_settings_delete, format_bt_addr_str, log_output_dropped_process, random` | NCS-2.5.1:zephyr/libzephyr.a |
| `tc_aes128_set_encrypt_key` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `tc_aes_encrypt` | `duplicate_owner_byproduct` | `` | all referencing reconstruction objects excluded from retained build |
| `tc_cmac_setup` | `genuine_sdk_library_external` | `gatt_db_hash_gen` | NCS-2.5.1:zephyr/libzephyr.a |
| `tc_hmac_prng_init` | `genuine_sdk_library_external` | `ble_rng_get_random_bytes` | NCS-2.5.1:zephyr/libzephyr.a |
| `tc_hmac_prng_reseed` | `genuine_sdk_library_external` | `ble_rng_seed_from_uptime` | NCS-2.5.1:zephyr/libzephyr.a |
| `thunk_FUN_00086c78` | `ghidra_compiler_pseudo` | `` | excluded CC312 caller; thunk spelling targets mapped memset_bytes VA |
| `u8_to_dec` | `genuine_sdk_library_external` | `bt_gatt_connected, bt_settings_delete` | NCS-2.5.1:zephyr/libzephyr.a |
| `virtio_create_virtqueues` | `genuine_sdk_library_external` | `rpmsg_virtqueue_channel_init` | NCS-2.5.1:modules/open-amp |
| `virtqueue_add_buffer` | `genuine_sdk_library_external` | `FUN_000710b4, FUN_0007118c, FUN_00085a9c, rpmsg_virtqueue_channel_init` | NCS-2.5.1:modules/open-amp |
| `virtqueue_get_buffer` | `genuine_sdk_library_external` | `FUN_0007118c, FUN_00085b0c` | NCS-2.5.1:modules/open-amp |
| `virtqueue_get_buffer_length` | `genuine_sdk_library_external` | `FUN_000710b4, FUN_00085a9c` | NCS-2.5.1:modules/open-amp |

Actionable gaps: **0**.
