#ifndef G1_APP_SYMBOLS_H
#define G1_APP_SYMBOLS_H
#ifndef bool
#define bool _Bool
#define true 1
#define false 0
#endif

/* ---- flash partitions ---- */

/* ---- MMIO registers ---- */
#define NRF_I2S0_CONFIG_CHANNELS 0x500055b8UL
#define NRF_NVMC_S       0x50039000UL
#define NRF_PDM_BASE     0x50026000UL
#define NRF_QSPI_BASE    0x5002b000UL
#define REG_50004500     0x50004500UL
#define REG_50005114     0x50005114UL
#define REG_50005514     0x50005514UL
#define REG_50005518     0x50005518UL
#define REG_5000555c     0x5000555cUL
#define REG_50005580     0x50005580UL
#define REG_5000d304     0x5000d304UL
#define REG_5000e000     0x5000e000UL
#define REG_5000e004     0x5000e004UL
#define REG_5000e00c     0x5000e00cUL
#define REG_5000e500     0x5000e500UL
#define REG_50015304     0x50015304UL
#define REG_50015504     0x50015504UL
#define REG_50017508     0x50017508UL
#define REG_50026004     0x50026004UL
#define REG_50026100     0x50026100UL
#define REG_50026104     0x50026104UL
#define REG_50026500     0x50026500UL
#define REG_5002a304     0x5002a304UL
#define REG_5002a308     0x5002a308UL
#define REG_5002b010     0x5002b010UL
#define REG_5002b100     0x5002b100UL
#define REG_5002b308     0x5002b308UL
#define REG_5002b500     0x5002b500UL
#define REG_5002b634     0x5002b634UL
#define REG_50039400     0x50039400UL

/* ---- function addresses ---- */
/* Relocation-correct rebind: function pointers now resolve to the
 * linker-placed symbol address (bit0=Thumb preserved), not the
 * original-image literal.  Aliased via __asm__ so the extern never
 * conflicts with the real definition's signature. */
extern const unsigned char __g1_fp_FUN_00021da8[] __asm__("ble_work_thread");
extern const unsigned char __g1_fp_FUN_00023844[] __asm__("brightness_level");
extern const unsigned char __g1_fp_FUN_0002a8d8[] __asm__("low_speed_peripheral_dispatch_thread");
extern const unsigned char __g1_fp_att_send_with_retry[] __asm__("att_send_with_retry");
extern const unsigned char __g1_fp_att_timeout[] __asm__("att_timeout");
extern const unsigned char __g1_fp_ble_ancs_data_req_thread[] __asm__("ble_ancs_data_req_thread");
extern const unsigned char __g1_fp_ble_conn_process_complete_or_disconnect[] __asm__("ble_conn_process_complete_or_disconnect");
extern const unsigned char __g1_fp_ble_requeue_command_via_dispatch[] __asm__("ble_requeue_command_via_dispatch");
extern const unsigned char __g1_fp_bt_ancs_cp_write_callback[] __asm__("bt_ancs_cp_write_callback");
extern const unsigned char __g1_fp_bt_ancs_data_source_handler[] __asm__("bt_ancs_data_source_handler");
extern const unsigned char __g1_fp_bt_le_adv_clear_pending_flag[] __asm__("bt_le_adv_clear_pending_flag");
extern const unsigned char __g1_fp_cbor_decode_bool[] __asm__("cbor_decode_bool");
extern const unsigned char __g1_fp_cbvprintf_wrapper[] __asm__("cbvprintf_wrapper");
extern const unsigned char __g1_fp_check_bonded_addr[] __asm__("check_bonded_addr");
extern const unsigned char __g1_fp_click_event_dispatch_loop[] __asm__("click_event_dispatch_loop");
extern const unsigned char __g1_fp_clock_event_notify_u16pair[] __asm__("clock_event_notify_u16pair");
extern const unsigned char __g1_fp_convert_to_id_on_match[] __asm__("convert_to_id_on_match");
extern const unsigned char __g1_fp_discovery_callback[] __asm__("discovery_callback");
extern const unsigned char __g1_fp_display_dispatch_thread[] __asm__("display_dispatch_thread");
extern const unsigned char __g1_fp_display_thread_handler[] __asm__("display_thread_handler");
extern const unsigned char __g1_fp_ext_flash_read[] __asm__("ext_flash_read");
extern const unsigned char __g1_fp_ext_flash_write[] __asm__("ext_flash_write");
extern const unsigned char __g1_fp_flash_ops_thread[] __asm__("flash_ops_thread");
extern const unsigned char __g1_fp_imu_fusion_thread[] __asm__("imu_fusion_thread");
extern const unsigned char __g1_fp_imu_fusion_init[] __asm__("imu_fusion_init");
extern const unsigned char __g1_fp_imu_fusion_resume[] __asm__("imu_fusion_resume");
extern const unsigned char __g1_fp_imu_fusion_suspend[] __asm__("imu_fusion_suspend");
extern const unsigned char __g1_fp_set_imu_thread_delay[] __asm__("set_imu_thread_delay");
extern const unsigned char __g1_fp_flowctl_schedule_next_send[] __asm__("flowctl_schedule_next_send");
extern const unsigned char __g1_fp_gatt_ccc_settings_set[] __asm__("gatt_ccc_settings_set");
extern const unsigned char __g1_fp_gatt_ccc_write[] __asm__("gatt_ccc_write");
extern const unsigned char __g1_fp_gatt_ccc_write_store_cb[] __asm__("gatt_ccc_write_store_cb");
extern const unsigned char __g1_fp_gatt_parse_find_by_type_rsp[] __asm__("gatt_parse_find_by_type_rsp");
extern const unsigned char __g1_fp_gatt_parse_find_info_rsp[] __asm__("gatt_parse_find_info_rsp");
extern const unsigned char __g1_fp_gatt_parse_read_by_type_rsp[] __asm__("gatt_parse_read_by_type_rsp");
extern const unsigned char __g1_fp_gatt_parse_read_by_type_rsp_128[] __asm__("gatt_parse_read_by_type_rsp_128");
extern const unsigned char __g1_fp_gatt_remove_peer_from_attr[] __asm__("gatt_remove_peer_from_attr");
extern const unsigned char __g1_fp_gatt_send_ccc_update[] __asm__("gatt_send_ccc_update");
extern const unsigned char __g1_fp_gatt_store_ccc_cf_triple[] __asm__("gatt_store_ccc_cf_triple");
extern const unsigned char __g1_fp_gatt_sub_resolve_handle[] __asm__("gatt_sub_resolve_handle");
extern const unsigned char __g1_fp_gatt_write_ccc_rsp[] __asm__("gatt_write_ccc_rsp");
extern const unsigned char __g1_fp_global_ipc_service_send[] __asm__("global_ipc_service_send");
extern const unsigned char __g1_fp_register_ipc_service_recv_callback[] __asm__("register_ipc_service_recv_callback");
extern const unsigned char __g1_fp_indicate_sc_cb[] __asm__("indicate_sc_cb");
extern const unsigned char __g1_fp_init_ble_work_thread[] __asm__("init_ble_work_thread");
extern const unsigned char __g1_fp_iobuf_ensure_capacity_and_append[] __asm__("iobuf_ensure_capacity_and_append");
extern const unsigned char __g1_fp_jdb_panel_init[] __asm__("jdb_panel_init");
extern const unsigned char __g1_fp_key_event_thread[] __asm__("key_event_thread");
extern const unsigned char __g1_fp_l2cap_chan_disconnected_cb[] __asm__("l2cap_chan_disconnected_cb");
extern const unsigned char __g1_fp_l2cap_disconnect_tx_chan[] __asm__("l2cap_disconnect_tx_chan");
extern const unsigned char __g1_fp_l2cap_reassemble_frag[] __asm__("l2cap_reassemble_frag");
extern const unsigned char __g1_fp_libc_stream_write_syscall[] __asm__("libc_stream_write_syscall");
extern const unsigned char __g1_fp_libc_write_buffer_via_putc[] __asm__("libc_write_buffer_via_putc");
extern const unsigned char __g1_fp_local_esbs_ipc_service_recv[] __asm__("local_esbs_ipc_service_recv");
extern const unsigned char __g1_fp_local_esbm_ipc_service_recv[] __asm__("local_esbm_ipc_service_recv");
extern const unsigned char __g1_fp_local_esbs_ctrl_ipc_service_recv[] __asm__("local_esbs_ctrl_ipc_service_recv");
extern const unsigned char __g1_fp_local_ipc_service_recv[] __asm__("local_ipc_service_recv");
extern const unsigned char __g1_fp_local_store_write[] __asm__("local_store_write");
extern const unsigned char __g1_fp_low_speed_peripheral_dispatch_thread_for_test[] __asm__("low_speed_peripheral_dispatch_thread_for_test");
extern const unsigned char __g1_fp_mic_transm_thread[] __asm__("mic_transm_thread");
extern const unsigned char __g1_fp_nfc_field_event_signal_sem[] __asm__("nfc_field_event_signal_sem");
extern const unsigned char __g1_fp_notify_config_change_if_connected[] __asm__("notify_config_change_if_connected");
extern const unsigned char __g1_fp_nrf53_sync_rtc_ipc_channel_setup[] __asm__("nrf53_sync_rtc_ipc_channel_setup");
extern const unsigned char __g1_fp_opt3001_read_lux_raw[] __asm__("opt3001_read_lux_raw");
extern const unsigned char __g1_fp_opt3007_chip_init[] __asm__("opt3007_chip_init");
extern const unsigned char __g1_fp_panel_off[] __asm__("panel_off");
extern const unsigned char __g1_fp_panel_on[] __asm__("panel_on");
extern const unsigned char __g1_fp_panel_suspend[] __asm__("panel_suspend");
extern const unsigned char __g1_fp_panel_resume[] __asm__("panel_resume");
extern const unsigned char __g1_fp_panel_set_brightness_level[] __asm__("panel_set_brightness_level");
extern const unsigned char __g1_fp_panel_render_screen_dispatch[] __asm__("panel_render_screen_dispatch");
extern const unsigned char __g1_fp_projector_clear_canvas[] __asm__("projector_clear_canvas");
extern const unsigned char __g1_fp_projector_flush_canvas[] __asm__("projector_flush_canvas");
extern const unsigned char __g1_fp_printf_render_float[] __asm__("printf_render_float");
extern const unsigned char __g1_fp_process_task_sync_event[] __asm__("process_task_sync_event");
extern const unsigned char __g1_fp_proxy_thread_handler[] __asm__("proxy_thread_handler");
extern const unsigned char __g1_fp_rpmsg_virtio_get_tx_buffer_wait[] __asm__("rpmsg_virtio_get_tx_buffer_wait");
extern const unsigned char __g1_fp_rpmsg_virtio_rx_notify[] __asm__("rpmsg_virtio_rx_notify");
extern const unsigned char __g1_fp_rpmsg_virtio_send_copy[] __asm__("rpmsg_virtio_send_copy");
extern const unsigned char __g1_fp_rpmsg_virtio_tx_enqueue[] __asm__("rpmsg_virtio_tx_enqueue");
extern const unsigned char __g1_fp_sc_restore[] __asm__("sc_restore");
extern const unsigned char __g1_fp_sc_restore_rsp[] __asm__("sc_restore_rsp");
extern const unsigned char __g1_fp_settings_nvs_read_fn[] __asm__("settings_nvs_read_fn");
extern const unsigned char __g1_fp_smp_dhkey_ready_cb[] __asm__("smp_dhkey_ready_cb");
extern const unsigned char __g1_fp_spi_master_init[] __asm__("spi_master_init");
extern const unsigned char __g1_fp_spi_master_trans_data_tx_rx[] __asm__("spi_master_trans_data_tx_rx");
extern const unsigned char __g1_fp_spim_select_instance_by_mode[] __asm__("spim_select_instance_by_mode");
extern const unsigned char __g1_fp_stdio_reset_ungetc_buffer[] __asm__("stdio_reset_ungetc_buffer");
extern const unsigned char __g1_fp_touch_key_thread[] __asm__("touch_key_thread");
extern const unsigned char __g1_fp_transport_dispatch_thread[] __asm__("transport_dispatch_thread");
extern const unsigned char __g1_fp_uart_callback[] __asm__("uart_callback");
extern const unsigned char __g1_fp_virtqueue_return_rx_buffer[] __asm__("virtqueue_return_rx_buffer");
extern const unsigned char __g1_fp_z_impl_net_if_ipv6_addr_rm_by_index[] __asm__("z_impl_net_if_ipv6_addr_rm_by_index");

#define ADDR_FUN_00021da8_THUMB (((unsigned long)&__g1_fp_FUN_00021da8) | 1u) /* FUN_00021da8 -> &ble_work_thread; was 0x21da9 */
#define ADDR_FUN_00023844_THUMB (((unsigned long)&__g1_fp_FUN_00023844) | 1u) /* FUN_00023844 -> &brightness_level; was 0x23845 */
#define ADDR_FUN_0002a8d8_THUMB (((unsigned long)&__g1_fp_FUN_0002a8d8) | 1u) /* FUN_0002a8d8 -> &low_speed_peripheral_dispatch_thread; was 0x2a8d9 */
/* UNRESOLVED (no defined symbol for 0x4d058) -- kept as original literal */
#define ADDR_FUN_0004d058_THUMB              0x4d059 /* FUN_0004d058 */
/* UNRESOLVED (no defined symbol for 0x7eb7e) -- kept as original literal */
#define ADDR_FUN_0007eb7e_THUMB              0x7eb7f /* FUN_0007eb7e */
/* UNRESOLVED (no defined symbol for 0x7f634) -- kept as original literal */
#define ADDR_FUN_0007f634_THUMB              0x7f635 /* FUN_0007f634 */
/* UNRESOLVED (no defined symbol for 0x81c8c) -- kept as original literal */
#define ADDR_FUN_00081c8c_THUMB              0x81c8d /* FUN_00081c8c */
/* UNRESOLVED (no defined symbol for 0x82d6a) -- kept as original literal */
#define ADDR_FUN_00082d6a_THUMB              0x82d6b /* FUN_00082d6a */
/* UNRESOLVED (no defined symbol for 0x859c2) -- kept as original literal */
#define ADDR_FUN_000859c2_THUMB              0x859c3 /* FUN_000859c2 */
/* UNRESOLVED (no defined symbol for 0x85a04) -- kept as original literal */
#define ADDR_FUN_00085a04_THUMB              0x85a05 /* FUN_00085a04 */
#define ADDR_att_send_with_retry_THUMB (((unsigned long)&__g1_fp_att_send_with_retry) | 1u) /* att_send_with_retry -> &att_send_with_retry; was 0x818dd */
#define ADDR_att_timeout_THUMB (((unsigned long)&__g1_fp_att_timeout) | 1u) /* att_timeout -> &att_timeout; was 0x59921 */
/* UNRESOLVED (no defined symbol for 0x81bd0) -- kept as original literal */
#define ADDR_attr_read_type_cb_THUMB         0x81bd1 /* attr_read_type_cb */
#define ADDR_ble_ancs_data_req_thread_THUMB (((unsigned long)&__g1_fp_ble_ancs_data_req_thread) | 1u) /* ble_ancs_data_req_thread -> &ble_ancs_data_req_thread; was 0x19719 */
#define ADDR_ble_conn_process_complete_or_disconnect_THUMB (((unsigned long)&__g1_fp_ble_conn_process_complete_or_disconnect) | 1u) /* ble_conn_process_complete_or_disconnect -> &ble_conn_process_complete_or_disconnect; was 0x570a1 */
#define ADDR_ble_requeue_command_via_dispatch_THUMB (((unsigned long)&__g1_fp_ble_requeue_command_via_dispatch) | 1u) /* ble_requeue_command_via_dispatch -> &ble_requeue_command_via_dispatch; was 0x7c245 */
/* UNRESOLVED (no defined symbol for 0x4cefc) -- kept as original literal */
#define ADDR_bound_cb_THUMB                  0x4cefd /* bound_cb */
#define ADDR_bt_ancs_cp_write_callback_THUMB (((unsigned long)&__g1_fp_bt_ancs_cp_write_callback) | 1u) /* bt_ancs_cp_write_callback -> &bt_ancs_cp_write_callback; was 0x7f5ef */
#define ADDR_bt_ancs_data_source_handler_THUMB (((unsigned long)&__g1_fp_bt_ancs_data_source_handler) | 1u) /* bt_ancs_data_source_handler -> &bt_ancs_data_source_handler; was 0x18c49 */
#define ADDR_bt_le_adv_clear_pending_flag_THUMB (((unsigned long)&__g1_fp_bt_le_adv_clear_pending_flag) | 1u) /* bt_le_adv_clear_pending_flag -> &bt_le_adv_clear_pending_flag; was 0x81081 */
#define ADDR_cbor_decode_bool_THUMB (((unsigned long)&__g1_fp_cbor_decode_bool) | 1u) /* cbor_decode_bool -> &cbor_decode_bool; was 0x86007 */
#define ADDR_cbvprintf_wrapper_THUMB (((unsigned long)&__g1_fp_cbvprintf_wrapper) | 1u) /* cbvprintf_wrapper -> &cbvprintf_wrapper; was 0x7eec1 */
#define ADDR_check_bonded_addr_THUMB (((unsigned long)&__g1_fp_check_bonded_addr) | 1u) /* check_bonded_addr -> &check_bonded_addr; was 0x183e5 */
#define ADDR_click_event_dispatch_loop_THUMB (((unsigned long)&__g1_fp_click_event_dispatch_loop) | 1u) /* click_event_dispatch_loop -> &click_event_dispatch_loop; was 0x28a1d */
#define ADDR_clock_event_notify_u16pair_THUMB (((unsigned long)&__g1_fp_clock_event_notify_u16pair) | 1u) /* clock_event_notify_u16pair -> &clock_event_notify_u16pair; was 0x7f895 */
#define ADDR_convert_to_id_on_match_THUMB (((unsigned long)&__g1_fp_convert_to_id_on_match) | 1u) /* convert_to_id_on_match -> &convert_to_id_on_match; was 0x831e3 */
#define ADDR_discovery_callback_THUMB (((unsigned long)&__g1_fp_discovery_callback) | 1u) /* discovery_callback -> &discovery_callback; was 0x4ea79 */
#define ADDR_display_dispatch_thread_THUMB (((unsigned long)&__g1_fp_display_dispatch_thread) | 1u) /* display_dispatch_thread -> &display_dispatch_thread; was 0x28bed */
#define ADDR_display_thread_handler_THUMB (((unsigned long)&__g1_fp_display_thread_handler) | 1u) /* display_thread_handler -> &display_thread_handler; was 0x49091 */
/* UNRESOLVED (no defined symbol for 0x7ecc4) -- kept as original literal */
#define ADDR_ept_cb_THUMB                    0x7ecc5 /* ept_cb */
#define ADDR_ext_flash_read_THUMB (((unsigned long)&__g1_fp_ext_flash_read) | 1u) /* ext_flash_read -> &ext_flash_read; was 0x2e399 */
#define ADDR_ext_flash_write_THUMB (((unsigned long)&__g1_fp_ext_flash_write) | 1u) /* ext_flash_write -> &ext_flash_write; was 0x2e441 */
#define ADDR_flash_ops_thread_THUMB (((unsigned long)&__g1_fp_flash_ops_thread) | 1u) /* flash_ops_thread -> &flash_ops_thread; was 0x23481 */
#define ADDR_imu_fusion_thread_THUMB (((unsigned long)&__g1_fp_imu_fusion_thread) | 1u) /* imu_fusion_thread -> &imu_fusion_thread; was 0xfe89 */
#define ADDR_imu_fusion_init_THUMB (((unsigned long)&__g1_fp_imu_fusion_init) | 1u) /* imu_fusion_init -> &imu_fusion_init; was 0x25fad */
#define ADDR_imu_fusion_resume_THUMB (((unsigned long)&__g1_fp_imu_fusion_resume) | 1u) /* imu_fusion_resume -> &imu_fusion_resume; was 0x25dc5 */
#define ADDR_imu_fusion_suspend_THUMB (((unsigned long)&__g1_fp_imu_fusion_suspend) | 1u) /* imu_fusion_suspend -> &imu_fusion_suspend; was 0x25df9 */
#define ADDR_set_imu_thread_delay_THUMB (((unsigned long)&__g1_fp_set_imu_thread_delay) | 1u) /* set_imu_thread_delay -> &set_imu_thread_delay; was 0x25d8d */
#define ADDR_flowctl_schedule_next_send_THUMB (((unsigned long)&__g1_fp_flowctl_schedule_next_send) | 1u) /* flowctl_schedule_next_send -> &flowctl_schedule_next_send; was 0x84b87 */
/* UNRESOLVED (no defined symbol for 0x8278a) -- kept as original literal */
#define ADDR_gatt_cancel_encode_THUMB        0x8278b /* gatt_cancel_encode */
#define ADDR_gatt_ccc_settings_set_THUMB (((unsigned long)&__g1_fp_gatt_ccc_settings_set) | 1u) /* gatt_ccc_settings_set -> &gatt_ccc_settings_set; was 0x5af8d */
#define ADDR_gatt_ccc_write_THUMB (((unsigned long)&__g1_fp_gatt_ccc_write) | 1u) /* gatt_ccc_write -> &gatt_ccc_write; was 0x5a465 */
#define ADDR_gatt_ccc_write_store_cb_THUMB (((unsigned long)&__g1_fp_gatt_ccc_write_store_cb) | 1u) /* gatt_ccc_write_store_cb -> &gatt_ccc_write_store_cb; was 0x59ded */
/* UNRESOLVED (no defined symbol for 0x8279c) -- kept as original literal */
#define ADDR_gatt_exec_encode_THUMB          0x8279d /* gatt_exec_encode */
/* UNRESOLVED (no defined symbol for 0x82772) -- kept as original literal */
#define ADDR_gatt_find_info_encode_THUMB     0x82773 /* gatt_find_info_encode */
/* UNRESOLVED (no defined symbol for 0x825d4) -- kept as original literal */
#define ADDR_gatt_indicate_rsp_THUMB         0x825d5 /* gatt_indicate_rsp */
#define ADDR_gatt_parse_find_by_type_rsp_THUMB (((unsigned long)&__g1_fp_gatt_parse_find_by_type_rsp) | 1u) /* gatt_parse_find_by_type_rsp -> &gatt_parse_find_by_type_rsp; was 0x5bbf5 */
#define ADDR_gatt_parse_find_info_rsp_THUMB (((unsigned long)&__g1_fp_gatt_parse_find_info_rsp) | 1u) /* gatt_parse_find_info_rsp -> &gatt_parse_find_info_rsp; was 0x5c0bd */
#define ADDR_gatt_parse_read_by_type_rsp_128_THUMB (((unsigned long)&__g1_fp_gatt_parse_read_by_type_rsp_128) | 1u) /* gatt_parse_read_by_type_rsp_128 -> &gatt_parse_read_by_type_rsp_128; was 0x5c005 */
#define ADDR_gatt_parse_read_by_type_rsp_THUMB (((unsigned long)&__g1_fp_gatt_parse_read_by_type_rsp) | 1u) /* gatt_parse_read_by_type_rsp -> &gatt_parse_read_by_type_rsp; was 0x5bd19 */
/* UNRESOLVED (no defined symbol for 0x82856) -- kept as original literal */
#define ADDR_gatt_prepare_write_encode_THUMB 0x82857 /* gatt_prepare_write_encode */
/* UNRESOLVED (no defined symbol for 0x827ae) -- kept as original literal */
#define ADDR_gatt_read_group_encode_THUMB    0x827af /* gatt_read_group_encode */
/* UNRESOLVED (no defined symbol for 0x827de) -- kept as original literal */
#define ADDR_gatt_read_type_encode_THUMB     0x827df /* gatt_read_type_encode */
#define ADDR_gatt_remove_peer_from_attr_THUMB (((unsigned long)&__g1_fp_gatt_remove_peer_from_attr) | 1u) /* gatt_remove_peer_from_attr -> &gatt_remove_peer_from_attr; was 0x5a3c5 */
#define ADDR_gatt_send_ccc_update_THUMB (((unsigned long)&__g1_fp_gatt_send_ccc_update) | 1u) /* gatt_send_ccc_update -> &gatt_send_ccc_update; was 0x5b891 */
#define ADDR_gatt_store_ccc_cf_triple_THUMB (((unsigned long)&__g1_fp_gatt_store_ccc_cf_triple) | 1u) /* gatt_store_ccc_cf_triple -> &gatt_store_ccc_cf_triple; was 0x82fa7 */
#define ADDR_gatt_sub_resolve_handle_THUMB (((unsigned long)&__g1_fp_gatt_sub_resolve_handle) | 1u) /* gatt_sub_resolve_handle -> &gatt_sub_resolve_handle; was 0x86f93 */
/* UNRESOLVED (no defined symbol for 0x82b6e) -- kept as original literal */
#define ADDR_gatt_write_ccc_buf_THUMB        0x82b6f /* gatt_write_ccc_buf */
#define ADDR_gatt_write_ccc_rsp_THUMB (((unsigned long)&__g1_fp_gatt_write_ccc_rsp) | 1u) /* gatt_write_ccc_rsp -> &gatt_write_ccc_rsp; was 0x5a1b1 */
/* UNRESOLVED (no defined symbol for 0x8281a) -- kept as original literal */
#define ADDR_gatt_write_encode_THUMB         0x8281b /* gatt_write_encode */
/* UNRESOLVED (no defined symbol for 0x8260c) -- kept as original literal */
#define ADDR_gen_hash_m_THUMB                0x8260d /* gen_hash_m */
#define ADDR_global_ipc_service_send_THUMB (((unsigned long)&__g1_fp_global_ipc_service_send) | 1u) /* global_ipc_service_send -> &global_ipc_service_send; was 0x25b79 */
/* iteration 4: the sibling slot ctx[0x64].  Was the raw pin rodata_25ae9
 * (original 0x25ae9); now reloc-backed to the reconstructed registrar. */
#define ADDR_register_ipc_service_recv_callback_THUMB (((unsigned long)&__g1_fp_register_ipc_service_recv_callback) | 1u) /* register_ipc_service_recv_callback -> &register_ipc_service_recv_callback; was 0x25ae9 */
/* UNRESOLVED (no defined symbol for 0x545f0) -- kept as original literal */
#define ADDR_hci_tx_thread_THUMB             0x545f1 /* hci_tx_thread */
#define ADDR_indicate_sc_cb_THUMB (((unsigned long)&__g1_fp_indicate_sc_cb) | 1u) /* indicate_sc_cb -> &indicate_sc_cb; was 0x18a39 */
#define ADDR_init_ble_work_thread_THUMB (((unsigned long)&__g1_fp_init_ble_work_thread) | 1u) /* init_ble_work_thread -> &init_ble_work_thread; was 0x2201d */
#define ADDR_iobuf_ensure_capacity_and_append_THUMB (((unsigned long)&__g1_fp_iobuf_ensure_capacity_and_append) | 1u) /* iobuf_ensure_capacity_and_append -> &iobuf_ensure_capacity_and_append; was 0x87737 */
#define ADDR_jdb_panel_init_THUMB (((unsigned long)&__g1_fp_jdb_panel_init) | 1u) /* jdb_panel_init -> &jdb_panel_init; was 0x46fc1 */
#define ADDR_key_event_thread_THUMB (((unsigned long)&__g1_fp_key_event_thread) | 1u) /* key_event_thread -> &key_event_thread; was 0x2955d */
#define ADDR_l2cap_chan_disconnected_cb_THUMB (((unsigned long)&__g1_fp_l2cap_chan_disconnected_cb) | 1u) /* l2cap_chan_disconnected_cb -> &l2cap_chan_disconnected_cb; was 0x81a77 */
#define ADDR_l2cap_disconnect_tx_chan_THUMB (((unsigned long)&__g1_fp_l2cap_disconnect_tx_chan) | 1u) /* l2cap_disconnect_tx_chan -> &l2cap_disconnect_tx_chan; was 0x81a61 */
#define ADDR_l2cap_reassemble_frag_THUMB (((unsigned long)&__g1_fp_l2cap_reassemble_frag) | 1u) /* l2cap_reassemble_frag -> &l2cap_reassemble_frag; was 0x82e05 */
#define ADDR_libc_stream_write_syscall_THUMB (((unsigned long)&__g1_fp_libc_stream_write_syscall) | 1u) /* libc_stream_write_syscall -> &libc_stream_write_syscall; was 0x86f5b */
#define ADDR_libc_write_buffer_via_putc_THUMB (((unsigned long)&__g1_fp_libc_write_buffer_via_putc) | 1u) /* libc_write_buffer_via_putc -> &libc_write_buffer_via_putc; was 0x86cb7 */
#define ADDR_local_esbs_ipc_service_recv_THUMB (((unsigned long)&__g1_fp_local_esbs_ipc_service_recv) | 1u) /* local_esbs_ipc_service_recv -> &local_esbs_ipc_service_recv; was 0x15961 */
#define ADDR_local_esbm_ipc_service_recv_THUMB (((unsigned long)&__g1_fp_local_esbm_ipc_service_recv) | 1u) /* local_esbm_ipc_service_recv -> &local_esbm_ipc_service_recv; was 0x16bf1 */
#define ADDR_local_esbs_ctrl_ipc_service_recv_THUMB (((unsigned long)&__g1_fp_local_esbs_ctrl_ipc_service_recv) | 1u) /* local_esbs_ctrl_ipc_service_recv -> &local_esbs_ctrl_ipc_service_recv; was 0x7c00d */
#define ADDR_local_ipc_service_recv_THUMB (((unsigned long)&__g1_fp_local_ipc_service_recv) | 1u) /* local_ipc_service_recv -> &local_ipc_service_recv; was 0x162ed */
#define ADDR_local_store_write_THUMB (((unsigned long)&__g1_fp_local_store_write) | 1u) /* local_store_write -> &local_store_write; was 0x22169 */
#define ADDR_low_speed_peripheral_dispatch_thread_for_test_THUMB (((unsigned long)&__g1_fp_low_speed_peripheral_dispatch_thread_for_test) | 1u) /* low_speed_peripheral_dispatch_thread_for_test -> &low_speed_peripheral_dispatch_thread_for_test; was 0x2685d */
#define ADDR_mic_transm_thread_THUMB (((unsigned long)&__g1_fp_mic_transm_thread) | 1u) /* mic_transm_thread -> &mic_transm_thread; was 0x324bd */
#define ADDR_nfc_field_event_signal_sem_THUMB (((unsigned long)&__g1_fp_nfc_field_event_signal_sem) | 1u) /* nfc_field_event_signal_sem -> &nfc_field_event_signal_sem; was 0x1793d */
#define ADDR_notify_config_change_if_connected_THUMB (((unsigned long)&__g1_fp_notify_config_change_if_connected) | 1u) /* notify_config_change_if_connected -> &notify_config_change_if_connected; was 0x17e85 */
#define ADDR_nrf53_sync_rtc_ipc_channel_setup_THUMB (((unsigned long)&__g1_fp_nrf53_sync_rtc_ipc_channel_setup) | 1u) /* nrf53_sync_rtc_ipc_channel_setup -> &nrf53_sync_rtc_ipc_channel_setup; was 0x4c419 */
#define ADDR_opt3001_read_lux_raw_THUMB (((unsigned long)&__g1_fp_opt3001_read_lux_raw) | 1u) /* opt3001_read_lux_raw -> &opt3001_read_lux_raw; was 0x2e649 */
#define ADDR_opt3007_chip_init_THUMB (((unsigned long)&__g1_fp_opt3007_chip_init) | 1u) /* opt3007_chip_init -> &opt3007_chip_init; was 0x2e67d */
#define ADDR_panel_off_THUMB (((unsigned long)&__g1_fp_panel_off) | 1u) /* panel_off -> &panel_off; was 0x46d2d */
#define ADDR_panel_on_THUMB (((unsigned long)&__g1_fp_panel_on) | 1u) /* panel_on -> &panel_on; was 0x46dd9 */
/* iteration 14: the six remaining slots of the projector-controller vtable
 * written by quicknote_buffer_pool_init (0x47148).  Ghidra folded each of
 * these into the tail of the preceding symbol, so our build kept them as raw
 * flash literals and global_system_suspend's `blx [ctx+0xb70]` faulted. */
