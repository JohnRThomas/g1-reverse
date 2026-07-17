#ifndef G1_NET_SYMBOLS_H
#define G1_NET_SYMBOLS_H
#ifndef bool
#define bool _Bool
#define true 1
#define false 0
#endif

/* ---- flash partitions ---- */

/* ---- MMIO registers ---- */
#define REG_41000e00     0x41000e00UL
#define REG_41004500     0x41004500UL
#define REG_41005000     0x41005000UL
#define REG_41005114     0x41005114UL
#define REG_41008000     0x41008000UL
#define REG_41008080     0x41008080UL
#define REG_41008304     0x41008304UL
#define REG_4100850c     0x4100850cUL
#define REG_41008510     0x41008510UL
#define REG_41008650     0x41008650UL
#define REG_4100a308     0x4100a308UL
#define REG_4100b000     0x4100b000UL
#define REG_4100b004     0x4100b004UL
#define REG_4100c140     0x4100c140UL
#define REG_4100c1c0     0x4100c1c0UL
#define REG_4100d000     0x4100d000UL
#define REG_4100e000     0x4100e000UL
#define REG_41011140     0x41011140UL
#define REG_410111c0     0x410111c0UL
#define REG_410121ac     0x410121acUL
#define REG_41016304     0x41016304UL
#define REG_41016308     0x41016308UL
#define REG_41016348     0x41016348UL

/* ---- function addresses ---- */
#define ADDR_FUN_01012438_THUMB              0x1012439 /* FUN_01012438 */
#define ADDR_FUN_010333e4_THUMB              0x10333e5 /* FUN_010333e4 */

/* ---- RAM globals / kernel objects (225) ---- */
extern volatile unsigned int g_net_fault_canary_flag; /* @0x20070000 */
extern volatile unsigned int g_net_esb_own_addr; /* @0x21000010 */
extern volatile char g_net_ble_pending_channel_idx; /* @0x2100001c */
extern volatile unsigned int g_net_flags_bitmap64; /* @0x21000020 */
extern volatile unsigned int g_net_clk_conv_cache_key; /* @0x2100003c */
extern volatile unsigned int g_net_clk_conv_cache_ext; /* @0x21000040 */
extern volatile unsigned long g_net_sdc_optfeat_fp_a; /* @0x21000044 */
extern volatile unsigned long g_net_sdc_optfeat_fp_c; /* @0x21000048 */
extern volatile unsigned long g_net_sdc_optfeat_fp_b; /* @0x2100004c */
extern volatile unsigned int g_21000050; /* @0x21000050 */
extern volatile unsigned int g_21000054; /* @0x21000054 */
extern volatile unsigned int g_21000058; /* @0x21000058 */
extern volatile unsigned int g_2100005c; /* @0x2100005c */
extern volatile unsigned int g_210001d4; /* @0x210001d4 */
extern volatile unsigned int g_210001e0; /* @0x210001e0 */
extern volatile unsigned int g_210001e4; /* @0x210001e4 */
extern volatile unsigned int g_210001e8; /* @0x210001e8 */
extern volatile unsigned int g_210001ec; /* @0x210001ec */
extern volatile unsigned int g_net_link_ctx_a_close_cb; /* @0x210001f4 */
extern volatile unsigned int g_21000208; /* @0x21000208 */
extern volatile unsigned int g_21000210; /* @0x21000210 */
extern volatile unsigned int g_net_conn_event_cb; /* @0x21000214 */
extern volatile unsigned int g_sdc_ll_ctx_field_308; /* @0x21000308 */
extern volatile unsigned int g_210004ac; /* @0x210004ac */
extern volatile unsigned int g_210004b0; /* @0x210004b0 */
extern volatile unsigned int g_210004b4; /* @0x210004b4 */
extern volatile unsigned int g_210004bc; /* @0x210004bc */
extern volatile unsigned int g_210004c8; /* @0x210004c8 */
extern volatile unsigned int g_net_link_ctx_b_close_cb; /* @0x210004d0 */
extern volatile int g_net_ble_conn_setup_err_cb; /* @0x210004d8 */
extern volatile int g_net_ble_conn_setup_ok_cb; /* @0x210004dc */
extern volatile unsigned int g_net_cb_handler_fn; /* @0x21000528 */
extern volatile unsigned int g_net_cb_registered_flag; /* @0x2100052c */
extern volatile unsigned int g_net_radio_ops_table_ptr; /* @0x21000530 */
extern volatile unsigned int g_net_driver_api_ptr; /* @0x21000574 */
extern volatile unsigned int g_net_last_fault_code; /* @0x2100057c */
extern volatile int g_zephyr_log_level; /* @0x21000580 */
extern volatile unsigned int g_net_radio_op_state; /* @0x210005b4 */
extern volatile unsigned int g_210005ec; /* @0x210005ec */
extern volatile unsigned int g_net_radio_crc_scratch; /* @0x21000684 */
extern volatile unsigned int g_net_log_msg_ctx; /* @0x21000698 */
extern volatile unsigned int g_sdc_res_pool_free_bitmap; /* @0x210006a4 */
extern volatile unsigned int g_sdc_res_pool_slot_tbl; /* @0x210006a8 */
extern volatile unsigned int g_net_conn_teardown_ctx_b; /* @0x2100071c */
extern volatile unsigned int g_net_kernel_timeout_dlist_head; /* @0x21000750 */
extern volatile unsigned int g_net_radio_sched_param_a; /* @0x21000761 */
extern volatile unsigned int g_net_radio_sched_param_b; /* @0x21000763 */
extern volatile unsigned int g_net_radio_sched_param_c; /* @0x21000767 */
extern volatile unsigned int g_net_periodic_work_obj; /* @0x2100086c */
extern volatile unsigned int g_net_layout_count_table; /* @0x21000a30 */
extern volatile unsigned int g_net_mac_pib_ext; /* @0x21000a40 */
extern volatile unsigned int g_21000a58; /* @0x21000a58 */
extern volatile unsigned char g_21000a5c; /* @0x21000a5c */
extern volatile unsigned int g_net_addr_record; /* @0x21000a60 */
extern volatile unsigned int g_21000a64; /* @0x21000a64 */
extern volatile unsigned int g_21000a68; /* @0x21000a68 */
extern volatile unsigned int g_21000b78; /* @0x21000b78 */
extern volatile unsigned char g_net_bump_alloc_state; /* @0x21000ba8 */
extern volatile int g_net_bump_alloc_cursor; /* @0x21000bac */
extern volatile unsigned int g_net_bump_alloc_offset; /* @0x21000bb0 */
extern volatile unsigned int g_net_obj_table_root_ptr; /* @0x21000bb4 */
extern volatile unsigned int g_net_bufpool_slot_cnt; /* @0x21000bb8 */
extern volatile unsigned int g_net_bufpool_base_ptr; /* @0x21000bbc */
extern volatile unsigned int g_net_storage_area_id; /* @0x21000bc0 */
extern volatile unsigned int g_net_retry_handle; /* @0x21000bc4 */
extern volatile unsigned char g_net_retry_param2; /* @0x21000bc8 */
extern volatile unsigned char g_sdc_last_cfg_param3; /* @0x21000bc9 */
extern volatile unsigned int g_net_pool_blk_cnt; /* @0x21000bec */
extern volatile signed int g_net_pool_blk_size; /* @0x21000bf0 */
extern volatile unsigned int g_net_ctrl_pending_req_busy_flag; /* @0x21000c2a */
extern volatile unsigned int g_net_ctrl_pending_req_id; /* @0x21000c2c */
extern volatile unsigned short g_21000c2e; /* @0x21000c2e */
extern volatile unsigned short g_net_ctrl_pending_req_target_id; /* @0x21000c30 */
extern volatile unsigned int g_net_addr_cache_pair; /* @0x21000c34 */
extern volatile unsigned int g_net_radio_drv_ctx; /* @0x21000c48 */
extern volatile unsigned int g_net_link_drv_ctx_0x24; /* @0x21000c6c */
extern volatile unsigned int g_ll_conn_empty_pdu_buf; /* @0x21000c90 */
extern volatile unsigned int g_ll_conn_tx_ctx_addr; /* @0x21000cc4 */
extern volatile unsigned int g_ll_conn_trace_ctx_addr; /* @0x21000cd0 */
extern volatile unsigned int g_ll_conn_pdu_hdr_ptr; /* @0x21000cfc */
extern volatile unsigned int g_net_radio_addr_match_tbl; /* @0x21000d18 */
extern volatile unsigned char g_net_rssi_cal_offset; /* @0x21000ea6 */
extern volatile unsigned char g_21000ea7; /* @0x21000ea7 */
extern volatile unsigned int g_net_esb_own_addr_valid; /* @0x21000ea8 */
extern volatile unsigned int g_net_ble_conn_create_ctx; /* @0x21000eac */
extern volatile unsigned short g_sdc_max_frag_len; /* @0x21000eae */
extern volatile unsigned int g_net_pending_work_list; /* @0x21000ec8 */
extern volatile unsigned int g_net_ctrl_timeout_node_addr; /* @0x21000ee0 */
extern volatile unsigned char g_21000ef2; /* @0x21000ef2 */
extern volatile unsigned int g_net_prng_state; /* @0x21000ef4 */
extern volatile unsigned int g_net_prng_state_s1; /* @0x21000ef8 */
extern volatile unsigned int g_net_esb_prng_state_hi; /* @0x21000efc */
extern volatile unsigned int g_net_esb_prng_state_lo; /* @0x21000f00 */
extern volatile unsigned int g_sdc_rssi_filter_cfg; /* @0x21000f04 */
extern volatile unsigned char g_net_lookup_table_desc; /* @0x21000f14 */
extern volatile unsigned int g_net_own_addr_info; /* @0x21000f20 */
extern volatile unsigned char g_21000f24; /* @0x21000f24 */
extern volatile unsigned int g_net_selected_peer_addr; /* @0x21000f41 */
extern volatile unsigned int g_net_selected_peer_id; /* @0x21000f45 */
extern volatile unsigned char g_net_radio_ack_pending_flag; /* @0x21000f54 */
extern volatile unsigned int g_21000f58; /* @0x21000f58 */
extern volatile unsigned char g_21000f5c; /* @0x21000f5c */
extern volatile unsigned int g_net_txbuf_alloc_idx; /* @0x21000f60 */
extern volatile unsigned char g_21000f64; /* @0x21000f64 */
extern volatile unsigned short g_21000f66; /* @0x21000f66 */
extern volatile unsigned int g_net_link_ctx_a; /* @0x21000f68 */
extern volatile unsigned int g_net_link_ctx_field_buf; /* @0x21000fec */
extern volatile unsigned int g_net_ctrlblk_chan_field; /* @0x21001008 */
extern volatile unsigned int g_sdc_ll_ctx_param; /* @0x21001019 */
extern volatile unsigned short g_net_radio_pending_proc_flag; /* @0x2100104a */
extern volatile unsigned char g_2100104c; /* @0x2100104c */
extern volatile unsigned int g_ll_conn_default_ctx; /* @0x21001058 */
extern volatile unsigned short g_2100109c; /* @0x2100109c */
extern volatile unsigned char g_net_session_state_block; /* @0x210010a0 */
extern volatile unsigned int g_net_session_queue_obj; /* @0x210010f0 */
extern volatile unsigned int g_net_conn_teardown_busy_flag; /* @0x2100111c */
extern volatile unsigned char g_2100111d; /* @0x2100111d */
extern volatile unsigned int g_21001120; /* @0x21001120 */
extern volatile unsigned int g_net_link_ctx_b; /* @0x21001124 */
extern volatile unsigned int g_timeout_list; /* @0x2100113c */
extern volatile unsigned char g_21001140; /* @0x21001140 */
extern volatile unsigned int g_net_ble_conn_role_cfg; /* @0x21001208 */
extern volatile unsigned int g_net_bufpool_id_tag; /* @0x21001225 */
extern volatile unsigned int g_net_radio_tx_power_level; /* @0x2100144a */
extern volatile unsigned char g_210014a8; /* @0x210014a8 */
extern volatile unsigned char g_net_ccm_op_status; /* @0x210014d8 */
extern volatile unsigned char g_net_radio_pending_reset_flag; /* @0x210014dc */
extern volatile unsigned char g_210015f7; /* @0x210015f7 */
extern volatile unsigned char g_21001609; /* @0x21001609 */
extern volatile unsigned char g_2100160a; /* @0x2100160a */
extern volatile unsigned int g_21001614; /* @0x21001614 */
extern volatile unsigned int g_net_ble_session_key_buf; /* @0x2100163c */
extern volatile unsigned int g_net_radio_frame_desc; /* @0x21001664 */
extern volatile unsigned char g_2100167c; /* @0x2100167c */
extern volatile unsigned int g_21001680; /* @0x21001680 */
extern volatile unsigned int g_net_res_reg_key; /* @0x210016b4 */
extern volatile unsigned int g_net_res_reg_handle; /* @0x210016bc */
extern volatile unsigned int g_net_res_reg_param16; /* @0x210016c0 */
extern volatile unsigned char g_210016dc; /* @0x210016dc */
extern volatile unsigned int g_net_deferred_cb_fn; /* @0x210016e0 */
extern volatile unsigned char g_210016e8; /* @0x210016e8 */
extern volatile unsigned int g_libc_tz_calc_state; /* @0x210016f0 */
extern volatile unsigned int g_net_deferred_irq_num; /* @0x21001bca */
extern volatile unsigned int g_net_link_state; /* @0x21001bcc */
extern volatile unsigned short g_21001bce; /* @0x21001bce */
extern volatile unsigned int g_154_critical_section_nest_cnt; /* @0x21001bd0 */
extern volatile unsigned short g_21001bd2; /* @0x21001bd2 */
extern volatile unsigned short g_21001bd4; /* @0x21001bd4 */
extern volatile unsigned int g_net_irq_lock_nest_cnt; /* @0x21001bd6 */
extern volatile unsigned int g_net_irq_lock_suppress_flag; /* @0x21001bdf */
extern volatile unsigned int g_net_radio_timer_active_flag; /* @0x21001bf7 */
extern volatile unsigned int g_net_radio_timer_sync_state; /* @0x21001bf8 */
extern volatile unsigned int g_21001c08; /* @0x21001c08 */
extern volatile unsigned char g_21001c18; /* @0x21001c18 */
extern volatile unsigned int g_net_task_state_struct; /* @0x21001c88 */
extern volatile unsigned int g_net_uptime_ms_lo; /* @0x21002788 */
extern volatile unsigned int g_net_uptime_ms_hi; /* @0x2100278c */
extern volatile unsigned int g_sdc_rtc_wrap_limit; /* @0x21002b88 */
extern volatile unsigned long long g_net_kernel_curr_tick; /* @0x210044f0 */
extern volatile unsigned int g_net_ctrl_report_len; /* @0x210045e4 */
extern volatile unsigned int g_net_ctrl_report_field0; /* @0x210045e8 */
extern volatile unsigned int g_net_ctrl_report_field1; /* @0x210045ec */
extern volatile unsigned int g_net_ctrl_report_field2; /* @0x210045f0 */
extern volatile unsigned int g_sdc_hci_transport_obj; /* @0x210045f4 */
extern volatile unsigned int g_net_radio_dev_ready_flag; /* @0x21004600 */
extern volatile unsigned int g_net_0x21004604_flag; /* @0x21004604 */
extern volatile unsigned int g_net_fault_record_ptr; /* @0x21004610 */
extern volatile unsigned int g_net_ipc_msg_data; /* @0x21004628 */
extern volatile unsigned int g_net_evt_callback_fn; /* @0x2100463c */
extern volatile unsigned int g_net_periodic_work_ptr; /* @0x2100465c */
extern volatile unsigned int g_net_current_thread_field_cache; /* @0x21004660 */
extern volatile int g_net_tick_correction_pending; /* @0x21004664 */
extern volatile unsigned int g_net_tick_pending_cnt; /* @0x21004668 */
extern volatile unsigned int g_21004690; /* @0x21004690 */
extern volatile unsigned int g_net_047fc; /* @0x210047fc */
extern volatile unsigned int g_rtc_overflow_cnt; /* @0x21004970 */
extern volatile unsigned int g_esb_event_handler_fn; /* @0x2100499c */
extern volatile unsigned int g_net_radio_irq_continuation_ptr; /* @0x210049a0 */
extern volatile unsigned int g_net_radio_op_status; /* @0x210049a4 */
extern volatile unsigned int g_esb_tx_busy_flag; /* @0x210049a8 */
extern volatile unsigned int g_esb_pipe_cfg_field; /* @0x210049ac */
extern volatile unsigned int g_210049b0; /* @0x210049b0 */
extern volatile unsigned int g_esb_tx_buf_pool; /* @0x210049d4 */
extern volatile unsigned int g_net_queue_stats_block_b; /* @0x21004a34 */
extern volatile unsigned int g_net_rf_cur_frame_ptr; /* @0x21004a8c */
extern volatile unsigned int g_21004a90; /* @0x21004a90 */
extern volatile unsigned int g_esb_state; /* @0x21004a94 */
extern volatile unsigned int g_net_radio_mode_state; /* @0x21004a9c */
extern volatile unsigned int g_sdc_radio_context_area; /* @0x21004aec */
extern volatile unsigned int g_net_gpiote_evt_handler_table; /* @0x21004af8 */
extern volatile unsigned char g_net_debug_trace_level; /* @0x21004b04 */
extern volatile void * g_net_debug_trace_cb; /* @0x21004b08 */
extern volatile unsigned int g_net_ipc_shm_pool_desc_ptr; /* @0x21004b30 */
extern volatile unsigned int g_zephyr_sched_thread_field; /* @0x21004b40 */
extern volatile unsigned int g_net_workq_pending_sync_list; /* @0x21004b50 */
extern volatile unsigned int g_zephyr_sched_swap_tmp; /* @0x21004b5c */
extern volatile int g_net_pipe_index_limit; /* @0x21004b60 */
extern volatile int g_net_ctx_active_count; /* @0x21004b64 */
extern volatile unsigned int announce_remaining; /* @0x21004b6c */
extern volatile unsigned int g_net_radio_temp_raw; /* @0x21004b9e */
extern volatile unsigned char g_net_ctrl_rx_ready_flag; /* @0x21004c9c */
extern volatile unsigned int g_net_ctrl_status_byte; /* @0x21004c9f */
extern volatile unsigned int g_net_ipc_msg_type; /* @0x21004fa2 */
extern volatile unsigned int g_net_evt_notify_disabled_flag; /* @0x21004fa5 */
extern volatile unsigned int g_net_evt_last_notified_state; /* @0x21004fa6 */
extern volatile unsigned int g_sdc_clock_recalc_flag; /* @0x21004fa7 */
extern volatile unsigned int g_sdc_clock_history_idx; /* @0x21004fa8 */
extern volatile unsigned int g_net_rtc_timer_sync_valid; /* @0x21004fa9 */
extern volatile unsigned int g_sdc_clock_calc_valid; /* @0x21004faa */
extern volatile unsigned int g_sdc_clock_calc_lock; /* @0x21004fab */
extern volatile unsigned char g_net_tick_handler_enable_flag; /* @0x21004fac */
extern volatile unsigned int g_net_dev_init_done_flag; /* @0x21004fad */
extern volatile unsigned int g_net_pending_tx_pkt; /* @0x210051ae */
extern volatile unsigned int g_esb_pipe_pid_cnt; /* @0x21006256 */
extern volatile unsigned int g_2100625a; /* @0x2100625a */
extern volatile unsigned int g_net_rf_ack_hdr_buf; /* @0x2100635b */
extern volatile unsigned char g_net_radio_busy_flag; /* @0x21006458 */
extern volatile unsigned char g_esb_enabled_flag; /* @0x21006459 */
extern volatile unsigned char g_net_radio_trx_ppi_ch_a; /* @0x2100645a */
extern volatile unsigned char g_esb_ppi_ch_id_1; /* @0x2100645b */
extern volatile unsigned char g_154_dppi_channel_ack; /* @0x2100645c */
extern volatile unsigned char g_esb_ppi_ch_id_3; /* @0x2100645d */
extern volatile unsigned char g_net_radio_trx_ppi_ch_e; /* @0x2100645e */
extern volatile unsigned char g_esb_ppi_ch_id_5; /* @0x2100645f */
extern volatile unsigned char g_esb_ppi_ch_id_6; /* @0x21006460 */