#define ADDR_panel_suspend_THUMB (((unsigned long)&__g1_fp_panel_suspend) | 1u) /* panel_suspend -> &panel_suspend; was 0x46d8d */
#define ADDR_panel_resume_THUMB (((unsigned long)&__g1_fp_panel_resume) | 1u) /* panel_resume -> &panel_resume; was 0x46f21 */
#define ADDR_panel_set_brightness_level_THUMB (((unsigned long)&__g1_fp_panel_set_brightness_level) | 1u) /* panel_set_brightness_level -> &panel_set_brightness_level; was 0x46ce9 */
#define ADDR_panel_render_screen_dispatch_THUMB (((unsigned long)&__g1_fp_panel_render_screen_dispatch) | 1u) /* panel_render_screen_dispatch -> &panel_render_screen_dispatch; was 0x35775 */
#define ADDR_projector_clear_canvas_THUMB (((unsigned long)&__g1_fp_projector_clear_canvas) | 1u) /* projector_clear_canvas -> &projector_clear_canvas; was 0x7d4cb */
#define ADDR_projector_flush_canvas_THUMB (((unsigned long)&__g1_fp_projector_flush_canvas) | 1u) /* projector_flush_canvas -> &projector_flush_canvas; was 0x7d4d7 */
#define ADDR_printf_render_float_THUMB (((unsigned long)&__g1_fp_printf_render_float) | 1u) /* printf_render_float -> &printf_render_float; was 0x7712d */
#define ADDR_process_task_sync_event_THUMB (((unsigned long)&__g1_fp_process_task_sync_event) | 1u) /* process_task_sync_event -> &process_task_sync_event; was 0x286f9 */
#define ADDR_proxy_thread_handler_THUMB (((unsigned long)&__g1_fp_proxy_thread_handler) | 1u) /* proxy_thread_handler -> &proxy_thread_handler; was 0x47c49 */
/* UNRESOLVED (no defined symbol for 0x8275e) -- kept as original literal */
#define ADDR_read_included_uuid_encode_THUMB 0x8275f /* read_included_uuid_encode */
#define ADDR_rpmsg_virtio_get_tx_buffer_wait_THUMB (((unsigned long)&__g1_fp_rpmsg_virtio_get_tx_buffer_wait) | 1u) /* rpmsg_virtio_get_tx_buffer_wait -> &rpmsg_virtio_get_tx_buffer_wait; was 0x85b0d */
#define ADDR_rpmsg_virtio_rx_notify_THUMB (((unsigned long)&__g1_fp_rpmsg_virtio_rx_notify) | 1u) /* rpmsg_virtio_rx_notify -> &rpmsg_virtio_rx_notify; was 0x7118d */
#define ADDR_rpmsg_virtio_send_copy_THUMB (((unsigned long)&__g1_fp_rpmsg_virtio_send_copy) | 1u) /* rpmsg_virtio_send_copy -> &rpmsg_virtio_send_copy; was 0x71295 */
#define ADDR_rpmsg_virtio_tx_enqueue_THUMB (((unsigned long)&__g1_fp_rpmsg_virtio_tx_enqueue) | 1u) /* rpmsg_virtio_tx_enqueue -> &rpmsg_virtio_tx_enqueue; was 0x710b5 */
#define ADDR_sc_restore_THUMB (((unsigned long)&__g1_fp_sc_restore) | 1u) /* sc_restore -> &sc_restore; was 0x5b555 */
#define ADDR_sc_restore_rsp_THUMB (((unsigned long)&__g1_fp_sc_restore_rsp) | 1u) /* sc_restore_rsp -> &sc_restore_rsp; was 0x82bd5 */
#define ADDR_settings_nvs_read_fn_THUMB (((unsigned long)&__g1_fp_settings_nvs_read_fn) | 1u) /* settings_nvs_read_fn -> &settings_nvs_read_fn; was 0x7f211 */
#define ADDR_smp_dhkey_ready_cb_THUMB (((unsigned long)&__g1_fp_smp_dhkey_ready_cb) | 1u) /* smp_dhkey_ready_cb -> &smp_dhkey_ready_cb; was 0x8349d */
/* UNRESOLVED (no defined symbol for 0x80ab4) -- kept as original literal */
#define ADDR_smp_handle_reqs_THUMB           0x80ab5 /* smp_handle_reqs */
#define ADDR_spi_master_init_THUMB (((unsigned long)&__g1_fp_spi_master_init) | 1u) /* spi_master_init -> &spi_master_init; was 0x26419 */
#define ADDR_spi_master_trans_data_tx_rx_THUMB (((unsigned long)&__g1_fp_spi_master_trans_data_tx_rx) | 1u) /* spi_master_trans_data_tx_rx -> &spi_master_trans_data_tx_rx; was 0x262ad */
#define ADDR_spim_select_instance_by_mode_THUMB (((unsigned long)&__g1_fp_spim_select_instance_by_mode) | 1u) /* spim_select_instance_by_mode -> &spim_select_instance_by_mode; was 0x26339 */
#define ADDR_stdio_reset_ungetc_buffer_THUMB (((unsigned long)&__g1_fp_stdio_reset_ungetc_buffer) | 1u) /* stdio_reset_ungetc_buffer -> &stdio_reset_ungetc_buffer; was 0x87863 */
#define ADDR_touch_key_thread_THUMB (((unsigned long)&__g1_fp_touch_key_thread) | 1u) /* touch_key_thread -> &touch_key_thread; was 0x2a0d9 */
#define ADDR_transport_dispatch_thread_THUMB (((unsigned long)&__g1_fp_transport_dispatch_thread) | 1u) /* transport_dispatch_thread -> &transport_dispatch_thread; was 0x2a4f5 */
#define ADDR_uart_callback_THUMB (((unsigned long)&__g1_fp_uart_callback) | 1u) /* uart_callback -> &uart_callback; was 0x33385 */
#define ADDR_virtqueue_return_rx_buffer_THUMB (((unsigned long)&__g1_fp_virtqueue_return_rx_buffer) | 1u) /* virtqueue_return_rx_buffer -> &virtqueue_return_rx_buffer; was 0x85a9d */
/* UNRESOLVED (no defined symbol for 0x7ee48) -- kept as original literal */
#define ADDR_z_cbprintf_cpy_THUMB            0x7ee49 /* z_cbprintf_cpy */
#define ADDR_z_impl_net_if_ipv6_addr_rm_by_index_THUMB (((unsigned long)&__g1_fp_z_impl_net_if_ipv6_addr_rm_by_index) | 1u) /* z_impl_net_if_ipv6_addr_rm_by_index -> &z_impl_net_if_ipv6_addr_rm_by_index; was 0x80c8d */
/* ---- RAM globals / kernel objects (738) ---- */
extern volatile unsigned int g_sram_base_word; /* @0x20000000 */
extern volatile unsigned int g_20000800; /* @0x20000800 */
extern volatile unsigned int g_ble_dev_state; /* @0x20002000 */
extern unsigned char g_bt_le_legacy_adv[]; /* @0x20002018 */
extern volatile unsigned int g_ble_adv_ctx_peer_addr; /* @0x20002021 */
extern volatile unsigned int g_ble_adv_ctx_flags; /* @0x20002028 */
extern volatile unsigned int g_20002069; /* @0x20002069 */
extern volatile unsigned char g_2000206f; /* @0x2000206f */
extern volatile unsigned int g_ble_dev_acl_buf_info; /* @0x20002078 */
extern volatile int g_ble_dev_ncmd_sem; /* @0x200020d4 */
extern volatile unsigned char g_ble_dev_le_features; /* @0x200020d8 */
extern volatile unsigned short g_bt_dev_hci_buf_ready; /* @0x20002104 */
extern volatile unsigned int g_ble_dev_le_pkts_sem; /* @0x20002108 */
extern volatile int g_ble_conn_ext_mode_pending; /* @0x20002110 */
extern volatile unsigned char g_ble_rl_entries_max; /* @0x20002120 */
extern volatile unsigned char g_ble_rl_entries_cnt; /* @0x20002121 */
extern volatile unsigned int g_20002128; /* @0x20002128 */
extern volatile unsigned int g_20002140; /* @0x20002140 */
extern volatile unsigned int g_bt_hci_recv_fifo; /* @0x20002144 */
extern volatile unsigned int hci_cmd_pool; /* @0x2000214c */
extern volatile unsigned long g_20002168; /* @0x20002168 */
extern unsigned char g_bt_dev_name[]; /* @0x2000216c */
extern volatile unsigned int adc_context; /* @0x20002190 */
extern volatile unsigned int g_adc_context_lock; /* @0x200021d0 */
extern volatile unsigned int g_adc_saadc_ctrl_mutex; /* @0x200021e8 */
extern volatile unsigned int m_adc_channel_input_cfg; /* @0x20002230 */
extern volatile int g_log_level; /* @0x2000230c */
extern unsigned int g_screen_render_table[]; /* @0x20002430 */
extern volatile unsigned int g_ancs_notify_sync_obj; /* @0x20002310 */
extern volatile unsigned int g_ancs_last_cmd_id; /* @0x2000231c */
extern volatile unsigned int g_20002320; /* @0x20002320 */
extern volatile unsigned int g_20002328; /* @0x20002328 */
extern volatile unsigned int g_20002338; /* @0x20002338 */
extern volatile unsigned int g_20002350; /* @0x20002350 */
extern volatile unsigned int g_20002358; /* @0x20002358 */
extern volatile unsigned int g_t_init; /* @0x20002368 */
extern volatile unsigned int g_box_event_state_buf; /* @0x20002380 */
extern volatile unsigned int g_st25dv_i2c_dev; /* @0x200023cc */
extern volatile unsigned int g_serialization_ipc_ept_ctx; /* @0x200023dc */
extern volatile int g_level_calc_result_cache; /* @0x200023f4 */
extern volatile int g_panel_calib_last_divisor; /* @0x200023f8 */
extern volatile unsigned int g_opt3007_bus_dev; /* @0x200023fc */
extern volatile int g_audio_flash_write_offset; /* @0x20002404 */
extern volatile unsigned int g_pt_nfc_link_cfg_static; /* @0x20002408 */
extern volatile unsigned int g_misc_dev_handle_2418; /* @0x20002418 */
extern volatile unsigned int g_20002420; /* @0x20002420 */
extern volatile int g_fuel_gauge_dev; /* @0x20002424 */
extern volatile int g_pt_comm_dev; /* @0x20002428 */
extern volatile unsigned char g_pt_comm_state; /* @0x2000242c */
extern volatile unsigned int g_demo_img_cached_height; /* @0x200024e0 */
extern volatile unsigned int g_demo_img_cached_width; /* @0x200024e4 */
extern volatile signed int g_quicknote_warn_offset_ms; /* @0x200024e8 */
extern volatile signed int g_even_ai_saved_page_index; /* @0x200024ec */
extern volatile unsigned int g_status_icon_last_state; /* @0x200024f0 */
extern volatile unsigned int g_translate_lang_string_table; /* @0x200024f4 */
extern volatile unsigned int g_display_canvas_y_cache; /* @0x2000253c */
extern volatile unsigned int g_display_canvas_x_cache; /* @0x20002540 */
extern volatile signed int g_dashboard_display_level; /* @0x20002544 */
extern volatile unsigned int g_fdtable_entries; /* @0x20002548 */
extern volatile unsigned int g_fdtable_refcount_field; /* @0x20002550 */
extern volatile unsigned int g_misc_val_27c8; /* @0x200027c8 */
extern volatile unsigned int g_200027f8; /* @0x200027f8 */
extern volatile unsigned int g_settings_nvs_backend_list_next; /* @0x200027fc */
extern volatile unsigned int g_20002838; /* @0x20002838 */
extern volatile unsigned int g_misc_286c_val; /* @0x2000286c */
extern volatile unsigned int g_200028b8; /* @0x200028b8 */
extern volatile unsigned int g_200028ec; /* @0x200028ec */
extern volatile unsigned int g_ancs_notify_work; /* @0x20002934 */
extern volatile unsigned int g_20002944; /* @0x20002944 */
extern volatile unsigned int g_20002958; /* @0x20002958 */
extern volatile unsigned int g_bt_hci_rx_work; /* @0x20002980 */
extern volatile unsigned int g_ble_conn_poll_signal; /* @0x20002990 */
extern volatile unsigned int att_prep_write_rsp_buf; /* @0x200029a0 */
extern volatile unsigned int g_bt_att_chan_ops; /* @0x200029ac */
extern volatile unsigned int g_200029d4; /* @0x200029d4 */
extern volatile unsigned int g_200029f8; /* @0x200029f8 */
extern volatile unsigned int g_bt_gatt_sc_ccc; /* @0x20002a20 */
extern volatile unsigned int g_bt_smp_settings_load_cb; /* @0x20002a50 */
extern volatile unsigned int g_cjson_hooks; /* @0x20002bac */
extern volatile unsigned long g_cjson_free_hook; /* @0x20002bb0 */
extern volatile unsigned int g_20002bb8; /* @0x20002bb8 */
extern volatile unsigned int g_flag32_channel_alloc_mask; /* @0x20002bbc */
extern unsigned char g_gpiote_cb[]; /* @0x20002bc0 */
extern volatile int g_gpiote_cb_evt; /* @0x20002bc4 */
extern volatile unsigned int g_ancs_notify_sync_field0_2bc8; /* @0x20002bc8 */
extern volatile unsigned int g_ancs_notify_sync_field1_2bcc; /* @0x20002bcc */
extern volatile unsigned int g_gpiote_lock; /* @0x20002c30 */
extern volatile unsigned int g_nrfx_gpiote_channels_mask; /* @0x20002c34 */
extern volatile unsigned int g_module_registry_node; /* @0x20002c3c */
extern volatile unsigned int g_20002c68; /* @0x20002c68 */
extern volatile unsigned int g_20002c90; /* @0x20002c90 */
extern volatile unsigned int g_20002cb8; /* @0x20002cb8 */
extern volatile unsigned int g_20002cf4; /* @0x20002cf4 */
extern volatile unsigned int g_20002cfc; /* @0x20002cfc */
extern volatile unsigned int g_20002d00; /* @0x20002d00 */
extern volatile unsigned int g_audio_755f8_wait_obj; /* @0x20002d04 */
extern volatile float g_batt_soc_curve_charge_lo; /* @0x20002d14 */
extern volatile float g_batt_soc_curve_charge_hi; /* @0x20002d18 */
extern volatile float g_spline_nan_sentinel; /* @0x20002d1c */
extern volatile int g_libc_heap_ctrl; /* @0x20002d20 */
extern volatile unsigned int g_20002d84; /* @0x20002d84 */
extern volatile unsigned int g_misc_static_ctx_ptr; /* @0x20002e74 */
extern volatile unsigned int g_misc_deferred_req_params; /* @0x20002ef8 */
extern volatile unsigned int g_misc_deferred_call_desc; /* @0x20002f0c */
extern volatile unsigned int g_ancs_conn_param; /* @0x20002f60 */
extern volatile unsigned char g_esb_bringup_log_pending_flag; /* @0x20002fe0 */
extern volatile unsigned int g_product_code_buf; /* @0x20002fe3 */
extern volatile unsigned int g_device_serial_buf; /* @0x20003003 */
extern volatile unsigned int g_20003023; /* @0x20003023 */
extern volatile char g_level_calc_input_c_cache; /* @0x20003024 */
extern volatile unsigned int g_check_work_mode_ed5_field_cache; /* @0x20003025 */
extern volatile unsigned int g_glassbox_lid_debounced_state; /* @0x20003026 */
extern volatile unsigned int g_last_reported_battery_pct; /* @0x20003027 */
extern volatile unsigned int g_last_reported_box_charge_status; /* @0x20003028 */
extern volatile unsigned int g_last_reported_box_charge_pct; /* @0x20003029 */
extern volatile unsigned int g_charge_notify_state_init_flag; /* @0x2000302a */
extern volatile unsigned char g_esb_sync_inbound_status; /* @0x2000302b */
extern volatile unsigned char g_flash_crc_active_flag; /* @0x2000302c */
extern volatile unsigned char g_last_standby_event_id; /* @0x2000302d */
extern volatile unsigned char g_send_event_pending_id; /* @0x2000302e */
extern volatile unsigned char g_low_battery_sync_flag; /* @0x2000302f */
extern volatile unsigned char g_pt_nfc_link_init_active; /* @0x20003030 */
extern volatile unsigned char g_periodic_check_ok_flag; /* @0x20003031 */
extern volatile unsigned char g_200033d2; /* @0x200033d2 */
extern volatile unsigned char g_200033d3; /* @0x200033d3 */
extern volatile unsigned char g_demo_image_last_page_idx; /* @0x200033d4 */
extern volatile unsigned int g_200034f3; /* @0x200034f3 */
extern volatile char onboarding_last_step_cache; /* @0x200034f5 */
extern volatile unsigned char g_gui_dark_light_dither_mask; /* @0x200034f6 */
extern volatile unsigned int g_md5_padding; /* @0x200034f7 */
extern volatile unsigned char g_smp_bondable_default; /* @0x200035ae */
extern volatile signed char g_libm_ieee_mode_flag; /* @0x200035af */
extern volatile unsigned int g_log_msg_mpsc_buffer; /* @0x20003648 */
extern volatile unsigned int g_200036c8; /* @0x200036c8 */
extern volatile unsigned int g_20003700; /* @0x20003700 */
extern volatile unsigned int g_bt_att_slab; /* @0x20003738 */
extern volatile unsigned int g_bt_att_chan_slab; /* @0x20003758 */
extern volatile unsigned int g_20003778; /* @0x20003778 */
extern volatile unsigned int req_slab; /* @0x20003798 */
extern volatile unsigned int g_uart_rx_mem_slab; /* @0x200037b8 */
extern volatile unsigned int g_malloc_lock; /* @0x200037f0 */
extern volatile unsigned int g_malloc_mutex; /* @0x20003804 */
extern volatile unsigned int g_env_mutex; /* @0x20003818 */
extern volatile unsigned int g_settings_lock; /* @0x20003868 */
extern volatile unsigned int g_audio_msgq; /* @0x20003890 */
extern volatile unsigned int g_display_msgq; /* @0x200038c4 */
extern volatile unsigned int g_bt_data_pipe; /* @0x200038f8 */
extern volatile unsigned int g_dashboard_response_msgq; /* @0x2000392c */
extern volatile unsigned int g_quicknote_flash_msgq; /* @0x20003960 */
extern volatile unsigned int g_flash_store_cmd_msgq; /* @0x20003994 */
extern volatile unsigned int g_serialization_ipc_mutex; /* @0x200039c8 */
extern volatile unsigned int g_200039f8; /* @0x200039f8 */
extern volatile unsigned int g_bt_att_pool; /* @0x20003a28 */
extern volatile unsigned int free_l2cap_tx_meta_data; /* @0x20003a44 */
extern volatile unsigned int g_bt_conn_tx_pending_cnt; /* @0x20003a60 */
extern volatile unsigned int acl_tx_pool; /* @0x20003a7c */
extern volatile unsigned int g_bt_conn_frag_pool; /* @0x20003b18 */
extern volatile int g_hci_cmd_pool; /* @0x20003b4c */
extern volatile unsigned int g_ancs_notify_3be8; /* @0x20003be8 */
extern volatile unsigned int g_ancs_work_thread; /* @0x20003c50 */
extern volatile unsigned int g_ble_work_timer; /* @0x20003d28 */
extern volatile unsigned int g_ble_work_thread; /* @0x20003d60 */
extern volatile unsigned int g_flash_ops_thread; /* @0x20003e38 */
extern volatile unsigned int g_brightness_thread; /* @0x20003f10 */
extern volatile unsigned int g_imu_fusion_thread; /* @0x20003fe8 */
extern volatile unsigned long long g_delay_deadline_ticks; /* @0x200040c8 */
extern volatile unsigned int g_200040d0; /* @0x200040d0 */
extern volatile unsigned int g_200041a8; /* @0x200041a8 */
extern volatile unsigned int g_20004280; /* @0x20004280 */
extern volatile unsigned int g_20004358; /* @0x20004358 */
extern volatile unsigned int g_20004430; /* @0x20004430 */
extern volatile unsigned int g_20004508; /* @0x20004508 */
extern volatile unsigned int g_200045e0; /* @0x200045e0 */
extern volatile unsigned int g_200046b8; /* @0x200046b8 */
extern volatile unsigned long long g_fuel_gauge_init_timestamp; /* @0x20004790 */
extern volatile unsigned int g_aging_mode_aux_thread; /* @0x20004798 */
extern volatile unsigned int g_aging_mode_thread; /* @0x20004870 */
extern volatile long long g_deadline_10s; /* @0x20004948 */
extern volatile unsigned int g_dashboard_widget_state; /* @0x20004950 */
extern volatile unsigned int g_display_last_drawn_lang; /* @0x20004968 */
extern volatile unsigned char g_dashboard_disp_mode; /* @0x2000496a */
extern volatile unsigned int g_quicknote_info; /* @0x20004978 */
extern volatile unsigned int g_notification_display_buffer; /* @0x20004988 */
extern volatile unsigned int g_200049b8; /* @0x200049b8 */
extern unsigned char g_ipc_or_evt_ctx[]; /* @0x20004bb8 */
extern volatile unsigned int g_20004bbc; /* @0x20004bbc */
extern volatile unsigned int g_20004bbd; /* @0x20004bbd */
extern volatile unsigned int g_20004bbe; /* @0x20004bbe */
extern volatile unsigned int g_20004bc6; /* @0x20004bc6 */
extern volatile unsigned int g_20004bc8; /* @0x20004bc8 */
extern volatile unsigned int g_20004bcc; /* @0x20004bcc */
extern volatile unsigned int g_20004bcd; /* @0x20004bcd */
extern volatile unsigned int g_20004bd0; /* @0x20004bd0 */
extern volatile unsigned int g_20004bd8; /* @0x20004bd8 */
extern volatile unsigned int g_20004be0; /* @0x20004be0 */
extern volatile unsigned int g_20004be5; /* @0x20004be5 */
extern volatile unsigned int g_20004be8; /* @0x20004be8 */
extern volatile unsigned char g_onboarding_step_retry_cnt; /* @0x20004bf0 */
extern volatile unsigned int g_proxy_thread; /* @0x20004c08 */
extern volatile unsigned int g_some_k_timer; /* @0x20004ce0 */
extern volatile unsigned int g_display_thread; /* @0x20004d18 */
extern volatile unsigned int g_dashboard_startup_snapshot; /* @0x20004df0 */
extern volatile unsigned int g_dashboard_dwell_base_hi; /* @0x20004df4 */
extern volatile unsigned int g_sync_baseline_timestamp; /* @0x20004df8 */
extern volatile unsigned int g_dashboard_dwell_start_ts_hi; /* @0x20004dfc */
extern volatile unsigned int log_process_timestamp; /* @0x200056a0 */
extern volatile unsigned int g_200056a8; /* @0x200056a8 */
extern volatile unsigned int smp_work_queue; /* @0x20005bb8 */
extern volatile unsigned int g_active_transfer_conn; /* @0x20005cb0 */
extern volatile unsigned int g_sys_work_q; /* @0x20005d38 */
extern volatile unsigned int rx_thread_data; /* @0x20005e30 */
extern volatile unsigned int bt_workqueue; /* @0x20005f08 */
extern volatile unsigned int g_hmac_prng_ctx; /* @0x20006000 */
extern volatile unsigned int g_ble_conn_pool; /* @0x20006138 */
extern volatile unsigned int g_ble_conn_ext_signal_buf; /* @0x20006170 */
extern volatile int g_ble_conn_pool_enabled; /* @0x20006208 */
extern volatile unsigned int g_l2cap_fixed_chan_ctx; /* @0x20006210 */
extern volatile unsigned int g_bt_gatt_sc_cfg; /* @0x20006328 */
extern volatile unsigned int g_bt_gatt_sc_cfg_addr; /* @0x20006329 */
extern volatile unsigned int g_bt_gatt_sc_cfg0_flags; /* @0x20006330 */
extern volatile unsigned int g_bt_gatt_sc_cfg1_flags; /* @0x2000633c */
extern volatile unsigned int g_bt_gatt_sc_cfg2_flags; /* @0x20006348 */
extern volatile unsigned int g_bt_gatt_delayed_store_work; /* @0x20006350 */
extern volatile unsigned int g_bt_gatt_db_hash; /* @0x20006380 */
extern volatile unsigned int g_20006390; /* @0x20006390 */
extern volatile unsigned int g_bt_gatt_db_hash_work; /* @0x200063a0 */
extern volatile unsigned int g_bt_gatt_db_hash_work_63d0; /* @0x200063d0 */
extern volatile unsigned int g_service_changed_range; /* @0x200063f8 */
extern volatile unsigned int g_bt_gatt_sc_work; /* @0x20006418 */
extern volatile unsigned int g_bt_gatt_flags; /* @0x20006448 */
extern volatile unsigned int g_misc_kobj_6454; /* @0x20006454 */
extern volatile unsigned int g_20006690; /* @0x20006690 */
extern volatile unsigned int g_rtc_cycle_range_minmax; /* @0x200066b8 */
extern volatile unsigned int g_uptime_ref_tick_hi; /* @0x200066bc */
extern volatile unsigned int g_caf_power_manager_timer; /* @0x200066f0 */
extern volatile unsigned int g_audio_module_spinlock; /* @0x200068d0 */
extern volatile unsigned int g_curr_tick_lo; /* @0x200069e0 */
extern volatile unsigned int g_curr_tick_hi; /* @0x200069e4 */
extern volatile unsigned int g_battery_percent; /* @0x200069e8 */
extern volatile unsigned int g_200069ec; /* @0x200069ec */
extern volatile unsigned int g_200069f0; /* @0x200069f0 */
extern volatile unsigned int g_200069f4; /* @0x200069f4 */
extern volatile unsigned int g_ambient_light_sensor_ready; /* @0x200069f8 */
extern volatile int device_info; /* @0x200069fc */
extern volatile int g_touch_key_irq_pending; /* @0x20006a00 */
extern volatile unsigned int g_button_irq_cb2; /* @0x20006a04 */
extern volatile unsigned int g_button_irq_cb2_handler; /* @0x20006a08 */
extern volatile unsigned int g_button_irq_cb1; /* @0x20006a10 */
extern volatile unsigned int g_button_irq_cb1_handler; /* @0x20006a14 */
extern volatile unsigned int g_settings_notify_mutex; /* @0x20006a1c */
extern volatile unsigned long g_ble_conn_ctx_ptr; /* @0x20006a30 */
extern volatile signed int g_ancs_security_fail_cnt; /* @0x20006a34 */
extern volatile unsigned int g_uid_pipe; /* @0x20006a38 */
extern volatile unsigned int g_ancs_msgq; /* @0x20006a6c */
extern volatile unsigned int g_ancs_notif_attr_id_latest; /* @0x20006aa0 */
extern volatile unsigned int g_ancs_notif_evt_id_latest; /* @0x20006aac */
extern volatile unsigned char g_20006ab2; /* @0x20006ab2 */
extern volatile unsigned int g_gatt_discovery_flags; /* @0x20006ab4 */
extern volatile unsigned long g_ancs_active_conn; /* @0x20006ab8 */
extern volatile unsigned int g_ancs_discover_params; /* @0x20006abc */
extern volatile unsigned int g_ancs_client; /* @0x20006ae8 */
extern volatile unsigned int g_bonded_count; /* @0x20007514 */
extern volatile unsigned int g_ancs_conn; /* @0x20007518 */
extern volatile unsigned int g_debug_msg_pipe; /* @0x2000751c */
extern volatile unsigned int g_ring_log_pending; /* @0x20007550 */
extern volatile int g_log_use_alt_sink; /* @0x20007554 */
extern volatile unsigned int g_dmic_send_fail_cnt; /* @0x20007558 */
extern volatile int g_dmic_send_pos_cnt; /* @0x2000755c */
extern volatile int g_dmic_send_hundreds_cnt; /* @0x20007560 */
extern volatile unsigned int g_20007564; /* @0x20007564 */
extern volatile unsigned int g_20007568; /* @0x20007568 */
extern volatile unsigned int g_dashboard_lock_sent_flags; /* @0x2000756c */
extern volatile unsigned int g_dashboard_lock_ready_flags; /* @0x20007570 */
extern volatile unsigned int g_ble_work_queue; /* @0x20007574 */
extern volatile unsigned int g_crc32_table; /* @0x200075a0 */
extern volatile unsigned int g_file_msg_pipe; /* @0x200079a0 */
extern volatile unsigned int g_200079c4; /* @0x200079c4 */
extern volatile unsigned int g_font_total_size; /* @0x200079d4 */
extern volatile unsigned int g_font_buf_len; /* @0x200079d8 */
extern volatile unsigned int g_font_flash_write_offset; /* @0x200079dc */
extern volatile unsigned int g_font_crc32; /* @0x200079e0 */
extern volatile unsigned int g_app_language_msgq; /* @0x200079e4 */
extern volatile unsigned int g_box_mailbox_synced_flag; /* @0x200079fc */
extern volatile unsigned int g_20007a00; /* @0x20007a00 */
extern volatile unsigned int g_20007a04; /* @0x20007a04 */
extern volatile unsigned int g_box_last_seen_uptime; /* @0x20007a10 */
extern volatile unsigned int g_st25dv_mailbox_msg; /* @0x20007a14 */
extern volatile unsigned int g_box_field_timer; /* @0x20007a24 */
extern volatile unsigned int g_elapsed_time_mark; /* @0x20007a28 */
extern volatile unsigned int g_box_field_timer_cfg_buf; /* @0x20007a2c */
extern volatile unsigned int g_box_field_raw_timestamp; /* @0x20007a34 */
extern volatile unsigned int g_st25dv_dev; /* @0x20007a44 */
extern volatile unsigned int g_st25dv_i2c_cfg; /* @0x20007a48 */
extern volatile unsigned int g_eeprom_comm_mutex; /* @0x20007a60 */
extern volatile unsigned int g_ipc_send_fail_cnt; /* @0x20007a74 */
extern volatile unsigned int g_serialization_ipc_ept; /* @0x20007a78 */
extern volatile int g_serialization_ipc_ready; /* @0x20007a80 */
extern volatile int g_ipc0_endpoint; /* @0x20007a84 */
extern volatile unsigned int g_20007a88; /* @0x20007a88 */
extern volatile unsigned int g_20007a8c; /* @0x20007a8c */
extern volatile unsigned int g_20007a90; /* @0x20007a90 */
extern volatile unsigned int g_20007a94; /* @0x20007a94 */
extern volatile int g_panel_calib_last_param84; /* @0x20007a98 */
extern volatile int g_level_calc_input_sl_cache; /* @0x20007a9c */
extern volatile unsigned int g_dashboard_reset_pending_flags; /* @0x20007aa0 */
extern volatile unsigned int g_dashboard_lock_pending_flag; /* @0x20007aa4 */
extern volatile unsigned int g_app_switch_pending_flag; /* @0x20007aa8 */
extern volatile unsigned int g_ble_switch_status_reason; /* @0x20007aac */
extern volatile unsigned int g_20007ab0; /* @0x20007ab0 */
extern volatile unsigned int g_20007ab1; /* @0x20007ab1 */
extern volatile unsigned int g_20007ab4; /* @0x20007ab4 */
extern volatile unsigned int g_20007ab8; /* @0x20007ab8 */
extern volatile unsigned int g_20007abc; /* @0x20007abc */
extern volatile unsigned int g_20007ac0; /* @0x20007ac0 */
extern volatile unsigned int g_20007ac4; /* @0x20007ac4 */
extern volatile unsigned int g_20007ac8; /* @0x20007ac8 */
extern volatile unsigned int g_20007acc; /* @0x20007acc */
extern volatile unsigned int g_20007ad0; /* @0x20007ad0 */
extern volatile unsigned int g_20007ad4; /* @0x20007ad4 */
extern volatile unsigned int g_20007ad8; /* @0x20007ad8 */
extern volatile unsigned int g_20007adc; /* @0x20007adc */
extern volatile unsigned int g_20007ae0; /* @0x20007ae0 */
extern volatile unsigned int g_20007ae4; /* @0x20007ae4 */
extern volatile unsigned int g_20007ae8; /* @0x20007ae8 */
extern volatile unsigned int g_20007aec; /* @0x20007aec */
extern volatile unsigned int g_sw0_irq_low_cnt; /* @0x20007af0 */
extern volatile signed int g_20007af4; /* @0x20007af4 */
extern volatile signed int g_20007af8; /* @0x20007af8 */
extern volatile signed int g_20007afc; /* @0x20007afc */
extern volatile unsigned int g_misc_dispatch_ctx; /* @0x20007b00 */
extern volatile int g_touch_key_reset_reason; /* @0x20007b18 */
extern volatile unsigned int g_some_module_sem; /* @0x20007b1c */
extern volatile unsigned int g_20007b38; /* @0x20007b38 */
extern volatile unsigned int g_ui_state_mutex; /* @0x20007b3c */
extern volatile unsigned int g_wdt_channel_id; /* @0x20007b50 */
extern volatile unsigned int g_ext_flash_mutex; /* @0x20007b54 */
extern volatile unsigned int g_ext_flash_dev; /* @0x20007b68 */
extern volatile unsigned int g_opt3007_dev; /* @0x20007b6c */
extern volatile unsigned int g_20007b70; /* @0x20007b70 */
extern volatile unsigned int g_20007b74; /* @0x20007b74 */
extern volatile int g_pending_event_word; /* @0x20007b78 */
extern volatile unsigned int g_dmic_msgq; /* @0x20007b7c */
extern volatile unsigned int g_atomic_scratch_20007bb0; /* @0x20007bb0 */
extern volatile unsigned int g_20007bb4; /* @0x20007bb4 */
extern volatile unsigned int g_20007bb8; /* @0x20007bb8 */
extern volatile unsigned int g_20007bbc; /* @0x20007bbc */
extern volatile unsigned int g_pt_nfc_link_cfg; /* @0x20007bc0 */
extern volatile int g_pt_nfc_link_attr_0x4414_cache; /* @0x20007bc4 */
extern volatile unsigned int g_pt_nfc_link_ready_flag; /* @0x20007bc8 */
extern volatile int g_pt_nfc_link_ready; /* @0x20007bcc */
extern volatile unsigned int g_20007bd4; /* @0x20007bd4 */
extern volatile int g_periodic_check_last_uptime_ms; /* @0x20007bf0 */
extern unsigned char g_esb_notify_ring_staging_buf[]; /* @0x20007bf4 */
extern volatile int g_ancs_notify_rx_buf; /* @0x20007da8 */
extern unsigned char g_message_pool[]; /* @0x20007dac */
extern volatile unsigned int g_notif_app_pkg_table_buf; /* @0x20007dbc */
extern unsigned char g_message_table_mirror[]; /* @0x20008eb4 */
extern unsigned char g_message_table_mirror_ovfl_slot[]; /* @0x20009e08 */
extern volatile unsigned int g_whitelist_app_parse_buf; /* @0x20009fbc */
extern volatile unsigned int g_misc_last_uptime_ms; /* @0x20009fc0 */
extern volatile int g_pixel4bit_bitpos; /* @0x20009fc4 */
extern volatile int g_pixel4bit_row_buf_off; /* @0x20009fc8 */
extern volatile int g_pixel4bit_row_buf; /* @0x20009fcc */
extern volatile unsigned int g_dashboard_reflash_frame_idx; /* @0x20009fd0 */
extern volatile signed int g_20009fd4; /* @0x20009fd4 */
extern volatile signed int g_even_ai_frame_idx; /* @0x20009fd8 */
extern volatile unsigned int g_20009fdc; /* @0x20009fdc */
extern volatile unsigned int g_20009fe0; /* @0x20009fe0 */
extern volatile unsigned int g_20009fe4; /* @0x20009fe4 */
extern volatile unsigned int g_20009fe8; /* @0x20009fe8 */
extern volatile unsigned int g_20009fec; /* @0x20009fec */
extern volatile unsigned int g_20009ff0; /* @0x20009ff0 */
extern volatile unsigned int g_20009ff4; /* @0x20009ff4 */
extern volatile unsigned int g_imu_pitch_render_state0; /* @0x2000a018 */
extern volatile unsigned int g_imu_pitch_render_state1; /* @0x2000a01c */
extern volatile unsigned int g_imu_pitch_render_state2; /* @0x2000a020 */
extern volatile unsigned int g_imu_pitch_render_state3; /* @0x2000a024 */
extern volatile unsigned int g_imu_pitch_render_state4; /* @0x2000a028 */
extern volatile unsigned int g_imu_pitch_render_state5; /* @0x2000a02c */
extern volatile unsigned int g_gui_canvas_flags; /* @0x2000a030 */
extern volatile int g_gui_active_canvas; /* @0x2000a034 */
extern volatile unsigned int g_even_ai_render_state; /* @0x2000a038 */
extern volatile unsigned int g_panel_reg_y_cache; /* @0x2000a058 */
extern volatile unsigned int g_panel_reg_x_cache; /* @0x2000a05c */
extern volatile unsigned int g_projector_bus_lock; /* @0x2000a060 */
extern volatile unsigned int g_panel_spi_id; /* @0x2000a074 */
extern volatile unsigned int g_2000a078; /* @0x2000a078 */
extern volatile unsigned int g_2000a07c; /* @0x2000a07c */
extern volatile unsigned int g_2000a080; /* @0x2000a080 */
extern volatile unsigned int g_2000a084; /* @0x2000a084 */
extern volatile unsigned int g_2000a088; /* @0x2000a088 */
extern volatile unsigned int g_2000a08c; /* @0x2000a08c */
extern volatile int g_proxy_thread_id; /* @0x2000a090 */
extern volatile unsigned int g_delayexitvalue; /* @0x2000a094 */
extern volatile signed int g_2000a098; /* @0x2000a098 */
extern volatile unsigned int g_display_thread_id; /* @0x2000a09c */
extern volatile unsigned int g_progress_tick_ms; /* @0x2000a0a0 */
extern volatile int g_boot_uptime_s; /* @0x2000a0b0 */
extern volatile unsigned int g_analytics_evt_tick_buf; /* @0x2000a0b4 */
extern volatile unsigned int g_2000a0c8; /* @0x2000a0c8 */
extern volatile unsigned int g_log_msg_pool_ptr; /* @0x2000a0cc */
extern volatile unsigned long g_2000a0d0; /* @0x2000a0d0 */
extern volatile signed int log_backend_count; /* @0x2000a0d4 */
extern volatile signed int log_buffered_cnt; /* @0x2000a0d8 */
extern volatile unsigned int z_log_process_guard; /* @0x2000a0dc */
extern volatile unsigned int g_2000a0e0; /* @0x2000a0e0 */
extern volatile unsigned int g_2000a0e4; /* @0x2000a0e4 */
extern volatile unsigned int g_settings_nvs_backend; /* @0x2000a100 */
extern volatile unsigned int g_settings_stores; /* @0x2000a104 */
extern volatile unsigned int g_settings_handlers; /* @0x2000a10c */
extern volatile unsigned int g_settings_nvs_default_backend; /* @0x2000a114 */
extern volatile unsigned int cur_service_val; /* @0x2000a154 */
extern volatile unsigned int g_gatt_dm_context; /* @0x2000a158 */
extern volatile unsigned int g_gatt_dm_discover_params_uuid; /* @0x2000a15c */
extern volatile unsigned int g_gatt_dm_discover_params_func; /* @0x2000a160 */
extern volatile unsigned short g_gatt_dm_discover_params_start_handle; /* @0x2000a164 */
extern volatile unsigned short g_gatt_dm_discover_params_end_handle; /* @0x2000a16a */
extern volatile unsigned char g_gatt_dm_discover_params_type; /* @0x2000a16c */
extern volatile unsigned int g_gatt_dm_attr_count; /* @0x2000a288 */
extern volatile unsigned int g_gatt_dm_in_progress_flag; /* @0x2000a28c */
extern volatile unsigned int g_gatt_dm_svc_uuid_buf; /* @0x2000a290 */
extern volatile unsigned int g_gatt_dm_chunk_list_head; /* @0x2000a2a4 */
extern volatile unsigned int g_gatt_dm_chunk_list_tail; /* @0x2000a2a8 */
extern volatile unsigned int g_gatt_dm_chunk_used_len; /* @0x2000a2ac */
extern volatile unsigned long g_gatt_dm_svc_range_end; /* @0x2000a2b0 */
extern volatile unsigned char g_gatt_dm_has_uuid_flag; /* @0x2000a2b4 */
extern volatile unsigned int g_2000a2b8; /* @0x2000a2b8 */
extern volatile unsigned int g_notify_pending_lock; /* @0x2000a2c4 */
extern volatile unsigned int g_notify_pending_slist; /* @0x2000a2c8 */
extern volatile unsigned int g_notify_pending_flags_bitmap; /* @0x2000a2d0 */
extern volatile unsigned int g_arm_mpu_dynamic_regions_tbl; /* @0x2000a7f4 */
extern volatile unsigned int g_heap_brk; /* @0x2000a808 */
extern volatile unsigned int g_mgmt_group_list_head; /* @0x2000a94c */
extern volatile unsigned int g_img_mgmt_flash_area; /* @0x2000a954 */
extern volatile unsigned char g_img_mgmt_active_slot; /* @0x2000ab7c */
extern unsigned char img_mgmt_state[]; /* @0x2000ab80 */
extern volatile unsigned char g_img_mgmt_flash_area_align; /* @0x2000ab88 */
extern volatile unsigned int g_misc_kobj_abac; /* @0x2000abac */
extern volatile unsigned int bt_hci_cmd_data; /* @0x2000abf4 */
extern volatile int ready_cb; /* @0x2000ac6c */
extern volatile int g_bt_dh_key_cb; /* @0x2000ac70 */
extern volatile unsigned int g_bt_pub_key_cb_slist; /* @0x2000ac74 */
extern volatile unsigned int g_bt_conn_pool; /* @0x2000ac7c */
extern volatile int g_ble_conn_cb_list_head; /* @0x2000ad1c */
extern volatile int g_bt_conn_auth_info_cb_list; /* @0x2000ad20 */
extern volatile int auth_info_cbs; /* @0x2000ad24 */
extern volatile int g_bt_conn_auth_cb; /* @0x2000ad28 */
extern volatile unsigned int g_2000ad2c; /* @0x2000ad2c */
extern volatile unsigned int l2cap_tx_meta_data_storage; /* @0x2000ad34 */
extern volatile unsigned int g_bt_gatt_indicate_ctx_pool; /* @0x2000add4 */
extern volatile int att_handle_rsp_thread; /* @0x2000ae9c */
extern volatile unsigned int cancel_req; /* @0x2000aea0 */
extern volatile unsigned int g_bt_gatt_cf_cfg; /* @0x2000aed4 */
extern volatile unsigned int g_2000aed5; /* @0x2000aed5 */
extern volatile unsigned int gatt_service_init_guard; /* @0x2000af04 */
extern volatile int g_bt_gatt_dynamic_db; /* @0x2000af08 */
extern volatile unsigned int g_2000af0c; /* @0x2000af0c */
extern volatile unsigned int g_bt_gatt_callback_list_head; /* @0x2000af10 */
extern volatile unsigned int g_2000af14; /* @0x2000af14 */
extern volatile unsigned int g_known_device_table; /* @0x2000af18 */
extern volatile unsigned int g_known_device_table_addr0; /* @0x2000af19 */
extern volatile unsigned int g_smp_local_public_key; /* @0x2000af48 */
extern volatile unsigned char bt_keys_pool; /* @0x2000af4c */
extern volatile unsigned int g_bt_keys_pool_entry0_addr; /* @0x2000af4d */
extern volatile unsigned int bt_keys_pool_0_irk; /* @0x2000af76 */
extern volatile unsigned int bt_keys_pool_1; /* @0x2000afa8 */
extern volatile unsigned int g_bt_keys_pool_entry1_addr; /* @0x2000afa9 */
extern volatile unsigned int bt_keys_pool_1_irk; /* @0x2000afd2 */
extern volatile unsigned int bt_keys_pool_1_addr; /* @0x2000afe2 */
extern volatile unsigned int g_net_buf_slist_lock; /* @0x2000b004 */
extern volatile unsigned int g_pdm_mic_ctrl_blk; /* @0x2000b008 */
extern volatile unsigned int g_pdm_mic_rx_msgq; /* @0x2000b024 */
extern volatile unsigned int g_2000b084; /* @0x2000b084 */
extern volatile unsigned int g_2000b094; /* @0x2000b094 */
extern volatile unsigned int g_2000b0b8; /* @0x2000b0b8 */
extern volatile unsigned int g_2000b154; /* @0x2000b154 */
extern volatile unsigned int g_gpio_pin_latch_mask; /* @0x2000b2d0 */
extern volatile unsigned int nrf_rtc_timer_free_channels; /* @0x2000b2d4 */
extern volatile unsigned int g_gpio_pin_enabled_mask; /* @0x2000b2d8 */
extern volatile unsigned int g_uptime_tick_overflow_state; /* @0x2000b2dc */
extern volatile unsigned int g_ancs_notify_slot_table; /* @0x2000b308 */
extern volatile unsigned int g_caf_power_manager_wake_evt_cnt; /* @0x2000b310 */
extern volatile unsigned int g_2000b314; /* @0x2000b314 */
extern volatile unsigned int g_clock_cb; /* @0x2000b31c */
extern volatile unsigned char nrfx_clock_module_initialized; /* @0x2000b320 */
extern volatile int g_nrfx_hal_init_flag; /* @0x2000b324 */
extern volatile unsigned char g_nrfx_gpiote_init_flag; /* @0x2000b328 */
extern volatile int g_nrfx_gpiote_init_ctx; /* @0x2000b32c */
extern volatile unsigned int g_pdm_cb; /* @0x2000b330 */
extern volatile unsigned char nrfx_pdm_drv_state; /* @0x2000b340 */
extern volatile unsigned char nrfx_pdm_state; /* @0x2000b341 */
extern volatile int g_qspi_cb; /* @0x2000b348 */
extern volatile unsigned char g_qspi_drv_state; /* @0x2000b378 */
extern volatile unsigned char g_qspi_skip_activate_flag; /* @0x2000b380 */
extern volatile unsigned int g_nrfx_spim_cb; /* @0x2000b384 */
extern volatile unsigned int g_nrfx_twim_cb; /* @0x2000b3cc */
extern volatile unsigned int m_dppi_channels; /* @0x2000b41c */
extern volatile unsigned int g_metal_generic_bus; /* @0x2000b424 */
extern volatile unsigned int metal_log_handler; /* @0x2000b428 */
struct z_kernel; extern struct z_kernel _kernel; /* @0x2000b448 */
extern volatile unsigned int g_current_thread_ptr; /* @0x2000b450 */
extern volatile unsigned char g_spinlock_validate_owner; /* @0x2000b458 */
extern volatile unsigned int g_sched_ready_runq; /* @0x2000b464 */
extern volatile unsigned int mutex_spinlock_b470; /* @0x2000b470 */
extern volatile unsigned int g_mutex_lock_spinlock; /* @0x2000b474 */
extern volatile unsigned int g_2000b478; /* @0x2000b478 */
extern volatile unsigned int timer_spinlock; /* @0x2000b480 */
extern volatile int g_pend_locked_thread_tmp; /* @0x2000b484 */
extern volatile int g_sched_ready_runq_prio_cache; /* @0x2000b488 */
extern volatile int g_sched_ready_runq_nonempty_flag; /* @0x2000b48c */
extern volatile unsigned int sched_spinlock; /* @0x2000b490 */
extern volatile unsigned int g_rtc_elapsed_calc_disabled_flag; /* @0x2000b494 */
extern volatile unsigned int g_timeout_list_spinlock; /* @0x2000b498 */
extern volatile unsigned int poll_spinlock; /* @0x2000b4a0 */
extern volatile unsigned int g_batt_soc_curve_interp_buf; /* @0x2000b4a4 */
extern volatile unsigned int g_batt_soc_curve_val_hi; /* @0x2000b4ec */
extern volatile unsigned int g_batt_soc_curve_val_lo; /* @0x2000b4f0 */
extern volatile unsigned int g_malloc_sbrk_start; /* @0x2000cc1c */
extern volatile unsigned int g_malloc_free_list; /* @0x2000cc20 */
extern volatile int g_errno; /* @0x2000cc24 */
extern volatile unsigned int g_pkcs7_rx_msg_id; /* @0x2000d6f0 */
extern volatile unsigned int g_pkcs7_rx_offset; /* @0x2000d6f2 */
extern volatile unsigned int g_pkcs7_pack_offset; /* @0x2000d6f4 */
extern volatile unsigned int g_2000d716; /* @0x2000d716 */
extern volatile unsigned int g_2000f6e4; /* @0x2000f6e4 */
extern volatile unsigned short g_esb_sync_last_result; /* @0x2000f6e6 */
extern volatile unsigned int g_2000f6ec; /* @0x2000f6ec */
extern volatile unsigned short g_gui_dynbmp_cycle_count; /* @0x2000f6fe */
extern volatile unsigned short g_gui_dynbmp_frame_index; /* @0x2000f700 */
extern volatile unsigned short g_gui_dynbmp_frame_limit; /* @0x2000f702 */
extern volatile unsigned int g_utf16_conv_buf; /* @0x2000f704 */
extern volatile unsigned int g_2000ff04; /* @0x2000ff04 */
extern volatile unsigned short g_bt_hci_pending_opcode; /* @0x2000ff06 */
extern volatile unsigned int g_bt_hci_acl_frag_conn_handle; /* @0x2000ff08 */
extern volatile unsigned int sc_range; /* @0x2000ff14 */
extern volatile unsigned int sc_cfg; /* @0x2000ff18 */
extern volatile unsigned int g_bt_gatt_sc_cfg_addr_ff19; /* @0x2000ff19 */
extern volatile unsigned short last_static_handle; /* @0x2000ff3c */
extern volatile unsigned int g_change_work_mode_busy; /* @0x2000ff4b */
extern volatile unsigned int g_notify_wakeup_msg_sync_flag; /* @0x2000ff4d */
extern volatile unsigned int g_2000ff4e; /* @0x2000ff4e */
extern volatile unsigned char g_runtime_mode_flag; /* @0x2000ff6e */
extern volatile unsigned char g_ble_indicate_sc_retry_count; /* @0x2000ff70 */
extern volatile unsigned int g_ancs_attr_data_pending; /* @0x2000ff71 */
extern volatile unsigned int g_2000ff72; /* @0x2000ff72 */
extern volatile unsigned int g_2000ff73; /* @0x2000ff73 */
extern volatile unsigned int g_2000ff87; /* @0x2000ff87 */
extern volatile unsigned int g_2000ffa7; /* @0x2000ffa7 */
extern unsigned char g_debug_msg_scratch_buf[]; /* @0x20010257 */
extern volatile unsigned int g_pkcs7_rx_cmd_id; /* @0x2001031f */
extern volatile unsigned int g_pkcs7_pack_cmd_id; /* @0x20010320 */
extern volatile unsigned int g_dmic_msg_seq; /* @0x20010321 */
extern volatile unsigned int g_20010322; /* @0x20010322 */
extern volatile unsigned char g_20010323; /* @0x20010323 */
extern volatile unsigned char g_20010324; /* @0x20010324 */
extern volatile unsigned int g_20010325; /* @0x20010325 */
extern volatile unsigned char g_20010326; /* @0x20010326 */
extern volatile unsigned int g_2001046a; /* @0x2001046a */
extern volatile unsigned int g_200107e3; /* @0x200107e3 */
extern volatile unsigned int g_2001197a; /* @0x2001197a */
extern volatile unsigned int g_200119ba; /* @0x200119ba */
extern volatile unsigned int g_200119da; /* @0x200119da */
extern volatile unsigned int g_20011d81; /* @0x20011d81 */
extern volatile unsigned int g_20011d82; /* @0x20011d82 */
extern volatile unsigned int g_20013dea; /* @0x20013dea */
extern volatile unsigned int g_20015e52; /* @0x20015e52 */
extern volatile unsigned int g_font_write_buf; /* @0x20017062 */
extern volatile unsigned char g_ui_mode_flag; /* @0x20018462 */
extern volatile unsigned int g_20018463; /* @0x20018463 */
extern unsigned char g_quicknote_flash_page_buf[]; /* @0x20018465 */
extern volatile unsigned int g_20018c65; /* @0x20018c65 */
extern volatile unsigned int g_20018c66; /* @0x20018c66 */
extern volatile unsigned int g_box_present_flag; /* @0x20018c68 */
extern volatile unsigned char g_board_rev_flag; /* @0x20018c69 */
extern volatile unsigned char g_ndef_build_status_flag; /* @0x20018c6a */
extern volatile unsigned char g_level_calc_input_b_cache; /* @0x20018c6b */
extern volatile unsigned int g_20018c6c; /* @0x20018c6c */
extern volatile unsigned int g_20018c6d; /* @0x20018c6d */
extern volatile unsigned int g_20018c6e; /* @0x20018c6e */
extern volatile unsigned char g_esb_seg_tx_frame_opcode; /* @0x20018c6f */
extern volatile unsigned int g_esb_seg_tx_frame_payload; /* @0x20018c71 */
extern volatile unsigned int g_esb_seg_ack_echo_buf; /* @0x20018d6b */
extern volatile unsigned char g_esb_notify_sync_retry_cnt; /* @0x20018d82 */
extern volatile unsigned int g_bind_status_log_debounce_cnt; /* @0x20018d83 */
extern volatile unsigned int g_box_state_debounce_cnt; /* @0x20018d84 */
extern volatile unsigned int g_glassbox_status_debounce_cnt; /* @0x20018d85 */
extern volatile unsigned int g_nfc_link_retry_cnt; /* @0x20018d86 */
extern volatile unsigned int g_wear_state_debounce_cnt; /* @0x20018d87 */
extern volatile unsigned char g_misc_dispatch_pending_flag; /* @0x20018d88 */
extern volatile unsigned char g_touch_key_press_active; /* @0x20018d89 */
extern volatile unsigned char g_some_module_init_done_flag; /* @0x20018d8a */
extern volatile unsigned char g_suspend_pending_flag; /* @0x20018d8b */
extern volatile unsigned int g_esb_seg_tx_lock_flag; /* @0x20018d8c */
extern volatile unsigned int g_new_notification_pending_flag; /* @0x20018d8d */
extern volatile unsigned char g_msg_queue_busy; /* @0x20018d8e */
extern volatile unsigned char g_esb_sync_tx_busy_flag; /* @0x20018d8f */
extern volatile unsigned char g_flash_crc_skip_watchdog_flag; /* @0x20018d90 */
extern volatile unsigned char g_box_lid_or_charge_state; /* @0x20018d91 */
extern volatile unsigned int g_wear_off_confirm_cnt; /* @0x20018d92 */
extern volatile unsigned int onboarding_pending_flag; /* @0x20018d93 */
extern volatile unsigned char g_low_power_mode_enabled; /* @0x20018d94 */
extern volatile unsigned char g_20018d95; /* @0x20018d95 */
extern volatile unsigned char g_20018d96; /* @0x20018d96 */
extern volatile unsigned int g_notify_wakeup_delay_flag; /* @0x20018d97 */
extern volatile unsigned char g_esb_notify_sync_substate; /* @0x20018d98 */
extern volatile unsigned char g_ble_xfer_seq_prev; /* @0x20018d99 */
extern volatile unsigned char g_ble_xfer_seq_cur; /* @0x20018d9a */
extern volatile unsigned char g_ble_dispatch_pending_marker; /* @0x20018d9b */
extern volatile unsigned char g_persist_task_status_lock; /* @0x20018d9c */
extern volatile unsigned char g_persist_task_status; /* @0x20018d9d */
extern volatile unsigned char g_pending_message_flag; /* @0x20018d9e */
extern volatile unsigned char g_esb_notify_slave_role_guard; /* @0x20018d9f */
extern volatile unsigned int g_battery_level_bucket; /* @0x20018da0 */
extern volatile unsigned char g_opt3007_chip_ready; /* @0x20018da1 */
extern volatile unsigned int g_20018da2; /* @0x20018da2 */
extern volatile unsigned char g_confirmed_state_flag_2; /* @0x20018da3 */
extern volatile unsigned char g_confirmed_state_flag_1; /* @0x20018da4 */
extern volatile unsigned int g_ancs_inbox_flag_cached; /* @0x20018da5 */
extern volatile unsigned char g_ancs_inbox_flag_current; /* @0x20018da6 */
extern volatile unsigned char g_lid_closed_flag; /* @0x20018da7 */
extern volatile unsigned char g_charging_flag; /* @0x20018da8 */
extern volatile unsigned char g_20018da9; /* @0x20018da9 */
extern volatile unsigned int g_voice_block_dir_buf; /* @0x20018daa */
extern volatile unsigned int g_20019daa; /* @0x20019daa */
extern volatile unsigned int g_audio_stream_mgr_busy_flag; /* @0x20019dab */
extern volatile unsigned char g_touch_key_irq_line_status; /* @0x20019dac */
extern volatile unsigned char g_pt_nfc_link_busy; /* @0x20019dad */
extern volatile unsigned char g_fuel_gauge_poll_stop_flag; /* @0x20019dae */
extern volatile unsigned int g_flash_info; /* @0x20019daf */
extern volatile unsigned char g_periodic_check_fail_cnt; /* @0x20019ef0 */
extern volatile unsigned int g_aging_mode_thread_started_flag; /* @0x20019ef1 */
extern volatile unsigned char g_click_dispatch_flag; /* @0x20019ef2 */
extern volatile unsigned char g_test_mode_flag; /* @0x20019ef3 */
extern volatile unsigned char g_glassbox_charge_status_byte; /* @0x20019ef4 */
extern volatile unsigned int g_pt_msg_encode_buf; /* @0x20019ef5 */
extern volatile unsigned int g_system_19ff5; /* @0x20019ff5 */
extern volatile unsigned int g_pt_status_msg_buf; /* @0x2001a0f5 */
extern volatile unsigned int g_serial_port_ready; /* @0x2001a127 */
extern volatile unsigned char g_uart_rx_frame_len; /* @0x2001a128 */
extern unsigned char g_uart_rx_frame_buf[]; /* @0x2001a129 */
extern volatile unsigned int g_2001a12d; /* @0x2001a12d */
extern volatile unsigned char g_message_pending_state; /* @0x2001a229 */
extern volatile unsigned char g_message_pool_index; /* @0x2001a22a */
extern volatile unsigned char g_message_table_slot_count; /* @0x2001a22b */
extern unsigned char g_app_whitelist_buffer[]; /* @0x2001a22c */
extern volatile unsigned char g_on_whitelist_by_identifier; /* @0x2001a22d */
extern volatile unsigned char g_new_message_pending_flag; /* @0x2001b80e */
extern volatile unsigned char g_dashboard_close_pending; /* @0x2001b80f */
extern volatile unsigned char g_display_page_index; /* @0x2001b810 */
extern volatile unsigned char g_display_page_dirty_flag; /* @0x2001b811 */
extern volatile unsigned char g_2001b812; /* @0x2001b812 */
extern volatile unsigned char g_2001b813; /* @0x2001b813 */
extern volatile unsigned char g_news_widget_index_raw; /* @0x2001b814 */
extern volatile unsigned char g_stocks_widget_index_raw; /* @0x2001b815 */
extern volatile unsigned char g_widget0_index_raw; /* @0x2001b816 */
extern volatile unsigned char g_quicknote_hint_shown; /* @0x2001b817 */
extern volatile unsigned int g_even_ai_line_text_buf; /* @0x2001b818 */
extern volatile unsigned int g_even_ai_active_flag; /* @0x2001b9a8 */
extern volatile unsigned char g_not_disturb_settings; /* @0x2001b9aa */
extern volatile unsigned char g_even_ai_mic_icon_visible; /* @0x2001b9ab */
extern unsigned char g_buf_2001b9ac[]; /* @0x2001b9ac */
extern volatile unsigned int g_2001ba2c; /* @0x2001ba2c */
extern volatile unsigned char g_2001ba2d; /* @0x2001ba2d */
extern unsigned char g_buf_2001ba2e[]; /* @0x2001ba2e */
extern volatile unsigned int g_2001c336; /* @0x2001c336 */
extern volatile unsigned int g_2001cc3e; /* @0x2001cc3e */
extern volatile char onboarding_secondary_reset_flag; /* @0x2001cdce */
extern volatile unsigned char g_onboarding_primary_reset_flag; /* @0x2001cdcf */
extern volatile unsigned int g_2001cdd0; /* @0x2001cdd0 */
extern volatile char onboarding_retry_counter; /* @0x2001cdd1 */
extern volatile unsigned char onboarding_attempt_counter; /* @0x2001cdd2 */
extern volatile unsigned char onboarding_watchdog_active_flag; /* @0x2001cdd3 */
extern volatile char g_gui_dark_light_flag; /* @0x2001cdd4 */
extern volatile unsigned int g_even_ai_render_state_init_val; /* @0x2001cdd7 */
extern volatile unsigned int g_glyph_bitmap_cache_buf; /* @0x2001ce57 */
extern volatile unsigned int g_imu_pitch_task_state; /* @0x2001cf8f */
extern volatile unsigned int g_imu_pitch_last_state; /* @0x2001cf91 */
extern volatile unsigned int g_chinese_glyph_bitmap_buf; /* @0x2001cf92 */
extern unsigned char g_icon_bitmap_buf[]; /* @0x2001d142 */
extern volatile unsigned int g_2001d262; /* @0x2001d262 */
extern volatile unsigned int g_2001d263; /* @0x2001d263 */
extern volatile unsigned int g_2001d264; /* @0x2001d264 */
extern volatile unsigned int g_2001d26a; /* @0x2001d26a */
extern volatile unsigned int g_2001d26e; /* @0x2001d26e */
extern volatile unsigned int g_2001d34a; /* @0x2001d34a */
extern volatile unsigned int g_2001d34b; /* @0x2001d34b */
extern volatile unsigned int g_2001d431; /* @0x2001d431 */
extern volatile unsigned int g_2001d432; /* @0x2001d432 */
extern volatile unsigned char g_display_reflash_pending; /* @0x2001d446 */
extern volatile unsigned short g_2001d447; /* @0x2001d447 */
extern volatile unsigned int g_analytics_evt_hist_ready; /* @0x2001d449 */
extern volatile unsigned int g_analytics_evt_buf_idx; /* @0x2001d44a */
extern volatile unsigned char log_process_active; /* @0x2001d44b */
extern volatile unsigned char g_log_initialized_flag; /* @0x2001d44c */
extern volatile unsigned char log_output_flush_done; /* @0x2001d44e */
extern volatile unsigned int g_arm_mpu_static_regions_num; /* @0x2001d450 */
extern volatile unsigned char g_smp_pairing_event_cnt; /* @0x2001d531 */
extern volatile unsigned char g_bt_settings_load_done; /* @0x2001d532 */
extern volatile unsigned char g_smp_pair_method_unbonded; /* @0x2001d533 */
extern volatile unsigned char g_smp_pair_method_bonded; /* @0x2001d534 */
extern volatile unsigned char g_qspi_nor_initialized; /* @0x2001d535 */
extern volatile unsigned char g_caf_power_manager_system_off_flag; /* @0x2001d563 */
extern volatile unsigned char g_tx_yield_allowed_flag; /* @0x2001d564 */
extern volatile unsigned int g_percpu_timeout_abort_flag; /* @0x2001d565 */
extern volatile unsigned int g_ancs_work_thread_stack; /* @0x2001d568 */
extern volatile unsigned int g_ble_work_thread_stack; /* @0x2001e968 */
extern volatile unsigned int g_imu_fusion_thread_stack; /* @0x20023568 */
extern volatile unsigned int g_flash_ops_thread_stack; /* @0x20021968 */
extern volatile unsigned int g_brightness_thread_stack; /* @0x20022168 */
extern volatile unsigned int g_20023c68; /* @0x20023c68 */
extern volatile unsigned int g_20024868; /* @0x20024868 */
extern volatile unsigned int g_20024c68; /* @0x20024c68 */
extern volatile unsigned int g_20025068; /* @0x20025068 */
extern volatile unsigned int g_20025468; /* @0x20025468 */
extern volatile unsigned int g_20025a68; /* @0x20025a68 */
extern volatile unsigned int g_20026268; /* @0x20026268 */
extern volatile unsigned int g_20026a68; /* @0x20026a68 */
extern volatile unsigned int g_aging_mode_aux_thread_stack; /* @0x20027668 */
extern volatile unsigned int g_aging_mode_thread_stack; /* @0x20027a68 */
extern volatile unsigned int g_proxy_thread_stack; /* @0x20028668 */
extern volatile unsigned int g_display_thread_stack_buf; /* @0x20028e68 */
extern volatile unsigned int rx_thread_stack; /* @0x2002bb80 */
extern volatile unsigned int bt_workqueue_stack; /* @0x2002bf80 */
extern volatile int g_dashboard_startup_mode_info_defaults; /* @0x2007fc00 */
extern volatile unsigned char g_all_static_info_fc04; /* @0x2007fc04 */
extern volatile unsigned char g_dashboard_startup_mode_info_field_05; /* @0x2007fc05 */
extern volatile int g_all_static_info_fc08; /* @0x2007fc08 */
extern volatile int g_all_static_info_fc0c; /* @0x2007fc0c */
extern volatile int g_all_static_info; /* @0x2007fc10 */
extern volatile int g_dashboard_startup_mode_info_field_14; /* @0x2007fc14 */
extern volatile int g_dashboard_startup_mode_info_field_18; /* @0x2007fc18 */
extern volatile int g_dashboard_startup_mode_info_field_1c; /* @0x2007fc1c */
extern volatile int g_all_static_info_fc35; /* @0x2007fc35 */
extern volatile int g_dashboard_startup_mode_info_field_39; /* @0x2007fc39 */
extern volatile unsigned char g_all_static_info_fc5f; /* @0x2007fc5f */
extern volatile unsigned char g_all_static_info_fc60; /* @0x2007fc60 */
extern volatile unsigned char g_dashboard_startup_mode_info_field_61; /* @0x2007fc61 */
extern volatile unsigned char g_all_static_info_fc62; /* @0x2007fc62 */
extern volatile unsigned char g_all_static_info_fc68; /* @0x2007fc68 */
extern volatile unsigned char g_dashboard_default_widget0_index; /* @0x2007fc69 */
extern volatile unsigned char g_2007fc70; /* @0x2007fc70 */

/* ---- rodata table externs (2598) ---- */
extern const unsigned char __settings_handler_static_list_start[]; /* @0x882b0 */
extern const unsigned char entropy_dev[]; /* @0x87b90 */
extern const unsigned char g_default_font_glyph_table_count[]; /* @0x8ac28 */
extern const unsigned char g_gpio0_dev[]; /* @0x87b60 */
extern const unsigned char g_gpio1_dev[]; /* @0x87b48 */
extern const unsigned char g_watchdog_device[]; /* @0x87cc8 */
extern const unsigned char lc3_attdet_nbytes_ranges[]; /* @0x884d0 */
extern const unsigned char lc3_bwdet_bws_table[]; /* @0x8bbe0 */
extern const unsigned char lc3_bwdet_l_table[]; /* @0x8bbc0 */
extern const unsigned char lc3_bwdet_thresholds[]; /* @0x884f0 */
extern const unsigned char lc3_energy_n1_table[]; /* @0x8bc60 */
extern const unsigned char lc3_sns_dct16_matrix[]; /* @0x8ce4c */
extern const unsigned char lc3_spec_iq_table[]; /* @0x8d350 */
extern const unsigned char lc3_tns_coeffs_models_row1[]; /* @0x8fea4 */
extern const unsigned char lc3_tns_coeffs_models_row2[]; /* @0x8fee8 */
extern const unsigned char lc3_tns_coeffs_models_row3[]; /* @0x8ff2c */
extern const unsigned char lc3_tns_coeffs_models_row4[]; /* @0x8ff70 */
extern const unsigned char lc3_tns_coeffs_models_row5[]; /* @0x8ffb4 */
extern const unsigned char lc3_tns_coeffs_models_row6[]; /* @0x8fff8 */
extern const unsigned char lc3_tns_coeffs_models_row7[]; /* @0x9003c */
extern const unsigned char lc3_tns_rc_levels[]; /* @0x98540 */
extern const unsigned char lc3_tns_rc_thresholds[]; /* @0x98564 */
extern const unsigned char lc3_tns_subdivision_table[]; /* @0x8853c */
extern const unsigned char log_module_bt_conn[]; /* @0x88108 */
extern const unsigned char rodata_10000[]; /* @0x10000 */
extern const unsigned char rodata_1253c[]; /* @0x1253c */
extern const unsigned char rodata_12540[]; /* @0x12540 */
extern const unsigned char rodata_12544[]; /* @0x12544 */
extern const unsigned char rodata_12548[]; /* @0x12548 */
extern const unsigned char rodata_1254c[]; /* @0x1254c */
extern const unsigned char rodata_12554[]; /* @0x12554 */
extern const unsigned char rodata_12558[]; /* @0x12558 */
extern const unsigned char rodata_1255c[]; /* @0x1255c */
extern const unsigned char rodata_1256c[]; /* @0x1256c */
extern const unsigned char rodata_1274f[]; /* @0x1274f */
extern const unsigned char rodata_162ed[]; /* @0x162ed */
extern const unsigned char rodata_16bf1[]; /* @0x16bf1 */
extern const unsigned char rodata_17819[]; /* @0x17819 */
extern const unsigned char rodata_1827d[]; /* @0x1827d */
extern const unsigned char rodata_18ef5[]; /* @0x18ef5 */
extern const unsigned char rodata_19ff1[]; /* @0x19ff1 */
extern const unsigned char rodata_1f400[]; /* @0x1f400 */
extern const unsigned char rodata_22121[]; /* @0x22121 */
extern const unsigned char rodata_243dc[]; /* @0x243dc */
extern const unsigned char rodata_243e0[]; /* @0x243e0 */
extern const unsigned char rodata_243e4[]; /* @0x243e4 */
extern const unsigned char rodata_243e8[]; /* @0x243e8 */
extern const unsigned char rodata_243ec[]; /* @0x243ec */
extern const unsigned char rodata_243f0[]; /* @0x243f0 */
extern const unsigned char rodata_243f4[]; /* @0x243f4 */
extern const unsigned char rodata_243f8[]; /* @0x243f8 */
extern const unsigned char rodata_24a41[]; /* @0x24a41 */
extern const unsigned char rodata_24ad9[]; /* @0x24ad9 */
extern const unsigned char rodata_25021[]; /* @0x25021 */
extern const unsigned char rodata_25059[]; /* @0x25059 */
extern const unsigned char rodata_25ae9[]; /* @0x25ae9 */
extern const unsigned char rodata_25d8d[]; /* @0x25d8d */
extern const unsigned char rodata_25dc5[]; /* @0x25dc5 */
extern const unsigned char rodata_25df9[]; /* @0x25df9 */
extern const unsigned char rodata_25fad[]; /* @0x25fad */
extern const unsigned char rodata_2692d[]; /* @0x2692d */
extern const unsigned char rodata_27cf8[]; /* @0x27cf8 */
extern const unsigned char rodata_27cfd[]; /* @0x27cfd */
extern const unsigned char rodata_28000[]; /* @0x28000 */
extern const unsigned char rodata_2e301[]; /* @0x2e301 */
extern const unsigned char rodata_30000[]; /* @0x30000 */
extern const unsigned char rodata_32421[]; /* @0x32421 */
extern const unsigned char rodata_33c44[]; /* @0x33c44 */
extern const unsigned char rodata_33c48[]; /* @0x33c48 */
extern const unsigned char rodata_35775[]; /* @0x35775 */
extern const unsigned char rodata_40000[]; /* @0x40000 */
extern const unsigned char rodata_40002[]; /* @0x40002 */
extern const unsigned char rodata_40202[]; /* @0x40202 */
extern const unsigned char rodata_46ce9[]; /* @0x46ce9 */
extern const unsigned char rodata_46d8d[]; /* @0x46d8d */
extern const unsigned char rodata_46f21[]; /* @0x46f21 */
extern const unsigned char rodata_4b1b5[]; /* @0x4b1b5 */
extern const unsigned char rodata_4b8a5[]; /* @0x4b8a5 */
extern const unsigned char rodata_4c38d[]; /* @0x4c38d */
extern const unsigned char rodata_4daad[]; /* @0x4daad */
extern const unsigned char rodata_4f4f1[]; /* @0x4f4f1 */
extern const unsigned char rodata_50100[]; /* @0x50100 */
extern const unsigned char rodata_57525[]; /* @0x57525 */
extern const unsigned char rodata_582b4[]; /* @0x582b4 */
extern const unsigned char rodata_588b5[]; /* @0x588b5 */
extern const unsigned char rodata_5a2d5[]; /* @0x5a2d5 */
extern const unsigned char rodata_5a2fd[]; /* @0x5a2fd */
extern const unsigned char rodata_5a329[]; /* @0x5a329 */
extern const unsigned char rodata_5b4bd[]; /* @0x5b4bd */
extern const unsigned char rodata_5e41d[]; /* @0x5e41d */
extern const unsigned char rodata_60635[]; /* @0x60635 */
extern const unsigned char rodata_72ab1[]; /* @0x72ab1 */
extern const unsigned char rodata_72dad[]; /* @0x72dad */
extern const unsigned char rodata_73729[]; /* @0x73729 */
extern const unsigned char rodata_75005[]; /* @0x75005 */
extern const unsigned char rodata_76b91[]; /* @0x76b91 */
extern const unsigned char rodata_79274[]; /* @0x79274 */
extern const unsigned char rodata_7c00d[]; /* @0x7c00d */
extern const unsigned char rodata_7c26b[]; /* @0x7c26b */
extern const unsigned char rodata_7c38b[]; /* @0x7c38b */
extern const unsigned char rodata_7c39d[]; /* @0x7c39d */
extern const unsigned char rodata_7d4cb[]; /* @0x7d4cb */
extern const unsigned char rodata_7d4d7[]; /* @0x7d4d7 */
extern const unsigned char rodata_7d86d[]; /* @0x7d86d */
extern const unsigned char rodata_7eb11[]; /* @0x7eb11 */
extern const unsigned char rodata_7eb1d[]; /* @0x7eb1d */
extern const unsigned char rodata_7eb37[]; /* @0x7eb37 */
extern const unsigned char rodata_7ed27[]; /* @0x7ed27 */
extern const unsigned char rodata_7f071[]; /* @0x7f071 */
extern const unsigned char rodata_7f5c5[]; /* @0x7f5c5 */
extern const unsigned char rodata_80e81[]; /* @0x80e81 */
extern const unsigned char rodata_81035[]; /* @0x81035 */
extern const unsigned char rodata_810ab[]; /* @0x810ab */
extern const unsigned char rodata_813d1[]; /* @0x813d1 */
extern const unsigned char rodata_81699[]; /* @0x81699 */
extern const unsigned char rodata_816af[]; /* @0x816af */
extern const unsigned char rodata_81b83[]; /* @0x81b83 */
extern const unsigned char rodata_825bb[]; /* @0x825bb */
extern const unsigned char rodata_825fb[]; /* @0x825fb */
extern const unsigned char rodata_82603[]; /* @0x82603 */
extern const unsigned char rodata_82a67[]; /* @0x82a67 */
extern const unsigned char rodata_82cb3[]; /* @0x82cb3 */
extern const unsigned char rodata_837a9[]; /* @0x837a9 */
extern const unsigned char rodata_838cb[]; /* @0x838cb */
extern const unsigned char rodata_84c57[]; /* @0x84c57 */
extern const unsigned char rodata_859a3[]; /* @0x859a3 */
extern const unsigned char rodata_859b1[]; /* @0x859b1 */
extern const unsigned char rodata_85f8d[]; /* @0x85f8d */
extern const unsigned char rodata_85f93[]; /* @0x85f93 */
extern const unsigned char rodata_85f97[]; /* @0x85f97 */
extern const unsigned char rodata_86661[]; /* @0x86661 */
extern const unsigned char rodata_86f35[]; /* @0x86f35 */
extern const unsigned char rodata_86f57[]; /* @0x86f57 */
extern const unsigned char rodata_86fb7[]; /* @0x86fb7 */
extern const unsigned char rodata_877ed[]; /* @0x877ed */
extern const unsigned char rodata_87b30[]; /* @0x87b30 */
extern const unsigned char rodata_87bc0[]; /* @0x87bc0 */
extern const unsigned char rodata_87bd8[]; /* @0x87bd8 */
extern const unsigned char rodata_87bf0[]; /* @0x87bf0 */
extern const unsigned char rodata_87bf8[]; /* @0x87bf8 */
extern const unsigned char rodata_87c08[]; /* @0x87c08 */
extern const unsigned char rodata_87c20[]; /* @0x87c20 */
extern const unsigned char rodata_87cb0[]; /* @0x87cb0 */
extern const unsigned char rodata_87ce0[]; /* @0x87ce0 "LDO2" device (iteration 9) */
extern const unsigned char rodata_87cf8[]; /* @0x87cf8 "LDO1" device (iteration 9) */
extern const unsigned char rodata_87d10[]; /* @0x87d10 "BUCK2" device (iteration 9) */
extern const unsigned char rodata_87d40[]; /* @0x87d40 */
extern const unsigned char rodata_87d58[]; /* @0x87d58 */
extern const unsigned char rodata_87d70[]; /* @0x87d70 */
extern const unsigned char rodata_87fc8[]; /* @0x87fc8 */
extern const unsigned char rodata_87fec[]; /* @0x87fec */
extern const unsigned char rodata_88058[]; /* @0x88058 */
extern const unsigned char rodata_88070[]; /* @0x88070 */
extern const unsigned char rodata_880d8[]; /* @0x880d8 */
extern const unsigned char rodata_880e0[]; /* @0x880e0 */
extern const unsigned char rodata_880e8[]; /* @0x880e8 */
extern const unsigned char rodata_880f0[]; /* @0x880f0 */
extern const unsigned char rodata_880f8[]; /* @0x880f8 */
extern const unsigned char rodata_88100[]; /* @0x88100 */
extern const unsigned char rodata_88120[]; /* @0x88120 */
extern const unsigned char rodata_88128[]; /* @0x88128 */
extern const unsigned char rodata_88130[]; /* @0x88130 */
extern const unsigned char rodata_88138[]; /* @0x88138 */
extern const unsigned char rodata_88148[]; /* @0x88148 */
extern const unsigned char rodata_88150[]; /* @0x88150 */
extern const unsigned char rodata_88158[]; /* @0x88158 */
extern const unsigned char rodata_88160[]; /* @0x88160 */
extern const unsigned char rodata_88178[]; /* @0x88178 */
extern const unsigned char rodata_88180[]; /* @0x88180 */
extern const unsigned char rodata_88188[]; /* @0x88188 */
extern const unsigned char rodata_881a0[]; /* @0x881a0 */
extern const unsigned char rodata_881a8[]; /* @0x881a8 */
extern const unsigned char rodata_881b0[]; /* @0x881b0 */
extern const unsigned char rodata_881b8[]; /* @0x881b8 */
extern const unsigned char rodata_881c0[]; /* @0x881c0 */
extern const unsigned char rodata_881d8[]; /* @0x881d8 */
extern const unsigned char rodata_881e0[]; /* @0x881e0 */
extern const unsigned char rodata_881f8[]; /* @0x881f8 */
extern const unsigned char rodata_88208[]; /* @0x88208 */
extern const unsigned char rodata_88220[]; /* @0x88220 */
extern const unsigned char rodata_88228[]; /* @0x88228 */
extern const unsigned char rodata_88250[]; /* @0x88250 */
extern const unsigned char rodata_88258[]; /* @0x88258 */
extern const unsigned char rodata_88268[]; /* @0x88268 */
extern const unsigned char rodata_88270[]; /* @0x88270 */
extern const unsigned char rodata_88278[]; /* @0x88278 */
extern const unsigned char rodata_88288[]; /* @0x88288 */
extern const unsigned char rodata_88290[]; /* @0x88290 */
extern const unsigned char rodata_882a0[]; /* @0x882a0 */
extern const unsigned char rodata_88340[]; /* @0x88340 */
extern const unsigned char rodata_88388[]; /* @0x88388 */
extern const unsigned char rodata_8839c[]; /* @0x8839c */
extern const unsigned char rodata_883b0[]; /* @0x883b0 */
extern const unsigned char rodata_883b4[]; /* @0x883b4 */
extern const unsigned char rodata_883b8[]; /* @0x883b8 */
extern const unsigned char rodata_883c8[]; /* @0x883c8 */
extern const unsigned char rodata_883ec[]; /* @0x883ec */
extern const unsigned char rodata_88410[]; /* @0x88410 */
extern const unsigned char rodata_88434[]; /* @0x88434 */
extern const unsigned char rodata_8843e[]; /* @0x8843e */
extern const unsigned char rodata_88480[]; /* @0x88480 */
extern const unsigned char rodata_88570[]; /* @0x88570 */
extern const unsigned char rodata_885b0[]; /* @0x885b0 */
extern const unsigned char rodata_885cc[]; /* @0x885cc */
extern const unsigned char rodata_88694[]; /* @0x88694 */
extern const unsigned char rodata_88697[]; /* @0x88697 */
extern const unsigned char rodata_887b7[]; /* @0x887b7 */
extern const unsigned char rodata_887c8[]; /* @0x887c8 */
extern const unsigned char rodata_887d9[]; /* @0x887d9 */
extern const unsigned char rodata_887ea[]; /* @0x887ea */
extern const unsigned char rodata_88848[]; /* @0x88848 */
extern const unsigned char rodata_88858[]; /* @0x88858 */
extern const unsigned char rodata_88868[]; /* @0x88868 */
extern const unsigned char rodata_88878[]; /* @0x88878 */
extern const unsigned char rodata_88888[]; /* @0x88888 */
extern const unsigned char rodata_888a8[]; /* @0x888a8 */
extern const unsigned char rodata_888e0[]; /* @0x888e0 */
extern const unsigned char rodata_88908[]; /* @0x88908 */
extern const unsigned char rodata_889d0[]; /* @0x889d0 */
extern const unsigned char rodata_889e0[]; /* @0x889e0 */
extern const unsigned char rodata_889d8[]; /* @0x889d8 */
extern const unsigned char rodata_889e8[]; /* @0x889e8 */
extern const unsigned char rodata_889f0[]; /* @0x889f0 */
extern const unsigned char rodata_889f8[]; /* @0x889f8 */
extern const unsigned char rodata_88a00[]; /* @0x88a00 */
extern const unsigned char rodata_88a0c[]; /* @0x88a0c */
extern const unsigned char rodata_88a2a[]; /* @0x88a2a */
extern const unsigned char rodata_88a38[]; /* @0x88a38 */
extern const unsigned char rodata_88a44[]; /* @0x88a44 */
extern const unsigned char rodata_8a050[]; /* @0x8a050 */
extern const unsigned char rodata_8a0a8[]; /* @0x8a0a8 */
extern const unsigned char rodata_8a208[]; /* @0x8a208 */
extern const unsigned char rodata_8a3e0[]; /* @0x8a3e0 */
extern const unsigned char rodata_8a4e8[]; /* @0x8a4e8 */
extern const unsigned char rodata_8a5f0[]; /* @0x8a5f0 */
extern const unsigned char rodata_8a6f8[]; /* @0x8a6f8 */
extern const unsigned char rodata_8a800[]; /* @0x8a800 */
extern const unsigned char rodata_8a908[]; /* @0x8a908 */
extern const unsigned char rodata_8aa10[]; /* @0x8aa10 */
extern const unsigned char rodata_8ab18[]; /* @0x8ab18 */
extern const unsigned char rodata_8ac20[]; /* @0x8ac20 */
extern const unsigned char rodata_8ac2c[]; /* @0x8ac2c */
extern const unsigned char rodata_8ac30[]; /* @0x8ac30 */
extern const unsigned char rodata_8ac34[]; /* @0x8ac34 */
extern const unsigned char rodata_8aca0[]; /* @0x8aca0 */
extern const unsigned char rodata_8acb4[]; /* @0x8acb4 */
extern const unsigned char rodata_8acc4[]; /* @0x8acc4 */
extern const unsigned char rodata_8acd8[]; /* @0x8acd8 */
extern const unsigned char rodata_8ad08[]; /* @0x8ad08 */
extern const unsigned char rodata_8ad40[]; /* @0x8ad40 */
extern const unsigned char rodata_8af10[]; /* @0x8af10 */
extern const unsigned char rodata_8af4c[]; /* @0x8af4c */
extern const unsigned char rodata_8b190[]; /* @0x8b190 */
extern const unsigned char rodata_8b264[]; /* @0x8b264 */
extern const unsigned char rodata_8b29c[]; /* @0x8b29c */
extern const unsigned char rodata_8b2b4[]; /* @0x8b2b4 */
extern const unsigned char rodata_8b3dc[]; /* @0x8b3dc */
extern const unsigned char rodata_8b508[]; /* @0x8b508 */
extern const unsigned char rodata_8b5fc[]; /* @0x8b5fc */
extern const unsigned char rodata_8ba64[]; /* @0x8ba64 */
extern const unsigned char rodata_8ba7c[]; /* @0x8ba7c */
extern const unsigned char rodata_8ba88[]; /* @0x8ba88 */
extern const unsigned char rodata_8ba94[]; /* @0x8ba94 */
extern const unsigned char rodata_8bb90[]; /* @0x8bb90 */
extern const unsigned char rodata_8bc88[]; /* @0x8bc88 */
extern const unsigned char rodata_8bc98[]; /* @0x8bc98 */
extern const unsigned char rodata_8c938[]; /* @0x8c938 */
extern const unsigned char rodata_8d24c[]; /* @0x8d24c */
extern const unsigned char rodata_98684[]; /* @0x98684 */
extern const unsigned char rodata_98690[]; /* @0x98690 */
extern const unsigned char rodata_9869c[]; /* @0x9869c */
extern const unsigned char rodata_986a4[]; /* @0x986a4 */
extern const unsigned char rodata_986ac[]; /* @0x986ac */
extern const unsigned char rodata_9873c[]; /* @0x9873c */
extern const unsigned char rodata_98768[]; /* @0x98768 */
extern const unsigned char rodata_98774[]; /* @0x98774 */
extern const unsigned char rodata_988a8[]; /* @0x988a8 */
extern const unsigned char rodata_9890c[]; /* @0x9890c */
extern const unsigned char rodata_98e3c[]; /* @0x98e3c */
extern const unsigned char rodata_98fbc[]; /* @0x98fbc */
extern const unsigned char rodata_98fe8[]; /* @0x98fe8 */
extern const unsigned char rodata_99014[]; /* @0x99014 */
extern const unsigned char rodata_99042[]; /* @0x99042 */
extern const unsigned char rodata_9905e[]; /* @0x9905e */
extern const unsigned char rodata_9907c[]; /* @0x9907c */
extern const unsigned char rodata_990cf[]; /* @0x990cf */
extern const unsigned char rodata_990dc[]; /* @0x990dc */
extern const unsigned char rodata_99105[]; /* @0x99105 */
extern const unsigned char rodata_99133[]; /* @0x99133 */
extern const unsigned char rodata_99152[]; /* @0x99152 */
extern const unsigned char rodata_99228[]; /* @0x99228 */
extern const unsigned char rodata_99297[]; /* @0x99297 */
extern const unsigned char rodata_992e1[]; /* @0x992e1 */
extern const unsigned char rodata_99329[]; /* @0x99329 */
extern const unsigned char rodata_99345[]; /* @0x99345 */
extern const unsigned char rodata_9938c[]; /* @0x9938c */
extern const unsigned char rodata_9940b[]; /* @0x9940b */
extern const unsigned char rodata_99427[]; /* @0x99427 */
extern const unsigned char rodata_9945a[]; /* @0x9945a */
extern const unsigned char rodata_9949a[]; /* @0x9949a */
extern const unsigned char rodata_994b9[]; /* @0x994b9 */
extern const unsigned char rodata_9951c[]; /* @0x9951c */
extern const unsigned char rodata_99528[]; /* @0x99528 */
extern const unsigned char rodata_99534[]; /* @0x99534 */
extern const unsigned char rodata_99540[]; /* @0x99540 */
extern const unsigned char rodata_9954c[]; /* @0x9954c */
extern const unsigned char rodata_99558[]; /* @0x99558 */
extern const unsigned char rodata_99564[]; /* @0x99564 */
extern const unsigned char rodata_99570[]; /* @0x99570 */
extern const unsigned char rodata_9957c[]; /* @0x9957c */
extern const unsigned char rodata_99707[]; /* @0x99707 */
extern const unsigned char rodata_99726[]; /* @0x99726 */
extern const unsigned char rodata_9976b[]; /* @0x9976b */
extern const unsigned char rodata_99830[]; /* @0x99830 */
extern const unsigned char rodata_99835[]; /* @0x99835 */
extern const unsigned char rodata_9985c[]; /* @0x9985c */
extern const unsigned char rodata_99899[]; /* @0x99899 */
extern const unsigned char rodata_998ad[]; /* @0x998ad */
extern const unsigned char rodata_998b5[]; /* @0x998b5 */
extern const unsigned char rodata_998da[]; /* @0x998da */
extern const unsigned char rodata_998e7[]; /* @0x998e7 */
extern const unsigned char rodata_998fc[]; /* @0x998fc */
extern const unsigned char rodata_99908[]; /* @0x99908 */
extern const unsigned char rodata_9992e[]; /* @0x9992e */
extern const unsigned char rodata_99942[]; /* @0x99942 */
extern const unsigned char rodata_9995c[]; /* @0x9995c */
extern const unsigned char rodata_99969[]; /* @0x99969 */
extern const unsigned char rodata_99976[]; /* @0x99976 */
extern const unsigned char rodata_9999c[]; /* @0x9999c */
extern const unsigned char rodata_999c2[]; /* @0x999c2 */
extern const unsigned char rodata_999e4[]; /* @0x999e4 */
extern const unsigned char rodata_999ff[]; /* @0x999ff */
extern const unsigned char rodata_99a23[]; /* @0x99a23 */
extern const unsigned char rodata_99a3e[]; /* @0x99a3e */
extern const unsigned char rodata_99a60[]; /* @0x99a60 */
extern const unsigned char rodata_99a7f[]; /* @0x99a7f */
extern const unsigned char rodata_99a94[]; /* @0x99a94 */
extern const unsigned char rodata_99aa4[]; /* @0x99aa4 */
extern const unsigned char rodata_99acf[]; /* @0x99acf */
extern const unsigned char rodata_99af4[]; /* @0x99af4 */
extern const unsigned char rodata_99b1e[]; /* @0x99b1e */
extern const unsigned char rodata_99b2a[]; /* @0x99b2a */
extern const unsigned char rodata_99b3d[]; /* @0x99b3d */
extern const unsigned char rodata_99b4c[]; /* @0x99b4c */
extern const unsigned char rodata_99b89[]; /* @0x99b89 */
extern const unsigned char rodata_99ba5[]; /* @0x99ba5 */
extern const unsigned char rodata_99bb2[]; /* @0x99bb2 */
extern const unsigned char rodata_99bb7[]; /* @0x99bb7 */
extern const unsigned char rodata_99bd8[]; /* @0x99bd8 */
extern const unsigned char rodata_99bee[]; /* @0x99bee */
extern const unsigned char rodata_99c00[]; /* @0x99c00 */
extern const unsigned char rodata_99c17[]; /* @0x99c17 */
extern const unsigned char rodata_99c28[]; /* @0x99c28 */
extern const unsigned char rodata_99c3e[]; /* @0x99c3e */
extern const unsigned char rodata_99c53[]; /* @0x99c53 */
extern const unsigned char rodata_99c84[]; /* @0x99c84 */
extern const unsigned char rodata_99cbd[]; /* @0x99cbd */
extern const unsigned char rodata_99cda[]; /* @0x99cda */
extern const unsigned char rodata_99d17[]; /* @0x99d17 */
extern const unsigned char rodata_99d5e[]; /* @0x99d5e */
extern const unsigned char rodata_99dad[]; /* @0x99dad */
extern const unsigned char rodata_99de0[]; /* @0x99de0 */
extern const unsigned char rodata_99e1e[]; /* @0x99e1e */
extern const unsigned char rodata_99e30[]; /* @0x99e30 */
extern const unsigned char rodata_99e71[]; /* @0x99e71 */
extern const unsigned char rodata_99e9d[]; /* @0x99e9d */
extern const unsigned char rodata_99ec7[]; /* @0x99ec7 */
extern const unsigned char rodata_99ef2[]; /* @0x99ef2 */
extern const unsigned char rodata_99f3c[]; /* @0x99f3c */
extern const unsigned char rodata_99f81[]; /* @0x99f81 */
extern const unsigned char rodata_99fd2[]; /* @0x99fd2 */
extern const unsigned char rodata_99fe8[]; /* @0x99fe8 */
extern const unsigned char rodata_9a016[]; /* @0x9a016 */
extern const unsigned char rodata_9a044[]; /* @0x9a044 */
extern const unsigned char rodata_9a072[]; /* @0x9a072 */
extern const unsigned char rodata_9a0a0[]; /* @0x9a0a0 */
extern const unsigned char rodata_9a0c6[]; /* @0x9a0c6 */
extern const unsigned char rodata_9a119[]; /* @0x9a119 */
extern const unsigned char rodata_9a126[]; /* @0x9a126 */
extern const unsigned char rodata_9a132[]; /* @0x9a132 */
extern const unsigned char rodata_9a143[]; /* @0x9a143 */
extern const unsigned char rodata_9a155[]; /* @0x9a155 */
extern const unsigned char rodata_9a18e[]; /* @0x9a18e */
extern const unsigned char rodata_9a1ae[]; /* @0x9a1ae */
extern const unsigned char rodata_9a1c8[]; /* @0x9a1c8 */
extern const unsigned char rodata_9a1cf[]; /* @0x9a1cf */
extern const unsigned char rodata_9a1d6[]; /* @0x9a1d6 */
extern const unsigned char rodata_9a1dd[]; /* @0x9a1dd */
extern const unsigned char rodata_9a1e0[]; /* @0x9a1e0 */
extern const unsigned char rodata_9a1ea[]; /* @0x9a1ea */
extern const unsigned char rodata_9a20d[]; /* @0x9a20d */
extern const unsigned char rodata_9a275[]; /* @0x9a275 */
extern const unsigned char rodata_9a295[]; /* @0x9a295 */
extern const unsigned char rodata_9a2b1[]; /* @0x9a2b1 */
extern const unsigned char rodata_9a2bf[]; /* @0x9a2bf */
extern const unsigned char rodata_9a2cd[]; /* @0x9a2cd */
extern const unsigned char rodata_9a401[]; /* @0x9a401 */
extern const unsigned char rodata_9a436[]; /* @0x9a436 */
extern const unsigned char rodata_9a458[]; /* @0x9a458 */
extern const unsigned char rodata_9a46f[]; /* @0x9a46f */
extern const unsigned char rodata_9a48b[]; /* @0x9a48b */
extern const unsigned char rodata_9a4af[]; /* @0x9a4af */
extern const unsigned char rodata_9a4e0[]; /* @0x9a4e0 */
extern const unsigned char rodata_9a4f7[]; /* @0x9a4f7 */
extern const unsigned char rodata_9a52b[]; /* @0x9a52b */
extern const unsigned char rodata_9a53f[]; /* @0x9a53f */
extern const unsigned char rodata_9a56b[]; /* @0x9a56b */
extern const unsigned char rodata_9a5ae[]; /* @0x9a5ae */
extern const unsigned char rodata_9a5d8[]; /* @0x9a5d8 */
extern const unsigned char rodata_9a5f4[]; /* @0x9a5f4 */
extern const unsigned char rodata_9a638[]; /* @0x9a638 */
extern const unsigned char rodata_9a65b[]; /* @0x9a65b */
extern const unsigned char rodata_9a688[]; /* @0x9a688 */
extern const unsigned char rodata_9a6c1[]; /* @0x9a6c1 */
extern const unsigned char rodata_9a6f2[]; /* @0x9a6f2 */
extern const unsigned char rodata_9a71e[]; /* @0x9a71e */
extern const unsigned char rodata_9a74c[]; /* @0x9a74c */
extern const unsigned char rodata_9a788[]; /* @0x9a788 */
extern const unsigned char rodata_9a7bc[]; /* @0x9a7bc */
extern const unsigned char rodata_9a7f2[]; /* @0x9a7f2 */
extern const unsigned char rodata_9a820[]; /* @0x9a820 */
extern const unsigned char rodata_9a854[]; /* @0x9a854 */
extern const unsigned char rodata_9a88a[]; /* @0x9a88a */
extern const unsigned char rodata_9a8c3[]; /* @0x9a8c3 */
extern const unsigned char rodata_9a8f9[]; /* @0x9a8f9 */
extern const unsigned char rodata_9a92a[]; /* @0x9a92a */
extern const unsigned char rodata_9a949[]; /* @0x9a949 */
extern const unsigned char rodata_9a964[]; /* @0x9a964 */
extern const unsigned char rodata_9a981[]; /* @0x9a981 */
extern const unsigned char rodata_9a992[]; /* @0x9a992 */
extern const unsigned char rodata_9a9cd[]; /* @0x9a9cd */
extern const unsigned char rodata_9aa1f[]; /* @0x9aa1f */
extern const unsigned char rodata_9aa2f[]; /* @0x9aa2f */
extern const unsigned char rodata_9aa4b[]; /* @0x9aa4b */
extern const unsigned char rodata_9aa64[]; /* @0x9aa64 */
extern const unsigned char rodata_9aafd[]; /* @0x9aafd */
extern const unsigned char rodata_9ab0c[]; /* @0x9ab0c */
extern const unsigned char rodata_9ab1e[]; /* @0x9ab1e */
extern const unsigned char rodata_9abbd[]; /* @0x9abbd */
extern const unsigned char rodata_9abdc[]; /* @0x9abdc */
extern const unsigned char rodata_9ac14[]; /* @0x9ac14 */
extern const unsigned char rodata_9ac4c[]; /* @0x9ac4c */
extern const unsigned char rodata_9ac60[]; /* @0x9ac60 */
extern const unsigned char rodata_9ac7c[]; /* @0x9ac7c */
extern const unsigned char rodata_9ac84[]; /* @0x9ac84 */
extern const unsigned char rodata_9ac9d[]; /* @0x9ac9d */
extern const unsigned char rodata_9acb2[]; /* @0x9acb2 */
extern const unsigned char rodata_9acc4[]; /* @0x9acc4 */
extern const unsigned char rodata_9ace0[]; /* @0x9ace0 */
extern const unsigned char rodata_9acf9[]; /* @0x9acf9 */
extern const unsigned char rodata_9ad0e[]; /* @0x9ad0e */
extern const unsigned char rodata_9ad20[]; /* @0x9ad20 */
extern const unsigned char rodata_9ad4b[]; /* @0x9ad4b */
extern const unsigned char rodata_9ad7c[]; /* @0x9ad7c */
extern const unsigned char rodata_9ad86[]; /* @0x9ad86 */
extern const unsigned char rodata_9adaa[]; /* @0x9adaa */
extern const unsigned char rodata_9adc7[]; /* @0x9adc7 */
extern const unsigned char rodata_9adf5[]; /* @0x9adf5 */
extern const unsigned char rodata_9ae34[]; /* @0x9ae34 */
extern const unsigned char rodata_9ae92[]; /* @0x9ae92 */
extern const unsigned char rodata_9aef3[]; /* @0x9aef3 */
extern const unsigned char rodata_9af2e[]; /* @0x9af2e */
extern const unsigned char rodata_9af3b[]; /* @0x9af3b */
extern const unsigned char rodata_9af75[]; /* @0x9af75 */
extern const unsigned char rodata_9afa1[]; /* @0x9afa1 */
extern const unsigned char rodata_9afc3[]; /* @0x9afc3 */
extern const unsigned char rodata_9afed[]; /* @0x9afed */
extern const unsigned char rodata_9b019[]; /* @0x9b019 */
extern const unsigned char rodata_9b04b[]; /* @0x9b04b */
extern const unsigned char rodata_9b060[]; /* @0x9b060 */
extern const unsigned char rodata_9b089[]; /* @0x9b089 */
extern const unsigned char rodata_9b0ae[]; /* @0x9b0ae */
extern const unsigned char rodata_9b0d8[]; /* @0x9b0d8 */
extern const unsigned char rodata_9b0f1[]; /* @0x9b0f1 */
extern const unsigned char rodata_9b108[]; /* @0x9b108 */
extern const unsigned char rodata_9b11a[]; /* @0x9b11a */
extern const unsigned char rodata_9b126[]; /* @0x9b126 */
extern const unsigned char rodata_9b135[]; /* @0x9b135 */
extern const unsigned char rodata_9b13f[]; /* @0x9b13f */
extern const unsigned char rodata_9b148[]; /* @0x9b148 */
extern const unsigned char rodata_9b15e[]; /* @0x9b15e */
extern const unsigned char rodata_9b16a[]; /* @0x9b16a */
extern const unsigned char rodata_9b176[]; /* @0x9b176 */
extern const unsigned char rodata_9b182[]; /* @0x9b182 */
extern const unsigned char rodata_9b190[]; /* @0x9b190 */
extern const unsigned char rodata_9b19d[]; /* @0x9b19d */
extern const unsigned char rodata_9b1aa[]; /* @0x9b1aa */
extern const unsigned char rodata_9b1b9[]; /* @0x9b1b9 */
extern const unsigned char rodata_9b1c8[]; /* @0x9b1c8 */
extern const unsigned char rodata_9b1da[]; /* @0x9b1da */
extern const unsigned char rodata_9b20d[]; /* @0x9b20d */
extern const unsigned char rodata_9b229[]; /* @0x9b229 */
extern const unsigned char rodata_9b257[]; /* @0x9b257 */
extern const unsigned char rodata_9b2ba[]; /* @0x9b2ba */
extern const unsigned char rodata_9b2f5[]; /* @0x9b2f5 */
extern const unsigned char rodata_9b331[]; /* @0x9b331 */
extern const unsigned char rodata_9b345[]; /* @0x9b345 */
extern const unsigned char rodata_9b35a[]; /* @0x9b35a */
extern const unsigned char rodata_9b371[]; /* @0x9b371 */
extern const unsigned char rodata_9b3b5[]; /* @0x9b3b5 */
extern const unsigned char rodata_9b3e0[]; /* @0x9b3e0 */
extern const unsigned char rodata_9b413[]; /* @0x9b413 */
extern const unsigned char rodata_9b44a[]; /* @0x9b44a */
extern const unsigned char rodata_9b45e[]; /* @0x9b45e */
extern const unsigned char rodata_9b482[]; /* @0x9b482 */
extern const unsigned char rodata_9b5dd[]; /* @0x9b5dd */
extern const unsigned char rodata_9b708[]; /* @0x9b708 */
extern const unsigned char rodata_9b74b[]; /* @0x9b74b */
extern const unsigned char rodata_9b8fd[]; /* @0x9b8fd */
extern const unsigned char rodata_9b98b[]; /* @0x9b98b */
extern const unsigned char rodata_9bbbf[]; /* @0x9bbbf */
extern const unsigned char rodata_9d000[]; /* @0x9d000 */
extern const unsigned char rodata_9d30b[]; /* @0x9d30b */
extern const unsigned char rodata_9d4e4[]; /* @0x9d4e4 */
extern const unsigned char rodata_9d518[]; /* @0x9d518 */
extern const unsigned char rodata_9d546[]; /* @0x9d546 */
extern const unsigned char rodata_9d587[]; /* @0x9d587 */
extern const unsigned char rodata_9d5af[]; /* @0x9d5af */
extern const unsigned char rodata_9d5da[]; /* @0x9d5da */
extern const unsigned char rodata_9d64e[]; /* @0x9d64e */
extern const unsigned char rodata_9d671[]; /* @0x9d671 */
extern const unsigned char rodata_9d681[]; /* @0x9d681 */
extern const unsigned char rodata_9d69e[]; /* @0x9d69e */
extern const unsigned char rodata_9d6a1[]; /* @0x9d6a1 */
extern const unsigned char rodata_9d6d8[]; /* @0x9d6d8 */
extern const unsigned char rodata_9d6ee[]; /* @0x9d6ee */
extern const unsigned char rodata_9d6f3[]; /* @0x9d6f3 */
extern const unsigned char rodata_9d70f[]; /* @0x9d70f */
extern const unsigned char rodata_9d714[]; /* @0x9d714 */
extern const unsigned char rodata_9d734[]; /* @0x9d734 */
extern const unsigned char rodata_9d749[]; /* @0x9d749 */
extern const unsigned char rodata_9d759[]; /* @0x9d759 */
extern const unsigned char rodata_9d768[]; /* @0x9d768 */
extern const unsigned char rodata_9d76c[]; /* @0x9d76c */
extern const unsigned char rodata_9d775[]; /* @0x9d775 */
extern const unsigned char rodata_9d77d[]; /* @0x9d77d */
extern const unsigned char rodata_9d789[]; /* @0x9d789 */
extern const unsigned char rodata_9d790[]; /* @0x9d790 */
extern const unsigned char rodata_9d79d[]; /* @0x9d79d */
extern const unsigned char rodata_9d7ae[]; /* @0x9d7ae */
extern const unsigned char rodata_9d7b8[]; /* @0x9d7b8 */
extern const unsigned char rodata_9d7cc[]; /* @0x9d7cc */
extern const unsigned char rodata_9d7d4[]; /* @0x9d7d4 */
extern const unsigned char rodata_9d7e1[]; /* @0x9d7e1 */
extern const unsigned char rodata_9d7e8[]; /* @0x9d7e8 */
extern const unsigned char rodata_9d7f7[]; /* @0x9d7f7 */
extern const unsigned char rodata_9d7fa[]; /* @0x9d7fa */
extern const unsigned char rodata_9d81e[]; /* @0x9d81e */
extern const unsigned char rodata_9d822[]; /* @0x9d822 */
extern const unsigned char rodata_9d857[]; /* @0x9d857 */
extern const unsigned char rodata_9d85b[]; /* @0x9d85b */
extern const unsigned char rodata_9d88c[]; /* @0x9d88c */
extern const unsigned char rodata_9d890[]; /* @0x9d890 */
extern const unsigned char rodata_9d8b1[]; /* @0x9d8b1 */
extern const unsigned char rodata_9d8b5[]; /* @0x9d8b5 */
extern const unsigned char rodata_9d8da[]; /* @0x9d8da */
extern const unsigned char rodata_9d8de[]; /* @0x9d8de */
extern const unsigned char rodata_9d8ed[]; /* @0x9d8ed */
extern const unsigned char rodata_9d8fc[]; /* @0x9d8fc */
extern const unsigned char rodata_9d90a[]; /* @0x9d90a */
extern const unsigned char rodata_9d925[]; /* @0x9d925 */
extern const unsigned char rodata_9d92b[]; /* @0x9d92b */
extern const unsigned char rodata_9d94a[]; /* @0x9d94a */
extern const unsigned char rodata_9d95b[]; /* @0x9d95b */
extern const unsigned char rodata_9d969[]; /* @0x9d969 */
extern const unsigned char rodata_9d9a5[]; /* @0x9d9a5 */
extern const unsigned char rodata_9d9ed[]; /* @0x9d9ed */
extern const unsigned char rodata_9da2f[]; /* @0x9da2f */
extern const unsigned char rodata_9da61[]; /* @0x9da61 */
extern const unsigned char rodata_9db03[]; /* @0x9db03 */
extern const unsigned char rodata_9db15[]; /* @0x9db15 */
extern const unsigned char rodata_9db45[]; /* @0x9db45 */
extern const unsigned char rodata_9db4f[]; /* @0x9db4f */
extern const unsigned char rodata_9db81[]; /* @0x9db81 */
extern const unsigned char rodata_9db91[]; /* @0x9db91 */
extern const unsigned char rodata_9dbb4[]; /* @0x9dbb4 */
extern const unsigned char rodata_9dbc5[]; /* @0x9dbc5 */
extern const unsigned char rodata_9dbec[]; /* @0x9dbec */
extern const unsigned char rodata_9dc17[]; /* @0x9dc17 */
extern const unsigned char rodata_9dc1a[]; /* @0x9dc1a */
extern const unsigned char rodata_9dc9c[]; /* @0x9dc9c */
extern const unsigned char rodata_9dcbb[]; /* @0x9dcbb */
extern const unsigned char rodata_9dd09[]; /* @0x9dd09 */
extern const unsigned char rodata_9dd24[]; /* @0x9dd24 */
extern const unsigned char rodata_9dd27[]; /* @0x9dd27 */
extern const unsigned char rodata_9dd4b[]; /* @0x9dd4b */
extern const unsigned char rodata_9dd4e[]; /* @0x9dd4e */
extern const unsigned char rodata_9dd6a[]; /* @0x9dd6a */
extern const unsigned char rodata_9dd6d[]; /* @0x9dd6d */
extern const unsigned char rodata_9dd70[]; /* @0x9dd70 */
extern const unsigned char rodata_9dd73[]; /* @0x9dd73 */
extern const unsigned char rodata_9dd91[]; /* @0x9dd91 */
extern const unsigned char rodata_9dd94[]; /* @0x9dd94 */
extern const unsigned char rodata_9ddb9[]; /* @0x9ddb9 */
extern const unsigned char rodata_9ddbc[]; /* @0x9ddbc */
extern const unsigned char rodata_9ddbf[]; /* @0x9ddbf */
extern const unsigned char rodata_9ddc8[]; /* @0x9ddc8 */
extern const unsigned char rodata_9ddcb[]; /* @0x9ddcb */
extern const unsigned char rodata_9ddce[]; /* @0x9ddce */
extern const unsigned char rodata_9ddd8[]; /* @0x9ddd8 */
extern const unsigned char rodata_9dddb[]; /* @0x9dddb */
extern const unsigned char rodata_9ddde[]; /* @0x9ddde */
extern const unsigned char rodata_9dde8[]; /* @0x9dde8 */
extern const unsigned char rodata_9ddeb[]; /* @0x9ddeb */
extern const unsigned char rodata_9de32[]; /* @0x9de32 */
extern const unsigned char rodata_9de35[]; /* @0x9de35 */
extern const unsigned char rodata_9de4c[]; /* @0x9de4c */
extern const unsigned char rodata_9de4f[]; /* @0x9de4f */
extern const unsigned char rodata_9de5e[]; /* @0x9de5e */
extern const unsigned char rodata_9de61[]; /* @0x9de61 */
extern const unsigned char rodata_9de63[]; /* @0x9de63 */
extern const unsigned char rodata_9de6e[]; /* @0x9de6e */
extern const unsigned char rodata_9de71[]; /* @0x9de71 */
extern const unsigned char rodata_9de74[]; /* @0x9de74 */
extern const unsigned char rodata_9dec8[]; /* @0x9dec8 */
extern const unsigned char rodata_9ded0[]; /* @0x9ded0 */
extern const unsigned char rodata_9dede[]; /* @0x9dede */
extern const unsigned char rodata_9deed[]; /* @0x9deed */
extern const unsigned char rodata_9df00[]; /* @0x9df00 */
extern const unsigned char rodata_9df28[]; /* @0x9df28 */
extern const unsigned char rodata_9df51[]; /* @0x9df51 */
extern const unsigned char rodata_9df99[]; /* @0x9df99 */
extern const unsigned char rodata_9dfa9[]; /* @0x9dfa9 */
extern const unsigned char rodata_9dfbf[]; /* @0x9dfbf */
extern const unsigned char rodata_9dfe8[]; /* @0x9dfe8 */
extern const unsigned char rodata_9e014[]; /* @0x9e014 */
extern const unsigned char rodata_9e032[]; /* @0x9e032 */
extern const unsigned char rodata_9e04e[]; /* @0x9e04e */
extern const unsigned char rodata_9e08b[]; /* @0x9e08b */
extern const unsigned char rodata_9e0a4[]; /* @0x9e0a4 */
extern const unsigned char rodata_9e0b2[]; /* @0x9e0b2 */
extern const unsigned char rodata_9e0d0[]; /* @0x9e0d0 */
extern const unsigned char rodata_9e161[]; /* @0x9e161 */
extern const unsigned char rodata_9e187[]; /* @0x9e187 */
extern const unsigned char rodata_9e1a8[]; /* @0x9e1a8 */
extern const unsigned char rodata_9e1b6[]; /* @0x9e1b6 */
extern const unsigned char rodata_9e1ba[]; /* @0x9e1ba */
extern const unsigned char rodata_9e1de[]; /* @0x9e1de */
extern const unsigned char rodata_9e1eb[]; /* @0x9e1eb */
extern const unsigned char rodata_9e201[]; /* @0x9e201 */
extern const unsigned char rodata_9e20e[]; /* @0x9e20e */
extern const unsigned char rodata_9e21f[]; /* @0x9e21f */
extern const unsigned char rodata_9e230[]; /* @0x9e230 */
extern const unsigned char rodata_9e235[]; /* @0x9e235 */
extern const unsigned char rodata_9e23c[]; /* @0x9e23c */
extern const unsigned char rodata_9e249[]; /* @0x9e249 */
extern const unsigned char rodata_9e259[]; /* @0x9e259 */
extern const unsigned char rodata_9e266[]; /* @0x9e266 */
extern const unsigned char rodata_9e2cb[]; /* @0x9e2cb */
extern const unsigned char rodata_9e2da[]; /* @0x9e2da */
extern const unsigned char rodata_9e2f1[]; /* @0x9e2f1 */
extern const unsigned char rodata_9e324[]; /* @0x9e324 */
extern const unsigned char rodata_9e345[]; /* @0x9e345 */
extern const unsigned char rodata_9e36d[]; /* @0x9e36d */
extern const unsigned char rodata_9e385[]; /* @0x9e385 */
extern const unsigned char rodata_9e3af[]; /* @0x9e3af */
extern const unsigned char rodata_9e3c6[]; /* @0x9e3c6 */
extern const unsigned char rodata_9e3db[]; /* @0x9e3db */
extern const unsigned char rodata_9e3e7[]; /* @0x9e3e7 */
extern const unsigned char rodata_9e403[]; /* @0x9e403 */
extern const unsigned char rodata_9e430[]; /* @0x9e430 */
extern const unsigned char rodata_9e44d[]; /* @0x9e44d */
extern const unsigned char rodata_9e46a[]; /* @0x9e46a */
extern const unsigned char rodata_9e484[]; /* @0x9e484 */
extern const unsigned char rodata_9e4a3[]; /* @0x9e4a3 */
extern const unsigned char rodata_9e4c7[]; /* @0x9e4c7 */
extern const unsigned char rodata_9e4e3[]; /* @0x9e4e3 */
extern const unsigned char rodata_9e4f0[]; /* @0x9e4f0 */
extern const unsigned char rodata_9e4f9[]; /* @0x9e4f9 */
extern const unsigned char rodata_9e508[]; /* @0x9e508 */
extern const unsigned char rodata_9e528[]; /* @0x9e528 */
extern const unsigned char rodata_9e53c[]; /* @0x9e53c */
extern const unsigned char rodata_9e549[]; /* @0x9e549 */
extern const unsigned char rodata_9e553[]; /* @0x9e553 */
extern const unsigned char rodata_9e580[]; /* @0x9e580 */
extern const unsigned char rodata_9e5a6[]; /* @0x9e5a6 */
extern const unsigned char rodata_9e5c8[]; /* @0x9e5c8 */
extern const unsigned char rodata_9e5f3[]; /* @0x9e5f3 */
extern const unsigned char rodata_9e60c[]; /* @0x9e60c */
extern const unsigned char rodata_9e632[]; /* @0x9e632 */
extern const unsigned char rodata_9e655[]; /* @0x9e655 */
extern const unsigned char rodata_9e67c[]; /* @0x9e67c */
extern const unsigned char rodata_9e6d7[]; /* @0x9e6d7 */
extern const unsigned char rodata_9e708[]; /* @0x9e708 */
extern const unsigned char rodata_9e72a[]; /* @0x9e72a */
extern const unsigned char rodata_9e747[]; /* @0x9e747 */
extern const unsigned char rodata_9e764[]; /* @0x9e764 */
extern const unsigned char rodata_9e777[]; /* @0x9e777 */
extern const unsigned char rodata_9e789[]; /* @0x9e789 */
extern const unsigned char rodata_9e7a6[]; /* @0x9e7a6 */
extern const unsigned char rodata_9e7b7[]; /* @0x9e7b7 */
extern const unsigned char rodata_9e7c9[]; /* @0x9e7c9 */
extern const unsigned char rodata_9e7da[]; /* @0x9e7da */
extern const unsigned char rodata_9e7fd[]; /* @0x9e7fd */
extern const unsigned char rodata_9e810[]; /* @0x9e810 */
extern const unsigned char rodata_9e824[]; /* @0x9e824 */
extern const unsigned char rodata_9e840[]; /* @0x9e840 */
extern const unsigned char rodata_9e85d[]; /* @0x9e85d */
extern const unsigned char rodata_9e873[]; /* @0x9e873 */
extern const unsigned char rodata_9e88b[]; /* @0x9e88b */
extern const unsigned char rodata_9e8af[]; /* @0x9e8af */
extern const unsigned char rodata_9e8be[]; /* @0x9e8be */
extern const unsigned char rodata_9e8cf[]; /* @0x9e8cf */
extern const unsigned char rodata_9e8e5[]; /* @0x9e8e5 */
extern const unsigned char rodata_9e8f6[]; /* @0x9e8f6 */
extern const unsigned char rodata_9e903[]; /* @0x9e903 */
extern const unsigned char rodata_9e932[]; /* @0x9e932 */
extern const unsigned char rodata_9e968[]; /* @0x9e968 */
extern const unsigned char rodata_9e98c[]; /* @0x9e98c */
extern const unsigned char rodata_9e9bf[]; /* @0x9e9bf */
extern const unsigned char rodata_9e9ea[]; /* @0x9e9ea */
extern const unsigned char rodata_9ea0a[]; /* @0x9ea0a */
extern const unsigned char rodata_9ea37[]; /* @0x9ea37 */
extern const unsigned char rodata_9ea58[]; /* @0x9ea58 */
extern const unsigned char rodata_9ea7b[]; /* @0x9ea7b */
extern const unsigned char rodata_9ead2[]; /* @0x9ead2 */
extern const unsigned char rodata_9eaf4[]; /* @0x9eaf4 */
extern const unsigned char rodata_9eb2e[]; /* @0x9eb2e */
extern const unsigned char rodata_9eba7[]; /* @0x9eba7 */
extern const unsigned char rodata_9ebc6[]; /* @0x9ebc6 */
extern const unsigned char rodata_9ecd5[]; /* @0x9ecd5 */
extern const unsigned char rodata_9ecf5[]; /* @0x9ecf5 */
extern const unsigned char rodata_9ed09[]; /* @0x9ed09 */
extern const unsigned char rodata_9ed2e[]; /* @0x9ed2e */
extern const unsigned char rodata_9ed4a[]; /* @0x9ed4a */
extern const unsigned char rodata_9ed68[]; /* @0x9ed68 */
extern const unsigned char rodata_9ed8f[]; /* @0x9ed8f */
extern const unsigned char rodata_9eda4[]; /* @0x9eda4 */
extern const unsigned char rodata_9edc2[]; /* @0x9edc2 */
extern const unsigned char rodata_9edf3[]; /* @0x9edf3 */
extern const unsigned char rodata_9ee23[]; /* @0x9ee23 */
extern const unsigned char rodata_9ee54[]; /* @0x9ee54 */
extern const unsigned char rodata_9ee80[]; /* @0x9ee80 */
extern const unsigned char rodata_9eeeb[]; /* @0x9eeeb */
extern const unsigned char rodata_9ef15[]; /* @0x9ef15 */
extern const unsigned char rodata_9ef67[]; /* @0x9ef67 */
extern const unsigned char rodata_9efaf[]; /* @0x9efaf */
extern const unsigned char rodata_9f010[]; /* @0x9f010 */
extern const unsigned char rodata_9f032[]; /* @0x9f032 */
extern const unsigned char rodata_9f050[]; /* @0x9f050 */
extern const unsigned char rodata_9f066[]; /* @0x9f066 */
extern const unsigned char rodata_9f080[]; /* @0x9f080 */
extern const unsigned char rodata_9f094[]; /* @0x9f094 */
extern const unsigned char rodata_9f0b0[]; /* @0x9f0b0 */
extern const unsigned char rodata_9f0db[]; /* @0x9f0db */
extern const unsigned char rodata_9f104[]; /* @0x9f104 */
extern const unsigned char rodata_9f120[]; /* @0x9f120 */
extern const unsigned char rodata_9f145[]; /* @0x9f145 */
extern const unsigned char rodata_9f176[]; /* @0x9f176 */
extern const unsigned char rodata_9f186[]; /* @0x9f186 */
extern const unsigned char rodata_9f196[]; /* @0x9f196 */
extern const unsigned char rodata_9f1af[]; /* @0x9f1af */
extern const unsigned char rodata_9f1c3[]; /* @0x9f1c3 */
extern const unsigned char rodata_9f1cf[]; /* @0x9f1cf */
extern const unsigned char rodata_9f1eb[]; /* @0x9f1eb */
extern const unsigned char rodata_9f203[]; /* @0x9f203 */
extern const unsigned char rodata_9f239[]; /* @0x9f239 */
extern const unsigned char rodata_9f250[]; /* @0x9f250 */
extern const unsigned char rodata_9f285[]; /* @0x9f285 */
extern const unsigned char rodata_9f2be[]; /* @0x9f2be */
extern const unsigned char rodata_9f2f8[]; /* @0x9f2f8 */
extern const unsigned char rodata_9f32d[]; /* @0x9f32d */
extern const unsigned char rodata_9f361[]; /* @0x9f361 */
extern const unsigned char rodata_9f396[]; /* @0x9f396 */
extern const unsigned char rodata_9f3fa[]; /* @0x9f3fa */
extern const unsigned char rodata_9f418[]; /* @0x9f418 */
extern const unsigned char rodata_9f433[]; /* @0x9f433 */
extern const unsigned char rodata_9f487[]; /* @0x9f487 */
extern const unsigned char rodata_9f4a1[]; /* @0x9f4a1 */
extern const unsigned char rodata_9f512[]; /* @0x9f512 */
extern const unsigned char rodata_9f540[]; /* @0x9f540 */
extern const unsigned char rodata_9f576[]; /* @0x9f576 */
extern const unsigned char rodata_9f5a9[]; /* @0x9f5a9 */
extern const unsigned char rodata_9f5ce[]; /* @0x9f5ce */
extern const unsigned char rodata_9f5ec[]; /* @0x9f5ec */
extern const unsigned char rodata_9f611[]; /* @0x9f611 */
extern const unsigned char rodata_9f63c[]; /* @0x9f63c */
extern const unsigned char rodata_9f67e[]; /* @0x9f67e */
extern const unsigned char rodata_9f6a3[]; /* @0x9f6a3 */
extern const unsigned char rodata_9f6c6[]; /* @0x9f6c6 */
extern const unsigned char rodata_9f6e3[]; /* @0x9f6e3 */
extern const unsigned char rodata_9f6f1[]; /* @0x9f6f1 */
extern const unsigned char rodata_9f704[]; /* @0x9f704 */
extern const unsigned char rodata_9f73d[]; /* @0x9f73d */
extern const unsigned char rodata_9f929[]; /* @0x9f929 */
extern const unsigned char rodata_9fa9c[]; /* @0x9fa9c */
extern const unsigned char rodata_9fb15[]; /* @0x9fb15 */
extern const unsigned char rodata_9f721[]; /* @0x9f721 */ /* iteration 13: imu_fusion_init log strings */
extern const unsigned char rodata_9f72f[]; /* @0x9f72f */ /* iteration 13: imu_fusion_init log strings */
extern const unsigned char rodata_9f773[]; /* @0x9f773 */ /* iteration 13: imu_fusion_init log strings */
extern const unsigned char rodata_9f797[]; /* @0x9f797 */ /* iteration 13: imu_fusion_init log strings */
extern const unsigned char rodata_9f7c3[]; /* @0x9f7c3 */ /* iteration 13: imu_fusion_init log strings */
extern const unsigned char rodata_9f812[]; /* @0x9f812 */ /* iteration 13: imu_fusion_init log strings */
extern const unsigned char rodata_9f851[]; /* @0x9f851 */ /* iteration 13: imu_fusion_init log strings */
extern const unsigned char rodata_9fae1[]; /* @0x9fae1 */ /* iteration 13: imu_fusion_init log strings */
extern const unsigned char rodata_9faf1[]; /* @0x9faf1 */ /* iteration 13: imu_fusion_init log strings */
extern const unsigned char rodata_9faf9[]; /* @0x9faf9 */ /* iteration 13: imu_fusion_init log strings */
extern const unsigned char rodata_9fb00[]; /* @0x9fb00 */ /* iteration 13: imu_fusion_init log strings */
extern const unsigned char rodata_9fb42[]; /* @0x9fb42 */
extern const unsigned char rodata_9fb59[]; /* @0x9fb59 */
extern const unsigned char rodata_9fb89[]; /* @0x9fb89 */
extern const unsigned char rodata_9fb9f[]; /* @0x9fb9f */
extern const unsigned char rodata_9fbda[]; /* @0x9fbda */
extern const unsigned char rodata_9fbfd[]; /* @0x9fbfd */
extern const unsigned char rodata_9fc15[]; /* @0x9fc15 */
extern const unsigned char rodata_9fc2c[]; /* @0x9fc2c */
extern const unsigned char rodata_9fc4d[]; /* @0x9fc4d */
extern const unsigned char rodata_9fc5d[]; /* @0x9fc5d */
extern const unsigned char rodata_9fc79[]; /* @0x9fc79 */
extern const unsigned char rodata_9fc8b[]; /* @0x9fc8b */
extern const unsigned char rodata_9fc99[]; /* @0x9fc99 */
extern const unsigned char rodata_9fcc1[]; /* @0x9fcc1 */
extern const unsigned char rodata_9fce4[]; /* @0x9fce4 */
extern const unsigned char rodata_9fd02[]; /* @0x9fd02 */
extern const unsigned char rodata_9fede[]; /* @0x9fede */
extern const unsigned char rodata_9ff05[]; /* @0x9ff05 */
extern const unsigned char rodata_9ff92[]; /* @0x9ff92 */
extern const unsigned char rodata_a0102[]; /* @0xa0102 */
extern const unsigned char rodata_a0132[]; /* @0xa0132 */
extern const unsigned char rodata_a0169[]; /* @0xa0169 */
extern const unsigned char rodata_a01c7[]; /* @0xa01c7 */
extern const unsigned char rodata_a01ea[]; /* @0xa01ea */
extern const unsigned char rodata_a020e[]; /* @0xa020e */
extern const unsigned char rodata_a0210[]; /* @0xa0210 */
extern const unsigned char rodata_a0231[]; /* @0xa0231 */
extern const unsigned char rodata_a024a[]; /* @0xa024a */
extern const unsigned char rodata_a0266[]; /* @0xa0266 */
extern const unsigned char rodata_a028c[]; /* @0xa028c */
extern const unsigned char rodata_a02ab[]; /* @0xa02ab */
extern const unsigned char rodata_a02cc[]; /* @0xa02cc */
extern const unsigned char rodata_a030d[]; /* @0xa030d */
extern const unsigned char rodata_a0354[]; /* @0xa0354 */
extern const unsigned char rodata_a036a[]; /* @0xa036a */
extern const unsigned char rodata_a0396[]; /* @0xa0396 */
extern const unsigned char rodata_a03b3[]; /* @0xa03b3 */
extern const unsigned char rodata_a03d9[]; /* @0xa03d9 */
extern const unsigned char rodata_a03f5[]; /* @0xa03f5 */
extern const unsigned char rodata_a0434[]; /* @0xa0434 */
extern const unsigned char rodata_a044e[]; /* @0xa044e */
extern const unsigned char rodata_a0477[]; /* @0xa0477 */
extern const unsigned char rodata_a04cb[]; /* @0xa04cb */
extern const unsigned char rodata_a050a[]; /* @0xa050a */
extern const unsigned char rodata_a052d[]; /* @0xa052d */
extern const unsigned char rodata_a0568[]; /* @0xa0568 */
extern const unsigned char rodata_a05c2[]; /* @0xa05c2 */
extern const unsigned char rodata_a0621[]; /* @0xa0621 */
extern const unsigned char rodata_a067b[]; /* @0xa067b */
extern const unsigned char rodata_a06d7[]; /* @0xa06d7 */
extern const unsigned char rodata_a07eb[]; /* @0xa07eb */
extern const unsigned char rodata_a0889[]; /* @0xa0889 */
extern const unsigned char rodata_a0932[]; /* @0xa0932 */
extern const unsigned char rodata_a0962[]; /* @0xa0962 */
extern const unsigned char rodata_a09ac[]; /* @0xa09ac */
extern const unsigned char rodata_a09ee[]; /* @0xa09ee */
extern const unsigned char rodata_a0a04[]; /* @0xa0a04 */
extern const unsigned char rodata_a0a2e[]; /* @0xa0a2e */
extern const unsigned char rodata_a0a47[]; /* @0xa0a47 */
extern const unsigned char rodata_a0a61[]; /* @0xa0a61 */
extern const unsigned char rodata_a0a7b[]; /* @0xa0a7b */
extern const unsigned char rodata_a0ca9[]; /* @0xa0ca9 */
extern const unsigned char rodata_a0cdf[]; /* @0xa0cdf */
extern const unsigned char rodata_a0d03[]; /* @0xa0d03 */
extern const unsigned char rodata_a0d1d[]; /* @0xa0d1d */
extern const unsigned char rodata_a0d34[]; /* @0xa0d34 */
extern const unsigned char rodata_a0d50[]; /* @0xa0d50 */
extern const unsigned char rodata_a0d77[]; /* @0xa0d77 */
extern const unsigned char rodata_a0d92[]; /* @0xa0d92 */
extern const unsigned char rodata_a0dcb[]; /* @0xa0dcb */
extern const unsigned char rodata_a0e3d[]; /* @0xa0e3d */
extern const unsigned char rodata_a0e91[]; /* @0xa0e91 */
extern const unsigned char rodata_a0ee6[]; /* @0xa0ee6 */
extern const unsigned char rodata_a0f08[]; /* @0xa0f08 */
extern const unsigned char rodata_a0fad[]; /* @0xa0fad */
extern const unsigned char rodata_a0fe5[]; /* @0xa0fe5 */
extern const unsigned char rodata_a1027[]; /* @0xa1027 */
extern const unsigned char rodata_a116d[]; /* @0xa116d */
extern const unsigned char rodata_a125e[]; /* @0xa125e */
extern const unsigned char rodata_a15d6[]; /* @0xa15d6 */
extern const unsigned char rodata_a1626[]; /* @0xa1626 */
extern const unsigned char rodata_a1681[]; /* @0xa1681 */
extern const unsigned char rodata_a172a[]; /* @0xa172a */
extern const unsigned char rodata_a1895[]; /* @0xa1895 */
extern const unsigned char rodata_a18bf[]; /* @0xa18bf */
extern const unsigned char rodata_a18cd[]; /* @0xa18cd */
extern const unsigned char rodata_a18ea[]; /* @0xa18ea */
extern const unsigned char rodata_a1914[]; /* @0xa1914 */
extern const unsigned char rodata_a193c[]; /* @0xa193c */
extern const unsigned char rodata_a1962[]; /* @0xa1962 */
extern const unsigned char rodata_a19af[]; /* @0xa19af */
extern const unsigned char rodata_a19c0[]; /* @0xa19c0 */
extern const unsigned char rodata_a19e5[]; /* @0xa19e5 */
extern const unsigned char rodata_a1a13[]; /* @0xa1a13 */
extern const unsigned char rodata_a1a43[]; /* @0xa1a43 */
extern const unsigned char rodata_a1a76[]; /* @0xa1a76 */
extern const unsigned char rodata_a1a98[]; /* @0xa1a98 */
extern const unsigned char rodata_a1ab1[]; /* @0xa1ab1 */
extern const unsigned char rodata_a1ad8[]; /* @0xa1ad8 */
extern const unsigned char rodata_a1aea[]; /* @0xa1aea */
extern const unsigned char rodata_a1b00[]; /* @0xa1b00 */
extern const unsigned char rodata_a1b10[]; /* @0xa1b10 */
extern const unsigned char rodata_a1b33[]; /* @0xa1b33 */
extern const unsigned char rodata_a1b50[]; /* @0xa1b50 */
extern const unsigned char rodata_a1b88[]; /* @0xa1b88 */
extern const unsigned char rodata_a1bbc[]; /* @0xa1bbc */
extern const unsigned char rodata_a1bf6[]; /* @0xa1bf6 */
extern const unsigned char rodata_a1c17[]; /* @0xa1c17 */
extern const unsigned char rodata_a1c4e[]; /* @0xa1c4e */
extern const unsigned char rodata_a1c6a[]; /* @0xa1c6a */
extern const unsigned char rodata_a1c85[]; /* @0xa1c85 */
extern const unsigned char rodata_a1c96[]; /* @0xa1c96 */
extern const unsigned char rodata_a1ca4[]; /* @0xa1ca4 */
extern const unsigned char rodata_a1ce0[]; /* @0xa1ce0 */
extern const unsigned char rodata_a1cfc[]; /* @0xa1cfc */
extern const unsigned char rodata_a1d06[]; /* @0xa1d06 */
extern const unsigned char rodata_a1d31[]; /* @0xa1d31 */
extern const unsigned char rodata_a1d59[]; /* @0xa1d59 */
extern const unsigned char rodata_a1dbe[]; /* @0xa1dbe */
extern const unsigned char rodata_a1df5[]; /* @0xa1df5 */
extern const unsigned char rodata_a1e3a[]; /* @0xa1e3a */
extern const unsigned char rodata_a1e66[]; /* @0xa1e66 */
extern const unsigned char rodata_a1ead[]; /* @0xa1ead */
extern const unsigned char rodata_a1edb[]; /* @0xa1edb */
extern const unsigned char rodata_a1f1a[]; /* @0xa1f1a */
extern const unsigned char rodata_a1f20[]; /* @0xa1f20 */
extern const unsigned char rodata_a1f24[]; /* @0xa1f24 */
extern const unsigned char rodata_a1f35[]; /* @0xa1f35 */
extern const unsigned char rodata_a1f49[]; /* @0xa1f49 */
extern const unsigned char rodata_a1f4d[]; /* @0xa1f4d */
extern const unsigned char rodata_a1f4e[]; /* @0xa1f4e */
extern const unsigned char rodata_a1f7d[]; /* @0xa1f7d */
extern const unsigned char rodata_a1fc7[]; /* @0xa1fc7 */
extern const unsigned char rodata_a1ff2[]; /* @0xa1ff2 */
extern const unsigned char rodata_a201b[]; /* @0xa201b */
extern const unsigned char rodata_a2041[]; /* @0xa2041 */
extern const unsigned char rodata_a2061[]; /* @0xa2061 */
extern const unsigned char rodata_a20c2[]; /* @0xa20c2 */
extern const unsigned char rodata_a20e9[]; /* @0xa20e9 */
extern const unsigned char rodata_a211e[]; /* @0xa211e */
extern const unsigned char rodata_a2184[]; /* @0xa2184 */
extern const unsigned char rodata_a21c4[]; /* @0xa21c4 */
extern const unsigned char rodata_a21f9[]; /* @0xa21f9 */
extern const unsigned char rodata_a2227[]; /* @0xa2227 */
extern const unsigned char rodata_a22b8[]; /* @0xa22b8 */
extern const unsigned char rodata_a2334[]; /* @0xa2334 */
extern const unsigned char rodata_a2364[]; /* @0xa2364 */
extern const unsigned char rodata_a2383[]; /* @0xa2383 */
extern const unsigned char rodata_a23a0[]; /* @0xa23a0 */
extern const unsigned char rodata_a23cd[]; /* @0xa23cd */
extern const unsigned char rodata_a23d0[]; /* @0xa23d0 */
extern const unsigned char rodata_a23e8[]; /* @0xa23e8 */
extern const unsigned char rodata_a23ff[]; /* @0xa23ff */
extern const unsigned char rodata_a2416[]; /* @0xa2416 */
extern const unsigned char rodata_a243a[]; /* @0xa243a */
extern const unsigned char rodata_a245b[]; /* @0xa245b */
extern const unsigned char rodata_a2470[]; /* @0xa2470 */
extern const unsigned char rodata_a2486[]; /* @0xa2486 */
extern const unsigned char rodata_a24a9[]; /* @0xa24a9 */
extern const unsigned char rodata_a24c3[]; /* @0xa24c3 */
extern const unsigned char rodata_a24dc[]; /* @0xa24dc */
extern const unsigned char rodata_a24e0[]; /* @0xa24e0 */
extern const unsigned char rodata_a24e4[]; /* @0xa24e4 */
extern const unsigned char rodata_a24eb[]; /* @0xa24eb */
extern const unsigned char rodata_a24f9[]; /* @0xa24f9 */
extern const unsigned char rodata_a251a[]; /* @0xa251a */
extern const unsigned char rodata_a2530[]; /* @0xa2530 */
extern const unsigned char rodata_a254a[]; /* @0xa254a */
extern const unsigned char rodata_a2597[]; /* @0xa2597 */
extern const unsigned char rodata_a25b9[]; /* @0xa25b9 */
extern const unsigned char rodata_a25d9[]; /* @0xa25d9 */
extern const unsigned char rodata_a25f8[]; /* @0xa25f8 */
extern const unsigned char rodata_a2625[]; /* @0xa2625 */
extern const unsigned char rodata_a2648[]; /* @0xa2648 */
extern const unsigned char rodata_a2660[]; /* @0xa2660 */
extern const unsigned char rodata_a26ae[]; /* @0xa26ae */
extern const unsigned char rodata_a26cb[]; /* @0xa26cb */
extern const unsigned char rodata_a26f7[]; /* @0xa26f7 */
extern const unsigned char rodata_a2733[]; /* @0xa2733 */
extern const unsigned char rodata_a2748[]; /* @0xa2748 */
extern const unsigned char rodata_a2768[]; /* @0xa2768 */
extern const unsigned char rodata_a2795[]; /* @0xa2795 */
extern const unsigned char rodata_a27b1[]; /* @0xa27b1 */
extern const unsigned char rodata_a2831[]; /* @0xa2831 */
extern const unsigned char rodata_a28d4[]; /* @0xa28d4 */
extern const unsigned char rodata_a28ee[]; /* @0xa28ee */
extern const unsigned char rodata_a291d[]; /* @0xa291d */
extern const unsigned char rodata_a294a[]; /* @0xa294a */
extern const unsigned char rodata_a2977[]; /* @0xa2977 */
extern const unsigned char rodata_a29be[]; /* @0xa29be */
extern const unsigned char rodata_a2a21[]; /* @0xa2a21 */
extern const unsigned char rodata_a2a32[]; /* @0xa2a32 */
extern const unsigned char rodata_a2a4d[]; /* @0xa2a4d */
extern const unsigned char rodata_a2a7e[]; /* @0xa2a7e */
extern const unsigned char rodata_a2aad[]; /* @0xa2aad */
extern const unsigned char rodata_a2ad4[]; /* @0xa2ad4 */
extern const unsigned char rodata_a2af2[]; /* @0xa2af2 */
extern const unsigned char rodata_a2b22[]; /* @0xa2b22 */
extern const unsigned char rodata_a2ba7[]; /* @0xa2ba7 */
extern const unsigned char rodata_a2c0b[]; /* @0xa2c0b */
extern const unsigned char rodata_a2c70[]; /* @0xa2c70 */
extern const unsigned char rodata_a2c85[]; /* @0xa2c85 */
extern const unsigned char rodata_a2cb2[]; /* @0xa2cb2 */
extern const unsigned char rodata_a2ce2[]; /* @0xa2ce2 */
extern const unsigned char rodata_a2cfc[]; /* @0xa2cfc */
extern const unsigned char rodata_a2d1a[]; /* @0xa2d1a */
extern const unsigned char rodata_a2d5a[]; /* @0xa2d5a */
extern const unsigned char rodata_a2d6f[]; /* @0xa2d6f */
extern const unsigned char rodata_a2d97[]; /* @0xa2d97 */
extern const unsigned char rodata_a2de3[]; /* @0xa2de3 */
extern const unsigned char rodata_a2e31[]; /* @0xa2e31 */
extern const unsigned char rodata_a2e5b[]; /* @0xa2e5b */
extern const unsigned char rodata_a2e7c[]; /* @0xa2e7c */
extern const unsigned char rodata_a2e93[]; /* @0xa2e93 */
extern const unsigned char rodata_a2ed8[]; /* @0xa2ed8 */
extern const unsigned char rodata_a2f08[]; /* @0xa2f08 */
extern const unsigned char rodata_a2f57[]; /* @0xa2f57 */
extern const unsigned char rodata_a2f7e[]; /* @0xa2f7e */
extern const unsigned char rodata_a2f9c[]; /* @0xa2f9c */
extern const unsigned char rodata_a2fb0[]; /* @0xa2fb0 */
extern const unsigned char rodata_a301e[]; /* @0xa301e */
extern const unsigned char rodata_a3071[]; /* @0xa3071 */
extern const unsigned char rodata_a30bd[]; /* @0xa30bd */
extern const unsigned char rodata_a30e5[]; /* @0xa30e5 */
extern const unsigned char rodata_a3104[]; /* @0xa3104 */
extern const unsigned char rodata_a3119[]; /* @0xa3119 */
extern const unsigned char rodata_a315d[]; /* @0xa315d */
extern const unsigned char rodata_a318d[]; /* @0xa318d */
extern const unsigned char rodata_a31da[]; /* @0xa31da */
extern const unsigned char rodata_a3201[]; /* @0xa3201 */
extern const unsigned char rodata_a3215[]; /* @0xa3215 */
extern const unsigned char rodata_a3244[]; /* @0xa3244 */
extern const unsigned char rodata_a3290[]; /* @0xa3290 */
extern const unsigned char rodata_a32b6[]; /* @0xa32b6 */
extern const unsigned char rodata_a32df[]; /* @0xa32df */
extern const unsigned char rodata_a32ef[]; /* @0xa32ef */
extern const unsigned char rodata_a3305[]; /* @0xa3305 */
extern const unsigned char rodata_a3311[]; /* @0xa3311 */
extern const unsigned char rodata_a3325[]; /* @0xa3325 */
extern const unsigned char rodata_a3373[]; /* @0xa3373 */
extern const unsigned char rodata_a339b[]; /* @0xa339b */
extern const unsigned char rodata_a33aa[]; /* @0xa33aa */
extern const unsigned char rodata_a33bf[]; /* @0xa33bf */
extern const unsigned char rodata_a33de[]; /* @0xa33de */
extern const unsigned char rodata_a342b[]; /* @0xa342b */
extern const unsigned char rodata_a3456[]; /* @0xa3456 */
extern const unsigned char rodata_a3468[]; /* @0xa3468 */
extern const unsigned char rodata_a3480[]; /* @0xa3480 */
extern const unsigned char rodata_a34a2[]; /* @0xa34a2 */
extern const unsigned char rodata_a34f2[]; /* @0xa34f2 */
extern const unsigned char rodata_a3517[]; /* @0xa3517 */
extern const unsigned char rodata_a3558[]; /* @0xa3558 */
extern const unsigned char rodata_a35a2[]; /* @0xa35a2 */
extern const unsigned char rodata_a35cd[]; /* @0xa35cd */
extern const unsigned char rodata_a35df[]; /* @0xa35df */
extern const unsigned char rodata_a35f7[]; /* @0xa35f7 */
extern const unsigned char rodata_a3619[]; /* @0xa3619 */
extern const unsigned char rodata_a3669[]; /* @0xa3669 */
extern const unsigned char rodata_a3696[]; /* @0xa3696 */
extern const unsigned char rodata_a36ff[]; /* @0xa36ff */
extern const unsigned char rodata_a3758[]; /* @0xa3758 */
extern const unsigned char rodata_a3770[]; /* @0xa3770 */
extern const unsigned char rodata_a37f6[]; /* @0xa37f6 */
extern const unsigned char rodata_a3811[]; /* @0xa3811 */
extern const unsigned char rodata_a383d[]; /* @0xa383d */
extern const unsigned char rodata_a384c[]; /* @0xa384c */
extern const unsigned char rodata_a3875[]; /* @0xa3875 */
extern const unsigned char rodata_a3886[]; /* @0xa3886 */
extern const unsigned char rodata_a38a5[]; /* @0xa38a5 */
extern const unsigned char rodata_a38be[]; /* @0xa38be */
extern const unsigned char rodata_a38dd[]; /* @0xa38dd */
extern const unsigned char rodata_a38f9[]; /* @0xa38f9 */
extern const unsigned char rodata_a3916[]; /* @0xa3916 */
extern const unsigned char rodata_a3930[]; /* @0xa3930 */
extern const unsigned char rodata_a394b[]; /* @0xa394b */
extern const unsigned char rodata_a3967[]; /* @0xa3967 */
extern const unsigned char rodata_a3982[]; /* @0xa3982 */
extern const unsigned char rodata_a39a0[]; /* @0xa39a0 */
extern const unsigned char rodata_a39bb[]; /* @0xa39bb */
extern const unsigned char rodata_a39d6[]; /* @0xa39d6 */
extern const unsigned char rodata_a39ef[]; /* @0xa39ef */
extern const unsigned char rodata_a3a0f[]; /* @0xa3a0f */
extern const unsigned char rodata_a3a24[]; /* @0xa3a24 */
extern const unsigned char rodata_a3a5a[]; /* @0xa3a5a */
extern const unsigned char rodata_a3a72[]; /* @0xa3a72 */
extern const unsigned char rodata_a3a8b[]; /* @0xa3a8b */
extern const unsigned char rodata_a3aa6[]; /* @0xa3aa6 */
extern const unsigned char rodata_a3ab6[]; /* @0xa3ab6 */
extern const unsigned char rodata_a3ac5[]; /* @0xa3ac5 */
extern const unsigned char rodata_a3ae5[]; /* @0xa3ae5 */
extern const unsigned char rodata_a3af8[]; /* @0xa3af8 */
extern const unsigned char rodata_a3b17[]; /* @0xa3b17 */
extern const unsigned char rodata_a3b3f[]; /* @0xa3b3f */
extern const unsigned char rodata_a3b5a[]; /* @0xa3b5a */
extern const unsigned char rodata_a3b7a[]; /* @0xa3b7a */
extern const unsigned char rodata_a3b8e[]; /* @0xa3b8e */
extern const unsigned char rodata_a3bd6[]; /* @0xa3bd6 */
extern const unsigned char rodata_a3c0c[]; /* @0xa3c0c */
extern const unsigned char rodata_a3c2d[]; /* @0xa3c2d */
extern const unsigned char rodata_a3c68[]; /* @0xa3c68 */
extern const unsigned char rodata_a3c82[]; /* @0xa3c82 */
extern const unsigned char rodata_a3cb9[]; /* @0xa3cb9 */
extern const unsigned char rodata_a3cda[]; /* @0xa3cda */
extern const unsigned char rodata_a3cee[]; /* @0xa3cee */
extern const unsigned char rodata_a3d00[]; /* @0xa3d00 */
extern const unsigned char rodata_a3d12[]; /* @0xa3d12 */
extern const unsigned char rodata_a3d26[]; /* @0xa3d26 */
extern const unsigned char rodata_a3d37[]; /* @0xa3d37 */
extern const unsigned char rodata_a3d62[]; /* @0xa3d62 */
extern const unsigned char rodata_a3d83[]; /* @0xa3d83 */
extern const unsigned char rodata_a3dae[]; /* @0xa3dae */
extern const unsigned char rodata_a3e08[]; /* @0xa3e08 */
extern const unsigned char rodata_a3e1a[]; /* @0xa3e1a */
extern const unsigned char rodata_a3e48[]; /* @0xa3e48 */
extern const unsigned char rodata_a3e62[]; /* @0xa3e62 */
extern const unsigned char rodata_a3e80[]; /* @0xa3e80 */
extern const unsigned char rodata_a3e9f[]; /* @0xa3e9f */
extern const unsigned char rodata_a3ec1[]; /* @0xa3ec1 */
extern const unsigned char rodata_a3ee4[]; /* @0xa3ee4 */
extern const unsigned char rodata_a3efc[]; /* @0xa3efc */
extern const unsigned char rodata_a3f17[]; /* @0xa3f17 */
extern const unsigned char rodata_a3f45[]; /* @0xa3f45 */
extern const unsigned char rodata_a3f62[]; /* @0xa3f62 */
extern const unsigned char rodata_a3f7f[]; /* @0xa3f7f */
extern const unsigned char rodata_a3fbe[]; /* @0xa3fbe */
extern const unsigned char rodata_a3fdf[]; /* @0xa3fdf */
extern const unsigned char rodata_a4038[]; /* @0xa4038 */
extern const unsigned char rodata_a404b[]; /* @0xa404b */
extern const unsigned char rodata_a4062[]; /* @0xa4062 */
extern const unsigned char rodata_a4075[]; /* @0xa4075 */
extern const unsigned char rodata_a40e6[]; /* @0xa40e6 */
extern const unsigned char rodata_a40ec[]; /* @0xa40ec */
extern const unsigned char rodata_a4120[]; /* @0xa4120 */
extern const unsigned char rodata_a4147[]; /* @0xa4147 */
extern const unsigned char rodata_a417e[]; /* @0xa417e */
extern const unsigned char rodata_a41a0[]; /* @0xa41a0 */
extern const unsigned char rodata_a41b0[]; /* @0xa41b0 */
extern const unsigned char rodata_a41c2[]; /* @0xa41c2 */
extern const unsigned char rodata_a41d5[]; /* @0xa41d5 */
extern const unsigned char rodata_a41e2[]; /* @0xa41e2 */
extern const unsigned char rodata_a41ef[]; /* @0xa41ef */
extern const unsigned char rodata_a41ff[]; /* @0xa41ff */
extern const unsigned char rodata_a420e[]; /* @0xa420e */
extern const unsigned char rodata_a4233[]; /* @0xa4233 */
extern const unsigned char rodata_a4253[]; /* @0xa4253 */
extern const unsigned char rodata_a427e[]; /* @0xa427e */
extern const unsigned char rodata_a42cf[]; /* @0xa42cf */
extern const unsigned char rodata_a4304[]; /* @0xa4304 */
extern const unsigned char rodata_a432a[]; /* @0xa432a */
extern const unsigned char rodata_a4395[]; /* @0xa4395 */
extern const unsigned char rodata_a43b9[]; /* @0xa43b9 */
extern const unsigned char rodata_a43f3[]; /* @0xa43f3 */
extern const unsigned char rodata_a4413[]; /* @0xa4413 */
extern const unsigned char rodata_a4439[]; /* @0xa4439 */
extern const unsigned char rodata_a447d[]; /* @0xa447d */
extern const unsigned char rodata_a44bf[]; /* @0xa44bf */
extern const unsigned char rodata_a4511[]; /* @0xa4511 */
extern const unsigned char rodata_a4558[]; /* @0xa4558 */
extern const unsigned char rodata_a457d[]; /* @0xa457d */
extern const unsigned char rodata_a45c1[]; /* @0xa45c1 */
extern const unsigned char rodata_a461a[]; /* @0xa461a */
extern const unsigned char rodata_a4675[]; /* @0xa4675 */
extern const unsigned char rodata_a4690[]; /* @0xa4690 */
extern const unsigned char rodata_a46cb[]; /* @0xa46cb */
extern const unsigned char rodata_a46fd[]; /* @0xa46fd */
extern const unsigned char rodata_a4739[]; /* @0xa4739 */
extern const unsigned char rodata_a47a2[]; /* @0xa47a2 */
extern const unsigned char rodata_a486b[]; /* @0xa486b */
extern const unsigned char rodata_a48fa[]; /* @0xa48fa */
extern const unsigned char rodata_a4908[]; /* @0xa4908 */
extern const unsigned char rodata_a4926[]; /* @0xa4926 */
extern const unsigned char rodata_a4944[]; /* @0xa4944 */
extern const unsigned char rodata_a4959[]; /* @0xa4959 */
extern const unsigned char rodata_a496f[]; /* @0xa496f */
extern const unsigned char rodata_a4986[]; /* @0xa4986 */
extern const unsigned char rodata_a49ed[]; /* @0xa49ed */
extern const unsigned char rodata_a64ed[]; /* @0xa64ed */
extern const unsigned char rodata_a6589[]; /* @0xa6589 */
extern const unsigned char rodata_a6603[]; /* @0xa6603 */
extern const unsigned char rodata_a6711[]; /* @0xa6711 */
extern const unsigned char rodata_a671e[]; /* @0xa671e */
extern const unsigned char rodata_a672f[]; /* @0xa672f */
extern const unsigned char rodata_a676d[]; /* @0xa676d */
extern const unsigned char rodata_a69f3[]; /* @0xa69f3 */
extern const unsigned char rodata_a6a0b[]; /* @0xa6a0b */
extern const unsigned char rodata_a6aab[]; /* @0xa6aab */
extern const unsigned char rodata_a701c[]; /* @0xa701c */
extern const unsigned char rodata_a7031[]; /* @0xa7031 */
extern const unsigned char rodata_a704b[]; /* @0xa704b */
extern const unsigned char rodata_a70a0[]; /* @0xa70a0 */
extern const unsigned char rodata_a70c1[]; /* @0xa70c1 */
extern const unsigned char rodata_a70e7[]; /* @0xa70e7 */
extern const unsigned char rodata_a715d[]; /* @0xa715d */
extern const unsigned char rodata_a7173[]; /* @0xa7173 */
extern const unsigned char rodata_a718e[]; /* @0xa718e */
extern const unsigned char rodata_a71ab[]; /* @0xa71ab */
extern const unsigned char rodata_a71cd[]; /* @0xa71cd */
extern const unsigned char rodata_a71e0[]; /* @0xa71e0 */
extern const unsigned char rodata_a7209[]; /* @0xa7209 */
extern const unsigned char rodata_a723e[]; /* @0xa723e */
extern const unsigned char rodata_a7266[]; /* @0xa7266 */
extern const unsigned char rodata_a7293[]; /* @0xa7293 */
extern const unsigned char rodata_a72ab[]; /* @0xa72ab */
extern const unsigned char rodata_a72c6[]; /* @0xa72c6 */
extern const unsigned char rodata_a72e1[]; /* @0xa72e1 */
extern const unsigned char rodata_a72fc[]; /* @0xa72fc */
extern const unsigned char rodata_a731c[]; /* @0xa731c */
extern const unsigned char rodata_a7336[]; /* @0xa7336 */
extern const unsigned char rodata_a73e2[]; /* @0xa73e2 */
extern const unsigned char rodata_a7411[]; /* @0xa7411 */
extern const unsigned char rodata_a742d[]; /* @0xa742d */
extern const unsigned char rodata_a74b9[]; /* @0xa74b9 */
extern const unsigned char rodata_a74dc[]; /* @0xa74dc */
extern const unsigned char rodata_a7500[]; /* @0xa7500 */
extern const unsigned char rodata_a756a[]; /* @0xa756a */
extern const unsigned char rodata_a757f[]; /* @0xa757f */
extern const unsigned char rodata_a759e[]; /* @0xa759e */
extern const unsigned char rodata_a75c2[]; /* @0xa75c2 */
extern const unsigned char rodata_a7655[]; /* @0xa7655 */
extern const unsigned char rodata_a766d[]; /* @0xa766d */
extern const unsigned char rodata_a769d[]; /* @0xa769d */
extern const unsigned char rodata_a76cb[]; /* @0xa76cb */
extern const unsigned char rodata_a76da[]; /* @0xa76da */
extern const unsigned char rodata_a76f2[]; /* @0xa76f2 */
extern const unsigned char rodata_a7712[]; /* @0xa7712 */
extern const unsigned char rodata_a7735[]; /* @0xa7735 */
extern const unsigned char rodata_a7751[]; /* @0xa7751 */
extern const unsigned char rodata_a776c[]; /* @0xa776c */
extern const unsigned char rodata_a7780[]; /* @0xa7780 */
extern const unsigned char rodata_a779f[]; /* @0xa779f */
extern const unsigned char rodata_a77b5[]; /* @0xa77b5 */
extern const unsigned char rodata_a77cc[]; /* @0xa77cc */
extern const unsigned char rodata_a780d[]; /* @0xa780d */
extern const unsigned char rodata_a7882[]; /* @0xa7882 */
extern const unsigned char rodata_a7892[]; /* @0xa7892 */
extern const unsigned char rodata_a78b9[]; /* @0xa78b9 */
extern const unsigned char rodata_a78d1[]; /* @0xa78d1 */
extern const unsigned char rodata_a78eb[]; /* @0xa78eb */
extern const unsigned char rodata_a7907[]; /* @0xa7907 */
extern const unsigned char rodata_a797b[]; /* @0xa797b */
extern const unsigned char rodata_a7993[]; /* @0xa7993 */
extern const unsigned char rodata_a7999[]; /* @0xa7999 */
extern const unsigned char rodata_a79ab[]; /* @0xa79ab */
extern const unsigned char rodata_a79bf[]; /* @0xa79bf */
extern const unsigned char rodata_a79eb[]; /* @0xa79eb */
extern const unsigned char rodata_a7a10[]; /* @0xa7a10 */
extern const unsigned char rodata_a7a19[]; /* @0xa7a19 */
extern const unsigned char rodata_a7a33[]; /* @0xa7a33 */
extern const unsigned char rodata_a7a52[]; /* @0xa7a52 */
extern const unsigned char rodata_a7aab[]; /* @0xa7aab */
extern const unsigned char rodata_a7ac1[]; /* @0xa7ac1 */
extern const unsigned char rodata_a7af2[]; /* @0xa7af2 */
extern const unsigned char rodata_a7b13[]; /* @0xa7b13 */
extern const unsigned char rodata_a7b29[]; /* @0xa7b29 */
extern const unsigned char rodata_a7b41[]; /* @0xa7b41 */
extern const unsigned char rodata_a7b56[]; /* @0xa7b56 */
extern const unsigned char rodata_a7b64[]; /* @0xa7b64 */
extern const unsigned char rodata_a7b94[]; /* @0xa7b94 */
extern const unsigned char rodata_a7bcc[]; /* @0xa7bcc */
extern const unsigned char rodata_a7bf5[]; /* @0xa7bf5 */
extern const unsigned char rodata_a7c2d[]; /* @0xa7c2d */
extern const unsigned char rodata_a7c4a[]; /* @0xa7c4a */
extern const unsigned char rodata_a7c9c[]; /* @0xa7c9c */
extern const unsigned char rodata_a7cb6[]; /* @0xa7cb6 */
extern const unsigned char rodata_a7cd6[]; /* @0xa7cd6 */
extern const unsigned char rodata_a7cf4[]; /* @0xa7cf4 */
extern const unsigned char rodata_a7d1c[]; /* @0xa7d1c */
extern const unsigned char rodata_a7d55[]; /* @0xa7d55 */
extern const unsigned char rodata_a7d87[]; /* @0xa7d87 */
extern const unsigned char rodata_a7dc5[]; /* @0xa7dc5 */
extern const unsigned char rodata_a7e3d[]; /* @0xa7e3d */
extern const unsigned char rodata_a7e85[]; /* @0xa7e85 */
extern const unsigned char rodata_a7ec3[]; /* @0xa7ec3 */
extern const unsigned char rodata_a7ef6[]; /* @0xa7ef6 */
extern const unsigned char rodata_a7f12[]; /* @0xa7f12 */
extern const unsigned char rodata_a7f41[]; /* @0xa7f41 */
extern const unsigned char rodata_a7f79[]; /* @0xa7f79 */
extern const unsigned char rodata_a7fae[]; /* @0xa7fae */
extern const unsigned char rodata_a8017[]; /* @0xa8017 */
extern const unsigned char rodata_a804b[]; /* @0xa804b */
extern const unsigned char rodata_a806c[]; /* @0xa806c */
extern const unsigned char rodata_a80bc[]; /* @0xa80bc */
extern const unsigned char rodata_a80e3[]; /* @0xa80e3 */
extern const unsigned char rodata_a8146[]; /* @0xa8146 */
extern const unsigned char rodata_a8174[]; /* @0xa8174 */
extern const unsigned char rodata_a819e[]; /* @0xa819e */
extern const unsigned char rodata_a81b7[]; /* @0xa81b7 */
extern const unsigned char rodata_a81d0[]; /* @0xa81d0 */
extern const unsigned char rodata_a81e6[]; /* @0xa81e6 */
extern const unsigned char rodata_a81fa[]; /* @0xa81fa */
extern const unsigned char rodata_a820f[]; /* @0xa820f */
extern const unsigned char rodata_a8221[]; /* @0xa8221 */
extern const unsigned char rodata_a822e[]; /* @0xa822e */
extern const unsigned char rodata_a823b[]; /* @0xa823b */
extern const unsigned char rodata_a8248[]; /* @0xa8248 */
extern const unsigned char rodata_a8255[]; /* @0xa8255 */
extern const unsigned char rodata_a8265[]; /* @0xa8265 */
extern const unsigned char rodata_a829f[]; /* @0xa829f */
extern const unsigned char rodata_a82c4[]; /* @0xa82c4 */
extern const unsigned char rodata_a82e2[]; /* @0xa82e2 */
extern const unsigned char rodata_a8300[]; /* @0xa8300 */
extern const unsigned char rodata_a831f[]; /* @0xa831f */
extern const unsigned char rodata_a833e[]; /* @0xa833e */
extern const unsigned char rodata_a835e[]; /* @0xa835e */
extern const unsigned char rodata_a8373[]; /* @0xa8373 */
extern const unsigned char rodata_a838d[]; /* @0xa838d */
extern const unsigned char rodata_a83aa[]; /* @0xa83aa */
extern const unsigned char rodata_a83ca[]; /* @0xa83ca */
extern const unsigned char rodata_a83d1[]; /* @0xa83d1 */
extern const unsigned char rodata_a83d8[]; /* @0xa83d8 */
extern const unsigned char rodata_a83e9[]; /* @0xa83e9 */
extern const unsigned char rodata_a8400[]; /* @0xa8400 */
extern const unsigned char rodata_a842e[]; /* @0xa842e */
extern const unsigned char rodata_a844e[]; /* @0xa844e */
extern const unsigned char rodata_a8491[]; /* @0xa8491 */
extern const unsigned char rodata_a84a2[]; /* @0xa84a2 */
extern const unsigned char rodata_a84c4[]; /* @0xa84c4 */
extern const unsigned char rodata_a85c4[]; /* @0xa85c4 */
extern const unsigned char rodata_a85d6[]; /* @0xa85d6 */
extern const unsigned char rodata_a8604[]; /* @0xa8604 */
extern const unsigned char rodata_a862c[]; /* @0xa862c */
extern const unsigned char rodata_a8638[]; /* @0xa8638 */
extern const unsigned char rodata_a864e[]; /* @0xa864e */
extern const unsigned char rodata_a866e[]; /* @0xa866e */
extern const unsigned char rodata_a869b[]; /* @0xa869b */
extern const unsigned char rodata_a870b[]; /* @0xa870b */
extern const unsigned char rodata_a8750[]; /* @0xa8750 */
extern const unsigned char rodata_a8762[]; /* @0xa8762 */
extern const unsigned char rodata_a886d[]; /* @0xa886d */
extern const unsigned char rodata_a8884[]; /* @0xa8884 */
extern const unsigned char rodata_a88a9[]; /* @0xa88a9 */
extern const unsigned char rodata_a88d8[]; /* @0xa88d8 */
extern const unsigned char rodata_a892b[]; /* @0xa892b */
extern const unsigned char rodata_a893c[]; /* @0xa893c */
extern const unsigned char rodata_a8952[]; /* @0xa8952 */
extern const unsigned char rodata_a896c[]; /* @0xa896c */
extern const unsigned char rodata_a8994[]; /* @0xa8994 */
extern const unsigned char rodata_a89c8[]; /* @0xa89c8 */
extern const unsigned char rodata_a8a05[]; /* @0xa8a05 */
extern const unsigned char rodata_a8a24[]; /* @0xa8a24 */
extern const unsigned char rodata_a8a33[]; /* @0xa8a33 */
extern const unsigned char rodata_a8a51[]; /* @0xa8a51 */
extern const unsigned char rodata_a8a6f[]; /* @0xa8a6f */
extern const unsigned char rodata_a8a8a[]; /* @0xa8a8a */
extern const unsigned char rodata_a8aa8[]; /* @0xa8aa8 */
extern const unsigned char rodata_a8ab7[]; /* @0xa8ab7 */
extern const unsigned char rodata_a8ac7[]; /* @0xa8ac7 */
extern const unsigned char rodata_a8afb[]; /* @0xa8afb */
extern const unsigned char rodata_a8b01[]; /* @0xa8b01 */
extern const unsigned char rodata_a8b0d[]; /* @0xa8b0d */
extern const unsigned char rodata_a8b19[]; /* @0xa8b19 */
extern const unsigned char rodata_a8b21[]; /* @0xa8b21 */
extern const unsigned char rodata_a8b2b[]; /* @0xa8b2b */
extern const unsigned char rodata_a8b2f[]; /* @0xa8b2f */
extern const unsigned char rodata_a8b37[]; /* @0xa8b37 */
extern const unsigned char rodata_a8b3f[]; /* @0xa8b3f */
extern const unsigned char rodata_a8b67[]; /* @0xa8b67 */
extern const unsigned char rodata_a8b7e[]; /* @0xa8b7e */
extern const unsigned char rodata_a8b8a[]; /* @0xa8b8a */
extern const unsigned char rodata_a8b96[]; /* @0xa8b96 */
extern const unsigned char rodata_a8ba0[]; /* @0xa8ba0 */
extern const unsigned char rodata_a8bcd[]; /* @0xa8bcd */
extern const unsigned char rodata_a8be6[]; /* @0xa8be6 */
extern const unsigned char rodata_a8c09[]; /* @0xa8c09 */
extern const unsigned char rodata_a8c11[]; /* @0xa8c11 */
extern const unsigned char rodata_a8c34[]; /* @0xa8c34 */
extern const unsigned char rodata_a8c37[]; /* @0xa8c37 */
extern const unsigned char rodata_a8c3a[]; /* @0xa8c3a */
extern const unsigned char rodata_a8c57[]; /* @0xa8c57 */
extern const unsigned char rodata_a8c60[]; /* @0xa8c60 */
extern const unsigned char rodata_a8c80[]; /* @0xa8c80 */
extern const unsigned char rodata_a8c97[]; /* @0xa8c97 */
extern const unsigned char rodata_a8cd1[]; /* @0xa8cd1 */
extern const unsigned char rodata_a8ce7[]; /* @0xa8ce7 */
extern const unsigned char rodata_a8cf4[]; /* @0xa8cf4 */
extern const unsigned char rodata_a8d20[]; /* @0xa8d20 */
extern const unsigned char rodata_a8d3a[]; /* @0xa8d3a */
extern const unsigned char rodata_a8d52[]; /* @0xa8d52 */
extern const unsigned char rodata_a8d5d[]; /* @0xa8d5d */
extern const unsigned char rodata_a8d69[]; /* @0xa8d69 */
extern const unsigned char rodata_a8d7f[]; /* @0xa8d7f */
extern const unsigned char rodata_a8da5[]; /* @0xa8da5 */
extern const unsigned char rodata_a8da8[]; /* @0xa8da8 */
extern const unsigned char rodata_a8dc1[]; /* @0xa8dc1 */
extern const unsigned char rodata_a8dde[]; /* @0xa8dde */
extern const unsigned char rodata_a8e02[]; /* @0xa8e02 */
extern const unsigned char rodata_a8e18[]; /* @0xa8e18 */
extern const unsigned char rodata_a8e27[]; /* @0xa8e27 */
extern const unsigned char rodata_a8e48[]; /* @0xa8e48 */
extern const unsigned char rodata_a8e61[]; /* @0xa8e61 */
extern const unsigned char rodata_a8e84[]; /* @0xa8e84 */
extern const unsigned char rodata_a8e98[]; /* @0xa8e98 */
extern const unsigned char rodata_a8ea0[]; /* @0xa8ea0 */
extern const unsigned char rodata_a8ea1[]; /* @0xa8ea1 */
extern const unsigned char rodata_a8eb5[]; /* @0xa8eb5 */
extern const unsigned char rodata_a8ec6[]; /* @0xa8ec6 */
extern const unsigned char rodata_a8edd[]; /* @0xa8edd */
extern const unsigned char rodata_a8eee[]; /* @0xa8eee */
extern const unsigned char rodata_a8f19[]; /* @0xa8f19 */
extern const unsigned char rodata_a8f46[]; /* @0xa8f46 */
extern const unsigned char rodata_a8fb7[]; /* @0xa8fb7 */
extern const unsigned char rodata_a8ff3[]; /* @0xa8ff3 */
extern const unsigned char rodata_a9009[]; /* @0xa9009 */
extern const unsigned char rodata_a9014[]; /* @0xa9014 */
extern const unsigned char rodata_a902d[]; /* @0xa902d */
extern const unsigned char rodata_a904c[]; /* @0xa904c */
extern const unsigned char rodata_a9078[]; /* @0xa9078 */
extern const unsigned char rodata_a9082[]; /* @0xa9082 */
extern const unsigned char rodata_a909f[]; /* @0xa909f */
extern const unsigned char rodata_a90b7[]; /* @0xa90b7 */
extern const unsigned char rodata_a90de[]; /* @0xa90de */
extern const unsigned char rodata_a9100[]; /* @0xa9100 */
extern const unsigned char rodata_a9121[]; /* @0xa9121 */
extern const unsigned char rodata_a9127[]; /* @0xa9127 */
extern const unsigned char rodata_a914d[]; /* @0xa914d */
extern const unsigned char rodata_a9155[]; /* @0xa9155 */
extern const unsigned char rodata_a915b[]; /* @0xa915b */
extern const unsigned char rodata_a916c[]; /* @0xa916c */
extern const unsigned char rodata_a917d[]; /* @0xa917d */
extern const unsigned char rodata_a9195[]; /* @0xa9195 */
extern const unsigned char rodata_a91a4[]; /* @0xa91a4 */
extern const unsigned char rodata_a91c0[]; /* @0xa91c0 */
extern const unsigned char rodata_a91db[]; /* @0xa91db */
extern const unsigned char rodata_a91f2[]; /* @0xa91f2 */
extern const unsigned char rodata_a9206[]; /* @0xa9206 */
extern const unsigned char rodata_a9219[]; /* @0xa9219 */
extern const unsigned char rodata_a922b[]; /* @0xa922b */
extern const unsigned char rodata_a9243[]; /* @0xa9243 */
extern const unsigned char rodata_a926f[]; /* @0xa926f */
extern const unsigned char rodata_a9292[]; /* @0xa9292 */
extern const unsigned char rodata_a92b0[]; /* @0xa92b0 */
extern const unsigned char rodata_a92ee[]; /* @0xa92ee */
extern const unsigned char rodata_a9318[]; /* @0xa9318 */
extern const unsigned char rodata_a933c[]; /* @0xa933c */
extern const unsigned char rodata_a93da[]; /* @0xa93da */
extern const unsigned char rodata_a9437[]; /* @0xa9437 */
extern const unsigned char rodata_a9465[]; /* @0xa9465 */
extern const unsigned char rodata_a947f[]; /* @0xa947f */
extern const unsigned char rodata_a94c5[]; /* @0xa94c5 */
extern const unsigned char rodata_a9529[]; /* @0xa9529 */
extern const unsigned char rodata_a9551[]; /* @0xa9551 */
extern const unsigned char rodata_a957d[]; /* @0xa957d */
extern const unsigned char rodata_a958f[]; /* @0xa958f */
extern const unsigned char rodata_a959e[]; /* @0xa959e */
extern const unsigned char rodata_a95ab[]; /* @0xa95ab */
extern const unsigned char rodata_a95b8[]; /* @0xa95b8 */
extern const unsigned char rodata_a95c9[]; /* @0xa95c9 */
extern const unsigned char rodata_a95d8[]; /* @0xa95d8 */
extern const unsigned char rodata_a95e7[]; /* @0xa95e7 */
extern const unsigned char rodata_a95f9[]; /* @0xa95f9 */
extern const unsigned char rodata_a960d[]; /* @0xa960d */
extern const unsigned char rodata_a9629[]; /* @0xa9629 */
extern const unsigned char rodata_a9654[]; /* @0xa9654 */
extern const unsigned char rodata_a9679[]; /* @0xa9679 */
extern const unsigned char rodata_a9690[]; /* @0xa9690 */
extern const unsigned char rodata_a96ac[]; /* @0xa96ac */
extern const unsigned char rodata_a96c8[]; /* @0xa96c8 */
extern const unsigned char rodata_a96e0[]; /* @0xa96e0 */
extern const unsigned char rodata_a9709[]; /* @0xa9709 */
extern const unsigned char rodata_a9727[]; /* @0xa9727 */
extern const unsigned char rodata_a974b[]; /* @0xa974b */
extern const unsigned char rodata_a9775[]; /* @0xa9775 */
extern const unsigned char rodata_a9797[]; /* @0xa9797 */
extern const unsigned char rodata_a97bb[]; /* @0xa97bb */
extern const unsigned char rodata_a97e4[]; /* @0xa97e4 */
extern const unsigned char rodata_a980b[]; /* @0xa980b */
extern const unsigned char rodata_a981a[]; /* @0xa981a */
extern const unsigned char rodata_a9831[]; /* @0xa9831 */
extern const unsigned char rodata_a9843[]; /* @0xa9843 */
extern const unsigned char rodata_a9855[]; /* @0xa9855 */
extern const unsigned char rodata_a9879[]; /* @0xa9879 */
extern const unsigned char rodata_a989f[]; /* @0xa989f */
extern const unsigned char rodata_a98ce[]; /* @0xa98ce */
extern const unsigned char rodata_a98de[]; /* @0xa98de */
extern const unsigned char rodata_a9935[]; /* @0xa9935 */
extern const unsigned char rodata_a9b76[]; /* @0xa9b76 */
extern const unsigned char rodata_a9c18[]; /* @0xa9c18 */
extern const unsigned char rodata_a9c22[]; /* @0xa9c22 */
extern const unsigned char rodata_a9c63[]; /* @0xa9c63 */
extern const unsigned char rodata_a9da3[]; /* @0xa9da3 */
extern const unsigned char rodata_a9dba[]; /* @0xa9dba */
extern const unsigned char rodata_a9e91[]; /* @0xa9e91 */
extern const unsigned char rodata_a9ebd[]; /* @0xa9ebd */
extern const unsigned char rodata_a9ee1[]; /* @0xa9ee1 */
extern const unsigned char rodata_a9eff[]; /* @0xa9eff */
extern const unsigned char rodata_a9f2a[]; /* @0xa9f2a */
extern const unsigned char rodata_a9f30[]; /* @0xa9f30 */
extern const unsigned char rodata_a9f51[]; /* @0xa9f51 */
extern const unsigned char rodata_a9f6f[]; /* @0xa9f6f */
extern const unsigned char rodata_a9f93[]; /* @0xa9f93 */
extern const unsigned char rodata_a9fcd[]; /* @0xa9fcd */
extern const unsigned char rodata_a9fe6[]; /* @0xa9fe6 */
extern const unsigned char rodata_a9ff7[]; /* @0xa9ff7 */
extern const unsigned char rodata_aa01a[]; /* @0xaa01a */
extern const unsigned char rodata_aa02b[]; /* @0xaa02b */
extern const unsigned char rodata_aa056[]; /* @0xaa056 */
extern const unsigned char rodata_aa070[]; /* @0xaa070 */
extern const unsigned char rodata_aa091[]; /* @0xaa091 */
extern const unsigned char rodata_aa0ae[]; /* @0xaa0ae */
extern const unsigned char rodata_aa0d7[]; /* @0xaa0d7 */
extern const unsigned char rodata_aa112[]; /* @0xaa112 */
extern const unsigned char rodata_aa138[]; /* @0xaa138 */
extern const unsigned char rodata_aa166[]; /* @0xaa166 */
extern const unsigned char rodata_aa1af[]; /* @0xaa1af */
extern const unsigned char rodata_aa204[]; /* @0xaa204 */
extern const unsigned char rodata_aa23d[]; /* @0xaa23d */
extern const unsigned char rodata_aa265[]; /* @0xaa265 */
extern const unsigned char rodata_aa297[]; /* @0xaa297 */
extern const unsigned char rodata_aa2e9[]; /* @0xaa2e9 */
extern const unsigned char rodata_aa341[]; /* @0xaa341 */
extern const unsigned char rodata_aa370[]; /* @0xaa370 */
extern const unsigned char rodata_aa3a8[]; /* @0xaa3a8 */
extern const unsigned char rodata_aa3ed[]; /* @0xaa3ed */
extern const unsigned char rodata_aa412[]; /* @0xaa412 */
extern const unsigned char rodata_aa425[]; /* @0xaa425 */
extern const unsigned char rodata_aa446[]; /* @0xaa446 */
extern const unsigned char rodata_aa466[]; /* @0xaa466 */
extern const unsigned char rodata_aa487[]; /* @0xaa487 */
extern const unsigned char rodata_aa4ea[]; /* @0xaa4ea */
extern const unsigned char rodata_aa4f0[]; /* @0xaa4f0 */
extern const unsigned char rodata_aa517[]; /* @0xaa517 */
extern const unsigned char rodata_aa53a[]; /* @0xaa53a */
extern const unsigned char rodata_aa56c[]; /* @0xaa56c */
extern const unsigned char rodata_aa599[]; /* @0xaa599 */
extern const unsigned char rodata_aa5ab[]; /* @0xaa5ab */
extern const unsigned char rodata_aa600[]; /* @0xaa600 */
extern const unsigned char rodata_aa604[]; /* @0xaa604 */
extern const unsigned char rodata_aa608[]; /* @0xaa608 */
extern const unsigned char rodata_aa60e[]; /* @0xaa60e */
extern const unsigned char rodata_aa611[]; /* @0xaa611 */
extern const unsigned char rodata_aa63d[]; /* @0xaa63d */
extern const unsigned char rodata_aa661[]; /* @0xaa661 */
extern const unsigned char rodata_aa665[]; /* @0xaa665 */
extern const unsigned char rodata_aa669[]; /* @0xaa669 */
extern const unsigned char rodata_aa66d[]; /* @0xaa66d */
extern const unsigned char rodata_aa671[]; /* @0xaa671 */
extern const unsigned char rodata_aa675[]; /* @0xaa675 */
extern const unsigned char rodata_aa679[]; /* @0xaa679 */
extern const unsigned char rodata_aa763[]; /* @0xaa763 */
extern const unsigned char rodata_aa778[]; /* @0xaa778 */
extern const unsigned char rodata_aa7a2[]; /* @0xaa7a2 */
extern const unsigned char rodata_aa7cb[]; /* @0xaa7cb */
extern const unsigned char rodata_aa7f2[]; /* @0xaa7f2 */
extern const unsigned char rodata_aa817[]; /* @0xaa817 */
extern const unsigned char rodata_aa83f[]; /* @0xaa83f */
extern const unsigned char rodata_aa855[]; /* @0xaa855 */
extern const unsigned char rodata_aa86c[]; /* @0xaa86c */
extern const unsigned char rodata_aa891[]; /* @0xaa891 */
extern const unsigned char rodata_aa8c8[]; /* @0xaa8c8 */
extern const unsigned char rodata_aa8eb[]; /* @0xaa8eb */
extern const unsigned char rodata_aa923[]; /* @0xaa923 */
extern const unsigned char rodata_aa951[]; /* @0xaa951 */
extern const unsigned char rodata_aa96d[]; /* @0xaa96d */
extern const unsigned char rodata_aaa01[]; /* @0xaaa01 */
extern const unsigned char rodata_aaa58[]; /* @0xaaa58 */
extern const unsigned char rodata_aaa7f[]; /* @0xaaa7f */
extern const unsigned char rodata_aaaac[]; /* @0xaaaac */
extern const unsigned char rodata_aaab7[]; /* @0xaaab7 */
extern const unsigned char rodata_aaad4[]; /* @0xaaad4 */
extern const unsigned char rodata_aab3b[]; /* @0xaab3b */
extern const unsigned char rodata_aab85[]; /* @0xaab85 */
extern const unsigned char rodata_aab9e[]; /* @0xaab9e */
extern const unsigned char rodata_aabd2[]; /* @0xaabd2 */
extern const unsigned char rodata_aac1e[]; /* @0xaac1e */
extern const unsigned char rodata_aac62[]; /* @0xaac62 */
extern const unsigned char rodata_aac9f[]; /* @0xaac9f */
extern const unsigned char rodata_aacaf[]; /* @0xaacaf */
extern const unsigned char rodata_aacc8[]; /* @0xaacc8 */
extern const unsigned char rodata_aacde[]; /* @0xaacde */
extern const unsigned char rodata_aacee[]; /* @0xaacee */
extern const unsigned char rodata_aad0b[]; /* @0xaad0b */
extern const unsigned char rodata_aad1a[]; /* @0xaad1a */
extern const unsigned char rodata_aad35[]; /* @0xaad35 */
extern const unsigned char rodata_aad4b[]; /* @0xaad4b */
extern const unsigned char rodata_aad64[]; /* @0xaad64 */
extern const unsigned char rodata_aad78[]; /* @0xaad78 */
extern const unsigned char rodata_aad8e[]; /* @0xaad8e */
extern const unsigned char rodata_aadac[]; /* @0xaadac */
extern const unsigned char rodata_aadb9[]; /* @0xaadb9 */
extern const unsigned char rodata_aadd0[]; /* @0xaadd0 */
extern const unsigned char rodata_aade4[]; /* @0xaade4 */
extern const unsigned char rodata_aae00[]; /* @0xaae00 */
extern const unsigned char rodata_aae0f[]; /* @0xaae0f */
extern const unsigned char rodata_aae20[]; /* @0xaae20 */
extern const unsigned char rodata_bb220[]; /* @0xbb220 */
extern const unsigned char rodata_bbfee[]; /* @0xbbfee */
extern const unsigned char rodata_bc04c[]; /* @0xbc04c */
extern const unsigned char rodata_bc083[]; /* @0xbc083 */
extern const unsigned char rodata_bc097[]; /* @0xbc097 */
extern const unsigned char rodata_bc181[]; /* @0xbc181 */
extern const unsigned char rodata_bc26b[]; /* @0xbc26b */
extern const unsigned char rodata_bc355[]; /* @0xbc355 */
extern const unsigned char rodata_bc43f[]; /* @0xbc43f */
extern const unsigned char rodata_bc529[]; /* @0xbc529 */
extern const unsigned char rodata_bc613[]; /* @0xbc613 */
extern const unsigned char rodata_bc6fd[]; /* @0xbc6fd */
extern const unsigned char rodata_bc7ca[]; /* @0xbc7ca */
extern const unsigned char rodata_bc7e0[]; /* @0xbc7e0 */
extern const unsigned char rodata_bc7f1[]; /* @0xbc7f1 */
extern const unsigned char rodata_bccd3[]; /* @0xbccd3 */
extern const unsigned char rodata_bd1b5[]; /* @0xbd1b5 */
extern const unsigned char rodata_bd697[]; /* @0xbd697 */
extern const unsigned char rodata_bdb79[]; /* @0xbdb79 */
extern const unsigned char rodata_be05b[]; /* @0xbe05b */
extern const unsigned char rodata_be53d[]; /* @0xbe53d */
extern const unsigned char rodata_bea1f[]; /* @0xbea1f */
extern const unsigned char rodata_bef01[]; /* @0xbef01 */
extern const unsigned char rodata_bf3e3[]; /* @0xbf3e3 */
extern const unsigned char rodata_bf8c5[]; /* @0xbf8c5 */
extern const unsigned char rodata_bfda7[]; /* @0xbfda7 */
extern const unsigned char rodata_c0289[]; /* @0xc0289 */
extern const unsigned char rodata_c076b[]; /* @0xc076b */
extern const unsigned char rodata_c0c4d[]; /* @0xc0c4d */
extern const unsigned char rodata_c112f[]; /* @0xc112f */
extern const unsigned char rodata_c1611[]; /* @0xc1611 */
extern const unsigned char rodata_c1af3[]; /* @0xc1af3 */
extern const unsigned char rodata_c1fd5[]; /* @0xc1fd5 */
extern const unsigned char rodata_c24b7[]; /* @0xc24b7 */
extern const unsigned char rodata_c2999[]; /* @0xc2999 */
extern const unsigned char rodata_c2e7b[]; /* @0xc2e7b */
extern const unsigned char rodata_c335d[]; /* @0xc335d */
extern const unsigned char rodata_c383f[]; /* @0xc383f */
extern const unsigned char rodata_c3d21[]; /* @0xc3d21 */
extern const unsigned char rodata_c4203[]; /* @0xc4203 */
extern const unsigned char rodata_c46e5[]; /* @0xc46e5 */
extern const unsigned char rodata_c4bc7[]; /* @0xc4bc7 */
extern const unsigned char rodata_c50a9[]; /* @0xc50a9 */
extern const unsigned char rodata_c558b[]; /* @0xc558b */
extern const unsigned char rodata_c5a6d[]; /* @0xc5a6d */
extern const unsigned char rodata_c5f4f[]; /* @0xc5f4f */
extern const unsigned char rodata_c6431[]; /* @0xc6431 */
extern const unsigned char rodata_c6913[]; /* @0xc6913 */
extern const unsigned char rodata_c6df5[]; /* @0xc6df5 */
extern const unsigned char rodata_c72d7[]; /* @0xc72d7 */
extern const unsigned char rodata_c7309[]; /* @0xc7309 */
extern const unsigned char rodata_c733b[]; /* @0xc733b */
extern const unsigned char rodata_c736d[]; /* @0xc736d */
extern const unsigned char rodata_c739f[]; /* @0xc739f */
extern const unsigned char rodata_c73fa[]; /* @0xc73fa */
extern const unsigned char rodata_c74c2[]; /* @0xc74c2 */
extern const unsigned char rodata_c758a[]; /* @0xc758a */
extern const unsigned char rodata_c760a[]; /* @0xc760a */
extern const unsigned char rodata_c768a[]; /* @0xc768a */
extern const unsigned char rodata_c77c4[]; /* @0xc77c4 */
extern const unsigned char rodata_c7956[]; /* @0xc7956 */
extern const unsigned char rodata_c7a90[]; /* @0xc7a90 */
extern const unsigned char rodata_c7c22[]; /* @0xc7c22 */
extern const unsigned char rodata_c7e92[]; /* @0xc7e92 */
extern const unsigned char rodata_c7f5a[]; /* @0xc7f5a */
extern const unsigned char rodata_c805e[]; /* @0xc805e */
extern const unsigned char rodata_c8162[]; /* @0xc8162 */
extern const unsigned char rodata_c81a3[]; /* @0xc81a3 */
extern const unsigned char rodata_c82db[]; /* @0xc82db */
extern const unsigned char rodata_c83a3[]; /* @0xc83a3 */
extern const unsigned char rodata_c846b[]; /* @0xc846b */
extern const unsigned char rodata_c8533[]; /* @0xc8533 */
extern const unsigned char rodata_c85fb[]; /* @0xc85fb */
extern const unsigned char rodata_c86c3[]; /* @0xc86c3 */
extern const unsigned char rodata_c87c7[]; /* @0xc87c7 */
extern const unsigned char rodata_c88cb[]; /* @0xc88cb */
extern const unsigned char rodata_c89cf[]; /* @0xc89cf */
extern const unsigned char rodata_c8a97[]; /* @0xc8a97 */
extern const unsigned char rodata_c8b5f[]; /* @0xc8b5f */
extern const unsigned char rodata_c8c27[]; /* @0xc8c27 */
extern const unsigned char rodata_c8cef[]; /* @0xc8cef */
extern const unsigned char rodata_c8db7[]; /* @0xc8db7 */
extern const unsigned char rodata_c8e7f[]; /* @0xc8e7f */
extern const unsigned char rodata_c8f47[]; /* @0xc8f47 */
extern const unsigned char rodata_c900f[]; /* @0xc900f */
extern const unsigned char rodata_c9113[]; /* @0xc9113 */
extern const unsigned char rodata_c9217[]; /* @0xc9217 */
extern const unsigned char rodata_c931b[]; /* @0xc931b */
extern const unsigned char rodata_c941f[]; /* @0xc941f */
extern const unsigned char rodata_c9523[]; /* @0xc9523 */
extern const unsigned char rodata_c9627[]; /* @0xc9627 */
extern const unsigned char rodata_c972b[]; /* @0xc972b */
extern const unsigned char rodata_c982f[]; /* @0xc982f */
extern const unsigned char rodata_c9933[]; /* @0xc9933 */
extern const unsigned char rodata_c9a37[]; /* @0xc9a37 */
extern const unsigned char rodata_c9b3b[]; /* @0xc9b3b */
extern const unsigned char rodata_c9c3f[]; /* @0xc9c3f */
extern const unsigned char rodata_c9d43[]; /* @0xc9d43 */
extern const unsigned char rodata_c9e47[]; /* @0xc9e47 */
extern const unsigned char rodata_c9f4b[]; /* @0xc9f4b */
extern const unsigned char rodata_ca04f[]; /* @0xca04f */
extern const unsigned char rodata_ca153[]; /* @0xca153 */
extern const unsigned char rodata_cb7fb[]; /* @0xcb7fb */
extern const unsigned char rodata_cc863[]; /* @0xcc863 */
extern const unsigned char rodata_cd5ab[]; /* @0xcd5ab */
extern const unsigned char rodata_ce483[]; /* @0xce483 */
extern const unsigned char rodata_cff13[]; /* @0xcff13 */
extern const unsigned char rodata_d06cf[]; /* @0xd06cf */
extern const unsigned char rodata_d0e9f[]; /* @0xd0e9f */
extern const unsigned char rodata_d15a7[]; /* @0xd15a7 */
extern const unsigned char rodata_d215f[]; /* @0xd215f */
extern const unsigned char rodata_d328f[]; /* @0xd328f */
extern const unsigned char rodata_d43bf[]; /* @0xd43bf */
extern const unsigned char rodata_d7173[]; /* @0xd7173 */
extern const unsigned char rodata_d71ad[]; /* @0xd71ad */
extern const unsigned char rodata_d71e3[]; /* @0xd71e3 */
extern const unsigned char rodata_d71f9[]; /* @0xd71f9 */
extern const unsigned char rodata_d720f[]; /* @0xd720f */
extern const unsigned char rodata_d721e[]; /* @0xd721e */
extern const unsigned char rodata_d723a[]; /* @0xd723a */
extern const unsigned char rodata_d7251[]; /* @0xd7251 */
extern const unsigned char rodata_d728d[]; /* @0xd728d */
extern const unsigned char rodata_d7272[]; /* @0xd7272 */
extern const unsigned char rodata_d72ac[]; /* @0xd72ac */
extern const unsigned char rodata_d72bb[]; /* @0xd72bb */
extern const unsigned char rodata_d72c4[]; /* @0xd72c4 */
extern const unsigned char rodata_d72d1[]; /* @0xd72d1 */
extern const unsigned char rodata_d72e9[]; /* @0xd72e9 */
extern const unsigned char rodata_d72db[]; /* @0xd72db */
extern const unsigned char rodata_d7310[]; /* @0xd7310 */
extern const unsigned char rodata_d732c[]; /* @0xd732c */
extern const unsigned char rodata_d7347[]; /* @0xd7347 */
extern const unsigned char rodata_d7374[]; /* @0xd7374 */
extern const unsigned char rodata_d7383[]; /* @0xd7383 */
extern const unsigned char rodata_d73a1[]; /* @0xd73a1 */
extern const unsigned char rodata_d73bc[]; /* @0xd73bc */
extern const unsigned char rodata_d73e0[]; /* @0xd73e0 */
extern const unsigned char rodata_d73f8[]; /* @0xd73f8 */
extern const unsigned char rodata_d7409[]; /* @0xd7409 */
extern const unsigned char rodata_d741b[]; /* @0xd741b */
extern const unsigned char rodata_d7426[]; /* @0xd7426 */
extern const unsigned char rodata_d7441[]; /* @0xd7441 */
extern const unsigned char rodata_d7459[]; /* @0xd7459 */
extern const unsigned char rodata_d748d[]; /* @0xd748d */
extern const unsigned char rodata_d7499[]; /* @0xd7499 */
extern const unsigned char rodata_d74af[]; /* @0xd74af */
extern const unsigned char rodata_d74bd[]; /* @0xd74bd */
extern const unsigned char rodata_d74d7[]; /* @0xd74d7 */
extern const unsigned char rodata_d74f4[]; /* @0xd74f4 */
extern const unsigned char rodata_d750b[]; /* @0xd750b */
extern const unsigned char rodata_d752a[]; /* @0xd752a */
extern const unsigned char rodata_d753a[]; /* @0xd753a */
extern const unsigned char rodata_e123a[]; /* @0xe123a */
extern const unsigned char rodata_e17da[]; /* @0xe17da */
extern const unsigned char rodata_e4408[]; /* @0xe4408 */
extern const unsigned char rodata_e5248[]; /* @0xe5248 */
extern const unsigned char rodata_e5f62[]; /* @0xe5f62 */
extern const unsigned char rodata_ef01c[]; /* @0xef01c */
extern const unsigned char rodata_ef058[]; /* @0xef058 */
extern const unsigned char rodata_ef081[]; /* @0xef081 */
extern const unsigned char rodata_ef0a1[]; /* @0xef0a1 */
extern const unsigned char rodata_ef0c9[]; /* @0xef0c9 */
extern const unsigned char rodata_ef0fb[]; /* @0xef0fb */
extern const unsigned char rodata_ef135[]; /* @0xef135 */
extern const unsigned char rodata_ef16d[]; /* @0xef16d */
extern const unsigned char rodata_ef1a8[]; /* @0xef1a8 */
extern const unsigned char rodata_ef1ea[]; /* @0xef1ea */
extern const unsigned char rodata_ef214[]; /* @0xef214 */
extern const unsigned char rodata_ef260[]; /* @0xef260 */
extern const unsigned char rodata_ef29b[]; /* @0xef29b */
extern const unsigned char rodata_ef2df[]; /* @0xef2df */
extern const unsigned char rodata_ef2fc[]; /* @0xef2fc */
extern const unsigned char rodata_ef338[]; /* @0xef338 */
extern const unsigned char rodata_ef377[]; /* @0xef377 */
extern const unsigned char rodata_ef3e2[]; /* @0xef3e2 */
extern const unsigned char rodata_ef40d[]; /* @0xef40d */
extern const unsigned char rodata_ef437[]; /* @0xef437 */
extern const unsigned char rodata_ef472[]; /* @0xef472 */
extern const unsigned char rodata_ef4d9[]; /* @0xef4d9 */
extern const unsigned char rodata_ef4fa[]; /* @0xef4fa */
extern const unsigned char rodata_ef519[]; /* @0xef519 */
extern const unsigned char rodata_ef553[]; /* @0xef553 */
extern const unsigned char rodata_ef596[]; /* @0xef596 */
extern const unsigned char rodata_ef59e[]; /* @0xef59e */
extern const unsigned char rodata_ef5df[]; /* @0xef5df */
extern const unsigned char rodata_ef603[]; /* @0xef603 */
extern const unsigned char rodata_ef644[]; /* @0xef644 */
extern const unsigned char rodata_ef694[]; /* @0xef694 */
extern const unsigned char rodata_ef6b0[]; /* @0xef6b0 */
extern const unsigned char rodata_ef6d4[]; /* @0xef6d4 */
extern const unsigned char rodata_ef6f2[]; /* @0xef6f2 */
extern const unsigned char rodata_ef707[]; /* @0xef707 */
extern const unsigned char rodata_ef71d[]; /* @0xef71d */
extern const unsigned char rodata_ef736[]; /* @0xef736 */
extern const unsigned char rodata_ef750[]; /* @0xef750 */
extern const unsigned char rodata_ef76f[]; /* @0xef76f */
extern const unsigned char rodata_ef784[]; /* @0xef784 */
extern const unsigned char rodata_ef7a0[]; /* @0xef7a0 */
extern const unsigned char rodata_ef7bb[]; /* @0xef7bb */
extern const unsigned char rodata_ef7ef[]; /* @0xef7ef */
extern const unsigned char rodata_ef87a[]; /* @0xef87a */
extern const unsigned char rodata_ef8d7[]; /* @0xef8d7 */
extern const unsigned char rodata_ef937[]; /* @0xef937 */
extern const unsigned char rodata_ef9bf[]; /* @0xef9bf */
extern const unsigned char rodata_efa29[]; /* @0xefa29 */
extern const unsigned char rodata_efaa5[]; /* @0xefaa5 */
extern const unsigned char rodata_efb0e[]; /* @0xefb0e */
extern const unsigned char rodata_efb2e[]; /* @0xefb2e */
extern const unsigned char rodata_efb50[]; /* @0xefb50 */
extern const unsigned char rodata_efb7a[]; /* @0xefb7a */
extern const unsigned char rodata_efb9f[]; /* @0xefb9f */
extern const unsigned char rodata_efbb7[]; /* @0xefbb7 */
extern const unsigned char rodata_efbe5[]; /* @0xefbe5 */
extern const unsigned char rodata_efc00[]; /* @0xefc00 */
extern const unsigned char rodata_efc2d[]; /* @0xefc2d */
extern const unsigned char rodata_efc62[]; /* @0xefc62 */
extern const unsigned char rodata_efc92[]; /* @0xefc92 */
extern const unsigned char rodata_efcdf[]; /* @0xefcdf */
extern const unsigned char rodata_efd03[]; /* @0xefd03 */
extern const unsigned char rodata_efd2d[]; /* @0xefd2d */
extern const unsigned char rodata_efd6f[]; /* @0xefd6f */
extern const unsigned char rodata_efe74[]; /* @0xefe74 */
extern const unsigned char rodata_efebc[]; /* @0xefebc */
extern const unsigned char rodata_eff70[]; /* @0xeff70 */
extern const unsigned char rodata_effaf[]; /* @0xeffaf */
extern const unsigned char rodata_effd2[]; /* @0xeffd2 */
extern const unsigned char rodata_efff4[]; /* @0xefff4 */
extern const unsigned char rodata_f0000[]; /* @0xf0000 */
extern const unsigned char rodata_f000[]; /* @0xf000 */
extern const unsigned char rodata_f001c[]; /* @0xf001c */
extern const unsigned char rodata_f0044[]; /* @0xf0044 */
extern const unsigned char rodata_f006d[]; /* @0xf006d */
extern const unsigned char rodata_f008c[]; /* @0xf008c */
extern const unsigned char rodata_f00bb[]; /* @0xf00bb */
extern const unsigned char rodata_f00ea[]; /* @0xf00ea */
extern const unsigned char rodata_f0126[]; /* @0xf0126 */
extern const unsigned char rodata_f0139[]; /* @0xf0139 */
extern const unsigned char rodata_f0151[]; /* @0xf0151 */
extern const unsigned char rodata_f0164[]; /* @0xf0164 */
extern const unsigned char rodata_f0177[]; /* @0xf0177 */
extern const unsigned char rodata_f018c[]; /* @0xf018c */
extern const unsigned char rodata_f019a[]; /* @0xf019a */
extern const unsigned char rodata_f01aa[]; /* @0xf01aa */
extern const unsigned char rodata_f01c1[]; /* @0xf01c1 */
extern const unsigned char rodata_f01d3[]; /* @0xf01d3 */
extern const unsigned char rodata_f01eb[]; /* @0xf01eb */
extern const unsigned char rodata_f0229[]; /* @0xf0229 */
extern const unsigned char rodata_f024d[]; /* @0xf024d */
extern const unsigned char rodata_f028c[]; /* @0xf028c */
extern const unsigned char rodata_f0297[]; /* @0xf0297 */
extern const unsigned char rodata_f02a3[]; /* @0xf02a3 */
extern const unsigned char rodata_f02a5[]; /* @0xf02a5 */
extern const unsigned char rodata_f02ad[]; /* @0xf02ad */
extern const unsigned char rodata_f02d2[]; /* @0xf02d2 */
extern const unsigned char rodata_f02e7[]; /* @0xf02e7 */
extern const unsigned char rodata_f02ff[]; /* @0xf02ff */
extern const unsigned char rodata_f0310[]; /* @0xf0310 */
extern const unsigned char rodata_f0337[]; /* @0xf0337 */
extern const unsigned char rodata_f0369[]; /* @0xf0369 */
extern const unsigned char rodata_f038d[]; /* @0xf038d */
extern const unsigned char rodata_f03c4[]; /* @0xf03c4 */
extern const unsigned char rodata_f0416[]; /* @0xf0416 */
extern const unsigned char rodata_f043b[]; /* @0xf043b */
extern const unsigned char rodata_f0459[]; /* @0xf0459 */
extern const unsigned char rodata_f0475[]; /* @0xf0475 */
extern const unsigned char rodata_f0492[]; /* @0xf0492 */
extern const unsigned char rodata_f04a9[]; /* @0xf04a9 */
extern const unsigned char rodata_f04c1[]; /* @0xf04c1 */
extern const unsigned char rodata_f04ef[]; /* @0xf04ef */
extern const unsigned char rodata_f0584[]; /* @0xf0584 */
extern const unsigned char rodata_f059f[]; /* @0xf059f */
extern const unsigned char rodata_f0642[]; /* @0xf0642 */
extern const unsigned char rodata_f0661[]; /* @0xf0661 */
extern const unsigned char rodata_f0692[]; /* @0xf0692 */
extern const unsigned char rodata_f06b3[]; /* @0xf06b3 */
extern const unsigned char rodata_f06c4[]; /* @0xf06c4 */
extern const unsigned char rodata_f06fc[]; /* @0xf06fc */
extern const unsigned char rodata_f0722[]; /* @0xf0722 */
extern const unsigned char rodata_f075e[]; /* @0xf075e */
extern const unsigned char rodata_f0779[]; /* @0xf0779 */
extern const unsigned char rodata_f0796[]; /* @0xf0796 */
extern const unsigned char rodata_f07b7[]; /* @0xf07b7 */
extern const unsigned char rodata_f07d0[]; /* @0xf07d0 */
extern const unsigned char rodata_f07f9[]; /* @0xf07f9 */
extern const unsigned char rodata_f0824[]; /* @0xf0824 */
extern const unsigned char rodata_f0846[]; /* @0xf0846 */
extern const unsigned char rodata_f0852[]; /* @0xf0852 */
extern const unsigned char rodata_f0875[]; /* @0xf0875 */
extern const unsigned char rodata_f088c[]; /* @0xf088c */
extern const unsigned char rodata_f08a2[]; /* @0xf08a2 */
extern const unsigned char rodata_f08b1[]; /* @0xf08b1 */
extern const unsigned char rodata_f08c7[]; /* @0xf08c7 */
extern const unsigned char rodata_f08f4[]; /* @0xf08f4 */
extern const unsigned char rodata_f090b[]; /* @0xf090b */
extern const unsigned char rodata_f0920[]; /* @0xf0920 */
extern const unsigned char rodata_f0935[]; /* @0xf0935 */
extern const unsigned char rodata_f094b[]; /* @0xf094b */
extern const unsigned char rodata_f0959[]; /* @0xf0959 */
extern const unsigned char rodata_f0982[]; /* @0xf0982 */
extern const unsigned char rodata_f09d1[]; /* @0xf09d1 */
extern const unsigned char rodata_f0a04[]; /* @0xf0a04 */
extern const unsigned char rodata_f0a2b[]; /* @0xf0a2b */
extern const unsigned char rodata_f0a5d[]; /* @0xf0a5d */
extern const unsigned char rodata_f0a68[]; /* @0xf0a68 */
extern const unsigned char rodata_f0a90[]; /* @0xf0a90 */
extern const unsigned char rodata_f0ac7[]; /* @0xf0ac7 */
extern const unsigned char rodata_f0ae4[]; /* @0xf0ae4 */
extern const unsigned char rodata_f0af8[]; /* @0xf0af8 */
extern const unsigned char rodata_f0b1a[]; /* @0xf0b1a */
extern const unsigned char rodata_f0b37[]; /* @0xf0b37 */
extern const unsigned char rodata_f0b4f[]; /* @0xf0b4f */
extern const unsigned char rodata_f0b63[]; /* @0xf0b63 */
extern const unsigned char rodata_f0b86[]; /* @0xf0b86 */
extern const unsigned char rodata_f0b9d[]; /* @0xf0b9d */
extern const unsigned char rodata_f0baf[]; /* @0xf0baf */
extern const unsigned char rodata_f0bc0[]; /* @0xf0bc0 */
extern const unsigned char rodata_f0be7[]; /* @0xf0be7 */
extern const unsigned char rodata_f0c14[]; /* @0xf0c14 */
extern const unsigned char rodata_f0c32[]; /* @0xf0c32 */
extern const unsigned char rodata_f0cae[]; /* @0xf0cae */
extern const unsigned char rodata_f0cdb[]; /* @0xf0cdb */
extern const unsigned char rodata_f0cff[]; /* @0xf0cff */
extern const unsigned char rodata_f0d20[]; /* @0xf0d20 */
extern const unsigned char rodata_f0d3f[]; /* @0xf0d3f */
extern const unsigned char rodata_f0da7[]; /* @0xf0da7 */
extern const unsigned char rodata_f0ddf[]; /* @0xf0ddf */
extern const unsigned char rodata_f0dff[]; /* @0xf0dff */
extern const unsigned char rodata_f0e3e[]; /* @0xf0e3e */
extern const unsigned char rodata_f0e6a[]; /* @0xf0e6a */
extern const unsigned char rodata_f0e73[]; /* @0xf0e73 */
extern const unsigned char rodata_f0ed2[]; /* @0xf0ed2 */
extern const unsigned char rodata_f0ed7[]; /* @0xf0ed7 */
extern const unsigned char rodata_f0ee3[]; /* @0xf0ee3 */
extern const unsigned char rodata_f0ee7[]; /* @0xf0ee7 */
extern const unsigned char rodata_f0ef0[]; /* @0xf0ef0 */
extern const unsigned char rodata_f0f0c[]; /* @0xf0f0c */
extern const unsigned char rodata_f0f12[]; /* @0xf0f12 */
extern const unsigned char rodata_f0f16[]; /* @0xf0f16 */
extern const unsigned char rodata_f0f1b[]; /* @0xf0f1b */
extern const unsigned char rodata_f0f24[]; /* @0xf0f24 */
extern const unsigned char rodata_f0f26[]; /* @0xf0f26 */
extern const unsigned char rodata_f0f29[]; /* @0xf0f29 */
extern const unsigned char rodata_f0f45[]; /* @0xf0f45 */
extern const unsigned char rodata_f0f61[]; /* @0xf0f61 */
extern const unsigned char rodata_f0f71[]; /* @0xf0f71 */
extern const unsigned char rodata_f0faf[]; /* @0xf0faf */
extern const unsigned char rodata_f0fed[]; /* @0xf0fed */
extern const unsigned char rodata_f0ff1[]; /* @0xf0ff1 */
extern const unsigned char rodata_f1015[]; /* @0xf1015 */
extern const unsigned char rodata_f1031[]; /* @0xf1031 */
extern const unsigned char rodata_f1036[]; /* @0xf1036 */
extern const unsigned char rodata_f1052[]; /* @0xf1052 */
extern const unsigned char rodata_f1080[]; /* @0xf1080 */
extern const unsigned char rodata_f10a4[]; /* @0xf10a4 */
extern const unsigned char rodata_f10ba[]; /* @0xf10ba */
extern const unsigned char rodata_f10ce[]; /* @0xf10ce */
extern const unsigned char rodata_f1105[]; /* @0xf1105 */
extern const unsigned char rodata_f1126[]; /* @0xf1126 */
extern const unsigned char rodata_f1158[]; /* @0xf1158 */
extern const unsigned char rodata_f1180[]; /* @0xf1180 */
extern const unsigned char rodata_f11a5[]; /* @0xf11a5 */
extern const unsigned char rodata_f11bc[]; /* @0xf11bc */
extern const unsigned char rodata_f11e7[]; /* @0xf11e7 */
extern const unsigned char rodata_f1237[]; /* @0xf1237 */
extern const unsigned char rodata_f1253[]; /* @0xf1253 */
extern const unsigned char rodata_f1270[]; /* @0xf1270 */
extern const unsigned char rodata_f1284[]; /* @0xf1284 */
extern const unsigned char rodata_f1299[]; /* @0xf1299 */
extern const unsigned char rodata_f12bb[]; /* @0xf12bb */
extern const unsigned char rodata_f13bc[]; /* @0xf13bc */
extern const unsigned char rodata_f13e5[]; /* @0xf13e5 */
extern const unsigned char rodata_f1404[]; /* @0xf1404 */
extern const unsigned char rodata_f1432[]; /* @0xf1432 */
extern const unsigned char rodata_f1459[]; /* @0xf1459 */
extern const unsigned char rodata_f1484[]; /* @0xf1484 */
extern const unsigned char rodata_f14c2[]; /* @0xf14c2 */
extern const unsigned char rodata_f1541[]; /* @0xf1541 */
extern const unsigned char rodata_f154a[]; /* @0xf154a */
extern const unsigned char rodata_f155e[]; /* @0xf155e */
extern const unsigned char rodata_f1574[]; /* @0xf1574 */
extern const unsigned char rodata_f1590[]; /* @0xf1590 */
extern const unsigned char rodata_f159e[]; /* @0xf159e */
extern const unsigned char rodata_f15cc[]; /* @0xf15cc */
extern const unsigned char rodata_f15f9[]; /* @0xf15f9 */
extern const unsigned char rodata_f1625[]; /* @0xf1625 */
extern const unsigned char rodata_f1681[]; /* @0xf1681 */
extern const unsigned char rodata_f16be[]; /* @0xf16be */
extern const unsigned char rodata_f1710[]; /* @0xf1710 */
extern const unsigned char rodata_f1722[]; /* @0xf1722 */
extern const unsigned char rodata_f1734[]; /* @0xf1734 */
extern const unsigned char rodata_f1754[]; /* @0xf1754 */
extern const unsigned char rodata_f176a[]; /* @0xf176a */
extern const unsigned char rodata_f17a1[]; /* @0xf17a1 */
extern const unsigned char rodata_f17c3[]; /* @0xf17c3 */
extern const unsigned char rodata_f17eb[]; /* @0xf17eb */
extern const unsigned char rodata_f1823[]; /* @0xf1823 */
extern const unsigned char rodata_f1885[]; /* @0xf1885 */
extern const unsigned char rodata_f18bd[]; /* @0xf18bd */
extern const unsigned char rodata_f18e0[]; /* @0xf18e0 */
extern const unsigned char rodata_f18ff[]; /* @0xf18ff */
extern const unsigned char rodata_f1920[]; /* @0xf1920 */
extern const unsigned char rodata_f1968[]; /* @0xf1968 */
extern const unsigned char rodata_f1abb[]; /* @0xf1abb */
extern const unsigned char rodata_f1aea[]; /* @0xf1aea */
extern const unsigned char rodata_f1b19[]; /* @0xf1b19 */
extern const unsigned char rodata_f1b28[]; /* @0xf1b28 */
extern const unsigned char rodata_f1b6b[]; /* @0xf1b6b */
extern const unsigned char rodata_f1b7a[]; /* @0xf1b7a */
extern const unsigned char rodata_f1ba8[]; /* @0xf1ba8 */
extern const unsigned char rodata_f1bde[]; /* @0xf1bde */
extern const unsigned char rodata_f1bf9[]; /* @0xf1bf9 */
extern const unsigned char rodata_f1c39[]; /* @0xf1c39 */
extern const unsigned char rodata_f1c4f[]; /* @0xf1c4f */
extern const unsigned char rodata_f1c82[]; /* @0xf1c82 */
extern const unsigned char rodata_f1c95[]; /* @0xf1c95 */
extern const unsigned char rodata_f1cad[]; /* @0xf1cad */
extern const unsigned char rodata_f1cc3[]; /* @0xf1cc3 */
extern const unsigned char rodata_f1ce2[]; /* @0xf1ce2 */
extern const unsigned char rodata_f1d11[]; /* @0xf1d11 */
extern const unsigned char rodata_f1d4b[]; /* @0xf1d4b */
extern const unsigned char rodata_f1d95[]; /* @0xf1d95 */
extern const unsigned char rodata_f1df9[]; /* @0xf1df9 */
extern const unsigned char rodata_f1e0f[]; /* @0xf1e0f */
extern const unsigned char rodata_f1e20[]; /* @0xf1e20 */
extern const unsigned char rodata_f1e39[]; /* @0xf1e39 */
extern const unsigned char rodata_f1e4e[]; /* @0xf1e4e */
extern const unsigned char rodata_f1e69[]; /* @0xf1e69 */
extern const unsigned char rodata_f1e81[]; /* @0xf1e81 */
extern const unsigned char rodata_f1e99[]; /* @0xf1e99 */
extern const unsigned char rodata_f1eac[]; /* @0xf1eac */
extern const unsigned char rodata_f1ec6[]; /* @0xf1ec6 */
extern const unsigned char rodata_f1ef0[]; /* @0xf1ef0 */
extern const unsigned char rodata_f1f0e[]; /* @0xf1f0e */
extern const unsigned char rodata_f1f33[]; /* @0xf1f33 */
extern const unsigned char rodata_f1f4d[]; /* @0xf1f4d */
extern const unsigned char rodata_f1fa6[]; /* @0xf1fa6 */
extern const unsigned char rodata_f1fd1[]; /* @0xf1fd1 */
extern const unsigned char rodata_f1fe4[]; /* @0xf1fe4 */
extern const unsigned char rodata_f2022[]; /* @0xf2022 */
extern const unsigned char rodata_f2039[]; /* @0xf2039 */
extern const unsigned char rodata_f205a[]; /* @0xf205a */
extern const unsigned char rodata_f2068[]; /* @0xf2068 */
extern const unsigned char rodata_f2087[]; /* @0xf2087 */
extern const unsigned char rodata_f20a3[]; /* @0xf20a3 */
extern const unsigned char rodata_f20c7[]; /* @0xf20c7 */
extern const unsigned char rodata_f20f7[]; /* @0xf20f7 */
extern const unsigned char rodata_f211b[]; /* @0xf211b */
extern const unsigned char rodata_f212c[]; /* @0xf212c */
extern const unsigned char rodata_f2132[]; /* @0xf2132 */
extern const unsigned char rodata_f2158[]; /* @0xf2158 */
extern const unsigned char rodata_f217b[]; /* @0xf217b */
extern const unsigned char rodata_f219e[]; /* @0xf219e */
extern const unsigned char rodata_f2201[]; /* @0xf2201 */
extern const unsigned char rodata_f22d5[]; /* @0xf22d5 */
extern const unsigned char rodata_f23d3[]; /* @0xf23d3 */
extern const unsigned char rodata_f23d4[]; /* @0xf23d4 */
extern const unsigned char rodata_f240f[]; /* @0xf240f */
extern const unsigned char rodata_f2432[]; /* @0xf2432 */
extern const unsigned char rodata_f2558[]; /* @0xf2558 */
extern const unsigned char rodata_f255b[]; /* @0xf255b */
extern const unsigned char rodata_f2561[]; /* @0xf2561 */
extern const unsigned char rodata_f25c5[]; /* @0xf25c5 */
extern const unsigned char rodata_f25e2[]; /* @0xf25e2 */
extern const unsigned char rodata_f25fb[]; /* @0xf25fb */
extern const unsigned char rodata_f261f[]; /* @0xf261f */
extern const unsigned char rodata_f2634[]; /* @0xf2634 */
extern const unsigned char rodata_f26c1[]; /* @0xf26c1 */
extern const unsigned char rodata_f26c4[]; /* @0xf26c4 */
extern const unsigned char rodata_f26e7[]; /* @0xf26e7 */
extern const unsigned char rodata_f270e[]; /* @0xf270e */
extern const unsigned char rodata_f272f[]; /* @0xf272f */
extern const unsigned char rodata_f2734[]; /* @0xf2734 */
extern const unsigned char rodata_f273a[]; /* @0xf273a */
extern const unsigned char rodata_f2743[]; /* @0xf2743 */
extern const unsigned char rodata_f274b[]; /* @0xf274b */
extern const unsigned char rodata_f2755[]; /* @0xf2755 */
extern const unsigned char rodata_f275f[]; /* @0xf275f */
extern const unsigned char rodata_f2766[]; /* @0xf2766 */
extern const unsigned char rodata_f2772[]; /* @0xf2772 */
extern const unsigned char rodata_f27cc[]; /* @0xf27cc */
extern const unsigned char rodata_f27cf[]; /* @0xf27cf */
extern const unsigned char rodata_f27db[]; /* @0xf27db */
extern const unsigned char rodata_f27df[]; /* @0xf27df */
extern const unsigned char rodata_f27e3[]; /* @0xf27e3 */
extern const unsigned char rodata_f27eb[]; /* @0xf27eb */
extern const unsigned char rodata_f280b[]; /* @0xf280b */
extern const unsigned char rodata_f289a[]; /* @0xf289a */
extern const unsigned char rodata_f28b4[]; /* @0xf28b4 */
extern const unsigned char rodata_f28d4[]; /* @0xf28d4 */
extern const unsigned char rodata_f2901[]; /* @0xf2901 */
extern const unsigned char rodata_f293b[]; /* @0xf293b */
extern const unsigned char rodata_f2963[]; /* @0xf2963 */
extern const unsigned char rodata_f2a45[]; /* @0xf2a45 */
extern const unsigned char rodata_f2a79[]; /* @0xf2a79 */
extern const unsigned char rodata_f2a99[]; /* @0xf2a99 */
extern const unsigned char rodata_f2abf[]; /* @0xf2abf */
extern const unsigned char rodata_f2af8[]; /* @0xf2af8 */
extern const unsigned char rodata_f2b15[]; /* @0xf2b15 */
extern const unsigned char rodata_f2b33[]; /* @0xf2b33 */
extern const unsigned char rodata_f2b3a[]; /* @0xf2b3a */
extern const unsigned char rodata_f2b41[]; /* @0xf2b41 */
extern const unsigned char rodata_f2b47[]; /* @0xf2b47 */
extern const unsigned char rodata_f2b65[]; /* @0xf2b65 */
extern const unsigned char rodata_f2b86[]; /* @0xf2b86 */
extern const unsigned char rodata_f2baa[]; /* @0xf2baa */
extern const unsigned char rodata_f2bcf[]; /* @0xf2bcf */
extern const unsigned char rodata_f2c01[]; /* @0xf2c01 */
extern const unsigned char rodata_f2c25[]; /* @0xf2c25 */
extern const unsigned char rodata_f2c46[]; /* @0xf2c46 */
extern const unsigned char rodata_f2c6b[]; /* @0xf2c6b */
extern const unsigned char rodata_f2c71[]; /* @0xf2c71 */
extern const unsigned char rodata_f2c8c[]; /* @0xf2c8c */
extern const unsigned char rodata_f2cc8[]; /* @0xf2cc8 */
extern const unsigned char rodata_f2d9d[]; /* @0xf2d9d */
extern const unsigned char rodata_f2db7[]; /* @0xf2db7 */
extern const unsigned char rodata_f2ddb[]; /* @0xf2ddb */
extern const unsigned char rodata_f2df8[]; /* @0xf2df8 */
extern const unsigned char rodata_f2e3c[]; /* @0xf2e3c */
extern const unsigned char rodata_f2e62[]; /* @0xf2e62 */
extern const unsigned char rodata_f2e84[]; /* @0xf2e84 */
extern const unsigned char rodata_f2eb8[]; /* @0xf2eb8 */
extern const unsigned char rodata_f2ed1[]; /* @0xf2ed1 */
extern const unsigned char rodata_f2ef5[]; /* @0xf2ef5 */
extern const unsigned char rodata_f2f17[]; /* @0xf2f17 */
extern const unsigned char rodata_f2f45[]; /* @0xf2f45 */
extern const unsigned char rodata_f2f59[]; /* @0xf2f59 */
extern const unsigned char rodata_f2f8e[]; /* @0xf2f8e */
extern const unsigned char rodata_f301e[]; /* @0xf301e */
extern const unsigned char rodata_f304a[]; /* @0xf304a */
extern const unsigned char rodata_f30dd[]; /* @0xf30dd */
extern const unsigned char rodata_f3103[]; /* @0xf3103 */
extern const unsigned char rodata_f3125[]; /* @0xf3125 */
extern const unsigned char rodata_f313c[]; /* @0xf313c */
extern const unsigned char rodata_f3157[]; /* @0xf3157 */
extern const unsigned char rodata_f3191[]; /* @0xf3191 */
extern const unsigned char rodata_f31a5[]; /* @0xf31a5 */
extern const unsigned char rodata_f31a9[]; /* @0xf31a9 */
extern const unsigned char rodata_f31b8[]; /* @0xf31b8 */
extern const unsigned char rodata_f31c9[]; /* @0xf31c9 */
extern const unsigned char rodata_f3207[]; /* @0xf3207 */
extern const unsigned char rodata_f322e[]; /* @0xf322e */
extern const unsigned char rodata_f325b[]; /* @0xf325b */
extern const unsigned char rodata_f327f[]; /* @0xf327f */
extern const unsigned char rodata_f32f7[]; /* @0xf32f7 */
extern const unsigned char rodata_f3324[]; /* @0xf3324 */
extern const unsigned char rodata_f3376[]; /* @0xf3376 */
extern const unsigned char rodata_f338f[]; /* @0xf338f */
extern const unsigned char rodata_f3395[]; /* @0xf3395 */
extern const unsigned char rodata_f339b[]; /* @0xf339b */
extern const unsigned char rodata_f33b7[]; /* @0xf33b7 */
extern const unsigned char rodata_f33d4[]; /* @0xf33d4 */
extern const unsigned char rodata_f33e4[]; /* @0xf33e4 */
extern const unsigned char rodata_f341d[]; /* @0xf341d */
extern const unsigned char rodata_f3449[]; /* @0xf3449 */
extern const unsigned char rodata_f349f[]; /* @0xf349f */
extern const unsigned char rodata_f3509[]; /* @0xf3509 */
extern const unsigned char rodata_f3537[]; /* @0xf3537 */
extern const unsigned char rodata_f354f[]; /* @0xf354f */
extern const unsigned char rodata_f3572[]; /* @0xf3572 */
extern const unsigned char rodata_f358a[]; /* @0xf358a */
extern const unsigned char rodata_f35bf[]; /* @0xf35bf */
extern const unsigned char rodata_f35e4[]; /* @0xf35e4 */
extern const unsigned char rodata_f3615[]; /* @0xf3615 */
extern const unsigned char rodata_f3630[]; /* @0xf3630 */
extern const unsigned char rodata_f3635[]; /* @0xf3635 */
extern const unsigned char rodata_f3655[]; /* @0xf3655 */
extern const unsigned char rodata_f367f[]; /* @0xf367f */
extern const unsigned char rodata_f369a[]; /* @0xf369a */
extern const unsigned char rodata_f36b3[]; /* @0xf36b3 */
extern const unsigned char rodata_f36e0[]; /* @0xf36e0 */
extern const unsigned char rodata_f3705[]; /* @0xf3705 */
extern const unsigned char rodata_f3733[]; /* @0xf3733 */
extern const unsigned char rodata_f374c[]; /* @0xf374c */
extern const unsigned char rodata_f376a[]; /* @0xf376a */
extern const unsigned char rodata_f3796[]; /* @0xf3796 */
extern const unsigned char rodata_f37b6[]; /* @0xf37b6 */
extern const unsigned char rodata_f37df[]; /* @0xf37df */
extern const unsigned char rodata_f3804[]; /* @0xf3804 */
extern const unsigned char rodata_f381d[]; /* @0xf381d */
extern const unsigned char rodata_f3857[]; /* @0xf3857 */
extern const unsigned char rodata_f3894[]; /* @0xf3894 */
extern const unsigned char rodata_f38c6[]; /* @0xf38c6 */
extern const unsigned char rodata_f391d[]; /* @0xf391d */
extern const unsigned char rodata_f394f[]; /* @0xf394f */
extern const unsigned char rodata_f3966[]; /* @0xf3966 */
extern const unsigned char rodata_f398f[]; /* @0xf398f */
extern const unsigned char rodata_f39ae[]; /* @0xf39ae */
extern const unsigned char rodata_f39ca[]; /* @0xf39ca */
extern const unsigned char rodata_f39f4[]; /* @0xf39f4 */
extern const unsigned char rodata_f3a5d[]; /* @0xf3a5d */
extern const unsigned char rodata_f3a8d[]; /* @0xf3a8d */
extern const unsigned char rodata_f3aa8[]; /* @0xf3aa8 */
extern const unsigned char rodata_f3abe[]; /* @0xf3abe */
extern const unsigned char rodata_f3ae4[]; /* @0xf3ae4 */
extern const unsigned char rodata_f3af9[]; /* @0xf3af9 */
extern const unsigned char rodata_f3b12[]; /* @0xf3b12 */
extern const unsigned char rodata_f3b2f[]; /* @0xf3b2f */
extern const unsigned char rodata_f3b4d[]; /* @0xf3b4d */
extern const unsigned char rodata_f3b6f[]; /* @0xf3b6f */
extern const unsigned char rodata_f3b74[]; /* @0xf3b74 */
extern const unsigned char rodata_f3b92[]; /* @0xf3b92 */
extern const unsigned char rodata_f3bad[]; /* @0xf3bad */
extern const unsigned char rodata_f3bd2[]; /* @0xf3bd2 */
extern const unsigned char rodata_f3be1[]; /* @0xf3be1 */
extern const unsigned char rodata_f3c02[]; /* @0xf3c02 */
extern const unsigned char rodata_f3c07[]; /* @0xf3c07 */
extern const unsigned char rodata_f3c0f[]; /* @0xf3c0f */
extern const unsigned char rodata_f3c37[]; /* @0xf3c37 */
extern const unsigned char rodata_f3c48[]; /* @0xf3c48 */
extern const unsigned char rodata_f3c5f[]; /* @0xf3c5f */
extern const unsigned char rodata_f3c7b[]; /* @0xf3c7b */
extern const unsigned char rodata_f3c92[]; /* @0xf3c92 */
extern const unsigned char rodata_f3d5b[]; /* @0xf3d5b */
extern const unsigned char rodata_f3d75[]; /* @0xf3d75 */
extern const unsigned char rodata_f3d84[]; /* @0xf3d84 */
extern const unsigned char rodata_f3dad[]; /* @0xf3dad */
extern const unsigned char rodata_f3dc4[]; /* @0xf3dc4 */
extern const unsigned char rodata_f3de7[]; /* @0xf3de7 */
extern const unsigned char rodata_f3dff[]; /* @0xf3dff */
extern const unsigned char rodata_f3e24[]; /* @0xf3e24 */
extern const unsigned char rodata_f3e4e[]; /* @0xf3e4e */
extern const unsigned char rodata_f3ebd[]; /* @0xf3ebd */
extern const unsigned char rodata_f3ec2[]; /* @0xf3ec2 */
extern const unsigned char rodata_f3eea[]; /* @0xf3eea */
extern const unsigned char rodata_f3f11[]; /* @0xf3f11 */
extern const unsigned char rodata_f3f55[]; /* @0xf3f55 */
extern const unsigned char rodata_f3f86[]; /* @0xf3f86 */
extern const unsigned char rodata_f3f8a[]; /* @0xf3f8a */
extern const unsigned char rodata_f3fc5[]; /* @0xf3fc5 */
extern const unsigned char rodata_f3fde[]; /* @0xf3fde */
extern const unsigned char rodata_f3fe3[]; /* @0xf3fe3 */
extern const unsigned char rodata_f402a[]; /* @0xf402a */
extern const unsigned char rodata_f4079[]; /* @0xf4079 */
extern const unsigned char rodata_f4080[]; /* @0xf4080 */
extern const unsigned char rodata_f4099[]; /* @0xf4099 */
extern const unsigned char rodata_f40af[]; /* @0xf40af */
extern const unsigned char rodata_f40c2[]; /* @0xf40c2 */
extern const unsigned char rodata_f40e4[]; /* @0xf40e4 */
extern const unsigned char rodata_f41a7[]; /* @0xf41a7 */
extern const unsigned char rodata_f41c5[]; /* @0xf41c5 */
extern const unsigned char rodata_f41e6[]; /* @0xf41e6 */
extern const unsigned char rodata_f4207[]; /* @0xf4207 */
extern const unsigned char rodata_f4223[]; /* @0xf4223 */
extern const unsigned char rodata_f4240[]; /* @0xf4240 */
extern const unsigned char rodata_f4245[]; /* @0xf4245 */
extern const unsigned char rodata_f426f[]; /* @0xf426f */
extern const unsigned char rodata_f4291[]; /* @0xf4291 */
extern const unsigned char rodata_f42b3[]; /* @0xf42b3 */
extern const unsigned char rodata_f42d4[]; /* @0xf42d4 */
extern const unsigned char rodata_f42f9[]; /* @0xf42f9 */
extern const unsigned char rodata_f431a[]; /* @0xf431a */
extern const unsigned char rodata_f4346[]; /* @0xf4346 */
extern const unsigned char rodata_f4388[]; /* @0xf4388 */
extern const unsigned char rodata_f43b7[]; /* @0xf43b7 */
extern const unsigned char rodata_f43b8[]; /* @0xf43b8 */
extern const unsigned char rodata_f43ca[]; /* @0xf43ca */
extern const unsigned char rodata_f43e9[]; /* @0xf43e9 */
extern const unsigned char rodata_f4408[]; /* @0xf4408 */
extern const unsigned char rodata_f445b[]; /* @0xf445b */
extern const unsigned char rodata_f4475[]; /* @0xf4475 */
extern const unsigned char rodata_f449a[]; /* @0xf449a */
extern const unsigned char rodata_f44c2[]; /* @0xf44c2 */
extern const unsigned char rodata_f452b[]; /* @0xf452b */
extern const unsigned char rodata_f453e[]; /* @0xf453e */
extern const unsigned char rodata_f4557[]; /* @0xf4557 */
extern const unsigned char rodata_f457a[]; /* @0xf457a */
extern const unsigned char rodata_f457f[]; /* @0xf457f */
extern const unsigned char rodata_f4589[]; /* @0xf4589 */
extern const unsigned char rodata_f4590[]; /* @0xf4590 */
extern const unsigned char rodata_f45af[]; /* @0xf45af */
extern const unsigned char rodata_f45be[]; /* @0xf45be */
extern const unsigned char rodata_f4617[]; /* @0xf4617 */
extern const unsigned char rodata_f4636[]; /* @0xf4636 */
extern const unsigned char rodata_f4651[]; /* @0xf4651 */
extern const unsigned char rodata_f4680[]; /* @0xf4680 */
extern const unsigned char rodata_f4697[]; /* @0xf4697 */
extern const unsigned char rodata_f46b8[]; /* @0xf46b8 */
extern const unsigned char rodata_f46e8[]; /* @0xf46e8 */
extern const unsigned char rodata_f4707[]; /* @0xf4707 */
extern const unsigned char rodata_f471e[]; /* @0xf471e */
extern const unsigned char rodata_f472a[]; /* @0xf472a */
extern const unsigned char rodata_f4746[]; /* @0xf4746 */
extern const unsigned char rodata_f4761[]; /* @0xf4761 */
extern const unsigned char rodata_f4783[]; /* @0xf4783 */
extern const unsigned char rodata_f47a4[]; /* @0xf47a4 */
extern const unsigned char rodata_f47c1[]; /* @0xf47c1 */
extern const unsigned char rodata_f47d7[]; /* @0xf47d7 */
extern const unsigned char rodata_f47f3[]; /* @0xf47f3 */
extern const unsigned char rodata_f4812[]; /* @0xf4812 */
extern const unsigned char rodata_f4849[]; /* @0xf4849 */
extern const unsigned char rodata_f486f[]; /* @0xf486f */
extern const unsigned char rodata_f4889[]; /* @0xf4889 */
extern const unsigned char rodata_f48b5[]; /* @0xf48b5 */
extern const unsigned char rodata_f48d7[]; /* @0xf48d7 */
extern const unsigned char rodata_f492b[]; /* @0xf492b */
extern const unsigned char rodata_f497c[]; /* @0xf497c */
extern const unsigned char rodata_f49a5[]; /* @0xf49a5 */
extern const unsigned char rodata_f49ac[]; /* @0xf49ac */
extern const unsigned char rodata_f49d4[]; /* @0xf49d4 */
extern const unsigned char rodata_f49ed[]; /* @0xf49ed */
extern const unsigned char rodata_f4a01[]; /* @0xf4a01 */
extern const unsigned char rodata_f4a06[]; /* @0xf4a06 */
extern const unsigned char rodata_f4a0a[]; /* @0xf4a0a */
extern const unsigned char rodata_f4a20[]; /* @0xf4a20 */
extern const unsigned char rodata_f4a2b[]; /* @0xf4a2b */
extern const unsigned char rodata_f4a3b[]; /* @0xf4a3b */
extern const unsigned char rodata_f4a7d[]; /* @0xf4a7d */
extern const unsigned char rodata_f4a9e[]; /* @0xf4a9e */
extern const unsigned char rodata_f4aa1[]; /* @0xf4aa1 */
extern const unsigned char rodata_f4aa5[]; /* @0xf4aa5 */
extern const unsigned char rodata_f4aba[]; /* @0xf4aba */
extern const unsigned char rodata_f4abf[]; /* @0xf4abf */
extern const unsigned char rodata_f4ad5[]; /* @0xf4ad5 */
extern const unsigned char rodata_f4aeb[]; /* @0xf4aeb */
extern const unsigned char rodata_f4b16[]; /* @0xf4b16 */
extern const unsigned char rodata_f4b3d[]; /* @0xf4b3d */
extern const unsigned char rodata_f4b44[]; /* @0xf4b44 */
extern const unsigned char rodata_f4bde[]; /* @0xf4bde */
extern const unsigned char rodata_f4c07[]; /* @0xf4c07 */
extern const unsigned char rodata_f4c1e[]; /* @0xf4c1e */
extern const unsigned char rodata_f4c4b[]; /* @0xf4c4b */
extern const unsigned char rodata_f4ca5[]; /* @0xf4ca5 */
extern const unsigned char rodata_f4ca8[]; /* @0xf4ca8 */
extern const unsigned char rodata_f4cbc[]; /* @0xf4cbc */
extern const unsigned char rodata_f4cce[]; /* @0xf4cce */
extern const unsigned char rodata_f4cdd[]; /* @0xf4cdd */
extern const unsigned char rodata_f4cff[]; /* @0xf4cff */
extern const unsigned char rodata_f4d35[]; /* @0xf4d35 */
extern const unsigned char rodata_f4d4e[]; /* @0xf4d4e */
extern const unsigned char rodata_f4d5c[]; /* @0xf4d5c */
extern const unsigned char rodata_f4d6f[]; /* @0xf4d6f */
extern const unsigned char rodata_f4d88[]; /* @0xf4d88 */
extern const unsigned char rodata_f4db4[]; /* @0xf4db4 */
extern const unsigned char rodata_f4ddd[]; /* @0xf4ddd */
extern const unsigned char rodata_f4de3[]; /* @0xf4de3 */
extern const unsigned char rodata_f4e22[]; /* @0xf4e22 */
extern const unsigned char rodata_f4e47[]; /* @0xf4e47 */
extern const unsigned char rodata_f4e60[]; /* @0xf4e60 */
extern const unsigned char rodata_f4e7a[]; /* @0xf4e7a */
extern const unsigned char rodata_f4e96[]; /* @0xf4e96 */
extern const unsigned char rodata_f4eb1[]; /* @0xf4eb1 */
extern const unsigned char rodata_f4f5c[]; /* @0xf4f5c */
extern const unsigned char rodata_f4f89[]; /* @0xf4f89 */
extern const unsigned char rodata_f4f98[]; /* @0xf4f98 */
extern const unsigned char rodata_f4ff0[]; /* @0xf4ff0 */
extern const unsigned char rodata_f500b[]; /* @0xf500b */
extern const unsigned char rodata_f503c[]; /* @0xf503c */
extern const unsigned char rodata_f505e[]; /* @0xf505e */
extern const unsigned char rodata_f5071[]; /* @0xf5071 */
extern const unsigned char rodata_f5078[]; /* @0xf5078 */
extern const unsigned char rodata_f50a7[]; /* @0xf50a7 */
extern const unsigned char rodata_f50d6[]; /* @0xf50d6 */
extern const unsigned char rodata_f512c[]; /* @0xf512c */
extern const unsigned char rodata_f516d[]; /* @0xf516d */
extern const unsigned char rodata_f5182[]; /* @0xf5182 */
extern const unsigned char rodata_f519d[]; /* @0xf519d */
extern const unsigned char rodata_f51c4[]; /* @0xf51c4 */
extern const unsigned char rodata_f51ec[]; /* @0xf51ec */
extern const unsigned char rodata_f520f[]; /* @0xf520f */
extern const unsigned char rodata_f5220[]; /* @0xf5220 */
extern const unsigned char rodata_f5248[]; /* @0xf5248 */
extern const unsigned char rodata_f5268[]; /* @0xf5268 */
extern const unsigned char rodata_f5298[]; /* @0xf5298 */
extern const unsigned char rodata_f52ac[]; /* @0xf52ac */
extern const unsigned char rodata_f52c0[]; /* @0xf52c0 */
extern const unsigned char rodata_f5353[]; /* @0xf5353 */
extern const unsigned char rodata_f5373[]; /* @0xf5373 */
extern const unsigned char rodata_f539a[]; /* @0xf539a */
extern const unsigned char rodata_f53be[]; /* @0xf53be */
extern const unsigned char rodata_f53cf[]; /* @0xf53cf */
extern const unsigned char rodata_f53e9[]; /* @0xf53e9 */
extern const unsigned char rodata_f53ee[]; /* @0xf53ee */
extern const unsigned char rodata_f53ff[]; /* @0xf53ff */
extern const unsigned char rodata_f5400[]; /* @0xf5400 */
extern const unsigned char rodata_f5402[]; /* @0xf5402 */
extern const unsigned char rodata_f5407[]; /* @0xf5407 */
extern const unsigned char rodata_f540e[]; /* @0xf540e */
extern const unsigned char rodata_f541c[]; /* @0xf541c */
extern const unsigned char rodata_f542d[]; /* @0xf542d */
extern const unsigned char rodata_f543a[]; /* @0xf543a */
extern const unsigned char rodata_f5465[]; /* @0xf5465 */
extern const unsigned char rodata_f5474[]; /* @0xf5474 */
extern const unsigned char rodata_f5484[]; /* @0xf5484 */
extern const unsigned char rodata_f54a8[]; /* @0xf54a8 */
extern const unsigned char rodata_f5503[]; /* @0xf5503 */
extern const unsigned char rodata_f5522[]; /* @0xf5522 */
extern const unsigned char rodata_f5546[]; /* @0xf5546 */
extern const unsigned char rodata_f5571[]; /* @0xf5571 */
extern const unsigned char rodata_f558f[]; /* @0xf558f */
extern const unsigned char rodata_f55a9[]; /* @0xf55a9 */
extern const unsigned char rodata_f55ce[]; /* @0xf55ce */
extern const unsigned char rodata_f5600[]; /* @0xf5600 */
extern const unsigned char rodata_f5623[]; /* @0xf5623 */
extern const unsigned char rodata_f5660[]; /* @0xf5660 */
extern const unsigned char rodata_f5679[]; /* @0xf5679 */
extern const unsigned char rodata_f5692[]; /* @0xf5692 */
extern const unsigned char rodata_f56ae[]; /* @0xf56ae */
extern const unsigned char rodata_f56ca[]; /* @0xf56ca */
extern const unsigned char rodata_f5702[]; /* @0xf5702 */
extern const unsigned char rodata_f5822[]; /* @0xf5822 */
extern const unsigned char rodata_f5840[]; /* @0xf5840 */
extern const unsigned char rodata_f585d[]; /* @0xf585d */
extern const unsigned char rodata_f586b[]; /* @0xf586b */
extern const unsigned char rodata_f5871[]; /* @0xf5871 */
extern const unsigned char rodata_f5ad9[]; /* @0xf5ad9 */
extern const unsigned char rodata_f5b16[]; /* @0xf5b16 */
extern const unsigned char rodata_f5bd6[]; /* @0xf5bd6 */
extern const unsigned char rodata_f5c20[]; /* @0xf5c20 */
extern const unsigned char rodata_f5c49[]; /* @0xf5c49 */
extern const unsigned char rodata_f5c59[]; /* @0xf5c59 */
extern const unsigned char rodata_f5c6a[]; /* @0xf5c6a */
extern const unsigned char rodata_f5c9c[]; /* @0xf5c9c */
extern const unsigned char rodata_f5cba[]; /* @0xf5cba */
extern const unsigned char rodata_f5cd8[]; /* @0xf5cd8 */
extern const unsigned char rodata_f5d81[]; /* @0xf5d81 */
extern const unsigned char rodata_f5d9e[]; /* @0xf5d9e */
extern const unsigned char rodata_f5dbd[]; /* @0xf5dbd */
extern const unsigned char rodata_f5dfc[]; /* @0xf5dfc */
extern const unsigned char rodata_f5e38[]; /* @0xf5e38 */
extern const unsigned char rodata_f5e41[]; /* @0xf5e41 */
extern const unsigned char rodata_f5e50[]; /* @0xf5e50 */
extern const unsigned char rodata_f5e62[]; /* @0xf5e62 */
extern const unsigned char rodata_f5e79[]; /* @0xf5e79 */
extern const unsigned char rodata_f5eeb[]; /* @0xf5eeb */
extern const unsigned char rodata_f60c5[]; /* @0xf60c5 */
extern const unsigned char rodata_f6292[]; /* @0xf6292 */
extern const unsigned char rodata_f62ac[]; /* @0xf62ac */
extern const unsigned char rodata_f62c5[]; /* @0xf62c5 */
extern const unsigned char rodata_f62e6[]; /* @0xf62e6 */
extern const unsigned char rodata_f62fd[]; /* @0xf62fd */
extern const unsigned char rodata_f6315[]; /* @0xf6315 */
extern const unsigned char rodata_f6337[]; /* @0xf6337 */
extern const unsigned char rodata_f6353[]; /* @0xf6353 */
extern const unsigned char rodata_f6364[]; /* @0xf6364 */
extern const unsigned char rodata_f6378[]; /* @0xf6378 */
extern const unsigned char rodata_f639f[]; /* @0xf639f */
extern const unsigned char rodata_f63b1[]; /* @0xf63b1 */
extern const unsigned char rodata_f63c1[]; /* @0xf63c1 */
extern const unsigned char rodata_f63e6[]; /* @0xf63e6 */
extern const unsigned char rodata_f63f9[]; /* @0xf63f9 */
extern const unsigned char rodata_f641c[]; /* @0xf641c */
extern const unsigned char rodata_f642d[]; /* @0xf642d */
extern const unsigned char rodata_f644e[]; /* @0xf644e */
extern const unsigned char rodata_f6468[]; /* @0xf6468 */
extern const unsigned char rodata_f6481[]; /* @0xf6481 */
extern const unsigned char rodata_f6521[]; /* @0xf6521 */
extern const unsigned char rodata_f6539[]; /* @0xf6539 */
extern const unsigned char rodata_f6552[]; /* @0xf6552 */
extern const unsigned char rodata_f6565[]; /* @0xf6565 */
extern const unsigned char rodata_f6589[]; /* @0xf6589 */
extern const unsigned char rodata_f6607[]; /* @0xf6607 */
extern const unsigned char rodata_f6659[]; /* @0xf6659 */
extern const unsigned char rodata_f668a[]; /* @0xf668a */
extern const unsigned char rodata_f66a6[]; /* @0xf66a6 */
extern const unsigned char rodata_f66c1[]; /* @0xf66c1 */
extern const unsigned char rodata_f66f9[]; /* @0xf66f9 */
extern const unsigned char rodata_f6716[]; /* @0xf6716 */
extern const unsigned char rodata_f6749[]; /* @0xf6749 */
extern const unsigned char rodata_f6769[]; /* @0xf6769 */
extern const unsigned char rodata_f67a5[]; /* @0xf67a5 */
extern const unsigned char rodata_f680e[]; /* @0xf680e */
extern const unsigned char rodata_f68c5[]; /* @0xf68c5 */
extern const unsigned char rodata_f68d7[]; /* @0xf68d7 */
extern const unsigned char rodata_f691a[]; /* @0xf691a */
extern const unsigned char rodata_f692c[]; /* @0xf692c */
extern const unsigned char rodata_f693a[]; /* @0xf693a */
extern const unsigned char rodata_f694f[]; /* @0xf694f */
extern const unsigned char rodata_f696e[]; /* @0xf696e */
extern const unsigned char rodata_f6977[]; /* @0xf6977 */
extern const unsigned char rodata_f697c[]; /* @0xf697c */
extern const unsigned char rodata_f6983[]; /* @0xf6983 */
extern const unsigned char rodata_f6987[]; /* @0xf6987 */
extern const unsigned char rodata_f698e[]; /* @0xf698e */
extern const unsigned char rodata_f6994[]; /* @0xf6994 */
extern const unsigned char rodata_f6999[]; /* @0xf6999 */
extern const unsigned char rodata_f6a09[]; /* @0xf6a09 */
extern const unsigned char rodata_f6a46[]; /* @0xf6a46 */
extern const unsigned char rodata_f6a4a[]; /* @0xf6a4a */
extern const unsigned char rodata_f6a4e[]; /* @0xf6a4e */
extern const unsigned char rodata_f6a8b[]; /* @0xf6a8b */
extern const unsigned char rodata_f6abf[]; /* @0xf6abf */
extern const unsigned char rodata_f6acd[]; /* @0xf6acd */
extern const unsigned char rodata_f6b00[]; /* @0xf6b00 */
extern const unsigned char rodata_f6b3e[]; /* @0xf6b3e */
extern const unsigned char rodata_f6b73[]; /* @0xf6b73 */
extern const unsigned char rodata_f6b7d[]; /* @0xf6b7d */
extern const unsigned char rodata_f6b87[]; /* @0xf6b87 */
extern const unsigned char rodata_f6b9c[]; /* @0xf6b9c */
extern const unsigned char rodata_f6ba7[]; /* @0xf6ba7 */
extern const unsigned char rodata_f6bb7[]; /* @0xf6bb7 */
extern const unsigned char rodata_f6bc5[]; /* @0xf6bc5 */
extern const unsigned char rodata_f6c00[]; /* @0xf6c00 */
extern const unsigned char rodata_f6c09[]; /* @0xf6c09 */
extern const unsigned char rodata_f6c32[]; /* @0xf6c32 */
extern const unsigned char rodata_f6c8e[]; /* @0xf6c8e */
extern const unsigned char rodata_f6ca8[]; /* @0xf6ca8 */
extern const unsigned char rodata_f6cc2[]; /* @0xf6cc2 */
extern const unsigned char rodata_f6ceb[]; /* @0xf6ceb */
extern const unsigned char rodata_f6d26[]; /* @0xf6d26 */
extern const unsigned char rodata_f6d5e[]; /* @0xf6d5e */
extern const unsigned char rodata_f6d9a[]; /* @0xf6d9a */
extern const unsigned char rodata_f6dc6[]; /* @0xf6dc6 */
extern const unsigned char rodata_f6dde[]; /* @0xf6dde */
extern const unsigned char rodata_f6df0[]; /* @0xf6df0 */
extern const unsigned char rodata_f6e2c[]; /* @0xf6e2c */
extern const unsigned char rodata_f6e32[]; /* @0xf6e32 */
extern const unsigned char rodata_f6e3a[]; /* @0xf6e3a */
extern const unsigned char rodata_f6e66[]; /* @0xf6e66 */
extern const unsigned char rodata_f6ead[]; /* @0xf6ead */
extern const unsigned char rodata_f6ef4[]; /* @0xf6ef4 */
extern const unsigned char rodata_f6fa3[]; /* @0xf6fa3 */
extern const unsigned char rodata_f6fd9[]; /* @0xf6fd9 */
extern const unsigned char rodata_f6fef[]; /* @0xf6fef */
extern const unsigned char rodata_f702b[]; /* @0xf702b */
extern const unsigned char rodata_f7052[]; /* @0xf7052 */
extern const unsigned char rodata_f707c[]; /* @0xf707c */
extern const unsigned char rodata_f78d1[]; /* @0xf78d1 */
extern const unsigned char rodata_f7921[]; /* @0xf7921 */
extern const unsigned char rodata_f7971[]; /* @0xf7971 */
extern const unsigned char rodata_f7987[]; /* @0xf7987 */
extern const unsigned char rodata_f799d[]; /* @0xf799d */
extern const unsigned char rodata_f79c8[]; /* @0xf79c8 */
extern const unsigned char rodata_f7a03[]; /* @0xf7a03 */
extern const unsigned char rodata_f7a1b[]; /* @0xf7a1b */
extern const unsigned char rodata_f7a30[]; /* @0xf7a30 */
extern const unsigned char rodata_f7a31[]; /* @0xf7a31 */
extern const unsigned char rodata_f7a32[]; /* @0xf7a32 */
extern const unsigned char rodata_f7a3f[]; /* @0xf7a3f */
extern const unsigned char rodata_f7a8a[]; /* @0xf7a8a */
extern const unsigned char rodata_f7a8c[]; /* @0xf7a8c */
extern const unsigned char rodata_f7a9f[]; /* @0xf7a9f */
extern const unsigned char rodata_f7ad6[]; /* @0xf7ad6 */
extern const unsigned char rodata_f7b6d[]; /* @0xf7b6d */
extern const unsigned char rodata_f7b6f[]; /* @0xf7b6f */
extern const unsigned char rodata_f7b84[]; /* @0xf7b84 */
extern const unsigned char rodata_f7ba6[]; /* @0xf7ba6 */
extern const unsigned char rodata_f7be9[]; /* @0xf7be9 */
extern const unsigned char rodata_f7c02[]; /* @0xf7c02 */
extern const unsigned char rodata_f7c0e[]; /* @0xf7c0e */
extern const unsigned char rodata_f7c1a[]; /* @0xf7c1a */
extern const unsigned char rodata_f7c24[]; /* @0xf7c24 */
extern const unsigned char rodata_f7c28[]; /* @0xf7c28 */
extern const unsigned char rodata_f7c2e[]; /* @0xf7c2e */
extern const unsigned char rodata_f7c34[]; /* @0xf7c34 */
extern const unsigned char rodata_f7c9c[]; /* @0xf7c9c */
extern const unsigned char rodata_f7cc4[]; /* @0xf7cc4 */
extern const unsigned char rodata_f7ce5[]; /* @0xf7ce5 */
extern const unsigned char rodata_f7cfd[]; /* @0xf7cfd */
extern const unsigned char rodata_f7d1f[]; /* @0xf7d1f */
extern const unsigned char rodata_f7d3c[]; /* @0xf7d3c */
extern const unsigned char rodata_f7dbe[]; /* @0xf7dbe */
extern const unsigned char rodata_f7df6[]; /* @0xf7df6 */
extern const unsigned char rodata_f7e3c[]; /* @0xf7e3c */
extern const unsigned char rodata_f7e7e[]; /* @0xf7e7e */
extern const unsigned char rodata_f7f29[]; /* @0xf7f29 */
extern const unsigned char rodata_f7f4b[]; /* @0xf7f4b */
extern const unsigned char rodata_f7f6e[]; /* @0xf7f6e */
extern const unsigned char rodata_f7fee[]; /* @0xf7fee */
extern const unsigned char rodata_f801f[]; /* @0xf801f */
extern const unsigned char rodata_f8031[]; /* @0xf8031 */
extern const unsigned char rodata_f8056[]; /* @0xf8056 */
extern const unsigned char rodata_f80cc[]; /* @0xf80cc */
extern const unsigned char rodata_f80ee[]; /* @0xf80ee */
extern const unsigned char rodata_f813a[]; /* @0xf813a */
extern const unsigned char rodata_f815c[]; /* @0xf815c */
extern const unsigned char rodata_f8181[]; /* @0xf8181 */
extern const unsigned char rodata_f8198[]; /* @0xf8198 */
extern const unsigned char rodata_f81b8[]; /* @0xf81b8 */
extern const unsigned char rodata_f820f[]; /* @0xf820f */
extern const unsigned char rodata_f8230[]; /* @0xf8230 */
extern const unsigned char rodata_f8247[]; /* @0xf8247 */
extern const unsigned char rodata_f824d[]; /* @0xf824d */
extern const unsigned char rodata_f8262[]; /* @0xf8262 */
extern const unsigned char rodata_f8291[]; /* @0xf8291 */
extern const unsigned char rodata_f82a5[]; /* @0xf82a5 */
extern const unsigned char rodata_f82ab[]; /* @0xf82ab */
extern const unsigned char rodata_f82df[]; /* @0xf82df */
extern const unsigned char rodata_f82e0[]; /* @0xf82e0 */
extern const unsigned char rodata_f82f4[]; /* @0xf82f4 */
extern const unsigned char rodata_f84af[]; /* @0xf84af */
extern const unsigned char rodata_f84d6[]; /* @0xf84d6 */
extern const unsigned char rodata_f84f7[]; /* @0xf84f7 */
extern const unsigned char rodata_f8522[]; /* @0xf8522 */
extern const unsigned char rodata_f8553[]; /* @0xf8553 */
extern const unsigned char rodata_f8584[]; /* @0xf8584 */
extern const unsigned char rodata_f85bb[]; /* @0xf85bb */
extern const unsigned char rodata_f85d2[]; /* @0xf85d2 */
extern const unsigned char rodata_f8658[]; /* @0xf8658 */
extern const unsigned char rodata_f8698[]; /* @0xf8698 */
extern const unsigned char rodata_f86b7[]; /* @0xf86b7 */
extern const unsigned char rodata_f86d9[]; /* @0xf86d9 */
extern const unsigned char rodata_f86fd[]; /* @0xf86fd */
extern const unsigned char rodata_f871d[]; /* @0xf871d */
extern const unsigned char rodata_f873e[]; /* @0xf873e */
extern const unsigned char rodata_f875b[]; /* @0xf875b */
extern const unsigned char rodata_f8775[]; /* @0xf8775 */
extern const unsigned char rodata_f878a[]; /* @0xf878a */
extern const unsigned char rodata_f87a6[]; /* @0xf87a6 */
extern const unsigned char rodata_f87b7[]; /* @0xf87b7 */
extern const unsigned char rodata_f87d4[]; /* @0xf87d4 */
extern const unsigned char rodata_f87eb[]; /* @0xf87eb */
extern const unsigned char rodata_f8806[]; /* @0xf8806 */
extern const unsigned char rodata_f881f[]; /* @0xf881f */
extern const unsigned char rodata_f8835[]; /* @0xf8835 */
extern const unsigned char rodata_f8855[]; /* @0xf8855 */
extern const unsigned char rodata_f887b[]; /* @0xf887b */
extern const unsigned char rodata_f889f[]; /* @0xf889f */
extern const unsigned char rodata_f88af[]; /* @0xf88af */
extern const unsigned char rodata_f88c2[]; /* @0xf88c2 */
extern const unsigned char rodata_f88dc[]; /* @0xf88dc */
extern const unsigned char rodata_f88f2[]; /* @0xf88f2 */
extern const unsigned char rodata_f8901[]; /* @0xf8901 */
extern const unsigned char rodata_f8911[]; /* @0xf8911 */
extern const unsigned char rodata_f891e[]; /* @0xf891e */
extern const unsigned char rodata_f8942[]; /* @0xf8942 */
extern const unsigned char rodata_f8974[]; /* @0xf8974 */
extern const unsigned char rodata_f899c[]; /* @0xf899c */
extern const unsigned char rodata_f89d9[]; /* @0xf89d9 */
extern const unsigned char rodata_f8a2e[]; /* @0xf8a2e */
extern const unsigned char rodata_f8a3b[]; /* @0xf8a3b */
extern const unsigned char rodata_f8a6b[]; /* @0xf8a6b */
extern const unsigned char rodata_f8b6b[]; /* @0xf8b6b */
extern const unsigned char rodata_f8b71[]; /* @0xf8b71 */
extern const unsigned char rodata_f8b75[]; /* @0xf8b75 */
extern const unsigned char rodata_f8b88[]; /* @0xf8b88 */
extern const unsigned char rodata_f8baa[]; /* @0xf8baa */
extern const unsigned char rodata_f8bb3[]; /* @0xf8bb3 */
extern const unsigned char rodata_f8bb7[]; /* @0xf8bb7 */
extern const unsigned char rodata_f8bce[]; /* @0xf8bce */
extern const unsigned char rodata_f8c42[]; /* @0xf8c42 */
extern const unsigned char rodata_f8c53[]; /* @0xf8c53 */
extern const unsigned char rodata_f8cd5[]; /* @0xf8cd5 */
extern const unsigned char rodata_fa08[]; /* @0xfa08 */
extern const unsigned char rodata_fa9b4[]; /* @0xfa9b4 */
extern const unsigned char rodata_fa9cc[]; /* @0xfa9cc */
extern const unsigned char rodata_faa14[]; /* @0xfaa14 */
extern const unsigned char rodata_faa2c[]; /* @0xfaa2c */
extern const unsigned char rodata_fc09[]; /* @0xfc09 */
extern const unsigned char rodata_fd00[]; /* @0xfd00 */
extern const unsigned char rodata_ff20[]; /* @0xff20 */
extern const unsigned char rodata_ff41[]; /* @0xff41 */