/* ---- rodata table externs (200) ---- */
extern const unsigned char rodata_10100a1[]; /* @0x10100a1 */
extern const unsigned char rodata_10101cd[]; /* @0x10101cd */
extern const unsigned char rodata_10102c1[]; /* @0x10102c1 */
extern const unsigned char rodata_101113d[]; /* @0x101113d */
extern const unsigned char rodata_1011869[]; /* @0x1011869 */
extern const unsigned char rodata_1011add[]; /* @0x1011add */
extern const unsigned char rodata_1011f29[]; /* @0x1011f29 */
extern const unsigned char rodata_101205d[]; /* @0x101205d */
extern const unsigned char rodata_1016591[]; /* @0x1016591 */
extern const unsigned char rodata_1017579[]; /* @0x1017579 */
extern const unsigned char rodata_101b321[]; /* @0x101b321 */
extern const unsigned char rodata_101ca79[]; /* @0x101ca79 */
extern const unsigned char rodata_101e0e9[]; /* @0x101e0e9 */
extern const unsigned char rodata_101e879[]; /* @0x101e879 */
extern const unsigned char rodata_101e961[]; /* @0x101e961 */
extern const unsigned char rodata_101e9e1[]; /* @0x101e9e1 */
extern const unsigned char rodata_101ec69[]; /* @0x101ec69 */
extern const unsigned char rodata_10203c9[]; /* @0x10203c9 */
extern const unsigned char rodata_10208e1[]; /* @0x10208e1 */
extern const unsigned char rodata_1029e3d[]; /* @0x1029e3d */
extern const unsigned char rodata_102a0f1[]; /* @0x102a0f1 */
extern const unsigned char rodata_102a1bf[]; /* @0x102a1bf */
extern const unsigned char rodata_102a2c1[]; /* @0x102a2c1 */
extern const unsigned char rodata_102a3b5[]; /* @0x102a3b5 */
extern const unsigned char rodata_102a3b9[]; /* @0x102a3b9 */
extern const unsigned char rodata_102a665[]; /* @0x102a665 */
extern const unsigned char rodata_102b351[]; /* @0x102b351 */
extern const unsigned char rodata_102b3ad[]; /* @0x102b3ad */
extern const unsigned char rodata_102b4f5[]; /* @0x102b4f5 */
extern const unsigned char rodata_102b5ad[]; /* @0x102b5ad */
extern const unsigned char rodata_102b95d[]; /* @0x102b95d */
extern const unsigned char rodata_102b9c9[]; /* @0x102b9c9 */
extern const unsigned char rodata_102ba05[]; /* @0x102ba05 */
extern const unsigned char rodata_102d22d[]; /* @0x102d22d */
extern const unsigned char rodata_1031555[]; /* @0x1031555 */
extern const unsigned char rodata_10320d9[]; /* @0x10320d9 */
extern const unsigned char rodata_1032fbd[]; /* @0x1032fbd */
extern const unsigned char rodata_1032fd9[]; /* @0x1032fd9 */
extern const unsigned char rodata_103309d[]; /* @0x103309d */
extern const unsigned char rodata_10333a5[]; /* @0x10333a5 */
extern const unsigned char rodata_10335e5[]; /* @0x10335e5 */
extern const unsigned char rodata_1033655[]; /* @0x1033655 */
extern const unsigned char rodata_1035f6d[]; /* @0x1035f6d */
extern const unsigned char rodata_103704c[]; /* @0x103704c */
extern const unsigned char rodata_1037050[]; /* @0x1037050 */
extern const unsigned char rodata_1037054[]; /* @0x1037054 */
extern const unsigned char rodata_1037058[]; /* @0x1037058 */
extern const unsigned char rodata_103a749[]; /* @0x103a749 */
extern const unsigned char rodata_103aacd[]; /* @0x103aacd */
extern const unsigned char rodata_103b6b3[]; /* @0x103b6b3 */
extern const unsigned char rodata_103b6c1[]; /* @0x103b6c1 */
extern const unsigned char rodata_103b6d3[]; /* @0x103b6d3 */
extern const unsigned char rodata_103b7ad[]; /* @0x103b7ad */
extern const unsigned char rodata_103b7f3[]; /* @0x103b7f3 */
extern const unsigned char rodata_103bac9[]; /* @0x103bac9 */
extern const unsigned char rodata_103be3f[]; /* @0x103be3f */
extern const unsigned char rodata_103bf70[]; /* @0x103bf70 */
extern const unsigned char rodata_103bfac[]; /* @0x103bfac */
extern const unsigned char rodata_103bfc0[]; /* @0x103bfc0 */
extern const unsigned char rodata_103bfec[]; /* @0x103bfec */
extern const unsigned char rodata_103c024[]; /* @0x103c024 */
extern const unsigned char rodata_103c044[]; /* @0x103c044 */
extern const unsigned char rodata_103c04c[]; /* @0x103c04c */
extern const unsigned char rodata_103c05c[]; /* @0x103c05c */
extern const unsigned char rodata_103c064[]; /* @0x103c064 */
extern const unsigned char rodata_103c074[]; /* @0x103c074 */
extern const unsigned char rodata_103c07c[]; /* @0x103c07c */
extern const unsigned char rodata_103c094[]; /* @0x103c094 */
extern const unsigned char rodata_103c0c4[]; /* @0x103c0c4 */
extern const unsigned char rodata_103c0ec[]; /* @0x103c0ec */
extern const unsigned char rodata_103c0fc[]; /* @0x103c0fc */
extern const unsigned char rodata_103c11c[]; /* @0x103c11c */
extern const unsigned char rodata_103c190[]; /* @0x103c190 */
extern const unsigned char rodata_103c1bc[]; /* @0x103c1bc */
extern const unsigned char rodata_103c1d4[]; /* @0x103c1d4 */
extern const unsigned char rodata_103c1f8[]; /* @0x103c1f8 */
extern const unsigned char rodata_103c24c[]; /* @0x103c24c */
extern const unsigned char rodata_103c254[]; /* @0x103c254 */
extern const unsigned char rodata_103c290[]; /* @0x103c290 */
extern const unsigned char rodata_103c3b0[]; /* @0x103c3b0 */
extern const unsigned char rodata_103c4cc[]; /* @0x103c4cc */
extern const unsigned char rodata_103c4d0[]; /* @0x103c4d0 */
extern const unsigned char rodata_103c578[]; /* @0x103c578 */
extern const unsigned char rodata_103c5b0[]; /* @0x103c5b0 */
extern const unsigned char rodata_103c5c4[]; /* @0x103c5c4 */
extern const unsigned char rodata_103c798[]; /* @0x103c798 */
extern const unsigned char rodata_103c900[]; /* @0x103c900 */
extern const unsigned char rodata_103cad0[]; /* @0x103cad0 */
extern const unsigned char rodata_103cae8[]; /* @0x103cae8 */
extern const unsigned char rodata_103cafc[]; /* @0x103cafc */
extern const unsigned char rodata_103cb30[]; /* @0x103cb30 */
extern const unsigned char rodata_103cd20[]; /* @0x103cd20 */
extern const unsigned char rodata_103cd46[]; /* @0x103cd46 */
extern const unsigned char rodata_103ce92[]; /* @0x103ce92 */
extern const unsigned char rodata_103ceac[]; /* @0x103ceac */
extern const unsigned char rodata_103cec3[]; /* @0x103cec3 */
extern const unsigned char rodata_103ced0[]; /* @0x103ced0 */
extern const unsigned char rodata_103cef6[]; /* @0x103cef6 */
extern const unsigned char rodata_103cf0a[]; /* @0x103cf0a */
extern const unsigned char rodata_103cf0b[]; /* @0x103cf0b */
extern const unsigned char rodata_103d088[]; /* @0x103d088 */
extern const unsigned char rodata_103d095[]; /* @0x103d095 */
extern const unsigned char rodata_103d0a2[]; /* @0x103d0a2 */
extern const unsigned char rodata_103d0bf[]; /* @0x103d0bf */
extern const unsigned char rodata_103d0db[]; /* @0x103d0db */
extern const unsigned char rodata_103d0f9[]; /* @0x103d0f9 */
extern const unsigned char rodata_103d11b[]; /* @0x103d11b */
extern const unsigned char rodata_103d13e[]; /* @0x103d13e */
extern const unsigned char rodata_103d14a[]; /* @0x103d14a */
extern const unsigned char rodata_103d18c[]; /* @0x103d18c */
extern const unsigned char rodata_103d19e[]; /* @0x103d19e */
extern const unsigned char rodata_103d1b8[]; /* @0x103d1b8 */
extern const unsigned char rodata_103d23b[]; /* @0x103d23b */
extern const unsigned char rodata_103d279[]; /* @0x103d279 */
extern const unsigned char rodata_103d2a7[]; /* @0x103d2a7 */
extern const unsigned char rodata_103d2bf[]; /* @0x103d2bf */
extern const unsigned char rodata_103d373[]; /* @0x103d373 */
extern const unsigned char rodata_103d394[]; /* @0x103d394 */
extern const unsigned char rodata_103d3b6[]; /* @0x103d3b6 */
extern const unsigned char rodata_103d3e3[]; /* @0x103d3e3 */
extern const unsigned char rodata_103d406[]; /* @0x103d406 */
extern const unsigned char rodata_103d42c[]; /* @0x103d42c */
extern const unsigned char rodata_103d53d[]; /* @0x103d53d */
extern const unsigned char rodata_103d55b[]; /* @0x103d55b */
extern const unsigned char rodata_103d5d7[]; /* @0x103d5d7 */
extern const unsigned char rodata_103d635[]; /* @0x103d635 */
extern const unsigned char rodata_103d676[]; /* @0x103d676 */
extern const unsigned char rodata_103d6b5[]; /* @0x103d6b5 */
extern const unsigned char rodata_103d73e[]; /* @0x103d73e */
extern const unsigned char rodata_103d7fb[]; /* @0x103d7fb */
extern const unsigned char rodata_103d82a[]; /* @0x103d82a */
extern const unsigned char rodata_103d859[]; /* @0x103d859 */
extern const unsigned char rodata_103d888[]; /* @0x103d888 */
extern const unsigned char rodata_103d897[]; /* @0x103d897 */
extern const unsigned char rodata_103d8c5[]; /* @0x103d8c5 */
extern const unsigned char rodata_103d8fb[]; /* @0x103d8fb */
extern const unsigned char rodata_103d911[]; /* @0x103d911 */
extern const unsigned char rodata_103d922[]; /* @0x103d922 */
extern const unsigned char rodata_103d935[]; /* @0x103d935 */
extern const unsigned char rodata_103d94e[]; /* @0x103d94e */
extern const unsigned char rodata_103d963[]; /* @0x103d963 */
extern const unsigned char rodata_103d97e[]; /* @0x103d97e */
extern const unsigned char rodata_103da8d[]; /* @0x103da8d */
extern const unsigned char rodata_103daa3[]; /* @0x103daa3 */
extern const unsigned char rodata_103dad6[]; /* @0x103dad6 */
extern const unsigned char rodata_103daee[]; /* @0x103daee */
extern const unsigned char rodata_103db04[]; /* @0x103db04 */
extern const unsigned char rodata_103db23[]; /* @0x103db23 */
extern const unsigned char rodata_103ddb9[]; /* @0x103ddb9 */
extern const unsigned char rodata_103ddcd[]; /* @0x103ddcd */
extern const unsigned char rodata_103de6b[]; /* @0x103de6b */
extern const unsigned char rodata_103df89[]; /* @0x103df89 */
extern const unsigned char rodata_103dfbc[]; /* @0x103dfbc */
extern const unsigned char rodata_103e004[]; /* @0x103e004 */
extern const unsigned char rodata_103e030[]; /* @0x103e030 */
extern const unsigned char rodata_103e16a[]; /* @0x103e16a */
extern const unsigned char rodata_103e187[]; /* @0x103e187 */
extern const unsigned char rodata_103e1f4[]; /* @0x103e1f4 */
extern const unsigned char rodata_103e216[]; /* @0x103e216 */
extern const unsigned char rodata_103e23d[]; /* @0x103e23d */
extern const unsigned char rodata_103e25d[]; /* @0x103e25d */
extern const unsigned char rodata_103e3bf[]; /* @0x103e3bf */
extern const unsigned char rodata_103e3e0[]; /* @0x103e3e0 */
extern const unsigned char rodata_103e414[]; /* @0x103e414 */
extern const unsigned char rodata_103e43d[]; /* @0x103e43d */
extern const unsigned char rodata_103e463[]; /* @0x103e463 */
extern const unsigned char rodata_103e47c[]; /* @0x103e47c */
extern const unsigned char rodata_103e4af[]; /* @0x103e4af */
extern const unsigned char rodata_103e4d1[]; /* @0x103e4d1 */
extern const unsigned char rodata_103e4f5[]; /* @0x103e4f5 */
extern const unsigned char rodata_103e628[]; /* @0x103e628 */
extern const unsigned char rodata_103e66f[]; /* @0x103e66f */
extern const unsigned char rodata_103e6ad[]; /* @0x103e6ad */
extern const unsigned char rodata_103e6e2[]; /* @0x103e6e2 */
extern const unsigned char rodata_103e6f2[]; /* @0x103e6f2 */
extern const unsigned char rodata_103e700[]; /* @0x103e700 */
extern const unsigned char rodata_103e73b[]; /* @0x103e73b */
extern const unsigned char rodata_103e867[]; /* @0x103e867 */
extern const unsigned char rodata_103e889[]; /* @0x103e889 */
extern const unsigned char rodata_103e8cc[]; /* @0x103e8cc */
extern const unsigned char rodata_103e8d2[]; /* @0x103e8d2 */
extern const unsigned char rodata_103e921[]; /* @0x103e921 */
extern const unsigned char rodata_103e929[]; /* @0x103e929 */
extern const unsigned char rodata_103e951[]; /* @0x103e951 */
extern const unsigned char rodata_103e972[]; /* @0x103e972 */
extern const unsigned char rodata_103e98a[]; /* @0x103e98a */
extern const unsigned char rodata_103e9fe[]; /* @0x103e9fe */
extern const unsigned char rodata_103ea45[]; /* @0x103ea45 */
extern const unsigned char rodata_103ea89[]; /* @0x103ea89 */
extern const unsigned char rodata_103eaab[]; /* @0x103eaab */
extern const unsigned char rodata_103eacd[]; /* @0x103eacd */
extern const unsigned char rodata_103eaed[]; /* @0x103eaed */
extern const unsigned char rodata_103eb0e[]; /* @0x103eb0e */
extern const unsigned char rodata_103eb30[]; /* @0x103eb30 */
extern const unsigned char rodata_103eb5b[]; /* @0x103eb5b */
extern const unsigned char rodata_103eb7f[]; /* @0x103eb7f */
extern const unsigned char rodata_103ebf5[]; /* @0x103ebf5 */
extern const unsigned char rodata_103ec0a[]; /* @0x103ec0a */
extern const unsigned char rodata_103ed11[]; /* @0x103ed11 */
extern const unsigned char rodata_103ed18[]; /* @0x103ed18 */

/* Generic fallbacks for sources not including liblc3 tables.h. */
#ifndef G1_APP_USE_LIBLC3_TABLE_DECLS
#endif

#endif