/* Generic fallbacks for sources not including liblc3 tables.h. */
#ifndef G1_APP_USE_LIBLC3_TABLE_DECLS
extern const unsigned char lc3_band_lim[]; /* @0x90c50 */
extern const unsigned char lc3_sns_hfcb[]; /* @0x90450 */
extern const unsigned char lc3_sns_lfcb[]; /* @0x90850 */
extern const unsigned char lc3_sns_mpvq_offsets[]; /* @0x90128 */
extern const unsigned char lc3_sns_vq_gains[]; /* @0x903e8 */
extern const unsigned char lc3_spectrum_bits[]; /* @0x8d3d0 */
extern const unsigned char lc3_spectrum_lookup[]; /* @0x8ed50 */
extern const unsigned char lc3_tns_coeffs_bits[]; /* @0x8fd50 */
extern const unsigned char lc3_tns_coeffs_models[]; /* @0x8fe60 */
extern const unsigned char lc3_tns_order_bits[]; /* @0x90080 */
#endif


/* Iteration 8: pins used by the three reconstructed IPC-service handlers. */
extern const unsigned char rodata_995d9[]; /* @0x995d9 */
extern const unsigned char rodata_99605[]; /* @0x99605 */
extern const unsigned char rodata_99638[]; /* @0x99638 */
extern const unsigned char rodata_996a3[]; /* @0x996a3 */
extern const unsigned char rodata_996b3[]; /* @0x996b3 */
extern const unsigned char rodata_996e3[]; /* @0x996e3 */
extern const unsigned char rodata_99789[]; /* @0x99789 */
extern const unsigned char rodata_997b2[]; /* @0x997b2 */
extern const unsigned char rodata_997d9[]; /* @0x997d9 */
extern const unsigned char rodata_99805[]; /* @0x99805 */
extern const unsigned char rodata_99b56[]; /* @0x99b56 */
extern const unsigned char rodata_99b6d[]; /* @0x99b6d */
extern unsigned char g_20007b34[]; /* @0x20007b34 */
extern unsigned char g_2000ff4a[]; /* @0x2000ff4a */

#endif
