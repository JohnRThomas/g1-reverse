#ifndef G1_RECOVERED_LAYOUTS_H
#define G1_RECOVERED_LAYOUTS_H
#include <stdint.h>
#include <stddef.h>

/* Generated from struct_catalog_app.json.  Each declaration is a
 * byte-slot presentation of verified offsets, not a replacement for
 * an authoritative SDK type.  Names preserve the catalog CID because
 * distinct observed objects can legitimately share a semantic type. */

/* global_0793 | G1-original | Fixed global scratch used by newlib dtoa_r double-to-ASCII conversion; trailing words are digit index/count into an internal buffer. | D1+D2 verified
 * review: Global @0x15100. Newlib dtoa internal, but this is a G1-linked static scratch object; only two idx4 words observed. */
struct __attribute__((packed)) g1_layout_dtoa_r_scratch__global_0793 {
    uint8_t _pad_0x0[0x20];
    uint8_t digit_index[0x4]; /* catalog type: uint32_t */
    uint8_t digit_count[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_dtoa_r_scratch__global_0793, digit_index) == 0x20, "g1_layout_dtoa_r_scratch__global_0793.digit_index");
_Static_assert(offsetof(struct g1_layout_dtoa_r_scratch__global_0793, digit_count) == 0x24, "g1_layout_dtoa_r_scratch__global_0793.digit_count");
_Static_assert(sizeof(struct g1_layout_dtoa_r_scratch__global_0793) >= 0x28, "g1_layout_dtoa_r_scratch__global_0793.size");

/* global_0809 | G1-original | Global GPIO descriptor read by gpio_pin_get_checked: a device/data pointer, a cached pin-state word, and a second pointer (callback/config). | D1+D2 verified
 * review: Kept sonnet naming; offsets unchanged. Likely a Zephyr GPIO device/data global but too few fields to pin a stock struct. */
struct __attribute__((packed)) g1_layout_gpio_pin_get_checked_ctx__global_0809 {
    uint8_t _pad_0x0[0x4];
    uint8_t gpio_dev[0x4]; /* catalog type: void* */
    uint8_t pin_state[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x4];
    uint8_t cb_or_cfg[0x4]; /* catalog type: void* */
};
_Static_assert(offsetof(struct g1_layout_gpio_pin_get_checked_ctx__global_0809, gpio_dev) == 0x4, "g1_layout_gpio_pin_get_checked_ctx__global_0809.gpio_dev");
_Static_assert(offsetof(struct g1_layout_gpio_pin_get_checked_ctx__global_0809, pin_state) == 0x8, "g1_layout_gpio_pin_get_checked_ctx__global_0809.pin_state");
_Static_assert(offsetof(struct g1_layout_gpio_pin_get_checked_ctx__global_0809, cb_or_cfg) == 0x10, "g1_layout_gpio_pin_get_checked_ctx__global_0809.cb_or_cfg");
_Static_assert(sizeof(struct g1_layout_gpio_pin_get_checked_ctx__global_0809) >= 0x14, "g1_layout_gpio_pin_get_checked_ctx__global_0809.size");

/* global_0832 | G1-original | Global ANCS notification-enqueue state (0x18c30) read by enqueue_ancs; sparse queue-cursor words observed. | D1+D2 verified
 * review: Only 2 sparse read offsets observed; names speculative but offsets are ground truth. */
struct __attribute__((packed)) g1_layout_ancs_enqueue_state__global_0832 {
    uint8_t _pad_0x0[0x10];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x10];
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ancs_enqueue_state__global_0832, field_0x10) == 0x10, "g1_layout_ancs_enqueue_state__global_0832.field_0x10");
_Static_assert(offsetof(struct g1_layout_ancs_enqueue_state__global_0832, field_0x24) == 0x24, "g1_layout_ancs_enqueue_state__global_0832.field_0x24");
_Static_assert(sizeof(struct g1_layout_ancs_enqueue_state__global_0832) >= 0x28, "g1_layout_ancs_enqueue_state__global_0832.size");

/* global_0836 | G1-original | G1-original global state read by enqueue_uid; a counter/id word at +0x10 and a secondary index/checksum word at +0x24. | D1+D2 verified
 * review: Kept sonnet proposal; only two sparse read offsets observed, G1-original global, no rename warranted. */
struct __attribute__((packed)) g1_layout_uid_enqueue_state__global_0836 {
    uint8_t _pad_0x0[0x10];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x10];
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_uid_enqueue_state__global_0836, field_0x10) == 0x10, "g1_layout_uid_enqueue_state__global_0836.field_0x10");
_Static_assert(offsetof(struct g1_layout_uid_enqueue_state__global_0836, field_0x24) == 0x24, "g1_layout_uid_enqueue_state__global_0836.field_0x24");
_Static_assert(sizeof(struct g1_layout_uid_enqueue_state__global_0836) >= 0x28, "g1_layout_uid_enqueue_state__global_0836.size");

/* global_0840 | G1-original | Small 4-word table at fixed addr 0x19650 read (index/idx4) by bt_start(); a BT controller init parameter/index table. | D1+D2 verified
 * review: Split out of the global_0840 footprint group: this is only a 4-consecutive-uint32 shape shared coincidentally with 7 unrelated pointer params. Kept as its own struct; corrected sonnet's is_library=true (bt_start reads it but the table itself is G1 data). */
struct __attribute__((packed)) g1_layout_bt_start_init_table__global_0840 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_start_init_table__global_0840, field_0x4) == 0x4, "g1_layout_bt_start_init_table__global_0840.field_0x4");
_Static_assert(offsetof(struct g1_layout_bt_start_init_table__global_0840, field_0x8) == 0x8, "g1_layout_bt_start_init_table__global_0840.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_start_init_table__global_0840, field_0xc) == 0xc, "g1_layout_bt_start_init_table__global_0840.field_0xc");
_Static_assert(offsetof(struct g1_layout_bt_start_init_table__global_0840, field_0x10) == 0x10, "g1_layout_bt_start_init_table__global_0840.field_0x10");
_Static_assert(sizeof(struct g1_layout_bt_start_init_table__global_0840) >= 0x14, "g1_layout_bt_start_init_table__global_0840.size");

/* global_0886 | G1-original | Small global flag/status block for SettingStoreHandler tracking a pending setting write. | D1+D2 verified
 * review: G1-original global at 0x243e8. Only two sub-word fields observed; kept as-is. */
struct __attribute__((packed)) g1_layout_setting_store_handler_state__global_0886 {
    uint8_t _pad_0x0[0x1];
    uint8_t pending_flag[0x1]; /* catalog type: uint8_t */
    uint8_t status_byte[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_setting_store_handler_state__global_0886, pending_flag) == 0x1, "g1_layout_setting_store_handler_state__global_0886.pending_flag");
_Static_assert(offsetof(struct g1_layout_setting_store_handler_state__global_0886, status_byte) == 0x2, "g1_layout_setting_store_handler_state__global_0886.status_byte");
_Static_assert(sizeof(struct g1_layout_setting_store_handler_state__global_0886) >= 0x3, "g1_layout_setting_store_handler_state__global_0886.size");

/* global_0943 | G1-original | G1-original global default-config record at 0x3074c committed at startup; three index/value words. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_default_config_record__global_0943 {
    uint8_t _pad_0x0[0x4];
    uint8_t cfg_a[0x4]; /* catalog type: uint32_t */
    uint8_t cfg_b[0x4]; /* catalog type: uint32_t */
    uint8_t cfg_c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_default_config_record__global_0943, cfg_a) == 0x4, "g1_layout_default_config_record__global_0943.cfg_a");
_Static_assert(offsetof(struct g1_layout_default_config_record__global_0943, cfg_b) == 0x8, "g1_layout_default_config_record__global_0943.cfg_b");
_Static_assert(offsetof(struct g1_layout_default_config_record__global_0943, cfg_c) == 0xc, "g1_layout_default_config_record__global_0943.cfg_c");
_Static_assert(sizeof(struct g1_layout_default_config_record__global_0943) >= 0x10, "g1_layout_default_config_record__global_0943.size");

/* global_0961 | G1-original | Global at 0x332a4 read by process_pt_data: two index/count words selecting a lookup entry. | D1+D2 verified
 * review: Single-cid; kept sonnet naming. */
struct __attribute__((packed)) g1_layout_pt_data_indices__global_0961 {
    uint8_t _pad_0x0[0x4];
    uint8_t index_a[0x4]; /* catalog type: uint32_t */
    uint8_t index_b[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_pt_data_indices__global_0961, index_a) == 0x4, "g1_layout_pt_data_indices__global_0961.index_a");
_Static_assert(offsetof(struct g1_layout_pt_data_indices__global_0961, index_b) == 0x8, "g1_layout_pt_data_indices__global_0961.index_b");
_Static_assert(sizeof(struct g1_layout_pt_data_indices__global_0961) >= 0xc, "g1_layout_pt_data_indices__global_0961.size");

/* global_0965 | G1-original | Fixed 8-word uint32 lookup/parameter table read by send_data_in_ble_chunks when splitting an outbound BLE payload into chunks (global at 0x338dc). | D1+D2 verified
 * review: Split out of the footprint-collision group global_0965: this cid is a distinct global at a distinct address (0x338dc) in send_data_in_ble_chunks, unrelated to the scroll-text tables, ndef ctx or stream_flash_ctx it was grouped with. Kept all offsets. */
struct __attribute__((packed)) g1_layout_ble_chunk_param_table__global_0965 {
    uint8_t _pad_0x0[0x4];
    uint8_t entry_1[0x4]; /* catalog type: uint32_t */
    uint8_t entry_2[0x4]; /* catalog type: uint32_t */
    uint8_t entry_3[0x4]; /* catalog type: uint32_t */
    uint8_t entry_4[0x4]; /* catalog type: uint32_t */
    uint8_t entry_5[0x4]; /* catalog type: uint32_t */
    uint8_t entry_6[0x4]; /* catalog type: uint32_t */
    uint8_t entry_7[0x4]; /* catalog type: uint32_t */
    uint8_t entry_8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ble_chunk_param_table__global_0965, entry_1) == 0x4, "g1_layout_ble_chunk_param_table__global_0965.entry_1");
_Static_assert(offsetof(struct g1_layout_ble_chunk_param_table__global_0965, entry_2) == 0x8, "g1_layout_ble_chunk_param_table__global_0965.entry_2");
_Static_assert(offsetof(struct g1_layout_ble_chunk_param_table__global_0965, entry_3) == 0xc, "g1_layout_ble_chunk_param_table__global_0965.entry_3");
_Static_assert(offsetof(struct g1_layout_ble_chunk_param_table__global_0965, entry_4) == 0x10, "g1_layout_ble_chunk_param_table__global_0965.entry_4");
_Static_assert(offsetof(struct g1_layout_ble_chunk_param_table__global_0965, entry_5) == 0x14, "g1_layout_ble_chunk_param_table__global_0965.entry_5");
_Static_assert(offsetof(struct g1_layout_ble_chunk_param_table__global_0965, entry_6) == 0x18, "g1_layout_ble_chunk_param_table__global_0965.entry_6");
_Static_assert(offsetof(struct g1_layout_ble_chunk_param_table__global_0965, entry_7) == 0x1c, "g1_layout_ble_chunk_param_table__global_0965.entry_7");
_Static_assert(offsetof(struct g1_layout_ble_chunk_param_table__global_0965, entry_8) == 0x20, "g1_layout_ble_chunk_param_table__global_0965.entry_8");
_Static_assert(sizeof(struct g1_layout_ble_chunk_param_table__global_0965) >= 0x24, "g1_layout_ble_chunk_param_table__global_0965.size");

/* global_0968 | G1-original | G1-original global at 0x33bbc tracking a pending BLE message queued for resend (flag/status bytes). | D1+D2 verified
 * review: Grouped with global_0969 by footprint but they are DISTINCT global addresses (0x33bbc vs 0x33bec) in different functions; coincidental 4-field shape. SEPARATE, not merged. */
struct __attribute__((packed)) g1_layout_resend_pending_msg_state__global_0968 {
    uint8_t _pad_0x0[0x114];
    uint8_t resend_flag[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x115[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x116[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x117[0x1];
    uint8_t field_0x118[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_resend_pending_msg_state__global_0968, resend_flag) == 0x114, "g1_layout_resend_pending_msg_state__global_0968.resend_flag");
_Static_assert(offsetof(struct g1_layout_resend_pending_msg_state__global_0968, field_0x115) == 0x115, "g1_layout_resend_pending_msg_state__global_0968.field_0x115");
_Static_assert(offsetof(struct g1_layout_resend_pending_msg_state__global_0968, field_0x116) == 0x116, "g1_layout_resend_pending_msg_state__global_0968.field_0x116");
_Static_assert(offsetof(struct g1_layout_resend_pending_msg_state__global_0968, field_0x118) == 0x118, "g1_layout_resend_pending_msg_state__global_0968.field_0x118");
_Static_assert(sizeof(struct g1_layout_resend_pending_msg_state__global_0968) >= 0x119, "g1_layout_resend_pending_msg_state__global_0968.size");

/* global_0969 | G1-original | G1-original global at 0x33bec used by pt_queue_get_free_slot (index/flag bookkeeping bytes). | D1+D2 verified
 * review: Distinct global address from global_0968; only shares footprint. SEPARATE. */
struct __attribute__((packed)) g1_layout_pt_queue_free_slot_state__global_0969 {
    uint8_t _pad_0x0[0x114];
    uint8_t write_idx[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x115[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x116[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x117[0x1];
    uint8_t field_0x118[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_pt_queue_free_slot_state__global_0969, write_idx) == 0x114, "g1_layout_pt_queue_free_slot_state__global_0969.write_idx");
_Static_assert(offsetof(struct g1_layout_pt_queue_free_slot_state__global_0969, field_0x115) == 0x115, "g1_layout_pt_queue_free_slot_state__global_0969.field_0x115");
_Static_assert(offsetof(struct g1_layout_pt_queue_free_slot_state__global_0969, field_0x116) == 0x116, "g1_layout_pt_queue_free_slot_state__global_0969.field_0x116");
_Static_assert(offsetof(struct g1_layout_pt_queue_free_slot_state__global_0969, field_0x118) == 0x118, "g1_layout_pt_queue_free_slot_state__global_0969.field_0x118");
_Static_assert(sizeof(struct g1_layout_pt_queue_free_slot_state__global_0969) >= 0x119, "g1_layout_pt_queue_free_slot_state__global_0969.size");

/* global_0972 | G1-original | On-glasses confirmation/dialog message global state (status word plus flag/marker bytes) referenced by confirm_message. | D1+D2 verified
 * review: G1-original. Kept sonnet layout; offsets are ground truth. */
struct __attribute__((packed)) g1_layout_confirm_message_state__global_0972 {
    uint8_t _pad_0x0[0x110];
    uint8_t msg_status[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x114[0x1];
    uint8_t confirm_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x116[0x2];
    uint8_t dismiss_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x119[0x19f];
    uint8_t trailer_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_confirm_message_state__global_0972, msg_status) == 0x110, "g1_layout_confirm_message_state__global_0972.msg_status");
_Static_assert(offsetof(struct g1_layout_confirm_message_state__global_0972, confirm_flag) == 0x115, "g1_layout_confirm_message_state__global_0972.confirm_flag");
_Static_assert(offsetof(struct g1_layout_confirm_message_state__global_0972, dismiss_flag) == 0x118, "g1_layout_confirm_message_state__global_0972.dismiss_flag");
_Static_assert(offsetof(struct g1_layout_confirm_message_state__global_0972, trailer_flag) == 0x2b8, "g1_layout_confirm_message_state__global_0972.trailer_flag");
_Static_assert(sizeof(struct g1_layout_confirm_message_state__global_0972) >= 0x2bc, "g1_layout_confirm_message_state__global_0972.size");

/* global_0997 | G1-original | Global state block read by DashBoard_Reflash: two byte flags and a status/counter word controlling the firmware reflash dashboard flow (global at 0x3abb4). | D1+D2 verified
 * review: Single-cid; sonnet naming reasonable. Offsets kept. */
struct __attribute__((packed)) g1_layout_dashboard_reflash_state__global_0997 {
    uint8_t _pad_0x0[0x19];
    uint8_t reflash_flag_a[0x1]; /* catalog type: uint8_t */
    uint8_t reflash_flag_b[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1b[0x1];
    uint8_t reflash_status[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_state__global_0997, reflash_flag_a) == 0x19, "g1_layout_dashboard_reflash_state__global_0997.reflash_flag_a");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_state__global_0997, reflash_flag_b) == 0x1a, "g1_layout_dashboard_reflash_state__global_0997.reflash_flag_b");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_state__global_0997, reflash_status) == 0x1c, "g1_layout_dashboard_reflash_state__global_0997.reflash_status");
_Static_assert(sizeof(struct g1_layout_dashboard_reflash_state__global_0997) >= 0x20, "g1_layout_dashboard_reflash_state__global_0997.size");

/* global_0998 | G1-original | Fixed-address global state block tracked by DashBoard_Reflash (two flag/char bytes plus a counter/status word). | D1+D2 verified
 * review: Kept sonnet naming; offsets unchanged. G1-original global at 0x374dc. */
struct __attribute__((packed)) g1_layout_dashboard_reflash_state__global_0998 {
    uint8_t _pad_0x0[0x19];
    uint8_t flag0[0x1]; /* catalog type: uint8_t */
    uint8_t flag1[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1b[0x1];
    uint8_t counter_or_status[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_state__global_0998, flag0) == 0x19, "g1_layout_dashboard_reflash_state__global_0998.flag0");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_state__global_0998, flag1) == 0x1a, "g1_layout_dashboard_reflash_state__global_0998.flag1");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_state__global_0998, counter_or_status) == 0x1c, "g1_layout_dashboard_reflash_state__global_0998.counter_or_status");
_Static_assert(sizeof(struct g1_layout_dashboard_reflash_state__global_0998) >= 0x20, "g1_layout_dashboard_reflash_state__global_0998.size");

/* global_1000 | G1-original | Global flags/counter block used by DashBoard_Reflash for panel reflash sequencing. | D1+D2 verified
 * review: Global @0x39270. G1-original UI state. */
struct __attribute__((packed)) g1_layout_dashboard_reflash_state__global_1000 {
    uint8_t _pad_0x0[0x19];
    uint8_t flag_0x19[0x1]; /* catalog type: uint8_t */
    uint8_t flag_0x1a[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1b[0x1];
    uint8_t counter[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_state__global_1000, flag_0x19) == 0x19, "g1_layout_dashboard_reflash_state__global_1000.flag_0x19");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_state__global_1000, flag_0x1a) == 0x1a, "g1_layout_dashboard_reflash_state__global_1000.flag_0x1a");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_state__global_1000, counter) == 0x1c, "g1_layout_dashboard_reflash_state__global_1000.counter");
_Static_assert(sizeof(struct g1_layout_dashboard_reflash_state__global_1000) >= 0x20, "g1_layout_dashboard_reflash_state__global_1000.size");

/* global_1019 | G1-original | Fixed uint32 index/offset table consumed by ui_render_scroll_text_frame when rendering scrolling text frames. global_1019 (0x442b4) and global_1020 (0x442b8) are the same table region referenced via base and base+4 pointers in the same function. | D1+D2 verified
 * review: Merged global_1019 and global_1020: adjacent fixed addresses 4 bytes apart, both from ui_render_scroll_text_frame with the identical 8-word read pattern — two pointers into one rodata table, not two objects. Split away from the rest of group global_0965 (unrelated objects). */
struct __attribute__((packed)) g1_layout_scroll_text_frame_idx_table__global_1019 {
    uint8_t _pad_0x0[0x4];
    uint8_t idx_1[0x4]; /* catalog type: uint32_t */
    uint8_t idx_2[0x4]; /* catalog type: uint32_t */
    uint8_t idx_3[0x4]; /* catalog type: uint32_t */
    uint8_t idx_4[0x4]; /* catalog type: uint32_t */
    uint8_t idx_5[0x4]; /* catalog type: uint32_t */
    uint8_t idx_6[0x4]; /* catalog type: uint32_t */
    uint8_t idx_7[0x4]; /* catalog type: uint32_t */
    uint8_t idx_8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_idx_table__global_1019, idx_1) == 0x4, "g1_layout_scroll_text_frame_idx_table__global_1019.idx_1");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_idx_table__global_1019, idx_2) == 0x8, "g1_layout_scroll_text_frame_idx_table__global_1019.idx_2");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_idx_table__global_1019, idx_3) == 0xc, "g1_layout_scroll_text_frame_idx_table__global_1019.idx_3");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_idx_table__global_1019, idx_4) == 0x10, "g1_layout_scroll_text_frame_idx_table__global_1019.idx_4");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_idx_table__global_1019, idx_5) == 0x14, "g1_layout_scroll_text_frame_idx_table__global_1019.idx_5");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_idx_table__global_1019, idx_6) == 0x18, "g1_layout_scroll_text_frame_idx_table__global_1019.idx_6");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_idx_table__global_1019, idx_7) == 0x1c, "g1_layout_scroll_text_frame_idx_table__global_1019.idx_7");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_idx_table__global_1019, idx_8) == 0x20, "g1_layout_scroll_text_frame_idx_table__global_1019.idx_8");
_Static_assert(sizeof(struct g1_layout_scroll_text_frame_idx_table__global_1019) >= 0x24, "g1_layout_scroll_text_frame_idx_table__global_1019.size");

/* global_1026 | G1-original | Global cursor/measurement state used by gui_utf_Wordwrap_draw during UTF-8 word-wrap layout. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_gui_wordwrap_state__global_1026 {
    uint8_t _pad_0x0[0x2];
    uint8_t width_or_count[0x2]; /* catalog type: uint16_t */
    uint8_t index_or_handle[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gui_wordwrap_state__global_1026, width_or_count) == 0x2, "g1_layout_gui_wordwrap_state__global_1026.width_or_count");
_Static_assert(offsetof(struct g1_layout_gui_wordwrap_state__global_1026, index_or_handle) == 0x4, "g1_layout_gui_wordwrap_state__global_1026.index_or_handle");
_Static_assert(sizeof(struct g1_layout_gui_wordwrap_state__global_1026) >= 0x8, "g1_layout_gui_wordwrap_state__global_1026.size");

/* global_1046 | G1-original | Global UI refresh/warp control state (0x40190) read by ui_refalsh_warp. | D1+D2 verified
 * review: Two sparse read offsets; kept offsets, generic names. */
struct __attribute__((packed)) g1_layout_ui_refresh_warp_state__global_1046 {
    uint8_t _pad_0x0[0x8];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x10];
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ui_refresh_warp_state__global_1046, field_0x8) == 0x8, "g1_layout_ui_refresh_warp_state__global_1046.field_0x8");
_Static_assert(offsetof(struct g1_layout_ui_refresh_warp_state__global_1046, field_0x1c) == 0x1c, "g1_layout_ui_refresh_warp_state__global_1046.field_0x1c");
_Static_assert(sizeof(struct g1_layout_ui_refresh_warp_state__global_1046) >= 0x20, "g1_layout_ui_refresh_warp_state__global_1046.size");

/* global_1068 | library | Global logging-subsystem state read by log_process (Zephyr logging backend), tracking message counters/indices. | D1+D2 verified
 * review: Opaque logging-subsystem global at a fixed address; the concrete backing struct is a file-local aggregate in log_core.c, so offsets cannot be matched to a public header (library_verified=false). */
struct __attribute__((packed)) g1_layout_log_process_state__global_1068 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x4];
    uint8_t field_0x10[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x14[0x10];
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_log_process_state__global_1068, field_0x4) == 0x4, "g1_layout_log_process_state__global_1068.field_0x4");
_Static_assert(offsetof(struct g1_layout_log_process_state__global_1068, field_0x8) == 0x8, "g1_layout_log_process_state__global_1068.field_0x8");
_Static_assert(offsetof(struct g1_layout_log_process_state__global_1068, field_0x10) == 0x10, "g1_layout_log_process_state__global_1068.field_0x10");
_Static_assert(offsetof(struct g1_layout_log_process_state__global_1068, field_0x24) == 0x24, "g1_layout_log_process_state__global_1068.field_0x24");
_Static_assert(sizeof(struct g1_layout_log_process_state__global_1068) >= 0x28, "g1_layout_log_process_state__global_1068.size");

/* global_1071 | library | Zephyr settings-subsystem backend source descriptor registered via settings_src_register (list node + backend itf pointer). | D1+D2 verified
 * review: CORRECTED sonnet: settings_src_register takes struct settings_store*, not settings_handler_static. VERIFIED: header struct settings_store { sys_snode_t cs_next; const struct settings_store_itf *cs_itf; } matches observed 0x0 node ptr + 0x4 itf ptr. */
struct __attribute__((packed)) g1_layout_settings_store__global_1071 {
    uint8_t cs_next[0x4]; /* catalog type: sys_snode_t; SDK member: cs_next */
    uint8_t cs_itf[0x4]; /* catalog type: const struct settings_store_itf *; SDK member: cs_itf */
};
_Static_assert(offsetof(struct g1_layout_settings_store__global_1071, cs_next) == 0x0, "g1_layout_settings_store__global_1071.cs_next");
_Static_assert(offsetof(struct g1_layout_settings_store__global_1071, cs_itf) == 0x4, "g1_layout_settings_store__global_1071.cs_itf");
_Static_assert(sizeof(struct g1_layout_settings_store__global_1071) >= 0x8, "g1_layout_settings_store__global_1071.size");

/* global_1075 | library | Global attribute pool used by gatt_dm_attr_alloc (Nordic bt_gatt_dm discovery). Tail fields: count, free-list ptr, status. | D1+D2 verified
 * review: gatt_dm internal pool lives in nrf/subsys/bluetooth/services/gatt_dm.c (not a public header); cannot verify the 0x150/0x154/0x158 offsets. Kept identification, verified=false. */
struct __attribute__((packed)) g1_layout_gatt_dm_attr_pool__global_1075 {
    uint8_t _pad_0x0[0x150];
    uint8_t pool_count[0x4]; /* catalog type: uint32_t */
    uint8_t free_list[0x4]; /* catalog type: void* */
    uint8_t status[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_dm_attr_pool__global_1075, pool_count) == 0x150, "g1_layout_gatt_dm_attr_pool__global_1075.pool_count");
_Static_assert(offsetof(struct g1_layout_gatt_dm_attr_pool__global_1075, free_list) == 0x154, "g1_layout_gatt_dm_attr_pool__global_1075.free_list");
_Static_assert(offsetof(struct g1_layout_gatt_dm_attr_pool__global_1075, status) == 0x158, "g1_layout_gatt_dm_attr_pool__global_1075.status");
_Static_assert(sizeof(struct g1_layout_gatt_dm_attr_pool__global_1075) >= 0x15c, "g1_layout_gatt_dm_attr_pool__global_1075.size");

/* global_1077 | G1-original | Global at 0x4ecf8 used by discovery_callback: a small header (write short) plus a large embedded table of discovered handle/index entries. | D1+D2 verified
 * review: Single-cid; far offset 0x134 is the tail of an embedded table. */
struct __attribute__((packed)) g1_layout_ble_discovery_state__global_1077 {
    uint8_t _pad_0x0[0x4];
    uint8_t discovery_flags[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x6[0x1a];
    uint8_t first_entry_idx[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x24[0x110];
    uint8_t last_entry_idx[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ble_discovery_state__global_1077, discovery_flags) == 0x4, "g1_layout_ble_discovery_state__global_1077.discovery_flags");
_Static_assert(offsetof(struct g1_layout_ble_discovery_state__global_1077, first_entry_idx) == 0x20, "g1_layout_ble_discovery_state__global_1077.first_entry_idx");
_Static_assert(offsetof(struct g1_layout_ble_discovery_state__global_1077, last_entry_idx) == 0x134, "g1_layout_ble_discovery_state__global_1077.last_entry_idx");
_Static_assert(sizeof(struct g1_layout_ble_discovery_state__global_1077) >= 0x138, "g1_layout_ble_discovery_state__global_1077.size");

/* global_1096 | library | Event header (fixed global 0x4f850) passed to app_event_manager_submit (NCS Application Event Manager): event type-id pointer plus one index-typed word. | D1+D2 verified
 * review: Only two words observed; app_event_header real layout (const struct event_type* type_id + optional tracking id) is plausible but not offset-verifiable from 2 fields, so library_verified=false. */
struct __attribute__((packed)) g1_layout_app_event_header__global_1096 {
    uint8_t type_id[0x4]; /* catalog type: uint32_t; SDK member: type_id */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_app_event_header__global_1096, type_id) == 0x0, "g1_layout_app_event_header__global_1096.type_id");
_Static_assert(offsetof(struct g1_layout_app_event_header__global_1096, field_0x4) == 0x4, "g1_layout_app_event_header__global_1096.field_0x4");
_Static_assert(sizeof(struct g1_layout_app_event_header__global_1096) >= 0x8, "g1_layout_app_event_header__global_1096.size");

/* global_1098 | library | tinycrypt AES-128 expanded key schedule (44 x uint32 words) written by tc_aes128_set_encrypt_key (global at 0x4fad4). | D1+D2 verified
 * review: Verified against tinycrypt aes.h: struct is `unsigned int words[Nb*(Nr+1)]` = words[44] at offset 0. Observed reads 0x4..0x28 are words[1..10]; word[0] at 0x0 is the pad. Offsets exact. */
struct __attribute__((packed)) g1_layout_tc_aes_key_sched_struct__global_1098 {
    uint8_t _pad_0x0[0x4];
    uint8_t words_1[0x4]; /* catalog type: uint32_t; SDK member: words[1] */
    uint8_t words_2[0x4]; /* catalog type: uint32_t; SDK member: words[2] */
    uint8_t words_3[0x4]; /* catalog type: uint32_t; SDK member: words[3] */
    uint8_t words_4[0x4]; /* catalog type: uint32_t; SDK member: words[4] */
    uint8_t words_5[0x4]; /* catalog type: uint32_t; SDK member: words[5] */
    uint8_t words_6[0x4]; /* catalog type: uint32_t; SDK member: words[6] */
    uint8_t words_7[0x4]; /* catalog type: uint32_t; SDK member: words[7] */
    uint8_t words_8[0x4]; /* catalog type: uint32_t; SDK member: words[8] */
    uint8_t words_9[0x4]; /* catalog type: uint32_t; SDK member: words[9] */
    uint8_t words_10[0x4]; /* catalog type: uint32_t; SDK member: words[10] */
};
_Static_assert(offsetof(struct g1_layout_tc_aes_key_sched_struct__global_1098, words_1) == 0x4, "g1_layout_tc_aes_key_sched_struct__global_1098.words_1");
_Static_assert(offsetof(struct g1_layout_tc_aes_key_sched_struct__global_1098, words_2) == 0x8, "g1_layout_tc_aes_key_sched_struct__global_1098.words_2");
_Static_assert(offsetof(struct g1_layout_tc_aes_key_sched_struct__global_1098, words_3) == 0xc, "g1_layout_tc_aes_key_sched_struct__global_1098.words_3");
_Static_assert(offsetof(struct g1_layout_tc_aes_key_sched_struct__global_1098, words_4) == 0x10, "g1_layout_tc_aes_key_sched_struct__global_1098.words_4");
_Static_assert(offsetof(struct g1_layout_tc_aes_key_sched_struct__global_1098, words_5) == 0x14, "g1_layout_tc_aes_key_sched_struct__global_1098.words_5");
_Static_assert(offsetof(struct g1_layout_tc_aes_key_sched_struct__global_1098, words_6) == 0x18, "g1_layout_tc_aes_key_sched_struct__global_1098.words_6");
_Static_assert(offsetof(struct g1_layout_tc_aes_key_sched_struct__global_1098, words_7) == 0x1c, "g1_layout_tc_aes_key_sched_struct__global_1098.words_7");
_Static_assert(offsetof(struct g1_layout_tc_aes_key_sched_struct__global_1098, words_8) == 0x20, "g1_layout_tc_aes_key_sched_struct__global_1098.words_8");
_Static_assert(offsetof(struct g1_layout_tc_aes_key_sched_struct__global_1098, words_9) == 0x24, "g1_layout_tc_aes_key_sched_struct__global_1098.words_9");
_Static_assert(offsetof(struct g1_layout_tc_aes_key_sched_struct__global_1098, words_10) == 0x28, "g1_layout_tc_aes_key_sched_struct__global_1098.words_10");
_Static_assert(sizeof(struct g1_layout_tc_aes_key_sched_struct__global_1098) >= 0x2c, "g1_layout_tc_aes_key_sched_struct__global_1098.size");

/* global_1102 | G1-original | Extra fault-record slots read by the ARM MemManage fault helper (arm_mem_manage_fault_helper) at fixed address 0x5052c. | D1+D2 verified
 * review: G1-original fault bookkeeping; offsets unchanged. */
struct __attribute__((packed)) g1_layout_memmanage_fault_record__global_1102 {
    uint8_t _pad_0x0[0x24];
    uint8_t fault_extra1[0x4]; /* catalog type: uint32_t */
    uint8_t fault_extra2[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_memmanage_fault_record__global_1102, fault_extra1) == 0x24, "g1_layout_memmanage_fault_record__global_1102.fault_extra1");
_Static_assert(offsetof(struct g1_layout_memmanage_fault_record__global_1102, fault_extra2) == 0x28, "g1_layout_memmanage_fault_record__global_1102.fault_extra2");
_Static_assert(sizeof(struct g1_layout_memmanage_fault_record__global_1102) >= 0x2c, "g1_layout_memmanage_fault_record__global_1102.size");

/* global_1117 | library | mcumgr image-management global state inspected during an in-progress firmware image upload (img_mgmt_upload_inspect). | D1+D2 verified
 * review: Global @0x51a3c. Identity inferred from img_mgmt_upload_inspect; only two idx4 words (size/off) observed so header offsets not verified. */
struct __attribute__((packed)) g1_layout_img_mgmt_upload_state__global_1117 {
    uint8_t _pad_0x0[0x8];
    uint8_t image_size[0x4]; /* catalog type: uint32_t */
    uint8_t image_off[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_state__global_1117, image_size) == 0x8, "g1_layout_img_mgmt_upload_state__global_1117.image_size");
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_state__global_1117, image_off) == 0xc, "g1_layout_img_mgmt_upload_state__global_1117.image_off");
_Static_assert(sizeof(struct g1_layout_img_mgmt_upload_state__global_1117) >= 0x10, "g1_layout_img_mgmt_upload_state__global_1117.size");

/* global_1152 | G1-original | Fixed global at 0x53378 consumed by ver_str: a 13-word version/build-info record concatenated into a version string. | D1+D2 verified
 * review: Split from param_0692: the 13-word footprint is a coincidental collision. This is a G1 version data blob (ver_str), NOT the libmetal io region that shares the shape. Corrected sonnet is_library=true. */
struct __attribute__((packed)) g1_layout_fw_version_info_table__global_1152 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x28[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x2c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x30[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x34[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0x4) == 0x4, "g1_layout_fw_version_info_table__global_1152.field_0x4");
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0x8) == 0x8, "g1_layout_fw_version_info_table__global_1152.field_0x8");
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0xc) == 0xc, "g1_layout_fw_version_info_table__global_1152.field_0xc");
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0x10) == 0x10, "g1_layout_fw_version_info_table__global_1152.field_0x10");
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0x14) == 0x14, "g1_layout_fw_version_info_table__global_1152.field_0x14");
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0x18) == 0x18, "g1_layout_fw_version_info_table__global_1152.field_0x18");
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0x1c) == 0x1c, "g1_layout_fw_version_info_table__global_1152.field_0x1c");
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0x20) == 0x20, "g1_layout_fw_version_info_table__global_1152.field_0x20");
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0x24) == 0x24, "g1_layout_fw_version_info_table__global_1152.field_0x24");
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0x28) == 0x28, "g1_layout_fw_version_info_table__global_1152.field_0x28");
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0x2c) == 0x2c, "g1_layout_fw_version_info_table__global_1152.field_0x2c");
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0x30) == 0x30, "g1_layout_fw_version_info_table__global_1152.field_0x30");
_Static_assert(offsetof(struct g1_layout_fw_version_info_table__global_1152, field_0x34) == 0x34, "g1_layout_fw_version_info_table__global_1152.field_0x34");
_Static_assert(sizeof(struct g1_layout_fw_version_info_table__global_1152) >= 0x38, "g1_layout_fw_version_info_table__global_1152.size");

/* global_1166 | library | Zephyr BLE host global device-state singleton; bt_id_add touches identity/oob flag bytes near offset 0x120. | D1+D2 verified
 * review: Confirmed this is the bt_dev singleton by the bt_id_add accessor, but bt_dev layout is heavily config-dependent and the two observed flag bytes at 0x120/0x121 cannot be pinned to named members from the header without a matching build config; library_verified=false. */
struct __attribute__((packed)) g1_layout_bt_dev__global_1166 {
    uint8_t _pad_0x0[0x120];
    uint8_t id_flag_0[0x1]; /* catalog type: uint8_t */
    uint8_t id_flag_1[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_bt_dev__global_1166, id_flag_0) == 0x120, "g1_layout_bt_dev__global_1166.id_flag_0");
_Static_assert(offsetof(struct g1_layout_bt_dev__global_1166, id_flag_1) == 0x121, "g1_layout_bt_dev__global_1166.id_flag_1");
_Static_assert(sizeof(struct g1_layout_bt_dev__global_1166) >= 0x122, "g1_layout_bt_dev__global_1166.size");

/* global_1168 | G1-original | Global BLE privacy identity state (0x551dc) touched by ble_privacy_id_remove; two adjacent status bytes near +0x120. | D1+D2 verified
 * review: Sparse byte accesses; offsets kept. */
struct __attribute__((packed)) g1_layout_ble_privacy_id_state__global_1168 {
    uint8_t _pad_0x0[0x120];
    uint8_t field_0x120[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x121[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_ble_privacy_id_state__global_1168, field_0x120) == 0x120, "g1_layout_ble_privacy_id_state__global_1168.field_0x120");
_Static_assert(offsetof(struct g1_layout_ble_privacy_id_state__global_1168, field_0x121) == 0x121, "g1_layout_ble_privacy_id_state__global_1168.field_0x121");
_Static_assert(sizeof(struct g1_layout_ble_privacy_id_state__global_1168) >= 0x122, "g1_layout_ble_privacy_id_state__global_1168.size");

/* global_1185 | library | Zephyr Bluetooth connection object (global connection pool slot); the two observed fields are in the TX/state tail region accessed by bt_conn_prepare_tx_events. | D1+D2 verified
 * review: Only two far-apart fields (0x104, 0x110) observed; bt_conn is defined in the private host header conn_internal.h (not in the include tree). Cannot confirm these specific offsets, so library_verified=false. */
struct __attribute__((packed)) g1_layout_bt_conn__global_1185 {
    uint8_t _pad_0x0[0x104];
    uint8_t field_0x104[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x106[0xa];
    uint8_t field_0x110[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_conn__global_1185, field_0x104) == 0x104, "g1_layout_bt_conn__global_1185.field_0x104");
_Static_assert(offsetof(struct g1_layout_bt_conn__global_1185, field_0x110) == 0x110, "g1_layout_bt_conn__global_1185.field_0x110");
_Static_assert(sizeof(struct g1_layout_bt_conn__global_1185) >= 0x114, "g1_layout_bt_conn__global_1185.size");

/* global_1189 | library | Static bt_conn_auth-info callback set registered via bt_conn_auth_info_cb_register (callback pointers + sys_snode_t list node). | D1+D2 verified
 * review: Registration object for bt_conn_auth_info_cb_register. Only two words observed (0x0,0x4); cannot pin which of pairing_complete/pairing_failed/bond_deleted/node they are, so left unverified. */
struct __attribute__((packed)) g1_layout_bt_conn_auth_info_cb__global_1189 {
    uint8_t cb0[0x4]; /* catalog type: void * */
    uint8_t cb1_or_node[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_bt_conn_auth_info_cb__global_1189, cb0) == 0x0, "g1_layout_bt_conn_auth_info_cb__global_1189.cb0");
_Static_assert(offsetof(struct g1_layout_bt_conn_auth_info_cb__global_1189, cb1_or_node) == 0x4, "g1_layout_bt_conn_auth_info_cb__global_1189.cb1_or_node");
_Static_assert(sizeof(struct g1_layout_bt_conn_auth_info_cb__global_1189) >= 0x8, "g1_layout_bt_conn_auth_info_cb__global_1189.size");

/* global_1218 | library | Zephyr GATT registered-callback node registered via bt_gatt_cb_register (slist node + att_mtu_updated cb). | D1+D2 verified
 * review: Only two fields observed (0x0 node, 0x4 att_mtu_updated), consistent with struct bt_gatt_cb {sys_snode_t _node; void (*att_mtu_updated)();}. Offsets plausible but I did not open bluetooth/gatt.h bt_gatt_cb def to fully confirm ordering; verified=false. */
struct __attribute__((packed)) g1_layout_bt_gatt_cb__global_1218 {
    uint8_t _node[0x4]; /* catalog type: void* */
    uint8_t att_mtu_updated[0x4]; /* catalog type: void* */
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_cb__global_1218, _node) == 0x0, "g1_layout_bt_gatt_cb__global_1218._node");
_Static_assert(offsetof(struct g1_layout_bt_gatt_cb__global_1218, att_mtu_updated) == 0x4, "g1_layout_bt_gatt_cb__global_1218.att_mtu_updated");
_Static_assert(sizeof(struct g1_layout_bt_gatt_cb__global_1218) >= 0x8, "g1_layout_bt_gatt_cb__global_1218.size");

/* global_1253 | library | Global scratch at 0x5e750 touched by bt_foreach_bond during bonded-device iteration (partial view of a bt_keys/bt_addr_le record). | D1+D2 verified
 * review: Unaligned reads (0x1 4-byte, 0xe 2-byte) are only a partial view; too little observed to verify against bt_keys header. */
struct __attribute__((packed)) g1_layout_bt_bond_iter_scratch__global_1253 {
    uint8_t _pad_0x0[0x1];
    uint8_t field_0x1[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x5[0x9];
    uint8_t field_0xe[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_bt_bond_iter_scratch__global_1253, field_0x1) == 0x1, "g1_layout_bt_bond_iter_scratch__global_1253.field_0x1");
_Static_assert(offsetof(struct g1_layout_bt_bond_iter_scratch__global_1253, field_0xe) == 0xe, "g1_layout_bt_bond_iter_scratch__global_1253.field_0xe");
_Static_assert(sizeof(struct g1_layout_bt_bond_iter_scratch__global_1253) >= 0x12, "g1_layout_bt_bond_iter_scratch__global_1253.size");

/* global_1256 | library | Zephyr Bluetooth bonded-keys storage pool (array of struct bt_keys) scanned by bt_keys_find_irk to resolve an IRK. | D1+D2 verified
 * review: Sparse accesses (0xe, 0x6a, 0x170) land inside different bt_keys array elements; cannot pin exact members without full element stride, so library_verified=false. */
struct __attribute__((packed)) g1_layout_bt_keys_pool__global_1256 {
    uint8_t _pad_0x0[0xe];
    uint8_t field_0xe[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x10[0x5a];
    uint8_t field_0x6a[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x6c[0x104];
    uint8_t field_0x170[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_keys_pool__global_1256, field_0xe) == 0xe, "g1_layout_bt_keys_pool__global_1256.field_0xe");
_Static_assert(offsetof(struct g1_layout_bt_keys_pool__global_1256, field_0x6a) == 0x6a, "g1_layout_bt_keys_pool__global_1256.field_0x6a");
_Static_assert(offsetof(struct g1_layout_bt_keys_pool__global_1256, field_0x170) == 0x170, "g1_layout_bt_keys_pool__global_1256.field_0x170");
_Static_assert(sizeof(struct g1_layout_bt_keys_pool__global_1256) >= 0x174, "g1_layout_bt_keys_pool__global_1256.size");

/* global_1271 | G1-original | Global SAADC driver state / sample-buffer region used by saadc_start_read; large (~0x630) block with a status word and a last-sample/error word at the tail (global at 0x5f95c). | D1+D2 verified
 * review: Single-cid G1 driver state. Only two tail scalar fields observed; large leading region is a buffer. Offsets kept. */
struct __attribute__((packed)) g1_layout_saadc_read_state__global_1271 {
    uint8_t _pad_0x0[0x5f0];
    uint8_t read_status[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x5f4[0x38];
    uint8_t last_sample_or_err[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_saadc_read_state__global_1271, read_status) == 0x5f0, "g1_layout_saadc_read_state__global_1271.read_status");
_Static_assert(offsetof(struct g1_layout_saadc_read_state__global_1271, last_sample_or_err) == 0x62c, "g1_layout_saadc_read_state__global_1271.last_sample_or_err");
_Static_assert(sizeof(struct g1_layout_saadc_read_state__global_1271) >= 0x630, "g1_layout_saadc_read_state__global_1271.size");

/* global_1272 | G1-original | Global PDM microphone driver state used by pdm_mic_event_handler (config/status word plus a trailing status-flag byte). | D1+D2 verified
 * review: G1-original driver global at 0x600e0; offsets unchanged. */
struct __attribute__((packed)) g1_layout_pdm_mic_event_ctx__global_1272 {
    uint8_t _pad_0x0[0x14];
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x3a];
    uint8_t status_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_pdm_mic_event_ctx__global_1272, field_0x14) == 0x14, "g1_layout_pdm_mic_event_ctx__global_1272.field_0x14");
_Static_assert(offsetof(struct g1_layout_pdm_mic_event_ctx__global_1272, status_flag) == 0x52, "g1_layout_pdm_mic_event_ctx__global_1272.status_flag");
_Static_assert(sizeof(struct g1_layout_pdm_mic_event_ctx__global_1272) >= 0x56, "g1_layout_pdm_mic_event_ctx__global_1272.size");

/* global_1293 | library | cJSON internal allocator hooks global referenced by cjson_parse_with_opts. | D1+D2 verified
 * review: Global @0x64c34. Best-fit is the static internal_hooks {allocate,deallocate,reallocate}: observed 0x4=deallocate, 0x8=reallocate, allocate@0x0 unobserved. Cannot fully disambiguate from global_error, so verified=false. */
struct __attribute__((packed)) g1_layout_cJSON_internal_hooks__global_1293 {
    uint8_t _pad_0x0[0x4];
    uint8_t deallocate_fn[0x4]; /* catalog type: void*; SDK member: internal_hooks.deallocate */
    uint8_t reallocate_fn[0x4]; /* catalog type: void*; SDK member: internal_hooks.reallocate */
};
_Static_assert(offsetof(struct g1_layout_cJSON_internal_hooks__global_1293, deallocate_fn) == 0x4, "g1_layout_cJSON_internal_hooks__global_1293.deallocate_fn");
_Static_assert(offsetof(struct g1_layout_cJSON_internal_hooks__global_1293, reallocate_fn) == 0x8, "g1_layout_cJSON_internal_hooks__global_1293.reallocate_fn");
_Static_assert(sizeof(struct g1_layout_cJSON_internal_hooks__global_1293) >= 0xc, "g1_layout_cJSON_internal_hooks__global_1293.size");

/* global_1323 | G1-original | Large global PDM microphone configuration block; pdm_configure_pins writes two trailer status/config words. | D1+D2 verified
 * review: Kept naming; offsets unchanged. Only trailer fields observed. */
struct __attribute__((packed)) g1_layout_pdm_pin_config_block__global_1323 {
    uint8_t _pad_0x0[0x520];
    uint8_t pin_config[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x524[0x1c];
    uint8_t pin_config_status[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_pdm_pin_config_block__global_1323, pin_config) == 0x520, "g1_layout_pdm_pin_config_block__global_1323.pin_config");
_Static_assert(offsetof(struct g1_layout_pdm_pin_config_block__global_1323, pin_config_status) == 0x540, "g1_layout_pdm_pin_config_block__global_1323.pin_config_status");
_Static_assert(sizeof(struct g1_layout_pdm_pin_config_block__global_1323) >= 0x544, "g1_layout_pdm_pin_config_block__global_1323.size");

/* global_1324 | library | nrfx PDM driver control-block/state (0x661cc) accessed by nrfx_pdm_init; two index/handle words observed. | D1+D2 verified
 * review: nrfx PDM internal control block is not a public-header struct (defined in nrfx_pdm.c); offsets 0x4/0x10 could not be verified against a header. Kept ground-truth offsets. */
struct __attribute__((packed)) g1_layout_nrfx_pdm_cb__global_1324 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_pdm_cb__global_1324, field_0x4) == 0x4, "g1_layout_nrfx_pdm_cb__global_1324.field_0x4");
_Static_assert(offsetof(struct g1_layout_nrfx_pdm_cb__global_1324, field_0x10) == 0x10, "g1_layout_nrfx_pdm_cb__global_1324.field_0x10");
_Static_assert(sizeof(struct g1_layout_nrfx_pdm_cb__global_1324) >= 0x14, "g1_layout_nrfx_pdm_cb__global_1324.size");

/* global_1326 | library | nrfx PDM (pulse-density microphone) driver control-block state accessed by nrfx_pdm_start: a driver-state enum byte and a flag byte. | D1+D2 verified
 * review: nrfx_pdm control block is a file-local static in nrfx_pdm.c (no public header exposes member offsets); kept sonnet naming, library_verified=false. */
struct __attribute__((packed)) g1_layout_nrfx_pdm_drv_state__global_1326 {
    uint8_t _pad_0x0[0x10];
    uint8_t drv_state[0x1]; /* catalog type: uint8_t */
    uint8_t flag_0x11[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_pdm_drv_state__global_1326, drv_state) == 0x10, "g1_layout_nrfx_pdm_drv_state__global_1326.drv_state");
_Static_assert(offsetof(struct g1_layout_nrfx_pdm_drv_state__global_1326, flag_0x11) == 0x11, "g1_layout_nrfx_pdm_drv_state__global_1326.flag_0x11");
_Static_assert(sizeof(struct g1_layout_nrfx_pdm_drv_state__global_1326) >= 0x12, "g1_layout_nrfx_pdm_drv_state__global_1326.size");

/* global_1328 | library | nrfx PDM driver control block; buffer-request/error flag bytes touched by nrfx_pdm_buffer_set. | D1+D2 verified
 * review: nrfx_pdm_cb_t is file-static inside nrfx_pdm.c (no public header exposes its layout), so offsets could not be verified. Two flag bytes at 0x10/0x11. */
struct __attribute__((packed)) g1_layout_nrfx_pdm_cb__global_1328 {
    uint8_t _pad_0x0[0x10];
    uint8_t buffer_requested[0x1]; /* catalog type: uint8_t */
    uint8_t error_flag[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_pdm_cb__global_1328, buffer_requested) == 0x10, "g1_layout_nrfx_pdm_cb__global_1328.buffer_requested");
_Static_assert(offsetof(struct g1_layout_nrfx_pdm_cb__global_1328, error_flag) == 0x11, "g1_layout_nrfx_pdm_cb__global_1328.error_flag");
_Static_assert(sizeof(struct g1_layout_nrfx_pdm_cb__global_1328) >= 0x12, "g1_layout_nrfx_pdm_cb__global_1328.size");

/* global_1329 | library | nrfx PDM driver control block (m_cb) queried by nrfx_pdm_stop: state byte + flag byte. | D1+D2 verified
 * review: nrfx_pdm m_cb is a static in nrfx_pdm.c, not a public header struct; 0x10/0x11 offsets unverifiable. verified=false. */
struct __attribute__((packed)) g1_layout_nrfx_pdm_cb__global_1329 {
    uint8_t _pad_0x0[0x10];
    uint8_t state[0x1]; /* catalog type: uint8_t */
    uint8_t error_mode[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_pdm_cb__global_1329, state) == 0x10, "g1_layout_nrfx_pdm_cb__global_1329.state");
_Static_assert(offsetof(struct g1_layout_nrfx_pdm_cb__global_1329, error_mode) == 0x11, "g1_layout_nrfx_pdm_cb__global_1329.error_mode");
_Static_assert(sizeof(struct g1_layout_nrfx_pdm_cb__global_1329) >= 0x12, "g1_layout_nrfx_pdm_cb__global_1329.size");

/* global_1330 | G1-original | Static PDM mic capture buffer/state around nrfx_pdm_stop (global 0x66360): status/count word at each end bracketing a ~0x4f8-byte buffer. | D1+D2 verified
 * review: nrfx_pdm_stop is an app wrapper; the global is a G1 capture buffer, not an nrfx driver struct. */
struct __attribute__((packed)) g1_layout_pdm_capture_buffer_state__global_1330 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x4f8];
    uint8_t field_0x500[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_pdm_capture_buffer_state__global_1330, field_0x4) == 0x4, "g1_layout_pdm_capture_buffer_state__global_1330.field_0x4");
_Static_assert(offsetof(struct g1_layout_pdm_capture_buffer_state__global_1330, field_0x500) == 0x500, "g1_layout_pdm_capture_buffer_state__global_1330.field_0x500");
_Static_assert(sizeof(struct g1_layout_pdm_capture_buffer_state__global_1330) >= 0x504, "g1_layout_pdm_capture_buffer_state__global_1330.size");

/* global_1336 | library | nrfx QSPI driver control block (global 0x66668): transfer-state word at 0x8 (read) and result/flags word at 0x24 (written) by qspi_event_xfer_handle. | D1+D2 verified
 * review: Distinct footprint from the global_1340 QSPI cb group (only 2 fields, size 0x28) so kept separate. nrfx_qspi internal cb has no pinned header; library_verified=false. */
struct __attribute__((packed)) g1_layout_nrfx_qspi_control_block__global_1336 {
    uint8_t _pad_0x0[0x8];
    uint8_t xfer_state[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x18];
    uint8_t result_or_flags[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_control_block__global_1336, xfer_state) == 0x8, "g1_layout_nrfx_qspi_control_block__global_1336.xfer_state");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_control_block__global_1336, result_or_flags) == 0x24, "g1_layout_nrfx_qspi_control_block__global_1336.result_or_flags");
_Static_assert(sizeof(struct g1_layout_nrfx_qspi_control_block__global_1336) >= 0x28, "g1_layout_nrfx_qspi_control_block__global_1336.size");

/* global_1337 | library | nRF5340 QSPI peripheral register block; CINSTRDAT0/1 custom-instruction data registers accessed by nrf_qspi_cinstrdata_get. | D1+D2 verified
 * review: Verified against nrf5340_application.h: CINSTRDAT0 @0x638, CINSTRDAT1 @0x63C — exact match to observed. Ghidra's fixed-address 0x6671c is a pointer-to-peripheral artifact; the offsets are QSPI register offsets. */
struct __attribute__((packed)) g1_layout_NRF_QSPI_Type__global_1337 {
    uint8_t _pad_0x0[0x638];
    uint8_t CINSTRDAT0[0x4]; /* catalog type: uint32_t; SDK member: CINSTRDAT0 */
    uint8_t CINSTRDAT1[0x4]; /* catalog type: uint32_t; SDK member: CINSTRDAT1 */
};
_Static_assert(offsetof(struct g1_layout_NRF_QSPI_Type__global_1337, CINSTRDAT0) == 0x638, "g1_layout_NRF_QSPI_Type__global_1337.CINSTRDAT0");
_Static_assert(offsetof(struct g1_layout_NRF_QSPI_Type__global_1337, CINSTRDAT1) == 0x63c, "g1_layout_NRF_QSPI_Type__global_1337.CINSTRDAT1");
_Static_assert(sizeof(struct g1_layout_NRF_QSPI_Type__global_1337) >= 0x640, "g1_layout_NRF_QSPI_Type__global_1337.size");

/* global_1338 | library | nRF5340 NRF_QSPI peripheral register block; the two trailing words are the custom-instruction data registers CINSTRDAT0/CINSTRDAT1 written by nrf_qspi_cinstrdata_set. | D1+D2 verified
 * review: Verified against MDK nrf5340_application.h: CINSTRDAT0 @0x638, CINSTRDAT1 @0x63C match exactly. Global at 0x66780 is NRF_QSPI base. */
struct __attribute__((packed)) g1_layout_qspi_cinstrdat_regs__global_1338 {
    uint8_t _pad_0x0[0x638];
    uint8_t CINSTRDAT0[0x4]; /* catalog type: uint32_t; SDK member: CINSTRDAT0 */
    uint8_t CINSTRDAT1[0x4]; /* catalog type: uint32_t; SDK member: CINSTRDAT1 */
};
_Static_assert(offsetof(struct g1_layout_qspi_cinstrdat_regs__global_1338, CINSTRDAT0) == 0x638, "g1_layout_qspi_cinstrdat_regs__global_1338.CINSTRDAT0");
_Static_assert(offsetof(struct g1_layout_qspi_cinstrdat_regs__global_1338, CINSTRDAT1) == 0x63c, "g1_layout_qspi_cinstrdat_regs__global_1338.CINSTRDAT1");
_Static_assert(sizeof(struct g1_layout_qspi_cinstrdat_regs__global_1338) >= 0x640, "g1_layout_qspi_cinstrdat_regs__global_1338.size");

/* global_1340 | library | nrfx QSPI driver internal control block (static singleton); tail fields 0x524-0x53c touched by qspi_workaround_apply (nRF5340 QSPI erratum patch) and nrfx_qspi_uninit. | D1+D2 verified
 * review: MERGED global_1340 (qspi_workaround_apply @0x6684c) + global_1347 (nrfx_qspi_uninit @0x66bc0): identical tail footprint (0x524..0x53c inside a >=0x540 object), both QSPI-driver internal state = same type. nrfx_qspi's control block is a private static struct with no pinned public header, so library_verified=false. Note the two global addresses differ (0x6684c vs 0x66bc0). */
struct __attribute__((packed)) g1_layout_nrfx_qspi_control_block__global_1340 {
    uint8_t _pad_0x0[0x524];
    uint8_t field_0x524[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x528[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x52c[0x4];
    uint8_t field_0x530[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x534[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x538[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x53c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_control_block__global_1340, field_0x524) == 0x524, "g1_layout_nrfx_qspi_control_block__global_1340.field_0x524");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_control_block__global_1340, field_0x528) == 0x528, "g1_layout_nrfx_qspi_control_block__global_1340.field_0x528");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_control_block__global_1340, field_0x530) == 0x530, "g1_layout_nrfx_qspi_control_block__global_1340.field_0x530");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_control_block__global_1340, field_0x534) == 0x534, "g1_layout_nrfx_qspi_control_block__global_1340.field_0x534");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_control_block__global_1340, field_0x538) == 0x538, "g1_layout_nrfx_qspi_control_block__global_1340.field_0x538");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_control_block__global_1340, field_0x53c) == 0x53c, "g1_layout_nrfx_qspi_control_block__global_1340.field_0x53c");
_Static_assert(sizeof(struct g1_layout_nrfx_qspi_control_block__global_1340) >= 0x540, "g1_layout_nrfx_qspi_control_block__global_1340.size");

/* global_1341 | library | Memory-mapped NRF_QSPI peripheral register block poked by the QSPI silicon-anomaly workaround routine (qspi_workaround_apply). | D1+D2 verified
 * review: Footprint-collision group split: this generic 5x uint32 shape collided with md5_context/datetime/qspi_pins/qspi_cinstr. Emitted separately. Word reads at 0x4-0x14 are the QSPI TASKS/config region; full register verification not done (idx4 approximations). */
struct __attribute__((packed)) g1_layout_qspi_workaround_regs__global_1341 {
    uint8_t _pad_0x0[0x4];
    uint8_t reg_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t reg_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t reg_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t reg_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t reg_0x14[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_qspi_workaround_regs__global_1341, reg_0x4) == 0x4, "g1_layout_qspi_workaround_regs__global_1341.reg_0x4");
_Static_assert(offsetof(struct g1_layout_qspi_workaround_regs__global_1341, reg_0x8) == 0x8, "g1_layout_qspi_workaround_regs__global_1341.reg_0x8");
_Static_assert(offsetof(struct g1_layout_qspi_workaround_regs__global_1341, reg_0xc) == 0xc, "g1_layout_qspi_workaround_regs__global_1341.reg_0xc");
_Static_assert(offsetof(struct g1_layout_qspi_workaround_regs__global_1341, reg_0x10) == 0x10, "g1_layout_qspi_workaround_regs__global_1341.reg_0x10");
_Static_assert(offsetof(struct g1_layout_qspi_workaround_regs__global_1341, reg_0x14) == 0x14, "g1_layout_qspi_workaround_regs__global_1341.reg_0x14");
_Static_assert(sizeof(struct g1_layout_qspi_workaround_regs__global_1341) >= 0x18, "g1_layout_qspi_workaround_regs__global_1341.size");

/* global_1344 | library | nrfx QSPI driver control block, accessed by nrfx_qspi_cinstr_xfer during a custom-instruction transfer. | D1+D2 verified
 * review: Global @0x66adc. Only two char fields observed; offsets not verifiable against nrfxlib header. */
struct __attribute__((packed)) g1_layout_nrfx_qspi_cb__global_1344 {
    uint8_t _pad_0x0[0x30];
    uint8_t field_0x30[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x31[0x7];
    uint8_t field_0x38[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_cb__global_1344, field_0x30) == 0x30, "g1_layout_nrfx_qspi_cb__global_1344.field_0x30");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_cb__global_1344, field_0x38) == 0x38, "g1_layout_nrfx_qspi_cb__global_1344.field_0x38");
_Static_assert(sizeof(struct g1_layout_nrfx_qspi_cb__global_1344) >= 0x39, "g1_layout_nrfx_qspi_cb__global_1344.size");

/* global_1355 | library | libmetal generic bus descriptor torn down by metal_generic_bus_unregister; two pointer-ish list/ops words near 0x24. | D1+D2 verified
 * review: Accessor is a libmetal bus function so likely struct metal_bus, but only two idx4 words observed and libmetal bus layout not pinned; library_verified=false. */
struct __attribute__((packed)) g1_layout_metal_generic_bus__global_1355 {
    uint8_t _pad_0x0[0x24];
    uint8_t list_node_or_name[0x4]; /* catalog type: uint32_t */
    uint8_t ops_or_next[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_metal_generic_bus__global_1355, list_node_or_name) == 0x24, "g1_layout_metal_generic_bus__global_1355.list_node_or_name");
_Static_assert(offsetof(struct g1_layout_metal_generic_bus__global_1355, ops_or_next) == 0x28, "g1_layout_metal_generic_bus__global_1355.ops_or_next");
_Static_assert(sizeof(struct g1_layout_metal_generic_bus__global_1355) >= 0x2c, "g1_layout_metal_generic_bus__global_1355.size");

/* global_1358 | library | LC3 codec attack-detector running-state / config block at fixed global 0x684a4, read by lc3_attdet_run (liblc3). Seven consecutive 32-bit parameter words. | D1+D2 verified
 * review: SPLIT from footprint-collision group global_1358: the 7 cids only share a generic 'seven uint32 at +0x4' shape across unrelated subsystems (LC3, IPC, mcumgr, QSPI, byteorder, libmetal) and are NOT the same object. Kept as its own struct. liblc3 attdet internal state has no pinned public header to check offsets against, so library_verified=false. */
struct __attribute__((packed)) g1_layout_lc3_attdet_state__global_1358 {
    uint8_t _pad_0x0[0x4];
    uint8_t attdet_word0[0x4]; /* catalog type: uint32_t */
    uint8_t attdet_word1[0x4]; /* catalog type: uint32_t */
    uint8_t attdet_word2[0x4]; /* catalog type: uint32_t */
    uint8_t attdet_word3[0x4]; /* catalog type: uint32_t */
    uint8_t attdet_word4[0x4]; /* catalog type: uint32_t */
    uint8_t attdet_word5[0x4]; /* catalog type: uint32_t */
    uint8_t attdet_word6[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_attdet_state__global_1358, attdet_word0) == 0x4, "g1_layout_lc3_attdet_state__global_1358.attdet_word0");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_state__global_1358, attdet_word1) == 0x8, "g1_layout_lc3_attdet_state__global_1358.attdet_word1");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_state__global_1358, attdet_word2) == 0xc, "g1_layout_lc3_attdet_state__global_1358.attdet_word2");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_state__global_1358, attdet_word3) == 0x10, "g1_layout_lc3_attdet_state__global_1358.attdet_word3");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_state__global_1358, attdet_word4) == 0x14, "g1_layout_lc3_attdet_state__global_1358.attdet_word4");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_state__global_1358, attdet_word5) == 0x18, "g1_layout_lc3_attdet_state__global_1358.attdet_word5");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_state__global_1358, attdet_word6) == 0x1c, "g1_layout_lc3_attdet_state__global_1358.attdet_word6");
_Static_assert(sizeof(struct g1_layout_lc3_attdet_state__global_1358) >= 0x20, "g1_layout_lc3_attdet_state__global_1358.size");

/* global_1360 | library | liblc3 bandwidth-detection internal lookup table (0x68b0c) referenced by lc3_bwdet_run. | D1+D2 verified
 * review: liblc3 internal const data, not a named public struct; cannot verify offsets against a header. Kept offsets. */
struct __attribute__((packed)) g1_layout_lc3_bwdet_table__global_1360 {
    uint8_t _pad_0x0[0x4];
    uint8_t entry_1[0x4]; /* catalog type: uint32_t */
    uint8_t entry_2[0x4]; /* catalog type: uint32_t */
    uint8_t entry_3[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_bwdet_table__global_1360, entry_1) == 0x4, "g1_layout_lc3_bwdet_table__global_1360.entry_1");
_Static_assert(offsetof(struct g1_layout_lc3_bwdet_table__global_1360, entry_2) == 0x8, "g1_layout_lc3_bwdet_table__global_1360.entry_2");
_Static_assert(offsetof(struct g1_layout_lc3_bwdet_table__global_1360, entry_3) == 0xc, "g1_layout_lc3_bwdet_table__global_1360.entry_3");
_Static_assert(sizeof(struct g1_layout_lc3_bwdet_table__global_1360) >= 0x10, "g1_layout_lc3_bwdet_table__global_1360.size");

/* global_1394 | library | Zephyr spinlock-validation bookkeeping global accessed by z_spin_unlock_valid to detect double-unlock / wrong-owner errors (CONFIG_SPIN_VALIDATE). | D1+D2 verified
 * review: Spin-validate tracking lives in kernel spinlock validation code as internal per-CPU arrays, not a header-exposed struct; kept naming, library_verified=false. */
struct __attribute__((packed)) g1_layout_spinlock_validate_state__global_1394 {
    uint8_t _pad_0x0[0x8];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x4];
    uint8_t field_0x10[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_spinlock_validate_state__global_1394, field_0x8) == 0x8, "g1_layout_spinlock_validate_state__global_1394.field_0x8");
_Static_assert(offsetof(struct g1_layout_spinlock_validate_state__global_1394, field_0x10) == 0x10, "g1_layout_spinlock_validate_state__global_1394.field_0x10");
_Static_assert(sizeof(struct g1_layout_spinlock_validate_state__global_1394) >= 0x14, "g1_layout_spinlock_validate_state__global_1394.size");

/* global_1395 | library | Kernel object read by z_spin_lock_set_owner while stamping a k_spinlock owner (SPIN_VALIDATE build). | D1+D2 verified
 * review: Sonnet called it k_spinlock, but a k_spinlock's thread_cpu is at 0x0 while the observed reads are at 0x8 and 0x10 - these do not fit a bare k_spinlock, so this global is more likely the per-CPU/current-thread source read during owner stamping. Left unverified; offsets do not match the proposed type. */
struct __attribute__((packed)) g1_layout_spinlock_owner_source__global_1395 {
    uint8_t _pad_0x0[0x8];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x4];
    uint8_t field_0x10[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_spinlock_owner_source__global_1395, field_0x8) == 0x8, "g1_layout_spinlock_owner_source__global_1395.field_0x8");
_Static_assert(offsetof(struct g1_layout_spinlock_owner_source__global_1395, field_0x10) == 0x10, "g1_layout_spinlock_owner_source__global_1395.field_0x10");
_Static_assert(sizeof(struct g1_layout_spinlock_owner_source__global_1395) >= 0x14, "g1_layout_spinlock_owner_source__global_1395.size");

/* global_1403 | G1-original | G1-original global scheduler cache at 0x7382c: count + two list pointers. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_sched_update_cache__global_1403 {
    uint8_t _pad_0x0[0x8];
    uint8_t count[0x4]; /* catalog type: uint32_t */
    uint8_t list_head[0x4]; /* catalog type: void* */
    uint8_t _pad_0x10[0xc];
    uint8_t aux_ptr[0x4]; /* catalog type: void* */
};
_Static_assert(offsetof(struct g1_layout_sched_update_cache__global_1403, count) == 0x8, "g1_layout_sched_update_cache__global_1403.count");
_Static_assert(offsetof(struct g1_layout_sched_update_cache__global_1403, list_head) == 0xc, "g1_layout_sched_update_cache__global_1403.list_head");
_Static_assert(offsetof(struct g1_layout_sched_update_cache__global_1403, aux_ptr) == 0x1c, "g1_layout_sched_update_cache__global_1403.aux_ptr");
_Static_assert(sizeof(struct g1_layout_sched_update_cache__global_1403) >= 0x20, "g1_layout_sched_update_cache__global_1403.size");

/* global_1405 | library | Zephyr kernel scheduler global (0x73a64) touched by z_reschedule; ready-queue/cpu-state ints. | D1+D2 verified
 * review: Only two ints observed at 0x8/0x18; insufficient to pin against struct _kernel/_ready_q offsets. */
struct __attribute__((packed)) g1_layout_z_kernel_sched_state__global_1405 {
    uint8_t _pad_0x0[0x8];
    uint8_t field_0x8[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0xc[0xc];
    uint8_t field_0x18[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_z_kernel_sched_state__global_1405, field_0x8) == 0x8, "g1_layout_z_kernel_sched_state__global_1405.field_0x8");
_Static_assert(offsetof(struct g1_layout_z_kernel_sched_state__global_1405, field_0x18) == 0x18, "g1_layout_z_kernel_sched_state__global_1405.field_0x18");
_Static_assert(sizeof(struct g1_layout_z_kernel_sched_state__global_1405) >= 0x1c, "g1_layout_z_kernel_sched_state__global_1405.size");

/* global_1431 | G1-original | G1-original global scratch context holding parse parameters (base/width) for scanf_convert_integer_field. | D1+D2 verified
 * review: G1-original custom scanf helper state. */
struct __attribute__((packed)) g1_layout_scanf_field_parse_ctx__global_1431 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_scanf_field_parse_ctx__global_1431, field_0x4) == 0x4, "g1_layout_scanf_field_parse_ctx__global_1431.field_0x4");
_Static_assert(offsetof(struct g1_layout_scanf_field_parse_ctx__global_1431, field_0x8) == 0x8, "g1_layout_scanf_field_parse_ctx__global_1431.field_0x8");
_Static_assert(sizeof(struct g1_layout_scanf_field_parse_ctx__global_1431) >= 0xc, "g1_layout_scanf_field_parse_ctx__global_1431.size");

/* global_1450 | library | Arm CryptoCell (CC3xx) HAL hardware register/state block written by CC_HalClearInterruptBit at offsets 0x108 and 0xa08 (global base 0x7a2a8). | D1+D2 verified
 * review: Library HW register block (CC3xx HAL). Could not locate a named struct in the pinned headers with these exact offsets to verify against; kept offsets, verified=false. */
struct __attribute__((packed)) g1_layout_cc3xx_hal_reg_block__global_1450 {
    uint8_t _pad_0x0[0x108];
    uint8_t reg_0x108[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10c[0x8fc];
    uint8_t reg_0xa08[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cc3xx_hal_reg_block__global_1450, reg_0x108) == 0x108, "g1_layout_cc3xx_hal_reg_block__global_1450.reg_0x108");
_Static_assert(offsetof(struct g1_layout_cc3xx_hal_reg_block__global_1450, reg_0xa08) == 0xa08, "g1_layout_cc3xx_hal_reg_block__global_1450.reg_0xa08");
_Static_assert(sizeof(struct g1_layout_cc3xx_hal_reg_block__global_1450) >= 0xa0c, "g1_layout_cc3xx_hal_reg_block__global_1450.size");

/* global_1452 | G1-original | Fixed-address CryptoCell crypto dispatch workspace (0xa00-byte scratch buffer plus length/status trailer) used by cc_crypto_dispatch_or_error. | D1+D2 verified
 * review: G1-original crypto workspace at 0x7a3c8; offsets unchanged. */
struct __attribute__((packed)) g1_layout_cc_crypto_workspace__global_1452 {
    uint8_t _pad_0x0[0xa00];
    uint8_t data_len[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xa04[0x4];
    uint8_t status_code[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cc_crypto_workspace__global_1452, data_len) == 0xa00, "g1_layout_cc_crypto_workspace__global_1452.data_len");
_Static_assert(offsetof(struct g1_layout_cc_crypto_workspace__global_1452, status_code) == 0xa08, "g1_layout_cc_crypto_workspace__global_1452.status_code");
_Static_assert(sizeof(struct g1_layout_cc_crypto_workspace__global_1452) >= 0xa0c, "g1_layout_cc_crypto_workspace__global_1452.size");

/* global_1453 | library | Arm CryptoCell (CC310/CC312) TRNG HAL wait/interrupt state used by CC_HalWaitInterruptRND. | D1+D2 verified
 * review: Global @0x7a3a0, size>=0xa0c. LIBRARY member. Sparse observed offsets (0x104,0xa00,0xa08) inside a large HW register/state block; cannot map to a named struct. */
struct __attribute__((packed)) g1_layout_cc_rnd_hal_state__global_1453 {
    uint8_t _pad_0x0[0x104];
    uint8_t isr_flag[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x108[0x8f8];
    uint8_t sample_count[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xa04[0x4];
    uint8_t result_word[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cc_rnd_hal_state__global_1453, isr_flag) == 0x104, "g1_layout_cc_rnd_hal_state__global_1453.isr_flag");
_Static_assert(offsetof(struct g1_layout_cc_rnd_hal_state__global_1453, sample_count) == 0xa00, "g1_layout_cc_rnd_hal_state__global_1453.sample_count");
_Static_assert(offsetof(struct g1_layout_cc_rnd_hal_state__global_1453, result_word) == 0xa08, "g1_layout_cc_rnd_hal_state__global_1453.result_word");
_Static_assert(sizeof(struct g1_layout_cc_rnd_hal_state__global_1453) >= 0xa0c, "g1_layout_cc_rnd_hal_state__global_1453.size");

/* global_1464 | library | Hardware TRNG driver context started by startTrngHW (a LIBRARY-class CryptoCell/CC3xx routine); large opaque buffer with two trailing status/count words. | D1+D2 verified
 * review: Kept naming; offsets unchanged. Exact CryptoCell TRNG context header not resolvable, only two trailer words observed; library_verified=false. */
struct __attribute__((packed)) g1_layout_trng_hw_context__global_1464 {
    uint8_t _pad_0x0[0x1c4];
    uint8_t trng_status[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1c8[0x10];
    uint8_t trng_byte_count[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_trng_hw_context__global_1464, trng_status) == 0x1c4, "g1_layout_trng_hw_context__global_1464.trng_status");
_Static_assert(offsetof(struct g1_layout_trng_hw_context__global_1464, trng_byte_count) == 0x1d8, "g1_layout_trng_hw_context__global_1464.trng_byte_count");
_Static_assert(sizeof(struct g1_layout_trng_hw_context__global_1464) >= 0x1dc, "g1_layout_trng_hw_context__global_1464.size");

/* global_1465 | library | CryptoCell/Oberon TRNG source state object (0x7a9ac) accessed by getTrngSource; large opaque region with two trailing status/count words. | D1+D2 verified
 * review: CryptoCell RND state is opaque; only +0x130/+0x138 observed. No header to verify against. Kept offsets. */
struct __attribute__((packed)) g1_layout_cc_trng_state__global_1465 {
    uint8_t _pad_0x0[0x130];
    uint8_t field_0x130[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x134[0x4];
    uint8_t field_0x138[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cc_trng_state__global_1465, field_0x130) == 0x130, "g1_layout_cc_trng_state__global_1465.field_0x130");
_Static_assert(offsetof(struct g1_layout_cc_trng_state__global_1465, field_0x138) == 0x138, "g1_layout_cc_trng_state__global_1465.field_0x138");
_Static_assert(sizeof(struct g1_layout_cc_trng_state__global_1465) >= 0x13c, "g1_layout_cc_trng_state__global_1465.size");

/* global_1479 | library | Large (0xb10-byte) CryptoCell hash-driver context/state global manipulated by ProcessHashDrv: scattered status/length scalars around a big internal buffer. | D1+D2 verified
 * review: ProcessHashDrv is a LIBRARY member (CryptoCell runtime); the exact HashContext struct is proprietary/unavailable in the pinned tree, so offsets cannot be verified. Kept sonnet field guesses. */
struct __attribute__((packed)) g1_layout_hash_drv_context__global_1479 {
    uint8_t _pad_0x0[0x650];
    uint8_t status[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x654[0x8];
    uint8_t field_0x65c[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x660[0x168];
    uint8_t field_0x7c8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x7cc[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x7d0[0x140];
    uint8_t field_0x910[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x914[0x1f8];
    uint8_t field_0xb0c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_hash_drv_context__global_1479, status) == 0x650, "g1_layout_hash_drv_context__global_1479.status");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__global_1479, field_0x65c) == 0x65c, "g1_layout_hash_drv_context__global_1479.field_0x65c");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__global_1479, field_0x7c8) == 0x7c8, "g1_layout_hash_drv_context__global_1479.field_0x7c8");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__global_1479, field_0x7cc) == 0x7cc, "g1_layout_hash_drv_context__global_1479.field_0x7cc");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__global_1479, field_0x910) == 0x910, "g1_layout_hash_drv_context__global_1479.field_0x910");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__global_1479, field_0xb0c) == 0xb0c, "g1_layout_hash_drv_context__global_1479.field_0xb0c");
_Static_assert(sizeof(struct g1_layout_hash_drv_context__global_1479) >= 0xb10, "g1_layout_hash_drv_context__global_1479.size");

/* global_1480 | library | AES key/round table + status context initialized by InitAes (LIBRARY crypto routine); ~0x914 bytes. | D1+D2 verified
 * review: InitAes is a LIBRARY-class crypto function; the backing struct is a proprietary/CryptoCell AES table blob with no matching pinned header, so unverified. Only an init flag (0x4c0) and a trailing status word (0x910) are observed within the 0x914-byte object. */
struct __attribute__((packed)) g1_layout_aes_context_tables__global_1480 {
    uint8_t _pad_0x0[0x4c0];
    uint8_t init_flag[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4c4[0x44c];
    uint8_t status[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_aes_context_tables__global_1480, init_flag) == 0x4c0, "g1_layout_aes_context_tables__global_1480.init_flag");
_Static_assert(offsetof(struct g1_layout_aes_context_tables__global_1480, status) == 0x910, "g1_layout_aes_context_tables__global_1480.status");
_Static_assert(sizeof(struct g1_layout_aes_context_tables__global_1480) >= 0x914, "g1_layout_aes_context_tables__global_1480.size");

/* global_1483 | library | CryptoCell/CC3xx AES driver context/register-shadow at 0x7b9a8 used by ProcessAesDrv (sparse control/status words across a ~0xc2c region). | D1+D2 verified
 * review: nrf_cc3xx is a closed-source blob (LIBRARY member); no header available to verify the 0x400..0xc28 offsets. verified=false. */
struct __attribute__((packed)) g1_layout_cc3xx_aes_drv_ctx__global_1483 {
    uint8_t _pad_0x0[0x400];
    uint8_t field_0x400[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x404[0x3c];
    uint8_t field_0x440[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x444[0x1c];
    uint8_t field_0x460[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x464[0x3ac];
    uint8_t field_0x810[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x814[0x2f8];
    uint8_t field_0xb0c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xb10[0x118];
    uint8_t field_0xc28[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cc3xx_aes_drv_ctx__global_1483, field_0x400) == 0x400, "g1_layout_cc3xx_aes_drv_ctx__global_1483.field_0x400");
_Static_assert(offsetof(struct g1_layout_cc3xx_aes_drv_ctx__global_1483, field_0x440) == 0x440, "g1_layout_cc3xx_aes_drv_ctx__global_1483.field_0x440");
_Static_assert(offsetof(struct g1_layout_cc3xx_aes_drv_ctx__global_1483, field_0x460) == 0x460, "g1_layout_cc3xx_aes_drv_ctx__global_1483.field_0x460");
_Static_assert(offsetof(struct g1_layout_cc3xx_aes_drv_ctx__global_1483, field_0x810) == 0x810, "g1_layout_cc3xx_aes_drv_ctx__global_1483.field_0x810");
_Static_assert(offsetof(struct g1_layout_cc3xx_aes_drv_ctx__global_1483, field_0xb0c) == 0xb0c, "g1_layout_cc3xx_aes_drv_ctx__global_1483.field_0xb0c");
_Static_assert(offsetof(struct g1_layout_cc3xx_aes_drv_ctx__global_1483, field_0xc28) == 0xc28, "g1_layout_cc3xx_aes_drv_ctx__global_1483.field_0xc28");
_Static_assert(sizeof(struct g1_layout_cc3xx_aes_drv_ctx__global_1483) >= 0xc2c, "g1_layout_cc3xx_aes_drv_ctx__global_1483.size");

/* global_1484 | library | Large CryptoCell/nrf_cc3xx AES hardware-driver context (global 0x7bbb0, >=0x814 bytes); FinishAesDrv (a LIBRARY fn) reads status/config near front, writes completion flags near end. | D1+D2 verified
 * review: Proprietary CryptoCell context; no pinned header with field offsets available, so unverified. */
struct __attribute__((packed)) g1_layout_aes_drv_ctx__global_1484 {
    uint8_t _pad_0x0[0x440];
    uint8_t field_0x440[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x444[0x1c];
    uint8_t field_0x460[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x464[0x18];
    uint8_t field_0x47c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x480[0x390];
    uint8_t field_0x810[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__global_1484, field_0x440) == 0x440, "g1_layout_aes_drv_ctx__global_1484.field_0x440");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__global_1484, field_0x460) == 0x460, "g1_layout_aes_drv_ctx__global_1484.field_0x460");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__global_1484, field_0x47c) == 0x47c, "g1_layout_aes_drv_ctx__global_1484.field_0x47c");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__global_1484, field_0x810) == 0x810, "g1_layout_aes_drv_ctx__global_1484.field_0x810");
_Static_assert(sizeof(struct g1_layout_aes_drv_ctx__global_1484) >= 0x814, "g1_layout_aes_drv_ctx__global_1484.size");

/* global_1561 | library | QSPI write region / register+EasyDMA block (global 0x66630) written by nrfx_qspi_write: task/trigger word at 0x100 and config/status words at 0x504/0x510. | D1+D2 verified
 * review: Distinct footprint (0x100/0x504/0x510 across 0x514) from other QSPI globals; kept separate. Not offset-matched to a public header; library_verified=false. */
struct __attribute__((packed)) g1_layout_nrfx_qspi_write_region__global_1561 {
    uint8_t _pad_0x0[0x100];
    uint8_t field_0x100[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x104[0x400];
    uint8_t field_0x504[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x508[0x8];
    uint8_t field_0x510[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_write_region__global_1561, field_0x100) == 0x100, "g1_layout_nrfx_qspi_write_region__global_1561.field_0x100");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_write_region__global_1561, field_0x504) == 0x504, "g1_layout_nrfx_qspi_write_region__global_1561.field_0x504");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_write_region__global_1561, field_0x510) == 0x510, "g1_layout_nrfx_qspi_write_region__global_1561.field_0x510");
_Static_assert(sizeof(struct g1_layout_nrfx_qspi_write_region__global_1561) >= 0x514, "g1_layout_nrfx_qspi_write_region__global_1561.size");

/* global_1562 | library | nrfx QSPI driver control-block / state referenced by nrfx_qspi_write; two index words read at 0x30 and 0x38 (global base 0x6661c). | D1+D2 verified
 * review: nrfx driver internal state; only two fields observed, insufficient to pin against a named nrfx struct. verified=false. */
struct __attribute__((packed)) g1_layout_nrfx_qspi_cb__global_1562 {
    uint8_t _pad_0x0[0x30];
    uint8_t field_0x30[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x34[0x4];
    uint8_t field_0x38[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_cb__global_1562, field_0x30) == 0x30, "g1_layout_nrfx_qspi_cb__global_1562.field_0x30");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_cb__global_1562, field_0x38) == 0x38, "g1_layout_nrfx_qspi_cb__global_1562.field_0x38");
_Static_assert(sizeof(struct g1_layout_nrfx_qspi_cb__global_1562) >= 0x3c, "g1_layout_nrfx_qspi_cb__global_1562.size");

/* param_0000 | G1-original | Large battery model/state structure (>=0x1778 bytes) passed to battery_model_state_update, holding voltage/current/capacity coefficients and history across several sub-regions. | D1+D2 verified
 * review: G1-original; sparse sampled offsets kept exactly. Only representative accessed words captured; large struct. */
struct __attribute__((packed)) g1_layout_battery_model_state__param_0000 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x40];
    uint8_t field_0x48[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x4c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x50[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x54[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x58[0x4];
    uint8_t field_0x5c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x60[0xc8];
    uint8_t field_0x128[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x12c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x130[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x134[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x138[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x13c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x140[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x144[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x148[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14c[0x318];
    uint8_t field_0x464[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x468[0x16b];
    uint8_t field_0x5d3[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x5d4[0x88];
    uint8_t field_0x65c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x660[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x664[0x314];
    uint8_t field_0x978[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x97c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x980[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x984[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x988[0x314];
    uint8_t field_0xc9c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xca0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xca4[0xaa0];
    uint8_t field_0x1744[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1748[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x174c[0x4];
    uint8_t field_0x1750[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1754[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1758[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x175c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1760[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1764[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1768[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x176c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1770[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1774[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x4) == 0x4, "g1_layout_battery_model_state__param_0000.field_0x4");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x48) == 0x48, "g1_layout_battery_model_state__param_0000.field_0x48");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x4c) == 0x4c, "g1_layout_battery_model_state__param_0000.field_0x4c");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x50) == 0x50, "g1_layout_battery_model_state__param_0000.field_0x50");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x54) == 0x54, "g1_layout_battery_model_state__param_0000.field_0x54");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x5c) == 0x5c, "g1_layout_battery_model_state__param_0000.field_0x5c");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x128) == 0x128, "g1_layout_battery_model_state__param_0000.field_0x128");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x12c) == 0x12c, "g1_layout_battery_model_state__param_0000.field_0x12c");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x130) == 0x130, "g1_layout_battery_model_state__param_0000.field_0x130");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x134) == 0x134, "g1_layout_battery_model_state__param_0000.field_0x134");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x138) == 0x138, "g1_layout_battery_model_state__param_0000.field_0x138");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x13c) == 0x13c, "g1_layout_battery_model_state__param_0000.field_0x13c");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x140) == 0x140, "g1_layout_battery_model_state__param_0000.field_0x140");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x144) == 0x144, "g1_layout_battery_model_state__param_0000.field_0x144");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x148) == 0x148, "g1_layout_battery_model_state__param_0000.field_0x148");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x464) == 0x464, "g1_layout_battery_model_state__param_0000.field_0x464");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x5d3) == 0x5d3, "g1_layout_battery_model_state__param_0000.field_0x5d3");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x65c) == 0x65c, "g1_layout_battery_model_state__param_0000.field_0x65c");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x660) == 0x660, "g1_layout_battery_model_state__param_0000.field_0x660");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x978) == 0x978, "g1_layout_battery_model_state__param_0000.field_0x978");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x97c) == 0x97c, "g1_layout_battery_model_state__param_0000.field_0x97c");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x980) == 0x980, "g1_layout_battery_model_state__param_0000.field_0x980");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x984) == 0x984, "g1_layout_battery_model_state__param_0000.field_0x984");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0xc9c) == 0xc9c, "g1_layout_battery_model_state__param_0000.field_0xc9c");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0xca0) == 0xca0, "g1_layout_battery_model_state__param_0000.field_0xca0");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x1744) == 0x1744, "g1_layout_battery_model_state__param_0000.field_0x1744");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x1748) == 0x1748, "g1_layout_battery_model_state__param_0000.field_0x1748");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x1750) == 0x1750, "g1_layout_battery_model_state__param_0000.field_0x1750");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x1754) == 0x1754, "g1_layout_battery_model_state__param_0000.field_0x1754");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x1758) == 0x1758, "g1_layout_battery_model_state__param_0000.field_0x1758");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x175c) == 0x175c, "g1_layout_battery_model_state__param_0000.field_0x175c");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x1760) == 0x1760, "g1_layout_battery_model_state__param_0000.field_0x1760");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x1764) == 0x1764, "g1_layout_battery_model_state__param_0000.field_0x1764");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x1768) == 0x1768, "g1_layout_battery_model_state__param_0000.field_0x1768");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x176c) == 0x176c, "g1_layout_battery_model_state__param_0000.field_0x176c");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x1770) == 0x1770, "g1_layout_battery_model_state__param_0000.field_0x1770");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0000, field_0x1774) == 0x1774, "g1_layout_battery_model_state__param_0000.field_0x1774");
_Static_assert(sizeof(struct g1_layout_battery_model_state__param_0000) >= 0x1778, "g1_layout_battery_model_state__param_0000.size");

/* param_0001 | G1-original | Battery fuel-gauge model state passed to battery_model_state_update (param_8), holding raw ADC/lookup indices. | D1+D2 verified
 * review: G1-original. Three idx4 words only. */
struct __attribute__((packed)) g1_layout_battery_model_state__param_0001 {
    uint8_t _pad_0x0[0x4];
    uint8_t idx_0[0x4]; /* catalog type: uint32_t */
    uint8_t idx_1[0x4]; /* catalog type: uint32_t */
    uint8_t idx_2[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0001, idx_0) == 0x4, "g1_layout_battery_model_state__param_0001.idx_0");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0001, idx_1) == 0x8, "g1_layout_battery_model_state__param_0001.idx_1");
_Static_assert(offsetof(struct g1_layout_battery_model_state__param_0001, idx_2) == 0xc, "g1_layout_battery_model_state__param_0001.idx_2");
_Static_assert(sizeof(struct g1_layout_battery_model_state__param_0001) >= 0x10, "g1_layout_battery_model_state__param_0001.size");

/* param_0002 | G1-original | Battery state-of-charge curve context (interpolation coefficients/points) passed to batt_soc_curve_estimate. | D1+D2 verified
 * review: Kept naming; refined field types to int32 (idx4 reads). Offsets unchanged. */
struct __attribute__((packed)) g1_layout_batt_soc_curve_ctx__param_0002 {
    uint8_t _pad_0x0[0x4];
    uint8_t soc_curve_x0[0x4]; /* catalog type: int32_t */
    uint8_t soc_curve_x1[0x4]; /* catalog type: int32_t */
    uint8_t soc_curve_x2[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_batt_soc_curve_ctx__param_0002, soc_curve_x0) == 0x4, "g1_layout_batt_soc_curve_ctx__param_0002.soc_curve_x0");
_Static_assert(offsetof(struct g1_layout_batt_soc_curve_ctx__param_0002, soc_curve_x1) == 0x8, "g1_layout_batt_soc_curve_ctx__param_0002.soc_curve_x1");
_Static_assert(offsetof(struct g1_layout_batt_soc_curve_ctx__param_0002, soc_curve_x2) == 0xc, "g1_layout_batt_soc_curve_ctx__param_0002.soc_curve_x2");
_Static_assert(sizeof(struct g1_layout_batt_soc_curve_ctx__param_0002) >= 0x10, "g1_layout_batt_soc_curve_ctx__param_0002.size");

/* param_0003 | G1-original | One (x,y) curve point read by battery_soc_from_curve during state-of-charge interpolation. | D1+D2 verified
 * review: Kept offsets; array-of-points interpretation. */
struct __attribute__((packed)) g1_layout_battery_soc_curve_point__param_0003 {
    uint8_t _pad_0x0[0x4];
    uint8_t x_value[0x4]; /* catalog type: uint32_t */
    uint8_t y_value[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_point__param_0003, x_value) == 0x4, "g1_layout_battery_soc_curve_point__param_0003.x_value");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_point__param_0003, y_value) == 0x8, "g1_layout_battery_soc_curve_point__param_0003.y_value");
_Static_assert(sizeof(struct g1_layout_battery_soc_curve_point__param_0003) >= 0xc, "g1_layout_battery_soc_curve_point__param_0003.size");

/* param_0004 | G1-original | 201-point interpolation curve table (backing size 0x324 = 201*4 bytes) consumed by curve_table_interp_201pt. | D1+D2 verified
 * review: G1-original lookup table; only first (0x4) and last (0x320) samples observed but stride and size imply a uniform 201-entry uint32 array. */
struct __attribute__((packed)) g1_layout_curve_table_201pt__param_0004 {
    uint8_t _pad_0x0[0x4];
    uint8_t points_1[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x318];
    uint8_t points_last[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_curve_table_201pt__param_0004, points_1) == 0x4, "g1_layout_curve_table_201pt__param_0004.points_1");
_Static_assert(offsetof(struct g1_layout_curve_table_201pt__param_0004, points_last) == 0x320, "g1_layout_curve_table_201pt__param_0004.points_last");
_Static_assert(sizeof(struct g1_layout_curve_table_201pt__param_0004) >= 0x324, "g1_layout_curve_table_201pt__param_0004.size");

/* param_0005 | G1-original | 201-point interpolation curve table passed (param_4) to curve_table_interp_201pt: a cursor index word plus a large point array. | D1+D2 verified
 * review: G1-original. 0x324-byte object (~201*4). Only the cursor (0x4) and the last two array entries (0x31c,0x320) are observed. */
struct __attribute__((packed)) g1_layout_curve_interp_table_201pt__param_0005 {
    uint8_t _pad_0x0[0x4];
    uint8_t cursor_idx[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x314];
    uint8_t point_n_minus1[0x4]; /* catalog type: uint32_t */
    uint8_t point_n[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_curve_interp_table_201pt__param_0005, cursor_idx) == 0x4, "g1_layout_curve_interp_table_201pt__param_0005.cursor_idx");
_Static_assert(offsetof(struct g1_layout_curve_interp_table_201pt__param_0005, point_n_minus1) == 0x31c, "g1_layout_curve_interp_table_201pt__param_0005.point_n_minus1");
_Static_assert(offsetof(struct g1_layout_curve_interp_table_201pt__param_0005, point_n) == 0x320, "g1_layout_curve_interp_table_201pt__param_0005.point_n");
_Static_assert(sizeof(struct g1_layout_curve_interp_table_201pt__param_0005) >= 0x324, "g1_layout_curve_interp_table_201pt__param_0005.size");

/* param_0006 | G1-original | 201-point interpolation curve table passed to curve_table_interp_201pt (point_count + tail coefficient words). | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_curve_table_201pt__param_0006 {
    uint8_t _pad_0x0[0x4];
    uint8_t point_count[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x314];
    uint8_t field_0x31c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x320[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_curve_table_201pt__param_0006, point_count) == 0x4, "g1_layout_curve_table_201pt__param_0006.point_count");
_Static_assert(offsetof(struct g1_layout_curve_table_201pt__param_0006, field_0x31c) == 0x31c, "g1_layout_curve_table_201pt__param_0006.field_0x31c");
_Static_assert(offsetof(struct g1_layout_curve_table_201pt__param_0006, field_0x320) == 0x320, "g1_layout_curve_table_201pt__param_0006.field_0x320");
_Static_assert(sizeof(struct g1_layout_curve_table_201pt__param_0006) >= 0x324, "g1_layout_curve_table_201pt__param_0006.size");

/* param_0007 | G1-original | Very large (0x1578) object unified across 8 unrelated functions (random, PKCS7 parse, BLE dispatch, notify build, push_message, battery SOC curve init). Almost certainly a mis-merge of several distinct pointer objects, not one real struct. | D1+D2 verified
 * review: Kept as one record per shard coverage rules, but flagged as a likely pointer-unification artifact. Overlapping widths at 0x1/0x4/0xc set is_union. The float clusters (0x324-0x334, 0x11a8, 0x1388-0x1394, 0x1570) look like battery SOC calibration table fragments belonging to battery_soc_curve_model_init, not the other members. */
struct __attribute__((packed)) g1_layout_app_shared_ctx_blob__param_0007 {
    uint8_t _pad_0x0[0x1];
    uint8_t field_0x1[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x3[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x198];
    uint8_t field_0x1b0[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x1b4[0x170];
    uint8_t soc_curve_pt0[0x4]; /* catalog type: float */
    uint8_t soc_curve_pt1[0x4]; /* catalog type: float */
    uint8_t soc_curve_pt2[0x4]; /* catalog type: float */
    uint8_t soc_curve_pt3[0x4]; /* catalog type: float */
    uint8_t soc_curve_pt4[0x4]; /* catalog type: float */
    uint8_t _pad_0x338[0x1dc];
    uint8_t field_0x514[0x4]; /* catalog type: float */
    uint8_t _pad_0x518[0xc90];
    uint8_t field_0x11a8[0x4]; /* catalog type: float */
    uint8_t field_0x11ac[0x4]; /* catalog type: float */
    uint8_t _pad_0x11b0[0x1d8];
    uint8_t field_0x1388[0x4]; /* catalog type: float */
    uint8_t field_0x138c[0x4]; /* catalog type: float */
    uint8_t field_0x1390[0x4]; /* catalog type: float */
    uint8_t field_0x1394[0x4]; /* catalog type: float */
    uint8_t _pad_0x1398[0x1d8];
    uint8_t field_0x1570[0x4]; /* catalog type: float */
    uint8_t field_0x1574[0x4]; /* catalog type: float */
};
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x1) == 0x1, "g1_layout_app_shared_ctx_blob__param_0007.field_0x1");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x3) == 0x3, "g1_layout_app_shared_ctx_blob__param_0007.field_0x3");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x4) == 0x4, "g1_layout_app_shared_ctx_blob__param_0007.field_0x4");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x8) == 0x8, "g1_layout_app_shared_ctx_blob__param_0007.field_0x8");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0xc) == 0xc, "g1_layout_app_shared_ctx_blob__param_0007.field_0xc");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x10) == 0x10, "g1_layout_app_shared_ctx_blob__param_0007.field_0x10");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x14) == 0x14, "g1_layout_app_shared_ctx_blob__param_0007.field_0x14");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x1b0) == 0x1b0, "g1_layout_app_shared_ctx_blob__param_0007.field_0x1b0");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, soc_curve_pt0) == 0x324, "g1_layout_app_shared_ctx_blob__param_0007.soc_curve_pt0");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, soc_curve_pt1) == 0x328, "g1_layout_app_shared_ctx_blob__param_0007.soc_curve_pt1");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, soc_curve_pt2) == 0x32c, "g1_layout_app_shared_ctx_blob__param_0007.soc_curve_pt2");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, soc_curve_pt3) == 0x330, "g1_layout_app_shared_ctx_blob__param_0007.soc_curve_pt3");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, soc_curve_pt4) == 0x334, "g1_layout_app_shared_ctx_blob__param_0007.soc_curve_pt4");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x514) == 0x514, "g1_layout_app_shared_ctx_blob__param_0007.field_0x514");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x11a8) == 0x11a8, "g1_layout_app_shared_ctx_blob__param_0007.field_0x11a8");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x11ac) == 0x11ac, "g1_layout_app_shared_ctx_blob__param_0007.field_0x11ac");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x1388) == 0x1388, "g1_layout_app_shared_ctx_blob__param_0007.field_0x1388");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x138c) == 0x138c, "g1_layout_app_shared_ctx_blob__param_0007.field_0x138c");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x1390) == 0x1390, "g1_layout_app_shared_ctx_blob__param_0007.field_0x1390");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x1394) == 0x1394, "g1_layout_app_shared_ctx_blob__param_0007.field_0x1394");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x1570) == 0x1570, "g1_layout_app_shared_ctx_blob__param_0007.field_0x1570");
_Static_assert(offsetof(struct g1_layout_app_shared_ctx_blob__param_0007, field_0x1574) == 0x1574, "g1_layout_app_shared_ctx_blob__param_0007.field_0x1574");
_Static_assert(sizeof(struct g1_layout_app_shared_ctx_blob__param_0007) >= 0x1578, "g1_layout_app_shared_ctx_blob__param_0007.size");

/* param_0008 | G1-original | G1-original battery state-of-charge curve model / lookup tables initialized by battery_soc_curve_model_init: model id, three coefficient tables and an init-complete flag. | D1+D2 verified
 * review: G1-original. All 27 ground-truth offsets preserved. */
struct __attribute__((packed)) g1_layout_battery_soc_curve_model__param_0008 {
    uint8_t _pad_0x0[0x4];
    uint8_t model_id[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x40];
    uint8_t curve_param_0[0x4]; /* catalog type: uint32_t */
    uint8_t curve_param_1[0x4]; /* catalog type: uint32_t */
    uint8_t curve_param_2[0x4]; /* catalog type: uint32_t */
    uint8_t curve_param_3[0x4]; /* catalog type: uint32_t */
    uint8_t curve_param_4[0x4]; /* catalog type: uint32_t */
    uint8_t curve_param_5[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x60[0xc8];
    uint8_t table2_param_0[0x4]; /* catalog type: uint32_t */
    uint8_t table2_param_1[0x4]; /* catalog type: uint32_t */
    uint8_t table2_param_2[0x4]; /* catalog type: uint32_t */
    uint8_t table2_param_3[0x4]; /* catalog type: uint32_t */
    uint8_t table2_param_4[0x4]; /* catalog type: uint32_t */
    uint8_t table2_param_5[0x4]; /* catalog type: uint32_t */
    uint8_t table2_param_6[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x144[0x48f];
    uint8_t model_ready_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x5d4[0x1170];
    uint8_t table3_param_0[0x4]; /* catalog type: uint32_t */
    uint8_t table3_param_1[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x174c[0x4];
    uint8_t table3_param_2[0x4]; /* catalog type: uint32_t */
    uint8_t table3_param_3[0x4]; /* catalog type: uint32_t */
    uint8_t table3_param_4[0x4]; /* catalog type: uint32_t */
    uint8_t table3_param_5[0x4]; /* catalog type: uint32_t */
    uint8_t table3_param_6[0x4]; /* catalog type: uint32_t */
    uint8_t table3_param_7[0x4]; /* catalog type: uint32_t */
    uint8_t table3_param_8[0x4]; /* catalog type: uint32_t */
    uint8_t table3_param_9[0x4]; /* catalog type: uint32_t */
    uint8_t table3_param_10[0x4]; /* catalog type: uint32_t */
    uint8_t table3_param_11[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, model_id) == 0x4, "g1_layout_battery_soc_curve_model__param_0008.model_id");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, curve_param_0) == 0x48, "g1_layout_battery_soc_curve_model__param_0008.curve_param_0");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, curve_param_1) == 0x4c, "g1_layout_battery_soc_curve_model__param_0008.curve_param_1");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, curve_param_2) == 0x50, "g1_layout_battery_soc_curve_model__param_0008.curve_param_2");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, curve_param_3) == 0x54, "g1_layout_battery_soc_curve_model__param_0008.curve_param_3");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, curve_param_4) == 0x58, "g1_layout_battery_soc_curve_model__param_0008.curve_param_4");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, curve_param_5) == 0x5c, "g1_layout_battery_soc_curve_model__param_0008.curve_param_5");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table2_param_0) == 0x128, "g1_layout_battery_soc_curve_model__param_0008.table2_param_0");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table2_param_1) == 0x12c, "g1_layout_battery_soc_curve_model__param_0008.table2_param_1");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table2_param_2) == 0x130, "g1_layout_battery_soc_curve_model__param_0008.table2_param_2");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table2_param_3) == 0x134, "g1_layout_battery_soc_curve_model__param_0008.table2_param_3");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table2_param_4) == 0x138, "g1_layout_battery_soc_curve_model__param_0008.table2_param_4");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table2_param_5) == 0x13c, "g1_layout_battery_soc_curve_model__param_0008.table2_param_5");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table2_param_6) == 0x140, "g1_layout_battery_soc_curve_model__param_0008.table2_param_6");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, model_ready_flag) == 0x5d3, "g1_layout_battery_soc_curve_model__param_0008.model_ready_flag");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table3_param_0) == 0x1744, "g1_layout_battery_soc_curve_model__param_0008.table3_param_0");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table3_param_1) == 0x1748, "g1_layout_battery_soc_curve_model__param_0008.table3_param_1");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table3_param_2) == 0x1750, "g1_layout_battery_soc_curve_model__param_0008.table3_param_2");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table3_param_3) == 0x1754, "g1_layout_battery_soc_curve_model__param_0008.table3_param_3");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table3_param_4) == 0x1758, "g1_layout_battery_soc_curve_model__param_0008.table3_param_4");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table3_param_5) == 0x175c, "g1_layout_battery_soc_curve_model__param_0008.table3_param_5");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table3_param_6) == 0x1760, "g1_layout_battery_soc_curve_model__param_0008.table3_param_6");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table3_param_7) == 0x1764, "g1_layout_battery_soc_curve_model__param_0008.table3_param_7");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table3_param_8) == 0x1768, "g1_layout_battery_soc_curve_model__param_0008.table3_param_8");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table3_param_9) == 0x176c, "g1_layout_battery_soc_curve_model__param_0008.table3_param_9");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table3_param_10) == 0x1770, "g1_layout_battery_soc_curve_model__param_0008.table3_param_10");
_Static_assert(offsetof(struct g1_layout_battery_soc_curve_model__param_0008, table3_param_11) == 0x1774, "g1_layout_battery_soc_curve_model__param_0008.table3_param_11");
_Static_assert(sizeof(struct g1_layout_battery_soc_curve_model__param_0008) >= 0x1778, "g1_layout_battery_soc_curve_model__param_0008.size");

/* param_0009 | G1-original | Pointer arg to array_max_skip_nan_a; two index/length fields describing an array scan (bounds or accumulator). | D1+D2 verified
 * review: Single-cid G1 helper. Offsets kept. */
struct __attribute__((packed)) g1_layout_array_scan_bounds__param_0009 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_array_scan_bounds__param_0009, field_0x4) == 0x4, "g1_layout_array_scan_bounds__param_0009.field_0x4");
_Static_assert(offsetof(struct g1_layout_array_scan_bounds__param_0009, field_0x8) == 0x8, "g1_layout_array_scan_bounds__param_0009.field_0x8");
_Static_assert(sizeof(struct g1_layout_array_scan_bounds__param_0009) >= 0xc, "g1_layout_array_scan_bounds__param_0009.size");

/* param_0010 | G1-original | Small length/count descriptor passed to numeric array-scan helper array_max_skip_nan_b, used for indexing. | D1+D2 verified
 * review: G1-original; offsets unchanged. */
struct __attribute__((packed)) g1_layout_array_len_desc__param_0010 {
    uint8_t _pad_0x0[0x4];
    uint8_t length[0x4]; /* catalog type: uint32_t */
    uint8_t count[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_array_len_desc__param_0010, length) == 0x4, "g1_layout_array_len_desc__param_0010.length");
_Static_assert(offsetof(struct g1_layout_array_len_desc__param_0010, count) == 0x8, "g1_layout_array_len_desc__param_0010.count");
_Static_assert(sizeof(struct g1_layout_array_len_desc__param_0010) >= 0xc, "g1_layout_array_len_desc__param_0010.size");

/* param_0013 | G1-original | Output struct receiving two interpolated values from spline_interp_pair_2out (param_2). | D1+D2 verified
 * review: G1-original two-value output record. */
struct __attribute__((packed)) g1_layout_interp_pair_out__param_0013 {
    uint8_t _pad_0x0[0x4];
    uint8_t out_0[0x4]; /* catalog type: int32_t */
    uint8_t out_1[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_interp_pair_out__param_0013, out_0) == 0x4, "g1_layout_interp_pair_out__param_0013.out_0");
_Static_assert(offsetof(struct g1_layout_interp_pair_out__param_0013, out_1) == 0x8, "g1_layout_interp_pair_out__param_0013.out_1");
_Static_assert(sizeof(struct g1_layout_interp_pair_out__param_0013) >= 0xc, "g1_layout_interp_pair_out__param_0013.size");

/* param_0015 | G1-original | 2D control point (x,y) consumed by spline_interp_3pt. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_spline_point2d__param_0015 {
    uint8_t _pad_0x0[0x4];
    uint8_t x[0x4]; /* catalog type: int32_t */
    uint8_t y[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_spline_point2d__param_0015, x) == 0x4, "g1_layout_spline_point2d__param_0015.x");
_Static_assert(offsetof(struct g1_layout_spline_point2d__param_0015, y) == 0x8, "g1_layout_spline_point2d__param_0015.y");
_Static_assert(sizeof(struct g1_layout_spline_point2d__param_0015) >= 0xc, "g1_layout_spline_point2d__param_0015.size");

/* param_0016 | G1-original | Control-point values fed to spline_interp_3pt (3-point spline interpolation). | D1+D2 verified
 * review: Kept offsets. */
struct __attribute__((packed)) g1_layout_spline_3pt_points__param_0016 {
    uint8_t _pad_0x0[0x4];
    uint8_t point_b[0x4]; /* catalog type: int32_t */
    uint8_t point_c[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_spline_3pt_points__param_0016, point_b) == 0x4, "g1_layout_spline_3pt_points__param_0016.point_b");
_Static_assert(offsetof(struct g1_layout_spline_3pt_points__param_0016, point_c) == 0x8, "g1_layout_spline_3pt_points__param_0016.point_c");
_Static_assert(sizeof(struct g1_layout_spline_3pt_points__param_0016) >= 0xc, "g1_layout_spline_3pt_points__param_0016.size");

/* param_0018 | G1-original | UI 'box' element state shared across presence/animation/config-default functions: presence & config flag bytes plus an animation step value. | D1+D2 verified
 * review: G1-original; kept sonnet naming/layout, all offsets ground-truth. */
struct __attribute__((packed)) g1_layout_g1_ui_box_state__param_0018 {
    uint8_t _pad_0x0[0x1];
    uint8_t presence_flag[0x1]; /* catalog type: uint8_t */
    uint8_t box_flags[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x2];
    uint8_t config_byte_5[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x6[0x1];
    uint8_t config_byte_7[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x8[0x3];
    uint8_t config_byte_b[0x1]; /* catalog type: uint8_t */
    uint8_t config_byte_c[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xd[0x6];
    uint8_t status_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x14[0x1c];
    uint8_t animation_step[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_g1_ui_box_state__param_0018, presence_flag) == 0x1, "g1_layout_g1_ui_box_state__param_0018.presence_flag");
_Static_assert(offsetof(struct g1_layout_g1_ui_box_state__param_0018, box_flags) == 0x2, "g1_layout_g1_ui_box_state__param_0018.box_flags");
_Static_assert(offsetof(struct g1_layout_g1_ui_box_state__param_0018, config_byte_5) == 0x5, "g1_layout_g1_ui_box_state__param_0018.config_byte_5");
_Static_assert(offsetof(struct g1_layout_g1_ui_box_state__param_0018, config_byte_7) == 0x7, "g1_layout_g1_ui_box_state__param_0018.config_byte_7");
_Static_assert(offsetof(struct g1_layout_g1_ui_box_state__param_0018, config_byte_b) == 0xb, "g1_layout_g1_ui_box_state__param_0018.config_byte_b");
_Static_assert(offsetof(struct g1_layout_g1_ui_box_state__param_0018, config_byte_c) == 0xc, "g1_layout_g1_ui_box_state__param_0018.config_byte_c");
_Static_assert(offsetof(struct g1_layout_g1_ui_box_state__param_0018, status_byte) == 0x13, "g1_layout_g1_ui_box_state__param_0018.status_byte");
_Static_assert(offsetof(struct g1_layout_g1_ui_box_state__param_0018, animation_step) == 0x30, "g1_layout_g1_ui_box_state__param_0018.animation_step");
_Static_assert(sizeof(struct g1_layout_g1_ui_box_state__param_0018) >= 0x32, "g1_layout_g1_ui_box_state__param_0018.size");

/* param_0019 | G1-original | Large shared IMU/orientation fusion runtime state (~0x6b0 bytes) feeding panel-level tilt calc; touched by imu_fusion_thread and panel_level_calc_cached. | D1+D2 verified
 * review: G1-original. Kept all 17 observed offsets; names are best-effort (accel triplet at 0x80-0x88, fused output triplet written at 0x198-0x1a0, several idx4 table cursors). */
struct __attribute__((packed)) g1_layout_imu_fusion_state__param_0019 {
    uint8_t _pad_0x0[0x8];
    uint8_t state_flags[0x4]; /* catalog type: uint32_t */
    uint8_t mode[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0xc];
    uint8_t sample_count[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x20[0x20];
    uint8_t cal_idx_0[0x4]; /* catalog type: uint32_t */
    uint8_t cal_idx_1[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x48[0x8];
    uint8_t cal_idx_2[0x4]; /* catalog type: uint32_t */
    uint8_t cal_idx_3[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x58[0x28];
    uint8_t accel_x[0x4]; /* catalog type: int32_t */
    uint8_t accel_y[0x4]; /* catalog type: int32_t */
    uint8_t accel_z[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x8c[0xec];
    uint8_t seq_id[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x17a[0x1e];
    uint8_t out_x[0x4]; /* catalog type: int32_t */
    uint8_t out_y[0x4]; /* catalog type: int32_t */
    uint8_t out_z[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x1a4[0x264];
    uint8_t table_idx_a[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x40c[0xc];
    uint8_t table_idx_b[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x41c[0x290];
    uint8_t table_idx_c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, state_flags) == 0x8, "g1_layout_imu_fusion_state__param_0019.state_flags");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, mode) == 0xc, "g1_layout_imu_fusion_state__param_0019.mode");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, sample_count) == 0x1c, "g1_layout_imu_fusion_state__param_0019.sample_count");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, cal_idx_0) == 0x40, "g1_layout_imu_fusion_state__param_0019.cal_idx_0");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, cal_idx_1) == 0x44, "g1_layout_imu_fusion_state__param_0019.cal_idx_1");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, cal_idx_2) == 0x50, "g1_layout_imu_fusion_state__param_0019.cal_idx_2");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, cal_idx_3) == 0x54, "g1_layout_imu_fusion_state__param_0019.cal_idx_3");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, accel_x) == 0x80, "g1_layout_imu_fusion_state__param_0019.accel_x");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, accel_y) == 0x84, "g1_layout_imu_fusion_state__param_0019.accel_y");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, accel_z) == 0x88, "g1_layout_imu_fusion_state__param_0019.accel_z");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, seq_id) == 0x178, "g1_layout_imu_fusion_state__param_0019.seq_id");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, out_x) == 0x198, "g1_layout_imu_fusion_state__param_0019.out_x");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, out_y) == 0x19c, "g1_layout_imu_fusion_state__param_0019.out_y");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, out_z) == 0x1a0, "g1_layout_imu_fusion_state__param_0019.out_z");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, table_idx_a) == 0x408, "g1_layout_imu_fusion_state__param_0019.table_idx_a");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, table_idx_b) == 0x418, "g1_layout_imu_fusion_state__param_0019.table_idx_b");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state__param_0019, table_idx_c) == 0x6ac, "g1_layout_imu_fusion_state__param_0019.table_idx_c");
_Static_assert(sizeof(struct g1_layout_imu_fusion_state__param_0019) >= 0x6b0, "g1_layout_imu_fusion_state__param_0019.size");

/* param_0022 | library | cJSON node walked by the JSON parser (child/type/valuestring/valueint/valuedouble). | D1+D2 verified
 * review: VERIFIED against cJSON.h: next@0x0,prev@0x4,child@0x8,type@0xc,valuestring@0x10,valueint@0x14,valuedouble@0x18. All observed offsets match exactly incl. 8-byte double at 0x18. */
struct __attribute__((packed)) g1_layout_cJSON__param_0022 {
    uint8_t _pad_0x0[0x8];
    uint8_t child[0x4]; /* catalog type: struct cJSON *; SDK member: child */
    uint8_t type[0x4]; /* catalog type: int; SDK member: type */
    uint8_t valuestring[0x4]; /* catalog type: char *; SDK member: valuestring */
    uint8_t valueint[0x4]; /* catalog type: int; SDK member: valueint */
    uint8_t valuedouble[0x8]; /* catalog type: double; SDK member: valuedouble */
};
_Static_assert(offsetof(struct g1_layout_cJSON__param_0022, child) == 0x8, "g1_layout_cJSON__param_0022.child");
_Static_assert(offsetof(struct g1_layout_cJSON__param_0022, type) == 0xc, "g1_layout_cJSON__param_0022.type");
_Static_assert(offsetof(struct g1_layout_cJSON__param_0022, valuestring) == 0x10, "g1_layout_cJSON__param_0022.valuestring");
_Static_assert(offsetof(struct g1_layout_cJSON__param_0022, valueint) == 0x14, "g1_layout_cJSON__param_0022.valueint");
_Static_assert(offsetof(struct g1_layout_cJSON__param_0022, valuedouble) == 0x18, "g1_layout_cJSON__param_0022.valuedouble");
_Static_assert(sizeof(struct g1_layout_cJSON__param_0022) >= 0x20, "g1_layout_cJSON__param_0022.size");

/* param_0023 | library | cJSON internal parse cursor: content pointer, length, offset, nesting depth, and embedded malloc/free hook pointers, shared by cjson_parse_value / cjson_parse_string / cjson_skip_whitespace. | D1+D2 verified
 * review: Footprint collision with k_sem (param_0731) and an lc3 coeff array (stack_1377) — split into 3 separate structs; these are NOT the same object. cJSON's parse_buffer is a file-local struct in cJSON.c, not a public header, so offsets cannot be checked against a pinned header (library_verified=false). Kept sonnet layout; content typed as cursor pointer. */
struct __attribute__((packed)) g1_layout_cjson_parse_buffer__param_0023 {
    uint8_t content[0x4]; /* catalog type: const unsigned char * */
    uint8_t length[0x4]; /* catalog type: uint32_t */
    uint8_t offset[0x4]; /* catalog type: uint32_t */
    uint8_t depth[0x4]; /* catalog type: uint32_t */
    uint8_t hooks_malloc_fn[0x4]; /* catalog type: void * */
    uint8_t hooks_free_fn[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_cjson_parse_buffer__param_0023, content) == 0x0, "g1_layout_cjson_parse_buffer__param_0023.content");
_Static_assert(offsetof(struct g1_layout_cjson_parse_buffer__param_0023, length) == 0x4, "g1_layout_cjson_parse_buffer__param_0023.length");
_Static_assert(offsetof(struct g1_layout_cjson_parse_buffer__param_0023, offset) == 0x8, "g1_layout_cjson_parse_buffer__param_0023.offset");
_Static_assert(offsetof(struct g1_layout_cjson_parse_buffer__param_0023, depth) == 0xc, "g1_layout_cjson_parse_buffer__param_0023.depth");
_Static_assert(offsetof(struct g1_layout_cjson_parse_buffer__param_0023, hooks_malloc_fn) == 0x10, "g1_layout_cjson_parse_buffer__param_0023.hooks_malloc_fn");
_Static_assert(offsetof(struct g1_layout_cjson_parse_buffer__param_0023, hooks_free_fn) == 0x14, "g1_layout_cjson_parse_buffer__param_0023.hooks_free_fn");
_Static_assert(sizeof(struct g1_layout_cjson_parse_buffer__param_0023) >= 0x18, "g1_layout_cjson_parse_buffer__param_0023.size");

/* param_0025 | G1-original | ~4KB local ESB/IPC service receive context (local_esbs_ipc_service_recv): header flag bytes, a large payload buffer region, then trailing buffer pointer + length/counters. | D1+D2 verified
 * review: Single-cid; kept sonnet layout. */
struct __attribute__((packed)) g1_layout_esbs_ipc_recv_ctx__param_0025 {
    uint8_t _pad_0x0[0xc9];
    uint8_t field_0xc9[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xca[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xcb[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xcc[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xcd[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xce[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xcf[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xd0[0x5];
    uint8_t field_0xd5[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xd6[0x4];
    uint8_t field_0xda[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xdb[0x9];
    uint8_t field_0xe4[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xe5[0x4];
    uint8_t field_0xe9[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xea[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xeb[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xec[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xed[0xdf7];
    uint8_t field_0xee4[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xee5[0x101];
    uint8_t field_0xfe6[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xfe7[0x5];
    uint8_t data_ptr[0x4]; /* catalog type: void * */
    uint8_t _pad_0xff0[0x4];
    uint8_t field_0xff4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xff8[0x2c];
    uint8_t field_0x1024[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1028[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xc9) == 0xc9, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xc9");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xca) == 0xca, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xca");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xcb) == 0xcb, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xcb");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xcc) == 0xcc, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xcc");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xcd) == 0xcd, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xcd");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xce) == 0xce, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xce");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xcf) == 0xcf, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xcf");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xd5) == 0xd5, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xd5");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xda) == 0xda, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xda");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xe4) == 0xe4, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xe4");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xe9) == 0xe9, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xe9");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xea) == 0xea, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xea");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xeb) == 0xeb, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xeb");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xec) == 0xec, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xec");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xee4) == 0xee4, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xee4");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xfe6) == 0xfe6, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xfe6");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, data_ptr) == 0xfec, "g1_layout_esbs_ipc_recv_ctx__param_0025.data_ptr");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0xff4) == 0xff4, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0xff4");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0x1024) == 0x1024, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0x1024");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_recv_ctx__param_0025, field_0x1028) == 0x1028, "g1_layout_esbs_ipc_recv_ctx__param_0025.field_0x1028");
_Static_assert(sizeof(struct g1_layout_esbs_ipc_recv_ctx__param_0025) >= 0x102c, "g1_layout_esbs_ipc_recv_ctx__param_0025.size");

/* param_0026 | G1-original | IPC message struct passed to local_esbs_ipc_service_recv; header bytes at 0x4 overlapped by a wide word read, plus three data words. | D1+D2 verified
 * review: G1-original. is_union=true: Ghidra notes width-4 read at 0x4 overlaps the 3-byte field then the 0x7 word (bytes accessed both narrow and wide). */
struct __attribute__((packed)) g1_layout_esbs_ipc_msg__param_0026 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x3]; /* catalog type: uint8_t[3] */
    uint8_t field_0x7[0x1]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_esbs_ipc_msg__param_0026, field_0x4) == 0x4, "g1_layout_esbs_ipc_msg__param_0026.field_0x4");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_msg__param_0026, field_0x7) == 0x7, "g1_layout_esbs_ipc_msg__param_0026.field_0x7");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_msg__param_0026, field_0x8) == 0x8, "g1_layout_esbs_ipc_msg__param_0026.field_0x8");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_msg__param_0026, field_0xc) == 0xc, "g1_layout_esbs_ipc_msg__param_0026.field_0xc");
_Static_assert(offsetof(struct g1_layout_esbs_ipc_msg__param_0026, field_0x10) == 0x10, "g1_layout_esbs_ipc_msg__param_0026.field_0x10");
_Static_assert(sizeof(struct g1_layout_esbs_ipc_msg__param_0026) >= 0x14, "g1_layout_esbs_ipc_msg__param_0026.size");

/* param_0027 | G1-original | Central G1-original device runtime/context object (~0x4244 bytes) threaded as param_1/param_2 through 31 functions: runtime_info_sync, user-setting load/save, ESB comms, display/key/touch dispatch threads, screen-state and task/message-queue processing. The shared global device-state struct. Includes a dense task/message dispatch callback pointer table at 0xfec-0x102c. | D1+D2 verified
 * review: Renamed from g1_system_runtime_state to g1_device_runtime_state. Set is_union=true per ground-truth layout notes (overlapping wide/narrow accesses at 0xc9,0xcd,0xd0,0xe5,0xec0,0xef4,0x1060,0x1069,0x106c,0x1090). All 0x4244 of ground-truth offsets preserved; the representative field set below covers the named/typed fields and the full callback-pointer table (0xfec-0x102c). The remaining ~120 sparse idx4 fields (0x324-0x3b0, 0x1b78-0x423c) are read-only table/array accesses and are kept as-is in the ground truth; offsets unchanged. */
struct __attribute__((packed)) g1_layout_g1_device_runtime_state__param_0027 {
    uint8_t _pad_0x0[0x1];
    uint8_t field_0x1[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x3[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x34];
    uint8_t field_0x40[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x44[0x14];
    uint8_t field_0x58[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x5c[0x6d];
    uint8_t field_0xc9[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xcd[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xd1[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xd3[0x1];
    uint8_t field_0xd4[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xd5[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xd6[0x2]; /* catalog type: uint16_t */
    uint8_t brightness_level[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xda[0x5];
    uint8_t field_0xdf[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xe3[0x2];
    uint8_t field_0xe5[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xe9[0x3];
    uint8_t field_0xec[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xed[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xef[0x5dd];
    uint8_t screen_state_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x6cd[0xb];
    uint8_t field_0x6d8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x6dc[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x6de[0x3];
    uint8_t persist_task_status[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x6e2[0x92];
    uint8_t field_0x774[0x4]; /* catalog type: void * */
    uint8_t _pad_0x778[0x23c];
    uint8_t field_0x9b4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x9b8[0x12c];
    uint8_t field_0xae4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xae8[0x24];
    uint8_t field_0xb0c[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xb0d[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xb0e[0x7e];
    uint8_t field_0xb8c[0x4]; /* catalog type: void * */
    uint8_t _pad_0xb90[0x324];
    uint8_t field_0xeb4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xeb8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xebc[0x4];
    uint8_t field_0xec0[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xec2[0x6];
    uint8_t field_0xec8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xecc[0x1c];
    uint8_t field_0xee8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xeec[0x7c];
    uint8_t field_0xf68[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xf6c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xf70[0x20];
    uint8_t field_0xf90[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xf94[0x58];
    uint8_t task_cb_0[0x4]; /* catalog type: void * */
    uint8_t task_cb_1[0x4]; /* catalog type: void * */
    uint8_t task_cb_2[0x4]; /* catalog type: void * */
    uint8_t task_cb_3[0x4]; /* catalog type: void * */
    uint8_t task_cb_4[0x4]; /* catalog type: void * */
    uint8_t task_cb_5[0x4]; /* catalog type: void * */
    uint8_t task_cb_6[0x4]; /* catalog type: void * */
    uint8_t task_cb_7[0x4]; /* catalog type: void * */
    uint8_t task_cb_8[0x4]; /* catalog type: void * */
    uint8_t task_cb_9[0x4]; /* catalog type: void * */
    uint8_t task_cb_10[0x4]; /* catalog type: void * */
    uint8_t task_cb_11[0x4]; /* catalog type: void * */
    uint8_t task_cb_12[0x4]; /* catalog type: void * */
    uint8_t task_cb_13[0x4]; /* catalog type: void * */
    uint8_t task_cb_14[0x4]; /* catalog type: void * */
    uint8_t task_cb_15[0x4]; /* catalog type: void * */
    uint8_t task_cb_16[0x4]; /* catalog type: void * */
    uint8_t _pad_0x1030[0x10];
    uint8_t field_0x1040[0x4]; /* catalog type: void * */
    uint8_t _pad_0x1044[0x8];
    uint8_t field_0x104c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1050[0x4];
    uint8_t field_0x1054[0x4]; /* catalog type: void * */
    uint8_t _pad_0x1058[0x8];
    uint8_t field_0x1060[0x8]; /* catalog type: uint64_t */
    uint8_t _pad_0x1068[0x10];
    uint8_t field_0x1078[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x107c[0x14];
    uint8_t field_0x1090[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x1092[0xae6];
    uint8_t field_0x1b78[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1b7c[0x100c];
    uint8_t field_0x2b88[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x2b8c[0xf44];
    uint8_t field_0x3ad0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x3ad4[0x764];
    uint8_t field_0x4238[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x423c[0x4]; /* catalog type: uint32_t */
    uint8_t _tail_pad[0x4];
};
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x1) == 0x1, "g1_layout_g1_device_runtime_state__param_0027.field_0x1");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x2) == 0x2, "g1_layout_g1_device_runtime_state__param_0027.field_0x2");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x3) == 0x3, "g1_layout_g1_device_runtime_state__param_0027.field_0x3");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x4) == 0x4, "g1_layout_g1_device_runtime_state__param_0027.field_0x4");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x8) == 0x8, "g1_layout_g1_device_runtime_state__param_0027.field_0x8");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x40) == 0x40, "g1_layout_g1_device_runtime_state__param_0027.field_0x40");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x58) == 0x58, "g1_layout_g1_device_runtime_state__param_0027.field_0x58");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xc9) == 0xc9, "g1_layout_g1_device_runtime_state__param_0027.field_0xc9");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xcd) == 0xcd, "g1_layout_g1_device_runtime_state__param_0027.field_0xcd");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xd1) == 0xd1, "g1_layout_g1_device_runtime_state__param_0027.field_0xd1");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xd4) == 0xd4, "g1_layout_g1_device_runtime_state__param_0027.field_0xd4");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xd5) == 0xd5, "g1_layout_g1_device_runtime_state__param_0027.field_0xd5");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xd6) == 0xd6, "g1_layout_g1_device_runtime_state__param_0027.field_0xd6");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, brightness_level) == 0xd8, "g1_layout_g1_device_runtime_state__param_0027.brightness_level");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xdf) == 0xdf, "g1_layout_g1_device_runtime_state__param_0027.field_0xdf");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xe5) == 0xe5, "g1_layout_g1_device_runtime_state__param_0027.field_0xe5");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xec) == 0xec, "g1_layout_g1_device_runtime_state__param_0027.field_0xec");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xed) == 0xed, "g1_layout_g1_device_runtime_state__param_0027.field_0xed");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, screen_state_flag) == 0x6cc, "g1_layout_g1_device_runtime_state__param_0027.screen_state_flag");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x6d8) == 0x6d8, "g1_layout_g1_device_runtime_state__param_0027.field_0x6d8");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x6dc) == 0x6dc, "g1_layout_g1_device_runtime_state__param_0027.field_0x6dc");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, persist_task_status) == 0x6e1, "g1_layout_g1_device_runtime_state__param_0027.persist_task_status");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x774) == 0x774, "g1_layout_g1_device_runtime_state__param_0027.field_0x774");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x9b4) == 0x9b4, "g1_layout_g1_device_runtime_state__param_0027.field_0x9b4");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xae4) == 0xae4, "g1_layout_g1_device_runtime_state__param_0027.field_0xae4");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xb0c) == 0xb0c, "g1_layout_g1_device_runtime_state__param_0027.field_0xb0c");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xb0d) == 0xb0d, "g1_layout_g1_device_runtime_state__param_0027.field_0xb0d");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xb8c) == 0xb8c, "g1_layout_g1_device_runtime_state__param_0027.field_0xb8c");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xeb4) == 0xeb4, "g1_layout_g1_device_runtime_state__param_0027.field_0xeb4");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xeb8) == 0xeb8, "g1_layout_g1_device_runtime_state__param_0027.field_0xeb8");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xec0) == 0xec0, "g1_layout_g1_device_runtime_state__param_0027.field_0xec0");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xec8) == 0xec8, "g1_layout_g1_device_runtime_state__param_0027.field_0xec8");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xee8) == 0xee8, "g1_layout_g1_device_runtime_state__param_0027.field_0xee8");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xf68) == 0xf68, "g1_layout_g1_device_runtime_state__param_0027.field_0xf68");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xf6c) == 0xf6c, "g1_layout_g1_device_runtime_state__param_0027.field_0xf6c");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0xf90) == 0xf90, "g1_layout_g1_device_runtime_state__param_0027.field_0xf90");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_0) == 0xfec, "g1_layout_g1_device_runtime_state__param_0027.task_cb_0");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_1) == 0xff0, "g1_layout_g1_device_runtime_state__param_0027.task_cb_1");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_2) == 0xff4, "g1_layout_g1_device_runtime_state__param_0027.task_cb_2");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_3) == 0xff8, "g1_layout_g1_device_runtime_state__param_0027.task_cb_3");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_4) == 0xffc, "g1_layout_g1_device_runtime_state__param_0027.task_cb_4");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_5) == 0x1000, "g1_layout_g1_device_runtime_state__param_0027.task_cb_5");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_6) == 0x1004, "g1_layout_g1_device_runtime_state__param_0027.task_cb_6");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_7) == 0x1008, "g1_layout_g1_device_runtime_state__param_0027.task_cb_7");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_8) == 0x100c, "g1_layout_g1_device_runtime_state__param_0027.task_cb_8");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_9) == 0x1010, "g1_layout_g1_device_runtime_state__param_0027.task_cb_9");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_10) == 0x1014, "g1_layout_g1_device_runtime_state__param_0027.task_cb_10");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_11) == 0x1018, "g1_layout_g1_device_runtime_state__param_0027.task_cb_11");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_12) == 0x101c, "g1_layout_g1_device_runtime_state__param_0027.task_cb_12");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_13) == 0x1020, "g1_layout_g1_device_runtime_state__param_0027.task_cb_13");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_14) == 0x1024, "g1_layout_g1_device_runtime_state__param_0027.task_cb_14");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_15) == 0x1028, "g1_layout_g1_device_runtime_state__param_0027.task_cb_15");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, task_cb_16) == 0x102c, "g1_layout_g1_device_runtime_state__param_0027.task_cb_16");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x1040) == 0x1040, "g1_layout_g1_device_runtime_state__param_0027.field_0x1040");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x104c) == 0x104c, "g1_layout_g1_device_runtime_state__param_0027.field_0x104c");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x1054) == 0x1054, "g1_layout_g1_device_runtime_state__param_0027.field_0x1054");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x1060) == 0x1060, "g1_layout_g1_device_runtime_state__param_0027.field_0x1060");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x1078) == 0x1078, "g1_layout_g1_device_runtime_state__param_0027.field_0x1078");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x1090) == 0x1090, "g1_layout_g1_device_runtime_state__param_0027.field_0x1090");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x1b78) == 0x1b78, "g1_layout_g1_device_runtime_state__param_0027.field_0x1b78");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x2b88) == 0x2b88, "g1_layout_g1_device_runtime_state__param_0027.field_0x2b88");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x3ad0) == 0x3ad0, "g1_layout_g1_device_runtime_state__param_0027.field_0x3ad0");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x4238) == 0x4238, "g1_layout_g1_device_runtime_state__param_0027.field_0x4238");
_Static_assert(offsetof(struct g1_layout_g1_device_runtime_state__param_0027, field_0x423c) == 0x423c, "g1_layout_g1_device_runtime_state__param_0027.field_0x423c");
_Static_assert(sizeof(struct g1_layout_g1_device_runtime_state__param_0027) >= 0x4244, "g1_layout_g1_device_runtime_state__param_0027.size");

/* param_0028 | G1-original | Pin/port descriptor consumed by gpio_pin_configure_17688, carrying a config-flags byte and a pin mask. | D1+D2 verified
 * review: Downgraded from sonnet gpio_dt_spec: byte@0x1 + ushort@0x6 does not match the stock gpio_dt_spec/device layout, so not treated as a verifiable library type. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_gpio_pin_desc__param_0028 {
    uint8_t _pad_0x0[0x1];
    uint8_t cfg_flags[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x4];
    uint8_t pin_mask[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_gpio_pin_desc__param_0028, cfg_flags) == 0x1, "g1_layout_gpio_pin_desc__param_0028.cfg_flags");
_Static_assert(offsetof(struct g1_layout_gpio_pin_desc__param_0028, pin_mask) == 0x6, "g1_layout_gpio_pin_desc__param_0028.pin_mask");
_Static_assert(sizeof(struct g1_layout_gpio_pin_desc__param_0028) >= 0x8, "g1_layout_gpio_pin_desc__param_0028.size");

/* param_0029 | library | Zephyr struct device instance handle (const struct device *port) passed to gpio_pin_set_checked. | D1+D2 verified
 * review: Corrected sonnet (was ad-hoc gpio_pin_ctx). Offsets match struct device: config@0x4, api@0x8, data@0x10; name@0x0 and state@0xc unobserved. 0x8 read as int is the api pointer used as a value. */
struct __attribute__((packed)) g1_layout_device__param_0029 {
    uint8_t _pad_0x0[0x4];
    uint8_t config[0x4]; /* catalog type: const void*; SDK member: config */
    uint8_t api[0x4]; /* catalog type: const void*; SDK member: api */
    uint8_t _pad_0xc[0x4];
    uint8_t data[0x4]; /* catalog type: void*; SDK member: data */
};
_Static_assert(offsetof(struct g1_layout_device__param_0029, config) == 0x4, "g1_layout_device__param_0029.config");
_Static_assert(offsetof(struct g1_layout_device__param_0029, api) == 0x8, "g1_layout_device__param_0029.api");
_Static_assert(offsetof(struct g1_layout_device__param_0029, data) == 0x10, "g1_layout_device__param_0029.data");
_Static_assert(sizeof(struct g1_layout_device__param_0029) >= 0x14, "g1_layout_device__param_0029.size");

/* param_0030 | G1-original | GPIO device context passed to gpio_pin_get_raw_checked: a driver data/api pointer plus a pin/config word. | D1+D2 verified
 * review: Downgraded sonnet's 'struct device' claim; the two observed fields cannot pin the Zephyr device struct. is_library=false. */
struct __attribute__((packed)) g1_layout_gpio_pin_get_raw_ctx__param_0030 {
    uint8_t _pad_0x0[0x4];
    uint8_t data_or_api_ptr[0x4]; /* catalog type: void* */
    uint8_t pin_or_config[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gpio_pin_get_raw_ctx__param_0030, data_or_api_ptr) == 0x4, "g1_layout_gpio_pin_get_raw_ctx__param_0030.data_or_api_ptr");
_Static_assert(offsetof(struct g1_layout_gpio_pin_get_raw_ctx__param_0030, pin_or_config) == 0x8, "g1_layout_gpio_pin_get_raw_ctx__param_0030.pin_or_config");
_Static_assert(sizeof(struct g1_layout_gpio_pin_get_raw_ctx__param_0030) >= 0xc, "g1_layout_gpio_pin_get_raw_ctx__param_0030.size");

/* param_0032 | G1-original | ANCS (Apple Notification Center Service) client context initialized by ancs_ctx_init; handle word, attribute-id triple, and status flags across a ~0x36a object. | D1+D2 verified
 * review: Kept all offsets; sparse fields on large struct. */
struct __attribute__((packed)) g1_layout_ancs_ctx__param_0032 {
    uint8_t _pad_0x0[0xc];
    uint8_t handle_or_state[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0xc9];
    uint8_t flag_0xd9[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xda[0x172];
    uint8_t attr_id_0[0x4]; /* catalog type: uint32_t */
    uint8_t attr_id_1[0x4]; /* catalog type: uint32_t */
    uint8_t attr_id_2[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x258[0x10d];
    uint8_t flag_0x365[0x1]; /* catalog type: uint8_t */
    uint8_t flag_0x366[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_ancs_ctx__param_0032, handle_or_state) == 0xc, "g1_layout_ancs_ctx__param_0032.handle_or_state");
_Static_assert(offsetof(struct g1_layout_ancs_ctx__param_0032, flag_0xd9) == 0xd9, "g1_layout_ancs_ctx__param_0032.flag_0xd9");
_Static_assert(offsetof(struct g1_layout_ancs_ctx__param_0032, attr_id_0) == 0x24c, "g1_layout_ancs_ctx__param_0032.attr_id_0");
_Static_assert(offsetof(struct g1_layout_ancs_ctx__param_0032, attr_id_1) == 0x250, "g1_layout_ancs_ctx__param_0032.attr_id_1");
_Static_assert(offsetof(struct g1_layout_ancs_ctx__param_0032, attr_id_2) == 0x254, "g1_layout_ancs_ctx__param_0032.attr_id_2");
_Static_assert(offsetof(struct g1_layout_ancs_ctx__param_0032, flag_0x365) == 0x365, "g1_layout_ancs_ctx__param_0032.flag_0x365");
_Static_assert(offsetof(struct g1_layout_ancs_ctx__param_0032, flag_0x366) == 0x366, "g1_layout_ancs_ctx__param_0032.flag_0x366");
_Static_assert(sizeof(struct g1_layout_ancs_ctx__param_0032) >= 0x36a, "g1_layout_ancs_ctx__param_0032.size");

/* param_0033 | G1-original | Object passed to format_bt_addr_str (param_1), read word-wise as six 32-bit fields; likely an address/formatting scratch record. | D1+D2 verified
 * review: SPLIT from the 5-cid footprint-collision group: identical 6-word shape but 5 different callees with unrelated purposes, so emitted separately. G1-original, distinct from bt_addr_le_str/settings/get_sectors/k_queue cids. */
struct __attribute__((packed)) g1_layout_bt_addr_fmt_arg__param_0033 {
    uint8_t _pad_0x0[0x4];
    uint8_t word_0[0x4]; /* catalog type: uint32_t */
    uint8_t word_1[0x4]; /* catalog type: uint32_t */
    uint8_t word_2[0x4]; /* catalog type: uint32_t */
    uint8_t word_3[0x4]; /* catalog type: uint32_t */
    uint8_t word_4[0x4]; /* catalog type: uint32_t */
    uint8_t word_5[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_addr_fmt_arg__param_0033, word_0) == 0x4, "g1_layout_bt_addr_fmt_arg__param_0033.word_0");
_Static_assert(offsetof(struct g1_layout_bt_addr_fmt_arg__param_0033, word_1) == 0x8, "g1_layout_bt_addr_fmt_arg__param_0033.word_1");
_Static_assert(offsetof(struct g1_layout_bt_addr_fmt_arg__param_0033, word_2) == 0xc, "g1_layout_bt_addr_fmt_arg__param_0033.word_2");
_Static_assert(offsetof(struct g1_layout_bt_addr_fmt_arg__param_0033, word_3) == 0x10, "g1_layout_bt_addr_fmt_arg__param_0033.word_3");
_Static_assert(offsetof(struct g1_layout_bt_addr_fmt_arg__param_0033, word_4) == 0x14, "g1_layout_bt_addr_fmt_arg__param_0033.word_4");
_Static_assert(offsetof(struct g1_layout_bt_addr_fmt_arg__param_0033, word_5) == 0x18, "g1_layout_bt_addr_fmt_arg__param_0033.word_5");
_Static_assert(sizeof(struct g1_layout_bt_addr_fmt_arg__param_0033) >= 0x1c, "g1_layout_bt_addr_fmt_arg__param_0033.size");

/* param_0034 | library | Zephyr Bluetooth connection object (bt_conn) — type/role, handle, ref/state, TX queues, L2CAP channel list, LE connection parameters, and security level, shared across 21 host functions. | D1+D2 verified
 * review: Confidently bt_conn (21 members incl. bt_conn_* /l2cap/att/smp). bt_conn is defined in the private host header subsys/bluetooth/host/conn_internal.h, not in the pinned include tree, so exact member offsets can't be checked (library_verified=false). is_union=true: several early fields (0x2,0x4,0xa,0xc,0xe) are accessed both wide and byte-wise per the layout notes (handle/addr union region). */
struct __attribute__((packed)) g1_layout_bt_conn__param_0034 {
    uint8_t _pad_0x0[0x1];
    uint8_t type_or_role[0x1]; /* catalog type: uint8_t */
    uint8_t handle[0x1]; /* catalog type: uint16_t */
    uint8_t field_0x3[0x1]; /* catalog type: uint8_t */
    uint8_t state_or_ref[0x2]; /* catalog type: uint32_t */
    uint8_t field_0x6[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x7[0x1];
    uint8_t field_0x8[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x9[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xa[0x2]; /* catalog type: void * */
    uint8_t field_0xc[0x1]; /* catalog type: uint32_t */
    uint8_t field_0xd[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xe[0x2]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t tx_pending_list_head[0x4]; /* catalog type: void * */
    uint8_t tx_notify_list_head[0x4]; /* catalog type: void * */
    uint8_t tx_data_count[0x4]; /* catalog type: uint32_t */
    uint8_t channel_list_head[0x4]; /* catalog type: void * */
    uint8_t le_param_or_role_ptr[0x4]; /* catalog type: void * */
    uint8_t _pad_0x28[0x2c];
    uint8_t field_0x54[0x4]; /* catalog type: void * */
    uint8_t field_0x58[0x4]; /* catalog type: void * */
    uint8_t _pad_0x5c[0x4a];
    uint8_t le_interval[0x2]; /* catalog type: uint16_t */
    uint8_t le_latency[0x2]; /* catalog type: uint16_t */
    uint8_t le_timeout[0x2]; /* catalog type: uint16_t */
    uint8_t le_interval_min[0x2]; /* catalog type: uint16_t */
    uint8_t le_interval_max[0x2]; /* catalog type: uint16_t */
    uint8_t le_pending_latency[0x2]; /* catalog type: uint16_t */
    uint8_t le_pending_timeout[0x2]; /* catalog type: uint16_t */
    uint8_t security_level[0x1]; /* catalog type: uint8_t */
    uint8_t security_flags[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xb6[0xa];
    uint8_t field_0xc0[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, type_or_role) == 0x1, "g1_layout_bt_conn__param_0034.type_or_role");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, handle) == 0x2, "g1_layout_bt_conn__param_0034.handle");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, field_0x3) == 0x3, "g1_layout_bt_conn__param_0034.field_0x3");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, state_or_ref) == 0x4, "g1_layout_bt_conn__param_0034.state_or_ref");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, field_0x6) == 0x6, "g1_layout_bt_conn__param_0034.field_0x6");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, field_0x8) == 0x8, "g1_layout_bt_conn__param_0034.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, field_0x9) == 0x9, "g1_layout_bt_conn__param_0034.field_0x9");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, field_0xa) == 0xa, "g1_layout_bt_conn__param_0034.field_0xa");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, field_0xc) == 0xc, "g1_layout_bt_conn__param_0034.field_0xc");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, field_0xd) == 0xd, "g1_layout_bt_conn__param_0034.field_0xd");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, field_0xe) == 0xe, "g1_layout_bt_conn__param_0034.field_0xe");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, field_0x10) == 0x10, "g1_layout_bt_conn__param_0034.field_0x10");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, tx_pending_list_head) == 0x14, "g1_layout_bt_conn__param_0034.tx_pending_list_head");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, tx_notify_list_head) == 0x18, "g1_layout_bt_conn__param_0034.tx_notify_list_head");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, tx_data_count) == 0x1c, "g1_layout_bt_conn__param_0034.tx_data_count");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, channel_list_head) == 0x20, "g1_layout_bt_conn__param_0034.channel_list_head");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, le_param_or_role_ptr) == 0x24, "g1_layout_bt_conn__param_0034.le_param_or_role_ptr");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, field_0x54) == 0x54, "g1_layout_bt_conn__param_0034.field_0x54");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, field_0x58) == 0x58, "g1_layout_bt_conn__param_0034.field_0x58");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, le_interval) == 0xa6, "g1_layout_bt_conn__param_0034.le_interval");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, le_latency) == 0xa8, "g1_layout_bt_conn__param_0034.le_latency");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, le_timeout) == 0xaa, "g1_layout_bt_conn__param_0034.le_timeout");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, le_interval_min) == 0xac, "g1_layout_bt_conn__param_0034.le_interval_min");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, le_interval_max) == 0xae, "g1_layout_bt_conn__param_0034.le_interval_max");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, le_pending_latency) == 0xb0, "g1_layout_bt_conn__param_0034.le_pending_latency");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, le_pending_timeout) == 0xb2, "g1_layout_bt_conn__param_0034.le_pending_timeout");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, security_level) == 0xb4, "g1_layout_bt_conn__param_0034.security_level");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, security_flags) == 0xb5, "g1_layout_bt_conn__param_0034.security_flags");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0034, field_0xc0) == 0xc0, "g1_layout_bt_conn__param_0034.field_0xc0");
_Static_assert(sizeof(struct g1_layout_bt_conn__param_0034) >= 0xc4, "g1_layout_bt_conn__param_0034.size");

/* param_0035 | library | ANCS (Apple Notification Center Service) data-source attribute record (id/len/data ptr) passed to bt_ancs_data_source_handler. | D1+D2 verified
 * review: nRF Connect SDK ANCS client type; layout not confirmed against a pinned header. id/len/data-ptr triplet at 0x4/0x8/0xc. */
struct __attribute__((packed)) g1_layout_bt_ancs_attr_data__param_0035 {
    uint8_t _pad_0x0[0x4];
    uint8_t attr_id[0x4]; /* catalog type: uint32_t */
    uint8_t attr_len[0x4]; /* catalog type: uint32_t */
    uint8_t attr_data_ptr[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_bt_ancs_attr_data__param_0035, attr_id) == 0x4, "g1_layout_bt_ancs_attr_data__param_0035.attr_id");
_Static_assert(offsetof(struct g1_layout_bt_ancs_attr_data__param_0035, attr_len) == 0x8, "g1_layout_bt_ancs_attr_data__param_0035.attr_len");
_Static_assert(offsetof(struct g1_layout_bt_ancs_attr_data__param_0035, attr_data_ptr) == 0xc, "g1_layout_bt_ancs_attr_data__param_0035.attr_data_ptr");
_Static_assert(sizeof(struct g1_layout_bt_ancs_attr_data__param_0035) >= 0x10, "g1_layout_bt_ancs_attr_data__param_0035.size");

/* param_0038 | G1-original | Large shared application/BLE context (~0x84a) passed across ANCS, audio, DMIC, notification dispatch: node/link ptrs, length, status words and flag bytes. | D1+D2 verified
 * review: Unified across 7 functions; G1-original aggregate. Kept all sparse offsets verbatim. */
struct __attribute__((packed)) g1_layout_app_ble_ctx_block__param_0038 {
    uint8_t _pad_0x0[0xc];
    uint8_t field_0xc[0x4]; /* catalog type: void* */
    uint8_t link_next[0x4]; /* catalog type: void* */
    uint8_t length_or_count[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x24];
    uint8_t status_0x3c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x40[0x1];
    uint8_t flag_0x41[0x1]; /* catalog type: uint8_t */
    uint8_t flag_0x42[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x43[0x1];
    uint8_t flag_0x44[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x45[0x1f];
    uint8_t flag_0x64[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x65[0x17f];
    uint8_t status_0x1e4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1e8[0x571];
    uint8_t field_0x759[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x75a[0xea];
    uint8_t field_0x844[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x845[0x1];
    uint8_t field_0x846[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_app_ble_ctx_block__param_0038, field_0xc) == 0xc, "g1_layout_app_ble_ctx_block__param_0038.field_0xc");
_Static_assert(offsetof(struct g1_layout_app_ble_ctx_block__param_0038, link_next) == 0x10, "g1_layout_app_ble_ctx_block__param_0038.link_next");
_Static_assert(offsetof(struct g1_layout_app_ble_ctx_block__param_0038, length_or_count) == 0x14, "g1_layout_app_ble_ctx_block__param_0038.length_or_count");
_Static_assert(offsetof(struct g1_layout_app_ble_ctx_block__param_0038, status_0x3c) == 0x3c, "g1_layout_app_ble_ctx_block__param_0038.status_0x3c");
_Static_assert(offsetof(struct g1_layout_app_ble_ctx_block__param_0038, flag_0x41) == 0x41, "g1_layout_app_ble_ctx_block__param_0038.flag_0x41");
_Static_assert(offsetof(struct g1_layout_app_ble_ctx_block__param_0038, flag_0x42) == 0x42, "g1_layout_app_ble_ctx_block__param_0038.flag_0x42");
_Static_assert(offsetof(struct g1_layout_app_ble_ctx_block__param_0038, flag_0x44) == 0x44, "g1_layout_app_ble_ctx_block__param_0038.flag_0x44");
_Static_assert(offsetof(struct g1_layout_app_ble_ctx_block__param_0038, flag_0x64) == 0x64, "g1_layout_app_ble_ctx_block__param_0038.flag_0x64");
_Static_assert(offsetof(struct g1_layout_app_ble_ctx_block__param_0038, status_0x1e4) == 0x1e4, "g1_layout_app_ble_ctx_block__param_0038.status_0x1e4");
_Static_assert(offsetof(struct g1_layout_app_ble_ctx_block__param_0038, field_0x759) == 0x759, "g1_layout_app_ble_ctx_block__param_0038.field_0x759");
_Static_assert(offsetof(struct g1_layout_app_ble_ctx_block__param_0038, field_0x844) == 0x844, "g1_layout_app_ble_ctx_block__param_0038.field_0x844");
_Static_assert(offsetof(struct g1_layout_app_ble_ctx_block__param_0038, field_0x846) == 0x846, "g1_layout_app_ble_ctx_block__param_0038.field_0x846");
_Static_assert(sizeof(struct g1_layout_app_ble_ctx_block__param_0038) >= 0x84a, "g1_layout_app_ble_ctx_block__param_0038.size");

/* param_0039 | G1-original | Wire-format command/message context threaded through audio firmware-load handling, UART callback, notification response building, and uint32_to_little_endian serialization. | D1+D2 verified
 * review: Single-cid, 5 members. Overlapping 16/32-bit access at 0x0/0x4/0x6/0x8 -> union. Corrected sonnet is_array=true (this is a heterogeneous message record, not an array). */
struct __attribute__((packed)) g1_layout_audio_fw_load_msg__param_0039 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x4[0x2]; /* catalog type: uint32_t */
    uint8_t field_0x6[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x8[0x2]; /* catalog type: uint32_t */
    uint8_t field_0xa[0x2]; /* catalog type: uint16_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x28[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x2c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x30[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x34[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x38[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x3c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x0) == 0x0, "g1_layout_audio_fw_load_msg__param_0039.field_0x0");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x4) == 0x4, "g1_layout_audio_fw_load_msg__param_0039.field_0x4");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x6) == 0x6, "g1_layout_audio_fw_load_msg__param_0039.field_0x6");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x8) == 0x8, "g1_layout_audio_fw_load_msg__param_0039.field_0x8");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0xa) == 0xa, "g1_layout_audio_fw_load_msg__param_0039.field_0xa");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0xc) == 0xc, "g1_layout_audio_fw_load_msg__param_0039.field_0xc");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x10) == 0x10, "g1_layout_audio_fw_load_msg__param_0039.field_0x10");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x14) == 0x14, "g1_layout_audio_fw_load_msg__param_0039.field_0x14");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x18) == 0x18, "g1_layout_audio_fw_load_msg__param_0039.field_0x18");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x1c) == 0x1c, "g1_layout_audio_fw_load_msg__param_0039.field_0x1c");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x20) == 0x20, "g1_layout_audio_fw_load_msg__param_0039.field_0x20");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x24) == 0x24, "g1_layout_audio_fw_load_msg__param_0039.field_0x24");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x28) == 0x28, "g1_layout_audio_fw_load_msg__param_0039.field_0x28");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x2c) == 0x2c, "g1_layout_audio_fw_load_msg__param_0039.field_0x2c");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x30) == 0x30, "g1_layout_audio_fw_load_msg__param_0039.field_0x30");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x34) == 0x34, "g1_layout_audio_fw_load_msg__param_0039.field_0x34");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x38) == 0x38, "g1_layout_audio_fw_load_msg__param_0039.field_0x38");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_msg__param_0039, field_0x3c) == 0x3c, "g1_layout_audio_fw_load_msg__param_0039.field_0x3c");
_Static_assert(sizeof(struct g1_layout_audio_fw_load_msg__param_0039) >= 0x40, "g1_layout_audio_fw_load_msg__param_0039.size");

/* param_0040 | G1-original | G1-original BLE background worker context: init/state flags, a pending work-item pointer, and trailing status counters, used by ble_work_thread. | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_ble_work_thread_ctx__param_0040 {
    uint8_t _pad_0x0[0x10];
    uint8_t init_flag[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x4];
    uint8_t state[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x19[0x22f];
    uint8_t done_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x249[0xb];
    uint8_t pending_item[0x4]; /* catalog type: void * */
    uint8_t _pad_0x258[0x100];
    uint8_t counter_a[0x4]; /* catalog type: uint32_t */
    uint8_t counter_b[0x4]; /* catalog type: uint32_t */
    uint8_t counter_c[0x4]; /* catalog type: uint32_t */
    uint8_t flags[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_ble_work_thread_ctx__param_0040, init_flag) == 0x10, "g1_layout_ble_work_thread_ctx__param_0040.init_flag");
_Static_assert(offsetof(struct g1_layout_ble_work_thread_ctx__param_0040, state) == 0x18, "g1_layout_ble_work_thread_ctx__param_0040.state");
_Static_assert(offsetof(struct g1_layout_ble_work_thread_ctx__param_0040, done_flag) == 0x248, "g1_layout_ble_work_thread_ctx__param_0040.done_flag");
_Static_assert(offsetof(struct g1_layout_ble_work_thread_ctx__param_0040, pending_item) == 0x254, "g1_layout_ble_work_thread_ctx__param_0040.pending_item");
_Static_assert(offsetof(struct g1_layout_ble_work_thread_ctx__param_0040, counter_a) == 0x358, "g1_layout_ble_work_thread_ctx__param_0040.counter_a");
_Static_assert(offsetof(struct g1_layout_ble_work_thread_ctx__param_0040, counter_b) == 0x35c, "g1_layout_ble_work_thread_ctx__param_0040.counter_b");
_Static_assert(offsetof(struct g1_layout_ble_work_thread_ctx__param_0040, counter_c) == 0x360, "g1_layout_ble_work_thread_ctx__param_0040.counter_c");
_Static_assert(offsetof(struct g1_layout_ble_work_thread_ctx__param_0040, flags) == 0x364, "g1_layout_ble_work_thread_ctx__param_0040.flags");
_Static_assert(sizeof(struct g1_layout_ble_work_thread_ctx__param_0040) >= 0x368, "g1_layout_ble_work_thread_ctx__param_0040.size");

/* param_0041 | G1-original | Initialization parameter block consumed by sett_init to configure a settings entry (three read words). | D1+D2 verified
 * review: Single-cid G1 settings init params. Offsets kept. */
struct __attribute__((packed)) g1_layout_sett_init_params__param_0041 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_sett_init_params__param_0041, field_0x4) == 0x4, "g1_layout_sett_init_params__param_0041.field_0x4");
_Static_assert(offsetof(struct g1_layout_sett_init_params__param_0041, field_0x8) == 0x8, "g1_layout_sett_init_params__param_0041.field_0x8");
_Static_assert(offsetof(struct g1_layout_sett_init_params__param_0041, field_0xc) == 0xc, "g1_layout_sett_init_params__param_0041.field_0xc");
_Static_assert(sizeof(struct g1_layout_sett_init_params__param_0041) >= 0x10, "g1_layout_sett_init_params__param_0041.size");

/* param_0042 | G1-original | Large shared settings/status blob (>=0x1078 bytes) read by load_sys_setting and build_and_send_device_status_report; many scalar config fields across a big buffer. | D1+D2 verified
 * review: G1-original. is_union=true: 0xedc accessed both 2-wide and 4-wide (overlaps 0xede). Offsets unchanged. */
struct __attribute__((packed)) g1_layout_device_settings_blob__param_0042 {
    uint8_t _pad_0x0[0x2];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x3[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x4[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x5[0xecf];
    uint8_t field_0xed4[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xed5[0x5];
    uint8_t field_0xeda[0x2]; /* catalog type: uint16_t */
    uint8_t field_0xedc[0x2]; /* catalog type: uint32_t */
    uint8_t field_0xede[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xee0[0x84];
    uint8_t field_0xf64[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xf68[0x2c];
    uint8_t field_0xf94[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xf98[0x8];
    uint8_t field_0xfa0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xfa4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xfa8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xfac[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xfb0[0x4]; /* catalog type: int32_t */
    uint8_t field_0xfb4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xfb8[0x98];
    uint8_t field_0x1050[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x1054[0x1e];
    uint8_t field_0x1072[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x1074[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0x2) == 0x2, "g1_layout_device_settings_blob__param_0042.field_0x2");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0x3) == 0x3, "g1_layout_device_settings_blob__param_0042.field_0x3");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0x4) == 0x4, "g1_layout_device_settings_blob__param_0042.field_0x4");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0xed4) == 0xed4, "g1_layout_device_settings_blob__param_0042.field_0xed4");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0xeda) == 0xeda, "g1_layout_device_settings_blob__param_0042.field_0xeda");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0xedc) == 0xedc, "g1_layout_device_settings_blob__param_0042.field_0xedc");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0xede) == 0xede, "g1_layout_device_settings_blob__param_0042.field_0xede");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0xf64) == 0xf64, "g1_layout_device_settings_blob__param_0042.field_0xf64");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0xf94) == 0xf94, "g1_layout_device_settings_blob__param_0042.field_0xf94");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0xfa0) == 0xfa0, "g1_layout_device_settings_blob__param_0042.field_0xfa0");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0xfa4) == 0xfa4, "g1_layout_device_settings_blob__param_0042.field_0xfa4");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0xfa8) == 0xfa8, "g1_layout_device_settings_blob__param_0042.field_0xfa8");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0xfac) == 0xfac, "g1_layout_device_settings_blob__param_0042.field_0xfac");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0xfb0) == 0xfb0, "g1_layout_device_settings_blob__param_0042.field_0xfb0");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0xfb4) == 0xfb4, "g1_layout_device_settings_blob__param_0042.field_0xfb4");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0x1050) == 0x1050, "g1_layout_device_settings_blob__param_0042.field_0x1050");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0x1072) == 0x1072, "g1_layout_device_settings_blob__param_0042.field_0x1072");
_Static_assert(offsetof(struct g1_layout_device_settings_blob__param_0042, field_0x1074) == 0x1074, "g1_layout_device_settings_blob__param_0042.field_0x1074");
_Static_assert(sizeof(struct g1_layout_device_settings_blob__param_0042) >= 0x1078, "g1_layout_device_settings_blob__param_0042.size");

/* param_0043 | G1-original | Telemetry 'burial point' record buffer (~0x10e0 bytes) loaded by load_burial_point; large data blob followed by count/flags/status trailer. | D1+D2 verified
 * review: G1-original analytics record. 0x10da accessed as both byte and short (sub-field access, not a distinct union). */
struct __attribute__((packed)) g1_layout_burial_point_record__param_0043 {
    uint8_t _pad_0x0[0x10c6];
    uint8_t record_count[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10ca[0x10];
    uint8_t flags[0x2]; /* catalog type: uint16_t */
    uint8_t status[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_burial_point_record__param_0043, record_count) == 0x10c6, "g1_layout_burial_point_record__param_0043.record_count");
_Static_assert(offsetof(struct g1_layout_burial_point_record__param_0043, flags) == 0x10da, "g1_layout_burial_point_record__param_0043.flags");
_Static_assert(offsetof(struct g1_layout_burial_point_record__param_0043, status) == 0x10dc, "g1_layout_burial_point_record__param_0043.status");
_Static_assert(sizeof(struct g1_layout_burial_point_record__param_0043) >= 0x10e0, "g1_layout_burial_point_record__param_0043.size");

/* param_0044 | G1-original | Large (>=0x1044) persistent device-info storage buffer; device_info_register_persistent_fields touches two trailer counters and a tail pointer. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_device_info_persist_store__param_0044 {
    uint8_t _pad_0x0[0xfec];
    uint8_t counter_a[0x4]; /* catalog type: uint32_t */
    uint8_t counter_b[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xff4[0x4c];
    uint8_t tail_ptr[0x4]; /* catalog type: void* */
};
_Static_assert(offsetof(struct g1_layout_device_info_persist_store__param_0044, counter_a) == 0xfec, "g1_layout_device_info_persist_store__param_0044.counter_a");
_Static_assert(offsetof(struct g1_layout_device_info_persist_store__param_0044, counter_b) == 0xff0, "g1_layout_device_info_persist_store__param_0044.counter_b");
_Static_assert(offsetof(struct g1_layout_device_info_persist_store__param_0044, tail_ptr) == 0x1040, "g1_layout_device_info_persist_store__param_0044.tail_ptr");
_Static_assert(sizeof(struct g1_layout_device_info_persist_store__param_0044) >= 0x1044, "g1_layout_device_info_persist_store__param_0044.size");

/* param_0045 | G1-original | On-flash system settings record read by read_sys_settting_from_flash (validity/version bytes, magic/crc words, length, flags, and a 6-word + 2-word data body). | D1+D2 verified
 * review: Kept all 15 offsets exactly; names refined from access widths. */
struct __attribute__((packed)) g1_layout_sys_settings_record__param_0045 {
    uint8_t _pad_0x0[0x2];
    uint8_t valid_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x2];
    uint8_t version[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x6[0x6];
    uint8_t magic_or_crc_a[0x4]; /* catalog type: uint32_t */
    uint8_t magic_or_crc_b[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0xa];
    uint8_t length[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x20[0x35];
    uint8_t flag_a[0x1]; /* catalog type: uint8_t */
    uint8_t flag_b[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x57[0x9];
    uint8_t data_0[0x4]; /* catalog type: uint32_t */
    uint8_t data_1[0x4]; /* catalog type: uint32_t */
    uint8_t data_2[0x4]; /* catalog type: uint32_t */
    uint8_t data_3[0x4]; /* catalog type: uint32_t */
    uint8_t data_4[0x4]; /* catalog type: uint32_t */
    uint8_t data_5[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x78[0x4];
    uint8_t tail_0[0x4]; /* catalog type: uint32_t */
    uint8_t tail_1[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, valid_flag) == 0x2, "g1_layout_sys_settings_record__param_0045.valid_flag");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, version) == 0x5, "g1_layout_sys_settings_record__param_0045.version");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, magic_or_crc_a) == 0xc, "g1_layout_sys_settings_record__param_0045.magic_or_crc_a");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, magic_or_crc_b) == 0x10, "g1_layout_sys_settings_record__param_0045.magic_or_crc_b");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, length) == 0x1e, "g1_layout_sys_settings_record__param_0045.length");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, flag_a) == 0x55, "g1_layout_sys_settings_record__param_0045.flag_a");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, flag_b) == 0x56, "g1_layout_sys_settings_record__param_0045.flag_b");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, data_0) == 0x60, "g1_layout_sys_settings_record__param_0045.data_0");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, data_1) == 0x64, "g1_layout_sys_settings_record__param_0045.data_1");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, data_2) == 0x68, "g1_layout_sys_settings_record__param_0045.data_2");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, data_3) == 0x6c, "g1_layout_sys_settings_record__param_0045.data_3");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, data_4) == 0x70, "g1_layout_sys_settings_record__param_0045.data_4");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, data_5) == 0x74, "g1_layout_sys_settings_record__param_0045.data_5");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, tail_0) == 0x7c, "g1_layout_sys_settings_record__param_0045.tail_0");
_Static_assert(offsetof(struct g1_layout_sys_settings_record__param_0045, tail_1) == 0x80, "g1_layout_sys_settings_record__param_0045.tail_1");
_Static_assert(sizeof(struct g1_layout_sys_settings_record__param_0045) >= 0x84, "g1_layout_sys_settings_record__param_0045.size");

/* param_0046 | G1-original | User settings record loaded from flash by read_usr_settting_from_flash; trailing flag byte and word near the end of the record. | D1+D2 verified
 * review: G1-original; kept sonnet naming, only two tail fields observed. */
struct __attribute__((packed)) g1_layout_usr_settings_record__param_0046 {
    uint8_t _pad_0x0[0x15];
    uint8_t flag_byte[0x1]; /* catalog type: uint8_t */
    uint8_t trailing_word[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_usr_settings_record__param_0046, flag_byte) == 0x15, "g1_layout_usr_settings_record__param_0046.flag_byte");
_Static_assert(offsetof(struct g1_layout_usr_settings_record__param_0046, trailing_word) == 0x16, "g1_layout_usr_settings_record__param_0046.trailing_word");
_Static_assert(sizeof(struct g1_layout_usr_settings_record__param_0046) >= 0x18, "g1_layout_usr_settings_record__param_0046.size");

/* param_0049 | G1-original | G1-original event record initialized by event_record_init: five payload/timestamp words plus a 16-bit type field. | D1+D2 verified
 * review: G1-original; all six fields written by the init routine. */
struct __attribute__((packed)) g1_layout_event_record__param_0049 {
    uint8_t _pad_0x0[0x4];
    uint8_t word0[0x4]; /* catalog type: uint32_t */
    uint8_t word1[0x4]; /* catalog type: uint32_t */
    uint8_t word2[0x4]; /* catalog type: uint32_t */
    uint8_t word3[0x4]; /* catalog type: uint32_t */
    uint8_t word4[0x4]; /* catalog type: uint32_t */
    uint8_t record_type[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_event_record__param_0049, word0) == 0x4, "g1_layout_event_record__param_0049.word0");
_Static_assert(offsetof(struct g1_layout_event_record__param_0049, word1) == 0x8, "g1_layout_event_record__param_0049.word1");
_Static_assert(offsetof(struct g1_layout_event_record__param_0049, word2) == 0xc, "g1_layout_event_record__param_0049.word2");
_Static_assert(offsetof(struct g1_layout_event_record__param_0049, word3) == 0x10, "g1_layout_event_record__param_0049.word3");
_Static_assert(offsetof(struct g1_layout_event_record__param_0049, word4) == 0x14, "g1_layout_event_record__param_0049.word4");
_Static_assert(offsetof(struct g1_layout_event_record__param_0049, record_type) == 0x18, "g1_layout_event_record__param_0049.record_type");
_Static_assert(sizeof(struct g1_layout_event_record__param_0049) >= 0x1c, "g1_layout_event_record__param_0049.size");

/* param_0050 | G1-original | Descriptor passed to event_record_init: 16-bit tag + 32-bit id. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_event_record_desc__param_0050 {
    uint8_t _pad_0x0[0x2];
    uint8_t tag[0x2]; /* catalog type: uint16_t */
    uint8_t id[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_event_record_desc__param_0050, tag) == 0x2, "g1_layout_event_record_desc__param_0050.tag");
_Static_assert(offsetof(struct g1_layout_event_record_desc__param_0050, id) == 0x4, "g1_layout_event_record_desc__param_0050.id");
_Static_assert(sizeof(struct g1_layout_event_record_desc__param_0050) >= 0x8, "g1_layout_event_record_desc__param_0050.size");

/* param_0051 | G1-original | Output record filled by fill_record_type8: five leading words written, plus a trailing index read at 0x60. | D1+D2 verified
 * review: Single-cid. */
struct __attribute__((packed)) g1_layout_record_type8__param_0051 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x48];
    uint8_t field_0x60[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_record_type8__param_0051, field_0x4) == 0x4, "g1_layout_record_type8__param_0051.field_0x4");
_Static_assert(offsetof(struct g1_layout_record_type8__param_0051, field_0x8) == 0x8, "g1_layout_record_type8__param_0051.field_0x8");
_Static_assert(offsetof(struct g1_layout_record_type8__param_0051, field_0xc) == 0xc, "g1_layout_record_type8__param_0051.field_0xc");
_Static_assert(offsetof(struct g1_layout_record_type8__param_0051, field_0x10) == 0x10, "g1_layout_record_type8__param_0051.field_0x10");
_Static_assert(offsetof(struct g1_layout_record_type8__param_0051, field_0x14) == 0x14, "g1_layout_record_type8__param_0051.field_0x14");
_Static_assert(offsetof(struct g1_layout_record_type8__param_0051, field_0x60) == 0x60, "g1_layout_record_type8__param_0051.field_0x60");
_Static_assert(sizeof(struct g1_layout_record_type8__param_0051) >= 0x64, "g1_layout_record_type8__param_0051.size");

/* param_0052 | G1-original | G1-original type-8 record builder context used by fill_record_type8: a type byte and a value word. | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_record_type8_ctx__param_0052 {
    uint8_t _pad_0x0[0x2];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x1];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_record_type8_ctx__param_0052, field_0x2) == 0x2, "g1_layout_record_type8_ctx__param_0052.field_0x2");
_Static_assert(offsetof(struct g1_layout_record_type8_ctx__param_0052, field_0x4) == 0x4, "g1_layout_record_type8_ctx__param_0052.field_0x4");
_Static_assert(sizeof(struct g1_layout_record_type8_ctx__param_0052) >= 0x8, "g1_layout_record_type8_ctx__param_0052.size");

/* param_0053 | G1-original | First pointer argument (param_1) to st25dv_build_and_write_ndef_records; record/context block (8 words) used to assemble NDEF records for the ST25DV NFC tag. | D1+D2 verified
 * review: Single-cid. Kept distinct from param_0054 (param_2 of the same function). Note the 0x14 gap in the layout. Offsets kept. */
struct __attribute__((packed)) g1_layout_st25dv_ndef_build_ctx_p1__param_0053 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x4];
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p1__param_0053, field_0x4) == 0x4, "g1_layout_st25dv_ndef_build_ctx_p1__param_0053.field_0x4");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p1__param_0053, field_0x8) == 0x8, "g1_layout_st25dv_ndef_build_ctx_p1__param_0053.field_0x8");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p1__param_0053, field_0xc) == 0xc, "g1_layout_st25dv_ndef_build_ctx_p1__param_0053.field_0xc");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p1__param_0053, field_0x10) == 0x10, "g1_layout_st25dv_ndef_build_ctx_p1__param_0053.field_0x10");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p1__param_0053, field_0x18) == 0x18, "g1_layout_st25dv_ndef_build_ctx_p1__param_0053.field_0x18");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p1__param_0053, field_0x1c) == 0x1c, "g1_layout_st25dv_ndef_build_ctx_p1__param_0053.field_0x1c");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p1__param_0053, field_0x20) == 0x20, "g1_layout_st25dv_ndef_build_ctx_p1__param_0053.field_0x20");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p1__param_0053, field_0x24) == 0x24, "g1_layout_st25dv_ndef_build_ctx_p1__param_0053.field_0x24");
_Static_assert(sizeof(struct g1_layout_st25dv_ndef_build_ctx_p1__param_0053) >= 0x28, "g1_layout_st25dv_ndef_build_ctx_p1__param_0053.size");

/* param_0054 | G1-original | Second pointer argument (param_2) to st25dv_build_and_write_ndef_records; an 8-word context/record block used while assembling NDEF records for the ST25DV NFC tag. | D1+D2 verified
 * review: Split from footprint-collision group global_0965. Distinct from param_0053 (which is param_1 of the same function) — different argument slot, kept separate. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_st25dv_ndef_build_ctx_p2__param_0054 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p2__param_0054, field_0x4) == 0x4, "g1_layout_st25dv_ndef_build_ctx_p2__param_0054.field_0x4");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p2__param_0054, field_0x8) == 0x8, "g1_layout_st25dv_ndef_build_ctx_p2__param_0054.field_0x8");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p2__param_0054, field_0xc) == 0xc, "g1_layout_st25dv_ndef_build_ctx_p2__param_0054.field_0xc");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p2__param_0054, field_0x10) == 0x10, "g1_layout_st25dv_ndef_build_ctx_p2__param_0054.field_0x10");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p2__param_0054, field_0x14) == 0x14, "g1_layout_st25dv_ndef_build_ctx_p2__param_0054.field_0x14");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p2__param_0054, field_0x18) == 0x18, "g1_layout_st25dv_ndef_build_ctx_p2__param_0054.field_0x18");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p2__param_0054, field_0x1c) == 0x1c, "g1_layout_st25dv_ndef_build_ctx_p2__param_0054.field_0x1c");
_Static_assert(offsetof(struct g1_layout_st25dv_ndef_build_ctx_p2__param_0054, field_0x20) == 0x20, "g1_layout_st25dv_ndef_build_ctx_p2__param_0054.field_0x20");
_Static_assert(sizeof(struct g1_layout_st25dv_ndef_build_ctx_p2__param_0054) >= 0x24, "g1_layout_st25dv_ndef_build_ctx_p2__param_0054.size");

/* param_0055 | G1-original | NDEF record descriptor (pointer/length-style pair) consumed by st25dv_build_and_write_ndef_records when assembling NFC tag records. | D1+D2 verified
 * review: G1-original; likely array of {word,word} record descriptors. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_ndef_record_desc__param_0055 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ndef_record_desc__param_0055, field_0x4) == 0x4, "g1_layout_ndef_record_desc__param_0055.field_0x4");
_Static_assert(offsetof(struct g1_layout_ndef_record_desc__param_0055, field_0x8) == 0x8, "g1_layout_ndef_record_desc__param_0055.field_0x8");
_Static_assert(sizeof(struct g1_layout_ndef_record_desc__param_0055) >= 0xc, "g1_layout_ndef_record_desc__param_0055.size");

/* param_0057 | G1-original | UI 'box' event/message passed to process_box_event (param_1): a type byte and a payload word. | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_box_event__param_0057 {
    uint8_t _pad_0x0[0x2];
    uint8_t event_type[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x5];
    uint8_t payload[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_box_event__param_0057, event_type) == 0x2, "g1_layout_box_event__param_0057.event_type");
_Static_assert(offsetof(struct g1_layout_box_event__param_0057, payload) == 0x8, "g1_layout_box_event__param_0057.payload");
_Static_assert(sizeof(struct g1_layout_box_event__param_0057) >= 0xc, "g1_layout_box_event__param_0057.size");

/* param_0058 | G1-original | UI 'box' widget event object consumed by process_box_event; event type/args plus scattered state fields within a larger UI object. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_box_event_ctx__param_0058 {
    uint8_t _pad_0x0[0x4];
    uint8_t event_type[0x4]; /* catalog type: uint32_t */
    uint8_t event_arg0[0x4]; /* catalog type: uint32_t */
    uint8_t event_arg1[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x4];
    uint8_t box_state[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x18];
    uint8_t box_field_30[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x34[0x18];
    uint8_t box_field_4c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x50[0x4];
    uint8_t box_field_54[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x58[0x78];
    uint8_t box_tail_field[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_box_event_ctx__param_0058, event_type) == 0x4, "g1_layout_box_event_ctx__param_0058.event_type");
_Static_assert(offsetof(struct g1_layout_box_event_ctx__param_0058, event_arg0) == 0x8, "g1_layout_box_event_ctx__param_0058.event_arg0");
_Static_assert(offsetof(struct g1_layout_box_event_ctx__param_0058, event_arg1) == 0xc, "g1_layout_box_event_ctx__param_0058.event_arg1");
_Static_assert(offsetof(struct g1_layout_box_event_ctx__param_0058, box_state) == 0x14, "g1_layout_box_event_ctx__param_0058.box_state");
_Static_assert(offsetof(struct g1_layout_box_event_ctx__param_0058, box_field_30) == 0x30, "g1_layout_box_event_ctx__param_0058.box_field_30");
_Static_assert(offsetof(struct g1_layout_box_event_ctx__param_0058, box_field_4c) == 0x4c, "g1_layout_box_event_ctx__param_0058.box_field_4c");
_Static_assert(offsetof(struct g1_layout_box_event_ctx__param_0058, box_field_54) == 0x54, "g1_layout_box_event_ctx__param_0058.box_field_54");
_Static_assert(offsetof(struct g1_layout_box_event_ctx__param_0058, box_tail_field) == 0xd0, "g1_layout_box_event_ctx__param_0058.box_tail_field");
_Static_assert(sizeof(struct g1_layout_box_event_ctx__param_0058) >= 0xd4, "g1_layout_box_event_ctx__param_0058.size");

/* param_0059 | G1-original | IPC endpoint context shared across ipc_ept_op_a_locked_retry / ipc_send_len_prefixed_packet_locked_retry / pt_comm_transport_write (ipc instance pointer + endpoint id). | D1+D2 verified
 * review: 3 members agree on layout; kept offsets. G1 wrapper around ipc_service usage. */
struct __attribute__((packed)) g1_layout_ipc_ept_ctx__param_0059 {
    uint8_t _pad_0x0[0x4];
    uint8_t ipc_instance_ptr[0x4]; /* catalog type: void * */
    uint8_t ept_id[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x4];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ipc_ept_ctx__param_0059, ipc_instance_ptr) == 0x4, "g1_layout_ipc_ept_ctx__param_0059.ipc_instance_ptr");
_Static_assert(offsetof(struct g1_layout_ipc_ept_ctx__param_0059, ept_id) == 0x8, "g1_layout_ipc_ept_ctx__param_0059.ept_id");
_Static_assert(offsetof(struct g1_layout_ipc_ept_ctx__param_0059, field_0x10) == 0x10, "g1_layout_ipc_ept_ctx__param_0059.field_0x10");
_Static_assert(sizeof(struct g1_layout_ipc_ept_ctx__param_0059) >= 0x14, "g1_layout_ipc_ept_ctx__param_0059.size");

/* param_0060 | G1-original | IPC endpoint operation context used by the locked-retry handlers for IPC-service endpoints B and C: a retry counter and an endpoint state word. | D1+D2 verified
 * review: Ground-truth hint is G1-original; the two G1 wrapper functions (ipc_ept_op_b/c_locked_retry) drive it. Corrected sonnet's is_library=True to False — this is an app-side context, not the stock ipc_ept struct. */
struct __attribute__((packed)) g1_layout_ipc_ept_locked_retry_ctx__param_0060 {
    uint8_t _pad_0x0[0x4];
    uint8_t retry_count[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t ept_state[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ipc_ept_locked_retry_ctx__param_0060, retry_count) == 0x4, "g1_layout_ipc_ept_locked_retry_ctx__param_0060.retry_count");
_Static_assert(offsetof(struct g1_layout_ipc_ept_locked_retry_ctx__param_0060, ept_state) == 0x10, "g1_layout_ipc_ept_locked_retry_ctx__param_0060.ept_state");
_Static_assert(sizeof(struct g1_layout_ipc_ept_locked_retry_ctx__param_0060) >= 0x14, "g1_layout_ipc_ept_locked_retry_ctx__param_0060.size");

/* param_0061 | G1-original | Message/buffer object passed as param_1 to ipc0_ept_recv (nRF IPC service endpoint receive callback), read as consecutive words. | D1+D2 verified
 * review: SPLIT from collision group global_1358 (coincidental 7-word footprint). G1-original IPC endpoint receive payload; not the same type as the other collision members. */
struct __attribute__((packed)) g1_layout_ipc0_ept_recv_msg__param_0061 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ipc0_ept_recv_msg__param_0061, field_0x4) == 0x4, "g1_layout_ipc0_ept_recv_msg__param_0061.field_0x4");
_Static_assert(offsetof(struct g1_layout_ipc0_ept_recv_msg__param_0061, field_0x8) == 0x8, "g1_layout_ipc0_ept_recv_msg__param_0061.field_0x8");
_Static_assert(offsetof(struct g1_layout_ipc0_ept_recv_msg__param_0061, field_0xc) == 0xc, "g1_layout_ipc0_ept_recv_msg__param_0061.field_0xc");
_Static_assert(offsetof(struct g1_layout_ipc0_ept_recv_msg__param_0061, field_0x10) == 0x10, "g1_layout_ipc0_ept_recv_msg__param_0061.field_0x10");
_Static_assert(offsetof(struct g1_layout_ipc0_ept_recv_msg__param_0061, field_0x14) == 0x14, "g1_layout_ipc0_ept_recv_msg__param_0061.field_0x14");
_Static_assert(offsetof(struct g1_layout_ipc0_ept_recv_msg__param_0061, field_0x18) == 0x18, "g1_layout_ipc0_ept_recv_msg__param_0061.field_0x18");
_Static_assert(offsetof(struct g1_layout_ipc0_ept_recv_msg__param_0061, field_0x1c) == 0x1c, "g1_layout_ipc0_ept_recv_msg__param_0061.field_0x1c");
_Static_assert(sizeof(struct g1_layout_ipc0_ept_recv_msg__param_0061) >= 0x20, "g1_layout_ipc0_ept_recv_msg__param_0061.size");

/* param_0062 | G1-original | IPC service context registered by register_ipc_service_context; two trailing handle/status words written by the register call. | D1+D2 verified
 * review: G1-original wrapper context (>=0x68). Only the two written tail words are observed. */
struct __attribute__((packed)) g1_layout_ipc_service_ctx__param_0062 {
    uint8_t _pad_0x0[0x60];
    uint8_t handle0[0x4]; /* catalog type: uint32_t */
    uint8_t handle1[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ipc_service_ctx__param_0062, handle0) == 0x60, "g1_layout_ipc_service_ctx__param_0062.handle0");
_Static_assert(offsetof(struct g1_layout_ipc_service_ctx__param_0062, handle1) == 0x64, "g1_layout_ipc_service_ctx__param_0062.handle1");
_Static_assert(sizeof(struct g1_layout_ipc_service_ctx__param_0062) >= 0x68, "g1_layout_ipc_service_ctx__param_0062.size");

/* param_0063 | G1-original | IMU sensor-fusion output context registered via register_imu_funsion_context; four write-only floats (quaternion-like output). | D1+D2 verified
 * review: Refined trailing four undefined4 to float (quaternion output). */
struct __attribute__((packed)) g1_layout_imu_fusion_ctx__param_0063 {
    uint8_t _pad_0x0[0x8c];
    uint8_t quat_w[0x4]; /* catalog type: float */
    uint8_t quat_x[0x4]; /* catalog type: float */
    uint8_t quat_y[0x4]; /* catalog type: float */
    uint8_t quat_z[0x4]; /* catalog type: float */
};
_Static_assert(offsetof(struct g1_layout_imu_fusion_ctx__param_0063, quat_w) == 0x8c, "g1_layout_imu_fusion_ctx__param_0063.quat_w");
_Static_assert(offsetof(struct g1_layout_imu_fusion_ctx__param_0063, quat_x) == 0x90, "g1_layout_imu_fusion_ctx__param_0063.quat_x");
_Static_assert(offsetof(struct g1_layout_imu_fusion_ctx__param_0063, quat_y) == 0x94, "g1_layout_imu_fusion_ctx__param_0063.quat_y");
_Static_assert(offsetof(struct g1_layout_imu_fusion_ctx__param_0063, quat_z) == 0x98, "g1_layout_imu_fusion_ctx__param_0063.quat_z");
_Static_assert(sizeof(struct g1_layout_imu_fusion_ctx__param_0063) >= 0x9c, "g1_layout_imu_fusion_ctx__param_0063.size");

/* param_0064 | G1-original | SPI master transaction descriptor (spi_master_trans_data_tx_rx): transfer length and a mode/flag byte. | D1+D2 verified
 * review: Single-cid. */
struct __attribute__((packed)) g1_layout_spi_trans_desc__param_0064 {
    uint8_t _pad_0x0[0x14];
    uint8_t xfer_len[0x4]; /* catalog type: int32_t */
    uint8_t xfer_flags[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_spi_trans_desc__param_0064, xfer_len) == 0x14, "g1_layout_spi_trans_desc__param_0064.xfer_len");
_Static_assert(offsetof(struct g1_layout_spi_trans_desc__param_0064, xfer_flags) == 0x18, "g1_layout_spi_trans_desc__param_0064.xfer_flags");
_Static_assert(sizeof(struct g1_layout_spi_trans_desc__param_0064) >= 0x1c, "g1_layout_spi_trans_desc__param_0064.size");

/* param_0065 | G1-original | G1 SPI/SPIM bus configuration+state block: two output register/handle words, a mode/state word, then six pin-assignment bytes (SCK/MOSI/MISO/CS + 2 extra). Passed to spim_select_instance_by_mode (param_0065) and spi_master_init (param_0066). | D1+D2 verified
 * review: Merged param_0065+param_0066: identical footprint (2 write words at 0xc/0x10, rw mode word at 0x14, 6 pin bytes 0x18-0x1d) and both are the param_1 config passed to sibling SPI-master init routines — same struct type. Leading 0xc pad indicates this is a sub-region of a larger board/instance struct, so NOT nrfx_spim_config_t (which starts pins at 0). Kept as G1-original. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_spi_bus_config__param_0065 {
    uint8_t _pad_0x0[0xc];
    uint8_t reg_base_or_handle[0x4]; /* catalog type: uint32_t */
    uint8_t handle_or_irq[0x4]; /* catalog type: uint32_t */
    uint8_t mode[0x4]; /* catalog type: int32_t */
    uint8_t pin_sck[0x1]; /* catalog type: uint8_t */
    uint8_t pin_mosi[0x1]; /* catalog type: uint8_t */
    uint8_t pin_miso[0x1]; /* catalog type: uint8_t */
    uint8_t pin_cs[0x1]; /* catalog type: uint8_t */
    uint8_t pin_extra1[0x1]; /* catalog type: uint8_t */
    uint8_t pin_extra2[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_spi_bus_config__param_0065, reg_base_or_handle) == 0xc, "g1_layout_spi_bus_config__param_0065.reg_base_or_handle");
_Static_assert(offsetof(struct g1_layout_spi_bus_config__param_0065, handle_or_irq) == 0x10, "g1_layout_spi_bus_config__param_0065.handle_or_irq");
_Static_assert(offsetof(struct g1_layout_spi_bus_config__param_0065, mode) == 0x14, "g1_layout_spi_bus_config__param_0065.mode");
_Static_assert(offsetof(struct g1_layout_spi_bus_config__param_0065, pin_sck) == 0x18, "g1_layout_spi_bus_config__param_0065.pin_sck");
_Static_assert(offsetof(struct g1_layout_spi_bus_config__param_0065, pin_mosi) == 0x19, "g1_layout_spi_bus_config__param_0065.pin_mosi");
_Static_assert(offsetof(struct g1_layout_spi_bus_config__param_0065, pin_miso) == 0x1a, "g1_layout_spi_bus_config__param_0065.pin_miso");
_Static_assert(offsetof(struct g1_layout_spi_bus_config__param_0065, pin_cs) == 0x1b, "g1_layout_spi_bus_config__param_0065.pin_cs");
_Static_assert(offsetof(struct g1_layout_spi_bus_config__param_0065, pin_extra1) == 0x1c, "g1_layout_spi_bus_config__param_0065.pin_extra1");
_Static_assert(offsetof(struct g1_layout_spi_bus_config__param_0065, pin_extra2) == 0x1d, "g1_layout_spi_bus_config__param_0065.pin_extra2");
_Static_assert(sizeof(struct g1_layout_spi_bus_config__param_0065) >= 0x21, "g1_layout_spi_bus_config__param_0065.size");

/* param_0067 | G1-original | G1-original two-word ops/context block passed to spi_master_install_ops (SPI master driver op-table slots). | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_spi_master_ops__param_0067 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_spi_master_ops__param_0067, field_0x4) == 0x4, "g1_layout_spi_master_ops__param_0067.field_0x4");
_Static_assert(offsetof(struct g1_layout_spi_master_ops__param_0067, field_0x8) == 0x8, "g1_layout_spi_master_ops__param_0067.field_0x8");
_Static_assert(sizeof(struct g1_layout_spi_master_ops__param_0067) >= 0xc, "g1_layout_spi_master_ops__param_0067.size");

/* param_0068 | G1-original | IMU fusion calibration parameter block (bias/scale table) consumed by imu_fusion_state_init. | D1+D2 verified
 * review: Single-cid. Ground-truth notes a 4-byte access at 0x8 exceeding the 2-byte gap to 0xa, so is_union=true; kept the 0x8 field as uint32 (dominant access) plus the sub-byte at 0xa. Offsets kept. */
struct __attribute__((packed)) g1_layout_imu_fusion_calib_params__param_0068 {
    uint8_t _pad_0x0[0x4];
    uint8_t cal_0[0x4]; /* catalog type: uint32_t */
    uint8_t cal_1[0x2]; /* catalog type: uint32_t */
    uint8_t field_0xa[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xb[0x1];
    uint8_t cal_2[0x4]; /* catalog type: uint32_t */
    uint8_t cal_3[0x4]; /* catalog type: uint32_t */
    uint8_t cal_4[0x4]; /* catalog type: uint32_t */
    uint8_t cal_5[0x4]; /* catalog type: uint32_t */
    uint8_t cal_6[0x4]; /* catalog type: uint32_t */
    uint8_t cal_7[0x4]; /* catalog type: uint32_t */
    uint8_t cal_8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x28[0x10];
    uint8_t cal_9[0x4]; /* catalog type: uint32_t */
    uint8_t cal_10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_imu_fusion_calib_params__param_0068, cal_0) == 0x4, "g1_layout_imu_fusion_calib_params__param_0068.cal_0");
_Static_assert(offsetof(struct g1_layout_imu_fusion_calib_params__param_0068, cal_1) == 0x8, "g1_layout_imu_fusion_calib_params__param_0068.cal_1");
_Static_assert(offsetof(struct g1_layout_imu_fusion_calib_params__param_0068, field_0xa) == 0xa, "g1_layout_imu_fusion_calib_params__param_0068.field_0xa");
_Static_assert(offsetof(struct g1_layout_imu_fusion_calib_params__param_0068, cal_2) == 0xc, "g1_layout_imu_fusion_calib_params__param_0068.cal_2");
_Static_assert(offsetof(struct g1_layout_imu_fusion_calib_params__param_0068, cal_3) == 0x10, "g1_layout_imu_fusion_calib_params__param_0068.cal_3");
_Static_assert(offsetof(struct g1_layout_imu_fusion_calib_params__param_0068, cal_4) == 0x14, "g1_layout_imu_fusion_calib_params__param_0068.cal_4");
_Static_assert(offsetof(struct g1_layout_imu_fusion_calib_params__param_0068, cal_5) == 0x18, "g1_layout_imu_fusion_calib_params__param_0068.cal_5");
_Static_assert(offsetof(struct g1_layout_imu_fusion_calib_params__param_0068, cal_6) == 0x1c, "g1_layout_imu_fusion_calib_params__param_0068.cal_6");
_Static_assert(offsetof(struct g1_layout_imu_fusion_calib_params__param_0068, cal_7) == 0x20, "g1_layout_imu_fusion_calib_params__param_0068.cal_7");
_Static_assert(offsetof(struct g1_layout_imu_fusion_calib_params__param_0068, cal_8) == 0x24, "g1_layout_imu_fusion_calib_params__param_0068.cal_8");
_Static_assert(offsetof(struct g1_layout_imu_fusion_calib_params__param_0068, cal_9) == 0x38, "g1_layout_imu_fusion_calib_params__param_0068.cal_9");
_Static_assert(offsetof(struct g1_layout_imu_fusion_calib_params__param_0068, cal_10) == 0x3c, "g1_layout_imu_fusion_calib_params__param_0068.cal_10");
_Static_assert(sizeof(struct g1_layout_imu_fusion_calib_params__param_0068) >= 0x40, "g1_layout_imu_fusion_calib_params__param_0068.size");

/* param_0069 | G1-original | Quaternion (q0..q3) read by the Mahony AHRS filter update imu_mahony_ahrs_update. | D1+D2 verified
 * review: G1-original; four consecutive floats. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_imu_ahrs_quaternion__param_0069 {
    uint8_t _pad_0x0[0xc];
    uint8_t q0[0x4]; /* catalog type: float */
    uint8_t q1[0x4]; /* catalog type: float */
    uint8_t q2[0x4]; /* catalog type: float */
    uint8_t q3[0x4]; /* catalog type: float */
};
_Static_assert(offsetof(struct g1_layout_imu_ahrs_quaternion__param_0069, q0) == 0xc, "g1_layout_imu_ahrs_quaternion__param_0069.q0");
_Static_assert(offsetof(struct g1_layout_imu_ahrs_quaternion__param_0069, q1) == 0x10, "g1_layout_imu_ahrs_quaternion__param_0069.q1");
_Static_assert(offsetof(struct g1_layout_imu_ahrs_quaternion__param_0069, q2) == 0x14, "g1_layout_imu_ahrs_quaternion__param_0069.q2");
_Static_assert(offsetof(struct g1_layout_imu_ahrs_quaternion__param_0069, q3) == 0x18, "g1_layout_imu_ahrs_quaternion__param_0069.q3");
_Static_assert(sizeof(struct g1_layout_imu_ahrs_quaternion__param_0069) >= 0x1c, "g1_layout_imu_ahrs_quaternion__param_0069.size");

/* param_0070 | G1-original | Tail of an orientation/IMU filter state updated by orientation_filter_update_dt: tick counter and computed delta-time float. | D1+D2 verified
 * review: G1-original. Float type at 0x40 confirmed by access. */
struct __attribute__((packed)) g1_layout_orientation_filter_state__param_0070 {
    uint8_t _pad_0x0[0x38];
    uint8_t last_update_tick[0x4]; /* catalog type: uint32_t */
    uint8_t tick_delta[0x4]; /* catalog type: uint32_t */
    uint8_t dt_seconds[0x4]; /* catalog type: float */
};
_Static_assert(offsetof(struct g1_layout_orientation_filter_state__param_0070, last_update_tick) == 0x38, "g1_layout_orientation_filter_state__param_0070.last_update_tick");
_Static_assert(offsetof(struct g1_layout_orientation_filter_state__param_0070, tick_delta) == 0x3c, "g1_layout_orientation_filter_state__param_0070.tick_delta");
_Static_assert(offsetof(struct g1_layout_orientation_filter_state__param_0070, dt_seconds) == 0x40, "g1_layout_orientation_filter_state__param_0070.dt_seconds");
_Static_assert(sizeof(struct g1_layout_orientation_filter_state__param_0070) >= 0x44, "g1_layout_orientation_filter_state__param_0070.size");

/* param_0071 | G1-original | Orientation/IMU-fusion state queried by orientation_get_yaw_deg: a status byte and computed yaw float. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_orientation_state__param_0071 {
    uint8_t _pad_0x0[0x28];
    uint8_t status[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x29[0x3];
    uint8_t yaw_deg[0x4]; /* catalog type: float */
};
_Static_assert(offsetof(struct g1_layout_orientation_state__param_0071, status) == 0x28, "g1_layout_orientation_state__param_0071.status");
_Static_assert(offsetof(struct g1_layout_orientation_state__param_0071, yaw_deg) == 0x2c, "g1_layout_orientation_state__param_0071.yaw_deg");
_Static_assert(sizeof(struct g1_layout_orientation_state__param_0071) >= 0x30, "g1_layout_orientation_state__param_0071.size");

/* param_0072 | G1-original | Orientation/attitude context read by orientation_get_pitch_deg (a flag byte and a float pitch value). | D1+D2 verified
 * review: Kept offsets; 0x30 is float. */
struct __attribute__((packed)) g1_layout_orientation_state__param_0072 {
    uint8_t _pad_0x0[0x28];
    uint8_t flag_0x28[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x29[0x7];
    uint8_t pitch_deg[0x4]; /* catalog type: float */
};
_Static_assert(offsetof(struct g1_layout_orientation_state__param_0072, flag_0x28) == 0x28, "g1_layout_orientation_state__param_0072.flag_0x28");
_Static_assert(offsetof(struct g1_layout_orientation_state__param_0072, pitch_deg) == 0x30, "g1_layout_orientation_state__param_0072.pitch_deg");
_Static_assert(sizeof(struct g1_layout_orientation_state__param_0072) >= 0x34, "g1_layout_orientation_state__param_0072.size");

/* param_0073 | G1-original | Orientation/IMU state struct exposing a computed heading angle read by orientation_get_heading_deg. | D1+D2 verified
 * review: G1-original; kept sonnet layout. */
struct __attribute__((packed)) g1_layout_orientation_state__param_0073 {
    uint8_t _pad_0x0[0x28];
    uint8_t status_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x29[0xb];
    uint8_t heading_deg[0x4]; /* catalog type: float */
};
_Static_assert(offsetof(struct g1_layout_orientation_state__param_0073, status_flag) == 0x28, "g1_layout_orientation_state__param_0073.status_flag");
_Static_assert(offsetof(struct g1_layout_orientation_state__param_0073, heading_deg) == 0x34, "g1_layout_orientation_state__param_0073.heading_deg");
_Static_assert(sizeof(struct g1_layout_orientation_state__param_0073) >= 0x38, "g1_layout_orientation_state__param_0073.size");

/* param_0074 | G1-original | Large (~0xfc6) dispatch/message buffer for the low-speed peripheral dispatch test thread: status byte plus trailing write-index halfwords. | D1+D2 verified
 * review: G1-original. Status byte at 0x1, two ushort write indices near tail (0xfc0/0xfc4). */
struct __attribute__((packed)) g1_layout_peripheral_dispatch_buf__param_0074 {
    uint8_t _pad_0x0[0x1];
    uint8_t status_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0xfbe];
    uint8_t write_idx0[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xfc2[0x2];
    uint8_t write_idx1[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_peripheral_dispatch_buf__param_0074, status_byte) == 0x1, "g1_layout_peripheral_dispatch_buf__param_0074.status_byte");
_Static_assert(offsetof(struct g1_layout_peripheral_dispatch_buf__param_0074, write_idx0) == 0xfc0, "g1_layout_peripheral_dispatch_buf__param_0074.write_idx0");
_Static_assert(offsetof(struct g1_layout_peripheral_dispatch_buf__param_0074, write_idx1) == 0xfc4, "g1_layout_peripheral_dispatch_buf__param_0074.write_idx1");
_Static_assert(sizeof(struct g1_layout_peripheral_dispatch_buf__param_0074) >= 0xfc6, "g1_layout_peripheral_dispatch_buf__param_0074.size");

/* param_0075 | G1-original | Large click/touch event dispatch state block (>0x107c): flag byte + event count + tail word. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_click_event_dispatch_ctx__param_0075 {
    uint8_t _pad_0x0[0x1];
    uint8_t dispatch_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x105a];
    uint8_t event_count[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x105e[0x1a];
    uint8_t tail_field[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_click_event_dispatch_ctx__param_0075, dispatch_flag) == 0x1, "g1_layout_click_event_dispatch_ctx__param_0075.dispatch_flag");
_Static_assert(offsetof(struct g1_layout_click_event_dispatch_ctx__param_0075, event_count) == 0x105c, "g1_layout_click_event_dispatch_ctx__param_0075.event_count");
_Static_assert(offsetof(struct g1_layout_click_event_dispatch_ctx__param_0075, tail_field) == 0x1078, "g1_layout_click_event_dispatch_ctx__param_0075.tail_field");
_Static_assert(sizeof(struct g1_layout_click_event_dispatch_ctx__param_0075) >= 0x107c, "g1_layout_click_event_dispatch_ctx__param_0075.size");

/* param_0076 | G1-original | Request/response context shared by master_process_audio_fw_load_req and post_notification_cmd_response: command header (type/len) + firmware-load params + trailing status word. | D1+D2 verified
 * review: Single-cid, 3 members. */
struct __attribute__((packed)) g1_layout_audio_fw_load_notify_ctx__param_0076 {
    uint8_t _pad_0x0[0x1];
    uint8_t cmd_type[0x1]; /* catalog type: uint8_t */
    uint8_t payload_len[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: int32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x28[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x2c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x30[0x184];
    uint8_t status_or_result[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, cmd_type) == 0x1, "g1_layout_audio_fw_load_notify_ctx__param_0076.cmd_type");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, payload_len) == 0x2, "g1_layout_audio_fw_load_notify_ctx__param_0076.payload_len");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, field_0x4) == 0x4, "g1_layout_audio_fw_load_notify_ctx__param_0076.field_0x4");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, field_0x8) == 0x8, "g1_layout_audio_fw_load_notify_ctx__param_0076.field_0x8");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, field_0xc) == 0xc, "g1_layout_audio_fw_load_notify_ctx__param_0076.field_0xc");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, field_0x10) == 0x10, "g1_layout_audio_fw_load_notify_ctx__param_0076.field_0x10");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, field_0x14) == 0x14, "g1_layout_audio_fw_load_notify_ctx__param_0076.field_0x14");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, field_0x18) == 0x18, "g1_layout_audio_fw_load_notify_ctx__param_0076.field_0x18");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, field_0x1c) == 0x1c, "g1_layout_audio_fw_load_notify_ctx__param_0076.field_0x1c");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, field_0x20) == 0x20, "g1_layout_audio_fw_load_notify_ctx__param_0076.field_0x20");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, field_0x24) == 0x24, "g1_layout_audio_fw_load_notify_ctx__param_0076.field_0x24");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, field_0x28) == 0x28, "g1_layout_audio_fw_load_notify_ctx__param_0076.field_0x28");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, field_0x2c) == 0x2c, "g1_layout_audio_fw_load_notify_ctx__param_0076.field_0x2c");
_Static_assert(offsetof(struct g1_layout_audio_fw_load_notify_ctx__param_0076, status_or_result) == 0x1b4, "g1_layout_audio_fw_load_notify_ctx__param_0076.status_or_result");
_Static_assert(sizeof(struct g1_layout_audio_fw_load_notify_ctx__param_0076) >= 0x1b8, "g1_layout_audio_fw_load_notify_ctx__param_0076.size");

/* param_0077 | G1-original | G1-original large system state/context object referenced by global_system_suspend during power-suspend: a subsystem/callback pointer and a trailing status byte. | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_system_suspend_ctx__param_0077 {
    uint8_t _pad_0x0[0xb70];
    uint8_t field_0xb70[0x4]; /* catalog type: void * */
    uint8_t _pad_0xb74[0x472];
    uint8_t field_0xfe6[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_system_suspend_ctx__param_0077, field_0xb70) == 0xb70, "g1_layout_system_suspend_ctx__param_0077.field_0xb70");
_Static_assert(offsetof(struct g1_layout_system_suspend_ctx__param_0077, field_0xfe6) == 0xfe6, "g1_layout_system_suspend_ctx__param_0077.field_0xfe6");
_Static_assert(sizeof(struct g1_layout_system_suspend_ctx__param_0077) >= 0xfea, "g1_layout_system_suspend_ctx__param_0077.size");

/* param_0078 | G1-original | View of the persistent task-status region (a sub-view of the large g1_device_runtime_state) updated by update_persist_task_status_to_wait_blow_head: a status byte at 0xd5 and a pointer at 0x1054. | D1+D2 verified
 * review: Single-cid. Offsets 0xd5 and 0x1054 coincide with g1_device_runtime_state fields (field_0xd5, field_0x1054) — likely the same object viewed by one function; kept as its own record per shard scope. Offsets kept. */
struct __attribute__((packed)) g1_layout_persist_task_ctx_view__param_0078 {
    uint8_t _pad_0x0[0xd5];
    uint8_t task_status[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xd6[0xf7e];
    uint8_t ctx_ptr[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_persist_task_ctx_view__param_0078, task_status) == 0xd5, "g1_layout_persist_task_ctx_view__param_0078.task_status");
_Static_assert(offsetof(struct g1_layout_persist_task_ctx_view__param_0078, ctx_ptr) == 0x1054, "g1_layout_persist_task_ctx_view__param_0078.ctx_ptr");
_Static_assert(sizeof(struct g1_layout_persist_task_ctx_view__param_0078) >= 0x1058, "g1_layout_persist_task_ctx_view__param_0078.size");

/* param_0079 | G1-original | Small event struct with two byte flags passed to process_for_new_message_come_on. | D1+D2 verified
 * review: G1-original; offsets unchanged. */
struct __attribute__((packed)) g1_layout_new_message_evt__param_0079 {
    uint8_t _pad_0x0[0x1];
    uint8_t msg_type[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x5];
    uint8_t status_flag[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_new_message_evt__param_0079, msg_type) == 0x1, "g1_layout_new_message_evt__param_0079.msg_type");
_Static_assert(offsetof(struct g1_layout_new_message_evt__param_0079, status_flag) == 0x7, "g1_layout_new_message_evt__param_0079.status_flag");
_Static_assert(sizeof(struct g1_layout_new_message_evt__param_0079) >= 0x8, "g1_layout_new_message_evt__param_0079.size");

/* param_0080 | G1-original | Message-display record consumed by process_for_message_show (param_2). | D1+D2 verified
 * review: G1-original. 0xb is an unaligned 4-byte read (timestamp or packed ptr). */
struct __attribute__((packed)) g1_layout_msg_show_item__param_0080 {
    uint8_t _pad_0x0[0x1];
    uint8_t msg_type[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x5];
    uint8_t status_flag[0x1]; /* catalog type: uint8_t */
    uint8_t state_flag[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x9[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xa[0x1];
    uint8_t payload[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xf[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_msg_show_item__param_0080, msg_type) == 0x1, "g1_layout_msg_show_item__param_0080.msg_type");
_Static_assert(offsetof(struct g1_layout_msg_show_item__param_0080, status_flag) == 0x7, "g1_layout_msg_show_item__param_0080.status_flag");
_Static_assert(offsetof(struct g1_layout_msg_show_item__param_0080, state_flag) == 0x8, "g1_layout_msg_show_item__param_0080.state_flag");
_Static_assert(offsetof(struct g1_layout_msg_show_item__param_0080, field_0x9) == 0x9, "g1_layout_msg_show_item__param_0080.field_0x9");
_Static_assert(offsetof(struct g1_layout_msg_show_item__param_0080, payload) == 0xb, "g1_layout_msg_show_item__param_0080.payload");
_Static_assert(offsetof(struct g1_layout_msg_show_item__param_0080, field_0xf) == 0xf, "g1_layout_msg_show_item__param_0080.field_0xf");
_Static_assert(sizeof(struct g1_layout_msg_show_item__param_0080) >= 0x13, "g1_layout_msg_show_item__param_0080.size");

/* param_0084 | G1-original | Init context for the OPT3007 ambient-light sensor driver (opt3007_init_ctx_setup): config/addr word and init flags. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_opt3007_init_ctx__param_0084 {
    uint8_t _pad_0x0[0xc];
    uint8_t i2c_addr_or_cfg[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0xc];
    uint8_t init_flags[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_opt3007_init_ctx__param_0084, i2c_addr_or_cfg) == 0xc, "g1_layout_opt3007_init_ctx__param_0084.i2c_addr_or_cfg");
_Static_assert(offsetof(struct g1_layout_opt3007_init_ctx__param_0084, init_flags) == 0x1c, "g1_layout_opt3007_init_ctx__param_0084.init_flags");
_Static_assert(sizeof(struct g1_layout_opt3007_init_ctx__param_0084) >= 0x20, "g1_layout_opt3007_init_ctx__param_0084.size");

/* param_0086 | G1-original | Descriptor passed to flash_write_and_verify_blob: source pointer, length, id/flags, and destination pointer for a blob write+verify. | D1+D2 verified
 * review: Separated from global_0840 collision group (genuinely distinct object). 0xc is accessed both 2- and 4-byte wide -> union flag set. */
struct __attribute__((packed)) g1_layout_flash_blob_write_req__param_0086 {
    uint8_t _pad_0x0[0x4];
    uint8_t src_ptr[0x4]; /* catalog type: void * */
    uint8_t length[0x4]; /* catalog type: uint32_t */
    uint8_t flags_or_id[0x4]; /* catalog type: uint32_t */
    uint8_t dest_ptr[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_flash_blob_write_req__param_0086, src_ptr) == 0x4, "g1_layout_flash_blob_write_req__param_0086.src_ptr");
_Static_assert(offsetof(struct g1_layout_flash_blob_write_req__param_0086, length) == 0x8, "g1_layout_flash_blob_write_req__param_0086.length");
_Static_assert(offsetof(struct g1_layout_flash_blob_write_req__param_0086, flags_or_id) == 0xc, "g1_layout_flash_blob_write_req__param_0086.flags_or_id");
_Static_assert(offsetof(struct g1_layout_flash_blob_write_req__param_0086, dest_ptr) == 0x10, "g1_layout_flash_blob_write_req__param_0086.dest_ptr");
_Static_assert(sizeof(struct g1_layout_flash_blob_write_req__param_0086) >= 0x14, "g1_layout_flash_blob_write_req__param_0086.size");

/* param_0087 | G1-original | NFC EEPROM link configuration (base/length/offset triple) consumed by pt_nfc_eeprom_link_init. | D1+D2 verified
 * review: Kept offsets. */
struct __attribute__((packed)) g1_layout_nfc_eeprom_link_cfg__param_0087 {
    uint8_t _pad_0x0[0x4];
    uint8_t base_addr[0x4]; /* catalog type: uint32_t */
    uint8_t length[0x4]; /* catalog type: uint32_t */
    uint8_t offset[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nfc_eeprom_link_cfg__param_0087, base_addr) == 0x4, "g1_layout_nfc_eeprom_link_cfg__param_0087.base_addr");
_Static_assert(offsetof(struct g1_layout_nfc_eeprom_link_cfg__param_0087, length) == 0x8, "g1_layout_nfc_eeprom_link_cfg__param_0087.length");
_Static_assert(offsetof(struct g1_layout_nfc_eeprom_link_cfg__param_0087, offset) == 0xc, "g1_layout_nfc_eeprom_link_cfg__param_0087.offset");
_Static_assert(sizeof(struct g1_layout_nfc_eeprom_link_cfg__param_0087) >= 0x10, "g1_layout_nfc_eeprom_link_cfg__param_0087.size");

/* param_0090 | G1-original | State struct for set_brightness_lum_base: a brightness level byte and a raw luminance/base value. | D1+D2 verified
 * review: G1-original; kept sonnet layout. */
struct __attribute__((packed)) g1_layout_brightness_lum_state__param_0090 {
    uint8_t _pad_0x0[0x4];
    uint8_t lum_level[0x1]; /* catalog type: uint8_t */
    uint8_t lum_raw[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_brightness_lum_state__param_0090, lum_level) == 0x4, "g1_layout_brightness_lum_state__param_0090.lum_level");
_Static_assert(offsetof(struct g1_layout_brightness_lum_state__param_0090, lum_raw) == 0x5, "g1_layout_brightness_lum_state__param_0090.lum_raw");
_Static_assert(sizeof(struct g1_layout_brightness_lum_state__param_0090) >= 0x7, "g1_layout_brightness_lum_state__param_0090.size");

/* param_0091 | G1-original | Small record of assigned channel bytes returned by get_assign_channel_info. | D1+D2 verified
 * review: G1-original. Three consecutive channel bytes at 0x4-0x6. */
struct __attribute__((packed)) g1_layout_channel_assign_info__param_0091 {
    uint8_t _pad_0x0[0x4];
    uint8_t channel_a[0x1]; /* catalog type: uint8_t */
    uint8_t channel_b[0x1]; /* catalog type: uint8_t */
    uint8_t channel_c[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_channel_assign_info__param_0091, channel_a) == 0x4, "g1_layout_channel_assign_info__param_0091.channel_a");
_Static_assert(offsetof(struct g1_layout_channel_assign_info__param_0091, channel_b) == 0x5, "g1_layout_channel_assign_info__param_0091.channel_b");
_Static_assert(offsetof(struct g1_layout_channel_assign_info__param_0091, channel_c) == 0x6, "g1_layout_channel_assign_info__param_0091.channel_c");
_Static_assert(sizeof(struct g1_layout_channel_assign_info__param_0091) >= 0x7, "g1_layout_channel_assign_info__param_0091.size");

/* param_0092 | G1-original | Command read by set_display_brightness: brightness level + mode/flag byte. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_display_brightness_cmd__param_0092 {
    uint8_t _pad_0x0[0x4];
    uint8_t brightness[0x1]; /* catalog type: uint8_t */
    uint8_t auto_mode[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_display_brightness_cmd__param_0092, brightness) == 0x4, "g1_layout_display_brightness_cmd__param_0092.brightness");
_Static_assert(offsetof(struct g1_layout_display_brightness_cmd__param_0092, auto_mode) == 0x5, "g1_layout_display_brightness_cmd__param_0092.auto_mode");
_Static_assert(sizeof(struct g1_layout_display_brightness_cmd__param_0092) >= 0x6, "g1_layout_display_brightness_cmd__param_0092.size");

/* param_0095 | G1-original | param_2 of uart_callback: UART driver event payload carrying a type/id int and two length/count words. | D1+D2 verified
 * review: Corrected sonnet is_library=true: uart_callback is an app callback and only 3 generic words are seen; not verifiable as struct uart_event. */
struct __attribute__((packed)) g1_layout_uart_event_data__param_0095 {
    uint8_t _pad_0x0[0x4];
    uint8_t evt_field[0x4]; /* catalog type: int32_t */
    uint8_t len_or_offset[0x4]; /* catalog type: uint32_t */
    uint8_t count[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_uart_event_data__param_0095, evt_field) == 0x4, "g1_layout_uart_event_data__param_0095.evt_field");
_Static_assert(offsetof(struct g1_layout_uart_event_data__param_0095, len_or_offset) == 0x8, "g1_layout_uart_event_data__param_0095.len_or_offset");
_Static_assert(offsetof(struct g1_layout_uart_event_data__param_0095, count) == 0xc, "g1_layout_uart_event_data__param_0095.count");
_Static_assert(sizeof(struct g1_layout_uart_event_data__param_0095) >= 0x10, "g1_layout_uart_event_data__param_0095.size");

/* param_0098 | G1-original | G1-original output struct for notification-count reply bytes written by get_notification_counts_cmd_process. | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_notif_count_out__param_0098 {
    uint8_t _pad_0x0[0x1];
    uint8_t count_a[0x1]; /* catalog type: uint8_t */
    uint8_t count_b[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_notif_count_out__param_0098, count_a) == 0x1, "g1_layout_notif_count_out__param_0098.count_a");
_Static_assert(offsetof(struct g1_layout_notif_count_out__param_0098, count_b) == 0x2, "g1_layout_notif_count_out__param_0098.count_b");
_Static_assert(sizeof(struct g1_layout_notif_count_out__param_0098) >= 0x3, "g1_layout_notif_count_out__param_0098.size");

/* param_0101 | G1-original | COINCIDENTAL over-unification: this cid merges param pointers from 18 unrelated functions (cJSON/log parse, mpsc_pbuf_init, img_mgmt, smp_transport_init, bt_keys_clear, lc3 setup, rpmsg/virtqueue, k_work_init, mbedtls ctr_drbg, onoff_manager_init, ipc vrings). Not one real object — a union of several distinct real structs sharing only generic first-arg pointer flow. | D1+D2 verified
 * review: Kept as a single record because the shard delivers it as one cid, but flagged clearly as a false unification (18 heterogeneous members incl. k_work, onoff_manager, ctr_drbg, rpmsg). Do NOT treat these offsets as one coherent type; the real per-function structs (k_work, onoff_manager, mbedtls_ctr_drbg_context, etc.) should be recovered individually. Offsets preserved verbatim. */
struct __attribute__((packed)) g1_layout_param_0101_false_union__param_0101 {
    uint8_t field_0x0[0x4]; /* catalog type: int32_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: void * */
    uint8_t _pad_0x14[0x4];
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
    uint8_t cb_ptr_0x28[0x4]; /* catalog type: void * */
    uint8_t cb_ptr_0x2c[0x4]; /* catalog type: void * */
    uint8_t cb_ptr_0x30[0x4]; /* catalog type: void * */
    uint8_t cb_ptr_0x34[0x4]; /* catalog type: void * */
    uint8_t _pad_0x38[0x10];
    uint8_t field_0x48[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4c[0x20];
    uint8_t field_0x6c[0x4]; /* catalog type: void * */
    uint8_t field_0x70[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x74[0x4];
    uint8_t field_0x78[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x7c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x80[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x84[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x88[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8c[0x4]; /* catalog type: uint32_t */
    uint8_t flag_0x90[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x91[0x3];
    uint8_t field_0x94[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x98[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x9c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xa0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xa4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xa8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xac[0x4]; /* catalog type: void * */
    uint8_t field_0xb0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xb4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xb8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xbc[0x18];
    uint8_t field_0xd4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xd8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xdc[0xd4];
    uint8_t field_0x1b0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1b4[0x2ec];
    uint8_t field_0x4a0[0x4]; /* catalog type: void * */
    uint8_t field_0x4a4[0x4]; /* catalog type: void * */
    uint8_t field_0x4a8[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x0) == 0x0, "g1_layout_param_0101_false_union__param_0101.field_0x0");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x4) == 0x4, "g1_layout_param_0101_false_union__param_0101.field_0x4");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x8) == 0x8, "g1_layout_param_0101_false_union__param_0101.field_0x8");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0xc) == 0xc, "g1_layout_param_0101_false_union__param_0101.field_0xc");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x10) == 0x10, "g1_layout_param_0101_false_union__param_0101.field_0x10");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x18) == 0x18, "g1_layout_param_0101_false_union__param_0101.field_0x18");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x1c) == 0x1c, "g1_layout_param_0101_false_union__param_0101.field_0x1c");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x20) == 0x20, "g1_layout_param_0101_false_union__param_0101.field_0x20");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x24) == 0x24, "g1_layout_param_0101_false_union__param_0101.field_0x24");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, cb_ptr_0x28) == 0x28, "g1_layout_param_0101_false_union__param_0101.cb_ptr_0x28");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, cb_ptr_0x2c) == 0x2c, "g1_layout_param_0101_false_union__param_0101.cb_ptr_0x2c");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, cb_ptr_0x30) == 0x30, "g1_layout_param_0101_false_union__param_0101.cb_ptr_0x30");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, cb_ptr_0x34) == 0x34, "g1_layout_param_0101_false_union__param_0101.cb_ptr_0x34");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x48) == 0x48, "g1_layout_param_0101_false_union__param_0101.field_0x48");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x6c) == 0x6c, "g1_layout_param_0101_false_union__param_0101.field_0x6c");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x70) == 0x70, "g1_layout_param_0101_false_union__param_0101.field_0x70");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x78) == 0x78, "g1_layout_param_0101_false_union__param_0101.field_0x78");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x7c) == 0x7c, "g1_layout_param_0101_false_union__param_0101.field_0x7c");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x80) == 0x80, "g1_layout_param_0101_false_union__param_0101.field_0x80");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x84) == 0x84, "g1_layout_param_0101_false_union__param_0101.field_0x84");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x88) == 0x88, "g1_layout_param_0101_false_union__param_0101.field_0x88");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x8c) == 0x8c, "g1_layout_param_0101_false_union__param_0101.field_0x8c");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, flag_0x90) == 0x90, "g1_layout_param_0101_false_union__param_0101.flag_0x90");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x94) == 0x94, "g1_layout_param_0101_false_union__param_0101.field_0x94");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x98) == 0x98, "g1_layout_param_0101_false_union__param_0101.field_0x98");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x9c) == 0x9c, "g1_layout_param_0101_false_union__param_0101.field_0x9c");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0xa0) == 0xa0, "g1_layout_param_0101_false_union__param_0101.field_0xa0");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0xa4) == 0xa4, "g1_layout_param_0101_false_union__param_0101.field_0xa4");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0xa8) == 0xa8, "g1_layout_param_0101_false_union__param_0101.field_0xa8");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0xac) == 0xac, "g1_layout_param_0101_false_union__param_0101.field_0xac");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0xb0) == 0xb0, "g1_layout_param_0101_false_union__param_0101.field_0xb0");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0xb4) == 0xb4, "g1_layout_param_0101_false_union__param_0101.field_0xb4");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0xb8) == 0xb8, "g1_layout_param_0101_false_union__param_0101.field_0xb8");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0xd4) == 0xd4, "g1_layout_param_0101_false_union__param_0101.field_0xd4");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0xd8) == 0xd8, "g1_layout_param_0101_false_union__param_0101.field_0xd8");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x1b0) == 0x1b0, "g1_layout_param_0101_false_union__param_0101.field_0x1b0");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x4a0) == 0x4a0, "g1_layout_param_0101_false_union__param_0101.field_0x4a0");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x4a4) == 0x4a4, "g1_layout_param_0101_false_union__param_0101.field_0x4a4");
_Static_assert(offsetof(struct g1_layout_param_0101_false_union__param_0101, field_0x4a8) == 0x4a8, "g1_layout_param_0101_false_union__param_0101.field_0x4a8");
_Static_assert(sizeof(struct g1_layout_param_0101_false_union__param_0101) >= 0x4ac, "g1_layout_param_0101_false_union__param_0101.size");

/* param_0102 | G1-original | Write-only byte pair used by send_whitelist_json_chunked to track chunk-transmission state. | D1+D2 verified
 * review: G1-original; offsets unchanged. */
struct __attribute__((packed)) g1_layout_whitelist_chunk_state__param_0102 {
    uint8_t _pad_0x0[0x1];
    uint8_t chunk_flag[0x1]; /* catalog type: uint8_t */
    uint8_t terminator[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_whitelist_chunk_state__param_0102, chunk_flag) == 0x1, "g1_layout_whitelist_chunk_state__param_0102.chunk_flag");
_Static_assert(offsetof(struct g1_layout_whitelist_chunk_state__param_0102, terminator) == 0x2, "g1_layout_whitelist_chunk_state__param_0102.terminator");
_Static_assert(sizeof(struct g1_layout_whitelist_chunk_state__param_0102) >= 0x3, "g1_layout_whitelist_chunk_state__param_0102.size");

/* param_0106 | G1-original | Message-draw context passed to draw_message (param_2): a type byte and a flags byte. | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_draw_message_ctx__param_0106 {
    uint8_t _pad_0x0[0x14];
    uint8_t msg_type[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x15[0x7];
    uint8_t msg_flags[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_draw_message_ctx__param_0106, msg_type) == 0x14, "g1_layout_draw_message_ctx__param_0106.msg_type");
_Static_assert(offsetof(struct g1_layout_draw_message_ctx__param_0106, msg_flags) == 0x1c, "g1_layout_draw_message_ctx__param_0106.msg_flags");
_Static_assert(sizeof(struct g1_layout_draw_message_ctx__param_0106) >= 0x1d, "g1_layout_draw_message_ctx__param_0106.size");

/* param_0109 | G1-original | Context struct consumed by DashBoard_Reflash describing dashboard reflash state via scattered flag bytes. | D1+D2 verified
 * review: Kept naming; offsets unchanged (all byte reads). */
struct __attribute__((packed)) g1_layout_dashboard_reflash_ctx__param_0109 {
    uint8_t _pad_0x0[0x4];
    uint8_t flag_04[0x1]; /* catalog type: uint8_t */
    uint8_t flag_05[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x6[0x59];
    uint8_t flag_5f[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x60[0x4];
    uint8_t flag_64[0x1]; /* catalog type: uint8_t */
    uint8_t flag_65[0x1]; /* catalog type: uint8_t */
    uint8_t flag_66[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x67[0x1];
    uint8_t flag_68[0x1]; /* catalog type: uint8_t */
    uint8_t flag_69[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_ctx__param_0109, flag_04) == 0x4, "g1_layout_dashboard_reflash_ctx__param_0109.flag_04");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_ctx__param_0109, flag_05) == 0x5, "g1_layout_dashboard_reflash_ctx__param_0109.flag_05");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_ctx__param_0109, flag_5f) == 0x5f, "g1_layout_dashboard_reflash_ctx__param_0109.flag_5f");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_ctx__param_0109, flag_64) == 0x64, "g1_layout_dashboard_reflash_ctx__param_0109.flag_64");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_ctx__param_0109, flag_65) == 0x65, "g1_layout_dashboard_reflash_ctx__param_0109.flag_65");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_ctx__param_0109, flag_66) == 0x66, "g1_layout_dashboard_reflash_ctx__param_0109.flag_66");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_ctx__param_0109, flag_68) == 0x68, "g1_layout_dashboard_reflash_ctx__param_0109.flag_68");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_ctx__param_0109, flag_69) == 0x69, "g1_layout_dashboard_reflash_ctx__param_0109.flag_69");
_Static_assert(sizeof(struct g1_layout_dashboard_reflash_ctx__param_0109) >= 0x6a, "g1_layout_dashboard_reflash_ctx__param_0109.size");

/* param_0111 | G1-original | Navigation overview-map display context passed to navigation_overview_map_display. | D1+D2 verified
 * review: Two sparse fields on a ~0xb5 object; kept offsets. */
struct __attribute__((packed)) g1_layout_nav_overview_map_ctx__param_0111 {
    uint8_t _pad_0x0[0x1];
    uint8_t field_0x1[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0xaf];
    uint8_t field_0xb1[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nav_overview_map_ctx__param_0111, field_0x1) == 0x1, "g1_layout_nav_overview_map_ctx__param_0111.field_0x1");
_Static_assert(offsetof(struct g1_layout_nav_overview_map_ctx__param_0111, field_0xb1) == 0xb1, "g1_layout_nav_overview_map_ctx__param_0111.field_0xb1");
_Static_assert(sizeof(struct g1_layout_nav_overview_map_ctx__param_0111) >= 0xb5, "g1_layout_nav_overview_map_ctx__param_0111.size");

/* param_0112 | G1-original | View/tile state for navigation_panoramic_map_display: a coordinate pair plus a trailing packed data reference. | D1+D2 verified
 * review: G1-original; unaligned 0xb1 read suggests it trails a packed byte buffer. Kept offsets exactly. */
struct __attribute__((packed)) g1_layout_panoramic_map_view_state__param_0112 {
    uint8_t _pad_0x0[0x8];
    uint8_t pos_x[0x2]; /* catalog type: uint16_t */
    uint8_t pos_y[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xc[0xa5];
    uint8_t tile_data_ref[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_panoramic_map_view_state__param_0112, pos_x) == 0x8, "g1_layout_panoramic_map_view_state__param_0112.pos_x");
_Static_assert(offsetof(struct g1_layout_panoramic_map_view_state__param_0112, pos_y) == 0xa, "g1_layout_panoramic_map_view_state__param_0112.pos_y");
_Static_assert(offsetof(struct g1_layout_panoramic_map_view_state__param_0112, tile_data_ref) == 0xb1, "g1_layout_panoramic_map_view_state__param_0112.tile_data_ref");
_Static_assert(sizeof(struct g1_layout_panoramic_map_view_state__param_0112) >= 0xb5, "g1_layout_panoramic_map_view_state__param_0112.size");

/* param_0114 | G1-original | Large onboarding/BLE processing context (~0x1018) with a state byte and a trailing conn/handle pointer, used by onboarding_ble_process. | D1+D2 verified
 * review: G1-original. State byte at 0xcd, pointer/handle at 0x1014. */
struct __attribute__((packed)) g1_layout_onboarding_ble_ctx__param_0114 {
    uint8_t _pad_0x0[0xcd];
    uint8_t onboarding_state[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xce[0xf46];
    uint8_t conn_or_handle_ptr[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_onboarding_ble_ctx__param_0114, onboarding_state) == 0xcd, "g1_layout_onboarding_ble_ctx__param_0114.onboarding_state");
_Static_assert(offsetof(struct g1_layout_onboarding_ble_ctx__param_0114, conn_or_handle_ptr) == 0x1014, "g1_layout_onboarding_ble_ctx__param_0114.conn_or_handle_ptr");
_Static_assert(sizeof(struct g1_layout_onboarding_ble_ctx__param_0114) >= 0x1018, "g1_layout_onboarding_ble_ctx__param_0114.size");

/* param_0116 | G1-original | Display panel driver state; panel_off writes a power-control word and a status word. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_panel_drv_state__param_0116 {
    uint8_t _pad_0x0[0x35c];
    uint8_t power_ctrl[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x360[0x14];
    uint8_t panel_status[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_panel_drv_state__param_0116, power_ctrl) == 0x35c, "g1_layout_panel_drv_state__param_0116.power_ctrl");
_Static_assert(offsetof(struct g1_layout_panel_drv_state__param_0116, panel_status) == 0x374, "g1_layout_panel_drv_state__param_0116.panel_status");
_Static_assert(sizeof(struct g1_layout_panel_drv_state__param_0116) >= 0x378, "g1_layout_panel_drv_state__param_0116.size");

/* param_0117 | G1-original | Display panel driver context manipulated by panel_on when powering the LCD panel. | D1+D2 verified
 * review: Single-cid. */
struct __attribute__((packed)) g1_layout_panel_ctx__param_0117 {
    uint8_t _pad_0x0[0x35c];
    uint8_t field_0x35c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x360[0x14];
    uint8_t field_0x374[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_panel_ctx__param_0117, field_0x35c) == 0x35c, "g1_layout_panel_ctx__param_0117.field_0x35c");
_Static_assert(offsetof(struct g1_layout_panel_ctx__param_0117, field_0x374) == 0x374, "g1_layout_panel_ctx__param_0117.field_0x374");
_Static_assert(sizeof(struct g1_layout_panel_ctx__param_0117) >= 0x378, "g1_layout_panel_ctx__param_0117.size");

/* param_0118 | G1-original | G1-original display-panel init/config object for jdb_panel_init: init flag, mode byte, status word. | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_jdb_panel_cfg__param_0118 {
    uint8_t _pad_0x0[0x35c];
    uint8_t panel_init_flag[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x360[0x9];
    uint8_t panel_mode[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x36a[0xa];
    uint8_t panel_status[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_jdb_panel_cfg__param_0118, panel_init_flag) == 0x35c, "g1_layout_jdb_panel_cfg__param_0118.panel_init_flag");
_Static_assert(offsetof(struct g1_layout_jdb_panel_cfg__param_0118, panel_mode) == 0x369, "g1_layout_jdb_panel_cfg__param_0118.panel_mode");
_Static_assert(offsetof(struct g1_layout_jdb_panel_cfg__param_0118, panel_status) == 0x374, "g1_layout_jdb_panel_cfg__param_0118.panel_status");
_Static_assert(sizeof(struct g1_layout_jdb_panel_cfg__param_0118) >= 0x378, "g1_layout_jdb_panel_cfg__param_0118.size");

/* param_0119 | G1-original | Quicknote subsystem buffer-pool descriptor initialized by quicknote_buffer_pool_init: pool metadata (8 leading words) plus a large buffer region and two tail fields. | D1+D2 verified
 * review: Single-cid G1 pool descriptor. Offsets kept. */
struct __attribute__((packed)) g1_layout_quicknote_buffer_pool__param_0119 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x24[0x320];
    uint8_t field_0x344[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x348[0x8];
    uint8_t field_0x350[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_quicknote_buffer_pool__param_0119, field_0x4) == 0x4, "g1_layout_quicknote_buffer_pool__param_0119.field_0x4");
_Static_assert(offsetof(struct g1_layout_quicknote_buffer_pool__param_0119, field_0x8) == 0x8, "g1_layout_quicknote_buffer_pool__param_0119.field_0x8");
_Static_assert(offsetof(struct g1_layout_quicknote_buffer_pool__param_0119, field_0xc) == 0xc, "g1_layout_quicknote_buffer_pool__param_0119.field_0xc");
_Static_assert(offsetof(struct g1_layout_quicknote_buffer_pool__param_0119, field_0x10) == 0x10, "g1_layout_quicknote_buffer_pool__param_0119.field_0x10");
_Static_assert(offsetof(struct g1_layout_quicknote_buffer_pool__param_0119, field_0x14) == 0x14, "g1_layout_quicknote_buffer_pool__param_0119.field_0x14");
_Static_assert(offsetof(struct g1_layout_quicknote_buffer_pool__param_0119, field_0x18) == 0x18, "g1_layout_quicknote_buffer_pool__param_0119.field_0x18");
_Static_assert(offsetof(struct g1_layout_quicknote_buffer_pool__param_0119, field_0x1c) == 0x1c, "g1_layout_quicknote_buffer_pool__param_0119.field_0x1c");
_Static_assert(offsetof(struct g1_layout_quicknote_buffer_pool__param_0119, field_0x20) == 0x20, "g1_layout_quicknote_buffer_pool__param_0119.field_0x20");
_Static_assert(offsetof(struct g1_layout_quicknote_buffer_pool__param_0119, field_0x344) == 0x344, "g1_layout_quicknote_buffer_pool__param_0119.field_0x344");
_Static_assert(offsetof(struct g1_layout_quicknote_buffer_pool__param_0119, field_0x350) == 0x350, "g1_layout_quicknote_buffer_pool__param_0119.field_0x350");
_Static_assert(sizeof(struct g1_layout_quicknote_buffer_pool__param_0119) >= 0x354, "g1_layout_quicknote_buffer_pool__param_0119.size");

/* param_0121 | G1-original | UTF-8 to Unicode decode cursor/context used by utf8_to_unicode (source/dest position or length pair). | D1+D2 verified
 * review: G1-original; offsets unchanged. */
struct __attribute__((packed)) g1_layout_utf8_decode_cursor__param_0121 {
    uint8_t _pad_0x0[0x4];
    uint8_t src_pos_or_ptr[0x4]; /* catalog type: uint32_t */
    uint8_t dst_pos_or_len[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_utf8_decode_cursor__param_0121, src_pos_or_ptr) == 0x4, "g1_layout_utf8_decode_cursor__param_0121.src_pos_or_ptr");
_Static_assert(offsetof(struct g1_layout_utf8_decode_cursor__param_0121, dst_pos_or_len) == 0x8, "g1_layout_utf8_decode_cursor__param_0121.dst_pos_or_len");
_Static_assert(sizeof(struct g1_layout_utf8_decode_cursor__param_0121) >= 0xc, "g1_layout_utf8_decode_cursor__param_0121.size");

/* param_0122 | G1-original | Large thread-context struct for proxy_thread_handler (BLE proxy worker), size>=0x1060. | D1+D2 verified
 * review: G1-original. Sparse observed fields across a large context. */
struct __attribute__((packed)) g1_layout_proxy_thread_ctx__param_0122 {
    uint8_t _pad_0x0[0x1];
    uint8_t state_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x786];
    uint8_t buf_ptr[0x4]; /* catalog type: void* */
    uint8_t _pad_0x78c[0x8d0];
    uint8_t length_or_id[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_proxy_thread_ctx__param_0122, state_flag) == 0x1, "g1_layout_proxy_thread_ctx__param_0122.state_flag");
_Static_assert(offsetof(struct g1_layout_proxy_thread_ctx__param_0122, buf_ptr) == 0x788, "g1_layout_proxy_thread_ctx__param_0122.buf_ptr");
_Static_assert(offsetof(struct g1_layout_proxy_thread_ctx__param_0122, length_or_id) == 0x105c, "g1_layout_proxy_thread_ctx__param_0122.length_or_id");
_Static_assert(sizeof(struct g1_layout_proxy_thread_ctx__param_0122) >= 0x1060, "g1_layout_proxy_thread_ctx__param_0122.size");

/* param_0123 | G1-original | Large (>=0xb84) display/UI thread context shared by ui_refalsh_warp and display_thread_handler; mode/status flag bytes and a trailing buffer/queue pointer. | D1+D2 verified
 * review: Kept naming; offsets unchanged. Two functions share this object. */
struct __attribute__((packed)) g1_layout_display_thread_ctx__param_0123 {
    uint8_t _pad_0x0[0x1];
    uint8_t mode_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0xd3];
    uint8_t status_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xd6[0xaaa];
    uint8_t buffer_or_queue[0x4]; /* catalog type: void* */
};
_Static_assert(offsetof(struct g1_layout_display_thread_ctx__param_0123, mode_flag) == 0x1, "g1_layout_display_thread_ctx__param_0123.mode_flag");
_Static_assert(offsetof(struct g1_layout_display_thread_ctx__param_0123, status_flag) == 0xd5, "g1_layout_display_thread_ctx__param_0123.status_flag");
_Static_assert(offsetof(struct g1_layout_display_thread_ctx__param_0123, buffer_or_queue) == 0xb80, "g1_layout_display_thread_ctx__param_0123.buffer_or_queue");
_Static_assert(sizeof(struct g1_layout_display_thread_ctx__param_0123) >= 0xb84, "g1_layout_display_thread_ctx__param_0123.size");

/* param_0124 | G1-original | MD5 hashing context passed to md5_init: 64-bit bit-count followed by the four 32-bit chaining state words (A,B,C,D). | D1+D2 verified
 * review: Split from footprint-collision group global_1341. Observed 0x4/0x8/0xc/0x10/0x14 matches the classic RFC1321/mbedtls MD5 layout (total[2]@0x0/0x4, state[4]@0x8..0x14, buffer@0x18). md5_init is APPLICATION-class so treated as G1-original MD5 rather than a stock lib type; offsets unchanged. */
struct __attribute__((packed)) g1_layout_md5_context__param_0124 {
    uint8_t _pad_0x0[0x4];
    uint8_t total_hi[0x4]; /* catalog type: uint32_t */
    uint8_t state_a[0x4]; /* catalog type: uint32_t */
    uint8_t state_b[0x4]; /* catalog type: uint32_t */
    uint8_t state_c[0x4]; /* catalog type: uint32_t */
    uint8_t state_d[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_md5_context__param_0124, total_hi) == 0x4, "g1_layout_md5_context__param_0124.total_hi");
_Static_assert(offsetof(struct g1_layout_md5_context__param_0124, state_a) == 0x8, "g1_layout_md5_context__param_0124.state_a");
_Static_assert(offsetof(struct g1_layout_md5_context__param_0124, state_b) == 0xc, "g1_layout_md5_context__param_0124.state_b");
_Static_assert(offsetof(struct g1_layout_md5_context__param_0124, state_c) == 0x10, "g1_layout_md5_context__param_0124.state_c");
_Static_assert(offsetof(struct g1_layout_md5_context__param_0124, state_d) == 0x14, "g1_layout_md5_context__param_0124.state_d");
_Static_assert(sizeof(struct g1_layout_md5_context__param_0124) >= 0x18, "g1_layout_md5_context__param_0124.size");

/* param_0125 | library | MD5 running-digest state (A/B/C/D words) processed one 64-byte block at a time by md5_process_block. | D1+D2 verified
 * review: Generic MD5 digest words; state[0]@0x0 not observed, 0x4/0x8/0xc = state[1..3]. Exact library not pinned; verified=false. */
struct __attribute__((packed)) g1_layout_md5_digest_state__param_0125 {
    uint8_t _pad_0x0[0x4];
    uint8_t state_1[0x4]; /* catalog type: uint32_t */
    uint8_t state_2[0x4]; /* catalog type: uint32_t */
    uint8_t state_3[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_md5_digest_state__param_0125, state_1) == 0x4, "g1_layout_md5_digest_state__param_0125.state_1");
_Static_assert(offsetof(struct g1_layout_md5_digest_state__param_0125, state_2) == 0x8, "g1_layout_md5_digest_state__param_0125.state_2");
_Static_assert(offsetof(struct g1_layout_md5_digest_state__param_0125, state_3) == 0xc, "g1_layout_md5_digest_state__param_0125.state_3");
_Static_assert(sizeof(struct g1_layout_md5_digest_state__param_0125) >= 0x10, "g1_layout_md5_digest_state__param_0125.size");

/* param_0126 | G1-original | Broken-down datetime output (year/month/day/hour/minute) associated with unix_timestamp_to_datetime. | D1+D2 verified
 * review: Split from footprint-collision group global_1341 (coincidental 5-word shape). G1-original datetime breakdown; offsets unchanged. */
struct __attribute__((packed)) g1_layout_datetime_fields__param_0126 {
    uint8_t _pad_0x0[0x4];
    uint8_t year[0x4]; /* catalog type: int32_t */
    uint8_t month[0x4]; /* catalog type: int32_t */
    uint8_t day[0x4]; /* catalog type: int32_t */
    uint8_t hour[0x4]; /* catalog type: int32_t */
    uint8_t minute[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_datetime_fields__param_0126, year) == 0x4, "g1_layout_datetime_fields__param_0126.year");
_Static_assert(offsetof(struct g1_layout_datetime_fields__param_0126, month) == 0x8, "g1_layout_datetime_fields__param_0126.month");
_Static_assert(offsetof(struct g1_layout_datetime_fields__param_0126, day) == 0xc, "g1_layout_datetime_fields__param_0126.day");
_Static_assert(offsetof(struct g1_layout_datetime_fields__param_0126, hour) == 0x10, "g1_layout_datetime_fields__param_0126.hour");
_Static_assert(offsetof(struct g1_layout_datetime_fields__param_0126, minute) == 0x14, "g1_layout_datetime_fields__param_0126.minute");
_Static_assert(sizeof(struct g1_layout_datetime_fields__param_0126) >= 0x18, "g1_layout_datetime_fields__param_0126.size");

/* param_0128 | library | cbprintf/log message package descriptor: three consecutive index words describing a formatted-argument package, shared by cbprintf_package_convert, z_log_msg_runtime_create, and arm_fault_forward_handler. | D1+D2 verified
 * review: cbprintf package layout is macro/byte-encoded rather than a named header struct with fixed offsets; only 0x4/0x8/0xc observed. library_verified=false. */
struct __attribute__((packed)) g1_layout_cbprintf_package_hdr__param_0128 {
    uint8_t _pad_0x0[0x4];
    uint8_t len_or_flags[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cbprintf_package_hdr__param_0128, len_or_flags) == 0x4, "g1_layout_cbprintf_package_hdr__param_0128.len_or_flags");
_Static_assert(offsetof(struct g1_layout_cbprintf_package_hdr__param_0128, field_0x8) == 0x8, "g1_layout_cbprintf_package_hdr__param_0128.field_0x8");
_Static_assert(offsetof(struct g1_layout_cbprintf_package_hdr__param_0128, field_0xc) == 0xc, "g1_layout_cbprintf_package_hdr__param_0128.field_0xc");
_Static_assert(sizeof(struct g1_layout_cbprintf_package_hdr__param_0128) >= 0x10, "g1_layout_cbprintf_package_hdr__param_0128.size");

/* param_0129 | library | Zephyr on/off service coordinator (client/monitor slists, transitions ptr, spinlock, last_res, flags, refs); param_1 of onoff_process_event/onoff_request_enqueue/onoff_release/process_recheck. | D1+D2 verified
 * review: VERIFIED against header under a CONFIG_SPIN_VALIDATE build (k_spinlock=4B thread_cpu): clients slist@0x0, monitors slist@0x8, transitions@0x10, last_res@0x18, flags@0x1c, refs@0x1e all match. CORRECTED sonnet mis-labels (it called 0x18 flags/0x1c refs/0x1e start_err). The anomalous 2-byte read Ghidra placed at 0x7 lands inside clients.tail and is kept as an observed offset only. */
struct __attribute__((packed)) g1_layout_onoff_manager__param_0129 {
    uint8_t clients[0x4]; /* catalog type: sys_slist_t; SDK member: clients */
    uint8_t _pad_0x4[0x3];
    uint8_t _anom_0x7[0x1]; /* catalog type: uint16_t */
    uint8_t monitors[0x4]; /* catalog type: sys_slist_t; SDK member: monitors */
    uint8_t _pad_0xc[0x4];
    uint8_t transitions[0x4]; /* catalog type: const struct onoff_transitions *; SDK member: transitions */
    uint8_t _pad_0x14[0x4];
    uint8_t last_res[0x4]; /* catalog type: int; SDK member: last_res */
    uint8_t flags[0x2]; /* catalog type: uint16_t; SDK member: flags */
    uint8_t refs[0x2]; /* catalog type: uint16_t; SDK member: refs */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_onoff_manager__param_0129, clients) == 0x0, "g1_layout_onoff_manager__param_0129.clients");
_Static_assert(offsetof(struct g1_layout_onoff_manager__param_0129, _anom_0x7) == 0x7, "g1_layout_onoff_manager__param_0129._anom_0x7");
_Static_assert(offsetof(struct g1_layout_onoff_manager__param_0129, monitors) == 0x8, "g1_layout_onoff_manager__param_0129.monitors");
_Static_assert(offsetof(struct g1_layout_onoff_manager__param_0129, transitions) == 0x10, "g1_layout_onoff_manager__param_0129.transitions");
_Static_assert(offsetof(struct g1_layout_onoff_manager__param_0129, last_res) == 0x18, "g1_layout_onoff_manager__param_0129.last_res");
_Static_assert(offsetof(struct g1_layout_onoff_manager__param_0129, flags) == 0x1c, "g1_layout_onoff_manager__param_0129.flags");
_Static_assert(offsetof(struct g1_layout_onoff_manager__param_0129, refs) == 0x1e, "g1_layout_onoff_manager__param_0129.refs");
_Static_assert(sizeof(struct g1_layout_onoff_manager__param_0129) >= 0x22, "g1_layout_onoff_manager__param_0129.size");

/* param_0130 | library | Zephyr async-notify object finalized by sys_notify_finalize (embedded in a larger container here). | D1+D2 verified
 * review: Checked sys/notify.h: struct sys_notify = {union method @0x0; uint32 flags @0x4} (size 8). Observed 0x4 matches flags (sonnet mislabeled it 'method'); observed 0x8 lies BEYOND the 8-byte sys_notify, i.e. a field of the containing struct (e.g. onoff_client). Partial match, verified=false. */
struct __attribute__((packed)) g1_layout_sys_notify__param_0130 {
    uint8_t _pad_0x0[0x4];
    uint8_t flags[0x4]; /* catalog type: uint32_t; SDK member: flags */
    uint8_t container_field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_sys_notify__param_0130, flags) == 0x4, "g1_layout_sys_notify__param_0130.flags");
_Static_assert(offsetof(struct g1_layout_sys_notify__param_0130, container_field_0x8) == 0x8, "g1_layout_sys_notify__param_0130.container_field_0x8");
_Static_assert(sizeof(struct g1_layout_sys_notify__param_0130) >= 0xc, "g1_layout_sys_notify__param_0130.size");

/* param_0131 | G1-original | param_3 of encode_uint: zcbor/CBOR encoder cursor with current payload pointer and payload-end pointer. | D1+D2 verified
 * review: Resembles zcbor_state_t head; only two pointers observed, unverified. */
struct __attribute__((packed)) g1_layout_zcbor_encode_cursor__param_0131 {
    uint8_t _pad_0x0[0x8];
    uint8_t payload[0x4]; /* catalog type: uint8_t * */
    uint8_t payload_end[0x4]; /* catalog type: uint8_t * */
};
_Static_assert(offsetof(struct g1_layout_zcbor_encode_cursor__param_0131, payload) == 0x8, "g1_layout_zcbor_encode_cursor__param_0131.payload");
_Static_assert(offsetof(struct g1_layout_zcbor_encode_cursor__param_0131, payload_end) == 0xc, "g1_layout_zcbor_encode_cursor__param_0131.payload_end");
_Static_assert(sizeof(struct g1_layout_zcbor_encode_cursor__param_0131) >= 0x10, "g1_layout_zcbor_encode_cursor__param_0131.size");

/* param_0132 | library | param_2 of mpsc_pbuf_init - Zephyr multi-producer/single-consumer packet buffer instance (buffer ptr/size + wr/rd index bookkeeping). | D1+D2 verified
 * review: Separated from global_0840 collision group. Named for the mpsc_pbuf_init call site, but only a generic 4-word footprint is observed; real mpsc_pbuf_buffer is much larger so offsets could not be verified against the header. */
struct __attribute__((packed)) g1_layout_mpsc_pbuf_buffer__param_0132 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0132, field_0x4) == 0x4, "g1_layout_mpsc_pbuf_buffer__param_0132.field_0x4");
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0132, field_0x8) == 0x8, "g1_layout_mpsc_pbuf_buffer__param_0132.field_0x8");
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0132, field_0xc) == 0xc, "g1_layout_mpsc_pbuf_buffer__param_0132.field_0xc");
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0132, field_0x10) == 0x10, "g1_layout_mpsc_pbuf_buffer__param_0132.field_0x10");
_Static_assert(sizeof(struct g1_layout_mpsc_pbuf_buffer__param_0132) >= 0x14, "g1_layout_mpsc_pbuf_buffer__param_0132.size");

/* param_0133 | library | Zephyr multi-producer single-consumer packet buffer (logging backend) manipulated by mpsc_pbuf_commit / idx_inc / rd_idx_inc / add_skip_item / drop_item_locked / post_drop_action / max_utilization_update. | D1+D2 verified
 * review: VERIFIED against mpsc_pbuf.h. Offsets line up exactly when k_spinlock lock is empty (no CONFIG_SPIN_VALIDATE): tmp_wr_idx@0,wr_idx@4,tmp_rd_idx@8,rd_idx@c,flags@10, lock@14(0B), notify_drop@14, get_wlen@18, buf@1c, size@20, max_usage@24, sem@28. CORRECTED sonnet: field@0x0 is tmp_wr_idx (not a notify_drop code ptr), and field@0x28 is the k_sem (not 'utilization'). */
struct __attribute__((packed)) g1_layout_mpsc_pbuf_buffer__param_0133 {
    uint8_t tmp_wr_idx[0x4]; /* catalog type: uint32_t; SDK member: tmp_wr_idx */
    uint8_t wr_idx[0x4]; /* catalog type: uint32_t; SDK member: wr_idx */
    uint8_t tmp_rd_idx[0x4]; /* catalog type: uint32_t; SDK member: tmp_rd_idx */
    uint8_t rd_idx[0x4]; /* catalog type: uint32_t; SDK member: rd_idx */
    uint8_t flags[0x4]; /* catalog type: uint32_t; SDK member: flags */
    uint8_t _pad_0x14[0x8];
    uint8_t buf[0x4]; /* catalog type: uint32_t *; SDK member: buf */
    uint8_t size[0x4]; /* catalog type: uint32_t; SDK member: size */
    uint8_t max_usage[0x4]; /* catalog type: uint32_t; SDK member: max_usage */
    uint8_t sem[0x4]; /* catalog type: uint32_t; SDK member: sem */
};
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0133, tmp_wr_idx) == 0x0, "g1_layout_mpsc_pbuf_buffer__param_0133.tmp_wr_idx");
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0133, wr_idx) == 0x4, "g1_layout_mpsc_pbuf_buffer__param_0133.wr_idx");
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0133, tmp_rd_idx) == 0x8, "g1_layout_mpsc_pbuf_buffer__param_0133.tmp_rd_idx");
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0133, rd_idx) == 0xc, "g1_layout_mpsc_pbuf_buffer__param_0133.rd_idx");
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0133, flags) == 0x10, "g1_layout_mpsc_pbuf_buffer__param_0133.flags");
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0133, buf) == 0x1c, "g1_layout_mpsc_pbuf_buffer__param_0133.buf");
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0133, size) == 0x20, "g1_layout_mpsc_pbuf_buffer__param_0133.size");
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0133, max_usage) == 0x24, "g1_layout_mpsc_pbuf_buffer__param_0133.max_usage");
_Static_assert(offsetof(struct g1_layout_mpsc_pbuf_buffer__param_0133, sem) == 0x28, "g1_layout_mpsc_pbuf_buffer__param_0133.sem");
_Static_assert(sizeof(struct g1_layout_mpsc_pbuf_buffer__param_0133) >= 0x2c, "g1_layout_mpsc_pbuf_buffer__param_0133.size");

/* param_0135 | library | Zephyr NVS filesystem context, param_1 across nvs_mount/nvs_write/nvs_read_hist/sector-advance/gc-done routines: offset, ATE/data write addresses, sector size/count, ready flag, mutex, flash device/parameters. | D1+D2 verified
 * review: Verified against nvs.h: offset(off_t)@0x0, ate_wra(uint32)@0x4, data_wra(uint32)@0x8, sector_size(uint16)@0xc, sector_count(uint16)@0xe, ready(bool)@0x10, k_mutex nvs_lock@0x14 (0x14 bytes), flash_device@0x28, flash_parameters@0x2c. Corrected sonnet: ate_wra is uint32 (not uint16); 0x28 is flash_device and 0x2c is flash_parameters (sonnet had them swapped). is_union=true reflects Ghidra's sub-word split reads of the 4-byte offset/sector fields (0x0,0xc overlaps). Offsets match exactly. */
struct __attribute__((packed)) g1_layout_nvs_fs__param_0135 {
    uint8_t offset[0x4]; /* catalog type: off_t; SDK member: offset */
    uint8_t ate_wra[0x4]; /* catalog type: uint32_t; SDK member: ate_wra */
    uint8_t data_wra[0x4]; /* catalog type: uint32_t; SDK member: data_wra */
    uint8_t sector_size[0x2]; /* catalog type: uint16_t; SDK member: sector_size */
    uint8_t sector_count[0x2]; /* catalog type: uint16_t; SDK member: sector_count */
    uint8_t ready[0x1]; /* catalog type: uint8_t; SDK member: ready */
    uint8_t _pad_0x11[0x17];
    uint8_t flash_device[0x4]; /* catalog type: const struct device *; SDK member: flash_device */
    uint8_t flash_parameters[0x4]; /* catalog type: const struct flash_parameters *; SDK member: flash_parameters */
};
_Static_assert(offsetof(struct g1_layout_nvs_fs__param_0135, offset) == 0x0, "g1_layout_nvs_fs__param_0135.offset");
_Static_assert(offsetof(struct g1_layout_nvs_fs__param_0135, ate_wra) == 0x4, "g1_layout_nvs_fs__param_0135.ate_wra");
_Static_assert(offsetof(struct g1_layout_nvs_fs__param_0135, data_wra) == 0x8, "g1_layout_nvs_fs__param_0135.data_wra");
_Static_assert(offsetof(struct g1_layout_nvs_fs__param_0135, sector_size) == 0xc, "g1_layout_nvs_fs__param_0135.sector_size");
_Static_assert(offsetof(struct g1_layout_nvs_fs__param_0135, sector_count) == 0xe, "g1_layout_nvs_fs__param_0135.sector_count");
_Static_assert(offsetof(struct g1_layout_nvs_fs__param_0135, ready) == 0x10, "g1_layout_nvs_fs__param_0135.ready");
_Static_assert(offsetof(struct g1_layout_nvs_fs__param_0135, flash_device) == 0x28, "g1_layout_nvs_fs__param_0135.flash_device");
_Static_assert(offsetof(struct g1_layout_nvs_fs__param_0135, flash_parameters) == 0x2c, "g1_layout_nvs_fs__param_0135.flash_parameters");
_Static_assert(sizeof(struct g1_layout_nvs_fs__param_0135) >= 0x30, "g1_layout_nvs_fs__param_0135.size");

/* param_0139 | G1-original | G1-original object with a pointer plus a dword near the end of a 0x1b0-byte structure, used by FUN_0004cce0. | D1+D2 verified
 * review: Low naming signal; offsets unchanged. */
struct __attribute__((packed)) g1_layout_unk_ctx_0139__param_0139 {
    uint8_t _pad_0x0[0x1a8];
    uint8_t field_0x1a8[0x4]; /* catalog type: void * */
    uint8_t field_0x1ac[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_unk_ctx_0139__param_0139, field_0x1a8) == 0x1a8, "g1_layout_unk_ctx_0139__param_0139.field_0x1a8");
_Static_assert(offsetof(struct g1_layout_unk_ctx_0139__param_0139, field_0x1ac) == 0x1ac, "g1_layout_unk_ctx_0139__param_0139.field_0x1ac");
_Static_assert(sizeof(struct g1_layout_unk_ctx_0139__param_0139) >= 0x1b0, "g1_layout_unk_ctx_0139__param_0139.size");

/* param_0140 | library | OpenAMP rpmsg_endpoint (embedded in a larger wrapper), shared across rpmsg_create_ept/register_endpoint/send_offchannel_raw/ept_cb. | D1+D2 verified
 * review: Corrected sonnet's addr/dest_addr shift. With RPMSG_NAME_SIZE=32, real offsets are rdev@0x20, addr@0x24, dest_addr@0x28, cb@0x2c, ns_unbind_cb@0x30, node(metal_list)@0x34-0x3b, priv@0x3c — all match observed. Fields at 0x64/0x68/0x6c lie beyond the 0x40-byte rpmsg_endpoint, so this object is a Zephyr ipc-service wrapper embedding rpmsg_endpoint plus a bound flag; those trailing fields are the container's. */
struct __attribute__((packed)) g1_layout_rpmsg_endpoint__param_0140 {
    uint8_t _pad_0x0[0x20];
    uint8_t rdev[0x4]; /* catalog type: struct rpmsg_device*; SDK member: rdev */
    uint8_t addr[0x4]; /* catalog type: uint32_t; SDK member: addr */
    uint8_t dest_addr[0x4]; /* catalog type: uint32_t; SDK member: dest_addr */
    uint8_t cb[0x4]; /* catalog type: rpmsg_ept_cb; SDK member: cb */
    uint8_t ns_unbind_cb[0x4]; /* catalog type: rpmsg_ns_unbind_cb; SDK member: ns_unbind_cb */
    uint8_t node_next[0x4]; /* catalog type: void*; SDK member: node.next */
    uint8_t node_prev[0x4]; /* catalog type: void*; SDK member: node.prev */
    uint8_t _pad_0x3c[0x28];
    uint8_t bound[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x65[0x3];
    uint8_t container_ptr[0x4]; /* catalog type: void* */
    uint8_t container_word[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_rpmsg_endpoint__param_0140, rdev) == 0x20, "g1_layout_rpmsg_endpoint__param_0140.rdev");
_Static_assert(offsetof(struct g1_layout_rpmsg_endpoint__param_0140, addr) == 0x24, "g1_layout_rpmsg_endpoint__param_0140.addr");
_Static_assert(offsetof(struct g1_layout_rpmsg_endpoint__param_0140, dest_addr) == 0x28, "g1_layout_rpmsg_endpoint__param_0140.dest_addr");
_Static_assert(offsetof(struct g1_layout_rpmsg_endpoint__param_0140, cb) == 0x2c, "g1_layout_rpmsg_endpoint__param_0140.cb");
_Static_assert(offsetof(struct g1_layout_rpmsg_endpoint__param_0140, ns_unbind_cb) == 0x30, "g1_layout_rpmsg_endpoint__param_0140.ns_unbind_cb");
_Static_assert(offsetof(struct g1_layout_rpmsg_endpoint__param_0140, node_next) == 0x34, "g1_layout_rpmsg_endpoint__param_0140.node_next");
_Static_assert(offsetof(struct g1_layout_rpmsg_endpoint__param_0140, node_prev) == 0x38, "g1_layout_rpmsg_endpoint__param_0140.node_prev");
_Static_assert(offsetof(struct g1_layout_rpmsg_endpoint__param_0140, bound) == 0x64, "g1_layout_rpmsg_endpoint__param_0140.bound");
_Static_assert(offsetof(struct g1_layout_rpmsg_endpoint__param_0140, container_ptr) == 0x68, "g1_layout_rpmsg_endpoint__param_0140.container_ptr");
_Static_assert(offsetof(struct g1_layout_rpmsg_endpoint__param_0140, container_word) == 0x6c, "g1_layout_rpmsg_endpoint__param_0140.container_word");
_Static_assert(sizeof(struct g1_layout_rpmsg_endpoint__param_0140) >= 0x70, "g1_layout_rpmsg_endpoint__param_0140.size");

/* param_0141 | G1-original | RPMsg IPC backend registration context (ipc_rpmsg_backend_register): endpoint pointer plus a config/flags word. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_ipc_rpmsg_backend_ctx__param_0141 {
    uint8_t _pad_0x0[0x4];
    uint8_t ept_ptr[0x4]; /* catalog type: void* */
    uint8_t _pad_0x8[0x8];
    uint8_t backend_flags[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ipc_rpmsg_backend_ctx__param_0141, ept_ptr) == 0x4, "g1_layout_ipc_rpmsg_backend_ctx__param_0141.ept_ptr");
_Static_assert(offsetof(struct g1_layout_ipc_rpmsg_backend_ctx__param_0141, backend_flags) == 0x10, "g1_layout_ipc_rpmsg_backend_ctx__param_0141.backend_flags");
_Static_assert(sizeof(struct g1_layout_ipc_rpmsg_backend_ctx__param_0141) >= 0x14, "g1_layout_ipc_rpmsg_backend_ctx__param_0141.size");

/* param_0145 | library | Zephyr ipc_service static_vrings backend instance initialized by ipc_static_vrings_init (vring descriptors, shared-memory addresses, virtqueue/rpmsg config). | D1+D2 verified
 * review: Strong name match (function + [LIBRARY] tag). 25 sparse fields could not be mapped one-by-one to the header within scope; verified=false. All offsets kept as ground truth. */
struct __attribute__((packed)) g1_layout_ipc_static_vrings__param_0145 {
    uint8_t _pad_0x0[0x18];
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1c[0x4];
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x24[0x4];
    uint8_t field_0x28[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x2c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x30[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x34[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x38[0x4];
    uint8_t field_0x3c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x40[0x4c];
    uint8_t field_0x8c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x90[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x94[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x98[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x9c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xa0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xa4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xa8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xac[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xb0[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xb2[0x6];
    uint8_t field_0xb8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xbc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc8[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xca[0x6];
    uint8_t field_0xd0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xd4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xd8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0x18) == 0x18, "g1_layout_ipc_static_vrings__param_0145.field_0x18");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0x20) == 0x20, "g1_layout_ipc_static_vrings__param_0145.field_0x20");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0x28) == 0x28, "g1_layout_ipc_static_vrings__param_0145.field_0x28");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0x2c) == 0x2c, "g1_layout_ipc_static_vrings__param_0145.field_0x2c");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0x30) == 0x30, "g1_layout_ipc_static_vrings__param_0145.field_0x30");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0x34) == 0x34, "g1_layout_ipc_static_vrings__param_0145.field_0x34");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0x3c) == 0x3c, "g1_layout_ipc_static_vrings__param_0145.field_0x3c");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0x8c) == 0x8c, "g1_layout_ipc_static_vrings__param_0145.field_0x8c");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0x90) == 0x90, "g1_layout_ipc_static_vrings__param_0145.field_0x90");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0x94) == 0x94, "g1_layout_ipc_static_vrings__param_0145.field_0x94");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0x98) == 0x98, "g1_layout_ipc_static_vrings__param_0145.field_0x98");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0x9c) == 0x9c, "g1_layout_ipc_static_vrings__param_0145.field_0x9c");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xa0) == 0xa0, "g1_layout_ipc_static_vrings__param_0145.field_0xa0");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xa4) == 0xa4, "g1_layout_ipc_static_vrings__param_0145.field_0xa4");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xa8) == 0xa8, "g1_layout_ipc_static_vrings__param_0145.field_0xa8");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xac) == 0xac, "g1_layout_ipc_static_vrings__param_0145.field_0xac");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xb0) == 0xb0, "g1_layout_ipc_static_vrings__param_0145.field_0xb0");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xb8) == 0xb8, "g1_layout_ipc_static_vrings__param_0145.field_0xb8");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xbc) == 0xbc, "g1_layout_ipc_static_vrings__param_0145.field_0xbc");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xc0) == 0xc0, "g1_layout_ipc_static_vrings__param_0145.field_0xc0");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xc4) == 0xc4, "g1_layout_ipc_static_vrings__param_0145.field_0xc4");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xc8) == 0xc8, "g1_layout_ipc_static_vrings__param_0145.field_0xc8");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xd0) == 0xd0, "g1_layout_ipc_static_vrings__param_0145.field_0xd0");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xd4) == 0xd4, "g1_layout_ipc_static_vrings__param_0145.field_0xd4");
_Static_assert(offsetof(struct g1_layout_ipc_static_vrings__param_0145, field_0xd8) == 0xd8, "g1_layout_ipc_static_vrings__param_0145.field_0xd8");
_Static_assert(sizeof(struct g1_layout_ipc_static_vrings__param_0145) >= 0xdc, "g1_layout_ipc_static_vrings__param_0145.size");

/* param_0148 | library | Zephyr logging message header/descriptor read by log_output_msg_process while formatting a log message (packed source-id/level/length header word plus following data word). | D1+D2 verified
 * review: log_msg header is a bitfield union in log_msg.h; observed accesses of width 4 over the 0x0/0x2 fields confirm overlapping bitfield reads (is_union=true). Exact bitfield offsets not byte-checkable, library_verified=false. */
struct __attribute__((packed)) g1_layout_log_msg_hdr__param_0148 {
    uint8_t hdr_word[0x2]; /* catalog type: uint32_t */
    uint8_t hdr_hi[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_log_msg_hdr__param_0148, hdr_word) == 0x0, "g1_layout_log_msg_hdr__param_0148.hdr_word");
_Static_assert(offsetof(struct g1_layout_log_msg_hdr__param_0148, hdr_hi) == 0x2, "g1_layout_log_msg_hdr__param_0148.hdr_hi");
_Static_assert(offsetof(struct g1_layout_log_msg_hdr__param_0148, field_0x4) == 0x4, "g1_layout_log_msg_hdr__param_0148.field_0x4");
_Static_assert(sizeof(struct g1_layout_log_msg_hdr__param_0148) >= 0x8, "g1_layout_log_msg_hdr__param_0148.size");

/* param_0150 | library | Zephyr DFU stream_flash streaming write context; param_1 of stream_flash_erase_page/flush_buffer/buffered_write. | D1+D2 verified
 * review: Split out of the sonnet footprint-collision group (param_0321/stack_0756 are unrelated). VERIFIED against header: 9 consecutive words match exactly under a CONFIG_STREAM_FLASH_ERASE build. Corrected sonnet mis-mappings (it had fa at 0x10 and callback at 0x18; real is fdev at 0xc, callback at 0x1c). */
struct __attribute__((packed)) g1_layout_stream_flash_ctx__param_0150 {
    uint8_t buf[0x4]; /* catalog type: uint8_t *; SDK member: buf */
    uint8_t buf_len[0x4]; /* catalog type: size_t; SDK member: buf_len */
    uint8_t buf_bytes[0x4]; /* catalog type: size_t; SDK member: buf_bytes */
    uint8_t fdev[0x4]; /* catalog type: const struct device *; SDK member: fdev */
    uint8_t bytes_written[0x4]; /* catalog type: size_t; SDK member: bytes_written */
    uint8_t offset[0x4]; /* catalog type: size_t; SDK member: offset */
    uint8_t available[0x4]; /* catalog type: size_t; SDK member: available */
    uint8_t callback[0x4]; /* catalog type: stream_flash_callback_t; SDK member: callback */
    uint8_t last_erased_page_start_offset[0x4]; /* catalog type: off_t; SDK member: last_erased_page_start_offset */
};
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0150, buf) == 0x0, "g1_layout_stream_flash_ctx__param_0150.buf");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0150, buf_len) == 0x4, "g1_layout_stream_flash_ctx__param_0150.buf_len");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0150, buf_bytes) == 0x8, "g1_layout_stream_flash_ctx__param_0150.buf_bytes");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0150, fdev) == 0xc, "g1_layout_stream_flash_ctx__param_0150.fdev");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0150, bytes_written) == 0x10, "g1_layout_stream_flash_ctx__param_0150.bytes_written");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0150, offset) == 0x14, "g1_layout_stream_flash_ctx__param_0150.offset");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0150, available) == 0x18, "g1_layout_stream_flash_ctx__param_0150.available");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0150, callback) == 0x1c, "g1_layout_stream_flash_ctx__param_0150.callback");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0150, last_erased_page_start_offset) == 0x20, "g1_layout_stream_flash_ctx__param_0150.last_erased_page_start_offset");
_Static_assert(sizeof(struct g1_layout_stream_flash_ctx__param_0150) >= 0x24, "g1_layout_stream_flash_ctx__param_0150.size");

/* param_0151 | library | Zephyr stream-flash (DFU streaming write) context; param_1 of stream_flash_init. Holds write buffer/length, flash device, bytes-written/offset/available metadata. | D1+D2 verified
 * review: Split from footprint-collision group global_0965. Verified against stream_flash.h: buf@0x0(pad), buf_len@0x4, buf_bytes@0x8, fdev@0xc, bytes_written@0x10, offset@0x14, available@0x18, callback@0x1c, last_erased_page_start_offset@0x20 — all observed read offsets line up exactly. */
struct __attribute__((packed)) g1_layout_stream_flash_ctx__param_0151 {
    uint8_t _pad_0x0[0x4];
    uint8_t buf_len[0x4]; /* catalog type: size_t; SDK member: buf_len */
    uint8_t buf_bytes[0x4]; /* catalog type: size_t; SDK member: buf_bytes */
    uint8_t fdev[0x4]; /* catalog type: const struct device *; SDK member: fdev */
    uint8_t bytes_written[0x4]; /* catalog type: size_t; SDK member: bytes_written */
    uint8_t offset[0x4]; /* catalog type: size_t; SDK member: offset */
    uint8_t available[0x4]; /* catalog type: size_t; SDK member: available */
    uint8_t callback[0x4]; /* catalog type: stream_flash_callback_t; SDK member: callback */
    uint8_t last_erased_page_start_offset[0x4]; /* catalog type: off_t; SDK member: last_erased_page_start_offset */
};
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0151, buf_len) == 0x4, "g1_layout_stream_flash_ctx__param_0151.buf_len");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0151, buf_bytes) == 0x8, "g1_layout_stream_flash_ctx__param_0151.buf_bytes");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0151, fdev) == 0xc, "g1_layout_stream_flash_ctx__param_0151.fdev");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0151, bytes_written) == 0x10, "g1_layout_stream_flash_ctx__param_0151.bytes_written");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0151, offset) == 0x14, "g1_layout_stream_flash_ctx__param_0151.offset");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0151, available) == 0x18, "g1_layout_stream_flash_ctx__param_0151.available");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0151, callback) == 0x1c, "g1_layout_stream_flash_ctx__param_0151.callback");
_Static_assert(offsetof(struct g1_layout_stream_flash_ctx__param_0151, last_erased_page_start_offset) == 0x20, "g1_layout_stream_flash_ctx__param_0151.last_erased_page_start_offset");
_Static_assert(sizeof(struct g1_layout_stream_flash_ctx__param_0151) >= 0x24, "g1_layout_stream_flash_ctx__param_0151.size");

/* param_0153 | library | Callback/context argument (param_5) passed into settings_call_set_handler: a read_cb function pointer plus cb-arg/length words. | D1+D2 verified
 * review: Settings subsystem; the exact aggregate for the h_set arg pack is not a single named public struct, so left unverified. field_0x0 is a code-typed (function) pointer. */
struct __attribute__((packed)) g1_layout_settings_set_handler_args__param_0153 {
    uint8_t read_cb[0x4]; /* catalog type: void * */
    uint8_t cb_arg[0x4]; /* catalog type: uint32_t */
    uint8_t len[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_settings_set_handler_args__param_0153, read_cb) == 0x0, "g1_layout_settings_set_handler_args__param_0153.read_cb");
_Static_assert(offsetof(struct g1_layout_settings_set_handler_args__param_0153, cb_arg) == 0x4, "g1_layout_settings_set_handler_args__param_0153.cb_arg");
_Static_assert(offsetof(struct g1_layout_settings_set_handler_args__param_0153, len) == 0x8, "g1_layout_settings_set_handler_args__param_0153.len");
_Static_assert(sizeof(struct g1_layout_settings_set_handler_args__param_0153) >= 0xc, "g1_layout_settings_set_handler_args__param_0153.size");

/* param_0155 | library | GATT discovery-manager attribute-add context (bt_gatt_dm) used by gatt_dm_data_add_attribute / discovery_callback. | D1+D2 verified
 * review: gatt_dm internal struct is in nrf gatt_dm.c, not a public header; 0x4/0xc/0x12 unverifiable. verified=false. */
struct __attribute__((packed)) g1_layout_bt_gatt_dm_attr_ctx__param_0155 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x6[0x6];
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x2];
    uint8_t field_0x12[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_dm_attr_ctx__param_0155, field_0x4) == 0x4, "g1_layout_bt_gatt_dm_attr_ctx__param_0155.field_0x4");
_Static_assert(offsetof(struct g1_layout_bt_gatt_dm_attr_ctx__param_0155, field_0xc) == 0xc, "g1_layout_bt_gatt_dm_attr_ctx__param_0155.field_0xc");
_Static_assert(offsetof(struct g1_layout_bt_gatt_dm_attr_ctx__param_0155, field_0x12) == 0x12, "g1_layout_bt_gatt_dm_attr_ctx__param_0155.field_0x12");
_Static_assert(sizeof(struct g1_layout_bt_gatt_dm_attr_ctx__param_0155) >= 0x16, "g1_layout_bt_gatt_dm_attr_ctx__param_0155.size");

/* param_0157 | G1-original | ANCS (Apple Notification Center Service) GATT client context shared by ancs_gatt_dm_assign_handles / ancs_subscribe_notification_source / ancs_subscribe_data_source: GATT handle shorts plus subscribe-param blocks. | D1+D2 verified
 * review: 3 members. Multiple 2-over-1 and 4-over-2 overlaps -> union. Corrected sonnet is_library=true: this is the G1 ANCS client instance, not verifiable against a stock header at these offsets. */
struct __attribute__((packed)) g1_layout_ancs_notif_ctx__param_0157 {
    uint8_t _pad_0x0[0x2];
    uint8_t field_0x2[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x1fd];
    uint8_t field_0x20d[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x20f[0x6];
    uint8_t field_0x215[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x217[0x611];
    uint8_t field_0x828[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x82c[0xa];
    uint8_t field_0x836[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x838[0x4];
    uint8_t field_0x83c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x840[0x4];
    uint8_t field_0x844[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x848[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x84c[0xa];
    uint8_t field_0x856[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x858[0x4];
    uint8_t field_0x85c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x860[0x4];
    uint8_t field_0x864[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x2) == 0x2, "g1_layout_ancs_notif_ctx__param_0157.field_0x2");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x4) == 0x4, "g1_layout_ancs_notif_ctx__param_0157.field_0x4");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x8) == 0x8, "g1_layout_ancs_notif_ctx__param_0157.field_0x8");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0xc) == 0xc, "g1_layout_ancs_notif_ctx__param_0157.field_0xc");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x20d) == 0x20d, "g1_layout_ancs_notif_ctx__param_0157.field_0x20d");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x215) == 0x215, "g1_layout_ancs_notif_ctx__param_0157.field_0x215");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x828) == 0x828, "g1_layout_ancs_notif_ctx__param_0157.field_0x828");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x836) == 0x836, "g1_layout_ancs_notif_ctx__param_0157.field_0x836");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x83c) == 0x83c, "g1_layout_ancs_notif_ctx__param_0157.field_0x83c");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x844) == 0x844, "g1_layout_ancs_notif_ctx__param_0157.field_0x844");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x848) == 0x848, "g1_layout_ancs_notif_ctx__param_0157.field_0x848");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x856) == 0x856, "g1_layout_ancs_notif_ctx__param_0157.field_0x856");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x85c) == 0x85c, "g1_layout_ancs_notif_ctx__param_0157.field_0x85c");
_Static_assert(offsetof(struct g1_layout_ancs_notif_ctx__param_0157, field_0x864) == 0x864, "g1_layout_ancs_notif_ctx__param_0157.field_0x864");
_Static_assert(sizeof(struct g1_layout_ancs_notif_ctx__param_0157) >= 0x868, "g1_layout_ancs_notif_ctx__param_0157.size");

/* param_0158 | G1-original | G1-original Apple Notification Center Service (ANCS) client context: handle/attribute bookkeeping fields, a large (~0x8bb-byte) attribute-data buffer, and discovery/state trailer fields; used by bt_ancs_cp_write / bt_ancs_request_attrs / bt_ancs_app_attr_request. | D1+D2 verified
 * review: G1-original ANCS client (0/3 members library-class despite bt prefix). is_union=true: width-4 read at 0x4 overlaps the 2-byte field. Likely the SAME type as param_0539 (bt_ancs_register_app_attr), which touches the same 0x8e8 region. */
struct __attribute__((packed)) g1_layout_bt_ancs_client_ctx__param_0158 {
    uint8_t _pad_0x0[0x2];
    uint8_t field_0x2[0x2]; /* catalog type: uint16_t */
    uint8_t state_flags[0x2]; /* catalog type: uint32_t */
    uint8_t field_0x6[0x2]; /* catalog type: uint16_t */
    uint8_t ccc_handle[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xa[0xa];
    uint8_t attr_id[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x2];
    uint8_t attr_len[0x2]; /* catalog type: uint16_t */
    uint8_t attr_flags[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x20[0x4];
    uint8_t notif_uid[0x4]; /* catalog type: uint32_t */
    uint8_t category_id[0x1]; /* catalog type: uint8_t */
    uint8_t category_count[0x1]; /* catalog type: uint8_t */
    uint8_t event_id[0x1]; /* catalog type: uint8_t */
    uint8_t event_flags[0x1]; /* catalog type: uint8_t */
    uint8_t client_state[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2d[0x8bb];
    uint8_t attr_buf_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x8e9[0xf];
    uint8_t attr_buf_len[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8fc[0x8];
    uint8_t discover_state[0x4]; /* catalog type: uint32_t */
    uint8_t conn_active[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, field_0x2) == 0x2, "g1_layout_bt_ancs_client_ctx__param_0158.field_0x2");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, state_flags) == 0x4, "g1_layout_bt_ancs_client_ctx__param_0158.state_flags");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, field_0x6) == 0x6, "g1_layout_bt_ancs_client_ctx__param_0158.field_0x6");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, ccc_handle) == 0x8, "g1_layout_bt_ancs_client_ctx__param_0158.ccc_handle");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, attr_id) == 0x14, "g1_layout_bt_ancs_client_ctx__param_0158.attr_id");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, attr_len) == 0x1a, "g1_layout_bt_ancs_client_ctx__param_0158.attr_len");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, attr_flags) == 0x1c, "g1_layout_bt_ancs_client_ctx__param_0158.attr_flags");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, notif_uid) == 0x24, "g1_layout_bt_ancs_client_ctx__param_0158.notif_uid");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, category_id) == 0x28, "g1_layout_bt_ancs_client_ctx__param_0158.category_id");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, category_count) == 0x29, "g1_layout_bt_ancs_client_ctx__param_0158.category_count");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, event_id) == 0x2a, "g1_layout_bt_ancs_client_ctx__param_0158.event_id");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, event_flags) == 0x2b, "g1_layout_bt_ancs_client_ctx__param_0158.event_flags");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, client_state) == 0x2c, "g1_layout_bt_ancs_client_ctx__param_0158.client_state");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, attr_buf_flag) == 0x8e8, "g1_layout_bt_ancs_client_ctx__param_0158.attr_buf_flag");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, attr_buf_len) == 0x8f8, "g1_layout_bt_ancs_client_ctx__param_0158.attr_buf_len");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, discover_state) == 0x904, "g1_layout_bt_ancs_client_ctx__param_0158.discover_state");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0158, conn_active) == 0x908, "g1_layout_bt_ancs_client_ctx__param_0158.conn_active");
_Static_assert(sizeof(struct g1_layout_bt_ancs_client_ctx__param_0158) >= 0x90c, "g1_layout_bt_ancs_client_ctx__param_0158.size");

/* param_0159 | G1-original | Large application context shared by parse_app_id_config_stream and invoke_object_callback_864: a stream pointer at 0x864 and a cluster of flags/counters/ids at 0x8fc-0x928. | D1+D2 verified
 * review: Single-cid G1 context; two functions share it. Offsets kept. */
struct __attribute__((packed)) g1_layout_app_id_config_stream_ctx__param_0159 {
    uint8_t _pad_0x0[0x864];
    uint8_t stream_ptr[0x4]; /* catalog type: void * */
    uint8_t _pad_0x868[0x94];
    uint8_t field_0x8fc[0x4]; /* catalog type: int32_t */
    uint8_t field_0x900[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x904[0x4]; /* catalog type: int32_t */
    uint8_t field_0x908[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x909[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x90a[0x6];
    uint8_t field_0x910[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x912[0x2];
    uint8_t field_0x914[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x918[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x919[0x3];
    uint8_t field_0x91c[0x2]; /* catalog type: int16_t */
    uint8_t _pad_0x91e[0x2];
    uint8_t field_0x920[0x4]; /* catalog type: int32_t */
    uint8_t field_0x924[0x4]; /* catalog type: int32_t */
    uint8_t field_0x928[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, stream_ptr) == 0x864, "g1_layout_app_id_config_stream_ctx__param_0159.stream_ptr");
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, field_0x8fc) == 0x8fc, "g1_layout_app_id_config_stream_ctx__param_0159.field_0x8fc");
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, field_0x900) == 0x900, "g1_layout_app_id_config_stream_ctx__param_0159.field_0x900");
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, field_0x904) == 0x904, "g1_layout_app_id_config_stream_ctx__param_0159.field_0x904");
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, field_0x908) == 0x908, "g1_layout_app_id_config_stream_ctx__param_0159.field_0x908");
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, field_0x909) == 0x909, "g1_layout_app_id_config_stream_ctx__param_0159.field_0x909");
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, field_0x910) == 0x910, "g1_layout_app_id_config_stream_ctx__param_0159.field_0x910");
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, field_0x914) == 0x914, "g1_layout_app_id_config_stream_ctx__param_0159.field_0x914");
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, field_0x918) == 0x918, "g1_layout_app_id_config_stream_ctx__param_0159.field_0x918");
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, field_0x91c) == 0x91c, "g1_layout_app_id_config_stream_ctx__param_0159.field_0x91c");
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, field_0x920) == 0x920, "g1_layout_app_id_config_stream_ctx__param_0159.field_0x920");
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, field_0x924) == 0x924, "g1_layout_app_id_config_stream_ctx__param_0159.field_0x924");
_Static_assert(offsetof(struct g1_layout_app_id_config_stream_ctx__param_0159, field_0x928) == 0x928, "g1_layout_app_id_config_stream_ctx__param_0159.field_0x928");
_Static_assert(sizeof(struct g1_layout_app_id_config_stream_ctx__param_0159) >= 0x92c, "g1_layout_app_id_config_stream_ctx__param_0159.size");

/* param_0160 | G1-original | G1 reimplementation of a GATT subscription context (value/CCC handles, callback/conn pointers), shared between gatt_subscribe_service_changed and gatt_service_changed_c_discovery_completed. | D1+D2 verified
 * review: Two APPLICATION members share this object; treated as G1-original (not stock bt_gatt_subscribe_params). is_union=true: 0x4 accessed 4-wide over 2-byte gap to 0x6. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_gatt_subscribe_ctx__param_0160 {
    uint8_t _pad_0x0[0x1];
    uint8_t subscribe_flags[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x3[0x1];
    uint8_t value_handle[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x6[0x2]; /* catalog type: uint16_t */
    uint8_t ccc_handle[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x8];
    uint8_t notify_cb[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x4];
    uint8_t conn_ptr[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x20[0x4];
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x28[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_subscribe_ctx__param_0160, subscribe_flags) == 0x1, "g1_layout_gatt_subscribe_ctx__param_0160.subscribe_flags");
_Static_assert(offsetof(struct g1_layout_gatt_subscribe_ctx__param_0160, value_handle) == 0x4, "g1_layout_gatt_subscribe_ctx__param_0160.value_handle");
_Static_assert(offsetof(struct g1_layout_gatt_subscribe_ctx__param_0160, field_0x6) == 0x6, "g1_layout_gatt_subscribe_ctx__param_0160.field_0x6");
_Static_assert(offsetof(struct g1_layout_gatt_subscribe_ctx__param_0160, ccc_handle) == 0x8, "g1_layout_gatt_subscribe_ctx__param_0160.ccc_handle");
_Static_assert(offsetof(struct g1_layout_gatt_subscribe_ctx__param_0160, notify_cb) == 0x14, "g1_layout_gatt_subscribe_ctx__param_0160.notify_cb");
_Static_assert(offsetof(struct g1_layout_gatt_subscribe_ctx__param_0160, conn_ptr) == 0x1c, "g1_layout_gatt_subscribe_ctx__param_0160.conn_ptr");
_Static_assert(offsetof(struct g1_layout_gatt_subscribe_ctx__param_0160, field_0x24) == 0x24, "g1_layout_gatt_subscribe_ctx__param_0160.field_0x24");
_Static_assert(offsetof(struct g1_layout_gatt_subscribe_ctx__param_0160, field_0x28) == 0x28, "g1_layout_gatt_subscribe_ctx__param_0160.field_0x28");
_Static_assert(sizeof(struct g1_layout_gatt_subscribe_ctx__param_0160) >= 0x2c, "g1_layout_gatt_subscribe_ctx__param_0160.size");

/* param_0162 | library | nRF Connect SDK CAF module_state_event handled by module_state_event_log_handler: module id pointer and state. | D1+D2 verified
 * review: CAF event; leading event_header (sys_slist node + type ptr) occupies 0x0-0x3, so module ptr lands at 0x4. Header offsets not checked, so verified=false. */
struct __attribute__((packed)) g1_layout_module_state_event__param_0162 {
    uint8_t _pad_0x0[0x4];
    uint8_t module_id[0x4]; /* catalog type: const void* */
    uint8_t field_0x8[0x4]; /* catalog type: void* */
    uint8_t state[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_module_state_event__param_0162, module_id) == 0x4, "g1_layout_module_state_event__param_0162.module_id");
_Static_assert(offsetof(struct g1_layout_module_state_event__param_0162, field_0x8) == 0x8, "g1_layout_module_state_event__param_0162.field_0x8");
_Static_assert(offsetof(struct g1_layout_module_state_event__param_0162, state) == 0xc, "g1_layout_module_state_event__param_0162.state");
_Static_assert(sizeof(struct g1_layout_module_state_event__param_0162) >= 0x10, "g1_layout_module_state_event__param_0162.size");

/* param_0163 | G1-original | Power-manager restrict-event log entry (power_manager_restrict_event_log): context pointer, value, status byte. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_power_restrict_event_entry__param_0163 {
    uint8_t _pad_0x0[0x4];
    uint8_t ctx_ptr[0x4]; /* catalog type: void* */
    uint8_t value[0x4]; /* catalog type: uint32_t */
    uint8_t status[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_power_restrict_event_entry__param_0163, ctx_ptr) == 0x4, "g1_layout_power_restrict_event_entry__param_0163.ctx_ptr");
_Static_assert(offsetof(struct g1_layout_power_restrict_event_entry__param_0163, value) == 0x8, "g1_layout_power_restrict_event_entry__param_0163.value");
_Static_assert(offsetof(struct g1_layout_power_restrict_event_entry__param_0163, status) == 0xc, "g1_layout_power_restrict_event_entry__param_0163.status");
_Static_assert(sizeof(struct g1_layout_power_restrict_event_entry__param_0163) >= 0x10, "g1_layout_power_restrict_event_entry__param_0163.size");

/* param_0164 | library | TinyCrypt SHA-256 state (iv[8], bits_hashed, leftover[64], leftover_offset) shared across tc_sha256/tc_cmac/tc_hmac_prng param-1 slot; +0x130 tail belongs to the enclosing tc_hmac_prng_struct. | D1+D2 verified
 * review: VERIFIED against sha256.h: iv[8]@0x0-0x1f, bits_hashed(u64)@0x20-0x27, leftover[64]@0x28-0x67, leftover_offset@0x68 — all observed offsets (0x4-0x68) fall inside these members. 0x20/0x24 are the two halves of bits_hashed. Cluster conflates tc_cmac_struct/tc_hmac_prng_struct (which embed sha256 state); +0x130 lies beyond tc_sha256_state_struct (size 0x6c) and belongs to tc_hmac_prng_struct. Corrected sonnet's flat iv0..iv6 labels. */
struct __attribute__((packed)) g1_layout_tc_sha256_state_struct__param_0164 {
    uint8_t _pad_0x0[0x4];
    uint8_t iv_1[0x4]; /* catalog type: uint32_t; SDK member: iv[1] */
    uint8_t iv_2[0x4]; /* catalog type: uint32_t; SDK member: iv[2] */
    uint8_t iv_3[0x4]; /* catalog type: uint32_t; SDK member: iv[3] */
    uint8_t iv_4[0x4]; /* catalog type: uint32_t; SDK member: iv[4] */
    uint8_t iv_5[0x4]; /* catalog type: uint32_t; SDK member: iv[5] */
    uint8_t iv_6[0x4]; /* catalog type: uint32_t; SDK member: iv[6] */
    uint8_t iv_7[0x4]; /* catalog type: uint32_t; SDK member: iv[7] */
    uint8_t bits_hashed_lo[0x4]; /* catalog type: uint32_t; SDK member: bits_hashed (low word) */
    uint8_t bits_hashed_hi[0x4]; /* catalog type: uint32_t; SDK member: bits_hashed (high word) */
    uint8_t _pad_0x28[0x1c];
    uint8_t leftover_44[0x4]; /* catalog type: uint32_t; SDK member: leftover[0x1c..] */
    uint8_t leftover_48[0x4]; /* catalog type: uint32_t; SDK member: leftover[0x20..] */
    uint8_t _pad_0x4c[0x4];
    uint8_t leftover_50[0x4]; /* catalog type: uint32_t; SDK member: leftover[0x28..] */
    uint8_t leftover_54[0x4]; /* catalog type: uint32_t; SDK member: leftover[0x2c..] */
    uint8_t leftover_58[0x4]; /* catalog type: uint32_t; SDK member: leftover[0x30..] */
    uint8_t _pad_0x5c[0x4];
    uint8_t leftover_60[0x1]; /* catalog type: uint8_t; SDK member: leftover[0x38] */
    uint8_t leftover_61[0x1]; /* catalog type: uint8_t; SDK member: leftover[0x39] */
    uint8_t leftover_62[0x1]; /* catalog type: uint8_t; SDK member: leftover[0x3a] */
    uint8_t leftover_63[0x1]; /* catalog type: uint8_t; SDK member: leftover[0x3b] */
    uint8_t leftover_64[0x4]; /* catalog type: uint32_t; SDK member: leftover[0x3c..0x3f] */
    uint8_t leftover_offset[0x4]; /* catalog type: uint32_t; SDK member: leftover_offset */
    uint8_t _pad_0x6c[0xc4];
    uint8_t hmac_prng_tail[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, iv_1) == 0x4, "g1_layout_tc_sha256_state_struct__param_0164.iv_1");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, iv_2) == 0x8, "g1_layout_tc_sha256_state_struct__param_0164.iv_2");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, iv_3) == 0xc, "g1_layout_tc_sha256_state_struct__param_0164.iv_3");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, iv_4) == 0x10, "g1_layout_tc_sha256_state_struct__param_0164.iv_4");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, iv_5) == 0x14, "g1_layout_tc_sha256_state_struct__param_0164.iv_5");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, iv_6) == 0x18, "g1_layout_tc_sha256_state_struct__param_0164.iv_6");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, iv_7) == 0x1c, "g1_layout_tc_sha256_state_struct__param_0164.iv_7");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, bits_hashed_lo) == 0x20, "g1_layout_tc_sha256_state_struct__param_0164.bits_hashed_lo");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, bits_hashed_hi) == 0x24, "g1_layout_tc_sha256_state_struct__param_0164.bits_hashed_hi");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, leftover_44) == 0x44, "g1_layout_tc_sha256_state_struct__param_0164.leftover_44");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, leftover_48) == 0x48, "g1_layout_tc_sha256_state_struct__param_0164.leftover_48");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, leftover_50) == 0x50, "g1_layout_tc_sha256_state_struct__param_0164.leftover_50");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, leftover_54) == 0x54, "g1_layout_tc_sha256_state_struct__param_0164.leftover_54");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, leftover_58) == 0x58, "g1_layout_tc_sha256_state_struct__param_0164.leftover_58");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, leftover_60) == 0x60, "g1_layout_tc_sha256_state_struct__param_0164.leftover_60");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, leftover_61) == 0x61, "g1_layout_tc_sha256_state_struct__param_0164.leftover_61");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, leftover_62) == 0x62, "g1_layout_tc_sha256_state_struct__param_0164.leftover_62");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, leftover_63) == 0x63, "g1_layout_tc_sha256_state_struct__param_0164.leftover_63");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, leftover_64) == 0x64, "g1_layout_tc_sha256_state_struct__param_0164.leftover_64");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, leftover_offset) == 0x68, "g1_layout_tc_sha256_state_struct__param_0164.leftover_offset");
_Static_assert(offsetof(struct g1_layout_tc_sha256_state_struct__param_0164, hmac_prng_tail) == 0x130, "g1_layout_tc_sha256_state_struct__param_0164.hmac_prng_tail");
_Static_assert(sizeof(struct g1_layout_tc_sha256_state_struct__param_0164) >= 0x134, "g1_layout_tc_sha256_state_struct__param_0164.size");

/* param_0166 | library | ARM Cortex-M exception stack frame (arch_esf / _esf_t) dumped by arm_fault_dump_esf_registers and z_fatal_error: r0-r3, r12, lr, pc, plus a trailing field. | D1+D2 verified
 * review: Register sequence r0..pc is unmistakable, but the observed frame starts at +0x4 (r0@0x4) whereas the canonical __basic_sf places a1/r0 at offset 0 — the pointer here is +0x4 into the frame (or a wrapping esf). Because the offsets are shifted vs the header, library_verified=false. */
struct __attribute__((packed)) g1_layout_arch_esf__param_0166 {
    uint8_t _pad_0x0[0x4];
    uint8_t r0[0x4]; /* catalog type: uint32_t */
    uint8_t r1[0x4]; /* catalog type: uint32_t */
    uint8_t r2[0x4]; /* catalog type: uint32_t */
    uint8_t r3[0x4]; /* catalog type: uint32_t */
    uint8_t r12[0x4]; /* catalog type: uint32_t */
    uint8_t lr[0x4]; /* catalog type: uint32_t */
    uint8_t pc[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x20[0x40];
    uint8_t field_0x60_extra[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_arch_esf__param_0166, r0) == 0x4, "g1_layout_arch_esf__param_0166.r0");
_Static_assert(offsetof(struct g1_layout_arch_esf__param_0166, r1) == 0x8, "g1_layout_arch_esf__param_0166.r1");
_Static_assert(offsetof(struct g1_layout_arch_esf__param_0166, r2) == 0xc, "g1_layout_arch_esf__param_0166.r2");
_Static_assert(offsetof(struct g1_layout_arch_esf__param_0166, r3) == 0x10, "g1_layout_arch_esf__param_0166.r3");
_Static_assert(offsetof(struct g1_layout_arch_esf__param_0166, r12) == 0x14, "g1_layout_arch_esf__param_0166.r12");
_Static_assert(offsetof(struct g1_layout_arch_esf__param_0166, lr) == 0x18, "g1_layout_arch_esf__param_0166.lr");
_Static_assert(offsetof(struct g1_layout_arch_esf__param_0166, pc) == 0x1c, "g1_layout_arch_esf__param_0166.pc");
_Static_assert(offsetof(struct g1_layout_arch_esf__param_0166, field_0x60_extra) == 0x60, "g1_layout_arch_esf__param_0166.field_0x60_extra");
_Static_assert(sizeof(struct g1_layout_arch_esf__param_0166) >= 0x64, "g1_layout_arch_esf__param_0166.size");

/* param_0167 | library | Heterogeneous cluster: one param_1 slot shared by many distinct Zephyr kernel objects (k_mutex/k_sem/k_msgq wait-q fields at low offsets; k_thread stack/entry fields at 0x50-0xd4 via arch_new_thread/z_setup_new_thread). | D1+D2 verified
 * review: Footprint over-merge of unrelated kernel structs sharing a param slot across 11 functions; cannot resolve to a single library layout, so unverified and marked union. 0xc has a 1/4-byte overlap (union). Low-offset fields belong to embedded sync primitives, high-offset (0x50+) to k_thread setup. */
struct __attribute__((packed)) g1_layout_kernel_obj_shared_param__param_0167 {
    uint8_t _pad_0x0[0x8];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x1]; /* catalog type: uint32_t */
    uint8_t field_0xd[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xe[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xf[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: void * */
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x28[0x28];
    uint8_t thread_field_0x50[0x4]; /* catalog type: uint32_t */
    uint8_t thread_field_0x54[0x4]; /* catalog type: uint32_t */
    uint8_t thread_field_0x58[0x4]; /* catalog type: uint32_t */
    uint8_t thread_field_0x5c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x60[0x10];
    uint8_t thread_field_0x70[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x71[0x3];
    uint8_t thread_field_0x74[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x78[0x4];
    uint8_t thread_field_0x7c[0x4]; /* catalog type: uint32_t */
    uint8_t thread_field_0x80[0x4]; /* catalog type: uint32_t */
    uint8_t thread_field_0x84[0x4]; /* catalog type: uint32_t */
    uint8_t thread_field_0x88[0x4]; /* catalog type: uint32_t */
    uint8_t thread_field_0x8c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x90[0x44];
    uint8_t thread_field_0xd4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, field_0x8) == 0x8, "g1_layout_kernel_obj_shared_param__param_0167.field_0x8");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, field_0xc) == 0xc, "g1_layout_kernel_obj_shared_param__param_0167.field_0xc");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, field_0xd) == 0xd, "g1_layout_kernel_obj_shared_param__param_0167.field_0xd");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, field_0xe) == 0xe, "g1_layout_kernel_obj_shared_param__param_0167.field_0xe");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, field_0xf) == 0xf, "g1_layout_kernel_obj_shared_param__param_0167.field_0xf");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, field_0x10) == 0x10, "g1_layout_kernel_obj_shared_param__param_0167.field_0x10");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, field_0x14) == 0x14, "g1_layout_kernel_obj_shared_param__param_0167.field_0x14");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, field_0x18) == 0x18, "g1_layout_kernel_obj_shared_param__param_0167.field_0x18");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, field_0x1c) == 0x1c, "g1_layout_kernel_obj_shared_param__param_0167.field_0x1c");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, field_0x20) == 0x20, "g1_layout_kernel_obj_shared_param__param_0167.field_0x20");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, field_0x24) == 0x24, "g1_layout_kernel_obj_shared_param__param_0167.field_0x24");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, thread_field_0x50) == 0x50, "g1_layout_kernel_obj_shared_param__param_0167.thread_field_0x50");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, thread_field_0x54) == 0x54, "g1_layout_kernel_obj_shared_param__param_0167.thread_field_0x54");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, thread_field_0x58) == 0x58, "g1_layout_kernel_obj_shared_param__param_0167.thread_field_0x58");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, thread_field_0x5c) == 0x5c, "g1_layout_kernel_obj_shared_param__param_0167.thread_field_0x5c");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, thread_field_0x70) == 0x70, "g1_layout_kernel_obj_shared_param__param_0167.thread_field_0x70");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, thread_field_0x74) == 0x74, "g1_layout_kernel_obj_shared_param__param_0167.thread_field_0x74");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, thread_field_0x7c) == 0x7c, "g1_layout_kernel_obj_shared_param__param_0167.thread_field_0x7c");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, thread_field_0x80) == 0x80, "g1_layout_kernel_obj_shared_param__param_0167.thread_field_0x80");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, thread_field_0x84) == 0x84, "g1_layout_kernel_obj_shared_param__param_0167.thread_field_0x84");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, thread_field_0x88) == 0x88, "g1_layout_kernel_obj_shared_param__param_0167.thread_field_0x88");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, thread_field_0x8c) == 0x8c, "g1_layout_kernel_obj_shared_param__param_0167.thread_field_0x8c");
_Static_assert(offsetof(struct g1_layout_kernel_obj_shared_param__param_0167, thread_field_0xd4) == 0xd4, "g1_layout_kernel_obj_shared_param__param_0167.thread_field_0xd4");
_Static_assert(sizeof(struct g1_layout_kernel_obj_shared_param__param_0167) >= 0xd8, "g1_layout_kernel_obj_shared_param__param_0167.size");

/* param_0168 | library | Zephyr thread control block (struct k_thread; _thread_base embedded at offset 0) accessed by scheduler internals: qnode, pended_on, user_options/thread_state/prio, timeout node. | D1+D2 verified
 * review: VERIFIED against _thread_base in kernel/thread.h (SMP off): qnode_dlist@0x0-0x8, pended_on@0x8, user_options@0xc, thread_state@0xd, prio/preempt@0xe, order_key@0x10, swap_data@0x14, timeout@0x18. Observed 0x4(qnode),0x8(pended_on),0xc(user_options),0xd(thread_state),0xe(prio),0x18(timeout) all line up. Sonnet's 'prio@0xc' corrected to user_options; 0xc is user_options, 0xe is prio. 0x58 is beyond _thread_base (arch/callee-saved region of k_thread), unverified. */
struct __attribute__((packed)) g1_layout_k_thread__param_0168 {
    uint8_t _pad_0x0[0x4];
    uint8_t qnode_dlist_next[0x4]; /* catalog type: void*; SDK member: base.qnode_dlist */
    uint8_t pended_on[0x4]; /* catalog type: void*; SDK member: base.pended_on */
    uint8_t user_options[0x1]; /* catalog type: uint8_t; SDK member: base.user_options */
    uint8_t thread_state[0x1]; /* catalog type: uint8_t; SDK member: base.thread_state */
    uint8_t prio[0x1]; /* catalog type: uint8_t; SDK member: base.prio */
    uint8_t _pad_0xf[0x9];
    uint8_t timeout_node[0x4]; /* catalog type: void*; SDK member: base.timeout.node */
    uint8_t _pad_0x1c[0x3c];
    uint8_t field_0x58[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_k_thread__param_0168, qnode_dlist_next) == 0x4, "g1_layout_k_thread__param_0168.qnode_dlist_next");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0168, pended_on) == 0x8, "g1_layout_k_thread__param_0168.pended_on");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0168, user_options) == 0xc, "g1_layout_k_thread__param_0168.user_options");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0168, thread_state) == 0xd, "g1_layout_k_thread__param_0168.thread_state");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0168, prio) == 0xe, "g1_layout_k_thread__param_0168.prio");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0168, timeout_node) == 0x18, "g1_layout_k_thread__param_0168.timeout_node");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0168, field_0x58) == 0x58, "g1_layout_k_thread__param_0168.field_0x58");
_Static_assert(sizeof(struct g1_layout_k_thread__param_0168) >= 0x5c, "g1_layout_k_thread__param_0168.size");

/* param_0169 | library | param_2 of region_init (a LIBRARY function): memory region descriptor with base and size words. | D1+D2 verified
 * review: region_init is LIBRARY but the exact type (sys_mem_blocks / rtio region / heap) is ambiguous from two generic words; left unverified. */
struct __attribute__((packed)) g1_layout_mem_region_desc__param_0169 {
    uint8_t _pad_0x0[0x8];
    uint8_t base[0x4]; /* catalog type: uint32_t */
    uint8_t size[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_mem_region_desc__param_0169, base) == 0x8, "g1_layout_mem_region_desc__param_0169.base");
_Static_assert(offsetof(struct g1_layout_mem_region_desc__param_0169, size) == 0xc, "g1_layout_mem_region_desc__param_0169.size");
_Static_assert(sizeof(struct g1_layout_mem_region_desc__param_0169) >= 0x10, "g1_layout_mem_region_desc__param_0169.size");

/* param_0170 | library | ARMv8-M (Cortex-M33) MPU region descriptor (name + base + attr) passed to arm_core_mpu_configure and mpu_configure_region. | D1+D2 verified
 * review: base@0x4 is consistent with arm_mpu_region {const char* name@0; uint32_t base@4; attr@8}, but Ghidra splits attr into a 0x8 word and a 0xa ushort (is_union=true) which does not cleanly match the RBAR/RLAR sub-layout, so library_verified=false. */
struct __attribute__((packed)) g1_layout_arm_mpu_region__param_0170 {
    uint8_t _pad_0x0[0x4];
    uint8_t base[0x4]; /* catalog type: uint32_t; SDK member: base */
    uint8_t attr[0x2]; /* catalog type: uint32_t; SDK member: attr */
    uint8_t attr_hi[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_arm_mpu_region__param_0170, base) == 0x4, "g1_layout_arm_mpu_region__param_0170.base");
_Static_assert(offsetof(struct g1_layout_arm_mpu_region__param_0170, attr) == 0x8, "g1_layout_arm_mpu_region__param_0170.attr");
_Static_assert(offsetof(struct g1_layout_arm_mpu_region__param_0170, attr_hi) == 0xa, "g1_layout_arm_mpu_region__param_0170.attr_hi");
_Static_assert(sizeof(struct g1_layout_arm_mpu_region__param_0170) >= 0xe, "g1_layout_arm_mpu_region__param_0170.size");

/* param_0172 | library | Zephyr net_buf network buffer threaded through the BLE stack (HCI/L2CAP/ATT/SMP RX/TX paths, net_buf_ref/unref/id/frags_len). | D1+D2 verified
 * review: Verified against buf.h: node(sys_snode_t)@0x0, frags@0x4, ref@0x8, flags@0x9, pool_id@0xa, user_data_size@0xb, then union{data@0xc, len@0x10, size@0x12, __buf@0x14}, then user_data[]@0x18. Corrected sonnet: 0xc is data pointer (via net_buf_simple), 0x14 is __buf (storage ptr) not 'reserved', 0x18/0x1c are user_data. is_union=true (net_buf_simple union at 0xc). All observed offsets line up. */
struct __attribute__((packed)) g1_layout_net_buf__param_0172 {
    uint8_t _pad_0x0[0x4];
    uint8_t frags[0x4]; /* catalog type: struct net_buf *; SDK member: frags */
    uint8_t ref[0x1]; /* catalog type: uint8_t; SDK member: ref */
    uint8_t flags[0x1]; /* catalog type: uint8_t; SDK member: flags */
    uint8_t pool_id[0x1]; /* catalog type: uint8_t; SDK member: pool_id */
    uint8_t user_data_size[0x1]; /* catalog type: uint8_t; SDK member: user_data_size */
    uint8_t data[0x4]; /* catalog type: uint8_t *; SDK member: data (net_buf_simple) */
    uint8_t len[0x2]; /* catalog type: uint16_t; SDK member: len (net_buf_simple) */
    uint8_t _pad_0x12[0x2];
    uint8_t __buf[0x4]; /* catalog type: uint8_t *; SDK member: __buf (net_buf_simple) */
    uint8_t user_data[0x1]; /* catalog type: uint8_t; SDK member: user_data[] */
    uint8_t _pad_0x19[0x3];
    uint8_t user_data_tail[0x1]; /* catalog type: uint8_t; SDK member: user_data[] */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_net_buf__param_0172, frags) == 0x4, "g1_layout_net_buf__param_0172.frags");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0172, ref) == 0x8, "g1_layout_net_buf__param_0172.ref");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0172, flags) == 0x9, "g1_layout_net_buf__param_0172.flags");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0172, pool_id) == 0xa, "g1_layout_net_buf__param_0172.pool_id");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0172, user_data_size) == 0xb, "g1_layout_net_buf__param_0172.user_data_size");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0172, data) == 0xc, "g1_layout_net_buf__param_0172.data");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0172, len) == 0x10, "g1_layout_net_buf__param_0172.len");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0172, __buf) == 0x14, "g1_layout_net_buf__param_0172.__buf");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0172, user_data) == 0x18, "g1_layout_net_buf__param_0172.user_data");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0172, user_data_tail) == 0x1c, "g1_layout_net_buf__param_0172.user_data_tail");
_Static_assert(sizeof(struct g1_layout_net_buf__param_0172) >= 0x20, "g1_layout_net_buf__param_0172.size");

/* param_0173 | library | MCUmgr SMP request-packet processing context (length/data pair) passed to smp_process_request_packet. | D1+D2 verified
 * review: Only two idx4 fields observed; likely a net_buf-style packet handle but insufficient signal to verify against a header. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_smp_pkt_ctx__param_0173 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_smp_pkt_ctx__param_0173, field_0x4) == 0x4, "g1_layout_smp_pkt_ctx__param_0173.field_0x4");
_Static_assert(offsetof(struct g1_layout_smp_pkt_ctx__param_0173, field_0x8) == 0x8, "g1_layout_smp_pkt_ctx__param_0173.field_0x8");
_Static_assert(sizeof(struct g1_layout_smp_pkt_ctx__param_0173) >= 0xc, "g1_layout_smp_pkt_ctx__param_0173.size");

/* param_0174 | library | zcbor encoder state shared by smp_add_cmd_err and the cbor_encode_* /zcbor_bstr_encode helpers: payload cursor/end plus error/length fields. | D1+D2 verified
 * review: Identity strong from cbor_encode_* member set; only idx4/short accesses observed, offsets not verified against zcbor header. */
struct __attribute__((packed)) g1_layout_zcbor_state_t__param_0174 {
    uint8_t _pad_0x0[0x8];
    uint8_t payload[0x4]; /* catalog type: uint8_t* */
    uint8_t payload_end[0x4]; /* catalog type: uint8_t* */
    uint8_t _pad_0x10[0x4];
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x18];
    uint8_t field_0x30[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x32[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0174, payload) == 0x8, "g1_layout_zcbor_state_t__param_0174.payload");
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0174, payload_end) == 0xc, "g1_layout_zcbor_state_t__param_0174.payload_end");
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0174, field_0x14) == 0x14, "g1_layout_zcbor_state_t__param_0174.field_0x14");
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0174, field_0x30) == 0x30, "g1_layout_zcbor_state_t__param_0174.field_0x30");
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0174, field_0x32) == 0x32, "g1_layout_zcbor_state_t__param_0174.field_0x32");
_Static_assert(sizeof(struct g1_layout_zcbor_state_t__param_0174) >= 0x36, "g1_layout_zcbor_state_t__param_0174.size");

/* param_0175 | library | MCUmgr image-upload request descriptor inspected by img_mgmt_upload_inspect (offset/size/chunk fields of a firmware upload chunk). | D1+D2 verified
 * review: SPLIT from collision group global_1358 (coincidental 7-word footprint). Real mcumgr img_mgmt_upload_req has mixed bool/size_t/ptr members that do not line up with the generic idx4 words Ghidra recovered, so library_verified=false. */
struct __attribute__((packed)) g1_layout_img_mgmt_upload_req__param_0175 {
    uint8_t _pad_0x0[0x4];
    uint8_t off[0x4]; /* catalog type: uint32_t */
    uint8_t size[0x4]; /* catalog type: uint32_t */
    uint8_t data_len[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_req__param_0175, off) == 0x4, "g1_layout_img_mgmt_upload_req__param_0175.off");
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_req__param_0175, size) == 0x8, "g1_layout_img_mgmt_upload_req__param_0175.size");
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_req__param_0175, data_len) == 0xc, "g1_layout_img_mgmt_upload_req__param_0175.data_len");
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_req__param_0175, field_0x10) == 0x10, "g1_layout_img_mgmt_upload_req__param_0175.field_0x10");
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_req__param_0175, field_0x14) == 0x14, "g1_layout_img_mgmt_upload_req__param_0175.field_0x14");
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_req__param_0175, field_0x18) == 0x18, "g1_layout_img_mgmt_upload_req__param_0175.field_0x18");
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_req__param_0175, field_0x1c) == 0x1c, "g1_layout_img_mgmt_upload_req__param_0175.field_0x1c");
_Static_assert(sizeof(struct g1_layout_img_mgmt_upload_req__param_0175) >= 0x20, "g1_layout_img_mgmt_upload_req__param_0175.size");

/* param_0176 | G1-original | Parameter passed to img_mgmt_state_read/write (mcumgr image-management handlers); two int fields, likely a decode/encode context. | D1+D2 verified
 * review: Downgraded sonnet's is_library=True: param is likely an mcumgr mgmt/zcbor context but only two generic int fields observed, not enough to name a stock struct. is_library=false. */
struct __attribute__((packed)) g1_layout_img_mgmt_req_ctx__param_0176 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: int32_t */
    uint8_t field_0x8[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_img_mgmt_req_ctx__param_0176, field_0x4) == 0x4, "g1_layout_img_mgmt_req_ctx__param_0176.field_0x4");
_Static_assert(offsetof(struct g1_layout_img_mgmt_req_ctx__param_0176, field_0x8) == 0x8, "g1_layout_img_mgmt_req_ctx__param_0176.field_0x8");
_Static_assert(sizeof(struct g1_layout_img_mgmt_req_ctx__param_0176) >= 0xc, "g1_layout_img_mgmt_req_ctx__param_0176.size");

/* param_0177 | library | MCUboot/bootutil firmware image version read by img_mgmt_ver_str (major/minor/revision/build_num). | D1+D2 verified
 * review: VERIFIED against bootutil/image.h: iv_major@0x0(u8), iv_minor@0x1(u8), iv_revision@0x2(u16), iv_build_num@0x4(u32). Observed 0x2/0x4 match iv_revision/iv_build_num. Corrected sonnet library_name (img_mgmt_image_version -> image_version). */
struct __attribute__((packed)) g1_layout_image_version__param_0177 {
    uint8_t _pad_0x0[0x2];
    uint8_t revision[0x2]; /* catalog type: uint16_t; SDK member: iv_revision */
    uint8_t build_num[0x4]; /* catalog type: uint32_t; SDK member: iv_build_num */
};
_Static_assert(offsetof(struct g1_layout_image_version__param_0177, revision) == 0x2, "g1_layout_image_version__param_0177.revision");
_Static_assert(offsetof(struct g1_layout_image_version__param_0177, build_num) == 0x4, "g1_layout_image_version__param_0177.build_num");
_Static_assert(sizeof(struct g1_layout_image_version__param_0177) >= 0x8, "g1_layout_image_version__param_0177.size");

/* param_0178 | G1-original | Context object for img_mgmt_erase (mcumgr image-management erase op); two int fields. | D1+D2 verified
 * review: Ground-truth hint is G1-original and only 2 generic int fields observed; corrected sonnet is_library=True to False (not a distinct stock mcumgr struct). */
struct __attribute__((packed)) g1_layout_img_mgmt_erase_ctx__param_0178 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: int32_t */
    uint8_t field_0x8[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_img_mgmt_erase_ctx__param_0178, field_0x4) == 0x4, "g1_layout_img_mgmt_erase_ctx__param_0178.field_0x4");
_Static_assert(offsetof(struct g1_layout_img_mgmt_erase_ctx__param_0178, field_0x8) == 0x8, "g1_layout_img_mgmt_erase_ctx__param_0178.field_0x8");
_Static_assert(sizeof(struct g1_layout_img_mgmt_erase_ctx__param_0178) >= 0xc, "g1_layout_img_mgmt_erase_ctx__param_0178.size");

/* param_0179 | library | MCUmgr img_mgmt image-upload action/context (offset/length/status words) used by img_mgmt_upload. | D1+D2 verified
 * review: mcumgr img_mgmt type; only two words observed, header not cross-checked, so unverified. */
struct __attribute__((packed)) g1_layout_img_mgmt_upload_action__param_0179 {
    uint8_t _pad_0x0[0x4];
    uint8_t offset_or_len[0x4]; /* catalog type: int32_t */
    uint8_t total_or_status[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_action__param_0179, offset_or_len) == 0x4, "g1_layout_img_mgmt_upload_action__param_0179.offset_or_len");
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_action__param_0179, total_or_status) == 0x8, "g1_layout_img_mgmt_upload_action__param_0179.total_or_status");
_Static_assert(sizeof(struct g1_layout_img_mgmt_upload_action__param_0179) >= 0xc, "g1_layout_img_mgmt_upload_action__param_0179.size");

/* param_0181 | library | Zephyr delayable work item passed to k_work_schedule/reschedule/cancel and internal cancel/submit helpers (embeds k_work + _timeout + queue ptr). | D1+D2 verified
 * review: Checked kernel.h: k_work_delayable = {k_work work(0x0-0x10: node,handler@0x4,queue@0x8,flags@0xc); _timeout timeout@0x10 (0x10 bytes); k_work_q* queue@0x20} => size ~0x24. Observed 0x8(queue) and 0xc(flags) match the k_work base. But tail offsets 0x28/0x38/0x3c exceed 0x24 — the param-flow unification merged in larger objects (smp_rx_remove_invalid/smp_free_buf take net_buf-like params), so tail fields are contamination. Identification kept, verified=false. */
struct __attribute__((packed)) g1_layout_k_work_delayable__param_0181 {
    uint8_t _pad_0x0[0x8];
    uint8_t queue[0x4]; /* catalog type: void*; SDK member: work.queue */
    uint8_t flags[0x4]; /* catalog type: uint32_t; SDK member: work.flags */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x14];
    uint8_t field_0x28[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x2c[0xc];
    uint8_t field_0x38[0x4]; /* catalog type: void* */
    uint8_t field_0x3c[0x4]; /* catalog type: void* */
};
_Static_assert(offsetof(struct g1_layout_k_work_delayable__param_0181, queue) == 0x8, "g1_layout_k_work_delayable__param_0181.queue");
_Static_assert(offsetof(struct g1_layout_k_work_delayable__param_0181, flags) == 0xc, "g1_layout_k_work_delayable__param_0181.flags");
_Static_assert(offsetof(struct g1_layout_k_work_delayable__param_0181, field_0x10) == 0x10, "g1_layout_k_work_delayable__param_0181.field_0x10");
_Static_assert(offsetof(struct g1_layout_k_work_delayable__param_0181, field_0x28) == 0x28, "g1_layout_k_work_delayable__param_0181.field_0x28");
_Static_assert(offsetof(struct g1_layout_k_work_delayable__param_0181, field_0x38) == 0x38, "g1_layout_k_work_delayable__param_0181.field_0x38");
_Static_assert(offsetof(struct g1_layout_k_work_delayable__param_0181, field_0x3c) == 0x3c, "g1_layout_k_work_delayable__param_0181.field_0x3c");
_Static_assert(sizeof(struct g1_layout_k_work_delayable__param_0181) >= 0x40, "g1_layout_k_work_delayable__param_0181.size");

/* param_0182 | library | Partial view of a BT ATT/connection channel read by gatt_notify_send_chunked and att_get_max_payload_len (negotiated MTU + state/role). | D1+D2 verified
 * review: MTU at 0x10 is consistent with an ATT channel but only 4 fields observed; not offset-verified. */
struct __attribute__((packed)) g1_layout_bt_att_chan_view__param_0182 {
    uint8_t _pad_0x0[0xc];
    uint8_t conn_state_or_handle[0x4]; /* catalog type: int32_t */
    uint8_t mtu[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x12[0x6];
    uint8_t role_or_type[0x4]; /* catalog type: uint32_t */
    uint8_t flags[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_bt_att_chan_view__param_0182, conn_state_or_handle) == 0xc, "g1_layout_bt_att_chan_view__param_0182.conn_state_or_handle");
_Static_assert(offsetof(struct g1_layout_bt_att_chan_view__param_0182, mtu) == 0x10, "g1_layout_bt_att_chan_view__param_0182.mtu");
_Static_assert(offsetof(struct g1_layout_bt_att_chan_view__param_0182, role_or_type) == 0x18, "g1_layout_bt_att_chan_view__param_0182.role_or_type");
_Static_assert(offsetof(struct g1_layout_bt_att_chan_view__param_0182, flags) == 0x1c, "g1_layout_bt_att_chan_view__param_0182.flags");
_Static_assert(sizeof(struct g1_layout_bt_att_chan_view__param_0182) >= 0x20, "g1_layout_bt_att_chan_view__param_0182.size");

/* param_0183 | G1-original | Argument to bt_addr_le_str (param_1), read as six 32-bit words while stringifying an address. | D1+D2 verified
 * review: SPLIT from param_0033 collision group. Word-wise reads at 0x4-0x18 do NOT match a 7-byte bt_addr_le_t, so not treated as that library type; kept as an opaque G1 arg record. */
struct __attribute__((packed)) g1_layout_bt_addr_le_str_arg__param_0183 {
    uint8_t _pad_0x0[0x4];
    uint8_t word_0[0x4]; /* catalog type: uint32_t */
    uint8_t word_1[0x4]; /* catalog type: uint32_t */
    uint8_t word_2[0x4]; /* catalog type: uint32_t */
    uint8_t word_3[0x4]; /* catalog type: uint32_t */
    uint8_t word_4[0x4]; /* catalog type: uint32_t */
    uint8_t word_5[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le_str_arg__param_0183, word_0) == 0x4, "g1_layout_bt_addr_le_str_arg__param_0183.word_0");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_str_arg__param_0183, word_1) == 0x8, "g1_layout_bt_addr_le_str_arg__param_0183.word_1");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_str_arg__param_0183, word_2) == 0xc, "g1_layout_bt_addr_le_str_arg__param_0183.word_2");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_str_arg__param_0183, word_3) == 0x10, "g1_layout_bt_addr_le_str_arg__param_0183.word_3");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_str_arg__param_0183, word_4) == 0x14, "g1_layout_bt_addr_le_str_arg__param_0183.word_4");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_str_arg__param_0183, word_5) == 0x18, "g1_layout_bt_addr_le_str_arg__param_0183.word_5");
_Static_assert(sizeof(struct g1_layout_bt_addr_le_str_arg__param_0183) >= 0x1c, "g1_layout_bt_addr_le_str_arg__param_0183.size");

/* param_0184 | G1-original | Identity/key descriptor passed to bt_settings_encode_key (param_4) when building a settings storage key. | D1+D2 verified
 * review: SPLIT from param_0033 collision group; separate purpose (settings key encode). G1-original. */
struct __attribute__((packed)) g1_layout_bt_settings_encode_key_arg__param_0184 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_settings_encode_key_arg__param_0184, field_0x4) == 0x4, "g1_layout_bt_settings_encode_key_arg__param_0184.field_0x4");
_Static_assert(offsetof(struct g1_layout_bt_settings_encode_key_arg__param_0184, field_0x8) == 0x8, "g1_layout_bt_settings_encode_key_arg__param_0184.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_settings_encode_key_arg__param_0184, field_0xc) == 0xc, "g1_layout_bt_settings_encode_key_arg__param_0184.field_0xc");
_Static_assert(offsetof(struct g1_layout_bt_settings_encode_key_arg__param_0184, field_0x10) == 0x10, "g1_layout_bt_settings_encode_key_arg__param_0184.field_0x10");
_Static_assert(offsetof(struct g1_layout_bt_settings_encode_key_arg__param_0184, field_0x14) == 0x14, "g1_layout_bt_settings_encode_key_arg__param_0184.field_0x14");
_Static_assert(offsetof(struct g1_layout_bt_settings_encode_key_arg__param_0184, field_0x18) == 0x18, "g1_layout_bt_settings_encode_key_arg__param_0184.field_0x18");
_Static_assert(sizeof(struct g1_layout_bt_settings_encode_key_arg__param_0184) >= 0x1c, "g1_layout_bt_settings_encode_key_arg__param_0184.size");

/* param_0185 | library | Zephyr Bluetooth 32-bit UUID object used by bt_uuid_expand_to_128 and bt_uuid_cmp: type byte (struct bt_uuid) followed by 32-bit val. | D1+D2 verified
 * review: VERIFIED: struct bt_uuid_32 { struct bt_uuid uuid (uint8_t type@0); uint32_t val@4 }. Observed val@0x4 matches; the 0x2 ushort read is a mid-word access, type@0 not read as word here. */
struct __attribute__((packed)) g1_layout_bt_uuid_32__param_0185 {
    uint8_t _pad_0x0[0x2];
    uint8_t field_0x2[0x2]; /* catalog type: uint16_t */
    uint8_t val[0x4]; /* catalog type: uint32_t; SDK member: val */
};
_Static_assert(offsetof(struct g1_layout_bt_uuid_32__param_0185, field_0x2) == 0x2, "g1_layout_bt_uuid_32__param_0185.field_0x2");
_Static_assert(offsetof(struct g1_layout_bt_uuid_32__param_0185, val) == 0x4, "g1_layout_bt_uuid_32__param_0185.val");
_Static_assert(sizeof(struct g1_layout_bt_uuid_32__param_0185) >= 0x8, "g1_layout_bt_uuid_32__param_0185.size");

/* param_0186 | library | 128-bit Bluetooth UUID expansion buffer built by bt_uuid_expand_to_128 (param_2): a type word at 0x0 and a 16-byte value stored as four words at 0x34-0x40. | D1+D2 verified
 * review: Header check FAILED to match: bt_uuid_128 has uuid.type@0x0 and val[16]@0x1, but observed value words are at 0x34-0x40 (not 0x1). Either the pointer targets a larger container with the uuid embedded at a +0x34 offset, or this is not a plain bt_uuid_128. Kept the bt_uuid_128 hypothesis but library_verified=false; offsets unchanged. */
struct __attribute__((packed)) g1_layout_bt_uuid_128__param_0186 {
    uint8_t uuid_type[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x30];
    uint8_t val_word0[0x4]; /* catalog type: uint32_t */
    uint8_t val_word1[0x4]; /* catalog type: uint32_t */
    uint8_t val_word2[0x4]; /* catalog type: uint32_t */
    uint8_t val_word3[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_uuid_128__param_0186, uuid_type) == 0x0, "g1_layout_bt_uuid_128__param_0186.uuid_type");
_Static_assert(offsetof(struct g1_layout_bt_uuid_128__param_0186, val_word0) == 0x34, "g1_layout_bt_uuid_128__param_0186.val_word0");
_Static_assert(offsetof(struct g1_layout_bt_uuid_128__param_0186, val_word1) == 0x38, "g1_layout_bt_uuid_128__param_0186.val_word1");
_Static_assert(offsetof(struct g1_layout_bt_uuid_128__param_0186, val_word2) == 0x3c, "g1_layout_bt_uuid_128__param_0186.val_word2");
_Static_assert(offsetof(struct g1_layout_bt_uuid_128__param_0186, val_word3) == 0x40, "g1_layout_bt_uuid_128__param_0186.val_word3");
_Static_assert(sizeof(struct g1_layout_bt_uuid_128__param_0186) >= 0x44, "g1_layout_bt_uuid_128__param_0186.size");

/* param_0187 | library | Zephyr net_buf accessed while logging an unhandled HCI event (data pointer/len region). | D1+D2 verified
 * review: Sonnet id kept (net_buf) but exact member offsets not verified against net_buf.h; only 0xc/0x10 observed. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_net_buf__param_0187 {
    uint8_t _pad_0x0[0xc];
    uint8_t data_or_len[0x4]; /* catalog type: uint32_t */
    uint8_t len[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_net_buf__param_0187, data_or_len) == 0xc, "g1_layout_net_buf__param_0187.data_or_len");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0187, len) == 0x10, "g1_layout_net_buf__param_0187.len");
_Static_assert(sizeof(struct g1_layout_net_buf__param_0187) >= 0x14, "g1_layout_net_buf__param_0187.size");

/* param_0189 | library | Zephyr BT HCI command-state descriptor set up by bt_hci_cmd_state_set_init (param_2). | D1+D2 verified
 * review: Identity from callee name. Real layout is {atomic_t *target; int bit; bool val}; observed 0x2(w u8)/0x4(u32) do not cleanly line up to that, so verified=false. */
struct __attribute__((packed)) g1_layout_bt_hci_cmd_state_set__param_0189 {
    uint8_t _pad_0x0[0x2];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x1];
    uint8_t bit_or_val[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_hci_cmd_state_set__param_0189, field_0x2) == 0x2, "g1_layout_bt_hci_cmd_state_set__param_0189.field_0x2");
_Static_assert(offsetof(struct g1_layout_bt_hci_cmd_state_set__param_0189, bit_or_val) == 0x4, "g1_layout_bt_hci_cmd_state_set__param_0189.bit_or_val");
_Static_assert(sizeof(struct g1_layout_bt_hci_cmd_state_set__param_0189) >= 0x8, "g1_layout_bt_hci_cmd_state_set__param_0189.size");

/* param_0200 | G1-original | param_1 of ble_conn_addr_and_params_valid: validates a BLE peer address + connection parameters (type/value words plus a role/status int). | D1+D2 verified
 * review: Separated from global_0840 collision group; distinct G1 object. */
struct __attribute__((packed)) g1_layout_ble_conn_addr_params__param_0200 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t role_or_status[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_ble_conn_addr_params__param_0200, field_0x4) == 0x4, "g1_layout_ble_conn_addr_params__param_0200.field_0x4");
_Static_assert(offsetof(struct g1_layout_ble_conn_addr_params__param_0200, field_0x8) == 0x8, "g1_layout_ble_conn_addr_params__param_0200.field_0x8");
_Static_assert(offsetof(struct g1_layout_ble_conn_addr_params__param_0200, field_0xc) == 0xc, "g1_layout_ble_conn_addr_params__param_0200.field_0xc");
_Static_assert(offsetof(struct g1_layout_ble_conn_addr_params__param_0200, role_or_status) == 0x10, "g1_layout_ble_conn_addr_params__param_0200.role_or_status");
_Static_assert(sizeof(struct g1_layout_ble_conn_addr_params__param_0200) >= 0x14, "g1_layout_ble_conn_addr_params__param_0200.size");

/* param_0204 | library | Zephyr net_buf passed to net_buf_destroy: frags pointer, ref/flags byte region, and data pointer. | D1+D2 verified
 * review: Verified against buf.h: net_buf = { sys_snode_t node@0; net_buf* frags@4; uint8 ref@8,flags@9,pool_id@a,user_data_size@b; union{ uint8* data@0xc; ... } }. Observed 0x4=frags, 0x8=ref (read as a word spanning ref/flags/pool_id/user_data_size), 0xc=data. Offsets line up. */
struct __attribute__((packed)) g1_layout_net_buf__param_0204 {
    uint8_t _pad_0x0[0x4];
    uint8_t frags[0x4]; /* catalog type: struct net_buf*; SDK member: frags */
    uint8_t ref_flags_word[0x4]; /* catalog type: uint32_t; SDK member: ref */
    uint8_t data[0x4]; /* catalog type: uint8_t*; SDK member: data */
};
_Static_assert(offsetof(struct g1_layout_net_buf__param_0204, frags) == 0x4, "g1_layout_net_buf__param_0204.frags");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0204, ref_flags_word) == 0x8, "g1_layout_net_buf__param_0204.ref_flags_word");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0204, data) == 0xc, "g1_layout_net_buf__param_0204.data");
_Static_assert(sizeof(struct g1_layout_net_buf__param_0204) >= 0x10, "g1_layout_net_buf__param_0204.size");

/* param_0205 | G1-original | Context shared by conn_tx_send_to_driver and saadc_start_read: header word plus data words; +0x10 accessed both as a word and as a byte. | D1+D2 verified
 * review: is_union=true: 0x10 read as width 4 overlapping the 0x11 byte (Ghidra flagged overlap); 0x4 read as both byte and word. Kept offsets. */
struct __attribute__((packed)) g1_layout_conn_tx_saadc_ctx__param_0205 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x1]; /* catalog type: uint32_t */
    uint8_t field_0x11[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_conn_tx_saadc_ctx__param_0205, field_0x4) == 0x4, "g1_layout_conn_tx_saadc_ctx__param_0205.field_0x4");
_Static_assert(offsetof(struct g1_layout_conn_tx_saadc_ctx__param_0205, field_0x8) == 0x8, "g1_layout_conn_tx_saadc_ctx__param_0205.field_0x8");
_Static_assert(offsetof(struct g1_layout_conn_tx_saadc_ctx__param_0205, field_0xc) == 0xc, "g1_layout_conn_tx_saadc_ctx__param_0205.field_0xc");
_Static_assert(offsetof(struct g1_layout_conn_tx_saadc_ctx__param_0205, field_0x10) == 0x10, "g1_layout_conn_tx_saadc_ctx__param_0205.field_0x10");
_Static_assert(offsetof(struct g1_layout_conn_tx_saadc_ctx__param_0205, field_0x11) == 0x11, "g1_layout_conn_tx_saadc_ctx__param_0205.field_0x11");
_Static_assert(sizeof(struct g1_layout_conn_tx_saadc_ctx__param_0205) >= 0x15, "g1_layout_conn_tx_saadc_ctx__param_0205.size");

/* param_0206 | G1-original | Connection TX driver-submission context used by conn_tx_send_to_driver (BLE controller TX path): a short field and a buffer/callback pointer. | D1+D2 verified
 * review: G1-original; kept sonnet naming. */
struct __attribute__((packed)) g1_layout_conn_tx_ctx__param_0206 {
    uint8_t _pad_0x0[0x10];
    uint8_t field_0x10[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x12[0x6];
    uint8_t field_0x18[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_conn_tx_ctx__param_0206, field_0x10) == 0x10, "g1_layout_conn_tx_ctx__param_0206.field_0x10");
_Static_assert(offsetof(struct g1_layout_conn_tx_ctx__param_0206, field_0x18) == 0x18, "g1_layout_conn_tx_ctx__param_0206.field_0x18");
_Static_assert(sizeof(struct g1_layout_conn_tx_ctx__param_0206) >= 0x1c, "g1_layout_conn_tx_ctx__param_0206.size");

/* param_0207 | library | Zephyr k_poll_event poll descriptor initialized by k_poll_event_init (poller ptr, packed type/state/mode bitfields, obj union). Cluster also merges an unrelated bt_conn param at the same slot. | D1+D2 verified
 * review: Footprint merges k_poll_event_init (true k_poll_event) with bt_conn_prepare_tx_events (a bt_conn), so treat as k_poll_event but note the 0x20 byte likely comes from the bt_conn member. 0xc accessed both byte-wide and word-wide -> union (packed bitfields). */
struct __attribute__((packed)) g1_layout_k_poll_event__param_0207 {
    uint8_t _pad_0x0[0x8];
    uint8_t poller[0x4]; /* catalog type: struct z_poller * */
    uint8_t tag_type_state_mode[0x4]; /* catalog type: uint32_t */
    uint8_t obj[0x4]; /* catalog type: void * */
    uint8_t _pad_0x14[0xc];
    uint8_t field_0x20[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_k_poll_event__param_0207, poller) == 0x8, "g1_layout_k_poll_event__param_0207.poller");
_Static_assert(offsetof(struct g1_layout_k_poll_event__param_0207, tag_type_state_mode) == 0xc, "g1_layout_k_poll_event__param_0207.tag_type_state_mode");
_Static_assert(offsetof(struct g1_layout_k_poll_event__param_0207, obj) == 0x10, "g1_layout_k_poll_event__param_0207.obj");
_Static_assert(offsetof(struct g1_layout_k_poll_event__param_0207, field_0x20) == 0x20, "g1_layout_k_poll_event__param_0207.field_0x20");
_Static_assert(sizeof(struct g1_layout_k_poll_event__param_0207) >= 0x24, "g1_layout_k_poll_event__param_0207.size");

/* param_0208 | library | BLE connection object read at LE-param-updated notify (ble_notify_le_param_updated): conn ref + interval/latency/timeout. | D1+D2 verified
 * review: bt_conn internal layout is in host/conn_internal.h (version-specific); observed 0xa6/0xa8/0xaa look like le.interval/latency/timeout but offsets unverifiable. 0xac is accessed both width 2 and width 4 (overlaps 0xae) => is_union=true. */
struct __attribute__((packed)) g1_layout_bt_conn_le_ctx__param_0208 {
    uint8_t _pad_0x0[0x4];
    uint8_t conn_ref[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x9e];
    uint8_t le_interval[0x2]; /* catalog type: uint16_t */
    uint8_t le_latency[0x2]; /* catalog type: uint16_t */
    uint8_t le_timeout[0x2]; /* catalog type: uint16_t */
    uint8_t field_0xac[0x2]; /* catalog type: uint16_t */
    uint8_t field_0xae[0x2]; /* catalog type: uint16_t */
    uint8_t field_0xb0[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_conn_le_ctx__param_0208, conn_ref) == 0x4, "g1_layout_bt_conn_le_ctx__param_0208.conn_ref");
_Static_assert(offsetof(struct g1_layout_bt_conn_le_ctx__param_0208, le_interval) == 0xa6, "g1_layout_bt_conn_le_ctx__param_0208.le_interval");
_Static_assert(offsetof(struct g1_layout_bt_conn_le_ctx__param_0208, le_latency) == 0xa8, "g1_layout_bt_conn_le_ctx__param_0208.le_latency");
_Static_assert(offsetof(struct g1_layout_bt_conn_le_ctx__param_0208, le_timeout) == 0xaa, "g1_layout_bt_conn_le_ctx__param_0208.le_timeout");
_Static_assert(offsetof(struct g1_layout_bt_conn_le_ctx__param_0208, field_0xac) == 0xac, "g1_layout_bt_conn_le_ctx__param_0208.field_0xac");
_Static_assert(offsetof(struct g1_layout_bt_conn_le_ctx__param_0208, field_0xae) == 0xae, "g1_layout_bt_conn_le_ctx__param_0208.field_0xae");
_Static_assert(offsetof(struct g1_layout_bt_conn_le_ctx__param_0208, field_0xb0) == 0xb0, "g1_layout_bt_conn_le_ctx__param_0208.field_0xb0");
_Static_assert(sizeof(struct g1_layout_bt_conn_le_ctx__param_0208) >= 0xb4, "g1_layout_bt_conn_le_ctx__param_0208.size");

/* param_0210 | library | Bluetooth connection object shared by ble_notify_remote_info_available and bt_smp_request_ltk (SMP/LTK flag bytes near front, status/handle word at 0xc0). | D1+D2 verified
 * review: Likely struct bt_conn but only a sparse partial view; bt_conn layout is config-dependent, not verified. */
struct __attribute__((packed)) g1_layout_bt_conn_ctx__param_0210 {
    uint8_t _pad_0x0[0x8];
    uint8_t field_0x8[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x9[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xa[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xb[0xb5];
    uint8_t field_0xc0[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_conn_ctx__param_0210, field_0x8) == 0x8, "g1_layout_bt_conn_ctx__param_0210.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_conn_ctx__param_0210, field_0x9) == 0x9, "g1_layout_bt_conn_ctx__param_0210.field_0x9");
_Static_assert(offsetof(struct g1_layout_bt_conn_ctx__param_0210, field_0xa) == 0xa, "g1_layout_bt_conn_ctx__param_0210.field_0xa");
_Static_assert(offsetof(struct g1_layout_bt_conn_ctx__param_0210, field_0xc0) == 0xc0, "g1_layout_bt_conn_ctx__param_0210.field_0xc0");
_Static_assert(sizeof(struct g1_layout_bt_conn_ctx__param_0210) >= 0xc4, "g1_layout_bt_conn_ctx__param_0210.size");

/* param_0211 | G1-original | G1-original LE connection-allocation parameter block used by ble_conn_le_alloc (interval/handle field plus a role/state byte). | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_ble_conn_le_alloc_param__param_0211 {
    uint8_t _pad_0x0[0x1];
    uint8_t field_0x1[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x3[0x3];
    uint8_t field_0x6[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_ble_conn_le_alloc_param__param_0211, field_0x1) == 0x1, "g1_layout_ble_conn_le_alloc_param__param_0211.field_0x1");
_Static_assert(offsetof(struct g1_layout_ble_conn_le_alloc_param__param_0211, field_0x6) == 0x6, "g1_layout_ble_conn_le_alloc_param__param_0211.field_0x6");
_Static_assert(sizeof(struct g1_layout_ble_conn_le_alloc_param__param_0211) >= 0x8, "g1_layout_ble_conn_le_alloc_param__param_0211.size");

/* param_0212 | library | Zephyr Bluetooth connection-info struct filled by bt_conn_get_info: type/role, id, LE address bytes, LE connection interval/latency/timeout, security/err. | D1+D2 verified
 * review: Matches bt_conn_get_info output shape (type@0x2, role@0x3, and LE union with interval/latency/timeout near 0xa6-0xae). bt_conn_info contains nested unions (le/br) so exact offsets were not byte-verified against the header in this pass; library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_bt_conn_info__param_0212 {
    uint8_t _pad_0x0[0x2];
    uint8_t type[0x1]; /* catalog type: uint8_t */
    uint8_t role[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x4[0x4];
    uint8_t id[0x1]; /* catalog type: uint8_t */
    uint8_t le_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xa[0x3];
    uint8_t le_addr_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xe[0x98];
    uint8_t le_interval[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xa8[0x4];
    uint8_t le_latency[0x2]; /* catalog type: uint16_t */
    uint8_t le_timeout[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xb0[0x10];
    uint8_t security_or_err[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0212, type) == 0x2, "g1_layout_bt_conn_info__param_0212.type");
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0212, role) == 0x3, "g1_layout_bt_conn_info__param_0212.role");
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0212, id) == 0x8, "g1_layout_bt_conn_info__param_0212.id");
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0212, le_flag) == 0x9, "g1_layout_bt_conn_info__param_0212.le_flag");
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0212, le_addr_byte) == 0xd, "g1_layout_bt_conn_info__param_0212.le_addr_byte");
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0212, le_interval) == 0xa6, "g1_layout_bt_conn_info__param_0212.le_interval");
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0212, le_latency) == 0xac, "g1_layout_bt_conn_info__param_0212.le_latency");
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0212, le_timeout) == 0xae, "g1_layout_bt_conn_info__param_0212.le_timeout");
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0212, security_or_err) == 0xc0, "g1_layout_bt_conn_info__param_0212.security_or_err");
_Static_assert(sizeof(struct g1_layout_bt_conn_info__param_0212) >= 0xc4, "g1_layout_bt_conn_info__param_0212.size");

/* param_0213 | library | Zephyr bt_conn_info populated by bt_conn_get_info describing connection type/role and LE parameters. | D1+D2 verified
 * review: Checked bt_conn_info/bt_conn_le_info in conn.h: real le.interval/latency/timeout sit at 0x18/0x1a/0x1c (union starts at 0x8, struct ~0x30 bytes). The observed trailing offsets 0x90/0x94/0x9c and size>=0xa0 do NOT match — Ghidra's unified param_2 footprint appears conflated/pointer-followed. Only 0x4 plausibly maps to role. Library id kept but library_verified=false; offsets left as ground truth without asserting member names for the mismatched high offsets. */
struct __attribute__((packed)) g1_layout_bt_conn_info__param_0213 {
    uint8_t _pad_0x0[0x4];
    uint8_t role_or_type[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x84];
    uint8_t field_0x90[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x94[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x98[0x4];
    uint8_t field_0x9c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0213, role_or_type) == 0x4, "g1_layout_bt_conn_info__param_0213.role_or_type");
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0213, field_0x8) == 0x8, "g1_layout_bt_conn_info__param_0213.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0213, field_0x90) == 0x90, "g1_layout_bt_conn_info__param_0213.field_0x90");
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0213, field_0x94) == 0x94, "g1_layout_bt_conn_info__param_0213.field_0x94");
_Static_assert(offsetof(struct g1_layout_bt_conn_info__param_0213, field_0x9c) == 0x9c, "g1_layout_bt_conn_info__param_0213.field_0x9c");
_Static_assert(sizeof(struct g1_layout_bt_conn_info__param_0213) >= 0xa0, "g1_layout_bt_conn_info__param_0213.size");

/* param_0214 | library | BLE connection parameters (interval/latency/timeout) shared by send_conn_le_param_update, bt_le_conn_params_valid, bt_conn_le_conn_update. | D1+D2 verified
 * review: Identity strong from library members. Real bt_le_conn_param is 4x uint16 {interval_min@0,interval_max@2,latency@4,timeout@6}=8 bytes; observed word-wise reads at 0x4/0x8/0xc do NOT align (base pointer appears offset by the cluster's 0x4 pad, or a wrapper), so verified=false. */
struct __attribute__((packed)) g1_layout_bt_le_conn_param__param_0214 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_le_conn_param__param_0214, field_0x4) == 0x4, "g1_layout_bt_le_conn_param__param_0214.field_0x4");
_Static_assert(offsetof(struct g1_layout_bt_le_conn_param__param_0214, field_0x8) == 0x8, "g1_layout_bt_le_conn_param__param_0214.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_le_conn_param__param_0214, field_0xc) == 0xc, "g1_layout_bt_le_conn_param__param_0214.field_0xc");
_Static_assert(sizeof(struct g1_layout_bt_le_conn_param__param_0214) >= 0x10, "g1_layout_bt_le_conn_param__param_0214.size");

/* param_0215 | G1-original | BLE connection completion/disconnection processing context (ble_conn_process_complete_or_disconnect); two words within a connection-info object. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_ble_conn_complete_ctx__param_0215 {
    uint8_t _pad_0x0[0x48];
    uint8_t field_0x48[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4c[0x4];
    uint8_t field_0x50[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ble_conn_complete_ctx__param_0215, field_0x48) == 0x48, "g1_layout_ble_conn_complete_ctx__param_0215.field_0x48");
_Static_assert(offsetof(struct g1_layout_ble_conn_complete_ctx__param_0215, field_0x50) == 0x50, "g1_layout_ble_conn_complete_ctx__param_0215.field_0x50");
_Static_assert(sizeof(struct g1_layout_ble_conn_complete_ctx__param_0215) >= 0x54, "g1_layout_ble_conn_complete_ctx__param_0215.size");

/* param_0216 | library | Zephyr pairing/authentication callback table registered via bt_conn_auth_cb_register; the register function reads several function-pointer members to validate them. | D1+D2 verified
 * review: Confirmed struct via conn.h (member order: pairing_accept@0x0, passkey_display@0x4, [passkey_display_keypress if CONFIG_BT_PASSKEY_KEYPRESS], passkey_entry, passkey_confirm, oob_data_request, cancel, pairing_confirm, pincode_entry). Exact offset->member map depends on unknown CONFIG flags, so verified=false. library_member values below assume keypress disabled. */
struct __attribute__((packed)) g1_layout_bt_conn_auth_cb__param_0216 {
    uint8_t _pad_0x0[0x4];
    uint8_t passkey_display[0x4]; /* catalog type: void *; SDK member: passkey_display */
    uint8_t passkey_entry[0x4]; /* catalog type: void *; SDK member: passkey_entry (keypress-disabled build) */
    uint8_t _pad_0xc[0x4];
    uint8_t oob_data_request[0x4]; /* catalog type: void *; SDK member: oob_data_request (keypress-disabled build) */
    uint8_t cancel[0x4]; /* catalog type: void *; SDK member: cancel (keypress-disabled build) */
};
_Static_assert(offsetof(struct g1_layout_bt_conn_auth_cb__param_0216, passkey_display) == 0x4, "g1_layout_bt_conn_auth_cb__param_0216.passkey_display");
_Static_assert(offsetof(struct g1_layout_bt_conn_auth_cb__param_0216, passkey_entry) == 0x8, "g1_layout_bt_conn_auth_cb__param_0216.passkey_entry");
_Static_assert(offsetof(struct g1_layout_bt_conn_auth_cb__param_0216, oob_data_request) == 0x10, "g1_layout_bt_conn_auth_cb__param_0216.oob_data_request");
_Static_assert(offsetof(struct g1_layout_bt_conn_auth_cb__param_0216, cancel) == 0x14, "g1_layout_bt_conn_auth_cb__param_0216.cancel");
_Static_assert(sizeof(struct g1_layout_bt_conn_auth_cb__param_0216) >= 0x18, "g1_layout_bt_conn_auth_cb__param_0216.size");

/* param_0218 | library | L2CAP LE credit-based channel descriptor initialized by l2cap_chan_rx_init: MTU, MPS, credits, and RX state. | D1+D2 verified
 * review: bt_l2cap_le_chan is in the private host header l2cap_internal.h (not in the pinned tree); MTU/MPS/credits/state pattern is consistent but offsets unverified. */
struct __attribute__((packed)) g1_layout_bt_l2cap_le_chan__param_0218 {
    uint8_t _pad_0x0[0x4];
    uint8_t mtu[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0xe];
    uint8_t mps[0x2]; /* catalog type: uint16_t */
    uint8_t credits[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x1a[0x2];
    uint8_t state[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan__param_0218, mtu) == 0x4, "g1_layout_bt_l2cap_le_chan__param_0218.mtu");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan__param_0218, mps) == 0x16, "g1_layout_bt_l2cap_le_chan__param_0218.mps");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan__param_0218, credits) == 0x18, "g1_layout_bt_l2cap_le_chan__param_0218.credits");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan__param_0218, state) == 0x1c, "g1_layout_bt_l2cap_le_chan__param_0218.state");
_Static_assert(sizeof(struct g1_layout_bt_l2cap_le_chan__param_0218) >= 0x20, "g1_layout_bt_l2cap_le_chan__param_0218.size");

/* param_0219 | library | tx flow-control substructure (mtu/mps/credits) inside a Zephyr bt_l2cap_le_chan, initialized by l2cap_chan_tx_init. | D1+D2 verified
 * review: BLE L2CAP LE channel tx block; nested offsets (0x24/0x28/0x2c) relative to the enclosing channel not verified against the host header. */
struct __attribute__((packed)) g1_layout_bt_l2cap_le_chan_tx__param_0219 {
    uint8_t _pad_0x0[0x24];
    uint8_t tx_mtu[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x26[0x2];
    uint8_t tx_mps[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2a[0x2];
    uint8_t tx_credits[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan_tx__param_0219, tx_mtu) == 0x24, "g1_layout_bt_l2cap_le_chan_tx__param_0219.tx_mtu");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan_tx__param_0219, tx_mps) == 0x28, "g1_layout_bt_l2cap_le_chan_tx__param_0219.tx_mps");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan_tx__param_0219, tx_credits) == 0x2c, "g1_layout_bt_l2cap_le_chan_tx__param_0219.tx_credits");
_Static_assert(sizeof(struct g1_layout_bt_l2cap_le_chan_tx__param_0219) >= 0x30, "g1_layout_bt_l2cap_le_chan_tx__param_0219.size");

/* param_0220 | library | Fragmentation/buffer context shared by l2cap_chan_le_send_seg and att_send_data_frags (total_len, mtu/flags, data ptr, remaining_len). | D1+D2 verified
 * review: Internal Zephyr host struct, no public header; 0x9 accessed width 2 into gap 1 (overlaps 0xa) => is_union=true. verified=false. */
struct __attribute__((packed)) g1_layout_att_l2cap_frag_ctx__param_0220 {
    uint8_t _pad_0x0[0x4];
    uint8_t total_len[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x1];
    uint8_t field_0x9[0x1]; /* catalog type: uint16_t */
    uint8_t field_0xa[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xc[0x4];
    uint8_t data_ptr_or_len[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x12];
    uint8_t remaining_len[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_att_l2cap_frag_ctx__param_0220, total_len) == 0x4, "g1_layout_att_l2cap_frag_ctx__param_0220.total_len");
_Static_assert(offsetof(struct g1_layout_att_l2cap_frag_ctx__param_0220, field_0x9) == 0x9, "g1_layout_att_l2cap_frag_ctx__param_0220.field_0x9");
_Static_assert(offsetof(struct g1_layout_att_l2cap_frag_ctx__param_0220, field_0xa) == 0xa, "g1_layout_att_l2cap_frag_ctx__param_0220.field_0xa");
_Static_assert(offsetof(struct g1_layout_att_l2cap_frag_ctx__param_0220, data_ptr_or_len) == 0x10, "g1_layout_att_l2cap_frag_ctx__param_0220.data_ptr_or_len");
_Static_assert(offsetof(struct g1_layout_att_l2cap_frag_ctx__param_0220, remaining_len) == 0x26, "g1_layout_att_l2cap_frag_ctx__param_0220.remaining_len");
_Static_assert(sizeof(struct g1_layout_att_l2cap_frag_ctx__param_0220) >= 0x2a, "g1_layout_att_l2cap_frag_ctx__param_0220.size");

/* param_0221 | library | Large BT connection/channel object shared across l2cap_chan_send_disconnect, l2cap_chan_le_recv_seg, l2cap_le_recv_pdu, gatt_notify_send, gatt_send_service_changed_ind. | D1+D2 verified
 * review: 5 members. Likely conflates bt_conn and bt_l2cap_chan via imprecise pointer unification; overlaps at 0x4/0x14 -> union. Not offset-verified. */
struct __attribute__((packed)) g1_layout_bt_conn_l2cap_view__param_0221 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0xc];
    uint8_t handle_or_state[0x2]; /* catalog type: uint32_t */
    uint8_t field_0x16[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x18[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x1a[0x2];
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x20[0x1];
    uint8_t att_mtu[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x23[0x1];
    uint8_t err_or_id[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x28[0x5];
    uint8_t flags_a[0x1]; /* catalog type: uint8_t */
    uint8_t flags_b[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2f[0x1d];
    uint8_t field_0x4c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x50[0x30];
    uint8_t channels_or_state[0x4]; /* catalog type: uint32_t */
    uint8_t mtu[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x86[0x2e];
    uint8_t field_0xb4[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xb5[0x1];
    uint8_t psm_or_cid[0x2]; /* catalog type: uint16_t */
    uint8_t field_0xb8[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, field_0x4) == 0x4, "g1_layout_bt_conn_l2cap_view__param_0221.field_0x4");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, handle_or_state) == 0x14, "g1_layout_bt_conn_l2cap_view__param_0221.handle_or_state");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, field_0x16) == 0x16, "g1_layout_bt_conn_l2cap_view__param_0221.field_0x16");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, field_0x18) == 0x18, "g1_layout_bt_conn_l2cap_view__param_0221.field_0x18");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, field_0x1c) == 0x1c, "g1_layout_bt_conn_l2cap_view__param_0221.field_0x1c");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, att_mtu) == 0x21, "g1_layout_bt_conn_l2cap_view__param_0221.att_mtu");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, err_or_id) == 0x24, "g1_layout_bt_conn_l2cap_view__param_0221.err_or_id");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, flags_a) == 0x2d, "g1_layout_bt_conn_l2cap_view__param_0221.flags_a");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, flags_b) == 0x2e, "g1_layout_bt_conn_l2cap_view__param_0221.flags_b");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, field_0x4c) == 0x4c, "g1_layout_bt_conn_l2cap_view__param_0221.field_0x4c");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, channels_or_state) == 0x80, "g1_layout_bt_conn_l2cap_view__param_0221.channels_or_state");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, mtu) == 0x84, "g1_layout_bt_conn_l2cap_view__param_0221.mtu");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, field_0xb4) == 0xb4, "g1_layout_bt_conn_l2cap_view__param_0221.field_0xb4");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, psm_or_cid) == 0xb6, "g1_layout_bt_conn_l2cap_view__param_0221.psm_or_cid");
_Static_assert(offsetof(struct g1_layout_bt_conn_l2cap_view__param_0221, field_0xb8) == 0xb8, "g1_layout_bt_conn_l2cap_view__param_0221.field_0xb8");
_Static_assert(sizeof(struct g1_layout_bt_conn_l2cap_view__param_0221) >= 0xbc, "g1_layout_bt_conn_l2cap_view__param_0221.size");

/* param_0222 | library | Zephyr L2CAP LE dynamic channel object populated by l2cap_chan_add: local CID, MTU/MPS/credits words, and a state byte. | D1+D2 verified
 * review: Plausible bt_l2cap_le_chan tx/rx table, but the struct is deeply nested (bt_l2cap_chan base + endpoints) and the sparse observed offsets were not matched member-by-member, so library_verified=false. */
struct __attribute__((packed)) g1_layout_bt_l2cap_le_chan__param_0222 {
    uint8_t _pad_0x0[0x5];
    uint8_t tx_cid[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x7[0x1];
    uint8_t tx_mtu[0x4]; /* catalog type: uint32_t */
    uint8_t tx_mps[0x4]; /* catalog type: uint32_t */
    uint8_t tx_credits[0x4]; /* catalog type: uint32_t */
    uint8_t rx_mtu[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x15];
    uint8_t state[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan__param_0222, tx_cid) == 0x5, "g1_layout_bt_l2cap_le_chan__param_0222.tx_cid");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan__param_0222, tx_mtu) == 0x8, "g1_layout_bt_l2cap_le_chan__param_0222.tx_mtu");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan__param_0222, tx_mps) == 0xc, "g1_layout_bt_l2cap_le_chan__param_0222.tx_mps");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan__param_0222, tx_credits) == 0x10, "g1_layout_bt_l2cap_le_chan__param_0222.tx_credits");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan__param_0222, rx_mtu) == 0x14, "g1_layout_bt_l2cap_le_chan__param_0222.rx_mtu");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan__param_0222, state) == 0x2d, "g1_layout_bt_l2cap_le_chan__param_0222.state");
_Static_assert(sizeof(struct g1_layout_bt_l2cap_le_chan__param_0222) >= 0x31, "g1_layout_bt_l2cap_le_chan__param_0222.size");

/* param_0223 | library | net_buf header fields (data/len region) read via L2CAP segment/PDU receive path (l2cap_chan_le_recv_seg, l2cap_le_recv_pdu); a data-or-len word at 0xc and len at 0x10. | D1+D2 verified
 * review: Partial view of a net_buf: 0xc and 0x10 correspond to the net_buf_simple data/len union region (verified layout in param_0172). Too few fields to fully verify this cid's base independently; library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_net_buf_l2cap_view__param_0223 {
    uint8_t _pad_0x0[0xc];
    uint8_t data_or_len[0x4]; /* catalog type: uint8_t * */
    uint8_t len[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_net_buf_l2cap_view__param_0223, data_or_len) == 0xc, "g1_layout_net_buf_l2cap_view__param_0223.data_or_len");
_Static_assert(offsetof(struct g1_layout_net_buf_l2cap_view__param_0223, len) == 0x10, "g1_layout_net_buf_l2cap_view__param_0223.len");
_Static_assert(sizeof(struct g1_layout_net_buf_l2cap_view__param_0223) >= 0x14, "g1_layout_net_buf_l2cap_view__param_0223.size");

/* param_0224 | library | Zephyr net_buf passed into l2cap_recv; data pointer and leading buffer bytes. | D1+D2 verified
 * review: net_buf id kept; exact member offsets not verified against net_buf.h. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_net_buf__param_0224 {
    uint8_t _pad_0x0[0xc];
    uint8_t data[0x4]; /* catalog type: void * */
    uint8_t buf_head[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_net_buf__param_0224, data) == 0xc, "g1_layout_net_buf__param_0224.data");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0224, buf_head) == 0x10, "g1_layout_net_buf__param_0224.buf_head");
_Static_assert(sizeof(struct g1_layout_net_buf__param_0224) >= 0x14, "g1_layout_net_buf__param_0224.size");

/* param_0225 | G1-original | Callback context for find_type_cb (param_1): a function pointer plus an associated index/id used during GATT attribute-type search. | D1+D2 verified
 * review: G1-original. 0x0 read as code pointer. */
struct __attribute__((packed)) g1_layout_find_type_cb_ctx__param_0225 {
    uint8_t callback_fn[0x4]; /* catalog type: void* */
    uint8_t user_index[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_find_type_cb_ctx__param_0225, callback_fn) == 0x0, "g1_layout_find_type_cb_ctx__param_0225.callback_fn");
_Static_assert(offsetof(struct g1_layout_find_type_cb_ctx__param_0225, user_index) == 0x4, "g1_layout_find_type_cb_ctx__param_0225.user_index");
_Static_assert(sizeof(struct g1_layout_find_type_cb_ctx__param_0225) >= 0x8, "g1_layout_find_type_cb_ctx__param_0225.size");

/* param_0226 | G1-original | Search/callback context used by find_type_cb: a type/index word, two lookup indices, and a write-only match flag. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_find_type_cb_ctx__param_0226 {
    uint8_t _pad_0x0[0x4];
    uint8_t type_or_key[0x4]; /* catalog type: uint32_t */
    uint8_t index_a[0x4]; /* catalog type: uint32_t */
    uint8_t index_b[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x1];
    uint8_t match_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_find_type_cb_ctx__param_0226, type_or_key) == 0x4, "g1_layout_find_type_cb_ctx__param_0226.type_or_key");
_Static_assert(offsetof(struct g1_layout_find_type_cb_ctx__param_0226, index_a) == 0x8, "g1_layout_find_type_cb_ctx__param_0226.index_a");
_Static_assert(offsetof(struct g1_layout_find_type_cb_ctx__param_0226, index_b) == 0xc, "g1_layout_find_type_cb_ctx__param_0226.index_b");
_Static_assert(offsetof(struct g1_layout_find_type_cb_ctx__param_0226, match_flag) == 0x11, "g1_layout_find_type_cb_ctx__param_0226.match_flag");
_Static_assert(sizeof(struct g1_layout_find_type_cb_ctx__param_0226) >= 0x15, "g1_layout_find_type_cb_ctx__param_0226.size");

/* param_0227 | library | Zephyr ATT channel object used by bt_att_chan_create_pdu (MTU fields near +0x1e/+0x2e, plus two words at struct tail). | D1+D2 verified
 * review: bt_att_chan is defined in Zephyr's private att_internal.h (not a public header in the pinned tree browsed); offsets not verified. Kept ground truth. */
struct __attribute__((packed)) g1_layout_bt_att_chan__param_0227 {
    uint8_t _pad_0x0[0x1e];
    uint8_t field_0x1e[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x20[0xe];
    uint8_t field_0x2e[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x30[0x114];
    uint8_t field_0x144[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x148[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0227, field_0x1e) == 0x1e, "g1_layout_bt_att_chan__param_0227.field_0x1e");
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0227, field_0x2e) == 0x2e, "g1_layout_bt_att_chan__param_0227.field_0x2e");
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0227, field_0x144) == 0x144, "g1_layout_bt_att_chan__param_0227.field_0x144");
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0227, field_0x148) == 0x148, "g1_layout_bt_att_chan__param_0227.field_0x148");
_Static_assert(sizeof(struct g1_layout_bt_att_chan__param_0227) >= 0x14c, "g1_layout_bt_att_chan__param_0227.size");

/* param_0228 | library | ATT Read-By-Type/Group iteration context shared by read_group_cb and att_read_type_iter_cb during ATT response building. | D1+D2 verified
 * review: File-local iterator struct in subsys/bluetooth/host/att.c — no public header. is_union=true: 0x4 is read width 4 over a gap of 1 (overlaps 0x5). library_verified=false. */
struct __attribute__((packed)) g1_layout_bt_att_read_group_data__param_0228 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x3];
    uint8_t field_0x4[0x1]; /* catalog type: uint32_t */
    uint8_t field_0x5[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x6[0x2];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_att_read_group_data__param_0228, field_0x0) == 0x0, "g1_layout_bt_att_read_group_data__param_0228.field_0x0");
_Static_assert(offsetof(struct g1_layout_bt_att_read_group_data__param_0228, field_0x4) == 0x4, "g1_layout_bt_att_read_group_data__param_0228.field_0x4");
_Static_assert(offsetof(struct g1_layout_bt_att_read_group_data__param_0228, field_0x5) == 0x5, "g1_layout_bt_att_read_group_data__param_0228.field_0x5");
_Static_assert(offsetof(struct g1_layout_bt_att_read_group_data__param_0228, field_0x8) == 0x8, "g1_layout_bt_att_read_group_data__param_0228.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_att_read_group_data__param_0228, field_0xc) == 0xc, "g1_layout_bt_att_read_group_data__param_0228.field_0xc");
_Static_assert(offsetof(struct g1_layout_bt_att_read_group_data__param_0228, field_0x10) == 0x10, "g1_layout_bt_att_read_group_data__param_0228.field_0x10");
_Static_assert(sizeof(struct g1_layout_bt_att_read_group_data__param_0228) >= 0x14, "g1_layout_bt_att_read_group_data__param_0228.size");

/* param_0229 | library | Bluetooth ATT channel context (MTU/CID + pending-request bookkeeping) used by att_chan_send/chan_req_send. | D1+D2 verified
 * review: BLE ATT internal channel struct (host att.c); offsets not verified against a header. */
struct __attribute__((packed)) g1_layout_bt_att_chan__param_0229 {
    uint8_t _pad_0x0[0x1e];
    uint8_t mtu_or_cid_a[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x20[0xe];
    uint8_t mtu_or_cid_b[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x30[0xf0];
    uint8_t req_state[0x4]; /* catalog type: uint32_t */
    uint8_t req_extra[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0229, mtu_or_cid_a) == 0x1e, "g1_layout_bt_att_chan__param_0229.mtu_or_cid_a");
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0229, mtu_or_cid_b) == 0x2e, "g1_layout_bt_att_chan__param_0229.mtu_or_cid_b");
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0229, req_state) == 0x120, "g1_layout_bt_att_chan__param_0229.req_state");
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0229, req_extra) == 0x124, "g1_layout_bt_att_chan__param_0229.req_extra");
_Static_assert(sizeof(struct g1_layout_bt_att_chan__param_0229) >= 0x128, "g1_layout_bt_att_chan__param_0229.size");

/* param_0234 | library | BLE ATT channel exposing rx/tx MTU fields, used by MTU exchange and response-PDU creation. | D1+D2 verified
 * review: bt_att_chan is defined in host/att.c (private); 0x1e/0x2e MTU offsets unverifiable against a header. verified=false. */
struct __attribute__((packed)) g1_layout_bt_att_chan__param_0234 {
    uint8_t _pad_0x0[0x1e];
    uint8_t rx_mtu[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x20[0xe];
    uint8_t tx_mtu[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0234, rx_mtu) == 0x1e, "g1_layout_bt_att_chan__param_0234.rx_mtu");
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0234, tx_mtu) == 0x2e, "g1_layout_bt_att_chan__param_0234.tx_mtu");
_Static_assert(sizeof(struct g1_layout_bt_att_chan__param_0234) >= 0x30, "g1_layout_bt_att_chan__param_0234.size");

/* param_0236 | library | param_2 of att_prepare_write_req: ATT prepare-write buffer/PDU view (length word + handle short). | D1+D2 verified
 * review: Only 2 fields; possibly a net_buf view but not verifiable. */
struct __attribute__((packed)) g1_layout_att_pdu_buf_view__param_0236 {
    uint8_t _pad_0x0[0xc];
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_att_pdu_buf_view__param_0236, field_0xc) == 0xc, "g1_layout_att_pdu_buf_view__param_0236.field_0xc");
_Static_assert(offsetof(struct g1_layout_att_pdu_buf_view__param_0236, field_0x10) == 0x10, "g1_layout_att_pdu_buf_view__param_0236.field_0x10");
_Static_assert(sizeof(struct g1_layout_att_pdu_buf_view__param_0236) >= 0x14, "g1_layout_att_pdu_buf_view__param_0236.size");

/* param_0241 | library | Zephyr ATT Find-By-Type-Value request PDU fields parsed by att_find_type_req. | D1+D2 verified
 * review: Only two sparse fields (0xc,0x10) recovered; not enough to confirm the packed ATT PDU layout, so library_verified=false. */
struct __attribute__((packed)) g1_layout_bt_att_find_type_req__param_0241 {
    uint8_t _pad_0x0[0xc];
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_bt_att_find_type_req__param_0241, field_0xc) == 0xc, "g1_layout_bt_att_find_type_req__param_0241.field_0xc");
_Static_assert(offsetof(struct g1_layout_bt_att_find_type_req__param_0241, field_0x10) == 0x10, "g1_layout_bt_att_find_type_req__param_0241.field_0x10");
_Static_assert(sizeof(struct g1_layout_bt_att_find_type_req__param_0241) >= 0x14, "g1_layout_bt_att_find_type_req__param_0241.size");

/* param_0245 | library | Object passed to gatt_ccc_write_store_cb during CCC settings persistence: a value word at 0x8 and a flags word at 0xc. | D1+D2 verified
 * review: Only two fields observed; not enough to pin against bt_gatt_ccc_cfg/_bt_gatt_ccc offsets. library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_gatt_ccc_store_ctx__param_0245 {
    uint8_t _pad_0x0[0x8];
    uint8_t ccc_value[0x4]; /* catalog type: int32_t */
    uint8_t ccc_flags[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_ccc_store_ctx__param_0245, ccc_value) == 0x8, "g1_layout_gatt_ccc_store_ctx__param_0245.ccc_value");
_Static_assert(offsetof(struct g1_layout_gatt_ccc_store_ctx__param_0245, ccc_flags) == 0xc, "g1_layout_gatt_ccc_store_ctx__param_0245.ccc_flags");
_Static_assert(sizeof(struct g1_layout_gatt_ccc_store_ctx__param_0245) >= 0x10, "g1_layout_gatt_ccc_store_ctx__param_0245.size");

/* param_0246 | library | GATT CCC (client characteristic configuration) entry passed to gatt_ccc_write_store_cb. | D1+D2 verified
 * review: Library id kept but not verified against gatt header. is_union=true: 0x0 accessed 2-wide over 1-byte gap to 0x1. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_gatt_ccc_cfg__param_0246 {
    uint8_t value_or_flags[0x1]; /* catalog type: uint16_t */
    uint8_t field_0x1[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x6];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_ccc_cfg__param_0246, value_or_flags) == 0x0, "g1_layout_gatt_ccc_cfg__param_0246.value_or_flags");
_Static_assert(offsetof(struct g1_layout_gatt_ccc_cfg__param_0246, field_0x1) == 0x1, "g1_layout_gatt_ccc_cfg__param_0246.field_0x1");
_Static_assert(offsetof(struct g1_layout_gatt_ccc_cfg__param_0246, field_0x8) == 0x8, "g1_layout_gatt_ccc_cfg__param_0246.field_0x8");
_Static_assert(offsetof(struct g1_layout_gatt_ccc_cfg__param_0246, field_0xc) == 0xc, "g1_layout_gatt_ccc_cfg__param_0246.field_0xc");
_Static_assert(sizeof(struct g1_layout_gatt_ccc_cfg__param_0246) >= 0x10, "g1_layout_gatt_ccc_cfg__param_0246.size");

/* param_0247 | G1-original | Linked-list node with a refcount/flags word and next pointer, used by gatt_sub_free and list_unlink_and_release. | D1+D2 verified
 * review: G1-original list node (both callees are application-class despite gatt prefix). */
struct __attribute__((packed)) g1_layout_refcounted_list_node__param_0247 {
    uint8_t _pad_0x0[0x8];
    uint8_t ref_count_or_flags[0x4]; /* catalog type: int32_t */
    uint8_t next[0x4]; /* catalog type: void* */
};
_Static_assert(offsetof(struct g1_layout_refcounted_list_node__param_0247, ref_count_or_flags) == 0x8, "g1_layout_refcounted_list_node__param_0247.ref_count_or_flags");
_Static_assert(offsetof(struct g1_layout_refcounted_list_node__param_0247, next) == 0xc, "g1_layout_refcounted_list_node__param_0247.next");
_Static_assert(sizeof(struct g1_layout_refcounted_list_node__param_0247) >= 0x10, "g1_layout_refcounted_list_node__param_0247.size");

/* param_0248 | library | Zephyr Bluetooth connection object shared across GATT service-change/CCC/indicate/notify and library bt_conn_* helpers; assorted flag bytes plus an int at 0xc0. | D1+D2 verified
 * review: Strongly confirmed as bt_conn (9 accessors incl. library bt_conn_ltk_present/is_peer_addr_le/bt_gatt_check_perm). bt_conn layout is config-dependent (SMP/BR/etc.) so exact member offsets can't be pinned from the header without the matching build config; library_verified=false. Offsets unchanged; field 0xc0 matches param_0585's 0xc0. */
struct __attribute__((packed)) g1_layout_bt_conn__param_0248 {
    uint8_t _pad_0x0[0x3];
    uint8_t field_0x3[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x9[0x2];
    uint8_t field_0xb[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xc[0x1];
    uint8_t field_0xd[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xe[0xb2];
    uint8_t field_0xc0[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0248, field_0x3) == 0x3, "g1_layout_bt_conn__param_0248.field_0x3");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0248, field_0x8) == 0x8, "g1_layout_bt_conn__param_0248.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0248, field_0xb) == 0xb, "g1_layout_bt_conn__param_0248.field_0xb");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0248, field_0xd) == 0xd, "g1_layout_bt_conn__param_0248.field_0xd");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0248, field_0xc0) == 0xc0, "g1_layout_bt_conn__param_0248.field_0xc0");
_Static_assert(sizeof(struct g1_layout_bt_conn__param_0248) >= 0xc4, "g1_layout_bt_conn__param_0248.size");

/* param_0249 | library | Internal GATT CCC/list node shared by gatt_write_ccc_rsp and list_unlink_and_release (handle + value + link fields). | D1+D2 verified
 * review: Internal (non-public) GATT structure; cannot verify offsets. 0x4 read as short and word. Kept offsets. */
struct __attribute__((packed)) g1_layout_gatt_ccc_list_node__param_0249 {
    uint8_t _pad_0x0[0x4];
    uint8_t handle[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0xc];
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_ccc_list_node__param_0249, handle) == 0x4, "g1_layout_gatt_ccc_list_node__param_0249.handle");
_Static_assert(offsetof(struct g1_layout_gatt_ccc_list_node__param_0249, field_0x8) == 0x8, "g1_layout_gatt_ccc_list_node__param_0249.field_0x8");
_Static_assert(offsetof(struct g1_layout_gatt_ccc_list_node__param_0249, field_0x18) == 0x18, "g1_layout_gatt_ccc_list_node__param_0249.field_0x18");
_Static_assert(sizeof(struct g1_layout_gatt_ccc_list_node__param_0249) >= 0x1c, "g1_layout_gatt_ccc_list_node__param_0249.size");

/* param_0250 | library | GATT client-features CCC/config record cleared by gatt_cf_cfg_clear: a valid flag and a features bitmap. | D1+D2 verified
 * review: bt_gatt_cf_cfg is a file-local struct in subsys/bluetooth/host/gatt.c; consistent with clear-on-disconnect but offsets unverified. */
struct __attribute__((packed)) g1_layout_bt_gatt_cf_cfg__param_0250 {
    uint8_t _pad_0x0[0x8];
    uint8_t valid_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x9[0x3];
    uint8_t features_bitmap[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_cf_cfg__param_0250, valid_flag) == 0x8, "g1_layout_bt_gatt_cf_cfg__param_0250.valid_flag");
_Static_assert(offsetof(struct g1_layout_bt_gatt_cf_cfg__param_0250, features_bitmap) == 0xc, "g1_layout_bt_gatt_cf_cfg__param_0250.features_bitmap");
_Static_assert(sizeof(struct g1_layout_bt_gatt_cf_cfg__param_0250) >= 0x10, "g1_layout_bt_gatt_cf_cfg__param_0250.size");

/* param_0251 | library | GATT attribute-like record (handle/id + linked ptr) scanned by gatt_remove_peer_from_attr. | D1+D2 verified
 * review: BLE GATT record; only 0x8/0xc observed, not verified. */
struct __attribute__((packed)) g1_layout_gatt_attr_record__param_0251 {
    uint8_t _pad_0x0[0x8];
    uint8_t attr_handle[0x4]; /* catalog type: uint32_t */
    uint8_t next_or_user_data[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_gatt_attr_record__param_0251, attr_handle) == 0x8, "g1_layout_gatt_attr_record__param_0251.attr_handle");
_Static_assert(offsetof(struct g1_layout_gatt_attr_record__param_0251, next_or_user_data) == 0xc, "g1_layout_gatt_attr_record__param_0251.next_or_user_data");
_Static_assert(sizeof(struct g1_layout_gatt_attr_record__param_0251) >= 0x10, "g1_layout_gatt_attr_record__param_0251.size");

/* param_0252 | library | GATT attribute descriptor passed to bt_gatt_check_perm and CCC write/restore/update paths (uuid/read/write/user_data/handle/perm). | D1+D2 verified
 * review: VERIFIED against gatt.h: uuid@0x0, read@0x4, write@0x8, user_data@0xc, handle@0x10(u16), perm@0x12(u16). Observed 0x4/0x8/0xc/0x12 all match. Corrected sonnet's int type at 0x4 to the read callback pointer. */
struct __attribute__((packed)) g1_layout_bt_gatt_attr__param_0252 {
    uint8_t _pad_0x0[0x4];
    uint8_t read[0x4]; /* catalog type: bt_gatt_attr_read_func_t; SDK member: read */
    uint8_t write[0x4]; /* catalog type: bt_gatt_attr_write_func_t; SDK member: write */
    uint8_t user_data[0x4]; /* catalog type: void *; SDK member: user_data */
    uint8_t _pad_0x10[0x2];
    uint8_t perm[0x2]; /* catalog type: uint16_t; SDK member: perm */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_attr__param_0252, read) == 0x4, "g1_layout_bt_gatt_attr__param_0252.read");
_Static_assert(offsetof(struct g1_layout_bt_gatt_attr__param_0252, write) == 0x8, "g1_layout_bt_gatt_attr__param_0252.write");
_Static_assert(offsetof(struct g1_layout_bt_gatt_attr__param_0252, user_data) == 0xc, "g1_layout_bt_gatt_attr__param_0252.user_data");
_Static_assert(offsetof(struct g1_layout_bt_gatt_attr__param_0252, perm) == 0x12, "g1_layout_bt_gatt_attr__param_0252.perm");
_Static_assert(sizeof(struct g1_layout_bt_gatt_attr__param_0252) >= 0x16, "g1_layout_bt_gatt_attr__param_0252.size");

/* param_0255 | library | Zephyr GATT attribute descriptor read by bt_gatt_attr_get_handle / bt_gatt_attr_value_handle: user_data pointer and 16-bit handle. | D1+D2 verified
 * review: Verified against gatt.h: uuid@0, read@4, write@8, user_data@0xc, handle@0x10, perm@0x12. Observed user_data@0xc and handle@0x10 match exactly. */
struct __attribute__((packed)) g1_layout_bt_gatt_attr__param_0255 {
    uint8_t _pad_0x0[0xc];
    uint8_t user_data[0x4]; /* catalog type: void *; SDK member: user_data */
    uint8_t handle[0x2]; /* catalog type: uint16_t; SDK member: handle */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_attr__param_0255, user_data) == 0xc, "g1_layout_bt_gatt_attr__param_0255.user_data");
_Static_assert(offsetof(struct g1_layout_bt_gatt_attr__param_0255, handle) == 0x10, "g1_layout_bt_gatt_attr__param_0255.handle");
_Static_assert(sizeof(struct g1_layout_bt_gatt_attr__param_0255) >= 0x14, "g1_layout_bt_gatt_attr__param_0255.size");

/* param_0257 | library | Zephyr GATT indicate parameters used by gatt_indicate / bt_gatt_indicate: attribute pointer, callback/destroy slot, data length and a type byte. | D1+D2 verified
 * review: Field set is consistent with bt_gatt_indicate_params but exact member offsets were not checked against gatt.h, so library_verified=false. */
struct __attribute__((packed)) g1_layout_bt_gatt_indicate_params__param_0257 {
    uint8_t _pad_0x0[0x4];
    uint8_t attr[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0x8];
    uint8_t func_or_destroy[0x4]; /* catalog type: uint32_t */
    uint8_t len[0x2]; /* catalog type: uint16_t */
    uint8_t type[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_indicate_params__param_0257, attr) == 0x4, "g1_layout_bt_gatt_indicate_params__param_0257.attr");
_Static_assert(offsetof(struct g1_layout_bt_gatt_indicate_params__param_0257, func_or_destroy) == 0x10, "g1_layout_bt_gatt_indicate_params__param_0257.func_or_destroy");
_Static_assert(offsetof(struct g1_layout_bt_gatt_indicate_params__param_0257, len) == 0x14, "g1_layout_bt_gatt_indicate_params__param_0257.len");
_Static_assert(offsetof(struct g1_layout_bt_gatt_indicate_params__param_0257, type) == 0x16, "g1_layout_bt_gatt_indicate_params__param_0257.type");
_Static_assert(sizeof(struct g1_layout_bt_gatt_indicate_params__param_0257) >= 0x1a, "g1_layout_bt_gatt_indicate_params__param_0257.size");

/* param_0259 | library | Zephyr GATT notify parameters used by gatt_notify/bt_gatt_notify_cb: uuid, attr, data, len, completion func, user_data. | D1+D2 verified
 * review: Verified against gatt.h: uuid@0x0, attr@0x4, data@0x8, len(uint16)@0xc, func@0x10, user_data@0x14. Observed reads at 0x4/0x8/0xc/0x10/0x14 match exactly (uuid@0x0 not read here, is the pad). */
struct __attribute__((packed)) g1_layout_bt_gatt_notify_params__param_0259 {
    uint8_t _pad_0x0[0x4];
    uint8_t attr[0x4]; /* catalog type: const struct bt_gatt_attr *; SDK member: attr */
    uint8_t data[0x4]; /* catalog type: const void *; SDK member: data */
    uint8_t len[0x2]; /* catalog type: uint16_t; SDK member: len */
    uint8_t _pad_0xe[0x2];
    uint8_t func[0x4]; /* catalog type: bt_gatt_complete_func_t; SDK member: func */
    uint8_t user_data[0x4]; /* catalog type: void *; SDK member: user_data */
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_notify_params__param_0259, attr) == 0x4, "g1_layout_bt_gatt_notify_params__param_0259.attr");
_Static_assert(offsetof(struct g1_layout_bt_gatt_notify_params__param_0259, data) == 0x8, "g1_layout_bt_gatt_notify_params__param_0259.data");
_Static_assert(offsetof(struct g1_layout_bt_gatt_notify_params__param_0259, len) == 0xc, "g1_layout_bt_gatt_notify_params__param_0259.len");
_Static_assert(offsetof(struct g1_layout_bt_gatt_notify_params__param_0259, func) == 0x10, "g1_layout_bt_gatt_notify_params__param_0259.func");
_Static_assert(offsetof(struct g1_layout_bt_gatt_notify_params__param_0259, user_data) == 0x14, "g1_layout_bt_gatt_notify_params__param_0259.user_data");
_Static_assert(sizeof(struct g1_layout_bt_gatt_notify_params__param_0259) >= 0x18, "g1_layout_bt_gatt_notify_params__param_0259.size");

/* param_0260 | library | CCC update context passed to gatt_send_ccc_update (handle/value pairs). | D1+D2 verified
 * review: Exact stock type not identifiable; kept as GATT CCC-related, unverified. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_gatt_ccc_update_ctx__param_0260 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x6[0x2];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xe[0x2];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_ccc_update_ctx__param_0260, field_0x4) == 0x4, "g1_layout_gatt_ccc_update_ctx__param_0260.field_0x4");
_Static_assert(offsetof(struct g1_layout_gatt_ccc_update_ctx__param_0260, field_0x8) == 0x8, "g1_layout_gatt_ccc_update_ctx__param_0260.field_0x8");
_Static_assert(offsetof(struct g1_layout_gatt_ccc_update_ctx__param_0260, field_0xc) == 0xc, "g1_layout_gatt_ccc_update_ctx__param_0260.field_0xc");
_Static_assert(offsetof(struct g1_layout_gatt_ccc_update_ctx__param_0260, field_0x10) == 0x10, "g1_layout_gatt_ccc_update_ctx__param_0260.field_0x10");
_Static_assert(sizeof(struct g1_layout_gatt_ccc_update_ctx__param_0260) >= 0x14, "g1_layout_gatt_ccc_update_ctx__param_0260.size");

/* param_0261 | library | Bluetooth ATT/GATT PDU buffer object shared across bt_gatt_discover/write, GATT response parsers, and l2cap_reassemble_frag; net_buf-like (vtable/data/len/size/flags) with mixed-width accesses. | D1+D2 verified
 * review: Multiple overlapping accesses (Ghidra flagged width>gap at 0x0/0x2/0x3/0x4/0x8/0xc) → is_union=true. Layout is net_buf-ish but not cleanly matched; kept faithful to observed offsets with generic names. */
struct __attribute__((packed)) g1_layout_bt_att_pdu_buf__param_0261 {
    uint8_t vtable_or_code[0x4]; /* catalog type: void* */
    uint8_t data[0x4]; /* catalog type: void* */
    uint8_t len[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xa[0x2];
    uint8_t handle_or_size[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xe[0x2];
    uint8_t flags[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_bt_att_pdu_buf__param_0261, vtable_or_code) == 0x0, "g1_layout_bt_att_pdu_buf__param_0261.vtable_or_code");
_Static_assert(offsetof(struct g1_layout_bt_att_pdu_buf__param_0261, data) == 0x4, "g1_layout_bt_att_pdu_buf__param_0261.data");
_Static_assert(offsetof(struct g1_layout_bt_att_pdu_buf__param_0261, len) == 0x8, "g1_layout_bt_att_pdu_buf__param_0261.len");
_Static_assert(offsetof(struct g1_layout_bt_att_pdu_buf__param_0261, handle_or_size) == 0xc, "g1_layout_bt_att_pdu_buf__param_0261.handle_or_size");
_Static_assert(offsetof(struct g1_layout_bt_att_pdu_buf__param_0261, flags) == 0x10, "g1_layout_bt_att_pdu_buf__param_0261.flags");
_Static_assert(sizeof(struct g1_layout_bt_att_pdu_buf__param_0261) >= 0x14, "g1_layout_bt_att_pdu_buf__param_0261.size");

/* param_0262 | library | Zephyr GATT subscribe-parameters object used by gatt_subscribe_add/bt_gatt_unsubscribe: value/CCC handles and callback/list fields. | D1+D2 verified
 * review: Header confirms bt_gatt_subscribe_params has value_handle@0xc(u16)+ccc_handle@0xe(u16), matching the observed 0xc/0xe pair (0xc is read as a 4-byte word spanning both handles -> is_union). But the observed u16 at 0x4 and word at 0x18 do not line up with notify/subscribe/write function pointers at 0x0/0x4/0x8, so the exact layout is config-dependent (CONFIG_BT_GATT_AUTO_DISCOVER_CCC); library_verified=false. */
struct __attribute__((packed)) g1_layout_bt_gatt_subscribe_params__param_0262 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x6[0x6];
    uint8_t value_handle[0x2]; /* catalog type: uint16_t; SDK member: value_handle */
    uint8_t ccc_handle[0x2]; /* catalog type: uint16_t; SDK member: ccc_handle */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x4];
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_subscribe_params__param_0262, field_0x4) == 0x4, "g1_layout_bt_gatt_subscribe_params__param_0262.field_0x4");
_Static_assert(offsetof(struct g1_layout_bt_gatt_subscribe_params__param_0262, value_handle) == 0xc, "g1_layout_bt_gatt_subscribe_params__param_0262.value_handle");
_Static_assert(offsetof(struct g1_layout_bt_gatt_subscribe_params__param_0262, ccc_handle) == 0xe, "g1_layout_bt_gatt_subscribe_params__param_0262.ccc_handle");
_Static_assert(offsetof(struct g1_layout_bt_gatt_subscribe_params__param_0262, field_0x10) == 0x10, "g1_layout_bt_gatt_subscribe_params__param_0262.field_0x10");
_Static_assert(offsetof(struct g1_layout_bt_gatt_subscribe_params__param_0262, field_0x18) == 0x18, "g1_layout_bt_gatt_subscribe_params__param_0262.field_0x18");
_Static_assert(sizeof(struct g1_layout_bt_gatt_subscribe_params__param_0262) >= 0x1c, "g1_layout_bt_gatt_subscribe_params__param_0262.size");

/* param_0263 | library | Zephyr GATT subscription parameters used by gatt_subscribe_add / bt_gatt_unsubscribe / gatt_mult_notify_dispatch. | D1+D2 verified
 * review: Confirmed struct via gatt.h (notify@0x0, subscribe@0x4, write@0x8, value_handle@0xc(u16), ccc_handle@0xe(u16)...). Observed accesses are byte-granular (0x8/0x9 within write ptr, 0xd within value_handle) and don't fall on clean member boundaries, so verified=false. */
struct __attribute__((packed)) g1_layout_bt_gatt_subscribe_params__param_0263 {
    uint8_t _pad_0x0[0x8];
    uint8_t field_0x8[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x9[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xa[0x3];
    uint8_t field_0xd[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_subscribe_params__param_0263, field_0x8) == 0x8, "g1_layout_bt_gatt_subscribe_params__param_0263.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_gatt_subscribe_params__param_0263, field_0x9) == 0x9, "g1_layout_bt_gatt_subscribe_params__param_0263.field_0x9");
_Static_assert(offsetof(struct g1_layout_bt_gatt_subscribe_params__param_0263, field_0xd) == 0xd, "g1_layout_bt_gatt_subscribe_params__param_0263.field_0xd");
_Static_assert(sizeof(struct g1_layout_bt_gatt_subscribe_params__param_0263) >= 0xe, "g1_layout_bt_gatt_subscribe_params__param_0263.size");

/* param_0265 | library | Zephyr Bluetooth SMP pairing context, shared across the whole SMP pairing state machine (pairing req/confirm/random, DHKey check, identity, error handling). | D1+D2 verified
 * review: Confidently bt_smp (14 smp_* members). Defined file-local in subsys/bluetooth/host/smp.c, so offsets can't be checked against a header (library_verified=false). is_union=true: layout notes flag overlapping wide/narrow accesses at 0xa, 0x11, 0x15, 0xe8. */
struct __attribute__((packed)) g1_layout_bt_smp__param_0265 {
    uint8_t _pad_0x0[0x2];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x1];
    uint8_t chan_or_conn[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x9[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xa[0x1]; /* catalog type: uint32_t */
    uint8_t field_0xb[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xc[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xd[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xe[0x2]; /* catalog type: uint16_t */
    uint8_t method[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x11[0x1]; /* catalog type: uint32_t */
    uint8_t field_0x12[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x13[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x14[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x15[0x1]; /* catalog type: uint16_t */
    uint8_t field_0x16[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x17[0x30];
    uint8_t key_byte_0[0x1]; /* catalog type: uint8_t */
    uint8_t key_byte_1[0x1]; /* catalog type: uint8_t */
    uint8_t key_byte_2[0x1]; /* catalog type: uint8_t */
    uint8_t key_byte_3[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x4b[0x8d];
    uint8_t field_0xd8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xdc[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xdd[0x3];
    uint8_t field_0xe0[0x4]; /* catalog type: void * */
    uint8_t field_0xe4[0x4]; /* catalog type: void * */
    uint8_t field_0xe8[0x1]; /* catalog type: uint16_t */
    uint8_t field_0xe9[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xea[0x6];
    uint8_t field_0xf0[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0x2) == 0x2, "g1_layout_bt_smp__param_0265.field_0x2");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, chan_or_conn) == 0x4, "g1_layout_bt_smp__param_0265.chan_or_conn");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0x8) == 0x8, "g1_layout_bt_smp__param_0265.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0x9) == 0x9, "g1_layout_bt_smp__param_0265.field_0x9");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0xa) == 0xa, "g1_layout_bt_smp__param_0265.field_0xa");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0xb) == 0xb, "g1_layout_bt_smp__param_0265.field_0xb");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0xc) == 0xc, "g1_layout_bt_smp__param_0265.field_0xc");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0xd) == 0xd, "g1_layout_bt_smp__param_0265.field_0xd");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0xe) == 0xe, "g1_layout_bt_smp__param_0265.field_0xe");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, method) == 0x10, "g1_layout_bt_smp__param_0265.method");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0x11) == 0x11, "g1_layout_bt_smp__param_0265.field_0x11");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0x12) == 0x12, "g1_layout_bt_smp__param_0265.field_0x12");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0x13) == 0x13, "g1_layout_bt_smp__param_0265.field_0x13");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0x14) == 0x14, "g1_layout_bt_smp__param_0265.field_0x14");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0x15) == 0x15, "g1_layout_bt_smp__param_0265.field_0x15");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0x16) == 0x16, "g1_layout_bt_smp__param_0265.field_0x16");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, key_byte_0) == 0x47, "g1_layout_bt_smp__param_0265.key_byte_0");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, key_byte_1) == 0x48, "g1_layout_bt_smp__param_0265.key_byte_1");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, key_byte_2) == 0x49, "g1_layout_bt_smp__param_0265.key_byte_2");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, key_byte_3) == 0x4a, "g1_layout_bt_smp__param_0265.key_byte_3");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0xd8) == 0xd8, "g1_layout_bt_smp__param_0265.field_0xd8");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0xdc) == 0xdc, "g1_layout_bt_smp__param_0265.field_0xdc");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0xe0) == 0xe0, "g1_layout_bt_smp__param_0265.field_0xe0");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0xe4) == 0xe4, "g1_layout_bt_smp__param_0265.field_0xe4");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0xe8) == 0xe8, "g1_layout_bt_smp__param_0265.field_0xe8");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0xe9) == 0xe9, "g1_layout_bt_smp__param_0265.field_0xe9");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0265, field_0xf0) == 0xf0, "g1_layout_bt_smp__param_0265.field_0xf0");
_Static_assert(sizeof(struct g1_layout_bt_smp__param_0265) >= 0xf4, "g1_layout_bt_smp__param_0265.size");

/* param_0272 | library | Bluetooth SMP pairing state machine object (~0xc4+) accessed by smp_alloc_pairing_keys. | D1+D2 verified
 * review: BLE SMP internal (host smp.c); only a flags byte (0x8) and a tail word (0xc0) observed, unverified. */
struct __attribute__((packed)) g1_layout_bt_smp__param_0272 {
    uint8_t _pad_0x0[0x8];
    uint8_t pairing_flags[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x9[0xb7];
    uint8_t keys_or_state[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0272, pairing_flags) == 0x8, "g1_layout_bt_smp__param_0272.pairing_flags");
_Static_assert(offsetof(struct g1_layout_bt_smp__param_0272, keys_or_state) == 0xc0, "g1_layout_bt_smp__param_0272.keys_or_state");
_Static_assert(sizeof(struct g1_layout_bt_smp__param_0272) >= 0xc4, "g1_layout_bt_smp__param_0272.size");

/* param_0273 | library | bt_conn subset read during bt_keys pool lookup (handle + id used to match keys). | D1+D2 verified
 * review: bt_conn internal; 0x1/0x6 offsets unverifiable against a header. verified=false. */
struct __attribute__((packed)) g1_layout_bt_conn_keys_ctx__param_0273 {
    uint8_t _pad_0x0[0x1];
    uint8_t conn_handle[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x3[0x3];
    uint8_t id[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_bt_conn_keys_ctx__param_0273, conn_handle) == 0x1, "g1_layout_bt_conn_keys_ctx__param_0273.conn_handle");
_Static_assert(offsetof(struct g1_layout_bt_conn_keys_ctx__param_0273, id) == 0x6, "g1_layout_bt_conn_keys_ctx__param_0273.id");
_Static_assert(sizeof(struct g1_layout_bt_conn_keys_ctx__param_0273) >= 0x8, "g1_layout_bt_conn_keys_ctx__param_0273.size");

/* param_0274 | library | param_2 of bt_keys_find_irk: partial bt_keys record scanned during IRK match. | D1+D2 verified
 * review: Unaligned partial reads (0x1,0x5,0x18); bt_keys layout config-dependent, not verified. */
struct __attribute__((packed)) g1_layout_bt_keys_irk_lookup_view__param_0274 {
    uint8_t _pad_0x0[0x1];
    uint8_t field_0x1[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x5[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x7[0x11];
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_keys_irk_lookup_view__param_0274, field_0x1) == 0x1, "g1_layout_bt_keys_irk_lookup_view__param_0274.field_0x1");
_Static_assert(offsetof(struct g1_layout_bt_keys_irk_lookup_view__param_0274, field_0x5) == 0x5, "g1_layout_bt_keys_irk_lookup_view__param_0274.field_0x5");
_Static_assert(offsetof(struct g1_layout_bt_keys_irk_lookup_view__param_0274, field_0x18) == 0x18, "g1_layout_bt_keys_irk_lookup_view__param_0274.field_0x18");
_Static_assert(sizeof(struct g1_layout_bt_keys_irk_lookup_view__param_0274) >= 0x1c, "g1_layout_bt_keys_irk_lookup_view__param_0274.size");

/* param_0276 | library | Zephyr net_buf network buffer manipulated by net_buf_reset and wrapped by cbor_nb_writer_init for CBOR encoding. | D1+D2 verified
 * review: VERIFIED against net/buf.h. node@0(4B), frags@4, ref@8, flags@9, pool_id@a, user_data_size@b, then union{ data@c, len@10, size@12, __buf@14 }. CORRECTED sonnet field mapping (was shifted): 0x4=frags not ref, 0xc=data not len, 0x10=len not size, 0x14=__buf not data. */
struct __attribute__((packed)) g1_layout_net_buf__param_0276 {
    uint8_t _pad_0x0[0x4];
    uint8_t frags[0x4]; /* catalog type: struct net_buf *; SDK member: frags */
    uint8_t _pad_0x8[0x1];
    uint8_t flags[0x1]; /* catalog type: uint8_t; SDK member: flags */
    uint8_t _pad_0xa[0x2];
    uint8_t data[0x4]; /* catalog type: uint8_t *; SDK member: data */
    uint8_t len[0x2]; /* catalog type: uint16_t; SDK member: len */
    uint8_t _pad_0x12[0x2];
    uint8_t __buf[0x4]; /* catalog type: uint8_t *; SDK member: __buf */
};
_Static_assert(offsetof(struct g1_layout_net_buf__param_0276, frags) == 0x4, "g1_layout_net_buf__param_0276.frags");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0276, flags) == 0x9, "g1_layout_net_buf__param_0276.flags");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0276, data) == 0xc, "g1_layout_net_buf__param_0276.data");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0276, len) == 0x10, "g1_layout_net_buf__param_0276.len");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0276, __buf) == 0x14, "g1_layout_net_buf__param_0276.__buf");
_Static_assert(sizeof(struct g1_layout_net_buf__param_0276) >= 0x18, "g1_layout_net_buf__param_0276.size");

/* param_0277 | library | Zephyr net_buf pool descriptor used by net_buf_alloc_len / net_buf_pool_get / bt_conn_alloc_pdu_buf to allocate ACL/PDU buffers: buffer count, uninit/avail counts, pool id, alloc callback, flags. | D1+D2 verified
 * review: Field roles (buf_count, uninit_count/avail_count pair, pool_id, alloc cb, flags) match net_buf_pool semantics but exact member offsets were not byte-verified against buf.h in this pass; library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_net_buf_pool__param_0277 {
    uint8_t _pad_0x0[0x4];
    uint8_t buf_count[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x18];
    uint8_t uninit_count[0x2]; /* catalog type: uint16_t */
    uint8_t avail_count[0x2]; /* catalog type: uint16_t */
    uint8_t pool_id[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x25[0x7];
    uint8_t alloc_cb_or_data[0x4]; /* catalog type: void * */
    uint8_t pool_flags[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_net_buf_pool__param_0277, buf_count) == 0x4, "g1_layout_net_buf_pool__param_0277.buf_count");
_Static_assert(offsetof(struct g1_layout_net_buf_pool__param_0277, uninit_count) == 0x20, "g1_layout_net_buf_pool__param_0277.uninit_count");
_Static_assert(offsetof(struct g1_layout_net_buf_pool__param_0277, avail_count) == 0x22, "g1_layout_net_buf_pool__param_0277.avail_count");
_Static_assert(offsetof(struct g1_layout_net_buf_pool__param_0277, pool_id) == 0x24, "g1_layout_net_buf_pool__param_0277.pool_id");
_Static_assert(offsetof(struct g1_layout_net_buf_pool__param_0277, alloc_cb_or_data) == 0x2c, "g1_layout_net_buf_pool__param_0277.alloc_cb_or_data");
_Static_assert(offsetof(struct g1_layout_net_buf_pool__param_0277, pool_flags) == 0x30, "g1_layout_net_buf_pool__param_0277.pool_flags");
_Static_assert(sizeof(struct g1_layout_net_buf_pool__param_0277) >= 0x34, "g1_layout_net_buf_pool__param_0277.size");

/* param_0278 | library | Zephyr singly-linked-list head passed to net_buf_slist_put (head/tail pointers). | D1+D2 verified
 * review: Corrected sonnet 'sys_snode_t' to sys_slist_t: net_buf_slist_put takes a list head. Observed 0x0/0x4 match the canonical sys_slist_t {head,tail} two-pointer layout, but header not opened so library_verified=false. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_sys_slist__param_0278 {
    uint8_t head[0x4]; /* catalog type: void * */
    uint8_t tail[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_sys_slist__param_0278, head) == 0x0, "g1_layout_sys_slist__param_0278.head");
_Static_assert(offsetof(struct g1_layout_sys_slist__param_0278, tail) == 0x4, "g1_layout_sys_slist__param_0278.tail");
_Static_assert(sizeof(struct g1_layout_sys_slist__param_0278) >= 0x8, "g1_layout_sys_slist__param_0278.size");

/* param_0280 | library | Zephyr net_buf network buffer (fragment chain) used by net_buf_frag_last/append_bytes/frags_len and att_chan_read. | D1+D2 verified
 * review: Offsets match net_buf: node(sys_snode_t)@0x0, frags@0x4, ref@0x8, flags@0x9, pool_id@0xa, then net_buf_simple union (data@0xc, len@0x10). Observed frags@0x4, pool_id@0xa, len@0x10 all line up. */
struct __attribute__((packed)) g1_layout_net_buf__param_0280 {
    uint8_t _pad_0x0[0x4];
    uint8_t frags[0x4]; /* catalog type: struct net_buf*; SDK member: frags */
    uint8_t _pad_0x8[0x2];
    uint8_t pool_id[0x1]; /* catalog type: uint8_t; SDK member: pool_id */
    uint8_t _pad_0xb[0x5];
    uint8_t len[0x2]; /* catalog type: uint16_t; SDK member: len (net_buf_simple) */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_net_buf__param_0280, frags) == 0x4, "g1_layout_net_buf__param_0280.frags");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0280, pool_id) == 0xa, "g1_layout_net_buf__param_0280.pool_id");
_Static_assert(offsetof(struct g1_layout_net_buf__param_0280, len) == 0x10, "g1_layout_net_buf__param_0280.len");
_Static_assert(sizeof(struct g1_layout_net_buf__param_0280) >= 0x14, "g1_layout_net_buf__param_0280.size");

/* param_0284 | library | Zephyr net_buf_simple descriptor manipulated by net_buf_simple_reserve. | D1+D2 verified
 * review: Verified against buf.h: net_buf_simple = { uint8* data@0; uint16 len@4; uint16 size@6; uint8* __buf@8 }. Observed 0x4 (len, read as a 4-byte word covering len+size) and 0x8 (__buf). Corrected sonnet which called 0x8 'size' — size is at 0x6 and 0x8 is __buf. */
struct __attribute__((packed)) g1_layout_net_buf_simple__param_0284 {
    uint8_t _pad_0x0[0x4];
    uint8_t len[0x2]; /* catalog type: uint16_t; SDK member: len */
    uint8_t _pad_0x6[0x2];
    uint8_t __buf[0x4]; /* catalog type: uint8_t*; SDK member: __buf */
};
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0284, len) == 0x4, "g1_layout_net_buf_simple__param_0284.len");
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0284, __buf) == 0x8, "g1_layout_net_buf_simple__param_0284.__buf");
_Static_assert(sizeof(struct g1_layout_net_buf_simple__param_0284) >= 0xc, "g1_layout_net_buf_simple__param_0284.size");

/* param_0285 | library | Zephyr net_buf_simple passed to net_buf_simple_push (data pointer / len / size / __buf). | D1+D2 verified
 * review: Real layout (buf.h): data@0x0(ptr), len@0x4(u16), size@0x6(u16), __buf@0x8(ptr). Observed offsets (0x1 sz2 write, 0x4 word read, 0x8 word read) do NOT line up cleanly with these members (esp. the 0x1 write), so verified=false. Corrected sonnet's len@0x1 label. Offsets kept. */
struct __attribute__((packed)) g1_layout_net_buf_simple__param_0285 {
    uint8_t _pad_0x0[0x1];
    uint8_t field_0x1[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x3[0x1];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t; SDK member: __buf */
};
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0285, field_0x1) == 0x1, "g1_layout_net_buf_simple__param_0285.field_0x1");
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0285, field_0x4) == 0x4, "g1_layout_net_buf_simple__param_0285.field_0x4");
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0285, field_0x8) == 0x8, "g1_layout_net_buf_simple__param_0285.field_0x8");
_Static_assert(sizeof(struct g1_layout_net_buf_simple__param_0285) >= 0xc, "g1_layout_net_buf_simple__param_0285.size");

/* param_0290 | library | ADC channel configuration descriptor passed as the cfg argument to adc_channel_config (gain/reference/acquisition-time/channel/inputs). | D1+D2 verified
 * review: param_2 of adc_channel_config should be struct adc_channel_cfg. Only acquisition_time@0x2 (uint16) lines up with the real header (with -fshort-enums: gain@0x0, reference@0x1, acquisition_time@0x2). The idx4 reads Ghidra placed at 0x10/0x14/0x18 exceed the real <8-byte struct, so those are almost certainly mis-analysis — library_verified=false, offsets left exactly as ground truth. */
struct __attribute__((packed)) g1_layout_adc_channel_cfg__param_0290 {
    uint8_t _pad_0x0[0x2];
    uint8_t acquisition_time[0x2]; /* catalog type: uint16_t; SDK member: acquisition_time */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_adc_channel_cfg__param_0290, acquisition_time) == 0x2, "g1_layout_adc_channel_cfg__param_0290.acquisition_time");
_Static_assert(offsetof(struct g1_layout_adc_channel_cfg__param_0290, field_0x4) == 0x4, "g1_layout_adc_channel_cfg__param_0290.field_0x4");
_Static_assert(offsetof(struct g1_layout_adc_channel_cfg__param_0290, field_0x10) == 0x10, "g1_layout_adc_channel_cfg__param_0290.field_0x10");
_Static_assert(offsetof(struct g1_layout_adc_channel_cfg__param_0290, field_0x14) == 0x14, "g1_layout_adc_channel_cfg__param_0290.field_0x14");
_Static_assert(offsetof(struct g1_layout_adc_channel_cfg__param_0290, field_0x18) == 0x18, "g1_layout_adc_channel_cfg__param_0290.field_0x18");
_Static_assert(sizeof(struct g1_layout_adc_channel_cfg__param_0290) >= 0x1c, "g1_layout_adc_channel_cfg__param_0290.size");

/* param_0292 | G1-original | PDM microphone-stream state flags checked/set by pdm_start_and_check. | D1+D2 verified
 * review: Ground-truth hint marks this G1-original (app wrapper pdm_start_and_check), so kept as app struct rather than sonnet's nrfx_pdm_cb_t. Started flag at 0x14, error flag at 0x51. */
struct __attribute__((packed)) g1_layout_pdm_start_state__param_0292 {
    uint8_t _pad_0x0[0x14];
    uint8_t started_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x15[0x3c];
    uint8_t error_flag[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_pdm_start_state__param_0292, started_flag) == 0x14, "g1_layout_pdm_start_state__param_0292.started_flag");
_Static_assert(offsetof(struct g1_layout_pdm_start_state__param_0292, error_flag) == 0x51, "g1_layout_pdm_start_state__param_0292.error_flag");
_Static_assert(sizeof(struct g1_layout_pdm_start_state__param_0292) >= 0x52, "g1_layout_pdm_start_state__param_0292.size");

/* param_0294 | G1-original | PDM clock/init configuration consumed by pdm_configure_clock_and_init (clock handler ptr + freq/mode word). | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_pdm_clock_config__param_0294 {
    uint8_t _pad_0x0[0x4];
    uint8_t clock_handler[0x4]; /* catalog type: void* */
    uint8_t _pad_0x8[0x8];
    uint8_t clock_freq_or_mode[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_pdm_clock_config__param_0294, clock_handler) == 0x4, "g1_layout_pdm_clock_config__param_0294.clock_handler");
_Static_assert(offsetof(struct g1_layout_pdm_clock_config__param_0294, clock_freq_or_mode) == 0x10, "g1_layout_pdm_clock_config__param_0294.clock_freq_or_mode");
_Static_assert(sizeof(struct g1_layout_pdm_clock_config__param_0294) >= 0x14, "g1_layout_pdm_clock_config__param_0294.size");

/* param_0295 | G1-original | param_2 of pdm_configure_clock_and_init: G1 PDM mic config (pin/clock word + config words for mode/edge/gain), later translated into nrfx_pdm calls. | D1+D2 verified
 * review: Corrected sonnet is_library=true: real nrfx_pdm_config_t uses different (byte-packed) field placement; observed word-per-field layout is a G1 wrapper config. 0x24 read wider than gap -> union. */
struct __attribute__((packed)) g1_layout_pdm_config_g1__param_0295 {
    uint8_t _pad_0x0[0x4];
    uint8_t pin_clk[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t pin_din[0x4]; /* catalog type: uint32_t */
    uint8_t mode[0x4]; /* catalog type: uint32_t */
    uint8_t edge[0x4]; /* catalog type: uint32_t */
    uint8_t clock_freq[0x4]; /* catalog type: uint32_t */
    uint8_t gain_l[0x4]; /* catalog type: uint32_t */
    uint8_t gain_r[0x1]; /* catalog type: uint32_t */
    uint8_t field_0x25[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x26[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x27[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_pdm_config_g1__param_0295, pin_clk) == 0x4, "g1_layout_pdm_config_g1__param_0295.pin_clk");
_Static_assert(offsetof(struct g1_layout_pdm_config_g1__param_0295, pin_din) == 0x10, "g1_layout_pdm_config_g1__param_0295.pin_din");
_Static_assert(offsetof(struct g1_layout_pdm_config_g1__param_0295, mode) == 0x14, "g1_layout_pdm_config_g1__param_0295.mode");
_Static_assert(offsetof(struct g1_layout_pdm_config_g1__param_0295, edge) == 0x18, "g1_layout_pdm_config_g1__param_0295.edge");
_Static_assert(offsetof(struct g1_layout_pdm_config_g1__param_0295, clock_freq) == 0x1c, "g1_layout_pdm_config_g1__param_0295.clock_freq");
_Static_assert(offsetof(struct g1_layout_pdm_config_g1__param_0295, gain_l) == 0x20, "g1_layout_pdm_config_g1__param_0295.gain_l");
_Static_assert(offsetof(struct g1_layout_pdm_config_g1__param_0295, gain_r) == 0x24, "g1_layout_pdm_config_g1__param_0295.gain_r");
_Static_assert(offsetof(struct g1_layout_pdm_config_g1__param_0295, field_0x25) == 0x25, "g1_layout_pdm_config_g1__param_0295.field_0x25");
_Static_assert(offsetof(struct g1_layout_pdm_config_g1__param_0295, field_0x26) == 0x26, "g1_layout_pdm_config_g1__param_0295.field_0x26");
_Static_assert(offsetof(struct g1_layout_pdm_config_g1__param_0295, field_0x27) == 0x27, "g1_layout_pdm_config_g1__param_0295.field_0x27");
_Static_assert(sizeof(struct g1_layout_pdm_config_g1__param_0295) >= 0x2b, "g1_layout_pdm_config_g1__param_0295.size");

/* param_0297 | G1-original | nRF clock-control on-request state accessed by clock_control_nrf_on: an initial status word and a completion/result word. | D1+D2 verified
 * review: Downgraded from sonnet's onoff_client guess to G1-original: only two ints observed, no confirmable stock struct match. */
struct __attribute__((packed)) g1_layout_clock_control_on_state__param_0297 {
    uint8_t _pad_0x0[0x4];
    uint8_t status[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t result[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_clock_control_on_state__param_0297, status) == 0x4, "g1_layout_clock_control_on_state__param_0297.status");
_Static_assert(offsetof(struct g1_layout_clock_control_on_state__param_0297, result) == 0x10, "g1_layout_clock_control_on_state__param_0297.result");
_Static_assert(sizeof(struct g1_layout_clock_control_on_state__param_0297) >= 0x14, "g1_layout_clock_control_on_state__param_0297.size");

/* param_0299 | G1-original | COINCIDENTAL merge of distinct QSPI-NOR driver data and I2S driver data structs that share the same param slot; treat as generic per-driver runtime data (semaphore/ready/counter words at 0x4/0x10/0x14). | D1+D2 verified
 * review: Flagged as footprint collision across 9 members (qspi_nor_* driver-data and audio_i2s_* driver-data). Not one real type; the qspi_nor and i2s instance-data structs should be recovered separately. Offsets preserved. */
struct __attribute__((packed)) g1_layout_param_0299_driver_data_collision__param_0299 {
    uint8_t _pad_0x0[0x4];
    uint8_t state_or_flag[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t field_0x10[0x4]; /* catalog type: int32_t */
    uint8_t field_0x14[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_param_0299_driver_data_collision__param_0299, state_or_flag) == 0x4, "g1_layout_param_0299_driver_data_collision__param_0299.state_or_flag");
_Static_assert(offsetof(struct g1_layout_param_0299_driver_data_collision__param_0299, field_0x10) == 0x10, "g1_layout_param_0299_driver_data_collision__param_0299.field_0x10");
_Static_assert(offsetof(struct g1_layout_param_0299_driver_data_collision__param_0299, field_0x14) == 0x14, "g1_layout_param_0299_driver_data_collision__param_0299.field_0x14");
_Static_assert(sizeof(struct g1_layout_param_0299_driver_data_collision__param_0299) >= 0x18, "g1_layout_param_0299_driver_data_collision__param_0299.size");

/* param_0300 | G1-original | G1 wrapper around a QSPI custom-instruction request carrying tx/rx buffer pointers, passed to qspi_nor_send_cinstr. | D1+D2 verified
 * review: G1-original; offsets unchanged. */
struct __attribute__((packed)) g1_layout_qspi_cinstr_req__param_0300 {
    uint8_t _pad_0x0[0x4];
    uint8_t tx_buf[0x4]; /* catalog type: void * */
    uint8_t rx_buf[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_qspi_cinstr_req__param_0300, tx_buf) == 0x4, "g1_layout_qspi_cinstr_req__param_0300.tx_buf");
_Static_assert(offsetof(struct g1_layout_qspi_cinstr_req__param_0300, rx_buf) == 0x8, "g1_layout_qspi_cinstr_req__param_0300.rx_buf");
_Static_assert(sizeof(struct g1_layout_qspi_cinstr_req__param_0300) >= 0xc, "g1_layout_qspi_cinstr_req__param_0300.size");

/* param_0305 | G1-original | Small context read by FUN_00061ba0 (param_1): a pointer field and a later integer field; insufficient evidence for semantics. | D1+D2 verified
 * review: G1-original, unnamed callee; kept generic. */
struct __attribute__((packed)) g1_layout_unk_ctx_305__param_0305 {
    uint8_t _pad_0x0[0x4];
    uint8_t ptr_field[0x4]; /* catalog type: void* */
    uint8_t _pad_0x8[0x8];
    uint8_t int_field[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_unk_ctx_305__param_0305, ptr_field) == 0x4, "g1_layout_unk_ctx_305__param_0305.ptr_field");
_Static_assert(offsetof(struct g1_layout_unk_ctx_305__param_0305, int_field) == 0x10, "g1_layout_unk_ctx_305__param_0305.int_field");
_Static_assert(sizeof(struct g1_layout_unk_ctx_305__param_0305) >= 0x14, "g1_layout_unk_ctx_305__param_0305.size");

/* param_0308 | G1-original | LSM6DSO IMU driver context used by lsm6dso_init_chip: a config/id int and a bus/device handle pointer. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_lsm6dso_dev_ctx__param_0308 {
    uint8_t _pad_0x0[0x4];
    uint8_t chip_id_or_cfg[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t bus_handle[0x4]; /* catalog type: void* */
};
_Static_assert(offsetof(struct g1_layout_lsm6dso_dev_ctx__param_0308, chip_id_or_cfg) == 0x4, "g1_layout_lsm6dso_dev_ctx__param_0308.chip_id_or_cfg");
_Static_assert(offsetof(struct g1_layout_lsm6dso_dev_ctx__param_0308, bus_handle) == 0x10, "g1_layout_lsm6dso_dev_ctx__param_0308.bus_handle");
_Static_assert(sizeof(struct g1_layout_lsm6dso_dev_ctx__param_0308) >= 0x14, "g1_layout_lsm6dso_dev_ctx__param_0308.size");

/* param_0311 | library | Zephyr generic UART config passed to uarte_nrfx_configure (baudrate/parity/stop_bits/data_bits/flow_ctrl). | D1+D2 verified
 * review: VERIFIED against drivers/uart.h: baudrate@0x0(u32), parity@0x4, stop_bits@0x5, data_bits@0x6, flow_ctrl@0x7. Observed 0x5/0x6/0x7 = stop_bits/data_bits/flow_ctrl; 0x4 is a width-4 read overlapping parity..flow_ctrl (is_union). 0x1 is a byte within baudrate. Corrected sonnet library_name (was uarte_nrfx_config). */
struct __attribute__((packed)) g1_layout_uart_config__param_0311 {
    uint8_t _pad_0x0[0x1];
    uint8_t baudrate_byte1[0x1]; /* catalog type: uint8_t; SDK member: baudrate (byte 1) */
    uint8_t _pad_0x2[0x2];
    uint8_t parity_word[0x1]; /* catalog type: uint32_t; SDK member: parity (width-4 read overlapping stop/data/flow) */
    uint8_t stop_bits[0x1]; /* catalog type: uint8_t; SDK member: stop_bits */
    uint8_t data_bits[0x1]; /* catalog type: uint8_t; SDK member: data_bits */
    uint8_t flow_ctrl[0x1]; /* catalog type: uint8_t; SDK member: flow_ctrl */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_uart_config__param_0311, baudrate_byte1) == 0x1, "g1_layout_uart_config__param_0311.baudrate_byte1");
_Static_assert(offsetof(struct g1_layout_uart_config__param_0311, parity_word) == 0x4, "g1_layout_uart_config__param_0311.parity_word");
_Static_assert(offsetof(struct g1_layout_uart_config__param_0311, stop_bits) == 0x5, "g1_layout_uart_config__param_0311.stop_bits");
_Static_assert(offsetof(struct g1_layout_uart_config__param_0311, data_bits) == 0x6, "g1_layout_uart_config__param_0311.data_bits");
_Static_assert(offsetof(struct g1_layout_uart_config__param_0311, flow_ctrl) == 0x7, "g1_layout_uart_config__param_0311.flow_ctrl");
_Static_assert(sizeof(struct g1_layout_uart_config__param_0311) >= 0xb, "g1_layout_uart_config__param_0311.size");

/* param_0312 | library | nrfx UARTE driver instance data used by uarte_nrfx_configure and uarte_nrfx_init; two pointer fields observed. | D1+D2 verified
 * review: UARTE Zephyr driver data is a file-local struct; only two pointers observed, offsets unverified. */
struct __attribute__((packed)) g1_layout_uarte_nrfx_data__param_0312 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0x8];
    uint8_t field_0x10[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_uarte_nrfx_data__param_0312, field_0x4) == 0x4, "g1_layout_uarte_nrfx_data__param_0312.field_0x4");
_Static_assert(offsetof(struct g1_layout_uarte_nrfx_data__param_0312, field_0x10) == 0x10, "g1_layout_uarte_nrfx_data__param_0312.field_0x10");
_Static_assert(sizeof(struct g1_layout_uarte_nrfx_data__param_0312) >= 0x14, "g1_layout_uarte_nrfx_data__param_0312.size");

/* param_0313 | library | nrfx UARTE driver runtime-data struct accessed by uarte_nrfx_pm_action for suspend/resume. | D1+D2 verified
 * review: Zephyr uart_nrfx_uarte driver data (file-static struct, no public header), unverified. */
struct __attribute__((packed)) g1_layout_uarte_nrfx_data__param_0313 {
    uint8_t _pad_0x0[0x4];
    uint8_t callback_or_cfg[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0x8];
    uint8_t pm_state[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_uarte_nrfx_data__param_0313, callback_or_cfg) == 0x4, "g1_layout_uarte_nrfx_data__param_0313.callback_or_cfg");
_Static_assert(offsetof(struct g1_layout_uarte_nrfx_data__param_0313, pm_state) == 0x10, "g1_layout_uarte_nrfx_data__param_0313.pm_state");
_Static_assert(sizeof(struct g1_layout_uarte_nrfx_data__param_0313) >= 0x14, "g1_layout_uarte_nrfx_data__param_0313.size");

/* param_0314 | G1-original | UARTE/DMA device data shared across TX/ISR/DMA and helper routines (config/cb ptr + two state words). | D1+D2 verified
 * review: Unified across 10 functions; treated as G1-original device-data block (nrfx UARTE data is private, unverifiable). */
struct __attribute__((packed)) g1_layout_uarte_driver_ctx__param_0314 {
    uint8_t _pad_0x0[0x4];
    uint8_t cfg_or_cb_ptr[0x4]; /* catalog type: void* */
    uint8_t _pad_0x8[0x8];
    uint8_t state_word_0[0x4]; /* catalog type: uint32_t */
    uint8_t state_word_1[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_uarte_driver_ctx__param_0314, cfg_or_cb_ptr) == 0x4, "g1_layout_uarte_driver_ctx__param_0314.cfg_or_cb_ptr");
_Static_assert(offsetof(struct g1_layout_uarte_driver_ctx__param_0314, state_word_0) == 0x10, "g1_layout_uarte_driver_ctx__param_0314.state_word_0");
_Static_assert(offsetof(struct g1_layout_uarte_driver_ctx__param_0314, state_word_1) == 0x14, "g1_layout_uarte_driver_ctx__param_0314.state_word_1");
_Static_assert(sizeof(struct g1_layout_uarte_driver_ctx__param_0314) >= 0x18, "g1_layout_uarte_driver_ctx__param_0314.size");

/* param_0315 | library | param_1 of wdt_install_timeout: watchdog timeout config with a callback/window pointer near front and a second pointer at 0x10. | D1+D2 verified
 * review: Only two pointers observed; struct wdt_timeout_cfg has window/callback/flags - not fully verifiable. */
struct __attribute__((packed)) g1_layout_wdt_timeout_cfg_view__param_0315 {
    uint8_t _pad_0x0[0x4];
    uint8_t callback_ptr[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0x8];
    uint8_t field_0x10[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_wdt_timeout_cfg_view__param_0315, callback_ptr) == 0x4, "g1_layout_wdt_timeout_cfg_view__param_0315.callback_ptr");
_Static_assert(offsetof(struct g1_layout_wdt_timeout_cfg_view__param_0315, field_0x10) == 0x10, "g1_layout_wdt_timeout_cfg_view__param_0315.field_0x10");
_Static_assert(sizeof(struct g1_layout_wdt_timeout_cfg_view__param_0315) >= 0x14, "g1_layout_wdt_timeout_cfg_view__param_0315.size");

/* param_0316 | library | Zephyr watchdog timeout configuration passed (param_2) to wdt_install_timeout: flags byte and a window/callback word. | D1+D2 verified
 * review: Observed 0x3(byte)/0x4(word) do not cleanly line up with wdt_timeout_cfg {wdt_window window{min@0,max@4}; callback@8; flags@c}, so library_verified=false. */
struct __attribute__((packed)) g1_layout_wdt_timeout_cfg__param_0316 {
    uint8_t _pad_0x0[0x3];
    uint8_t flags[0x1]; /* catalog type: uint8_t */
    uint8_t window_max[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_wdt_timeout_cfg__param_0316, flags) == 0x3, "g1_layout_wdt_timeout_cfg__param_0316.flags");
_Static_assert(offsetof(struct g1_layout_wdt_timeout_cfg__param_0316, window_max) == 0x4, "g1_layout_wdt_timeout_cfg__param_0316.window_max");
_Static_assert(sizeof(struct g1_layout_wdt_timeout_cfg__param_0316) >= 0x8, "g1_layout_wdt_timeout_cfg__param_0316.size");

/* param_0319 | library | Zephyr/MCUboot flash_area descriptor used by boot/flash_area/nvs routines: fa_off, fa_size, fa_dev. | D1+D2 verified
 * review: Verified against flash_map.h: fa_id(uint8)@0x0, pad16@0x2, fa_off(off_t)@0x4, fa_size(size_t)@0x8, fa_dev(const device*)@0xc. Observed reads at 0x4/0x8/0xc match exactly (corrected sonnet: 0x4 is fa_off, not fa_id). */
struct __attribute__((packed)) g1_layout_flash_area__param_0319 {
    uint8_t _pad_0x0[0x4];
    uint8_t fa_off[0x4]; /* catalog type: off_t; SDK member: fa_off */
    uint8_t fa_size[0x4]; /* catalog type: size_t; SDK member: fa_size */
    uint8_t fa_dev[0x4]; /* catalog type: const struct device *; SDK member: fa_dev */
};
_Static_assert(offsetof(struct g1_layout_flash_area__param_0319, fa_off) == 0x4, "g1_layout_flash_area__param_0319.fa_off");
_Static_assert(offsetof(struct g1_layout_flash_area__param_0319, fa_size) == 0x8, "g1_layout_flash_area__param_0319.fa_size");
_Static_assert(offsetof(struct g1_layout_flash_area__param_0319, fa_dev) == 0xc, "g1_layout_flash_area__param_0319.fa_dev");
_Static_assert(sizeof(struct g1_layout_flash_area__param_0319) >= 0x10, "g1_layout_flash_area__param_0319.size");

/* param_0320 | G1-original | Flash boot-swap allocation-table entry read by flash_read_boot_swap_ate. | D1+D2 verified
 * review: G1-original; offsets unchanged. */
struct __attribute__((packed)) g1_layout_flash_boot_swap_ate__param_0320 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_flash_boot_swap_ate__param_0320, field_0x4) == 0x4, "g1_layout_flash_boot_swap_ate__param_0320.field_0x4");
_Static_assert(offsetof(struct g1_layout_flash_boot_swap_ate__param_0320, field_0x10) == 0x10, "g1_layout_flash_boot_swap_ate__param_0320.field_0x10");
_Static_assert(sizeof(struct g1_layout_flash_boot_swap_ate__param_0320) >= 0x14, "g1_layout_flash_boot_swap_ate__param_0320.size");

/* param_0321 | library | cJSON growable print/parse buffer (buffer ptr, length, offset, depth, noalloc/format flags, hooks) shared by cjson_print_string/value and generic cursor/growbuf helpers. | D1+D2 verified
 * review: Separated from param_0150: coincidental 9-word/0x24 footprint collision, NOT the same object as stream_flash_ctx. cJSON is a vendored module, not in the pinned Zephyr/nrf headers, and two members (cursor_advance_past_cstring/growbuf_ensure_capacity) are generic, so left unverified. field_0x0 is a buffer pointer that Ghidra typed as code. */
struct __attribute__((packed)) g1_layout_cjson_printbuffer__param_0321 {
    uint8_t buffer[0x4]; /* catalog type: unsigned char * */
    uint8_t length[0x4]; /* catalog type: size_t */
    uint8_t offset[0x4]; /* catalog type: size_t */
    uint8_t depth[0x4]; /* catalog type: size_t */
    uint8_t noalloc[0x4]; /* catalog type: int32_t */
    uint8_t format[0x4]; /* catalog type: int32_t */
    uint8_t hooks_alloc[0x4]; /* catalog type: void * */
    uint8_t hooks_free[0x4]; /* catalog type: void * */
    uint8_t hooks_realloc[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0321, buffer) == 0x0, "g1_layout_cjson_printbuffer__param_0321.buffer");
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0321, length) == 0x4, "g1_layout_cjson_printbuffer__param_0321.length");
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0321, offset) == 0x8, "g1_layout_cjson_printbuffer__param_0321.offset");
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0321, depth) == 0xc, "g1_layout_cjson_printbuffer__param_0321.depth");
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0321, noalloc) == 0x10, "g1_layout_cjson_printbuffer__param_0321.noalloc");
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0321, format) == 0x14, "g1_layout_cjson_printbuffer__param_0321.format");
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0321, hooks_alloc) == 0x18, "g1_layout_cjson_printbuffer__param_0321.hooks_alloc");
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0321, hooks_free) == 0x1c, "g1_layout_cjson_printbuffer__param_0321.hooks_free");
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0321, hooks_realloc) == 0x20, "g1_layout_cjson_printbuffer__param_0321.hooks_realloc");
_Static_assert(sizeof(struct g1_layout_cjson_printbuffer__param_0321) >= 0x24, "g1_layout_cjson_printbuffer__param_0321.size");

/* param_0322 | library | cJSON item node used by cjson_add_item_to_object and traversed via sllist_insert_after. | D1+D2 verified
 * review: Offsets match cJSON: next@0x0, prev@0x4, child@0x8, type@0xc, valuestring@0x10, valueint@0x14, valuedouble@0x18, string@0x20. Observed 0x4=prev, 0xc=type, 0x20=string all line up. */
struct __attribute__((packed)) g1_layout_cJSON__param_0322 {
    uint8_t _pad_0x0[0x4];
    uint8_t prev[0x4]; /* catalog type: struct cJSON*; SDK member: prev */
    uint8_t _pad_0x8[0x4];
    uint8_t type[0x4]; /* catalog type: int; SDK member: type */
    uint8_t _pad_0x10[0x10];
    uint8_t string[0x4]; /* catalog type: char*; SDK member: string */
};
_Static_assert(offsetof(struct g1_layout_cJSON__param_0322, prev) == 0x4, "g1_layout_cJSON__param_0322.prev");
_Static_assert(offsetof(struct g1_layout_cJSON__param_0322, type) == 0xc, "g1_layout_cJSON__param_0322.type");
_Static_assert(offsetof(struct g1_layout_cJSON__param_0322, string) == 0x20, "g1_layout_cJSON__param_0322.string");
_Static_assert(sizeof(struct g1_layout_cJSON__param_0322) >= 0x24, "g1_layout_cJSON__param_0322.size");

/* param_0323 | library | cJSON print-buffer state used by cjson_print_value: output buffer pointer, noalloc flag, length, offset and depth counters. | D1+D2 verified
 * review: cJSON printbuffer is a static (file-local) struct not present in a pinned public header; offsets are consistent with {buffer,length,offset,noalloc,depth,...} but cannot be verified against a header. Kept naming, offsets unchanged. */
struct __attribute__((packed)) g1_layout_cjson_printbuffer__param_0323 {
    uint8_t _pad_0x0[0x8];
    uint8_t buffer[0x4]; /* catalog type: char* */
    uint8_t noalloc[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xd[0x3];
    uint8_t length[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x4];
    uint8_t offset[0x4]; /* catalog type: uint32_t */
    uint8_t depth[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0323, buffer) == 0x8, "g1_layout_cjson_printbuffer__param_0323.buffer");
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0323, noalloc) == 0xc, "g1_layout_cjson_printbuffer__param_0323.noalloc");
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0323, length) == 0x10, "g1_layout_cjson_printbuffer__param_0323.length");
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0323, offset) == 0x18, "g1_layout_cjson_printbuffer__param_0323.offset");
_Static_assert(offsetof(struct g1_layout_cjson_printbuffer__param_0323, depth) == 0x1c, "g1_layout_cjson_printbuffer__param_0323.depth");
_Static_assert(sizeof(struct g1_layout_cjson_printbuffer__param_0323) >= 0x20, "g1_layout_cjson_printbuffer__param_0323.size");

/* param_0324 | library | cJSON tree node freed recursively by cjson_delete (child/type/valuestring/string accessed). | D1+D2 verified
 * review: VERIFIED against cJSON.h: next@0x0, prev@0x4, child@0x8, type@0xc, valuestring@0x10, valueint@0x14, valuedouble@0x18, string@0x20. Observed 0x8/0xc/0x10/0x20 match child/type/valuestring/string exactly. */
struct __attribute__((packed)) g1_layout_cJSON__param_0324 {
    uint8_t _pad_0x0[0x8];
    uint8_t child[0x4]; /* catalog type: struct cJSON *; SDK member: child */
    uint8_t type[0x4]; /* catalog type: int; SDK member: type */
    uint8_t valuestring[0x4]; /* catalog type: char *; SDK member: valuestring */
    uint8_t _pad_0x14[0xc];
    uint8_t string[0x4]; /* catalog type: char *; SDK member: string */
};
_Static_assert(offsetof(struct g1_layout_cJSON__param_0324, child) == 0x8, "g1_layout_cJSON__param_0324.child");
_Static_assert(offsetof(struct g1_layout_cJSON__param_0324, type) == 0xc, "g1_layout_cJSON__param_0324.type");
_Static_assert(offsetof(struct g1_layout_cJSON__param_0324, valuestring) == 0x10, "g1_layout_cJSON__param_0324.valuestring");
_Static_assert(offsetof(struct g1_layout_cJSON__param_0324, string) == 0x20, "g1_layout_cJSON__param_0324.string");
_Static_assert(sizeof(struct g1_layout_cJSON__param_0324) >= 0x24, "g1_layout_cJSON__param_0324.size");

/* param_0331 | G1-original | Small context passed to gpiote_trigger_enable identifying a GPIOTE channel/pin and a config word. | D1+D2 verified
 * review: G1-original; kept sonnet naming. */
struct __attribute__((packed)) g1_layout_gpiote_trigger_ctx__param_0331 {
    uint8_t _pad_0x0[0x4];
    uint8_t channel_or_pin[0x4]; /* catalog type: uint32_t */
    uint8_t config_word[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gpiote_trigger_ctx__param_0331, channel_or_pin) == 0x4, "g1_layout_gpiote_trigger_ctx__param_0331.channel_or_pin");
_Static_assert(offsetof(struct g1_layout_gpiote_trigger_ctx__param_0331, config_word) == 0x8, "g1_layout_gpiote_trigger_ctx__param_0331.config_word");
_Static_assert(sizeof(struct g1_layout_gpiote_trigger_ctx__param_0331) >= 0xc, "g1_layout_gpiote_trigger_ctx__param_0331.size");

/* param_0333 | G1-original | PDM GPIO pin configuration (clock/data pin numbers and related fields) consumed by pdm_configure_pins. | D1+D2 verified
 * review: G1-original config struct; kept all 9 observed offsets. */
struct __attribute__((packed)) g1_layout_pdm_pin_config__param_0333 {
    uint8_t _pad_0x0[0x4];
    uint8_t pin_clk[0x4]; /* catalog type: uint32_t */
    uint8_t pin_din[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x30];
    uint8_t field_0x40[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x44[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x48[0x4];
    uint8_t field_0x4c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x50[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x54[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x58[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_pdm_pin_config__param_0333, pin_clk) == 0x4, "g1_layout_pdm_pin_config__param_0333.pin_clk");
_Static_assert(offsetof(struct g1_layout_pdm_pin_config__param_0333, pin_din) == 0x8, "g1_layout_pdm_pin_config__param_0333.pin_din");
_Static_assert(offsetof(struct g1_layout_pdm_pin_config__param_0333, field_0xc) == 0xc, "g1_layout_pdm_pin_config__param_0333.field_0xc");
_Static_assert(offsetof(struct g1_layout_pdm_pin_config__param_0333, field_0x40) == 0x40, "g1_layout_pdm_pin_config__param_0333.field_0x40");
_Static_assert(offsetof(struct g1_layout_pdm_pin_config__param_0333, field_0x44) == 0x44, "g1_layout_pdm_pin_config__param_0333.field_0x44");
_Static_assert(offsetof(struct g1_layout_pdm_pin_config__param_0333, field_0x4c) == 0x4c, "g1_layout_pdm_pin_config__param_0333.field_0x4c");
_Static_assert(offsetof(struct g1_layout_pdm_pin_config__param_0333, field_0x50) == 0x50, "g1_layout_pdm_pin_config__param_0333.field_0x50");
_Static_assert(offsetof(struct g1_layout_pdm_pin_config__param_0333, field_0x54) == 0x54, "g1_layout_pdm_pin_config__param_0333.field_0x54");
_Static_assert(offsetof(struct g1_layout_pdm_pin_config__param_0333, field_0x58) == 0x58, "g1_layout_pdm_pin_config__param_0333.field_0x58");
_Static_assert(sizeof(struct g1_layout_pdm_pin_config__param_0333) >= 0x5c, "g1_layout_pdm_pin_config__param_0333.size");

/* param_0334 | library | PDM configuration record read by nrfx_pdm_init (mode/edge/gain bytes near tail). | D1+D2 verified
 * review: Only sparse tail bytes (0x10/0x11/0x15) observed; did not fully match against nrfx_pdm.h field-by-field. verified=false. */
struct __attribute__((packed)) g1_layout_nrfx_pdm_config__param_0334 {
    uint8_t _pad_0x0[0x10];
    uint8_t mode[0x1]; /* catalog type: uint8_t */
    uint8_t edge[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x12[0x3];
    uint8_t gain_or_flag[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_pdm_config__param_0334, mode) == 0x10, "g1_layout_nrfx_pdm_config__param_0334.mode");
_Static_assert(offsetof(struct g1_layout_nrfx_pdm_config__param_0334, edge) == 0x11, "g1_layout_nrfx_pdm_config__param_0334.edge");
_Static_assert(offsetof(struct g1_layout_nrfx_pdm_config__param_0334, gain_or_flag) == 0x15, "g1_layout_nrfx_pdm_config__param_0334.gain_or_flag");
_Static_assert(sizeof(struct g1_layout_nrfx_pdm_config__param_0334) >= 0x16, "g1_layout_nrfx_pdm_config__param_0334.size");

/* param_0335 | library | QSPI custom-instruction data buffer read/written by nrf_qspi_cinstrdata_get and nrf_qspi_cinstrdata_set (nrfx nrf_qspi HAL, CINSTRDAT0/DAT1 register payload). | D1+D2 verified
 * review: SPLIT from collision group global_1358, but MERGED param_0335 (cinstrdata_get) + param_0336 (cinstrdata_set): both are param_2 = the same QSPI custom-instruction data buffer type for the get/set HAL pair. Underlying object is at most an 8-byte data buffer; the 7-word footprint is Ghidra over-read, so library_verified=false. */
struct __attribute__((packed)) g1_layout_nrf_qspi_cinstr_data__param_0335 {
    uint8_t _pad_0x0[0x4];
    uint8_t data_word0[0x4]; /* catalog type: uint32_t */
    uint8_t data_word1[0x4]; /* catalog type: uint32_t */
    uint8_t data_word2[0x4]; /* catalog type: uint32_t */
    uint8_t data_word3[0x4]; /* catalog type: uint32_t */
    uint8_t data_word4[0x4]; /* catalog type: uint32_t */
    uint8_t data_word5[0x4]; /* catalog type: uint32_t */
    uint8_t data_word6[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nrf_qspi_cinstr_data__param_0335, data_word0) == 0x4, "g1_layout_nrf_qspi_cinstr_data__param_0335.data_word0");
_Static_assert(offsetof(struct g1_layout_nrf_qspi_cinstr_data__param_0335, data_word1) == 0x8, "g1_layout_nrf_qspi_cinstr_data__param_0335.data_word1");
_Static_assert(offsetof(struct g1_layout_nrf_qspi_cinstr_data__param_0335, data_word2) == 0xc, "g1_layout_nrf_qspi_cinstr_data__param_0335.data_word2");
_Static_assert(offsetof(struct g1_layout_nrf_qspi_cinstr_data__param_0335, data_word3) == 0x10, "g1_layout_nrf_qspi_cinstr_data__param_0335.data_word3");
_Static_assert(offsetof(struct g1_layout_nrf_qspi_cinstr_data__param_0335, data_word4) == 0x14, "g1_layout_nrf_qspi_cinstr_data__param_0335.data_word4");
_Static_assert(offsetof(struct g1_layout_nrf_qspi_cinstr_data__param_0335, data_word5) == 0x18, "g1_layout_nrf_qspi_cinstr_data__param_0335.data_word5");
_Static_assert(offsetof(struct g1_layout_nrf_qspi_cinstr_data__param_0335, data_word6) == 0x1c, "g1_layout_nrf_qspi_cinstr_data__param_0335.data_word6");
_Static_assert(sizeof(struct g1_layout_nrf_qspi_cinstr_data__param_0335) >= 0x20, "g1_layout_nrf_qspi_cinstr_data__param_0335.size");

/* param_0337 | library | QSPI pin-assignment argument to nrf_qspi_pins_set (sck/csn/io0-io3). | D1+D2 verified
 * review: Split from footprint-collision group global_1341. The real nrf_qspi_pins_t is six packed uint8 pin numbers (6 bytes); Ghidra's 5x uint32 idx4 footprint is an over-extended approximation. Offsets kept as ground truth but do not literally map to the 6-byte struct. */
struct __attribute__((packed)) g1_layout_qspi_pins_config__param_0337 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_qspi_pins_config__param_0337, field_0x4) == 0x4, "g1_layout_qspi_pins_config__param_0337.field_0x4");
_Static_assert(offsetof(struct g1_layout_qspi_pins_config__param_0337, field_0x8) == 0x8, "g1_layout_qspi_pins_config__param_0337.field_0x8");
_Static_assert(offsetof(struct g1_layout_qspi_pins_config__param_0337, field_0xc) == 0xc, "g1_layout_qspi_pins_config__param_0337.field_0xc");
_Static_assert(offsetof(struct g1_layout_qspi_pins_config__param_0337, field_0x10) == 0x10, "g1_layout_qspi_pins_config__param_0337.field_0x10");
_Static_assert(offsetof(struct g1_layout_qspi_pins_config__param_0337, field_0x14) == 0x14, "g1_layout_qspi_pins_config__param_0337.field_0x14");
_Static_assert(sizeof(struct g1_layout_qspi_pins_config__param_0337) >= 0x18, "g1_layout_qspi_pins_config__param_0337.size");

/* param_0338 | G1-original | param_1 of qspi_configure_pins_and_interface: G1 QSPI config (GPIO pin words + protocol/PHY bytes readoc/writeoc/addrmode/sck_delay/spi_mode/sck_freq + flags word + irq priority). | D1+D2 verified
 * review: Corrected sonnet's high-confidence nrfx_qspi_config_t claim: real nrfx_qspi_config_t uses uint8 pins in nested sub-structs, whereas here pins are 32-bit words (0x8-0x18). This is a G1 wrapper config. 0x4 read overlaps its pad -> union. */
struct __attribute__((packed)) g1_layout_qspi_config_g1__param_0338 {
    uint8_t _pad_0x0[0x7];
    uint8_t field_0x7[0x1]; /* catalog type: uint8_t */
    uint8_t pin_a[0x4]; /* catalog type: uint32_t */
    uint8_t pin_b[0x4]; /* catalog type: uint32_t */
    uint8_t pin_c[0x4]; /* catalog type: uint32_t */
    uint8_t pin_d[0x4]; /* catalog type: uint32_t */
    uint8_t pin_e[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1c[0x1];
    uint8_t readoc[0x1]; /* catalog type: uint8_t */
    uint8_t writeoc[0x1]; /* catalog type: uint8_t */
    uint8_t addrmode[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x20[0x1];
    uint8_t sck_delay[0x1]; /* catalog type: uint8_t */
    uint8_t spi_mode[0x1]; /* catalog type: uint8_t */
    uint8_t sck_freq[0x1]; /* catalog type: uint8_t */
    uint8_t skip_cfg_flags[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x28[0x1];
    uint8_t irq_priority[0x1]; /* catalog type: uint8_t */
    uint8_t reserved[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, field_0x7) == 0x7, "g1_layout_qspi_config_g1__param_0338.field_0x7");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, pin_a) == 0x8, "g1_layout_qspi_config_g1__param_0338.pin_a");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, pin_b) == 0xc, "g1_layout_qspi_config_g1__param_0338.pin_b");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, pin_c) == 0x10, "g1_layout_qspi_config_g1__param_0338.pin_c");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, pin_d) == 0x14, "g1_layout_qspi_config_g1__param_0338.pin_d");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, pin_e) == 0x18, "g1_layout_qspi_config_g1__param_0338.pin_e");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, readoc) == 0x1d, "g1_layout_qspi_config_g1__param_0338.readoc");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, writeoc) == 0x1e, "g1_layout_qspi_config_g1__param_0338.writeoc");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, addrmode) == 0x1f, "g1_layout_qspi_config_g1__param_0338.addrmode");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, sck_delay) == 0x21, "g1_layout_qspi_config_g1__param_0338.sck_delay");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, spi_mode) == 0x22, "g1_layout_qspi_config_g1__param_0338.spi_mode");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, sck_freq) == 0x23, "g1_layout_qspi_config_g1__param_0338.sck_freq");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, skip_cfg_flags) == 0x24, "g1_layout_qspi_config_g1__param_0338.skip_cfg_flags");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, irq_priority) == 0x29, "g1_layout_qspi_config_g1__param_0338.irq_priority");
_Static_assert(offsetof(struct g1_layout_qspi_config_g1__param_0338, reserved) == 0x2a, "g1_layout_qspi_config_g1__param_0338.reserved");
_Static_assert(sizeof(struct g1_layout_qspi_config_g1__param_0338) >= 0x2e, "g1_layout_qspi_config_g1__param_0338.size");

/* param_0339 | library | nrfx QSPI custom-instruction transfer configuration consumed by nrfx_qspi_cinstr_xfer (opcode/length/IO levels/WREN). | D1+D2 verified
 * review: Split from footprint-collision group global_1341. Real nrfx_qspi_cinstr_config_t is byte-packed (~6 bytes: opcode,length,io2/io3/wren/wipwait); the 5x uint32 shape is a Ghidra idx4 approximation. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_nrfx_qspi_cinstr_config__param_0339 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_cinstr_config__param_0339, field_0x4) == 0x4, "g1_layout_nrfx_qspi_cinstr_config__param_0339.field_0x4");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_cinstr_config__param_0339, field_0x8) == 0x8, "g1_layout_nrfx_qspi_cinstr_config__param_0339.field_0x8");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_cinstr_config__param_0339, field_0xc) == 0xc, "g1_layout_nrfx_qspi_cinstr_config__param_0339.field_0xc");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_cinstr_config__param_0339, field_0x10) == 0x10, "g1_layout_nrfx_qspi_cinstr_config__param_0339.field_0x10");
_Static_assert(offsetof(struct g1_layout_nrfx_qspi_cinstr_config__param_0339, field_0x14) == 0x14, "g1_layout_nrfx_qspi_cinstr_config__param_0339.field_0x14");
_Static_assert(sizeof(struct g1_layout_nrfx_qspi_cinstr_config__param_0339) >= 0x18, "g1_layout_nrfx_qspi_cinstr_config__param_0339.size");

/* param_0340 | library | Pin/frequency validation configuration (param_2) passed to nrfx_pin_freq_config_validate (QSPI pin config). | D1+D2 verified
 * review: nrfx-adjacent config struct; not matched to a specific pinned header, so library_verified=false. */
struct __attribute__((packed)) g1_layout_nrfx_pin_freq_cfg__param_0340 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x4];
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x4];
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x20[0x1];
    uint8_t field_0x21[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x22[0x1];
    uint8_t field_0x23[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_pin_freq_cfg__param_0340, field_0x4) == 0x4, "g1_layout_nrfx_pin_freq_cfg__param_0340.field_0x4");
_Static_assert(offsetof(struct g1_layout_nrfx_pin_freq_cfg__param_0340, field_0x8) == 0x8, "g1_layout_nrfx_pin_freq_cfg__param_0340.field_0x8");
_Static_assert(offsetof(struct g1_layout_nrfx_pin_freq_cfg__param_0340, field_0xc) == 0xc, "g1_layout_nrfx_pin_freq_cfg__param_0340.field_0xc");
_Static_assert(offsetof(struct g1_layout_nrfx_pin_freq_cfg__param_0340, field_0x14) == 0x14, "g1_layout_nrfx_pin_freq_cfg__param_0340.field_0x14");
_Static_assert(offsetof(struct g1_layout_nrfx_pin_freq_cfg__param_0340, field_0x1c) == 0x1c, "g1_layout_nrfx_pin_freq_cfg__param_0340.field_0x1c");
_Static_assert(offsetof(struct g1_layout_nrfx_pin_freq_cfg__param_0340, field_0x21) == 0x21, "g1_layout_nrfx_pin_freq_cfg__param_0340.field_0x21");
_Static_assert(offsetof(struct g1_layout_nrfx_pin_freq_cfg__param_0340, field_0x23) == 0x23, "g1_layout_nrfx_pin_freq_cfg__param_0340.field_0x23");
_Static_assert(offsetof(struct g1_layout_nrfx_pin_freq_cfg__param_0340, field_0x24) == 0x24, "g1_layout_nrfx_pin_freq_cfg__param_0340.field_0x24");
_Static_assert(sizeof(struct g1_layout_nrfx_pin_freq_cfg__param_0340) >= 0x28, "g1_layout_nrfx_pin_freq_cfg__param_0340.size");

/* param_0342 | library | nrfx SPIM peripheral instance handle used by nrfx_spim_configure/nrfx_spim_init: a driver-instance index byte plus a byte read at 0x4. | D1+D2 verified
 * review: Only two sub-word byte reads (0x1, 0x4) observed; insufficient to verify against nrfx_spim_t ({p_reg; drv_inst_idx}). library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_nrfx_spim_t__param_0342 {
    uint8_t _pad_0x0[0x1];
    uint8_t field_0x1[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x2];
    uint8_t field_0x4[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_spim_t__param_0342, field_0x1) == 0x1, "g1_layout_nrfx_spim_t__param_0342.field_0x1");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_t__param_0342, field_0x4) == 0x4, "g1_layout_nrfx_spim_t__param_0342.field_0x4");
_Static_assert(sizeof(struct g1_layout_nrfx_spim_t__param_0342) >= 0x5, "g1_layout_nrfx_spim_t__param_0342.size");

/* param_0343 | library | nrfx SPIM peripheral configuration struct passed to nrfx_spim_configure (pin selects, IRQ priority, ORC, frequency/mode/bit-order flags). | D1+D2 verified
 * review: nrfx_spim_config_t id kept; field semantics plausible but exact offsets not cross-checked against nrfx_spim.h. is_union=true (0x4 and 0x8 accessed both byte- and word-wide). Offsets unchanged. */
struct __attribute__((packed)) g1_layout_nrfx_spim_config__param_0343 {
    uint8_t _pad_0x0[0x4];
    uint8_t sck_pin[0x2]; /* catalog type: uint32_t */
    uint8_t field_0x6[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x7[0x1];
    uint8_t mosi_pin[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x9[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xa[0x2];
    uint8_t miso_pin[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x2];
    uint8_t ss_active_high[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x13[0x1];
    uint8_t irq_priority[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x1];
    uint8_t orc[0x1]; /* catalog type: uint8_t */
    uint8_t frequency[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1b[0x1];
    uint8_t mode_or_ss[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x20[0x1];
    uint8_t bit_order[0x1]; /* catalog type: uint8_t */
    uint8_t skip_gpio_cfg[0x1]; /* catalog type: uint8_t */
    uint8_t skip_psel_cfg[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, sck_pin) == 0x4, "g1_layout_nrfx_spim_config__param_0343.sck_pin");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, field_0x6) == 0x6, "g1_layout_nrfx_spim_config__param_0343.field_0x6");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, mosi_pin) == 0x8, "g1_layout_nrfx_spim_config__param_0343.mosi_pin");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, field_0x9) == 0x9, "g1_layout_nrfx_spim_config__param_0343.field_0x9");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, miso_pin) == 0xc, "g1_layout_nrfx_spim_config__param_0343.miso_pin");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, ss_active_high) == 0x12, "g1_layout_nrfx_spim_config__param_0343.ss_active_high");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, irq_priority) == 0x14, "g1_layout_nrfx_spim_config__param_0343.irq_priority");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, orc) == 0x19, "g1_layout_nrfx_spim_config__param_0343.orc");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, frequency) == 0x1a, "g1_layout_nrfx_spim_config__param_0343.frequency");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, mode_or_ss) == 0x1c, "g1_layout_nrfx_spim_config__param_0343.mode_or_ss");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, bit_order) == 0x21, "g1_layout_nrfx_spim_config__param_0343.bit_order");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, skip_gpio_cfg) == 0x22, "g1_layout_nrfx_spim_config__param_0343.skip_gpio_cfg");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_config__param_0343, skip_psel_cfg) == 0x23, "g1_layout_nrfx_spim_config__param_0343.skip_psel_cfg");
_Static_assert(sizeof(struct g1_layout_nrfx_spim_config__param_0343) >= 0x27, "g1_layout_nrfx_spim_config__param_0343.size");

/* param_0344 | library | nrfx SPIM peripheral instance control block, accessed by nrfx_spim_uninit. | D1+D2 verified
 * review: Identity from callee; drv_inst_idx byte at 0x1 plus a p_reg/flags word at 0x4 fit nrfx_spim_t but offsets not header-verified. */
struct __attribute__((packed)) g1_layout_nrfx_spim_t__param_0344 {
    uint8_t _pad_0x0[0x1];
    uint8_t drv_inst_idx[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x2];
    uint8_t p_reg_or_flags[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_spim_t__param_0344, drv_inst_idx) == 0x1, "g1_layout_nrfx_spim_t__param_0344.drv_inst_idx");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_t__param_0344, p_reg_or_flags) == 0x4, "g1_layout_nrfx_spim_t__param_0344.p_reg_or_flags");
_Static_assert(sizeof(struct g1_layout_nrfx_spim_t__param_0344) >= 0x8, "g1_layout_nrfx_spim_t__param_0344.size");

/* param_0346 | library | nrfx SPIM single-transfer descriptor passed to nrfx_spim_xfer. | D1+D2 verified
 * review: Verified against nrfy_spim.h struct nrfy_spim_xfer_desc_t (= nrfx_spim_xfer_desc_t): p_tx_buffer@0, tx_length@4, p_rx_buffer@8, rx_length@0xc. Corrected sonnet's off-by-one (it labeled 0x4 as p_tx_buffer; p_tx_buffer is @0x0, unobserved here). Observed 0x4/0x8/0xc map exactly to tx_length/p_rx_buffer/rx_length. */
struct __attribute__((packed)) g1_layout_nrfx_spim_xfer_desc_t__param_0346 {
    uint8_t _pad_0x0[0x4];
    uint8_t tx_length[0x4]; /* catalog type: size_t; SDK member: tx_length */
    uint8_t p_rx_buffer[0x4]; /* catalog type: uint8_t*; SDK member: p_rx_buffer */
    uint8_t rx_length[0x4]; /* catalog type: size_t; SDK member: rx_length */
};
_Static_assert(offsetof(struct g1_layout_nrfx_spim_xfer_desc_t__param_0346, tx_length) == 0x4, "g1_layout_nrfx_spim_xfer_desc_t__param_0346.tx_length");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_xfer_desc_t__param_0346, p_rx_buffer) == 0x8, "g1_layout_nrfx_spim_xfer_desc_t__param_0346.p_rx_buffer");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_xfer_desc_t__param_0346, rx_length) == 0xc, "g1_layout_nrfx_spim_xfer_desc_t__param_0346.rx_length");
_Static_assert(sizeof(struct g1_layout_nrfx_spim_xfer_desc_t__param_0346) >= 0x10, "g1_layout_nrfx_spim_xfer_desc_t__param_0346.size");

/* param_0347 | library | nRF TWIM (I2C) driver config used by nrfx_twim_init / twim_configure (SCL/SDA pins, frequency, flags). | D1+D2 verified
 * review: VERIFIED against nrfx_twim.h: scl_pin@0x0(u32), sda_pin@0x4(u32), frequency@0x8(enum u32), interrupt_priority@0xc, hold_bus_uninit@0xd, skip_gpio_cfg@0xe, skip_psel_cfg@0xf. Corrected sonnet's shifted labels (it called 0x4=scl_pin/0x8=sda_pin/0xd=frequency; correct is 0x4=sda_pin, 0x8=frequency, 0xd=hold_bus_uninit). */
struct __attribute__((packed)) g1_layout_nrfx_twim_config_t__param_0347 {
    uint8_t _pad_0x0[0x4];
    uint8_t sda_pin[0x4]; /* catalog type: uint32_t; SDK member: sda_pin */
    uint8_t frequency[0x4]; /* catalog type: uint32_t; SDK member: frequency */
    uint8_t _pad_0xc[0x1];
    uint8_t hold_bus_uninit[0x1]; /* catalog type: uint8_t; SDK member: hold_bus_uninit */
    uint8_t skip_gpio_cfg[0x1]; /* catalog type: uint8_t; SDK member: skip_gpio_cfg */
    uint8_t skip_psel_cfg[0x1]; /* catalog type: uint8_t; SDK member: skip_psel_cfg */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_nrfx_twim_config_t__param_0347, sda_pin) == 0x4, "g1_layout_nrfx_twim_config_t__param_0347.sda_pin");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_config_t__param_0347, frequency) == 0x8, "g1_layout_nrfx_twim_config_t__param_0347.frequency");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_config_t__param_0347, hold_bus_uninit) == 0xd, "g1_layout_nrfx_twim_config_t__param_0347.hold_bus_uninit");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_config_t__param_0347, skip_gpio_cfg) == 0xe, "g1_layout_nrfx_twim_config_t__param_0347.skip_gpio_cfg");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_config_t__param_0347, skip_psel_cfg) == 0xf, "g1_layout_nrfx_twim_config_t__param_0347.skip_psel_cfg");
_Static_assert(sizeof(struct g1_layout_nrfx_twim_config_t__param_0347) >= 0x13, "g1_layout_nrfx_twim_config_t__param_0347.size");

/* param_0348 | library | nrfx TWIM (I2C master) peripheral configuration used by twim_configure and nrfx_twim_init; SCL and SDA pin fields. | D1+D2 verified
 * review: nrfx_twim_config_t (nrfx/drivers/include/nrfx_twim.h) — sonnet mapped scl_pin@0x1, sda_pin@0x4. Real nrfx_twim_config_t begins with scl/sda pins but exact packing not re-checked here; library_verified=false. */
struct __attribute__((packed)) g1_layout_nrfx_twim_config__param_0348 {
    uint8_t _pad_0x0[0x1];
    uint8_t scl_pin[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x2];
    uint8_t sda_pin[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_twim_config__param_0348, scl_pin) == 0x1, "g1_layout_nrfx_twim_config__param_0348.scl_pin");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_config__param_0348, sda_pin) == 0x4, "g1_layout_nrfx_twim_config__param_0348.sda_pin");
_Static_assert(sizeof(struct g1_layout_nrfx_twim_config__param_0348) >= 0x5, "g1_layout_nrfx_twim_config__param_0348.size");

/* param_0349 | library | nrfx TWIM (I2C master) driver control block (config, transfer descriptors, IRQ context) used by nrfx_twim_irq_handler/nrfx_twim_xfer/xfer_completeness_check. | D1+D2 verified
 * review: ~0x58c object; this is the file-static per-instance control block inside nrfx_twim.c, not the small public nrfx_twim_t handle, and its layout is not in a public header, so unverified. Kept all 23 offsets. */
struct __attribute__((packed)) g1_layout_nrfx_twim_control_block__param_0349 {
    uint8_t _pad_0x0[0x1];
    uint8_t drv_state[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x6];
    uint8_t p_reg_or_addr[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x8];
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x8];
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x24[0xe0];
    uint8_t field_0x104[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x108[0x1c];
    uint8_t field_0x124[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x128[0x20];
    uint8_t field_0x148[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14c[0x10];
    uint8_t field_0x15c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x160[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x164[0x9c];
    uint8_t xfer_flags[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x204[0x100];
    uint8_t field_0x304[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x308[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x30c[0x1b8];
    uint8_t field_0x4c4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4c8[0x38];
    uint8_t field_0x500[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x504[0x30];
    uint8_t field_0x534[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x538[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x53c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x540[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x544[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x548[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x54c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x550[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x554[0x34];
    uint8_t field_0x588[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, drv_state) == 0x1, "g1_layout_nrfx_twim_control_block__param_0349.drv_state");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, p_reg_or_addr) == 0x8, "g1_layout_nrfx_twim_control_block__param_0349.p_reg_or_addr");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x14) == 0x14, "g1_layout_nrfx_twim_control_block__param_0349.field_0x14");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x20) == 0x20, "g1_layout_nrfx_twim_control_block__param_0349.field_0x20");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x104) == 0x104, "g1_layout_nrfx_twim_control_block__param_0349.field_0x104");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x124) == 0x124, "g1_layout_nrfx_twim_control_block__param_0349.field_0x124");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x148) == 0x148, "g1_layout_nrfx_twim_control_block__param_0349.field_0x148");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x15c) == 0x15c, "g1_layout_nrfx_twim_control_block__param_0349.field_0x15c");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x160) == 0x160, "g1_layout_nrfx_twim_control_block__param_0349.field_0x160");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, xfer_flags) == 0x200, "g1_layout_nrfx_twim_control_block__param_0349.xfer_flags");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x304) == 0x304, "g1_layout_nrfx_twim_control_block__param_0349.field_0x304");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x308) == 0x308, "g1_layout_nrfx_twim_control_block__param_0349.field_0x308");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x4c4) == 0x4c4, "g1_layout_nrfx_twim_control_block__param_0349.field_0x4c4");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x500) == 0x500, "g1_layout_nrfx_twim_control_block__param_0349.field_0x500");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x534) == 0x534, "g1_layout_nrfx_twim_control_block__param_0349.field_0x534");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x538) == 0x538, "g1_layout_nrfx_twim_control_block__param_0349.field_0x538");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x53c) == 0x53c, "g1_layout_nrfx_twim_control_block__param_0349.field_0x53c");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x540) == 0x540, "g1_layout_nrfx_twim_control_block__param_0349.field_0x540");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x544) == 0x544, "g1_layout_nrfx_twim_control_block__param_0349.field_0x544");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x548) == 0x548, "g1_layout_nrfx_twim_control_block__param_0349.field_0x548");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x54c) == 0x54c, "g1_layout_nrfx_twim_control_block__param_0349.field_0x54c");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x550) == 0x550, "g1_layout_nrfx_twim_control_block__param_0349.field_0x550");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_control_block__param_0349, field_0x588) == 0x588, "g1_layout_nrfx_twim_control_block__param_0349.field_0x588");
_Static_assert(sizeof(struct g1_layout_nrfx_twim_control_block__param_0349) >= 0x58c, "g1_layout_nrfx_twim_control_block__param_0349.size");

/* param_0350 | library | nrfx TWIM (I2C master) control block used by IRQ handler and transfer-completeness check (handler/ctx, primary/secondary buf ptrs+lengths, address, error byte). | D1+D2 verified
 * review: nrfx TWIM cb is a static in nrfx_twim.c, not a public header; unverifiable. Ghidra flags overlaps at 0x8 (width4 into gap1) and 0x20 (width4 into gap3) => is_union=true. Kept offsets verbatim. */
struct __attribute__((packed)) g1_layout_nrfx_twim_cb__param_0350 {
    uint8_t _pad_0x0[0x4];
    uint8_t handler_or_ctx[0x4]; /* catalog type: void* */
    uint8_t field_0x8[0x1]; /* catalog type: uint32_t */
    uint8_t field_0x9[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xa[0x2];
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t p_primary_buf[0x4]; /* catalog type: void* */
    uint8_t primary_length[0x4]; /* catalog type: uint32_t */
    uint8_t p_secondary_buf[0x4]; /* catalog type: void* */
    uint8_t secondary_length[0x4]; /* catalog type: uint32_t */
    uint8_t address_or_flags[0x3]; /* catalog type: uint32_t */
    uint8_t field_0x23[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x24[0x1];
    uint8_t error_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_nrfx_twim_cb__param_0350, handler_or_ctx) == 0x4, "g1_layout_nrfx_twim_cb__param_0350.handler_or_ctx");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_cb__param_0350, field_0x8) == 0x8, "g1_layout_nrfx_twim_cb__param_0350.field_0x8");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_cb__param_0350, field_0x9) == 0x9, "g1_layout_nrfx_twim_cb__param_0350.field_0x9");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_cb__param_0350, field_0xc) == 0xc, "g1_layout_nrfx_twim_cb__param_0350.field_0xc");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_cb__param_0350, p_primary_buf) == 0x10, "g1_layout_nrfx_twim_cb__param_0350.p_primary_buf");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_cb__param_0350, primary_length) == 0x14, "g1_layout_nrfx_twim_cb__param_0350.primary_length");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_cb__param_0350, p_secondary_buf) == 0x18, "g1_layout_nrfx_twim_cb__param_0350.p_secondary_buf");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_cb__param_0350, secondary_length) == 0x1c, "g1_layout_nrfx_twim_cb__param_0350.secondary_length");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_cb__param_0350, address_or_flags) == 0x20, "g1_layout_nrfx_twim_cb__param_0350.address_or_flags");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_cb__param_0350, field_0x23) == 0x23, "g1_layout_nrfx_twim_cb__param_0350.field_0x23");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_cb__param_0350, error_byte) == 0x25, "g1_layout_nrfx_twim_cb__param_0350.error_byte");
_Static_assert(sizeof(struct g1_layout_nrfx_twim_cb__param_0350) >= 0x29, "g1_layout_nrfx_twim_cb__param_0350.size");

/* param_0353 | G1-original | param_2 of nrfx_twim_xfer - a TWI(M) transfer descriptor (buffer/length words). | D1+D2 verified
 * review: Separated from global_0840 collision group. Corrected sonnet's high-confidence nrfx_twim_xfer_desc_t claim: real nrfx_twim_xfer_desc_t leads with type/address bytes, not four aligned uint32; observed 4-word shape does NOT match, so is_library=false. */
struct __attribute__((packed)) g1_layout_twim_xfer_desc__param_0353 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_twim_xfer_desc__param_0353, field_0x4) == 0x4, "g1_layout_twim_xfer_desc__param_0353.field_0x4");
_Static_assert(offsetof(struct g1_layout_twim_xfer_desc__param_0353, field_0x8) == 0x8, "g1_layout_twim_xfer_desc__param_0353.field_0x8");
_Static_assert(offsetof(struct g1_layout_twim_xfer_desc__param_0353, field_0xc) == 0xc, "g1_layout_twim_xfer_desc__param_0353.field_0xc");
_Static_assert(offsetof(struct g1_layout_twim_xfer_desc__param_0353, field_0x10) == 0x10, "g1_layout_twim_xfer_desc__param_0353.field_0x10");
_Static_assert(sizeof(struct g1_layout_twim_xfer_desc__param_0353) >= 0x14, "g1_layout_twim_xfer_desc__param_0353.size");

/* param_0360 | library | param_1 of metal_register_generic_device (libmetal): region/attribute block within struct metal_device (four consecutive words). | D1+D2 verified
 * review: metal_register_generic_device is an app wrapper; only four words at 0x1c-0x28 observed, insufficient to pin against struct metal_device. */
struct __attribute__((packed)) g1_layout_metal_device_region_view__param_0360 {
    uint8_t _pad_0x0[0x1c];
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x28[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_metal_device_region_view__param_0360, field_0x1c) == 0x1c, "g1_layout_metal_device_region_view__param_0360.field_0x1c");
_Static_assert(offsetof(struct g1_layout_metal_device_region_view__param_0360, field_0x20) == 0x20, "g1_layout_metal_device_region_view__param_0360.field_0x20");
_Static_assert(offsetof(struct g1_layout_metal_device_region_view__param_0360, field_0x24) == 0x24, "g1_layout_metal_device_region_view__param_0360.field_0x24");
_Static_assert(offsetof(struct g1_layout_metal_device_region_view__param_0360, field_0x28) == 0x28, "g1_layout_metal_device_region_view__param_0360.field_0x28");
_Static_assert(sizeof(struct g1_layout_metal_device_region_view__param_0360) >= 0x2c, "g1_layout_metal_device_region_view__param_0360.size");

/* param_0362 | library | libmetal bus descriptor registered via metal_bus_register_device: name pointer near the front and device-list pointers near the end. | D1+D2 verified
 * review: libmetal bus struct plausible; not offset-verified against a pinned libmetal header, so library_verified=false. */
struct __attribute__((packed)) g1_layout_metal_bus__param_0362 {
    uint8_t _pad_0x0[0x4];
    uint8_t name[0x4]; /* catalog type: const char * */
    uint8_t ops_or_next[0x4]; /* catalog type: void * */
    uint8_t _pad_0xc[0x38];
    uint8_t dev_list_head[0x4]; /* catalog type: void * */
    uint8_t dev_list_tail[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_metal_bus__param_0362, name) == 0x4, "g1_layout_metal_bus__param_0362.name");
_Static_assert(offsetof(struct g1_layout_metal_bus__param_0362, ops_or_next) == 0x8, "g1_layout_metal_bus__param_0362.ops_or_next");
_Static_assert(offsetof(struct g1_layout_metal_bus__param_0362, dev_list_head) == 0x44, "g1_layout_metal_bus__param_0362.dev_list_head");
_Static_assert(offsetof(struct g1_layout_metal_bus__param_0362, dev_list_tail) == 0x48, "g1_layout_metal_bus__param_0362.dev_list_tail");
_Static_assert(sizeof(struct g1_layout_metal_bus__param_0362) >= 0x4c, "g1_layout_metal_bus__param_0362.size");

/* param_0364 | library | LC3 codec attack-detector substate accessed by lc3_attdet_run (param_4): two state/index words. | D1+D2 verified
 * review: LC3 codec internal; no public named struct to verify offsets against. library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_lc3_attdet_state__param_0364 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: int32_t */
    uint8_t field_0x8[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_attdet_state__param_0364, field_0x4) == 0x4, "g1_layout_lc3_attdet_state__param_0364.field_0x4");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_state__param_0364, field_0x8) == 0x8, "g1_layout_lc3_attdet_state__param_0364.field_0x8");
_Static_assert(sizeof(struct g1_layout_lc3_attdet_state__param_0364) >= 0xc, "g1_layout_lc3_attdet_state__param_0364.size");

/* param_0365 | G1-original | LC3 codec bit-allocation context used by lc3_setup_bits (nbits budget/used pair). | D1+D2 verified
 * review: G1-adapted liblc3 internal; exact header not verifiable. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_lc3_bit_budget_ctx__param_0365 {
    uint8_t _pad_0x0[0x4];
    uint8_t nbits_budget[0x4]; /* catalog type: int32_t */
    uint8_t nbits_used[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_bit_budget_ctx__param_0365, nbits_budget) == 0x4, "g1_layout_lc3_bit_budget_ctx__param_0365.nbits_budget");
_Static_assert(offsetof(struct g1_layout_lc3_bit_budget_ctx__param_0365, nbits_used) == 0x8, "g1_layout_lc3_bit_budget_ctx__param_0365.nbits_used");
_Static_assert(sizeof(struct g1_layout_lc3_bit_budget_ctx__param_0365) >= 0xc, "g1_layout_lc3_bit_budget_ctx__param_0365.size");

/* param_0366 | library | LC3 codec bitstream writer/reader state shared across lc3_put_bits_generic/ac_write_renorm/ltpf/sns/spec/tns put helpers: counters/accumulators plus buffer pointers. | D1+D2 verified
 * review: Strong identity from the 8-member lc3 encoder set. Buffer pointers at 0x2c/0x30 and accumulator run 0x4-0x24 consistent with liblc3 bit writer, but exact struct offsets not header-verified. */
struct __attribute__((packed)) g1_layout_lc3_bits_t__param_0366 {
    uint8_t _pad_0x0[0x4];
    uint8_t nbits_or_pos[0x4]; /* catalog type: uint32_t */
    uint8_t cache[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x4];
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x28[0x4];
    uint8_t buffer[0x4]; /* catalog type: uint8_t* */
    uint8_t buffer_cursor[0x4]; /* catalog type: uint8_t* */
    uint8_t field_0x34[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_bits_t__param_0366, nbits_or_pos) == 0x4, "g1_layout_lc3_bits_t__param_0366.nbits_or_pos");
_Static_assert(offsetof(struct g1_layout_lc3_bits_t__param_0366, cache) == 0x8, "g1_layout_lc3_bits_t__param_0366.cache");
_Static_assert(offsetof(struct g1_layout_lc3_bits_t__param_0366, field_0xc) == 0xc, "g1_layout_lc3_bits_t__param_0366.field_0xc");
_Static_assert(offsetof(struct g1_layout_lc3_bits_t__param_0366, field_0x10) == 0x10, "g1_layout_lc3_bits_t__param_0366.field_0x10");
_Static_assert(offsetof(struct g1_layout_lc3_bits_t__param_0366, field_0x14) == 0x14, "g1_layout_lc3_bits_t__param_0366.field_0x14");
_Static_assert(offsetof(struct g1_layout_lc3_bits_t__param_0366, field_0x1c) == 0x1c, "g1_layout_lc3_bits_t__param_0366.field_0x1c");
_Static_assert(offsetof(struct g1_layout_lc3_bits_t__param_0366, field_0x20) == 0x20, "g1_layout_lc3_bits_t__param_0366.field_0x20");
_Static_assert(offsetof(struct g1_layout_lc3_bits_t__param_0366, field_0x24) == 0x24, "g1_layout_lc3_bits_t__param_0366.field_0x24");
_Static_assert(offsetof(struct g1_layout_lc3_bits_t__param_0366, buffer) == 0x2c, "g1_layout_lc3_bits_t__param_0366.buffer");
_Static_assert(offsetof(struct g1_layout_lc3_bits_t__param_0366, buffer_cursor) == 0x30, "g1_layout_lc3_bits_t__param_0366.buffer_cursor");
_Static_assert(offsetof(struct g1_layout_lc3_bits_t__param_0366, field_0x34) == 0x34, "g1_layout_lc3_bits_t__param_0366.field_0x34");
_Static_assert(sizeof(struct g1_layout_lc3_bits_t__param_0366) >= 0x38, "g1_layout_lc3_bits_t__param_0366.size");

/* param_0367 | library | LC3 (liblc3) bitstream writer/accumulator state used by lc3_flush_bits: accumulator, bit counters, byte position, and buffer pointers. | D1+D2 verified
 * review: Kept naming; offsets unchanged. liblc3 lc3_bits/accu struct is internal (not in a pinned header); library_verified=false. */
struct __attribute__((packed)) g1_layout_lc3_bits_state__param_0367 {
    uint8_t _pad_0x0[0x4];
    uint8_t accumulator[0x4]; /* catalog type: uint32_t */
    uint8_t nbits_acc[0x4]; /* catalog type: uint32_t */
    uint8_t position[0x4]; /* catalog type: uint32_t */
    uint8_t nbits_out[0x4]; /* catalog type: uint32_t */
    uint8_t overflow_flag[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x4];
    uint8_t buf_offset[0x4]; /* catalog type: uint32_t */
    uint8_t buf_len[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x24[0x8];
    uint8_t buf_ptr[0x4]; /* catalog type: void* */
    uint8_t buf_end_ptr[0x4]; /* catalog type: void* */
    uint8_t nbytes[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_bits_state__param_0367, accumulator) == 0x4, "g1_layout_lc3_bits_state__param_0367.accumulator");
_Static_assert(offsetof(struct g1_layout_lc3_bits_state__param_0367, nbits_acc) == 0x8, "g1_layout_lc3_bits_state__param_0367.nbits_acc");
_Static_assert(offsetof(struct g1_layout_lc3_bits_state__param_0367, position) == 0xc, "g1_layout_lc3_bits_state__param_0367.position");
_Static_assert(offsetof(struct g1_layout_lc3_bits_state__param_0367, nbits_out) == 0x10, "g1_layout_lc3_bits_state__param_0367.nbits_out");
_Static_assert(offsetof(struct g1_layout_lc3_bits_state__param_0367, overflow_flag) == 0x14, "g1_layout_lc3_bits_state__param_0367.overflow_flag");
_Static_assert(offsetof(struct g1_layout_lc3_bits_state__param_0367, buf_offset) == 0x1c, "g1_layout_lc3_bits_state__param_0367.buf_offset");
_Static_assert(offsetof(struct g1_layout_lc3_bits_state__param_0367, buf_len) == 0x20, "g1_layout_lc3_bits_state__param_0367.buf_len");
_Static_assert(offsetof(struct g1_layout_lc3_bits_state__param_0367, buf_ptr) == 0x2c, "g1_layout_lc3_bits_state__param_0367.buf_ptr");
_Static_assert(offsetof(struct g1_layout_lc3_bits_state__param_0367, buf_end_ptr) == 0x30, "g1_layout_lc3_bits_state__param_0367.buf_end_ptr");
_Static_assert(offsetof(struct g1_layout_lc3_bits_state__param_0367, nbytes) == 0x34, "g1_layout_lc3_bits_state__param_0367.nbytes");
_Static_assert(sizeof(struct g1_layout_lc3_bits_state__param_0367) >= 0x38, "g1_layout_lc3_bits_state__param_0367.size");

/* param_0368 | library | liblc3 bandwidth-detector running state updated by lc3_bwdet_put_bw. | D1+D2 verified
 * review: liblc3 internal state, not a public struct; offsets not verifiable. Kept offsets. */
struct __attribute__((packed)) g1_layout_lc3_bwdet_state__param_0368 {
    uint8_t _pad_0x0[0x1c];
    uint8_t nbits_bw[0x4]; /* catalog type: uint32_t */
    uint8_t bw_band_idx[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_bwdet_state__param_0368, nbits_bw) == 0x1c, "g1_layout_lc3_bwdet_state__param_0368.nbits_bw");
_Static_assert(offsetof(struct g1_layout_lc3_bwdet_state__param_0368, bw_band_idx) == 0x20, "g1_layout_lc3_bwdet_state__param_0368.bw_band_idx");
_Static_assert(sizeof(struct g1_layout_lc3_bwdet_state__param_0368) >= 0x24, "g1_layout_lc3_bwdet_state__param_0368.size");

/* param_0369 | library | LC3 codec context passed to lc3_load_s24_3le: a small header field plus a count and buffer pointer after a large sample buffer region. | D1+D2 verified
 * review: liblc3 internal state, no pinned header; offsets unverified. */
struct __attribute__((packed)) g1_layout_lc3_encoder_state__param_0369 {
    uint8_t _pad_0x0[0x8];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x494];
    uint8_t sample_count_or_stride[0x4]; /* catalog type: int32_t */
    uint8_t buf_ptr[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_lc3_encoder_state__param_0369, field_0x8) == 0x8, "g1_layout_lc3_encoder_state__param_0369.field_0x8");
_Static_assert(offsetof(struct g1_layout_lc3_encoder_state__param_0369, sample_count_or_stride) == 0x4a0, "g1_layout_lc3_encoder_state__param_0369.sample_count_or_stride");
_Static_assert(offsetof(struct g1_layout_lc3_encoder_state__param_0369, buf_ptr) == 0x4a4, "g1_layout_lc3_encoder_state__param_0369.buf_ptr");
_Static_assert(sizeof(struct g1_layout_lc3_encoder_state__param_0369) >= 0x4a8, "g1_layout_lc3_encoder_state__param_0369.size");

/* param_0370 | library | LC3 24-bit PCM sample-buffer descriptor (sample ptr + count) consumed by lc3_load_s24_3le. | D1+D2 verified
 * review: liblc3 internal; ptr/count pair at 0x4/0x8, unverified. */
struct __attribute__((packed)) g1_layout_lc3_pcm_buf_desc__param_0370 {
    uint8_t _pad_0x0[0x4];
    uint8_t samples_ptr[0x4]; /* catalog type: void * */
    uint8_t num_samples[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_pcm_buf_desc__param_0370, samples_ptr) == 0x4, "g1_layout_lc3_pcm_buf_desc__param_0370.samples_ptr");
_Static_assert(offsetof(struct g1_layout_lc3_pcm_buf_desc__param_0370, num_samples) == 0x8, "g1_layout_lc3_pcm_buf_desc__param_0370.num_samples");
_Static_assert(sizeof(struct g1_layout_lc3_pcm_buf_desc__param_0370) >= 0xc, "g1_layout_lc3_pcm_buf_desc__param_0370.size");

/* param_0371 | library | LC3 sample-load context used by lc3_load_s24: bit position + trailing nbytes + data pointer. | D1+D2 verified
 * review: liblc3 internal; 0x8/0x4a0/0x4a4 offsets not verifiable against a shipped header. verified=false. */
struct __attribute__((packed)) g1_layout_lc3_load_ctx__param_0371 {
    uint8_t _pad_0x0[0x8];
    uint8_t bit_pos[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x494];
    uint8_t nbytes[0x4]; /* catalog type: uint32_t */
    uint8_t data[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_lc3_load_ctx__param_0371, bit_pos) == 0x8, "g1_layout_lc3_load_ctx__param_0371.bit_pos");
_Static_assert(offsetof(struct g1_layout_lc3_load_ctx__param_0371, nbytes) == 0x4a0, "g1_layout_lc3_load_ctx__param_0371.nbytes");
_Static_assert(offsetof(struct g1_layout_lc3_load_ctx__param_0371, data) == 0x4a4, "g1_layout_lc3_load_ctx__param_0371.data");
_Static_assert(sizeof(struct g1_layout_lc3_load_ctx__param_0371) >= 0x4a8, "g1_layout_lc3_load_ctx__param_0371.size");

/* param_0372 | library | param_1 of lc3_load_float: LC3 codec bitstream/buffer context (early word + late count word + pointer at 0x4a4). | D1+D2 verified
 * review: liblc3 internal state; sparse observation, unverified. */
struct __attribute__((packed)) g1_layout_lc3_bitstream_ctx__param_0372 {
    uint8_t _pad_0x0[0x8];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x494];
    uint8_t field_0x4a0[0x4]; /* catalog type: int32_t */
    uint8_t field_0x4a4[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_lc3_bitstream_ctx__param_0372, field_0x8) == 0x8, "g1_layout_lc3_bitstream_ctx__param_0372.field_0x8");
_Static_assert(offsetof(struct g1_layout_lc3_bitstream_ctx__param_0372, field_0x4a0) == 0x4a0, "g1_layout_lc3_bitstream_ctx__param_0372.field_0x4a0");
_Static_assert(offsetof(struct g1_layout_lc3_bitstream_ctx__param_0372, field_0x4a4) == 0x4a4, "g1_layout_lc3_bitstream_ctx__param_0372.field_0x4a4");
_Static_assert(sizeof(struct g1_layout_lc3_bitstream_ctx__param_0372) >= 0x4a8, "g1_layout_lc3_bitstream_ctx__param_0372.size");

/* param_0373 | library | LC3 codec encoder state (param_1) passed to lc3_encode: frame-config words near the start and derived analysis outputs near the end. | D1+D2 verified
 * review: liblc3 encoder state; internal layout not in pinned headers, so library_verified=false. */
struct __attribute__((packed)) g1_layout_lc3_encoder_ctx__param_0373 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x494];
    uint8_t field_0x4a0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x4a4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x4a8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_encoder_ctx__param_0373, field_0x4) == 0x4, "g1_layout_lc3_encoder_ctx__param_0373.field_0x4");
_Static_assert(offsetof(struct g1_layout_lc3_encoder_ctx__param_0373, field_0x8) == 0x8, "g1_layout_lc3_encoder_ctx__param_0373.field_0x8");
_Static_assert(offsetof(struct g1_layout_lc3_encoder_ctx__param_0373, field_0x4a0) == 0x4a0, "g1_layout_lc3_encoder_ctx__param_0373.field_0x4a0");
_Static_assert(offsetof(struct g1_layout_lc3_encoder_ctx__param_0373, field_0x4a4) == 0x4a4, "g1_layout_lc3_encoder_ctx__param_0373.field_0x4a4");
_Static_assert(offsetof(struct g1_layout_lc3_encoder_ctx__param_0373, field_0x4a8) == 0x4a8, "g1_layout_lc3_encoder_ctx__param_0373.field_0x4a8");
_Static_assert(sizeof(struct g1_layout_lc3_encoder_ctx__param_0373) >= 0x4ac, "g1_layout_lc3_encoder_ctx__param_0373.size");

/* param_0374 | library | LC3 long-term pitch prediction (LTPF) analysis state used by lc3_ltpf_detect_pitch/lc3_ltpf_analyse: pitch index/gains header plus a large (0x474) history buffer and a trailing length word. | D1+D2 verified
 * review: LC3 codec internal; no public named struct to verify against. Kept float typing at 0x8/0xc. library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_lc3_ltpf_state__param_0374 {
    uint8_t _pad_0x0[0x4];
    uint8_t pitch_index[0x4]; /* catalog type: uint32_t */
    uint8_t pitch_gain[0x4]; /* catalog type: float */
    uint8_t prev_gain[0x4]; /* catalog type: float */
    uint8_t _pad_0x10[0x474];
    uint8_t history_len[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_ltpf_state__param_0374, pitch_index) == 0x4, "g1_layout_lc3_ltpf_state__param_0374.pitch_index");
_Static_assert(offsetof(struct g1_layout_lc3_ltpf_state__param_0374, pitch_gain) == 0x8, "g1_layout_lc3_ltpf_state__param_0374.pitch_gain");
_Static_assert(offsetof(struct g1_layout_lc3_ltpf_state__param_0374, prev_gain) == 0xc, "g1_layout_lc3_ltpf_state__param_0374.prev_gain");
_Static_assert(offsetof(struct g1_layout_lc3_ltpf_state__param_0374, history_len) == 0x484, "g1_layout_lc3_ltpf_state__param_0374.history_len");
_Static_assert(sizeof(struct g1_layout_lc3_ltpf_state__param_0374) >= 0x488, "g1_layout_lc3_ltpf_state__param_0374.size");

/* param_0375 | G1-original | LC3 LTPF (long-term post filter) pitch-detection sample/coefficient buffer used by lc3_ltpf_detect_pitch; uniform 32-bit array 0x4..0xfc. | D1+D2 verified
 * review: 63 uniform-stride 32-bit fields collapse to one array. Kept as int32 samples[63] starting at 0x4. G1-adapted liblc3 internal; offsets unchanged. */
struct __attribute__((packed)) g1_layout_lc3_ltpf_pitch_buf__param_0375 {
    uint8_t _pad_0x0[0x4];
    uint8_t samples[0x4]; /* catalog type: int32_t[63] */
    uint8_t _tail_pad[0xf8];
};
_Static_assert(offsetof(struct g1_layout_lc3_ltpf_pitch_buf__param_0375, samples) == 0x4, "g1_layout_lc3_ltpf_pitch_buf__param_0375.samples");
_Static_assert(sizeof(struct g1_layout_lc3_ltpf_pitch_buf__param_0375) >= 0x100, "g1_layout_lc3_ltpf_pitch_buf__param_0375.size");

/* param_0381 | library | LC3 (liblc3) SNS spectral-noise-shaping coefficient buffer, read as a uniform 15-word array by lc3_sns_unquantize and lc3_sns_spectral_shaping. | D1+D2 verified
 * review: This footprint-collision group actually holds two unrelated object families. Merged the three LC3 SNS array params (unquantize p3, unquantize p6, spectral_shaping p3) into one coefficient-buffer type — same library, same uniform-word-array access. Split the two tinycrypt AES params into a separate struct. Kept offsets exactly; the 15-word count is a generic array footprint, not a fixed liblc3 struct, so library_verified=false. */
struct __attribute__((packed)) g1_layout_lc3_sns_coeff_buffer__param_0381 {
    uint8_t _pad_0x0[0x4];
    uint8_t coeff_0[0x4]; /* catalog type: float */
    uint8_t coeff_1[0x4]; /* catalog type: float */
    uint8_t coeff_2[0x4]; /* catalog type: float */
    uint8_t coeff_3[0x4]; /* catalog type: float */
    uint8_t coeff_4[0x4]; /* catalog type: float */
    uint8_t coeff_5[0x4]; /* catalog type: float */
    uint8_t coeff_6[0x4]; /* catalog type: float */
    uint8_t coeff_7[0x4]; /* catalog type: float */
    uint8_t coeff_8[0x4]; /* catalog type: float */
    uint8_t coeff_9[0x4]; /* catalog type: float */
    uint8_t coeff_10[0x4]; /* catalog type: float */
    uint8_t coeff_11[0x4]; /* catalog type: float */
    uint8_t coeff_12[0x4]; /* catalog type: float */
    uint8_t coeff_13[0x4]; /* catalog type: float */
    uint8_t coeff_14[0x4]; /* catalog type: float */
};
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_0) == 0x4, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_0");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_1) == 0x8, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_1");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_2) == 0xc, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_2");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_3) == 0x10, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_3");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_4) == 0x14, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_4");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_5) == 0x18, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_5");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_6) == 0x1c, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_6");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_7) == 0x20, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_7");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_8) == 0x24, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_8");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_9) == 0x28, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_9");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_10) == 0x2c, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_10");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_11) == 0x30, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_11");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_12) == 0x34, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_12");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_13) == 0x38, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_13");
_Static_assert(offsetof(struct g1_layout_lc3_sns_coeff_buffer__param_0381, coeff_14) == 0x3c, "g1_layout_lc3_sns_coeff_buffer__param_0381.coeff_14");
_Static_assert(sizeof(struct g1_layout_lc3_sns_coeff_buffer__param_0381) >= 0x40, "g1_layout_lc3_sns_coeff_buffer__param_0381.size");

/* param_0384 | G1-original | LC3 codec SNS (spectral noise shaping) analysis state shared by lc3_sns_analyze (param_5) and lc3_sns_put_data (param_2). | D1+D2 verified
 * review: Genuine merge: param_0384 (lc3_sns_analyze) and param_0385 (lc3_sns_put_data) share the same footprint AND the same LC3 SNS subsystem — same object. Both members APPLICATION-class, so treated as G1-adapted liblc3 internal state, not a verifiable stock struct. is_union=true because 0x4 is accessed 4-wide over a 2-byte gap to 0x6. */
struct __attribute__((packed)) g1_layout_lc3_sns_state__param_0384 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x6[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x7[0x1];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x1];
    uint8_t flag_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_lc3_sns_state__param_0384, field_0x4) == 0x4, "g1_layout_lc3_sns_state__param_0384.field_0x4");
_Static_assert(offsetof(struct g1_layout_lc3_sns_state__param_0384, field_0x6) == 0x6, "g1_layout_lc3_sns_state__param_0384.field_0x6");
_Static_assert(offsetof(struct g1_layout_lc3_sns_state__param_0384, field_0x8) == 0x8, "g1_layout_lc3_sns_state__param_0384.field_0x8");
_Static_assert(offsetof(struct g1_layout_lc3_sns_state__param_0384, field_0xc) == 0xc, "g1_layout_lc3_sns_state__param_0384.field_0xc");
_Static_assert(offsetof(struct g1_layout_lc3_sns_state__param_0384, field_0x10) == 0x10, "g1_layout_lc3_sns_state__param_0384.field_0x10");
_Static_assert(offsetof(struct g1_layout_lc3_sns_state__param_0384, field_0x14) == 0x14, "g1_layout_lc3_sns_state__param_0384.field_0x14");
_Static_assert(offsetof(struct g1_layout_lc3_sns_state__param_0384, flag_byte) == 0x19, "g1_layout_lc3_sns_state__param_0384.flag_byte");
_Static_assert(sizeof(struct g1_layout_lc3_sns_state__param_0384) >= 0x1d, "g1_layout_lc3_sns_state__param_0384.size");

/* param_0388 | library | LC3 spectral 'side' encoding data passed to lc3_spec_put_side (param_4). | D1+D2 verified
 * review: Identity from callee; only a byte@0x2 and word@0x4 observed. */
struct __attribute__((packed)) g1_layout_lc3_side_data__param_0388 {
    uint8_t _pad_0x0[0x2];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x1];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_side_data__param_0388, field_0x2) == 0x2, "g1_layout_lc3_side_data__param_0388.field_0x2");
_Static_assert(offsetof(struct g1_layout_lc3_side_data__param_0388, field_0x4) == 0x4, "g1_layout_lc3_side_data__param_0388.field_0x4");
_Static_assert(sizeof(struct g1_layout_lc3_side_data__param_0388) >= 0x8, "g1_layout_lc3_side_data__param_0388.size");

/* param_0389 | library | Small scalar/flag parameter block passed to lc3_spec_encode (LC3 spectral encoding). | D1+D2 verified
 * review: Kept naming; offsets unchanged. Only an int and a flag byte observed; not enough to pin a liblc3 struct. */
struct __attribute__((packed)) g1_layout_lc3_spec_encode_ctx__param_0389 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: int32_t */
    uint8_t flag_0x8[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_lc3_spec_encode_ctx__param_0389, field_0x4) == 0x4, "g1_layout_lc3_spec_encode_ctx__param_0389.field_0x4");
_Static_assert(offsetof(struct g1_layout_lc3_spec_encode_ctx__param_0389, flag_0x8) == 0x8, "g1_layout_lc3_spec_encode_ctx__param_0389.flag_0x8");
_Static_assert(sizeof(struct g1_layout_lc3_spec_encode_ctx__param_0389) >= 0xc, "g1_layout_lc3_spec_encode_ctx__param_0389.size");

/* param_0391 | library | liblc3 Temporal Noise Shaping analysis parameter block passed to lc3_tns_analyze. | D1+D2 verified
 * review: liblc3 internal; not verifiable against a header. Kept offsets. */
struct __attribute__((packed)) g1_layout_lc3_tns_params__param_0391 {
    uint8_t _pad_0x0[0x1];
    uint8_t num_filters[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x2];
    uint8_t rc_order_or_bits[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_tns_params__param_0391, num_filters) == 0x1, "g1_layout_lc3_tns_params__param_0391.num_filters");
_Static_assert(offsetof(struct g1_layout_lc3_tns_params__param_0391, rc_order_or_bits) == 0x4, "g1_layout_lc3_tns_params__param_0391.rc_order_or_bits");
_Static_assert(sizeof(struct g1_layout_lc3_tns_params__param_0391) >= 0x8, "g1_layout_lc3_tns_params__param_0391.size");

/* param_0392 | library | Per-subframe bit-count table consumed uniformly by lc3_tns_get_nbits (LC3 TNS coding): a leading flag byte and 17 int array entries. | D1+D2 verified
 * review: liblc3 internal; kept uniform int-array interpretation. Offsets ground-truth. */
struct __attribute__((packed)) g1_layout_lc3_tns_nbits_table__param_0392 {
    uint8_t _pad_0x0[0x1];
    uint8_t flag_0x1[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x6];
    uint8_t nbits_0[0x4]; /* catalog type: int32_t */
    uint8_t nbits_1[0x4]; /* catalog type: int32_t */
    uint8_t nbits_2[0x4]; /* catalog type: int32_t */
    uint8_t nbits_3[0x4]; /* catalog type: int32_t */
    uint8_t nbits_4[0x4]; /* catalog type: int32_t */
    uint8_t nbits_5[0x4]; /* catalog type: int32_t */
    uint8_t nbits_6[0x4]; /* catalog type: int32_t */
    uint8_t nbits_7[0x4]; /* catalog type: int32_t */
    uint8_t nbits_8[0x4]; /* catalog type: int32_t */
    uint8_t nbits_9[0x4]; /* catalog type: int32_t */
    uint8_t nbits_10[0x4]; /* catalog type: int32_t */
    uint8_t nbits_11[0x4]; /* catalog type: int32_t */
    uint8_t nbits_12[0x4]; /* catalog type: int32_t */
    uint8_t nbits_13[0x4]; /* catalog type: int32_t */
    uint8_t nbits_14[0x4]; /* catalog type: int32_t */
    uint8_t nbits_15[0x4]; /* catalog type: int32_t */
    uint8_t nbits_16[0x4]; /* catalog type: int32_t */
    uint8_t nbits_17[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, flag_0x1) == 0x1, "g1_layout_lc3_tns_nbits_table__param_0392.flag_0x1");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_0) == 0x8, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_0");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_1) == 0xc, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_1");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_2) == 0x10, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_2");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_3) == 0x14, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_3");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_4) == 0x18, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_4");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_5) == 0x1c, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_5");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_6) == 0x20, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_6");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_7) == 0x24, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_7");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_8) == 0x28, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_8");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_9) == 0x2c, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_9");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_10) == 0x30, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_10");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_11) == 0x34, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_11");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_12) == 0x38, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_12");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_13) == 0x3c, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_13");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_14) == 0x40, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_14");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_15) == 0x44, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_15");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_16) == 0x48, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_16");
_Static_assert(offsetof(struct g1_layout_lc3_tns_nbits_table__param_0392, nbits_17) == 0x4c, "g1_layout_lc3_tns_nbits_table__param_0392.nbits_17");
_Static_assert(sizeof(struct g1_layout_lc3_tns_nbits_table__param_0392) >= 0x50, "g1_layout_lc3_tns_nbits_table__param_0392.size");

/* param_0394 | library | OpenAMP/libmetal virtio device/virtqueue creation context shared by virtio_create_virtqueues and virtqueue_create (nRF5340 IPC). | D1+D2 verified
 * review: Both members are LIBRARY-class (OpenAMP). num_queues/vq_array/features/status fields; not verified against an OpenAMP header (not in the pinned Zephyr tree). */
struct __attribute__((packed)) g1_layout_virtio_device__param_0394 {
    uint8_t _pad_0x0[0x18];
    uint8_t num_queues[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x1c[0x4];
    uint8_t vq_array_ptr[0x4]; /* catalog type: void * */
    uint8_t _pad_0x24[0x4];
    uint8_t features[0x4]; /* catalog type: uint32_t */
    uint8_t status[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_virtio_device__param_0394, num_queues) == 0x18, "g1_layout_virtio_device__param_0394.num_queues");
_Static_assert(offsetof(struct g1_layout_virtio_device__param_0394, vq_array_ptr) == 0x20, "g1_layout_virtio_device__param_0394.vq_array_ptr");
_Static_assert(offsetof(struct g1_layout_virtio_device__param_0394, features) == 0x28, "g1_layout_virtio_device__param_0394.features");
_Static_assert(offsetof(struct g1_layout_virtio_device__param_0394, status) == 0x2c, "g1_layout_virtio_device__param_0394.status");
_Static_assert(sizeof(struct g1_layout_virtio_device__param_0394) >= 0x30, "g1_layout_virtio_device__param_0394.size");

/* param_0395 | library | VirtIO/OpenAMP virtqueue freed by virtqueue_free (dev/id word + two 16-bit count fields). | D1+D2 verified
 * review: OpenAMP virtqueue header not opened; only sparse fields (0x4,0xa,0x24) observed. verified=false. */
struct __attribute__((packed)) g1_layout_virtqueue__param_0395 {
    uint8_t _pad_0x0[0x4];
    uint8_t vq_dev_or_id[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x2];
    uint8_t vq_free_cnt[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xc[0x18];
    uint8_t vq_nentries[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0395, vq_dev_or_id) == 0x4, "g1_layout_virtqueue__param_0395.vq_dev_or_id");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0395, vq_free_cnt) == 0xa, "g1_layout_virtqueue__param_0395.vq_free_cnt");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0395, vq_nentries) == 0x24, "g1_layout_virtqueue__param_0395.vq_nentries");
_Static_assert(sizeof(struct g1_layout_virtqueue__param_0395) >= 0x28, "g1_layout_virtqueue__param_0395.size");

/* param_0397 | library | OpenAMP rpmsg-over-virtio device object accessed by rpmsg_virtio_tx_enqueue / send_copy / get_tx_buffer_wait: tx virtqueue fields and buffer pointers. | D1+D2 verified
 * review: 3 members; OpenAMP struct but offsets not verified against an available header. */
struct __attribute__((packed)) g1_layout_rpmsg_virtio_device__param_0397 {
    uint8_t _pad_0x0[0x94];
    uint8_t tx_vq_field[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x98[0x8];
    uint8_t config_field[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0xa4[0x4];
    uint8_t buf_size_or_count[0x4]; /* catalog type: int32_t */
    uint8_t buf_ptr[0x4]; /* catalog type: void * */
    uint8_t buf_len[0x4]; /* catalog type: uint32_t */
    uint8_t notify_or_shbuf_ptr[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_rpmsg_virtio_device__param_0397, tx_vq_field) == 0x94, "g1_layout_rpmsg_virtio_device__param_0397.tx_vq_field");
_Static_assert(offsetof(struct g1_layout_rpmsg_virtio_device__param_0397, config_field) == 0xa0, "g1_layout_rpmsg_virtio_device__param_0397.config_field");
_Static_assert(offsetof(struct g1_layout_rpmsg_virtio_device__param_0397, buf_size_or_count) == 0xa8, "g1_layout_rpmsg_virtio_device__param_0397.buf_size_or_count");
_Static_assert(offsetof(struct g1_layout_rpmsg_virtio_device__param_0397, buf_ptr) == 0xac, "g1_layout_rpmsg_virtio_device__param_0397.buf_ptr");
_Static_assert(offsetof(struct g1_layout_rpmsg_virtio_device__param_0397, buf_len) == 0xb0, "g1_layout_rpmsg_virtio_device__param_0397.buf_len");
_Static_assert(offsetof(struct g1_layout_rpmsg_virtio_device__param_0397, notify_or_shbuf_ptr) == 0xb4, "g1_layout_rpmsg_virtio_device__param_0397.notify_or_shbuf_ptr");
_Static_assert(sizeof(struct g1_layout_rpmsg_virtio_device__param_0397) >= 0xb8, "g1_layout_rpmsg_virtio_device__param_0397.size");

/* param_0398 | G1-original | G1-original audio sync ring-buffer with write/read cursor words, queried by sync_buffer_available_space. | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_audio_sync_ringbuf__param_0398 {
    uint8_t _pad_0x0[0x94];
    uint8_t write_idx[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x98[0x8];
    uint8_t read_idx[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_audio_sync_ringbuf__param_0398, write_idx) == 0x94, "g1_layout_audio_sync_ringbuf__param_0398.write_idx");
_Static_assert(offsetof(struct g1_layout_audio_sync_ringbuf__param_0398, read_idx) == 0xa0, "g1_layout_audio_sync_ringbuf__param_0398.read_idx");
_Static_assert(sizeof(struct g1_layout_audio_sync_ringbuf__param_0398) >= 0xa4, "g1_layout_audio_sync_ringbuf__param_0398.size");

/* param_0399 | G1-original | Configuration (param_2) passed to rpmsg_virtqueue_channel_init: descriptor count/align words at 0x10/0x14, a count/int at 0x24, and a vring/callback pointer at 0x2c. | D1+D2 verified
 * review: Ghidra hint marks this G1-original (0/1 library-class); it is a G1 wrapper config around OpenAMP vring setup rather than a stock OpenAMP struct, so is_library=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_rpmsg_vqueue_channel_cfg__param_0399 {
    uint8_t _pad_0x0[0x10];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0xc];
    uint8_t field_0x24[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x28[0x4];
    uint8_t vring_or_cb[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_rpmsg_vqueue_channel_cfg__param_0399, field_0x10) == 0x10, "g1_layout_rpmsg_vqueue_channel_cfg__param_0399.field_0x10");
_Static_assert(offsetof(struct g1_layout_rpmsg_vqueue_channel_cfg__param_0399, field_0x14) == 0x14, "g1_layout_rpmsg_vqueue_channel_cfg__param_0399.field_0x14");
_Static_assert(offsetof(struct g1_layout_rpmsg_vqueue_channel_cfg__param_0399, field_0x24) == 0x24, "g1_layout_rpmsg_vqueue_channel_cfg__param_0399.field_0x24");
_Static_assert(offsetof(struct g1_layout_rpmsg_vqueue_channel_cfg__param_0399, vring_or_cb) == 0x2c, "g1_layout_rpmsg_vqueue_channel_cfg__param_0399.vring_or_cb");
_Static_assert(sizeof(struct g1_layout_rpmsg_vqueue_channel_cfg__param_0399) >= 0x30, "g1_layout_rpmsg_vqueue_channel_cfg__param_0399.size");

/* param_0400 | G1-original | Virtqueue allocation descriptor passed to rpmsg_virtqueue_channel_init (flag/id byte plus a pointer+size pair). | D1+D2 verified
 * review: OpenAMP/rpmsg usage but treated as G1-original arg block; not verified. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_rpmsg_vq_alloc_info__param_0400 {
    uint8_t _pad_0x0[0x2];
    uint8_t flags_or_id[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x1];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_rpmsg_vq_alloc_info__param_0400, flags_or_id) == 0x2, "g1_layout_rpmsg_vq_alloc_info__param_0400.flags_or_id");
_Static_assert(offsetof(struct g1_layout_rpmsg_vq_alloc_info__param_0400, field_0x4) == 0x4, "g1_layout_rpmsg_vq_alloc_info__param_0400.field_0x4");
_Static_assert(offsetof(struct g1_layout_rpmsg_vq_alloc_info__param_0400, field_0x8) == 0x8, "g1_layout_rpmsg_vq_alloc_info__param_0400.field_0x8");
_Static_assert(sizeof(struct g1_layout_rpmsg_vq_alloc_info__param_0400) >= 0xc, "g1_layout_rpmsg_vq_alloc_info__param_0400.size");

/* param_0401 | library | OpenAMP rpmsg-virtio shared-memory pool descriptor used by rpmsg_virtqueue_channel_init and rpmsg_virtio_shm_pool_get_buffer. | D1+D2 verified
 * review: Identity from library member; two idx4 words only, offsets not header-verified. */
struct __attribute__((packed)) g1_layout_rpmsg_virtio_shm_pool__param_0401 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_rpmsg_virtio_shm_pool__param_0401, field_0x4) == 0x4, "g1_layout_rpmsg_virtio_shm_pool__param_0401.field_0x4");
_Static_assert(offsetof(struct g1_layout_rpmsg_virtio_shm_pool__param_0401, field_0x8) == 0x8, "g1_layout_rpmsg_virtio_shm_pool__param_0401.field_0x8");
_Static_assert(sizeof(struct g1_layout_rpmsg_virtio_shm_pool__param_0401) >= 0xc, "g1_layout_rpmsg_virtio_shm_pool__param_0401.size");

/* param_0402 | library | libmetal/OpenAMP I/O region descriptor used by rpmsg_virtqueue_channel_init and metal_io_block_set. | D1+D2 verified
 * review: metal_io_block_set(struct metal_io_region*, ...) confirms the type, but only 3 sparse fields (a code/fn-ptr word at 0x0, and idx4 at 0x8/0x28) observed; libmetal metal_io_region layout not pinned. library_verified=false. */
struct __attribute__((packed)) g1_layout_metal_io_region__param_0402 {
    uint8_t virt_or_ops[0x4]; /* catalog type: void* */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x1c];
    uint8_t field_0x28[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0402, virt_or_ops) == 0x0, "g1_layout_metal_io_region__param_0402.virt_or_ops");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0402, field_0x8) == 0x8, "g1_layout_metal_io_region__param_0402.field_0x8");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0402, field_0x28) == 0x28, "g1_layout_metal_io_region__param_0402.field_0x28");
_Static_assert(sizeof(struct g1_layout_metal_io_region__param_0402) >= 0x2c, "g1_layout_metal_io_region__param_0402.size");

/* param_0403 | library | Zephyr kernel memory-slab allocator object freed by k_mem_slab_free. | D1+D2 verified
 * review: VERIFIED against kernel.h: after wait_q + spinlock header (0xc bytes in this build), members run consecutively num_blocks, block_size, buffer, free_list, num_used — matching observed 0xc/0x10/0x14/0x18/0x1c exactly in order and type. */
struct __attribute__((packed)) g1_layout_k_mem_slab__param_0403 {
    uint8_t _pad_0x0[0xc];
    uint8_t num_blocks[0x4]; /* catalog type: uint32_t; SDK member: num_blocks */
    uint8_t block_size[0x4]; /* catalog type: size_t; SDK member: block_size */
    uint8_t buffer[0x4]; /* catalog type: char *; SDK member: buffer */
    uint8_t free_list[0x4]; /* catalog type: char *; SDK member: free_list */
    uint8_t num_used[0x4]; /* catalog type: uint32_t; SDK member: num_used */
};
_Static_assert(offsetof(struct g1_layout_k_mem_slab__param_0403, num_blocks) == 0xc, "g1_layout_k_mem_slab__param_0403.num_blocks");
_Static_assert(offsetof(struct g1_layout_k_mem_slab__param_0403, block_size) == 0x10, "g1_layout_k_mem_slab__param_0403.block_size");
_Static_assert(offsetof(struct g1_layout_k_mem_slab__param_0403, buffer) == 0x14, "g1_layout_k_mem_slab__param_0403.buffer");
_Static_assert(offsetof(struct g1_layout_k_mem_slab__param_0403, free_list) == 0x18, "g1_layout_k_mem_slab__param_0403.free_list");
_Static_assert(offsetof(struct g1_layout_k_mem_slab__param_0403, num_used) == 0x1c, "g1_layout_k_mem_slab__param_0403.num_used");
_Static_assert(sizeof(struct g1_layout_k_mem_slab__param_0403) >= 0x20, "g1_layout_k_mem_slab__param_0403.size");

/* param_0408 | library | Fragment of a Zephyr struct k_thread / scheduling control block touched by k_work_queue_start, sched_ready_queue_insert, and sched_thread_ready: thread-base scheduling fields, ready-queue linkage, and a swap/stack-info region. | D1+D2 verified
 * review: k_thread is a large struct built from many config-dependent sub-structs (thread_base, callee_saved, arch, stack_info); only a sparse fragment is observed and its exact offsets depend on Kconfig, so library_verified=false. */
struct __attribute__((packed)) g1_layout_k_thread__param_0408 {
    uint8_t _pad_0x0[0x4];
    uint8_t base_field0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x5];
    uint8_t sched_flag[0x1]; /* catalog type: uint8_t */
    uint8_t prio_or_flags[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xf[0x9];
    uint8_t ready_q_field[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1c[0xbc];
    uint8_t swap_data0[0x4]; /* catalog type: uint32_t */
    uint8_t swap_data1[0x4]; /* catalog type: uint32_t */
    uint8_t stack_info0[0x4]; /* catalog type: uint32_t */
    uint8_t stack_info1[0x4]; /* catalog type: uint32_t */
    uint8_t stack_info2[0x4]; /* catalog type: uint32_t */
    uint8_t stack_info3[0x4]; /* catalog type: uint32_t */
    uint8_t thread_state[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_k_thread__param_0408, base_field0) == 0x4, "g1_layout_k_thread__param_0408.base_field0");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0408, sched_flag) == 0xd, "g1_layout_k_thread__param_0408.sched_flag");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0408, prio_or_flags) == 0xe, "g1_layout_k_thread__param_0408.prio_or_flags");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0408, ready_q_field) == 0x18, "g1_layout_k_thread__param_0408.ready_q_field");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0408, swap_data0) == 0xd8, "g1_layout_k_thread__param_0408.swap_data0");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0408, swap_data1) == 0xdc, "g1_layout_k_thread__param_0408.swap_data1");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0408, stack_info0) == 0xe0, "g1_layout_k_thread__param_0408.stack_info0");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0408, stack_info1) == 0xe4, "g1_layout_k_thread__param_0408.stack_info1");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0408, stack_info2) == 0xe8, "g1_layout_k_thread__param_0408.stack_info2");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0408, stack_info3) == 0xec, "g1_layout_k_thread__param_0408.stack_info3");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0408, thread_state) == 0xf0, "g1_layout_k_thread__param_0408.thread_state");
_Static_assert(sizeof(struct g1_layout_k_thread__param_0408) >= 0xf4, "g1_layout_k_thread__param_0408.size");

/* param_0410 | library | Zephyr work-queue struct accessed by k_work_queue_drain (flags word + drain semaphore/count). | D1+D2 verified
 * review: k_work_q embeds a full k_thread so the high offsets (0xd8 flags, 0xf0) are plausible but were not byte-verified against the header. Left unverified. */
struct __attribute__((packed)) g1_layout_k_work_q__param_0410 {
    uint8_t _pad_0x0[0xd8];
    uint8_t flags[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xdc[0x14];
    uint8_t drain_sem_or_count[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_k_work_q__param_0410, flags) == 0xd8, "g1_layout_k_work_q__param_0410.flags");
_Static_assert(offsetof(struct g1_layout_k_work_q__param_0410, drain_sem_or_count) == 0xf0, "g1_layout_k_work_q__param_0410.drain_sem_or_count");
_Static_assert(sizeof(struct g1_layout_k_work_q__param_0410) >= 0xf4, "g1_layout_k_work_q__param_0410.size");

/* param_0411 | library | Thread control block inspected by sched_thread_should_preempt: thread_state byte + preempt (prio|sched_locked) u16. | D1+D2 verified
 * review: VERIFIED against _thread_base: thread_state@0xd, and the union preempt(u16)@0xe (prio@0xe/sched_locked@0xf). Observed 0xd(byte) and 0xe(read as 1 and 2 bytes) match. Sonnet reversed the two (priority@0xd/state@0xe); corrected. 0xe read both as char and u16 => is_union=true (prio vs preempt). */
struct __attribute__((packed)) g1_layout_k_thread__param_0411 {
    uint8_t _pad_0x0[0xd];
    uint8_t thread_state[0x1]; /* catalog type: uint8_t; SDK member: base.thread_state */
    uint8_t preempt[0x2]; /* catalog type: uint16_t; SDK member: base.preempt */
};
_Static_assert(offsetof(struct g1_layout_k_thread__param_0411, thread_state) == 0xd, "g1_layout_k_thread__param_0411.thread_state");
_Static_assert(offsetof(struct g1_layout_k_thread__param_0411, preempt) == 0xe, "g1_layout_k_thread__param_0411.preempt");
_Static_assert(sizeof(struct g1_layout_k_thread__param_0411) >= 0x10, "g1_layout_k_thread__param_0411.size");

/* param_0412 | library | param_1 of add_thread_to_wait_queue: Zephyr thread object linked into a wait queue (linkage words + state/priority bytes). | D1+D2 verified
 * review: add_thread_to_wait_queue is an app helper; the four fields resemble _thread_base linkage but were not offset-verified (config-dependent). */
struct __attribute__((packed)) g1_layout_k_thread_waitq_view__param_0412 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x1];
    uint8_t field_0xd[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xe[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_k_thread_waitq_view__param_0412, field_0x4) == 0x4, "g1_layout_k_thread_waitq_view__param_0412.field_0x4");
_Static_assert(offsetof(struct g1_layout_k_thread_waitq_view__param_0412, field_0x8) == 0x8, "g1_layout_k_thread_waitq_view__param_0412.field_0x8");
_Static_assert(offsetof(struct g1_layout_k_thread_waitq_view__param_0412, field_0xd) == 0xd, "g1_layout_k_thread_waitq_view__param_0412.field_0xd");
_Static_assert(offsetof(struct g1_layout_k_thread_waitq_view__param_0412, field_0xe) == 0xe, "g1_layout_k_thread_waitq_view__param_0412.field_0xe");
_Static_assert(sizeof(struct g1_layout_k_thread_waitq_view__param_0412) >= 0x12, "g1_layout_k_thread_waitq_view__param_0412.size");

/* param_0414 | library | Zephyr kernel timer (embeds struct _timeout) manipulated by remove_timeout / z_add_timeout / z_impl_k_timer_start. | D1+D2 verified
 * review: VERIFIED against kernel.h + kernel_structs.h with CONFIG_TIMEOUT_64BIT=y. _timeout{node.next@0,node.prev@4,fn@8,dticks(int64)@10}; k_timer{timeout@0,wait_q@18,expiry_fn@20,stop_fn@24,period(k_timeout_t 8B)@28,status@30,user_data@34}. CORRECTED sonnet: 0x10/0x14 are the two halves of timeout.dticks; 0x28/0x2c are the two halves of period.ticks; 0x30 is status (sonnet had these shifted/mislabeled as expiry/stop/user_data). */
struct __attribute__((packed)) g1_layout_k_timer__param_0414 {
    uint8_t _pad_0x0[0x4];
    uint8_t timeout_node_prev[0x4]; /* catalog type: void *; SDK member: timeout.node.prev */
    uint8_t timeout_fn[0x4]; /* catalog type: void *; SDK member: timeout.fn */
    uint8_t _pad_0xc[0x4];
    uint8_t timeout_dticks_lo[0x4]; /* catalog type: int32_t; SDK member: timeout.dticks */
    uint8_t timeout_dticks_hi[0x4]; /* catalog type: int32_t; SDK member: timeout.dticks */
    uint8_t _pad_0x18[0x10];
    uint8_t period_lo[0x4]; /* catalog type: int32_t; SDK member: period.ticks */
    uint8_t period_hi[0x4]; /* catalog type: int32_t; SDK member: period.ticks */
    uint8_t status[0x4]; /* catalog type: uint32_t; SDK member: status */
};
_Static_assert(offsetof(struct g1_layout_k_timer__param_0414, timeout_node_prev) == 0x4, "g1_layout_k_timer__param_0414.timeout_node_prev");
_Static_assert(offsetof(struct g1_layout_k_timer__param_0414, timeout_fn) == 0x8, "g1_layout_k_timer__param_0414.timeout_fn");
_Static_assert(offsetof(struct g1_layout_k_timer__param_0414, timeout_dticks_lo) == 0x10, "g1_layout_k_timer__param_0414.timeout_dticks_lo");
_Static_assert(offsetof(struct g1_layout_k_timer__param_0414, timeout_dticks_hi) == 0x14, "g1_layout_k_timer__param_0414.timeout_dticks_hi");
_Static_assert(offsetof(struct g1_layout_k_timer__param_0414, period_lo) == 0x28, "g1_layout_k_timer__param_0414.period_lo");
_Static_assert(offsetof(struct g1_layout_k_timer__param_0414, period_hi) == 0x2c, "g1_layout_k_timer__param_0414.period_hi");
_Static_assert(offsetof(struct g1_layout_k_timer__param_0414, status) == 0x30, "g1_layout_k_timer__param_0414.status");
_Static_assert(sizeof(struct g1_layout_k_timer__param_0414) >= 0x34, "g1_layout_k_timer__param_0414.size");

/* param_0415 | G1-original | Event registration record shared by register_events and add_event: event id, callback pointer, count, and next-list pointer. | D1+D2 verified
 * review: Single-cid G1 record. Ground-truth notes a 4-byte access at 0xc overlapping the 0xd byte, so is_union=true; kept 0xc as count (wide) plus 0xd sub-byte. Offsets kept. */
struct __attribute__((packed)) g1_layout_event_registration__param_0415 {
    uint8_t _pad_0x0[0x4];
    uint8_t event_id[0x4]; /* catalog type: uint32_t */
    uint8_t callback[0x4]; /* catalog type: void * */
    uint8_t count[0x1]; /* catalog type: uint32_t */
    uint8_t field_0xd[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xe[0x2];
    uint8_t next[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_event_registration__param_0415, event_id) == 0x4, "g1_layout_event_registration__param_0415.event_id");
_Static_assert(offsetof(struct g1_layout_event_registration__param_0415, callback) == 0x8, "g1_layout_event_registration__param_0415.callback");
_Static_assert(offsetof(struct g1_layout_event_registration__param_0415, count) == 0xc, "g1_layout_event_registration__param_0415.count");
_Static_assert(offsetof(struct g1_layout_event_registration__param_0415, field_0xd) == 0xd, "g1_layout_event_registration__param_0415.field_0xd");
_Static_assert(offsetof(struct g1_layout_event_registration__param_0415, next) == 0x10, "g1_layout_event_registration__param_0415.next");
_Static_assert(sizeof(struct g1_layout_event_registration__param_0415) >= 0x14, "g1_layout_event_registration__param_0415.size");

/* param_0416 | library | Zephyr kernel poll-signal object locked/updated by poll_signal_event_locked. | D1+D2 verified
 * review: Verified against kernel.h struct k_poll_signal: sys_dlist_t poll_events @0x0 (8 bytes), unsigned int signaled @0x8, int result @0xc. Observed 0x8/0xc match signaled/result exactly. */
struct __attribute__((packed)) g1_layout_k_poll_signal__param_0416 {
    uint8_t _pad_0x0[0x8];
    uint8_t signaled[0x4]; /* catalog type: uint32_t; SDK member: signaled */
    uint8_t result[0x4]; /* catalog type: int32_t; SDK member: result */
};
_Static_assert(offsetof(struct g1_layout_k_poll_signal__param_0416, signaled) == 0x8, "g1_layout_k_poll_signal__param_0416.signaled");
_Static_assert(offsetof(struct g1_layout_k_poll_signal__param_0416, result) == 0xc, "g1_layout_k_poll_signal__param_0416.result");
_Static_assert(sizeof(struct g1_layout_k_poll_signal__param_0416) >= 0x10, "g1_layout_k_poll_signal__param_0416.size");

/* param_0417 | library | newlib/picolibc stdio FILE object manipulated by internal stdio routines (_fflush_r, _vfprintf_r, __sfvwrite_r, smakebuf_r, etc.). | D1+D2 verified
 * review: Identity high (classic newlib stdio internal function set). Ghidra flagged overlapping accesses at 0x0/0x3/0xc → is_union=true. Field naming follows the newlib __sFILE layout but exact variant offsets not header-verified, so verified=false. Kept every observed offset. */
struct __attribute__((packed)) g1_layout___sFILE__param_0417 {
    uint8_t _p[0x4]; /* catalog type: unsigned char* */
    uint8_t _r[0x4]; /* catalog type: int */
    uint8_t _w[0x4]; /* catalog type: int */
    uint8_t _flags[0x2]; /* catalog type: int16_t */
    uint8_t _file[0x2]; /* catalog type: int16_t */
    uint8_t _bf_base[0x4]; /* catalog type: unsigned char* */
    uint8_t _bf_size[0x4]; /* catalog type: int */
    uint8_t _lbfsize[0x4]; /* catalog type: int */
    uint8_t _pad_0x1c[0x4];
    uint8_t _cookie[0x4]; /* catalog type: void* */
    uint8_t _pad_0x24[0x4];
    uint8_t _read_fn[0x4]; /* catalog type: void* */
    uint8_t _write_fn[0x4]; /* catalog type: void* */
    uint8_t _pad_0x30[0x4];
    uint8_t _seek_fn[0x4]; /* catalog type: void* */
    uint8_t _pad_0x38[0x8];
    uint8_t _close_fn[0x4]; /* catalog type: void* */
    uint8_t _pad_0x44[0x10];
    uint8_t _ub_base[0x4]; /* catalog type: void* */
    uint8_t _ub_size[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x5c[0x8];
    uint8_t _lock_or_flags2[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _p) == 0x0, "g1_layout___sFILE__param_0417._p");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _r) == 0x4, "g1_layout___sFILE__param_0417._r");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _w) == 0x8, "g1_layout___sFILE__param_0417._w");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _flags) == 0xc, "g1_layout___sFILE__param_0417._flags");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _file) == 0xe, "g1_layout___sFILE__param_0417._file");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _bf_base) == 0x10, "g1_layout___sFILE__param_0417._bf_base");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _bf_size) == 0x14, "g1_layout___sFILE__param_0417._bf_size");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _lbfsize) == 0x18, "g1_layout___sFILE__param_0417._lbfsize");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _cookie) == 0x20, "g1_layout___sFILE__param_0417._cookie");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _read_fn) == 0x28, "g1_layout___sFILE__param_0417._read_fn");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _write_fn) == 0x2c, "g1_layout___sFILE__param_0417._write_fn");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _seek_fn) == 0x34, "g1_layout___sFILE__param_0417._seek_fn");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _close_fn) == 0x40, "g1_layout___sFILE__param_0417._close_fn");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _ub_base) == 0x54, "g1_layout___sFILE__param_0417._ub_base");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _ub_size) == 0x58, "g1_layout___sFILE__param_0417._ub_size");
_Static_assert(offsetof(struct g1_layout___sFILE__param_0417, _lock_or_flags2) == 0x64, "g1_layout___sFILE__param_0417._lock_or_flags2");
_Static_assert(sizeof(struct g1_layout___sFILE__param_0417) >= 0x68, "g1_layout___sFILE__param_0417.size");

/* param_0418 | library | C library FILE stream object used by _fflush_r/smakebuf_r/_vfprintf_r/libc_putc_buffered: buffer pointers, cookie, and flags. | D1+D2 verified
 * review: Downgraded sonnet's confidence high->medium. Accessors are clearly stdio internals (FILE), but observed offsets (_p@4,_base@8,_cookie@0xc,_flags@0x18) do not match a canonical newlib __sFILE (_flags@0); this is picolibc's layout which is not pinned in a resolvable header. library_verified=false. */
struct __attribute__((packed)) g1_layout_libc_FILE__param_0418 {
    uint8_t _pad_0x0[0x4];
    uint8_t _p[0x4]; /* catalog type: unsigned char* */
    uint8_t _base[0x4]; /* catalog type: unsigned char* */
    uint8_t _cookie[0x4]; /* catalog type: void* */
    uint8_t _pad_0x10[0x8];
    uint8_t _flags[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x1c[0xc];
    uint8_t field_0x28[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_libc_FILE__param_0418, _p) == 0x4, "g1_layout_libc_FILE__param_0418._p");
_Static_assert(offsetof(struct g1_layout_libc_FILE__param_0418, _base) == 0x8, "g1_layout_libc_FILE__param_0418._base");
_Static_assert(offsetof(struct g1_layout_libc_FILE__param_0418, _cookie) == 0xc, "g1_layout_libc_FILE__param_0418._cookie");
_Static_assert(offsetof(struct g1_layout_libc_FILE__param_0418, _flags) == 0x18, "g1_layout_libc_FILE__param_0418._flags");
_Static_assert(offsetof(struct g1_layout_libc_FILE__param_0418, field_0x28) == 0x28, "g1_layout_libc_FILE__param_0418.field_0x28");
_Static_assert(sizeof(struct g1_layout_libc_FILE__param_0418) >= 0x2c, "g1_layout_libc_FILE__param_0418.size");

/* param_0419 | library | newlib stdio FILE (__sFILE) stream object initialized by newlib_stdio_init_stream (flags/fd, buffer base/size, and read/write/seek/close function-pointer table). | D1+D2 verified
 * review: Function name strongly implies newlib FILE. newlib __sFILE header not in the pinned NCS tree browsed, so offsets not verified. 0x3 is a width-2 write overlapping the next byte (is_union). Kept all offsets. */
struct __attribute__((packed)) g1_layout_newlib_FILE__param_0419 {
    uint8_t _pad_0x0[0x3];
    uint8_t _flags[0x1]; /* catalog type: uint16_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t _r[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x2];
    uint8_t _file[0x2]; /* catalog type: uint16_t */
    uint8_t _bf_base[0x4]; /* catalog type: void * */
    uint8_t _bf_size[0x4]; /* catalog type: uint32_t */
    uint8_t _lbfsize[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1c[0x4];
    uint8_t _cookie[0x4]; /* catalog type: void * */
    uint8_t _read_fn[0x4]; /* catalog type: void * */
    uint8_t _write_fn[0x4]; /* catalog type: void * */
    uint8_t _seek_fn[0x4]; /* catalog type: void * */
    uint8_t _close_fn[0x4]; /* catalog type: void * */
    uint8_t _pad_0x34[0x30];
    uint8_t _lock_or_mbstate[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, _flags) == 0x3, "g1_layout_newlib_FILE__param_0419._flags");
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, field_0x4) == 0x4, "g1_layout_newlib_FILE__param_0419.field_0x4");
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, _r) == 0x8, "g1_layout_newlib_FILE__param_0419._r");
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, _file) == 0xe, "g1_layout_newlib_FILE__param_0419._file");
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, _bf_base) == 0x10, "g1_layout_newlib_FILE__param_0419._bf_base");
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, _bf_size) == 0x14, "g1_layout_newlib_FILE__param_0419._bf_size");
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, _lbfsize) == 0x18, "g1_layout_newlib_FILE__param_0419._lbfsize");
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, _cookie) == 0x20, "g1_layout_newlib_FILE__param_0419._cookie");
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, _read_fn) == 0x24, "g1_layout_newlib_FILE__param_0419._read_fn");
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, _write_fn) == 0x28, "g1_layout_newlib_FILE__param_0419._write_fn");
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, _seek_fn) == 0x2c, "g1_layout_newlib_FILE__param_0419._seek_fn");
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, _close_fn) == 0x30, "g1_layout_newlib_FILE__param_0419._close_fn");
_Static_assert(offsetof(struct g1_layout_newlib_FILE__param_0419, _lock_or_mbstate) == 0x64, "g1_layout_newlib_FILE__param_0419._lock_or_mbstate");
_Static_assert(sizeof(struct g1_layout_newlib_FILE__param_0419) >= 0x68, "g1_layout_newlib_FILE__param_0419.size");

/* param_0420 | library | Newlib/Picolibc per-task reentrancy struct (_reent) initialized by __sinit to set up the standard I/O streams. | D1+D2 verified
 * review: __sinit strongly implies struct _reent, but the pinned tree doesn't ship the newlib reent.h used at build time and _reent has heavy #ifdef variation; sparse observed offsets not verified. */
struct __attribute__((packed)) g1_layout__reent__param_0420 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x8];
    uint8_t field_0x18[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x1c[0xc];
    uint8_t field_0x28[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x2c[0x1c];
    uint8_t field_0x48[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x4c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x50[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout__reent__param_0420, field_0x4) == 0x4, "g1_layout__reent__param_0420.field_0x4");
_Static_assert(offsetof(struct g1_layout__reent__param_0420, field_0x8) == 0x8, "g1_layout__reent__param_0420.field_0x8");
_Static_assert(offsetof(struct g1_layout__reent__param_0420, field_0xc) == 0xc, "g1_layout__reent__param_0420.field_0xc");
_Static_assert(offsetof(struct g1_layout__reent__param_0420, field_0x18) == 0x18, "g1_layout__reent__param_0420.field_0x18");
_Static_assert(offsetof(struct g1_layout__reent__param_0420, field_0x28) == 0x28, "g1_layout__reent__param_0420.field_0x28");
_Static_assert(offsetof(struct g1_layout__reent__param_0420, field_0x48) == 0x48, "g1_layout__reent__param_0420.field_0x48");
_Static_assert(offsetof(struct g1_layout__reent__param_0420, field_0x4c) == 0x4c, "g1_layout__reent__param_0420.field_0x4c");
_Static_assert(offsetof(struct g1_layout__reent__param_0420, field_0x50) == 0x50, "g1_layout__reent__param_0420.field_0x50");
_Static_assert(sizeof(struct g1_layout__reent__param_0420) >= 0x54, "g1_layout__reent__param_0420.size");

/* param_0421 | G1-original | picolibc/newlib vfprintf conversion-spec state (width/precision/flags, pad char, sign, formatted-digit buffer) shared by printf_render_float/vfprintf_format_engine/vfprintf_emit_padded_field. | D1+D2 verified
 * review: Ground-truth marks this G1-original (an internal printf-engine scratch), not a named public struct; kept all 12 offsets. */
struct __attribute__((packed)) g1_layout_vfprintf_conv_state__param_0421 {
    uint8_t _pad_0x0[0x4];
    uint8_t width_or_flags[0x4]; /* catalog type: uint32_t */
    uint8_t precision[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1c[0x26];
    uint8_t pad_char[0x1]; /* catalog type: uint8_t */
    uint8_t sign_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x44[0x1];
    uint8_t field_0x45[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x46[0x2];
    uint8_t digit_buf_ptr[0x4]; /* catalog type: uint32_t */
    uint8_t digit_count[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x50[0x8];
    uint8_t field_0x58[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_vfprintf_conv_state__param_0421, width_or_flags) == 0x4, "g1_layout_vfprintf_conv_state__param_0421.width_or_flags");
_Static_assert(offsetof(struct g1_layout_vfprintf_conv_state__param_0421, precision) == 0x8, "g1_layout_vfprintf_conv_state__param_0421.precision");
_Static_assert(offsetof(struct g1_layout_vfprintf_conv_state__param_0421, field_0xc) == 0xc, "g1_layout_vfprintf_conv_state__param_0421.field_0xc");
_Static_assert(offsetof(struct g1_layout_vfprintf_conv_state__param_0421, field_0x10) == 0x10, "g1_layout_vfprintf_conv_state__param_0421.field_0x10");
_Static_assert(offsetof(struct g1_layout_vfprintf_conv_state__param_0421, field_0x14) == 0x14, "g1_layout_vfprintf_conv_state__param_0421.field_0x14");
_Static_assert(offsetof(struct g1_layout_vfprintf_conv_state__param_0421, field_0x18) == 0x18, "g1_layout_vfprintf_conv_state__param_0421.field_0x18");
_Static_assert(offsetof(struct g1_layout_vfprintf_conv_state__param_0421, pad_char) == 0x42, "g1_layout_vfprintf_conv_state__param_0421.pad_char");
_Static_assert(offsetof(struct g1_layout_vfprintf_conv_state__param_0421, sign_flag) == 0x43, "g1_layout_vfprintf_conv_state__param_0421.sign_flag");
_Static_assert(offsetof(struct g1_layout_vfprintf_conv_state__param_0421, field_0x45) == 0x45, "g1_layout_vfprintf_conv_state__param_0421.field_0x45");
_Static_assert(offsetof(struct g1_layout_vfprintf_conv_state__param_0421, digit_buf_ptr) == 0x48, "g1_layout_vfprintf_conv_state__param_0421.digit_buf_ptr");
_Static_assert(offsetof(struct g1_layout_vfprintf_conv_state__param_0421, digit_count) == 0x4c, "g1_layout_vfprintf_conv_state__param_0421.digit_count");
_Static_assert(offsetof(struct g1_layout_vfprintf_conv_state__param_0421, field_0x58) == 0x58, "g1_layout_vfprintf_conv_state__param_0421.field_0x58");
_Static_assert(sizeof(struct g1_layout_vfprintf_conv_state__param_0421) >= 0x5c, "g1_layout_vfprintf_conv_state__param_0421.size");

/* param_0423 | G1-original | Third parameter scratch state in dtoa (double-to-ASCII): three index words. | D1+D2 verified
 * review: libc dtoa internal scratch; treated as G1/newlib-vendored, no header to verify. Kept is_library=false (generic scratch). */
struct __attribute__((packed)) g1_layout_dtoa_scratch__param_0423 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: int32_t */
    uint8_t field_0x8[0x4]; /* catalog type: int32_t */
    uint8_t field_0xc[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_dtoa_scratch__param_0423, field_0x4) == 0x4, "g1_layout_dtoa_scratch__param_0423.field_0x4");
_Static_assert(offsetof(struct g1_layout_dtoa_scratch__param_0423, field_0x8) == 0x8, "g1_layout_dtoa_scratch__param_0423.field_0x8");
_Static_assert(offsetof(struct g1_layout_dtoa_scratch__param_0423, field_0xc) == 0xc, "g1_layout_dtoa_scratch__param_0423.field_0xc");
_Static_assert(sizeof(struct g1_layout_dtoa_scratch__param_0423) >= 0x10, "g1_layout_dtoa_scratch__param_0423.size");

/* param_0424 | library | David Gay dtoa.c arbitrary-precision Bigint manipulated by Bfree/multadd/lshift: exponent/word-count k, maxwds, and current word count wds. | D1+D2 verified
 * review: Classic newlib/dtoa Bigint { next; k; maxwds; sign; wds; x[] } -> k@0x4, maxwds@0x8, wds@0x10 matches the canonical layout (with next@0 and sign@0xc). No pinned dtoa header available so left unverified but confidence raised to medium. */
struct __attribute__((packed)) g1_layout_dtoa_bigint__param_0424 {
    uint8_t _pad_0x0[0x4];
    uint8_t k[0x4]; /* catalog type: int32_t; SDK member: k */
    uint8_t maxwds[0x4]; /* catalog type: int32_t; SDK member: maxwds */
    uint8_t _pad_0xc[0x4];
    uint8_t wds[0x4]; /* catalog type: int32_t; SDK member: wds */
};
_Static_assert(offsetof(struct g1_layout_dtoa_bigint__param_0424, k) == 0x4, "g1_layout_dtoa_bigint__param_0424.k");
_Static_assert(offsetof(struct g1_layout_dtoa_bigint__param_0424, maxwds) == 0x8, "g1_layout_dtoa_bigint__param_0424.maxwds");
_Static_assert(offsetof(struct g1_layout_dtoa_bigint__param_0424, wds) == 0x10, "g1_layout_dtoa_bigint__param_0424.wds");
_Static_assert(sizeof(struct g1_layout_dtoa_bigint__param_0424) >= 0x14, "g1_layout_dtoa_bigint__param_0424.size");

/* param_0425 | G1-original | G1-original big-integer length/dimension fields read by bigint_mult. | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_bigint_dims__param_0425 {
    uint8_t _pad_0x0[0x4];
    uint8_t len_a[0x4]; /* catalog type: int32_t */
    uint8_t len_b[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0xc[0x4];
    uint8_t len_c[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_bigint_dims__param_0425, len_a) == 0x4, "g1_layout_bigint_dims__param_0425.len_a");
_Static_assert(offsetof(struct g1_layout_bigint_dims__param_0425, len_b) == 0x8, "g1_layout_bigint_dims__param_0425.len_b");
_Static_assert(offsetof(struct g1_layout_bigint_dims__param_0425, len_c) == 0x10, "g1_layout_bigint_dims__param_0425.len_c");
_Static_assert(sizeof(struct g1_layout_bigint_dims__param_0425) >= 0x14, "g1_layout_bigint_dims__param_0425.size");

/* param_0427 | G1-original | G1-original arbitrary-precision integer state used by bigint_diff/bignum_div_trial_subtract/bignum_compare_abs: a sign/length word at 0x4 and a scratch word at 0x10. | D1+D2 verified
 * review: Single-cid G1 bignum. Offsets kept. */
struct __attribute__((packed)) g1_layout_bignum_state__param_0427 {
    uint8_t _pad_0x0[0x4];
    uint8_t sign_or_len[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t scratch[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_bignum_state__param_0427, sign_or_len) == 0x4, "g1_layout_bignum_state__param_0427.sign_or_len");
_Static_assert(offsetof(struct g1_layout_bignum_state__param_0427, scratch) == 0x10, "g1_layout_bignum_state__param_0427.scratch");
_Static_assert(sizeof(struct g1_layout_bignum_state__param_0427) >= 0x14, "g1_layout_bignum_state__param_0427.size");

/* param_0430 | G1-original | Internal printf/scanf conversion-specifier fragment shared by vfprintf_core, vfprintf_field_scan_match, and scanf_convert_integer_field (a width/flags 16-bit field). | D1+D2 verified
 * review: picolibc/newlib-internal but treated as G1-original scratch (3 APPLICATION members). is_union=true: 0x3 accessed 2-wide over 1-byte gap to 0x4. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_fmt_conv_spec__param_0430 {
    uint8_t _pad_0x0[0x3];
    uint8_t width_or_flags[0x1]; /* catalog type: uint16_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_fmt_conv_spec__param_0430, width_or_flags) == 0x3, "g1_layout_fmt_conv_spec__param_0430.width_or_flags");
_Static_assert(offsetof(struct g1_layout_fmt_conv_spec__param_0430, field_0x4) == 0x4, "g1_layout_fmt_conv_spec__param_0430.field_0x4");
_Static_assert(sizeof(struct g1_layout_fmt_conv_spec__param_0430) >= 0x8, "g1_layout_fmt_conv_spec__param_0430.size");

/* param_0432 | G1-original | Format-field scanning context used by vfprintf_field_scan_match (param_2): output function pointer, a run of index fields, and a trailing flag near 0x180. | D1+D2 verified
 * review: G1-original (application-class printf helper). 0x0 is a code pointer. */
struct __attribute__((packed)) g1_layout_vfprintf_scan_ctx__param_0432 {
    uint8_t out_fn[0x4]; /* catalog type: void* */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1c[0x164];
    uint8_t tail_flag[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_vfprintf_scan_ctx__param_0432, out_fn) == 0x0, "g1_layout_vfprintf_scan_ctx__param_0432.out_fn");
_Static_assert(offsetof(struct g1_layout_vfprintf_scan_ctx__param_0432, field_0x8) == 0x8, "g1_layout_vfprintf_scan_ctx__param_0432.field_0x8");
_Static_assert(offsetof(struct g1_layout_vfprintf_scan_ctx__param_0432, field_0xc) == 0xc, "g1_layout_vfprintf_scan_ctx__param_0432.field_0xc");
_Static_assert(offsetof(struct g1_layout_vfprintf_scan_ctx__param_0432, field_0x10) == 0x10, "g1_layout_vfprintf_scan_ctx__param_0432.field_0x10");
_Static_assert(offsetof(struct g1_layout_vfprintf_scan_ctx__param_0432, field_0x14) == 0x14, "g1_layout_vfprintf_scan_ctx__param_0432.field_0x14");
_Static_assert(offsetof(struct g1_layout_vfprintf_scan_ctx__param_0432, field_0x18) == 0x18, "g1_layout_vfprintf_scan_ctx__param_0432.field_0x18");
_Static_assert(offsetof(struct g1_layout_vfprintf_scan_ctx__param_0432, tail_flag) == 0x180, "g1_layout_vfprintf_scan_ctx__param_0432.tail_flag");
_Static_assert(sizeof(struct g1_layout_vfprintf_scan_ctx__param_0432) >= 0x184, "g1_layout_vfprintf_scan_ctx__param_0432.size");

/* param_0433 | G1-original | scanf integer-field conversion context/state for scanf_convert_integer_field: a callback/vtable word, several counters, and two trailer words. | D1+D2 verified
 * review: Kept naming; offsets unchanged. Likely a picolibc vfscanf state but not pinnable. */
struct __attribute__((packed)) g1_layout_scanf_convert_ctx__param_0433 {
    uint8_t callback_or_vtable[0x4]; /* catalog type: void* */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1c[0x160];
    uint8_t field_0x17c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x180[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_scanf_convert_ctx__param_0433, callback_or_vtable) == 0x0, "g1_layout_scanf_convert_ctx__param_0433.callback_or_vtable");
_Static_assert(offsetof(struct g1_layout_scanf_convert_ctx__param_0433, field_0x4) == 0x4, "g1_layout_scanf_convert_ctx__param_0433.field_0x4");
_Static_assert(offsetof(struct g1_layout_scanf_convert_ctx__param_0433, field_0x8) == 0x8, "g1_layout_scanf_convert_ctx__param_0433.field_0x8");
_Static_assert(offsetof(struct g1_layout_scanf_convert_ctx__param_0433, field_0xc) == 0xc, "g1_layout_scanf_convert_ctx__param_0433.field_0xc");
_Static_assert(offsetof(struct g1_layout_scanf_convert_ctx__param_0433, field_0x10) == 0x10, "g1_layout_scanf_convert_ctx__param_0433.field_0x10");
_Static_assert(offsetof(struct g1_layout_scanf_convert_ctx__param_0433, field_0x14) == 0x14, "g1_layout_scanf_convert_ctx__param_0433.field_0x14");
_Static_assert(offsetof(struct g1_layout_scanf_convert_ctx__param_0433, field_0x18) == 0x18, "g1_layout_scanf_convert_ctx__param_0433.field_0x18");
_Static_assert(offsetof(struct g1_layout_scanf_convert_ctx__param_0433, field_0x17c) == 0x17c, "g1_layout_scanf_convert_ctx__param_0433.field_0x17c");
_Static_assert(offsetof(struct g1_layout_scanf_convert_ctx__param_0433, field_0x180) == 0x180, "g1_layout_scanf_convert_ctx__param_0433.field_0x180");
_Static_assert(sizeof(struct g1_layout_scanf_convert_ctx__param_0433) >= 0x184, "g1_layout_scanf_convert_ctx__param_0433.size");

/* param_0436 | G1-original | Deferred call-pair setup context used by setup_deferred_call_pair (three words). | D1+D2 verified
 * review: G1-original; kept offsets. */
struct __attribute__((packed)) g1_layout_deferred_call_pair_ctx__param_0436 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_deferred_call_pair_ctx__param_0436, field_0x4) == 0x4, "g1_layout_deferred_call_pair_ctx__param_0436.field_0x4");
_Static_assert(offsetof(struct g1_layout_deferred_call_pair_ctx__param_0436, field_0x8) == 0x8, "g1_layout_deferred_call_pair_ctx__param_0436.field_0x8");
_Static_assert(offsetof(struct g1_layout_deferred_call_pair_ctx__param_0436, field_0xc) == 0xc, "g1_layout_deferred_call_pair_ctx__param_0436.field_0xc");
_Static_assert(sizeof(struct g1_layout_deferred_call_pair_ctx__param_0436) >= 0x10, "g1_layout_deferred_call_pair_ctx__param_0436.size");

/* param_0437 | G1-original | param_2 of setup_deferred_call_pair: four related handles/pointers (callback+arg+linkage) for a deferred-work pairing. | D1+D2 verified
 * review: Separated from global_0840 collision group. */
struct __attribute__((packed)) g1_layout_deferred_call_pair__param_0437 {
    uint8_t _pad_0x0[0x4];
    uint8_t handle_a[0x4]; /* catalog type: uint32_t */
    uint8_t handle_b[0x4]; /* catalog type: uint32_t */
    uint8_t handle_c[0x4]; /* catalog type: uint32_t */
    uint8_t handle_d[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_deferred_call_pair__param_0437, handle_a) == 0x4, "g1_layout_deferred_call_pair__param_0437.handle_a");
_Static_assert(offsetof(struct g1_layout_deferred_call_pair__param_0437, handle_b) == 0x8, "g1_layout_deferred_call_pair__param_0437.handle_b");
_Static_assert(offsetof(struct g1_layout_deferred_call_pair__param_0437, handle_c) == 0xc, "g1_layout_deferred_call_pair__param_0437.handle_c");
_Static_assert(offsetof(struct g1_layout_deferred_call_pair__param_0437, handle_d) == 0x10, "g1_layout_deferred_call_pair__param_0437.handle_d");
_Static_assert(sizeof(struct g1_layout_deferred_call_pair__param_0437) >= 0x14, "g1_layout_deferred_call_pair__param_0437.size");

/* param_0438 | library | mbedTLS CTR-DRBG context: 16-byte counter (V), reseed/prediction-resistance/entropy-length/reseed-interval scalars, AES cipher context, and entropy callback + context pointer. | D1+D2 verified
 * review: Verified against ctr_drbg.h: counter[16] @0x0-0xf (words read at 0x4/0x8/0xc), reseed_counter @0x10, prediction_resistance @0x14, entropy_len @0x18, reseed_interval @0x1c, aes_ctx @0x20 — all match exactly. aes_ctx internal words (0x20-0x3c) and f_entropy @0x94 / p_entropy @0x98 follow; the callback offset depends on the AES-context variant size so those two are consistent but not byte-checked. */
struct __attribute__((packed)) g1_layout_mbedtls_ctr_drbg_context__param_0438 {
    uint8_t _pad_0x0[0x4];
    uint8_t counter_w1[0x4]; /* catalog type: uint32_t; SDK member: counter */
    uint8_t counter_w2[0x4]; /* catalog type: uint32_t; SDK member: counter */
    uint8_t counter_w3[0x4]; /* catalog type: uint32_t; SDK member: counter */
    uint8_t reseed_counter[0x4]; /* catalog type: int32_t; SDK member: reseed_counter */
    uint8_t prediction_resistance[0x4]; /* catalog type: int32_t; SDK member: prediction_resistance */
    uint8_t entropy_len[0x4]; /* catalog type: size_t; SDK member: entropy_len */
    uint8_t reseed_interval[0x4]; /* catalog type: int32_t; SDK member: reseed_interval */
    uint8_t aes_ctx_w0[0x4]; /* catalog type: uint32_t; SDK member: aes_ctx */
    uint8_t aes_ctx_w1[0x4]; /* catalog type: uint32_t; SDK member: aes_ctx */
    uint8_t aes_ctx_w2[0x4]; /* catalog type: uint32_t; SDK member: aes_ctx */
    uint8_t aes_ctx_w3[0x4]; /* catalog type: uint32_t; SDK member: aes_ctx */
    uint8_t aes_ctx_w4[0x4]; /* catalog type: uint32_t; SDK member: aes_ctx */
    uint8_t aes_ctx_w5[0x4]; /* catalog type: uint32_t; SDK member: aes_ctx */
    uint8_t aes_ctx_w6[0x4]; /* catalog type: uint32_t; SDK member: aes_ctx */
    uint8_t aes_ctx_w7[0x4]; /* catalog type: uint32_t; SDK member: aes_ctx */
    uint8_t _pad_0x40[0x54];
    uint8_t f_entropy[0x4]; /* catalog type: void *; SDK member: f_entropy */
    uint8_t p_entropy[0x4]; /* catalog type: void *; SDK member: p_entropy */
};
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, counter_w1) == 0x4, "g1_layout_mbedtls_ctr_drbg_context__param_0438.counter_w1");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, counter_w2) == 0x8, "g1_layout_mbedtls_ctr_drbg_context__param_0438.counter_w2");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, counter_w3) == 0xc, "g1_layout_mbedtls_ctr_drbg_context__param_0438.counter_w3");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, reseed_counter) == 0x10, "g1_layout_mbedtls_ctr_drbg_context__param_0438.reseed_counter");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, prediction_resistance) == 0x14, "g1_layout_mbedtls_ctr_drbg_context__param_0438.prediction_resistance");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, entropy_len) == 0x18, "g1_layout_mbedtls_ctr_drbg_context__param_0438.entropy_len");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, reseed_interval) == 0x1c, "g1_layout_mbedtls_ctr_drbg_context__param_0438.reseed_interval");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, aes_ctx_w0) == 0x20, "g1_layout_mbedtls_ctr_drbg_context__param_0438.aes_ctx_w0");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, aes_ctx_w1) == 0x24, "g1_layout_mbedtls_ctr_drbg_context__param_0438.aes_ctx_w1");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, aes_ctx_w2) == 0x28, "g1_layout_mbedtls_ctr_drbg_context__param_0438.aes_ctx_w2");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, aes_ctx_w3) == 0x2c, "g1_layout_mbedtls_ctr_drbg_context__param_0438.aes_ctx_w3");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, aes_ctx_w4) == 0x30, "g1_layout_mbedtls_ctr_drbg_context__param_0438.aes_ctx_w4");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, aes_ctx_w5) == 0x34, "g1_layout_mbedtls_ctr_drbg_context__param_0438.aes_ctx_w5");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, aes_ctx_w6) == 0x38, "g1_layout_mbedtls_ctr_drbg_context__param_0438.aes_ctx_w6");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, aes_ctx_w7) == 0x3c, "g1_layout_mbedtls_ctr_drbg_context__param_0438.aes_ctx_w7");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, f_entropy) == 0x94, "g1_layout_mbedtls_ctr_drbg_context__param_0438.f_entropy");
_Static_assert(offsetof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438, p_entropy) == 0x98, "g1_layout_mbedtls_ctr_drbg_context__param_0438.p_entropy");
_Static_assert(sizeof(struct g1_layout_mbedtls_ctr_drbg_context__param_0438) >= 0x9c, "g1_layout_mbedtls_ctr_drbg_context__param_0438.size");

/* param_0439 | library | mbedTLS CTR_DRBG internal seed/tmp working block accessed uniformly (idx4) by ctr_drbg_update_internal. | D1+D2 verified
 * review: LIBRARY-class member (mbedtls). 11 consecutive words read as a uniform array -> is_array; not header-verified. */
struct __attribute__((packed)) g1_layout_ctr_drbg_work_buf__param_0439 {
    uint8_t _pad_0x0[0x4];
    uint8_t word_0[0x4]; /* catalog type: uint32_t */
    uint8_t word_1[0x4]; /* catalog type: uint32_t */
    uint8_t word_2[0x4]; /* catalog type: uint32_t */
    uint8_t word_3[0x4]; /* catalog type: uint32_t */
    uint8_t word_4[0x4]; /* catalog type: uint32_t */
    uint8_t word_5[0x4]; /* catalog type: uint32_t */
    uint8_t word_6[0x4]; /* catalog type: uint32_t */
    uint8_t word_7[0x4]; /* catalog type: uint32_t */
    uint8_t word_8[0x4]; /* catalog type: uint32_t */
    uint8_t word_9[0x4]; /* catalog type: uint32_t */
    uint8_t word_10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ctr_drbg_work_buf__param_0439, word_0) == 0x4, "g1_layout_ctr_drbg_work_buf__param_0439.word_0");
_Static_assert(offsetof(struct g1_layout_ctr_drbg_work_buf__param_0439, word_1) == 0x8, "g1_layout_ctr_drbg_work_buf__param_0439.word_1");
_Static_assert(offsetof(struct g1_layout_ctr_drbg_work_buf__param_0439, word_2) == 0xc, "g1_layout_ctr_drbg_work_buf__param_0439.word_2");
_Static_assert(offsetof(struct g1_layout_ctr_drbg_work_buf__param_0439, word_3) == 0x10, "g1_layout_ctr_drbg_work_buf__param_0439.word_3");
_Static_assert(offsetof(struct g1_layout_ctr_drbg_work_buf__param_0439, word_4) == 0x14, "g1_layout_ctr_drbg_work_buf__param_0439.word_4");
_Static_assert(offsetof(struct g1_layout_ctr_drbg_work_buf__param_0439, word_5) == 0x18, "g1_layout_ctr_drbg_work_buf__param_0439.word_5");
_Static_assert(offsetof(struct g1_layout_ctr_drbg_work_buf__param_0439, word_6) == 0x1c, "g1_layout_ctr_drbg_work_buf__param_0439.word_6");
_Static_assert(offsetof(struct g1_layout_ctr_drbg_work_buf__param_0439, word_7) == 0x20, "g1_layout_ctr_drbg_work_buf__param_0439.word_7");
_Static_assert(offsetof(struct g1_layout_ctr_drbg_work_buf__param_0439, word_8) == 0x24, "g1_layout_ctr_drbg_work_buf__param_0439.word_8");
_Static_assert(offsetof(struct g1_layout_ctr_drbg_work_buf__param_0439, word_9) == 0x28, "g1_layout_ctr_drbg_work_buf__param_0439.word_9");
_Static_assert(offsetof(struct g1_layout_ctr_drbg_work_buf__param_0439, word_10) == 0x2c, "g1_layout_ctr_drbg_work_buf__param_0439.word_10");
_Static_assert(sizeof(struct g1_layout_ctr_drbg_work_buf__param_0439) >= 0x30, "g1_layout_ctr_drbg_work_buf__param_0439.size");

/* param_0440 | library | mbed TLS entropy context used by entropy gather and cc_mbedtls_entropy_func (source_count, mutex/ctx ptr, accumulator words). | D1+D2 verified
 * review: mbedtls entropy.h not present under the pinned trees (CC3xx uses a vendored mbedtls); the 0xf8+ offsets depend on MBEDTLS config (accumulator size, MAX_SOURCES) so cannot be verified. Both members are LIBRARY-class, identification confident but verified=false. */
struct __attribute__((packed)) g1_layout_mbedtls_entropy_context__param_0440 {
    uint8_t _pad_0x0[0xf8];
    uint8_t source_count[0x4]; /* catalog type: uint32_t */
    uint8_t mutex_or_ctx[0x4]; /* catalog type: void* */
    uint8_t field_0x100[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x104[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x108[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_mbedtls_entropy_context__param_0440, source_count) == 0xf8, "g1_layout_mbedtls_entropy_context__param_0440.source_count");
_Static_assert(offsetof(struct g1_layout_mbedtls_entropy_context__param_0440, mutex_or_ctx) == 0xfc, "g1_layout_mbedtls_entropy_context__param_0440.mutex_or_ctx");
_Static_assert(offsetof(struct g1_layout_mbedtls_entropy_context__param_0440, field_0x100) == 0x100, "g1_layout_mbedtls_entropy_context__param_0440.field_0x100");
_Static_assert(offsetof(struct g1_layout_mbedtls_entropy_context__param_0440, field_0x104) == 0x104, "g1_layout_mbedtls_entropy_context__param_0440.field_0x104");
_Static_assert(offsetof(struct g1_layout_mbedtls_entropy_context__param_0440, field_0x108) == 0x108, "g1_layout_mbedtls_entropy_context__param_0440.field_0x108");
_Static_assert(offsetof(struct g1_layout_mbedtls_entropy_context__param_0440, field_0x10c) == 0x10c, "g1_layout_mbedtls_entropy_context__param_0440.field_0x10c");
_Static_assert(sizeof(struct g1_layout_mbedtls_entropy_context__param_0440) >= 0x110, "g1_layout_mbedtls_entropy_context__param_0440.size");

/* param_0442 | library | Arm CryptoCell TRNG hardware context used by startTrngHW / getTrngSource / LLF_RND_GetFastestRosc (all LIBRARY): rosc source, sample config words, sample count, result code. | D1+D2 verified
 * review: All 3 members are LIBRARY (CryptoCell), but the type is proprietary with no pinned header, so unverified. */
struct __attribute__((packed)) g1_layout_cc_trng_ctx__param_0442 {
    uint8_t _pad_0x0[0x10];
    uint8_t rosc_freq_or_source[0x4]; /* catalog type: uint32_t */
    uint8_t trng_flags0[0x4]; /* catalog type: uint32_t */
    uint8_t trng_flags1[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1c[0x4];
    uint8_t sample_count[0x4]; /* catalog type: uint32_t */
    uint8_t result_code[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_cc_trng_ctx__param_0442, rosc_freq_or_source) == 0x10, "g1_layout_cc_trng_ctx__param_0442.rosc_freq_or_source");
_Static_assert(offsetof(struct g1_layout_cc_trng_ctx__param_0442, trng_flags0) == 0x14, "g1_layout_cc_trng_ctx__param_0442.trng_flags0");
_Static_assert(offsetof(struct g1_layout_cc_trng_ctx__param_0442, trng_flags1) == 0x18, "g1_layout_cc_trng_ctx__param_0442.trng_flags1");
_Static_assert(offsetof(struct g1_layout_cc_trng_ctx__param_0442, sample_count) == 0x20, "g1_layout_cc_trng_ctx__param_0442.sample_count");
_Static_assert(offsetof(struct g1_layout_cc_trng_ctx__param_0442, result_code) == 0x24, "g1_layout_cc_trng_ctx__param_0442.result_code");
_Static_assert(sizeof(struct g1_layout_cc_trng_ctx__param_0442) >= 0x28, "g1_layout_cc_trng_ctx__param_0442.size");

/* param_0444 | library | mbedTLS AES context initialized by cc_mbedtls_aes_init (CryptoCell mbedtls). Observed writes fall inside the round-key schedule buffer. | D1+D2 verified
 * review: VERIFIED: mbedtls_aes_context { int nr@0; size_t rk_offset@4; uint32_t buf[68]@8 }. Observed 0x54..0x60 = buf[19..22], i.e. interior round-key words written during key expansion. Offsets are consistent with the header (all inside buf[]). */
struct __attribute__((packed)) g1_layout_mbedtls_aes_context__param_0444 {
    uint8_t _pad_0x0[0x54];
    uint8_t buf_19[0x4]; /* catalog type: uint32_t; SDK member: buf[19] */
    uint8_t buf_20[0x4]; /* catalog type: uint32_t; SDK member: buf[20] */
    uint8_t buf_21[0x4]; /* catalog type: uint32_t; SDK member: buf[21] */
    uint8_t buf_22[0x4]; /* catalog type: uint32_t; SDK member: buf[22] */
};
_Static_assert(offsetof(struct g1_layout_mbedtls_aes_context__param_0444, buf_19) == 0x54, "g1_layout_mbedtls_aes_context__param_0444.buf_19");
_Static_assert(offsetof(struct g1_layout_mbedtls_aes_context__param_0444, buf_20) == 0x58, "g1_layout_mbedtls_aes_context__param_0444.buf_20");
_Static_assert(offsetof(struct g1_layout_mbedtls_aes_context__param_0444, buf_21) == 0x5c, "g1_layout_mbedtls_aes_context__param_0444.buf_21");
_Static_assert(offsetof(struct g1_layout_mbedtls_aes_context__param_0444, buf_22) == 0x60, "g1_layout_mbedtls_aes_context__param_0444.buf_22");
_Static_assert(sizeof(struct g1_layout_mbedtls_aes_context__param_0444) >= 0x64, "g1_layout_mbedtls_aes_context__param_0444.size");

/* param_0445 | library | mbedTLS/CC3xx hardware-accelerated AES context initialized by cc_mbedtls_aes_setkey_enc: rounds/nr word, mode/keylen word, a flag byte. | D1+D2 verified
 * review: CC3xx mbedTLS backend AES context; the backend's struct layout differs from vanilla mbedtls and was not located/verified in the pinned tree. library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_mbedtls_aes_context__param_0445 {
    uint8_t _pad_0x0[0x30];
    uint8_t nr_or_rounds[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x34[0x4];
    uint8_t mode_or_keylen[0x4]; /* catalog type: uint32_t */
    uint8_t flag_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_mbedtls_aes_context__param_0445, nr_or_rounds) == 0x30, "g1_layout_mbedtls_aes_context__param_0445.nr_or_rounds");
_Static_assert(offsetof(struct g1_layout_mbedtls_aes_context__param_0445, mode_or_keylen) == 0x38, "g1_layout_mbedtls_aes_context__param_0445.mode_or_keylen");
_Static_assert(offsetof(struct g1_layout_mbedtls_aes_context__param_0445, flag_byte) == 0x3c, "g1_layout_mbedtls_aes_context__param_0445.flag_byte");
_Static_assert(sizeof(struct g1_layout_mbedtls_aes_context__param_0445) >= 0x40, "g1_layout_mbedtls_aes_context__param_0445.size");

/* param_0446 | library | AES driver/CryptoCell context shared by cc_mbedtls_aes_crypt_ecb, InitAes, ProcessAesDrv and FinishAesDrv (key schedule + state words). | D1+D2 verified
 * review: All four members LIBRARY-class AES routines; mbedtls_aes_context plausible but the CryptoCell alt driver layout differs from stock mbedtls, so not verified. is_union=true: 0xc accessed 4-wide over 3-byte gap (0xf). Offsets unchanged. */
struct __attribute__((packed)) g1_layout_aes_drv_ctx__param_0446 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x3]; /* catalog type: uint32_t */
    uint8_t field_0xf[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x10[0x20];
    uint8_t field_0x30[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x34[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x38[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x3c[0x4];
    uint8_t field_0x40[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x44[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x48[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x4c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x50[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x54[0x4];
    uint8_t field_0x58[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x5c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x60[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x64[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x68[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x6c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x70[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x4) == 0x4, "g1_layout_aes_drv_ctx__param_0446.field_0x4");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x8) == 0x8, "g1_layout_aes_drv_ctx__param_0446.field_0x8");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0xc) == 0xc, "g1_layout_aes_drv_ctx__param_0446.field_0xc");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0xf) == 0xf, "g1_layout_aes_drv_ctx__param_0446.field_0xf");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x30) == 0x30, "g1_layout_aes_drv_ctx__param_0446.field_0x30");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x34) == 0x34, "g1_layout_aes_drv_ctx__param_0446.field_0x34");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x38) == 0x38, "g1_layout_aes_drv_ctx__param_0446.field_0x38");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x40) == 0x40, "g1_layout_aes_drv_ctx__param_0446.field_0x40");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x44) == 0x44, "g1_layout_aes_drv_ctx__param_0446.field_0x44");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x48) == 0x48, "g1_layout_aes_drv_ctx__param_0446.field_0x48");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x4c) == 0x4c, "g1_layout_aes_drv_ctx__param_0446.field_0x4c");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x50) == 0x50, "g1_layout_aes_drv_ctx__param_0446.field_0x50");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x58) == 0x58, "g1_layout_aes_drv_ctx__param_0446.field_0x58");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x5c) == 0x5c, "g1_layout_aes_drv_ctx__param_0446.field_0x5c");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x60) == 0x60, "g1_layout_aes_drv_ctx__param_0446.field_0x60");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x64) == 0x64, "g1_layout_aes_drv_ctx__param_0446.field_0x64");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x68) == 0x68, "g1_layout_aes_drv_ctx__param_0446.field_0x68");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x6c) == 0x6c, "g1_layout_aes_drv_ctx__param_0446.field_0x6c");
_Static_assert(offsetof(struct g1_layout_aes_drv_ctx__param_0446, field_0x70) == 0x70, "g1_layout_aes_drv_ctx__param_0446.field_0x70");
_Static_assert(sizeof(struct g1_layout_aes_drv_ctx__param_0446) >= 0x74, "g1_layout_aes_drv_ctx__param_0446.size");

/* param_0447 | library | SHA-256 hashing state initialized by mbedtls_sha_starts_internal; the same footprint is reused by CryptoCell RNG param getters (word buffer + trailing count). | D1+D2 verified
 * review: 3/3 members are library-class (mbedtls/CC). Word run 0x4-0x24 = hash state/data block, 0x5c = total/count. Offsets not header-verified; the RNG-param callees may be a coincidental footprint reuse but all are mbedtls/CryptoCell so kept as one crypto context. */
struct __attribute__((packed)) g1_layout_mbedtls_sha256_context__param_0447 {
    uint8_t _pad_0x0[0x4];
    uint8_t word_0[0x4]; /* catalog type: uint32_t */
    uint8_t word_1[0x4]; /* catalog type: uint32_t */
    uint8_t word_2[0x4]; /* catalog type: uint32_t */
    uint8_t word_3[0x4]; /* catalog type: uint32_t */
    uint8_t word_4[0x4]; /* catalog type: uint32_t */
    uint8_t word_5[0x4]; /* catalog type: uint32_t */
    uint8_t word_6[0x4]; /* catalog type: uint32_t */
    uint8_t word_7[0x4]; /* catalog type: uint32_t */
    uint8_t word_8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x28[0x34];
    uint8_t total_len_or_count[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0447, word_0) == 0x4, "g1_layout_mbedtls_sha256_context__param_0447.word_0");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0447, word_1) == 0x8, "g1_layout_mbedtls_sha256_context__param_0447.word_1");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0447, word_2) == 0xc, "g1_layout_mbedtls_sha256_context__param_0447.word_2");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0447, word_3) == 0x10, "g1_layout_mbedtls_sha256_context__param_0447.word_3");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0447, word_4) == 0x14, "g1_layout_mbedtls_sha256_context__param_0447.word_4");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0447, word_5) == 0x18, "g1_layout_mbedtls_sha256_context__param_0447.word_5");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0447, word_6) == 0x1c, "g1_layout_mbedtls_sha256_context__param_0447.word_6");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0447, word_7) == 0x20, "g1_layout_mbedtls_sha256_context__param_0447.word_7");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0447, word_8) == 0x24, "g1_layout_mbedtls_sha256_context__param_0447.word_8");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0447, total_len_or_count) == 0x5c, "g1_layout_mbedtls_sha256_context__param_0447.total_len_or_count");
_Static_assert(sizeof(struct g1_layout_mbedtls_sha256_context__param_0447) >= 0x60, "g1_layout_mbedtls_sha256_context__param_0447.size");

/* param_0448 | library | SHA-256/224 hashing context shared by mbedtls_sha_update/finish_internal and ProcessHashDrv: total bit-count, 8-word digest state, 64-byte message buffer. | D1+D2 verified
 * review: Verified against mbedtls/sha256.h: { uint32 total[2]@0; uint32 state[8]@8; uchar buffer[64]@0x28; int is224@0x68 }. Observed 0x4=total[1], 0x8..0x24=state[0..7] (the canonical 8-word SHA-256 signature), 0x48/0x4c/0x5c/0x60 fall inside buffer. All offsets line up. */
struct __attribute__((packed)) g1_layout_mbedtls_sha256_context__param_0448 {
    uint8_t _pad_0x0[0x4];
    uint8_t total_1[0x4]; /* catalog type: uint32_t; SDK member: total[1] */
    uint8_t state_0[0x4]; /* catalog type: uint32_t; SDK member: state[0] */
    uint8_t state_1[0x4]; /* catalog type: uint32_t; SDK member: state[1] */
    uint8_t state_2[0x4]; /* catalog type: uint32_t; SDK member: state[2] */
    uint8_t state_3[0x4]; /* catalog type: uint32_t; SDK member: state[3] */
    uint8_t state_4[0x4]; /* catalog type: uint32_t; SDK member: state[4] */
    uint8_t state_5[0x4]; /* catalog type: uint32_t; SDK member: state[5] */
    uint8_t state_6[0x4]; /* catalog type: uint32_t; SDK member: state[6] */
    uint8_t state_7[0x4]; /* catalog type: uint32_t; SDK member: state[7] */
    uint8_t _pad_0x28[0x20];
    uint8_t buffer_20[0x4]; /* catalog type: uint32_t; SDK member: buffer[32] */
    uint8_t buffer_24[0x4]; /* catalog type: uint32_t; SDK member: buffer[36] */
    uint8_t _pad_0x50[0xc];
    uint8_t buffer_34[0x4]; /* catalog type: uint32_t; SDK member: buffer[52] */
    uint8_t buffer_38[0x4]; /* catalog type: uint32_t; SDK member: buffer[56] */
};
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, total_1) == 0x4, "g1_layout_mbedtls_sha256_context__param_0448.total_1");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, state_0) == 0x8, "g1_layout_mbedtls_sha256_context__param_0448.state_0");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, state_1) == 0xc, "g1_layout_mbedtls_sha256_context__param_0448.state_1");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, state_2) == 0x10, "g1_layout_mbedtls_sha256_context__param_0448.state_2");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, state_3) == 0x14, "g1_layout_mbedtls_sha256_context__param_0448.state_3");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, state_4) == 0x18, "g1_layout_mbedtls_sha256_context__param_0448.state_4");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, state_5) == 0x1c, "g1_layout_mbedtls_sha256_context__param_0448.state_5");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, state_6) == 0x20, "g1_layout_mbedtls_sha256_context__param_0448.state_6");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, state_7) == 0x24, "g1_layout_mbedtls_sha256_context__param_0448.state_7");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, buffer_20) == 0x48, "g1_layout_mbedtls_sha256_context__param_0448.buffer_20");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, buffer_24) == 0x4c, "g1_layout_mbedtls_sha256_context__param_0448.buffer_24");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, buffer_34) == 0x5c, "g1_layout_mbedtls_sha256_context__param_0448.buffer_34");
_Static_assert(offsetof(struct g1_layout_mbedtls_sha256_context__param_0448, buffer_38) == 0x60, "g1_layout_mbedtls_sha256_context__param_0448.buffer_38");
_Static_assert(sizeof(struct g1_layout_mbedtls_sha256_context__param_0448) >= 0x64, "g1_layout_mbedtls_sha256_context__param_0448.size");

/* param_0449 | library | CryptoCell low-level RND (ring-oscillator) state read by LLF_RND_GetRoscSampleCnt (sample-count field at +0x24). | D1+D2 verified
 * review: CryptoCell RND HAL state is opaque; offsets not verifiable against a pinned header. Kept offsets. */
struct __attribute__((packed)) g1_layout_llf_rnd_state__param_0449 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x14];
    uint8_t rosc_sample_cnt[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_llf_rnd_state__param_0449, field_0x4) == 0x4, "g1_layout_llf_rnd_state__param_0449.field_0x4");
_Static_assert(offsetof(struct g1_layout_llf_rnd_state__param_0449, field_0x8) == 0x8, "g1_layout_llf_rnd_state__param_0449.field_0x8");
_Static_assert(offsetof(struct g1_layout_llf_rnd_state__param_0449, field_0xc) == 0xc, "g1_layout_llf_rnd_state__param_0449.field_0xc");
_Static_assert(offsetof(struct g1_layout_llf_rnd_state__param_0449, rosc_sample_cnt) == 0x24, "g1_layout_llf_rnd_state__param_0449.rosc_sample_cnt");
_Static_assert(sizeof(struct g1_layout_llf_rnd_state__param_0449) >= 0x28, "g1_layout_llf_rnd_state__param_0449.size");

/* param_0453 | library | CryptoCell hash-driver working state finalized by FinishHashDrv: an 8-word running digest plus additional internal counters/buffer words (SHA-family hash context). | D1+D2 verified
 * review: FinishHashDrv is a LIBRARY (CryptoCell) member; proprietary hash context, no pinned header, offsets unverified. */
struct __attribute__((packed)) g1_layout_hash_drv_context__param_0453 {
    uint8_t _pad_0x0[0x8];
    uint8_t state_0[0x4]; /* catalog type: uint32_t */
    uint8_t state_1[0x4]; /* catalog type: uint32_t */
    uint8_t state_2[0x4]; /* catalog type: uint32_t */
    uint8_t state_3[0x4]; /* catalog type: uint32_t */
    uint8_t state_4[0x4]; /* catalog type: uint32_t */
    uint8_t state_5[0x4]; /* catalog type: uint32_t */
    uint8_t state_6[0x4]; /* catalog type: uint32_t */
    uint8_t state_7[0x4]; /* catalog type: uint32_t */
    uint8_t word_8[0x4]; /* catalog type: uint32_t */
    uint8_t word_9[0x4]; /* catalog type: uint32_t */
    uint8_t word_10[0x4]; /* catalog type: uint32_t */
    uint8_t word_11[0x4]; /* catalog type: uint32_t */
    uint8_t word_12[0x4]; /* catalog type: uint32_t */
    uint8_t word_13[0x4]; /* catalog type: uint32_t */
    uint8_t word_14[0x4]; /* catalog type: uint32_t */
    uint8_t word_15[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, state_0) == 0x8, "g1_layout_hash_drv_context__param_0453.state_0");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, state_1) == 0xc, "g1_layout_hash_drv_context__param_0453.state_1");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, state_2) == 0x10, "g1_layout_hash_drv_context__param_0453.state_2");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, state_3) == 0x14, "g1_layout_hash_drv_context__param_0453.state_3");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, state_4) == 0x18, "g1_layout_hash_drv_context__param_0453.state_4");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, state_5) == 0x1c, "g1_layout_hash_drv_context__param_0453.state_5");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, state_6) == 0x20, "g1_layout_hash_drv_context__param_0453.state_6");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, state_7) == 0x24, "g1_layout_hash_drv_context__param_0453.state_7");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, word_8) == 0x28, "g1_layout_hash_drv_context__param_0453.word_8");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, word_9) == 0x2c, "g1_layout_hash_drv_context__param_0453.word_9");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, word_10) == 0x30, "g1_layout_hash_drv_context__param_0453.word_10");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, word_11) == 0x34, "g1_layout_hash_drv_context__param_0453.word_11");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, word_12) == 0x38, "g1_layout_hash_drv_context__param_0453.word_12");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, word_13) == 0x3c, "g1_layout_hash_drv_context__param_0453.word_13");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, word_14) == 0x40, "g1_layout_hash_drv_context__param_0453.word_14");
_Static_assert(offsetof(struct g1_layout_hash_drv_context__param_0453, word_15) == 0x44, "g1_layout_hash_drv_context__param_0453.word_15");
_Static_assert(sizeof(struct g1_layout_hash_drv_context__param_0453) >= 0x48, "g1_layout_hash_drv_context__param_0453.size");

/* param_0454 | library | AES key-loading context read by LoadAesKey: eight key words, a rounds/length word, a status byte, and a trailing word. | D1+D2 verified
 * review: LIBRARY-class crypto (LoadAesKey); proprietary AES context with no matching pinned header, unverified. */
struct __attribute__((packed)) g1_layout_aes_key_context__param_0454 {
    uint8_t _pad_0x0[0x10];
    uint8_t key_word_0[0x4]; /* catalog type: uint32_t */
    uint8_t key_word_1[0x4]; /* catalog type: uint32_t */
    uint8_t key_word_2[0x4]; /* catalog type: uint32_t */
    uint8_t key_word_3[0x4]; /* catalog type: uint32_t */
    uint8_t key_word_4[0x4]; /* catalog type: uint32_t */
    uint8_t key_word_5[0x4]; /* catalog type: uint32_t */
    uint8_t key_word_6[0x4]; /* catalog type: uint32_t */
    uint8_t key_word_7[0x4]; /* catalog type: uint32_t */
    uint8_t rounds_or_len[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x34[0x8];
    uint8_t status[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3d[0x3];
    uint8_t field_0x40[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_aes_key_context__param_0454, key_word_0) == 0x10, "g1_layout_aes_key_context__param_0454.key_word_0");
_Static_assert(offsetof(struct g1_layout_aes_key_context__param_0454, key_word_1) == 0x14, "g1_layout_aes_key_context__param_0454.key_word_1");
_Static_assert(offsetof(struct g1_layout_aes_key_context__param_0454, key_word_2) == 0x18, "g1_layout_aes_key_context__param_0454.key_word_2");
_Static_assert(offsetof(struct g1_layout_aes_key_context__param_0454, key_word_3) == 0x1c, "g1_layout_aes_key_context__param_0454.key_word_3");
_Static_assert(offsetof(struct g1_layout_aes_key_context__param_0454, key_word_4) == 0x20, "g1_layout_aes_key_context__param_0454.key_word_4");
_Static_assert(offsetof(struct g1_layout_aes_key_context__param_0454, key_word_5) == 0x24, "g1_layout_aes_key_context__param_0454.key_word_5");
_Static_assert(offsetof(struct g1_layout_aes_key_context__param_0454, key_word_6) == 0x28, "g1_layout_aes_key_context__param_0454.key_word_6");
_Static_assert(offsetof(struct g1_layout_aes_key_context__param_0454, key_word_7) == 0x2c, "g1_layout_aes_key_context__param_0454.key_word_7");
_Static_assert(offsetof(struct g1_layout_aes_key_context__param_0454, rounds_or_len) == 0x30, "g1_layout_aes_key_context__param_0454.rounds_or_len");
_Static_assert(offsetof(struct g1_layout_aes_key_context__param_0454, status) == 0x3c, "g1_layout_aes_key_context__param_0454.status");
_Static_assert(offsetof(struct g1_layout_aes_key_context__param_0454, field_0x40) == 0x40, "g1_layout_aes_key_context__param_0454.field_0x40");
_Static_assert(sizeof(struct g1_layout_aes_key_context__param_0454) >= 0x44, "g1_layout_aes_key_context__param_0454.size");

/* param_0458 | G1-original | Small header read by opt_node_header_len: two size/length words. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_opt_node_header__param_0458 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_opt_node_header__param_0458, field_0x4) == 0x4, "g1_layout_opt_node_header__param_0458.field_0x4");
_Static_assert(offsetof(struct g1_layout_opt_node_header__param_0458, field_0x8) == 0x8, "g1_layout_opt_node_header__param_0458.field_0x8");
_Static_assert(sizeof(struct g1_layout_opt_node_header__param_0458) >= 0xc, "g1_layout_opt_node_header__param_0458.size");

/* param_0459 | G1-original | Serializable option/attribute list node used across the opt_node_* serialization routines (serialize, append, copy fields), with type/flags header, list link, value pointer/len, and a trailing sub-record block. | D1+D2 verified
 * review: 6 members, cohesive G1 serialization node. */
struct __attribute__((packed)) g1_layout_opt_node_t__param_0459 {
    uint8_t _pad_0x0[0x1];
    uint8_t type[0x1]; /* catalog type: uint8_t */
    uint8_t flags[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x1];
    uint8_t next[0x4]; /* catalog type: uint32_t */
    uint8_t child_or_value_ptr[0x4]; /* catalog type: uint32_t */
    uint8_t value_ptr[0x4]; /* catalog type: uint32_t */
    uint8_t value_len[0x4]; /* catalog type: uint32_t */
    uint8_t extra[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x18[0x48];
    uint8_t sub_field_0[0x4]; /* catalog type: uint32_t */
    uint8_t sub_field_1[0x4]; /* catalog type: uint32_t */
    uint8_t sub_field_2[0x4]; /* catalog type: uint32_t */
    uint8_t sub_field_3[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_opt_node_t__param_0459, type) == 0x1, "g1_layout_opt_node_t__param_0459.type");
_Static_assert(offsetof(struct g1_layout_opt_node_t__param_0459, flags) == 0x2, "g1_layout_opt_node_t__param_0459.flags");
_Static_assert(offsetof(struct g1_layout_opt_node_t__param_0459, next) == 0x4, "g1_layout_opt_node_t__param_0459.next");
_Static_assert(offsetof(struct g1_layout_opt_node_t__param_0459, child_or_value_ptr) == 0x8, "g1_layout_opt_node_t__param_0459.child_or_value_ptr");
_Static_assert(offsetof(struct g1_layout_opt_node_t__param_0459, value_ptr) == 0xc, "g1_layout_opt_node_t__param_0459.value_ptr");
_Static_assert(offsetof(struct g1_layout_opt_node_t__param_0459, value_len) == 0x10, "g1_layout_opt_node_t__param_0459.value_len");
_Static_assert(offsetof(struct g1_layout_opt_node_t__param_0459, extra) == 0x14, "g1_layout_opt_node_t__param_0459.extra");
_Static_assert(offsetof(struct g1_layout_opt_node_t__param_0459, sub_field_0) == 0x60, "g1_layout_opt_node_t__param_0459.sub_field_0");
_Static_assert(offsetof(struct g1_layout_opt_node_t__param_0459, sub_field_1) == 0x64, "g1_layout_opt_node_t__param_0459.sub_field_1");
_Static_assert(offsetof(struct g1_layout_opt_node_t__param_0459, sub_field_2) == 0x68, "g1_layout_opt_node_t__param_0459.sub_field_2");
_Static_assert(offsetof(struct g1_layout_opt_node_t__param_0459, sub_field_3) == 0x6c, "g1_layout_opt_node_t__param_0459.sub_field_3");
_Static_assert(sizeof(struct g1_layout_opt_node_t__param_0459) >= 0x70, "g1_layout_opt_node_t__param_0459.size");

/* param_0460 | G1-original | G1-original small option/TLV setter context (a flag byte and an index word) used by opt_field1_set. | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_opt_field1_ctx__param_0460 {
    uint8_t _pad_0x0[0x1];
    uint8_t flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x2];
    uint8_t idx[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_opt_field1_ctx__param_0460, flag) == 0x1, "g1_layout_opt_field1_ctx__param_0460.flag");
_Static_assert(offsetof(struct g1_layout_opt_field1_ctx__param_0460, idx) == 0x4, "g1_layout_opt_field1_ctx__param_0460.idx");
_Static_assert(sizeof(struct g1_layout_opt_field1_ctx__param_0460) >= 0x8, "g1_layout_opt_field1_ctx__param_0460.size");

/* param_0461 | G1-original | G1-original option/attribute record with settable option-field slots (0x4-0x1c, written by opt_field1/2/3_set and opt_record_init) plus a four-word decoded tail (0x60-0x6c) read back by opt_record_decode. | D1+D2 verified
 * review: Single-cid G1 record; five accessor functions confirm cohesion. Offsets kept. */
struct __attribute__((packed)) g1_layout_opt_record__param_0461 {
    uint8_t _pad_0x0[0x4];
    uint8_t field1[0x4]; /* catalog type: uint32_t */
    uint8_t field2[0x4]; /* catalog type: uint32_t */
    uint8_t field3[0x4]; /* catalog type: uint32_t */
    uint8_t field4[0x4]; /* catalog type: uint32_t */
    uint8_t field5[0x4]; /* catalog type: uint32_t */
    uint8_t field6[0x4]; /* catalog type: uint32_t */
    uint8_t field7[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x20[0x40];
    uint8_t decoded_a[0x4]; /* catalog type: uint32_t */
    uint8_t decoded_b[0x4]; /* catalog type: uint32_t */
    uint8_t decoded_c[0x4]; /* catalog type: uint32_t */
    uint8_t decoded_d[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_opt_record__param_0461, field1) == 0x4, "g1_layout_opt_record__param_0461.field1");
_Static_assert(offsetof(struct g1_layout_opt_record__param_0461, field2) == 0x8, "g1_layout_opt_record__param_0461.field2");
_Static_assert(offsetof(struct g1_layout_opt_record__param_0461, field3) == 0xc, "g1_layout_opt_record__param_0461.field3");
_Static_assert(offsetof(struct g1_layout_opt_record__param_0461, field4) == 0x10, "g1_layout_opt_record__param_0461.field4");
_Static_assert(offsetof(struct g1_layout_opt_record__param_0461, field5) == 0x14, "g1_layout_opt_record__param_0461.field5");
_Static_assert(offsetof(struct g1_layout_opt_record__param_0461, field6) == 0x18, "g1_layout_opt_record__param_0461.field6");
_Static_assert(offsetof(struct g1_layout_opt_record__param_0461, field7) == 0x1c, "g1_layout_opt_record__param_0461.field7");
_Static_assert(offsetof(struct g1_layout_opt_record__param_0461, decoded_a) == 0x60, "g1_layout_opt_record__param_0461.decoded_a");
_Static_assert(offsetof(struct g1_layout_opt_record__param_0461, decoded_b) == 0x64, "g1_layout_opt_record__param_0461.decoded_b");
_Static_assert(offsetof(struct g1_layout_opt_record__param_0461, decoded_c) == 0x68, "g1_layout_opt_record__param_0461.decoded_c");
_Static_assert(offsetof(struct g1_layout_opt_record__param_0461, decoded_d) == 0x6c, "g1_layout_opt_record__param_0461.decoded_d");
_Static_assert(sizeof(struct g1_layout_opt_record__param_0461) >= 0x70, "g1_layout_opt_record__param_0461.size");

/* param_0463 | G1-original | Small option/attribute record written by opt_field3_set (flag byte + index/id). | D1+D2 verified
 * review: G1-original; offsets unchanged. */
struct __attribute__((packed)) g1_layout_opt_field3_ctx__param_0463 {
    uint8_t _pad_0x0[0x1];
    uint8_t flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x2];
    uint8_t id[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_opt_field3_ctx__param_0463, flag) == 0x1, "g1_layout_opt_field3_ctx__param_0463.flag");
_Static_assert(offsetof(struct g1_layout_opt_field3_ctx__param_0463, id) == 0x4, "g1_layout_opt_field3_ctx__param_0463.id");
_Static_assert(sizeof(struct g1_layout_opt_field3_ctx__param_0463) >= 0x8, "g1_layout_opt_field3_ctx__param_0463.size");

/* param_0466 | G1-original | Option record value-binding structure passed to opt_record_bind_value (param_2). | D1+D2 verified
 * review: G1-original; three int words only. */
struct __attribute__((packed)) g1_layout_opt_record__param_0466 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: int32_t */
    uint8_t field_0x8[0x4]; /* catalog type: int32_t */
    uint8_t field_0xc[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_opt_record__param_0466, field_0x4) == 0x4, "g1_layout_opt_record__param_0466.field_0x4");
_Static_assert(offsetof(struct g1_layout_opt_record__param_0466, field_0x8) == 0x8, "g1_layout_opt_record__param_0466.field_0x8");
_Static_assert(offsetof(struct g1_layout_opt_record__param_0466, field_0xc) == 0xc, "g1_layout_opt_record__param_0466.field_0xc");
_Static_assert(sizeof(struct g1_layout_opt_record__param_0466) >= 0x10, "g1_layout_opt_record__param_0466.size");

/* param_0472 | G1-original | Singly-linked list node appended by opt_list_append_node: next link plus a data/value word. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_opt_list_node__param_0472 {
    uint8_t _pad_0x0[0x4];
    uint8_t next[0x4]; /* catalog type: void* */
    uint8_t data[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_opt_list_node__param_0472, next) == 0x4, "g1_layout_opt_list_node__param_0472.next");
_Static_assert(offsetof(struct g1_layout_opt_list_node__param_0472, data) == 0x8, "g1_layout_opt_list_node__param_0472.data");
_Static_assert(sizeof(struct g1_layout_opt_list_node__param_0472) >= 0xc, "g1_layout_opt_list_node__param_0472.size");

/* param_0482 | G1-original | Array/struct of integer date-time components read by format_log_timestamp_mmdd_hhmm to render an 'MM/DD HH:MM' log timestamp. | D1+D2 verified
 * review: 12 consecutive word reads; likely a broken-down time struct/array. Kept offsets. */
struct __attribute__((packed)) g1_layout_log_timestamp_fields__param_0482 {
    uint8_t _pad_0x0[0x4];
    uint8_t comp_0[0x4]; /* catalog type: uint32_t */
    uint8_t comp_1[0x4]; /* catalog type: uint32_t */
    uint8_t comp_2[0x4]; /* catalog type: uint32_t */
    uint8_t comp_3[0x4]; /* catalog type: uint32_t */
    uint8_t comp_4[0x4]; /* catalog type: uint32_t */
    uint8_t comp_5[0x4]; /* catalog type: uint32_t */
    uint8_t comp_6[0x4]; /* catalog type: uint32_t */
    uint8_t comp_7[0x4]; /* catalog type: uint32_t */
    uint8_t comp_8[0x4]; /* catalog type: uint32_t */
    uint8_t comp_9[0x4]; /* catalog type: uint32_t */
    uint8_t comp_10[0x4]; /* catalog type: uint32_t */
    uint8_t comp_11[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_log_timestamp_fields__param_0482, comp_0) == 0x4, "g1_layout_log_timestamp_fields__param_0482.comp_0");
_Static_assert(offsetof(struct g1_layout_log_timestamp_fields__param_0482, comp_1) == 0x8, "g1_layout_log_timestamp_fields__param_0482.comp_1");
_Static_assert(offsetof(struct g1_layout_log_timestamp_fields__param_0482, comp_2) == 0xc, "g1_layout_log_timestamp_fields__param_0482.comp_2");
_Static_assert(offsetof(struct g1_layout_log_timestamp_fields__param_0482, comp_3) == 0x10, "g1_layout_log_timestamp_fields__param_0482.comp_3");
_Static_assert(offsetof(struct g1_layout_log_timestamp_fields__param_0482, comp_4) == 0x14, "g1_layout_log_timestamp_fields__param_0482.comp_4");
_Static_assert(offsetof(struct g1_layout_log_timestamp_fields__param_0482, comp_5) == 0x18, "g1_layout_log_timestamp_fields__param_0482.comp_5");
_Static_assert(offsetof(struct g1_layout_log_timestamp_fields__param_0482, comp_6) == 0x1c, "g1_layout_log_timestamp_fields__param_0482.comp_6");
_Static_assert(offsetof(struct g1_layout_log_timestamp_fields__param_0482, comp_7) == 0x20, "g1_layout_log_timestamp_fields__param_0482.comp_7");
_Static_assert(offsetof(struct g1_layout_log_timestamp_fields__param_0482, comp_8) == 0x24, "g1_layout_log_timestamp_fields__param_0482.comp_8");
_Static_assert(offsetof(struct g1_layout_log_timestamp_fields__param_0482, comp_9) == 0x28, "g1_layout_log_timestamp_fields__param_0482.comp_9");
_Static_assert(offsetof(struct g1_layout_log_timestamp_fields__param_0482, comp_10) == 0x2c, "g1_layout_log_timestamp_fields__param_0482.comp_10");
_Static_assert(offsetof(struct g1_layout_log_timestamp_fields__param_0482, comp_11) == 0x30, "g1_layout_log_timestamp_fields__param_0482.comp_11");
_Static_assert(sizeof(struct g1_layout_log_timestamp_fields__param_0482) >= 0x34, "g1_layout_log_timestamp_fields__param_0482.size");

/* param_0483 | G1-original | IMU orientation math object: quaternion input floats (w,x,y,z) and output euler-angle + validity fields written by quaternion_to_euler. | D1+D2 verified
 * review: G1-original; float positions self-consistent with a quaternion->euler conversion. Kept offsets exactly. */
struct __attribute__((packed)) g1_layout_quaternion_euler_ctx__param_0483 {
    uint8_t _pad_0x0[0xc];
    uint8_t quat_w[0x4]; /* catalog type: float */
    uint8_t quat_x[0x4]; /* catalog type: float */
    uint8_t quat_y[0x4]; /* catalog type: float */
    uint8_t quat_z[0x4]; /* catalog type: float */
    uint8_t _pad_0x1c[0xc];
    uint8_t euler_valid_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x29[0x3];
    uint8_t euler_roll[0x4]; /* catalog type: float */
    uint8_t euler_pitch[0x4]; /* catalog type: float */
    uint8_t euler_yaw[0x4]; /* catalog type: float */
};
_Static_assert(offsetof(struct g1_layout_quaternion_euler_ctx__param_0483, quat_w) == 0xc, "g1_layout_quaternion_euler_ctx__param_0483.quat_w");
_Static_assert(offsetof(struct g1_layout_quaternion_euler_ctx__param_0483, quat_x) == 0x10, "g1_layout_quaternion_euler_ctx__param_0483.quat_x");
_Static_assert(offsetof(struct g1_layout_quaternion_euler_ctx__param_0483, quat_y) == 0x14, "g1_layout_quaternion_euler_ctx__param_0483.quat_y");
_Static_assert(offsetof(struct g1_layout_quaternion_euler_ctx__param_0483, quat_z) == 0x18, "g1_layout_quaternion_euler_ctx__param_0483.quat_z");
_Static_assert(offsetof(struct g1_layout_quaternion_euler_ctx__param_0483, euler_valid_flag) == 0x28, "g1_layout_quaternion_euler_ctx__param_0483.euler_valid_flag");
_Static_assert(offsetof(struct g1_layout_quaternion_euler_ctx__param_0483, euler_roll) == 0x2c, "g1_layout_quaternion_euler_ctx__param_0483.euler_roll");
_Static_assert(offsetof(struct g1_layout_quaternion_euler_ctx__param_0483, euler_pitch) == 0x30, "g1_layout_quaternion_euler_ctx__param_0483.euler_pitch");
_Static_assert(offsetof(struct g1_layout_quaternion_euler_ctx__param_0483, euler_yaw) == 0x34, "g1_layout_quaternion_euler_ctx__param_0483.euler_yaw");
_Static_assert(sizeof(struct g1_layout_quaternion_euler_ctx__param_0483) >= 0x38, "g1_layout_quaternion_euler_ctx__param_0483.size");

/* param_0485 | G1-original | param_1 of reset_countdown_timer_default: run of four counter/threshold words reset to defaults. | D1+D2 verified
 * review: Separated from global_0840 collision group. */
struct __attribute__((packed)) g1_layout_countdown_timer_state__param_0485 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_countdown_timer_state__param_0485, field_0x4) == 0x4, "g1_layout_countdown_timer_state__param_0485.field_0x4");
_Static_assert(offsetof(struct g1_layout_countdown_timer_state__param_0485, field_0x8) == 0x8, "g1_layout_countdown_timer_state__param_0485.field_0x8");
_Static_assert(offsetof(struct g1_layout_countdown_timer_state__param_0485, field_0xc) == 0xc, "g1_layout_countdown_timer_state__param_0485.field_0xc");
_Static_assert(offsetof(struct g1_layout_countdown_timer_state__param_0485, field_0x10) == 0x10, "g1_layout_countdown_timer_state__param_0485.field_0x10");
_Static_assert(sizeof(struct g1_layout_countdown_timer_state__param_0485) >= 0x14, "g1_layout_countdown_timer_state__param_0485.size");

/* param_0486 | G1-original | Little-endian uint32 output array written by bytes_to_u32le_array (param_2). | D1+D2 verified
 * review: G1-original; uniform stride-4 array. */
struct __attribute__((packed)) g1_layout_u32le_array__param_0486 {
    uint8_t _pad_0x0[0x4];
    uint8_t words_0[0x4]; /* catalog type: uint32_t */
    uint8_t words_1[0x4]; /* catalog type: uint32_t */
    uint8_t words_2[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_u32le_array__param_0486, words_0) == 0x4, "g1_layout_u32le_array__param_0486.words_0");
_Static_assert(offsetof(struct g1_layout_u32le_array__param_0486, words_1) == 0x8, "g1_layout_u32le_array__param_0486.words_1");
_Static_assert(offsetof(struct g1_layout_u32le_array__param_0486, words_2) == 0xc, "g1_layout_u32le_array__param_0486.words_2");
_Static_assert(sizeof(struct g1_layout_u32le_array__param_0486) >= 0x10, "g1_layout_u32le_array__param_0486.size");

/* param_0489 | library | cbprintf external output context used by cbpprintf_external (buffer ptr/size/index). | D1+D2 verified
 * review: This is a G1/Zephyr caller-defined out-context struct (cbvprintf_out_ctx / cbprintf_fp), not a single fixed public struct; offsets unverifiable. verified=false. */
struct __attribute__((packed)) g1_layout_cbprintf_out_ctx__param_0489 {
    uint8_t _pad_0x0[0x4];
    uint8_t out_buf[0x4]; /* catalog type: char * */
    uint8_t out_size[0x4]; /* catalog type: uint32_t */
    uint8_t out_idx[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cbprintf_out_ctx__param_0489, out_buf) == 0x4, "g1_layout_cbprintf_out_ctx__param_0489.out_buf");
_Static_assert(offsetof(struct g1_layout_cbprintf_out_ctx__param_0489, out_size) == 0x8, "g1_layout_cbprintf_out_ctx__param_0489.out_size");
_Static_assert(offsetof(struct g1_layout_cbprintf_out_ctx__param_0489, out_idx) == 0xc, "g1_layout_cbprintf_out_ctx__param_0489.out_idx");
_Static_assert(sizeof(struct g1_layout_cbprintf_out_ctx__param_0489) >= 0x10, "g1_layout_cbprintf_out_ctx__param_0489.size");

/* param_0492 | G1-original | Small two-word output struct written by callee 'out'. | D1+D2 verified
 * review: Single-cid. */
struct __attribute__((packed)) g1_layout_out_pair__param_0492 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_out_pair__param_0492, field_0x4) == 0x4, "g1_layout_out_pair__param_0492.field_0x4");
_Static_assert(offsetof(struct g1_layout_out_pair__param_0492, field_0x8) == 0x8, "g1_layout_out_pair__param_0492.field_0x8");
_Static_assert(sizeof(struct g1_layout_out_pair__param_0492) >= 0xc, "g1_layout_out_pair__param_0492.size");

/* param_0493 | library | Zephyr sys_heap internal chunk header manipulated by chunk_field / chunk_set / alloc_chunk / free_list_add / free_list_remove_bidx: size/flags word and a free-list link. | D1+D2 verified
 * review: Strong functional match to lib/os/heap chunk helpers, but heap chunk fields are addressed in chunk-unit indices via macros (not a plain struct), so exact offsets were not header-verified; library_verified=false. */
struct __attribute__((packed)) g1_layout_sys_heap_chunk__param_0493 {
    uint8_t _pad_0x0[0x8];
    uint8_t size_and_flags[0x4]; /* catalog type: uint32_t */
    uint8_t free_list_link[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_sys_heap_chunk__param_0493, size_and_flags) == 0x8, "g1_layout_sys_heap_chunk__param_0493.size_and_flags");
_Static_assert(offsetof(struct g1_layout_sys_heap_chunk__param_0493, free_list_link) == 0xc, "g1_layout_sys_heap_chunk__param_0493.free_list_link");
_Static_assert(sizeof(struct g1_layout_sys_heap_chunk__param_0493) >= 0x10, "g1_layout_sys_heap_chunk__param_0493.size");

/* param_0498 | library | Zephyr sys_notify async-operation notification object validated by sys_notify_validate: method union (signal/callback) and flags word. | D1+D2 verified
 * review: Header check MISMATCH: sys_notify is {union method@0x0; uint32_t flags@0x4} (8 bytes), but observed reads are at 0x4 and 0x8 with size>=0xc — shifted +4 from the header. Likely a containing struct (e.g. onoff_client) with sys_notify embedded at +0x4, or a base-offset artifact. library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_sys_notify__param_0498 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_sys_notify__param_0498, field_0x4) == 0x4, "g1_layout_sys_notify__param_0498.field_0x4");
_Static_assert(offsetof(struct g1_layout_sys_notify__param_0498, field_0x8) == 0x8, "g1_layout_sys_notify__param_0498.field_0x8");
_Static_assert(sizeof(struct g1_layout_sys_notify__param_0498) >= 0xc, "g1_layout_sys_notify__param_0498.size");

/* param_0499 | G1-original | 64-bit in/out value pointed to by newlib internal helper _ldiv5 (divide-by-5 used in floating-point printf). | D1+D2 verified
 * review: Not a real struct — an output pointer to a uint64. is_union=true: 0x0 accessed 8-wide (ulonglong) overlapping the 4-wide read at 0x4. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_ldiv5_result__param_0499 {
    uint8_t result[0x4]; /* catalog type: uint64_t */
    uint8_t result_hi[0x4]; /* catalog type: uint32_t */
    uint8_t _tail_pad[0x4];
};
_Static_assert(offsetof(struct g1_layout_ldiv5_result__param_0499, result) == 0x0, "g1_layout_ldiv5_result__param_0499.result");
_Static_assert(offsetof(struct g1_layout_ldiv5_result__param_0499, result_hi) == 0x4, "g1_layout_ldiv5_result__param_0499.result_hi");
_Static_assert(sizeof(struct g1_layout_ldiv5_result__param_0499) >= 0xc, "g1_layout_ldiv5_result__param_0499.size");

/* param_0501 | library | Filesystem usage/free-space statistics read by free_space and get_usage (block counters resembling statvfs). | D1+D2 verified
 * review: Both callees application-class; statvfs-like but offsets (0xc/0x10/0x24) not header-verified. */
struct __attribute__((packed)) g1_layout_fs_usage_stats__param_0501 {
    uint8_t _pad_0x0[0xc];
    uint8_t block_count[0x4]; /* catalog type: uint32_t */
    uint8_t block_size[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x10];
    uint8_t free_blocks[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_fs_usage_stats__param_0501, block_count) == 0xc, "g1_layout_fs_usage_stats__param_0501.block_count");
_Static_assert(offsetof(struct g1_layout_fs_usage_stats__param_0501, block_size) == 0x10, "g1_layout_fs_usage_stats__param_0501.block_size");
_Static_assert(offsetof(struct g1_layout_fs_usage_stats__param_0501, free_blocks) == 0x24, "g1_layout_fs_usage_stats__param_0501.free_blocks");
_Static_assert(sizeof(struct g1_layout_fs_usage_stats__param_0501) >= 0x28, "g1_layout_fs_usage_stats__param_0501.size");

/* param_0502 | library | Zephyr NVS allocation-table entry whose fields feed the CRC8 in nvs_ate_crc8_update. | D1+D2 verified
 * review: Verified against nvs_priv.h __packed struct nvs_ate: { u16 id@0; u16 offset@2; u16 len@4; u8 part@6; u8 crc8@7 }. Observed 0x2=offset and 0x7=crc8 match exactly (crc8 is the last byte). Corrected sonnet's ambiguous 'len_or_offset' -> offset. */
struct __attribute__((packed)) g1_layout_nvs_ate__param_0502 {
    uint8_t _pad_0x0[0x2];
    uint8_t offset[0x2]; /* catalog type: uint16_t; SDK member: offset */
    uint8_t _pad_0x4[0x3];
    uint8_t crc8[0x1]; /* catalog type: uint8_t; SDK member: crc8 */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_nvs_ate__param_0502, offset) == 0x2, "g1_layout_nvs_ate__param_0502.offset");
_Static_assert(offsetof(struct g1_layout_nvs_ate__param_0502, crc8) == 0x7, "g1_layout_nvs_ate__param_0502.crc8");
_Static_assert(sizeof(struct g1_layout_nvs_ate__param_0502) >= 0x9, "g1_layout_nvs_ate__param_0502.size");

/* param_0503 | G1-original | Small two-word object (0x4/0x8) used only within FUN_0007e6a6; insufficient naming signal. | D1+D2 verified
 * review: Unidentified G1 object; kept offsets, generic names. */
struct __attribute__((packed)) g1_layout_pair_ctx_0503__param_0503 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_pair_ctx_0503__param_0503, field_0x4) == 0x4, "g1_layout_pair_ctx_0503__param_0503.field_0x4");
_Static_assert(offsetof(struct g1_layout_pair_ctx_0503__param_0503, field_0x8) == 0x8, "g1_layout_pair_ctx_0503__param_0503.field_0x8");
_Static_assert(sizeof(struct g1_layout_pair_ctx_0503__param_0503) >= 0xc, "g1_layout_pair_ctx_0503__param_0503.size");

/* param_0505 | G1-original | G1-original context object read by FUN_0007eb5c: a pointer field and a separate int field. | D1+D2 verified
 * review: G1-original; unnamed caller, kept generic naming. */
struct __attribute__((packed)) g1_layout_generic_handle_ctx__param_0505 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0x8];
    uint8_t field_0x10[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_generic_handle_ctx__param_0505, field_0x4) == 0x4, "g1_layout_generic_handle_ctx__param_0505.field_0x4");
_Static_assert(offsetof(struct g1_layout_generic_handle_ctx__param_0505, field_0x10) == 0x10, "g1_layout_generic_handle_ctx__param_0505.field_0x10");
_Static_assert(sizeof(struct g1_layout_generic_handle_ctx__param_0505) >= 0x14, "g1_layout_generic_handle_ctx__param_0505.size");

/* param_0506 | G1-original | Register-level device driver context (config word, register-map ptr, far threshold value) shared across dev_write_reg3/4, dev_reg_modify_bits, dev_set_threshold_and_arm. | D1+D2 verified
 * review: G1-original; 5 members share this param slot. Only 3 offsets observed. */
struct __attribute__((packed)) g1_layout_reg_dev_ctx__param_0506 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x9c];
    uint8_t threshold[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_reg_dev_ctx__param_0506, field_0x4) == 0x4, "g1_layout_reg_dev_ctx__param_0506.field_0x4");
_Static_assert(offsetof(struct g1_layout_reg_dev_ctx__param_0506, field_0x10) == 0x10, "g1_layout_reg_dev_ctx__param_0506.field_0x10");
_Static_assert(offsetof(struct g1_layout_reg_dev_ctx__param_0506, threshold) == 0xb0, "g1_layout_reg_dev_ctx__param_0506.threshold");
_Static_assert(sizeof(struct g1_layout_reg_dev_ctx__param_0506) >= 0xb4, "g1_layout_reg_dev_ctx__param_0506.size");

/* param_0507 | G1-original | Unknown small context read by FUN_0007ec0e: a pointer field and an int field. Insufficient signal to name. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_unk_ctx_7ec0e__param_0507 {
    uint8_t _pad_0x0[0x4];
    uint8_t ptr_field[0x4]; /* catalog type: void* */
    uint8_t _pad_0x8[0x8];
    uint8_t int_field[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_unk_ctx_7ec0e__param_0507, ptr_field) == 0x4, "g1_layout_unk_ctx_7ec0e__param_0507.ptr_field");
_Static_assert(offsetof(struct g1_layout_unk_ctx_7ec0e__param_0507, int_field) == 0x10, "g1_layout_unk_ctx_7ec0e__param_0507.int_field");
_Static_assert(sizeof(struct g1_layout_unk_ctx_7ec0e__param_0507) >= 0x14, "g1_layout_unk_ctx_7ec0e__param_0507.size");

/* param_0509 | library | Large IPC/rpmsg backend instance torn down by ipc_rpmsg_deinit; only three trailing bookkeeping words observed (counters/state near struct end). | D1+D2 verified
 * review: Zephyr IPC service rpmsg backend; only the tail was observed, unverified. */
struct __attribute__((packed)) g1_layout_ipc_rpmsg_instance__param_0509 {
    uint8_t _pad_0x0[0x19c];
    uint8_t field_0x19c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1a0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x1a4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ipc_rpmsg_instance__param_0509, field_0x19c) == 0x19c, "g1_layout_ipc_rpmsg_instance__param_0509.field_0x19c");
_Static_assert(offsetof(struct g1_layout_ipc_rpmsg_instance__param_0509, field_0x1a0) == 0x1a0, "g1_layout_ipc_rpmsg_instance__param_0509.field_0x1a0");
_Static_assert(offsetof(struct g1_layout_ipc_rpmsg_instance__param_0509, field_0x1a4) == 0x1a4, "g1_layout_ipc_rpmsg_instance__param_0509.field_0x1a4");
_Static_assert(sizeof(struct g1_layout_ipc_rpmsg_instance__param_0509) >= 0x1a8, "g1_layout_ipc_rpmsg_instance__param_0509.size");

/* param_0510 | library | Zephyr cbprintf internal copy descriptor (param_3) used by z_cbprintf_cpy: destination/length pair. | D1+D2 verified
 * review: Internal cbprintf helper state; not in a pinned public header, so library_verified=false. */
struct __attribute__((packed)) g1_layout_cbprintf_cpy_ctx__param_0510 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cbprintf_cpy_ctx__param_0510, field_0x4) == 0x4, "g1_layout_cbprintf_cpy_ctx__param_0510.field_0x4");
_Static_assert(offsetof(struct g1_layout_cbprintf_cpy_ctx__param_0510, field_0x8) == 0x8, "g1_layout_cbprintf_cpy_ctx__param_0510.field_0x8");
_Static_assert(sizeof(struct g1_layout_cbprintf_cpy_ctx__param_0510) >= 0xc, "g1_layout_cbprintf_cpy_ctx__param_0510.size");

/* param_0511 | library | Zephyr log message header/descriptor accessed by log_msg_finalize_commit inside the mpsc_pbuf-backed logging buffer: two sequential descriptor/length words. | D1+D2 verified
 * review: Only two words observed; log_msg/mpsc_pbuf header uses bitfields, not verifiable from these two reads. library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_log_msg_generic_hdr__param_0511 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_log_msg_generic_hdr__param_0511, field_0x4) == 0x4, "g1_layout_log_msg_generic_hdr__param_0511.field_0x4");
_Static_assert(offsetof(struct g1_layout_log_msg_generic_hdr__param_0511, field_0x8) == 0x8, "g1_layout_log_msg_generic_hdr__param_0511.field_0x8");
_Static_assert(sizeof(struct g1_layout_log_msg_generic_hdr__param_0511) >= 0xc, "g1_layout_log_msg_generic_hdr__param_0511.size");

/* param_0512 | library | Zephyr logging output context flushed by log_output_flush. | D1+D2 verified
 * review: log_output id kept (LIBRARY member) but exact member offsets not verified. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_log_output_ctx__param_0512 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_log_output_ctx__param_0512, field_0x0) == 0x0, "g1_layout_log_output_ctx__param_0512.field_0x0");
_Static_assert(offsetof(struct g1_layout_log_output_ctx__param_0512, field_0x4) == 0x4, "g1_layout_log_output_ctx__param_0512.field_0x4");
_Static_assert(offsetof(struct g1_layout_log_output_ctx__param_0512, field_0x8) == 0x8, "g1_layout_log_output_ctx__param_0512.field_0x8");
_Static_assert(sizeof(struct g1_layout_log_output_ctx__param_0512) >= 0xc, "g1_layout_log_output_ctx__param_0512.size");

/* param_0513 | G1-original | param_2 of build_status_byte_packet: G1 status-byte packet building context (four words). | D1+D2 verified
 * review: Separated from global_0840 collision group; last of the eight distinct objects that shared the 4-word footprint. */
struct __attribute__((packed)) g1_layout_status_byte_packet_ctx__param_0513 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_status_byte_packet_ctx__param_0513, field_0x4) == 0x4, "g1_layout_status_byte_packet_ctx__param_0513.field_0x4");
_Static_assert(offsetof(struct g1_layout_status_byte_packet_ctx__param_0513, field_0x8) == 0x8, "g1_layout_status_byte_packet_ctx__param_0513.field_0x8");
_Static_assert(offsetof(struct g1_layout_status_byte_packet_ctx__param_0513, field_0xc) == 0xc, "g1_layout_status_byte_packet_ctx__param_0513.field_0xc");
_Static_assert(offsetof(struct g1_layout_status_byte_packet_ctx__param_0513, field_0x10) == 0x10, "g1_layout_status_byte_packet_ctx__param_0513.field_0x10");
_Static_assert(sizeof(struct g1_layout_status_byte_packet_ctx__param_0513) >= 0x14, "g1_layout_status_byte_packet_ctx__param_0513.size");

/* param_0519 | G1-original | Flash sector-enumeration callback context passed to get_sectors_cb (param_2), carrying sector geometry and a written-back result. | D1+D2 verified
 * review: SPLIT from param_0033 collision group; this cid has distinct rw types (uint/int/rw/w) unlike the pure idx4 siblings, confirming it is a different object. */
struct __attribute__((packed)) g1_layout_flash_sector_enum_ctx__param_0519 {
    uint8_t _pad_0x0[0x4];
    uint8_t sector_count[0x4]; /* catalog type: uint32_t */
    uint8_t sector_offset[0x4]; /* catalog type: int32_t */
    uint8_t sector_size[0x4]; /* catalog type: int32_t */
    uint8_t cursor[0x4]; /* catalog type: uint32_t */
    uint8_t limit[0x4]; /* catalog type: uint32_t */
    uint8_t result[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_flash_sector_enum_ctx__param_0519, sector_count) == 0x4, "g1_layout_flash_sector_enum_ctx__param_0519.sector_count");
_Static_assert(offsetof(struct g1_layout_flash_sector_enum_ctx__param_0519, sector_offset) == 0x8, "g1_layout_flash_sector_enum_ctx__param_0519.sector_offset");
_Static_assert(offsetof(struct g1_layout_flash_sector_enum_ctx__param_0519, sector_size) == 0xc, "g1_layout_flash_sector_enum_ctx__param_0519.sector_size");
_Static_assert(offsetof(struct g1_layout_flash_sector_enum_ctx__param_0519, cursor) == 0x10, "g1_layout_flash_sector_enum_ctx__param_0519.cursor");
_Static_assert(offsetof(struct g1_layout_flash_sector_enum_ctx__param_0519, limit) == 0x14, "g1_layout_flash_sector_enum_ctx__param_0519.limit");
_Static_assert(offsetof(struct g1_layout_flash_sector_enum_ctx__param_0519, result) == 0x18, "g1_layout_flash_sector_enum_ctx__param_0519.result");
_Static_assert(sizeof(struct g1_layout_flash_sector_enum_ctx__param_0519) >= 0x1c, "g1_layout_flash_sector_enum_ctx__param_0519.size");

/* param_0526 | library | Zephyr settings NVS backend init config populated by settings_nvs_backend_init (fs handle, sector info, flags). | D1+D2 verified
 * review: Identity from callee; sparse write/read fields, offsets not header-verified. */
struct __attribute__((packed)) g1_layout_settings_nvs_backend_cfg__param_0526 {
    uint8_t _pad_0x0[0x30];
    uint8_t init_result[0x4]; /* catalog type: int */
    uint8_t _pad_0x34[0x4];
    uint8_t sector_size_or_cnt[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x3a[0x2];
    uint8_t backend_flags[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_settings_nvs_backend_cfg__param_0526, init_result) == 0x30, "g1_layout_settings_nvs_backend_cfg__param_0526.init_result");
_Static_assert(offsetof(struct g1_layout_settings_nvs_backend_cfg__param_0526, sector_size_or_cnt) == 0x38, "g1_layout_settings_nvs_backend_cfg__param_0526.sector_size_or_cnt");
_Static_assert(offsetof(struct g1_layout_settings_nvs_backend_cfg__param_0526, backend_flags) == 0x3c, "g1_layout_settings_nvs_backend_cfg__param_0526.backend_flags");
_Static_assert(sizeof(struct g1_layout_settings_nvs_backend_cfg__param_0526) >= 0x40, "g1_layout_settings_nvs_backend_cfg__param_0526.size");

/* param_0528 | G1-original | GATT service attribute memory pool released by svc_attr_memory_release: a size/count word and a pair of allocation pointers near the end. | D1+D2 verified
 * review: Kept naming; offsets unchanged. */
struct __attribute__((packed)) g1_layout_svc_attr_memory_pool__param_0528 {
    uint8_t _pad_0x0[0x134];
    uint8_t size_or_count[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x138[0x18];
    uint8_t alloc_ptr_1[0x4]; /* catalog type: void* */
    uint8_t alloc_ptr_2[0x4]; /* catalog type: void* */
    uint8_t field_0x158[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_svc_attr_memory_pool__param_0528, size_or_count) == 0x134, "g1_layout_svc_attr_memory_pool__param_0528.size_or_count");
_Static_assert(offsetof(struct g1_layout_svc_attr_memory_pool__param_0528, alloc_ptr_1) == 0x150, "g1_layout_svc_attr_memory_pool__param_0528.alloc_ptr_1");
_Static_assert(offsetof(struct g1_layout_svc_attr_memory_pool__param_0528, alloc_ptr_2) == 0x154, "g1_layout_svc_attr_memory_pool__param_0528.alloc_ptr_2");
_Static_assert(offsetof(struct g1_layout_svc_attr_memory_pool__param_0528, field_0x158) == 0x158, "g1_layout_svc_attr_memory_pool__param_0528.field_0x158");
_Static_assert(sizeof(struct g1_layout_svc_attr_memory_pool__param_0528) >= 0x15c, "g1_layout_svc_attr_memory_pool__param_0528.size");

/* param_0529 | library | Zephyr GATT discovery parameters/context whose error path is handled by discovery_complete_error. | D1+D2 verified
 * review: Only 2 sparse offsets (0x4, 0x15c) on a ~0x160 object; too sparse to verify member mapping. Kept offsets. */
struct __attribute__((packed)) g1_layout_bt_gatt_discover_params__param_0529 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x154];
    uint8_t field_0x15c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_discover_params__param_0529, field_0x4) == 0x4, "g1_layout_bt_gatt_discover_params__param_0529.field_0x4");
_Static_assert(offsetof(struct g1_layout_bt_gatt_discover_params__param_0529, field_0x15c) == 0x15c, "g1_layout_bt_gatt_discover_params__param_0529.field_0x15c");
_Static_assert(sizeof(struct g1_layout_bt_gatt_discover_params__param_0529) >= 0x160, "g1_layout_bt_gatt_discover_params__param_0529.size");

/* param_0530 | G1-original | BLE GATT discovery context handled by discovery_complete_not_found when a discovery search finishes without a match. | D1+D2 verified
 * review: G1-original; two sparse fields, kept naming. */
struct __attribute__((packed)) g1_layout_ble_discovery_ctx__param_0530 {
    uint8_t _pad_0x0[0x4];
    uint8_t discover_state[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x154];
    uint8_t discover_tail_field[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ble_discovery_ctx__param_0530, discover_state) == 0x4, "g1_layout_ble_discovery_ctx__param_0530.discover_state");
_Static_assert(offsetof(struct g1_layout_ble_discovery_ctx__param_0530, discover_tail_field) == 0x15c, "g1_layout_ble_discovery_ctx__param_0530.discover_tail_field");
_Static_assert(sizeof(struct g1_layout_ble_discovery_ctx__param_0530) >= 0x160, "g1_layout_ble_discovery_ctx__param_0530.size");

/* param_0536 | G1-original | Small struct (flag byte + index word) passed as param_3 to FUN_0007f634. | D1+D2 verified
 * review: G1-original; two fields observed. */
struct __attribute__((packed)) g1_layout_flag_index_pair__param_0536 {
    uint8_t _pad_0x0[0x2];
    uint8_t flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x1];
    uint8_t index[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_flag_index_pair__param_0536, flag) == 0x2, "g1_layout_flag_index_pair__param_0536.flag");
_Static_assert(offsetof(struct g1_layout_flag_index_pair__param_0536, index) == 0x4, "g1_layout_flag_index_pair__param_0536.index");
_Static_assert(sizeof(struct g1_layout_flag_index_pair__param_0536) >= 0x8, "g1_layout_flag_index_pair__param_0536.size");

/* param_0537 | library | ANCS attribute request record used by bt_ancs_request_attrs (attr_id + get-all flag). | D1+D2 verified
 * review: nrf ANCS client internal; 0x1/0x6 offsets unverifiable. verified=false. */
struct __attribute__((packed)) g1_layout_bt_ancs_attr_request__param_0537 {
    uint8_t _pad_0x0[0x1];
    uint8_t attr_id[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x4];
    uint8_t get_all_flag[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_bt_ancs_attr_request__param_0537, attr_id) == 0x1, "g1_layout_bt_ancs_attr_request__param_0537.attr_id");
_Static_assert(offsetof(struct g1_layout_bt_ancs_attr_request__param_0537, get_all_flag) == 0x6, "g1_layout_bt_ancs_attr_request__param_0537.get_all_flag");
_Static_assert(sizeof(struct g1_layout_bt_ancs_attr_request__param_0537) >= 0x7, "g1_layout_bt_ancs_attr_request__param_0537.size");

/* param_0538 | G1-original | param_1 of bt_ancs_register_attr: ANCS attribute registration/storage buffer (registered flag + count/len + status, all near 0x868). | D1+D2 verified
 * review: G1 ANCS registry; only tail fields observed. */
struct __attribute__((packed)) g1_layout_ancs_attr_registry__param_0538 {
    uint8_t _pad_0x0[0x868];
    uint8_t attr_registered_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x869[0x7];
    uint8_t attr_count_or_len[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x872[0x2];
    uint8_t attr_status[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_ancs_attr_registry__param_0538, attr_registered_flag) == 0x868, "g1_layout_ancs_attr_registry__param_0538.attr_registered_flag");
_Static_assert(offsetof(struct g1_layout_ancs_attr_registry__param_0538, attr_count_or_len) == 0x870, "g1_layout_ancs_attr_registry__param_0538.attr_count_or_len");
_Static_assert(offsetof(struct g1_layout_ancs_attr_registry__param_0538, attr_status) == 0x874, "g1_layout_ancs_attr_registry__param_0538.attr_status");
_Static_assert(sizeof(struct g1_layout_ancs_attr_registry__param_0538) >= 0x878, "g1_layout_ancs_attr_registry__param_0538.size");

/* param_0539 | G1-original | G1-original ANCS client context (>=0x8f8) passed to bt_ancs_register_app_attr: a flag byte and count/status fields in the discovery-state trailer. | D1+D2 verified
 * review: G1-original. Almost certainly the SAME ANCS client context type as param_0158 (shared 0x8e8 region), but placed in a separate footprint group so emitted as its own struct; noting the relationship rather than force-merging across groups. */
struct __attribute__((packed)) g1_layout_bt_ancs_client_ctx__param_0539 {
    uint8_t _pad_0x0[0x8e8];
    uint8_t field_0x8e8[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x8e9[0x7];
    uint8_t field_0x8f0[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x8f2[0x2];
    uint8_t field_0x8f4[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0539, field_0x8e8) == 0x8e8, "g1_layout_bt_ancs_client_ctx__param_0539.field_0x8e8");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0539, field_0x8f0) == 0x8f0, "g1_layout_bt_ancs_client_ctx__param_0539.field_0x8f0");
_Static_assert(offsetof(struct g1_layout_bt_ancs_client_ctx__param_0539, field_0x8f4) == 0x8f4, "g1_layout_bt_ancs_client_ctx__param_0539.field_0x8f4");
_Static_assert(sizeof(struct g1_layout_bt_ancs_client_ctx__param_0539) >= 0x8f8, "g1_layout_bt_ancs_client_ctx__param_0539.size");

/* param_0542 | G1-original | Audio codec register-access bus context used by audio_codec_reg_op_dispatch/audio_codec_bus_write: a bus/device pointer at 0x4 and a register address at 0xc. | D1+D2 verified
 * review: Single-cid G1 codec bus ctx. Offsets kept. */
struct __attribute__((packed)) g1_layout_audio_codec_bus_ctx__param_0542 {
    uint8_t _pad_0x0[0x4];
    uint8_t bus_dev[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0x4];
    uint8_t reg_addr[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_audio_codec_bus_ctx__param_0542, bus_dev) == 0x4, "g1_layout_audio_codec_bus_ctx__param_0542.bus_dev");
_Static_assert(offsetof(struct g1_layout_audio_codec_bus_ctx__param_0542, reg_addr) == 0xc, "g1_layout_audio_codec_bus_ctx__param_0542.reg_addr");
_Static_assert(sizeof(struct g1_layout_audio_codec_bus_ctx__param_0542) >= 0x10, "g1_layout_audio_codec_bus_ctx__param_0542.size");

/* param_0543 | G1-original | 6-byte device ID accessed as two 32-bit words by read_6byte_id_words. | D1+D2 verified
 * review: G1-original; offsets unchanged. */
struct __attribute__((packed)) g1_layout_id_words_pair__param_0543 {
    uint8_t _pad_0x0[0x4];
    uint8_t id_lo[0x4]; /* catalog type: uint32_t */
    uint8_t id_hi[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_id_words_pair__param_0543, id_lo) == 0x4, "g1_layout_id_words_pair__param_0543.id_lo");
_Static_assert(offsetof(struct g1_layout_id_words_pair__param_0543, id_hi) == 0x8, "g1_layout_id_words_pair__param_0543.id_hi");
_Static_assert(sizeof(struct g1_layout_id_words_pair__param_0543) >= 0xc, "g1_layout_id_words_pair__param_0543.size");

/* param_0544 | G1-original | id/value pair populated by settings_read_6byte_id28 (param_2). | D1+D2 verified
 * review: Application-class callee despite settings prefix; two idx4 words. */
struct __attribute__((packed)) g1_layout_settings_read_result__param_0544 {
    uint8_t _pad_0x0[0x4];
    uint8_t setting_id[0x4]; /* catalog type: uint32_t */
    uint8_t setting_value[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_settings_read_result__param_0544, setting_id) == 0x4, "g1_layout_settings_read_result__param_0544.setting_id");
_Static_assert(offsetof(struct g1_layout_settings_read_result__param_0544, setting_value) == 0x8, "g1_layout_settings_read_result__param_0544.setting_value");
_Static_assert(sizeof(struct g1_layout_settings_read_result__param_0544) >= 0xc, "g1_layout_settings_read_result__param_0544.size");

/* param_0545 | library | AES 16-byte state/round-key block passed as param_2 to tinycrypt add_round_key, accessed as an overlapping 4x4 byte/short/word matrix during AddRoundKey. | D1+D2 verified
 * review: Distinct object from param_0546/0547 (this is add_round_key's param_2, the round-key/state read with overlapping byte+short+word accesses at 0x2-0xf -> is_union). Offsets unchanged. tinycrypt AES has no named member offsets to verify beyond the 16-byte block; library_verified=false. */
struct __attribute__((packed)) g1_layout_aes_state_matrix__param_0545 {
    uint8_t _pad_0x0[0x2];
    uint8_t m0_hi[0x1]; /* catalog type: uint16_t */
    uint8_t m0_b[0x1]; /* catalog type: uint8_t */
    uint8_t w1[0x2]; /* catalog type: uint32_t */
    uint8_t m1_hi[0x1]; /* catalog type: uint16_t */
    uint8_t m1_b[0x1]; /* catalog type: uint8_t */
    uint8_t w2[0x2]; /* catalog type: uint32_t */
    uint8_t m2_hi[0x1]; /* catalog type: uint16_t */
    uint8_t m2_b[0x1]; /* catalog type: uint8_t */
    uint8_t w3[0x2]; /* catalog type: uint32_t */
    uint8_t m3_hi[0x1]; /* catalog type: uint16_t */
    uint8_t m3_b[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_aes_state_matrix__param_0545, m0_hi) == 0x2, "g1_layout_aes_state_matrix__param_0545.m0_hi");
_Static_assert(offsetof(struct g1_layout_aes_state_matrix__param_0545, m0_b) == 0x3, "g1_layout_aes_state_matrix__param_0545.m0_b");
_Static_assert(offsetof(struct g1_layout_aes_state_matrix__param_0545, w1) == 0x4, "g1_layout_aes_state_matrix__param_0545.w1");
_Static_assert(offsetof(struct g1_layout_aes_state_matrix__param_0545, m1_hi) == 0x6, "g1_layout_aes_state_matrix__param_0545.m1_hi");
_Static_assert(offsetof(struct g1_layout_aes_state_matrix__param_0545, m1_b) == 0x7, "g1_layout_aes_state_matrix__param_0545.m1_b");
_Static_assert(offsetof(struct g1_layout_aes_state_matrix__param_0545, w2) == 0x8, "g1_layout_aes_state_matrix__param_0545.w2");
_Static_assert(offsetof(struct g1_layout_aes_state_matrix__param_0545, m2_hi) == 0xa, "g1_layout_aes_state_matrix__param_0545.m2_hi");
_Static_assert(offsetof(struct g1_layout_aes_state_matrix__param_0545, m2_b) == 0xb, "g1_layout_aes_state_matrix__param_0545.m2_b");
_Static_assert(offsetof(struct g1_layout_aes_state_matrix__param_0545, w3) == 0xc, "g1_layout_aes_state_matrix__param_0545.w3");
_Static_assert(offsetof(struct g1_layout_aes_state_matrix__param_0545, m3_hi) == 0xe, "g1_layout_aes_state_matrix__param_0545.m3_hi");
_Static_assert(offsetof(struct g1_layout_aes_state_matrix__param_0545, m3_b) == 0xf, "g1_layout_aes_state_matrix__param_0545.m3_b");
_Static_assert(sizeof(struct g1_layout_aes_state_matrix__param_0545) >= 0x13, "g1_layout_aes_state_matrix__param_0545.size");

/* param_0546 | library | tinycrypt AES cipher state / round buffer operated on by add_round_key and shift_rows (both take it as their first pointer param), accessed here as a run of 32-bit words. | D1+D2 verified
 * review: Separated from the LC3 buffers in the same footprint group. Merged add_round_key(param_1) and shift_rows(param_1): in tinycrypt both are the same 16-byte AES state pointer, so this is genuinely one object. The 15-word footprint is a clustering artifact (real state is 16 bytes read as words); library_verified=false because the word count exceeds the true state size and no exact tinycrypt struct member offsets can be pinned. */
struct __attribute__((packed)) g1_layout_aes_cipher_state__param_0546 {
    uint8_t _pad_0x0[0x4];
    uint8_t word_0[0x4]; /* catalog type: uint32_t */
    uint8_t word_1[0x4]; /* catalog type: uint32_t */
    uint8_t word_2[0x4]; /* catalog type: uint32_t */
    uint8_t word_3[0x4]; /* catalog type: uint32_t */
    uint8_t word_4[0x4]; /* catalog type: uint32_t */
    uint8_t word_5[0x4]; /* catalog type: uint32_t */
    uint8_t word_6[0x4]; /* catalog type: uint32_t */
    uint8_t word_7[0x4]; /* catalog type: uint32_t */
    uint8_t word_8[0x4]; /* catalog type: uint32_t */
    uint8_t word_9[0x4]; /* catalog type: uint32_t */
    uint8_t word_10[0x4]; /* catalog type: uint32_t */
    uint8_t word_11[0x4]; /* catalog type: uint32_t */
    uint8_t word_12[0x4]; /* catalog type: uint32_t */
    uint8_t word_13[0x4]; /* catalog type: uint32_t */
    uint8_t word_14[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_0) == 0x4, "g1_layout_aes_cipher_state__param_0546.word_0");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_1) == 0x8, "g1_layout_aes_cipher_state__param_0546.word_1");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_2) == 0xc, "g1_layout_aes_cipher_state__param_0546.word_2");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_3) == 0x10, "g1_layout_aes_cipher_state__param_0546.word_3");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_4) == 0x14, "g1_layout_aes_cipher_state__param_0546.word_4");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_5) == 0x18, "g1_layout_aes_cipher_state__param_0546.word_5");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_6) == 0x1c, "g1_layout_aes_cipher_state__param_0546.word_6");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_7) == 0x20, "g1_layout_aes_cipher_state__param_0546.word_7");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_8) == 0x24, "g1_layout_aes_cipher_state__param_0546.word_8");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_9) == 0x28, "g1_layout_aes_cipher_state__param_0546.word_9");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_10) == 0x2c, "g1_layout_aes_cipher_state__param_0546.word_10");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_11) == 0x30, "g1_layout_aes_cipher_state__param_0546.word_11");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_12) == 0x34, "g1_layout_aes_cipher_state__param_0546.word_12");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_13) == 0x38, "g1_layout_aes_cipher_state__param_0546.word_13");
_Static_assert(offsetof(struct g1_layout_aes_cipher_state__param_0546, word_14) == 0x3c, "g1_layout_aes_cipher_state__param_0546.word_14");
_Static_assert(sizeof(struct g1_layout_aes_cipher_state__param_0546) >= 0x40, "g1_layout_aes_cipher_state__param_0546.size");

/* param_0548 | G1-original | Row of a small matrix (3 elements) used by mult_row_column_0 in a row-column multiply. | D1+D2 verified
 * review: Kept offsets. */
struct __attribute__((packed)) g1_layout_mat3_row__param_0548 {
    uint8_t _pad_0x0[0x4];
    uint8_t col0[0x4]; /* catalog type: uint32_t */
    uint8_t col1[0x4]; /* catalog type: uint32_t */
    uint8_t col2[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_mat3_row__param_0548, col0) == 0x4, "g1_layout_mat3_row__param_0548.col0");
_Static_assert(offsetof(struct g1_layout_mat3_row__param_0548, col1) == 0x8, "g1_layout_mat3_row__param_0548.col1");
_Static_assert(offsetof(struct g1_layout_mat3_row__param_0548, col2) == 0xc, "g1_layout_mat3_row__param_0548.col2");
_Static_assert(sizeof(struct g1_layout_mat3_row__param_0548) >= 0x10, "g1_layout_mat3_row__param_0548.size");

/* param_0549 | G1-original | Row/column descriptor read by mult_row_column_0 during matrix multiplication: three word fields (likely stride/length/data-pointer). | D1+D2 verified
 * review: G1-original; kept naming. */
struct __attribute__((packed)) g1_layout_matrix_row_desc__param_0549 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_a[0x4]; /* catalog type: uint32_t */
    uint8_t field_b[0x4]; /* catalog type: uint32_t */
    uint8_t field_c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_matrix_row_desc__param_0549, field_a) == 0x4, "g1_layout_matrix_row_desc__param_0549.field_a");
_Static_assert(offsetof(struct g1_layout_matrix_row_desc__param_0549, field_b) == 0x8, "g1_layout_matrix_row_desc__param_0549.field_b");
_Static_assert(offsetof(struct g1_layout_matrix_row_desc__param_0549, field_c) == 0xc, "g1_layout_matrix_row_desc__param_0549.field_c");
_Static_assert(sizeof(struct g1_layout_matrix_row_desc__param_0549) >= 0x10, "g1_layout_matrix_row_desc__param_0549.size");

/* param_0552 | library | mcumgr SMP transport header written by smp_make_rsp_hdr (group + seq/id fields). | D1+D2 verified
 * review: mcumgr smp header; the two observed halfwords at 0x4/0x6 fit nh_group and nh_seq/nh_id of the 8-byte smp_hdr but were not header-verified. */
struct __attribute__((packed)) g1_layout_smp_hdr__param_0552 {
    uint8_t _pad_0x0[0x4];
    uint8_t nh_group[0x2]; /* catalog type: uint16_t */
    uint8_t nh_seq_id[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_smp_hdr__param_0552, nh_group) == 0x4, "g1_layout_smp_hdr__param_0552.nh_group");
_Static_assert(offsetof(struct g1_layout_smp_hdr__param_0552, nh_seq_id) == 0x6, "g1_layout_smp_hdr__param_0552.nh_seq_id");
_Static_assert(sizeof(struct g1_layout_smp_hdr__param_0552) >= 0x8, "g1_layout_smp_hdr__param_0552.size");

/* param_0553 | library | Mcumgr SMP header built by smp_make_rsp_hdr (op/flags/len/group/seq/id packed). | D1+D2 verified
 * review: mcumgr smp header; Ghidra shows width-4 accesses over 2-byte fields at 0x0 and 0x4 (byte-swapped u16 stores) => is_union=true. Offsets kept verbatim; not verified against header. */
struct __attribute__((packed)) g1_layout_smp_hdr__param_0553 {
    uint8_t field_0x0[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x2[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x4[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x6[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_smp_hdr__param_0553, field_0x0) == 0x0, "g1_layout_smp_hdr__param_0553.field_0x0");
_Static_assert(offsetof(struct g1_layout_smp_hdr__param_0553, field_0x2) == 0x2, "g1_layout_smp_hdr__param_0553.field_0x2");
_Static_assert(offsetof(struct g1_layout_smp_hdr__param_0553, field_0x4) == 0x4, "g1_layout_smp_hdr__param_0553.field_0x4");
_Static_assert(offsetof(struct g1_layout_smp_hdr__param_0553, field_0x6) == 0x6, "g1_layout_smp_hdr__param_0553.field_0x6");
_Static_assert(offsetof(struct g1_layout_smp_hdr__param_0553, field_0x8) == 0x8, "g1_layout_smp_hdr__param_0553.field_0x8");
_Static_assert(offsetof(struct g1_layout_smp_hdr__param_0553, field_0xc) == 0xc, "g1_layout_smp_hdr__param_0553.field_0xc");
_Static_assert(sizeof(struct g1_layout_smp_hdr__param_0553) >= 0x10, "g1_layout_smp_hdr__param_0553.size");

/* param_0555 | library | MCUboot/img_mgmt image version compared by img_mgmt_vercmp: iv_revision (u16) and iv_build_num (u32). | D1+D2 verified
 * review: Verified against bootutil/image.h: iv_major@0, iv_minor@1, iv_revision@2, iv_build_num@4. Observed 0x2(ushort) and 0x4(uint32) match exactly (major/minor bytes at 0x0/0x1 not read). */
struct __attribute__((packed)) g1_layout_image_version__param_0555 {
    uint8_t _pad_0x0[0x2];
    uint8_t iv_revision[0x2]; /* catalog type: uint16_t; SDK member: iv_revision */
    uint8_t iv_build_num[0x4]; /* catalog type: uint32_t; SDK member: iv_build_num */
};
_Static_assert(offsetof(struct g1_layout_image_version__param_0555, iv_revision) == 0x2, "g1_layout_image_version__param_0555.iv_revision");
_Static_assert(offsetof(struct g1_layout_image_version__param_0555, iv_build_num) == 0x4, "g1_layout_image_version__param_0555.iv_build_num");
_Static_assert(sizeof(struct g1_layout_image_version__param_0555) >= 0x8, "g1_layout_image_version__param_0555.size");

/* param_0556 | library | MCUboot/mcumgr struct image_version (major.minor.revision.build) compared by img_mgmt_vercmp during firmware image management. | D1+D2 verified
 * review: VERIFIED: struct image_version {uint8_t iv_major@0; uint8_t iv_minor@1; uint16_t iv_revision@2; uint32_t iv_build_num@4} __packed. Observed iv_revision@0x2 and iv_build_num@0x4 match exactly. */
struct __attribute__((packed)) g1_layout_image_version__param_0556 {
    uint8_t _pad_0x0[0x2];
    uint8_t iv_revision[0x2]; /* catalog type: uint16_t; SDK member: iv_revision */
    uint8_t iv_build_num[0x4]; /* catalog type: uint32_t; SDK member: iv_build_num */
};
_Static_assert(offsetof(struct g1_layout_image_version__param_0556, iv_revision) == 0x2, "g1_layout_image_version__param_0556.iv_revision");
_Static_assert(offsetof(struct g1_layout_image_version__param_0556, iv_build_num) == 0x4, "g1_layout_image_version__param_0556.iv_build_num");
_Static_assert(sizeof(struct g1_layout_image_version__param_0556) >= 0x8, "g1_layout_image_version__param_0556.size");

/* param_0558 | library | MCUmgr SMP transport reassembly context (part of smp_transport) initialized by smp_reassembly_init: a reassembly net_buf pointer at 0x40 and an expected-length short at 0x44. | D1+D2 verified
 * review: Sub-region of the MCUmgr smp_transport struct; not verified against a pinned header. library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_smp_reassembly_ctx__param_0558 {
    uint8_t _pad_0x0[0x40];
    uint8_t reassembly_buf[0x4]; /* catalog type: void * */
    uint8_t expected_len[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_smp_reassembly_ctx__param_0558, reassembly_buf) == 0x40, "g1_layout_smp_reassembly_ctx__param_0558.reassembly_buf");
_Static_assert(offsetof(struct g1_layout_smp_reassembly_ctx__param_0558, expected_len) == 0x44, "g1_layout_smp_reassembly_ctx__param_0558.expected_len");
_Static_assert(sizeof(struct g1_layout_smp_reassembly_ctx__param_0558) >= 0x48, "g1_layout_smp_reassembly_ctx__param_0558.size");

/* param_0559 | library | MCUmgr SMP transport object; smp_reassembly_expected reads the expected-length field of its embedded reassembly state. | D1+D2 verified
 * review: smp_transport id kept; reassembly field offset not verified against smp.h. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_smp_transport_reassembly__param_0559 {
    uint8_t _pad_0x0[0x40];
    uint8_t reassembly_expected[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x44[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_smp_transport_reassembly__param_0559, reassembly_expected) == 0x40, "g1_layout_smp_transport_reassembly__param_0559.reassembly_expected");
_Static_assert(offsetof(struct g1_layout_smp_transport_reassembly__param_0559, field_0x44) == 0x44, "g1_layout_smp_transport_reassembly__param_0559.field_0x44");
_Static_assert(sizeof(struct g1_layout_smp_transport_reassembly__param_0559) >= 0x48, "g1_layout_smp_transport_reassembly__param_0559.size");

/* param_0560 | library | SMP L2CAP fragment-reassembly context used by smp_reassembly_collect: remaining length and write cursor. | D1+D2 verified
 * review: Identity from callee; two fields at 0x40/0x44, offsets not header-verified. */
struct __attribute__((packed)) g1_layout_bt_smp_reassembly_ctx__param_0560 {
    uint8_t _pad_0x0[0x40];
    uint8_t remaining_len[0x4]; /* catalog type: uint32_t */
    uint8_t cursor[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_bt_smp_reassembly_ctx__param_0560, remaining_len) == 0x40, "g1_layout_bt_smp_reassembly_ctx__param_0560.remaining_len");
_Static_assert(offsetof(struct g1_layout_bt_smp_reassembly_ctx__param_0560, cursor) == 0x44, "g1_layout_bt_smp_reassembly_ctx__param_0560.cursor");
_Static_assert(sizeof(struct g1_layout_bt_smp_reassembly_ctx__param_0560) >= 0x48, "g1_layout_bt_smp_reassembly_ctx__param_0560.size");

/* param_0562 | library | mcumgr SMP transport reassembly state tracked by smp_reassembly_complete: accumulated length and expected length. | D1+D2 verified
 * review: Kept naming; offsets unchanged. mcumgr smp_transport reassembly fields are internal; library_verified=false. */
struct __attribute__((packed)) g1_layout_smp_reassembly_ctx__param_0562 {
    uint8_t _pad_0x0[0x40];
    uint8_t reassembly_len[0x4]; /* catalog type: int32_t */
    uint8_t reassembly_expected_len[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_smp_reassembly_ctx__param_0562, reassembly_len) == 0x40, "g1_layout_smp_reassembly_ctx__param_0562.reassembly_len");
_Static_assert(offsetof(struct g1_layout_smp_reassembly_ctx__param_0562, reassembly_expected_len) == 0x44, "g1_layout_smp_reassembly_ctx__param_0562.reassembly_expected_len");
_Static_assert(sizeof(struct g1_layout_smp_reassembly_ctx__param_0562) >= 0x48, "g1_layout_smp_reassembly_ctx__param_0562.size");

/* param_0565 | G1-original | Connection identity/address matching record used by conn_match_id_and_addr (conn id word + address-type byte). | D1+D2 verified
 * review: Kept offsets. */
struct __attribute__((packed)) g1_layout_conn_id_addr__param_0565 {
    uint8_t _pad_0x0[0x18];
    uint8_t conn_id[0x4]; /* catalog type: uint32_t */
    uint8_t addr_type[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_conn_id_addr__param_0565, conn_id) == 0x18, "g1_layout_conn_id_addr__param_0565.conn_id");
_Static_assert(offsetof(struct g1_layout_conn_id_addr__param_0565, addr_type) == 0x1c, "g1_layout_conn_id_addr__param_0565.addr_type");
_Static_assert(sizeof(struct g1_layout_conn_id_addr__param_0565) >= 0x20, "g1_layout_conn_id_addr__param_0565.size");

/* param_0568 | library | Bluetooth UUID object (16-bit or 32-bit variant) initialized by bt_uuid_create; a bt_uuid header type byte followed by a 16-bit or 32-bit value. | D1+D2 verified
 * review: Verified against uuid.h: struct bt_uuid { uint8_t type; } at 0x0, then bt_uuid_16.val (uint16) at 0x2 and bt_uuid_32.val (uint32) at 0x4. The object is written as one of the two variants depending on UUID type, so is_union=true. Offsets match exactly. */
struct __attribute__((packed)) g1_layout_bt_uuid__param_0568 {
    uint8_t _pad_0x0[0x2];
    uint8_t val16[0x2]; /* catalog type: uint16_t; SDK member: bt_uuid_16.val */
    uint8_t val32[0x4]; /* catalog type: uint32_t; SDK member: bt_uuid_32.val */
};
_Static_assert(offsetof(struct g1_layout_bt_uuid__param_0568, val16) == 0x2, "g1_layout_bt_uuid__param_0568.val16");
_Static_assert(offsetof(struct g1_layout_bt_uuid__param_0568, val32) == 0x4, "g1_layout_bt_uuid__param_0568.val32");
_Static_assert(sizeof(struct g1_layout_bt_uuid__param_0568) >= 0x8, "g1_layout_bt_uuid__param_0568.size");

/* param_0571 | library | Zephyr bt_conn: security-level fields updated by update_sec_level (sec_level byte + required byte + a word at 0xc0). | D1+D2 verified
 * review: LIBRARY-class member (update_sec_level); bt_conn is a large host struct, only 3 offsets touched, not header-verified. */
struct __attribute__((packed)) g1_layout_bt_conn__param_0571 {
    uint8_t _pad_0x0[0x9];
    uint8_t sec_level[0x1]; /* catalog type: uint8_t */
    uint8_t required_sec_level[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xb[0xb5];
    uint8_t field_0xc0[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0571, sec_level) == 0x9, "g1_layout_bt_conn__param_0571.sec_level");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0571, required_sec_level) == 0xa, "g1_layout_bt_conn__param_0571.required_sec_level");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0571, field_0xc0) == 0xc0, "g1_layout_bt_conn__param_0571.field_0xc0");
_Static_assert(sizeof(struct g1_layout_bt_conn__param_0571) >= 0xc4, "g1_layout_bt_conn__param_0571.size");

/* param_0572 | library | Bluetooth LE address (type + 6-byte addr) written by bt_addr_le_copy. | D1+D2 verified
 * review: Checked addr.h: bt_addr_le_t = {uint8 type@0x0; bt_addr_t a (uint8 val[6])@0x1..0x7}. Observed writes at 0x1(u16) and 0x6(u8) fall inside a.val[] (this is a 7-byte memcpy-style copy), so they line up with the struct. Corrected sonnet's '0x1 = type' (type is @0x0; 0x1 is a.val[0]). */
struct __attribute__((packed)) g1_layout_bt_addr_le_t__param_0572 {
    uint8_t _pad_0x0[0x1];
    uint8_t addr_val[0x4]; /* catalog type: uint8_t[]; SDK member: a.val */
    uint8_t _pad_0x5[0x1];
    uint8_t addr_val_5[0x1]; /* catalog type: uint8_t; SDK member: a.val[5] */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0572, addr_val) == 0x1, "g1_layout_bt_addr_le_t__param_0572.addr_val");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0572, addr_val_5) == 0x6, "g1_layout_bt_addr_le_t__param_0572.addr_val_5");
_Static_assert(sizeof(struct g1_layout_bt_addr_le_t__param_0572) >= 0x8, "g1_layout_bt_addr_le_t__param_0572.size");

/* param_0573 | library | Bluetooth LE address (type + 6-byte address) copied by bt_addr_le_copy_80e94. | D1+D2 verified
 * review: Verified against addr.h: bt_addr_le_t { uint8_t type@0; bt_addr_t a@1 (val[6]) }. Observed reads at 0x1 (2 bytes) and 0x6 (last byte) span the 6-byte address a (bytes 1..6), confirming type@0. Copy touches only the address portion. */
struct __attribute__((packed)) g1_layout_bt_addr_le_t__param_0573 {
    uint8_t _pad_0x0[0x1];
    uint8_t a_val[0x4]; /* catalog type: uint8_t[6]; SDK member: a.val */
    uint8_t _pad_0x5[0x1];
    uint8_t a_val_last[0x1]; /* catalog type: uint8_t; SDK member: a.val[5] */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0573, a_val) == 0x1, "g1_layout_bt_addr_le_t__param_0573.a_val");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0573, a_val_last) == 0x6, "g1_layout_bt_addr_le_t__param_0573.a_val_last");
_Static_assert(sizeof(struct g1_layout_bt_addr_le_t__param_0573) >= 0x8, "g1_layout_bt_addr_le_t__param_0573.size");

/* param_0574 | G1-original | Little-endian serialization output buffer progressively filled by repeated sys_put_le64 calls (Zephyr byteorder helper). | D1+D2 verified
 * review: SPLIT from collision group global_1358. This is just a caller output buffer written by sys_put_le64, not a named library struct, so is_library=false. */
struct __attribute__((packed)) g1_layout_le_serialize_buffer__param_0574 {
    uint8_t _pad_0x0[0x4];
    uint8_t word_0[0x4]; /* catalog type: uint32_t */
    uint8_t word_1[0x4]; /* catalog type: uint32_t */
    uint8_t word_2[0x4]; /* catalog type: uint32_t */
    uint8_t word_3[0x4]; /* catalog type: uint32_t */
    uint8_t word_4[0x4]; /* catalog type: uint32_t */
    uint8_t word_5[0x4]; /* catalog type: uint32_t */
    uint8_t word_6[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_le_serialize_buffer__param_0574, word_0) == 0x4, "g1_layout_le_serialize_buffer__param_0574.word_0");
_Static_assert(offsetof(struct g1_layout_le_serialize_buffer__param_0574, word_1) == 0x8, "g1_layout_le_serialize_buffer__param_0574.word_1");
_Static_assert(offsetof(struct g1_layout_le_serialize_buffer__param_0574, word_2) == 0xc, "g1_layout_le_serialize_buffer__param_0574.word_2");
_Static_assert(offsetof(struct g1_layout_le_serialize_buffer__param_0574, word_3) == 0x10, "g1_layout_le_serialize_buffer__param_0574.word_3");
_Static_assert(offsetof(struct g1_layout_le_serialize_buffer__param_0574, word_4) == 0x14, "g1_layout_le_serialize_buffer__param_0574.word_4");
_Static_assert(offsetof(struct g1_layout_le_serialize_buffer__param_0574, word_5) == 0x18, "g1_layout_le_serialize_buffer__param_0574.word_5");
_Static_assert(offsetof(struct g1_layout_le_serialize_buffer__param_0574, word_6) == 0x1c, "g1_layout_le_serialize_buffer__param_0574.word_6");
_Static_assert(sizeof(struct g1_layout_le_serialize_buffer__param_0574) >= 0x20, "g1_layout_le_serialize_buffer__param_0574.size");

/* param_0577 | library | Bluetooth LE address (type + 6-byte address) written by a local bt_addr_le_copy reimplementation (bt_addr_le_copy_80fc4). | D1+D2 verified
 * review: VERIFIED: bt_addr_le_t {uint8_t type@0; bt_addr_t a (uint8_t val[6])@1}. Observed writes at 0x1 (first 2 addr bytes) and 0x6 (last addr byte) fall within a.val[0..5]; type@0 not accessed as a word here. */
struct __attribute__((packed)) g1_layout_bt_addr_le_t__param_0577 {
    uint8_t _pad_0x0[0x1];
    uint8_t addr_lo16[0x2]; /* catalog type: uint16_t; SDK member: a.val */
    uint8_t _pad_0x3[0x3];
    uint8_t addr_byte5[0x1]; /* catalog type: uint8_t; SDK member: a.val[5] */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0577, addr_lo16) == 0x1, "g1_layout_bt_addr_le_t__param_0577.addr_lo16");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0577, addr_byte5) == 0x6, "g1_layout_bt_addr_le_t__param_0577.addr_byte5");
_Static_assert(sizeof(struct g1_layout_bt_addr_le_t__param_0577) >= 0x8, "g1_layout_bt_addr_le_t__param_0577.size");

/* param_0578 | library | Zephyr Bluetooth LE address (type + 6-byte address) copied by bt_addr_le_copy_80fc4; accessed as a 2-byte slice at 0x1 and a byte at 0x6. | D1+D2 verified
 * review: Verified against addr.h: bt_addr_le_t = {uint8_t type@0x0; bt_addr_t a@0x1 (uint8_t val[6])}. Observed 2-byte read at 0x1 (a.val[0..1]) and byte at 0x6 (a.val[5]) fall inside the 6-byte address. Offsets match. */
struct __attribute__((packed)) g1_layout_bt_addr_le_t__param_0578 {
    uint8_t _pad_0x0[0x1];
    uint8_t addr_lo16[0x1]; /* catalog type: uint8_t; SDK member: a.val[0] */
    uint8_t _pad_0x2[0x4];
    uint8_t addr_byte5[0x1]; /* catalog type: uint8_t; SDK member: a.val[5] */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0578, addr_lo16) == 0x1, "g1_layout_bt_addr_le_t__param_0578.addr_lo16");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0578, addr_byte5) == 0x6, "g1_layout_bt_addr_le_t__param_0578.addr_byte5");
_Static_assert(sizeof(struct g1_layout_bt_addr_le_t__param_0578) >= 0x8, "g1_layout_bt_addr_le_t__param_0578.size");

/* param_0580 | library | Bluetooth LE address (type + 6-byte address) copied by bt_addr_le_copy @0x81196. | D1+D2 verified
 * review: Verified against addr.h: bt_addr_le_t { uint8_t type @0x0; bt_addr_t a (uint8 val[6]) @0x1 }. Observed word write @0x1 = a.val[0..1] and byte @0x6 = a.val[5]; total 7 bytes. Matches. */
struct __attribute__((packed)) g1_layout_bt_addr_le__param_0580 {
    uint8_t _pad_0x0[0x1];
    uint8_t addr_lo[0x2]; /* catalog type: uint16_t; SDK member: a.val */
    uint8_t _pad_0x3[0x3];
    uint8_t addr_byte5[0x1]; /* catalog type: uint8_t; SDK member: a.val[5] */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le__param_0580, addr_lo) == 0x1, "g1_layout_bt_addr_le__param_0580.addr_lo");
_Static_assert(offsetof(struct g1_layout_bt_addr_le__param_0580, addr_byte5) == 0x6, "g1_layout_bt_addr_le__param_0580.addr_byte5");
_Static_assert(sizeof(struct g1_layout_bt_addr_le__param_0580) >= 0x8, "g1_layout_bt_addr_le__param_0580.size");

/* param_0581 | library | Bluetooth LE address (type byte + 6-byte address) copied by bt_addr_le_copy (param_2). | D1+D2 verified
 * review: Layout consistent with bt_addr_le_t {uint8_t type; bt_addr_t a[6]}: type@0x0(unobserved), address bytes 0x1-0x6. Observed a 2-byte read@0x1 and byte@0x6. Not header-verified. */
struct __attribute__((packed)) g1_layout_bt_addr_le_t__param_0581 {
    uint8_t _pad_0x0[0x1];
    uint8_t addr_lo[0x2]; /* catalog type: uint16_t; SDK member: a.val[0..1] */
    uint8_t _pad_0x3[0x3];
    uint8_t addr_byte5[0x1]; /* catalog type: uint8_t; SDK member: a.val[5] */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0581, addr_lo) == 0x1, "g1_layout_bt_addr_le_t__param_0581.addr_lo");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0581, addr_byte5) == 0x6, "g1_layout_bt_addr_le_t__param_0581.addr_byte5");
_Static_assert(sizeof(struct g1_layout_bt_addr_le_t__param_0581) >= 0x8, "g1_layout_bt_addr_le_t__param_0581.size");

/* param_0585 | library | Zephyr Bluetooth connection object; bt_conn_enc_key_size reads an enc_key_size-style byte at 0xb and a uint at 0xc0. | D1+D2 verified
 * review: Same bt_conn type as param_0248 (kept separate as it is its own footprint group / different accessor). Confirmed by library accessor bt_conn_enc_key_size; 0xb and 0xc0 match param_0248's fields. Config-dependent layout means member offsets are not header-verifiable; library_verified=false. */
struct __attribute__((packed)) g1_layout_bt_conn__param_0585 {
    uint8_t _pad_0x0[0xb];
    uint8_t enc_key_size[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xc[0xb4];
    uint8_t field_0xc0[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0585, enc_key_size) == 0xb, "g1_layout_bt_conn__param_0585.enc_key_size");
_Static_assert(offsetof(struct g1_layout_bt_conn__param_0585, field_0xc0) == 0xc0, "g1_layout_bt_conn__param_0585.field_0xc0");
_Static_assert(sizeof(struct g1_layout_bt_conn__param_0585) >= 0xc4, "g1_layout_bt_conn__param_0585.size");

/* param_0586 | library | BLE connection-parameter set passed to bt_conn_le_param_update (interval/latency/timeout). | D1+D2 verified
 * review: Real bt_le_conn_param is 8 bytes of uint16 (interval_min@0x0, interval_max@0x2, latency@0x4, timeout@0x6). Observed word reads at 0x4/0x8/0xc extend past the struct and don't align, so verified=false — the param may be a wrapper/different object. Kept offsets. */
struct __attribute__((packed)) g1_layout_bt_le_conn_param__param_0586 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_le_conn_param__param_0586, field_0x4) == 0x4, "g1_layout_bt_le_conn_param__param_0586.field_0x4");
_Static_assert(offsetof(struct g1_layout_bt_le_conn_param__param_0586, field_0x8) == 0x8, "g1_layout_bt_le_conn_param__param_0586.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_le_conn_param__param_0586, field_0xc) == 0xc, "g1_layout_bt_le_conn_param__param_0586.field_0xc");
_Static_assert(sizeof(struct g1_layout_bt_le_conn_param__param_0586) >= 0x10, "g1_layout_bt_le_conn_param__param_0586.size");

/* param_0590 | G1-original | Atomic counter + poll-signal context used by atomic_counter_add_and_signal: a read-only limit/target, a rw running counter, and a rw result/status word. | D1+D2 verified
 * review: G1-original; kept naming. */
struct __attribute__((packed)) g1_layout_atomic_signal_ctx__param_0590 {
    uint8_t _pad_0x0[0x4];
    uint8_t limit_or_target[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t counter[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x18];
    uint8_t signal_result[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_atomic_signal_ctx__param_0590, limit_or_target) == 0x4, "g1_layout_atomic_signal_ctx__param_0590.limit_or_target");
_Static_assert(offsetof(struct g1_layout_atomic_signal_ctx__param_0590, counter) == 0x10, "g1_layout_atomic_signal_ctx__param_0590.counter");
_Static_assert(offsetof(struct g1_layout_atomic_signal_ctx__param_0590, signal_result) == 0x2c, "g1_layout_atomic_signal_ctx__param_0590.signal_result");
_Static_assert(sizeof(struct g1_layout_atomic_signal_ctx__param_0590) >= 0x30, "g1_layout_atomic_signal_ctx__param_0590.size");

/* param_0592 | G1-original | Context object released/notified via context_release_and_notify: leading callback ptr, flags, and a semaphore/event value near the end. | D1+D2 verified
 * review: G1-original (~0xba). field_0x0 is a code-typed callback ptr. */
struct __attribute__((packed)) g1_layout_context_release_ctx__param_0592 {
    uint8_t callback_fn[0x4]; /* catalog type: void * */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x4];
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x1d];
    uint8_t field_0x2d[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2e[0x88];
    uint8_t field_0xb6[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_context_release_ctx__param_0592, callback_fn) == 0x0, "g1_layout_context_release_ctx__param_0592.callback_fn");
_Static_assert(offsetof(struct g1_layout_context_release_ctx__param_0592, field_0x4) == 0x4, "g1_layout_context_release_ctx__param_0592.field_0x4");
_Static_assert(offsetof(struct g1_layout_context_release_ctx__param_0592, field_0xc) == 0xc, "g1_layout_context_release_ctx__param_0592.field_0xc");
_Static_assert(offsetof(struct g1_layout_context_release_ctx__param_0592, field_0x2d) == 0x2d, "g1_layout_context_release_ctx__param_0592.field_0x2d");
_Static_assert(offsetof(struct g1_layout_context_release_ctx__param_0592, field_0xb6) == 0xb6, "g1_layout_context_release_ctx__param_0592.field_0xb6");
_Static_assert(sizeof(struct g1_layout_context_release_ctx__param_0592) >= 0xba, "g1_layout_context_release_ctx__param_0592.size");

/* param_0597 | library | L2CAP channel context passed to l2cap_chan_disconnected_cb (state u16 + ptr + word). | D1+D2 verified
 * review: bt_l2cap_chan internal (host/l2cap_internal.h, version-specific); 0x4/0x8/0xc unverifiable. verified=false. */
struct __attribute__((packed)) g1_layout_bt_l2cap_chan_ctx__param_0597 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x6[0x2];
    uint8_t field_0x8[0x4]; /* catalog type: void * */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_l2cap_chan_ctx__param_0597, field_0x4) == 0x4, "g1_layout_bt_l2cap_chan_ctx__param_0597.field_0x4");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_chan_ctx__param_0597, field_0x8) == 0x8, "g1_layout_bt_l2cap_chan_ctx__param_0597.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_chan_ctx__param_0597, field_0xc) == 0xc, "g1_layout_bt_l2cap_chan_ctx__param_0597.field_0xc");
_Static_assert(sizeof(struct g1_layout_bt_l2cap_chan_ctx__param_0597) >= 0x10, "g1_layout_bt_l2cap_chan_ctx__param_0597.size");

/* param_0599 | library | param_3 of attr_read_type_cb (a LIBRARY fn): ATT read-by-type response accumulation context (attr/list pointer + running count word). | D1+D2 verified
 * review: Internal bt_att accumulation struct; only 2 fields, unverified. */
struct __attribute__((packed)) g1_layout_att_read_type_acc__param_0599 {
    uint8_t _pad_0x0[0xc];
    uint8_t attr_ptr[0x4]; /* catalog type: void * */
    uint8_t count_or_len[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_att_read_type_acc__param_0599, attr_ptr) == 0xc, "g1_layout_att_read_type_acc__param_0599.attr_ptr");
_Static_assert(offsetof(struct g1_layout_att_read_type_acc__param_0599, count_or_len) == 0x10, "g1_layout_att_read_type_acc__param_0599.count_or_len");
_Static_assert(sizeof(struct g1_layout_att_read_type_acc__param_0599) >= 0x14, "g1_layout_att_read_type_acc__param_0599.size");

/* param_0601 | library | Zephyr BLE ATT notify-multiple internal parameter block (param_2) used by att_notify_mult: a data-length word and a handle/count field. | D1+D2 verified
 * review: Internal ATT params; not in a pinned public header, so library_verified=false. */
struct __attribute__((packed)) g1_layout_att_notify_mult_ctx__param_0601 {
    uint8_t _pad_0x0[0xc];
    uint8_t data_len[0x4]; /* catalog type: uint32_t */
    uint8_t handle_or_count[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_att_notify_mult_ctx__param_0601, data_len) == 0xc, "g1_layout_att_notify_mult_ctx__param_0601.data_len");
_Static_assert(offsetof(struct g1_layout_att_notify_mult_ctx__param_0601, handle_or_count) == 0x10, "g1_layout_att_notify_mult_ctx__param_0601.handle_or_count");
_Static_assert(sizeof(struct g1_layout_att_notify_mult_ctx__param_0601) >= 0x14, "g1_layout_att_notify_mult_ctx__param_0601.size");

/* param_0602 | library | ATT notify buffer (a net_buf view) read by att_notify: a size/data word at 0xc and a length short at 0x10. | D1+D2 verified
 * review: Same net_buf_simple data/len region (0xc/0x10) as param_0172/param_0223, but only two fields here; library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_net_buf_att_view__param_0602 {
    uint8_t _pad_0x0[0xc];
    uint8_t data[0x4]; /* catalog type: uint8_t * */
    uint8_t len[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_net_buf_att_view__param_0602, data) == 0xc, "g1_layout_net_buf_att_view__param_0602.data");
_Static_assert(offsetof(struct g1_layout_net_buf_att_view__param_0602, len) == 0x10, "g1_layout_net_buf_att_view__param_0602.len");
_Static_assert(sizeof(struct g1_layout_net_buf_att_view__param_0602) >= 0x14, "g1_layout_net_buf_att_view__param_0602.size");

/* param_0603 | G1-original | Small descriptor passed to FUN_00081c8c (likely a UI element/box render descriptor: type/id, size, pointer/index, coordinate). | D1+D2 verified
 * review: G1-original, low signal. is_union=true: 0x4 accessed 2-wide over 1-byte gap to 0x5. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_box_render_desc__param_0603 {
    uint8_t _pad_0x0[0x2];
    uint8_t type_id[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x1];
    uint8_t size[0x1]; /* catalog type: uint16_t */
    uint8_t field_0x5[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x6[0x6];
    uint8_t ptr_or_index[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x2];
    uint8_t coord_or_count[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_box_render_desc__param_0603, type_id) == 0x2, "g1_layout_box_render_desc__param_0603.type_id");
_Static_assert(offsetof(struct g1_layout_box_render_desc__param_0603, size) == 0x4, "g1_layout_box_render_desc__param_0603.size");
_Static_assert(offsetof(struct g1_layout_box_render_desc__param_0603, field_0x5) == 0x5, "g1_layout_box_render_desc__param_0603.field_0x5");
_Static_assert(offsetof(struct g1_layout_box_render_desc__param_0603, ptr_or_index) == 0xc, "g1_layout_box_render_desc__param_0603.ptr_or_index");
_Static_assert(offsetof(struct g1_layout_box_render_desc__param_0603, coord_or_count) == 0x12, "g1_layout_box_render_desc__param_0603.coord_or_count");
_Static_assert(sizeof(struct g1_layout_box_render_desc__param_0603) >= 0x16, "g1_layout_box_render_desc__param_0603.size");

/* param_0604 | library | net_buf_simple-style buffer cursor shared by GATT ATT encode helpers (find_info_cb, gatt_read_group/type_encode, gatt_prepare_write_encode, gatt_write_ccc_buf). | D1+D2 verified
 * review: All 5 members library-class GATT encoders. Ghidra flagged overlaps at 0x4/0xc (width>gap) → is_union=true. Mixed 8/16/32-bit accesses of a data/len/size descriptor; offsets not header-verified. */
struct __attribute__((packed)) g1_layout_net_buf_simple__param_0604 {
    uint8_t type_or_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x3];
    uint8_t data_or_len[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x6[0x2];
    uint8_t size_or_off[0x4]; /* catalog type: uint32_t */
    uint8_t handle_or_uuid[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xe[0x2];
    uint8_t tail_field[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0604, type_or_flag) == 0x0, "g1_layout_net_buf_simple__param_0604.type_or_flag");
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0604, data_or_len) == 0x4, "g1_layout_net_buf_simple__param_0604.data_or_len");
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0604, size_or_off) == 0x8, "g1_layout_net_buf_simple__param_0604.size_or_off");
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0604, handle_or_uuid) == 0xc, "g1_layout_net_buf_simple__param_0604.handle_or_uuid");
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0604, tail_field) == 0x10, "g1_layout_net_buf_simple__param_0604.tail_field");
_Static_assert(sizeof(struct g1_layout_net_buf_simple__param_0604) >= 0x14, "g1_layout_net_buf_simple__param_0604.size");

/* param_0606 | library | Zephyr ATT channel context used by att_chan_read: an MTU field and a pending handle/offset field. | D1+D2 verified
 * review: Accessor att_chan_read suggests bt_att_chan, but bt_att_chan is a private host struct (not in a pinned public header) and only three sparse fields observed; library_verified=false. */
struct __attribute__((packed)) g1_layout_bt_att_chan__param_0606 {
    uint8_t _pad_0x0[0x8];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x12];
    uint8_t mtu[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x20[0xe];
    uint8_t handle_or_offset[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0606, field_0x8) == 0x8, "g1_layout_bt_att_chan__param_0606.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0606, mtu) == 0x1e, "g1_layout_bt_att_chan__param_0606.mtu");
_Static_assert(offsetof(struct g1_layout_bt_att_chan__param_0606, handle_or_offset) == 0x2e, "g1_layout_bt_att_chan__param_0606.handle_or_offset");
_Static_assert(sizeof(struct g1_layout_bt_att_chan__param_0606) >= 0x32, "g1_layout_bt_att_chan__param_0606.size");

/* param_0607 | G1-original | Unidentified small G1 context (flag byte + two words) used inside FUN_00081fbe. | D1+D2 verified
 * review: Unidentified; kept offsets. */
struct __attribute__((packed)) g1_layout_cmd_ctx_0607__param_0607 {
    uint8_t _pad_0x0[0x3];
    uint8_t field_0x3[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cmd_ctx_0607__param_0607, field_0x3) == 0x3, "g1_layout_cmd_ctx_0607__param_0607.field_0x3");
_Static_assert(offsetof(struct g1_layout_cmd_ctx_0607__param_0607, field_0x4) == 0x4, "g1_layout_cmd_ctx_0607__param_0607.field_0x4");
_Static_assert(offsetof(struct g1_layout_cmd_ctx_0607__param_0607, field_0x8) == 0x8, "g1_layout_cmd_ctx_0607__param_0607.field_0x8");
_Static_assert(sizeof(struct g1_layout_cmd_ctx_0607__param_0607) >= 0xc, "g1_layout_cmd_ctx_0607__param_0607.size");

/* param_0610 | library | Zephyr Bluetooth ATT request object processed by att_req_send_process: response callback, user data, and the request net_buf pointer. | D1+D2 verified
 * review: bt_att_req is defined in the private host header att_internal.h (not in the pinned tree); callback/user_data/buf triple is consistent but offsets unverified. */
struct __attribute__((packed)) g1_layout_bt_att_req__param_0610 {
    uint8_t _pad_0x0[0x4];
    uint8_t func_or_cb[0x4]; /* catalog type: void * */
    uint8_t user_data[0x4]; /* catalog type: void * */
    uint8_t _pad_0xc[0x24];
    uint8_t buf[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_bt_att_req__param_0610, func_or_cb) == 0x4, "g1_layout_bt_att_req__param_0610.func_or_cb");
_Static_assert(offsetof(struct g1_layout_bt_att_req__param_0610, user_data) == 0x8, "g1_layout_bt_att_req__param_0610.user_data");
_Static_assert(offsetof(struct g1_layout_bt_att_req__param_0610, buf) == 0x30, "g1_layout_bt_att_req__param_0610.buf");
_Static_assert(sizeof(struct g1_layout_bt_att_req__param_0610) >= 0x34, "g1_layout_bt_att_req__param_0610.size");

/* param_0611 | library | ATT indicate parameters passed to att_indicate (value word + attribute handle). | D1+D2 verified
 * review: LIBRARY-class member (att_indicate); only two fields observed, unverified. */
struct __attribute__((packed)) g1_layout_bt_gatt_indicate_params__param_0611 {
    uint8_t _pad_0x0[0xc];
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t handle[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_indicate_params__param_0611, field_0xc) == 0xc, "g1_layout_bt_gatt_indicate_params__param_0611.field_0xc");
_Static_assert(offsetof(struct g1_layout_bt_gatt_indicate_params__param_0611, handle) == 0x10, "g1_layout_bt_gatt_indicate_params__param_0611.handle");
_Static_assert(sizeof(struct g1_layout_bt_gatt_indicate_params__param_0611) >= 0x14, "g1_layout_bt_gatt_indicate_params__param_0611.size");

/* param_0612 | library | ATT channel view read by att_write_cmd (conn state word + MTU u16); same family as param_0234/bt_att_chan. | D1+D2 verified
 * review: Internal ATT channel; offsets 0xc/0x10 unverifiable. Distinct param slot from param_0234, kept separate. verified=false. */
struct __attribute__((packed)) g1_layout_bt_att_chan_view2__param_0612 {
    uint8_t _pad_0x0[0xc];
    uint8_t conn_state[0x4]; /* catalog type: uint32_t */
    uint8_t mtu[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_bt_att_chan_view2__param_0612, conn_state) == 0xc, "g1_layout_bt_att_chan_view2__param_0612.conn_state");
_Static_assert(offsetof(struct g1_layout_bt_att_chan_view2__param_0612, mtu) == 0x10, "g1_layout_bt_att_chan_view2__param_0612.mtu");
_Static_assert(sizeof(struct g1_layout_bt_att_chan_view2__param_0612) >= 0x14, "g1_layout_bt_att_chan_view2__param_0612.size");

/* param_0613 | library | param_2 of att_write_req_recv: ATT Write Request PDU/context view (length/ctx word + attribute handle). | D1+D2 verified
 * review: Only 2 fields; ATT handle at 0x10 plausible but unverified. */
struct __attribute__((packed)) g1_layout_att_write_req_view__param_0613 {
    uint8_t _pad_0x0[0xc];
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t attr_handle[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_att_write_req_view__param_0613, field_0xc) == 0xc, "g1_layout_att_write_req_view__param_0613.field_0xc");
_Static_assert(offsetof(struct g1_layout_att_write_req_view__param_0613, attr_handle) == 0x10, "g1_layout_att_write_req_view__param_0613.attr_handle");
_Static_assert(sizeof(struct g1_layout_att_write_req_view__param_0613) >= 0x14, "g1_layout_att_write_req_view__param_0613.size");

/* param_0614 | G1-original | G1-original small length/data-pointer/value entry accessed inside FUN_000822bc. | D1+D2 verified
 * review: G1-original; low naming signal (anonymous containing function). */
struct __attribute__((packed)) g1_layout_generic_kv_entry__param_0614 {
    uint8_t _pad_0x0[0x4];
    uint8_t len[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x6[0x2];
    uint8_t data_ptr[0x4]; /* catalog type: void * */
    uint8_t value[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_generic_kv_entry__param_0614, len) == 0x4, "g1_layout_generic_kv_entry__param_0614.len");
_Static_assert(offsetof(struct g1_layout_generic_kv_entry__param_0614, data_ptr) == 0x8, "g1_layout_generic_kv_entry__param_0614.data_ptr");
_Static_assert(offsetof(struct g1_layout_generic_kv_entry__param_0614, value) == 0xc, "g1_layout_generic_kv_entry__param_0614.value");
_Static_assert(sizeof(struct g1_layout_generic_kv_entry__param_0614) >= 0x10, "g1_layout_generic_kv_entry__param_0614.size");

/* param_0618 | library | GATT Client Characteristic Configuration state read/written by gatt_ccc_changed: a CCC value short at 0x8, a second short at 0xa, and a cfg_changed callback pointer at 0xc. | D1+D2 verified
 * review: Field roles plausible for _bt_gatt_ccc but the cfg[] array and callback offsets were not byte-verified. library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_bt_gatt_ccc_managed_user_data__param_0618 {
    uint8_t _pad_0x0[0x8];
    uint8_t value[0x2]; /* catalog type: uint16_t */
    uint8_t field_0xa[0x2]; /* catalog type: uint16_t */
    uint8_t cfg_changed[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_ccc_managed_user_data__param_0618, value) == 0x8, "g1_layout_bt_gatt_ccc_managed_user_data__param_0618.value");
_Static_assert(offsetof(struct g1_layout_bt_gatt_ccc_managed_user_data__param_0618, field_0xa) == 0xa, "g1_layout_bt_gatt_ccc_managed_user_data__param_0618.field_0xa");
_Static_assert(offsetof(struct g1_layout_bt_gatt_ccc_managed_user_data__param_0618, cfg_changed) == 0xc, "g1_layout_bt_gatt_ccc_managed_user_data__param_0618.cfg_changed");
_Static_assert(sizeof(struct g1_layout_bt_gatt_ccc_managed_user_data__param_0618) >= 0x10, "g1_layout_bt_gatt_ccc_managed_user_data__param_0618.size");

/* param_0619 | library | GATT indicate-parameters block used by gatt_indicate_rsp (param_5): callback and destroy function pointers plus a type/flags byte. | D1+D2 verified
 * review: gatt_indicate_rsp is LIBRARY-class; bt_gatt_indicate_params plausible (func@0x8, destroy@0xc, type@0x16) but not cross-checked against gatt.h. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_bt_gatt_indicate_params__param_0619 {
    uint8_t _pad_0x0[0x8];
    uint8_t func[0x4]; /* catalog type: void * */
    uint8_t destroy[0x4]; /* catalog type: void * */
    uint8_t _pad_0x10[0x6];
    uint8_t type[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_indicate_params__param_0619, func) == 0x8, "g1_layout_bt_gatt_indicate_params__param_0619.func");
_Static_assert(offsetof(struct g1_layout_bt_gatt_indicate_params__param_0619, destroy) == 0xc, "g1_layout_bt_gatt_indicate_params__param_0619.destroy");
_Static_assert(offsetof(struct g1_layout_bt_gatt_indicate_params__param_0619, type) == 0x16, "g1_layout_bt_gatt_indicate_params__param_0619.type");
_Static_assert(sizeof(struct g1_layout_bt_gatt_indicate_params__param_0619) >= 0x1a, "g1_layout_bt_gatt_indicate_params__param_0619.size");

/* param_0620 | library | Small descriptor (hash function pointer + context index) passed to gen_hash_m (param_1). | D1+D2 verified
 * review: Callee is library-class but no matching stock struct identified; kept generic {code ptr, ctx idx}. is_library retained true only to flag the library-class callee; no library_name asserted. */
struct __attribute__((packed)) g1_layout_hash_algo_desc__param_0620 {
    uint8_t hash_fn[0x4]; /* catalog type: void* */
    uint8_t ctx_idx[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_hash_algo_desc__param_0620, hash_fn) == 0x0, "g1_layout_hash_algo_desc__param_0620.hash_fn");
_Static_assert(offsetof(struct g1_layout_hash_algo_desc__param_0620, ctx_idx) == 0x4, "g1_layout_hash_algo_desc__param_0620.ctx_idx");
_Static_assert(sizeof(struct g1_layout_hash_algo_desc__param_0620) >= 0x8, "g1_layout_hash_algo_desc__param_0620.size");

/* param_0623 | library | ATT Find-Information response encoding context (attribute handle / UUID 16-bit fields) used by gatt_find_info_encode. | D1+D2 verified
 * review: Kept naming; offsets unchanged. Exact ATT find-info struct unresolved. */
struct __attribute__((packed)) g1_layout_gatt_find_info_entry__param_0623 {
    uint8_t _pad_0x0[0x8];
    uint8_t field_0x8[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xa[0x4];
    uint8_t field_0xe[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_find_info_entry__param_0623, field_0x8) == 0x8, "g1_layout_gatt_find_info_entry__param_0623.field_0x8");
_Static_assert(offsetof(struct g1_layout_gatt_find_info_entry__param_0623, field_0xe) == 0xe, "g1_layout_gatt_find_info_entry__param_0623.field_0xe");
_Static_assert(sizeof(struct g1_layout_gatt_find_info_entry__param_0623) >= 0x10, "g1_layout_gatt_find_info_entry__param_0623.size");

/* param_0624 | library | ATT write-request encode context used by gatt_write_encode (handle u16, value/opcode word, second handle/offset u16). | D1+D2 verified
 * review: Internal ATT encode context (non-public); offsets not verifiable. Kept offsets. */
struct __attribute__((packed)) g1_layout_gatt_write_encode_ctx__param_0624 {
    uint8_t _pad_0x0[0x4];
    uint8_t handle[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x6[0x2];
    uint8_t value_or_opcode[0x4]; /* catalog type: uint32_t */
    uint8_t offset_or_handle2[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_gatt_write_encode_ctx__param_0624, handle) == 0x4, "g1_layout_gatt_write_encode_ctx__param_0624.handle");
_Static_assert(offsetof(struct g1_layout_gatt_write_encode_ctx__param_0624, value_or_opcode) == 0x8, "g1_layout_gatt_write_encode_ctx__param_0624.value_or_opcode");
_Static_assert(offsetof(struct g1_layout_gatt_write_encode_ctx__param_0624, offset_or_handle2) == 0xc, "g1_layout_gatt_write_encode_ctx__param_0624.offset_or_handle2");
_Static_assert(sizeof(struct g1_layout_gatt_write_encode_ctx__param_0624) >= 0x10, "g1_layout_gatt_write_encode_ctx__param_0624.size");

/* param_0625 | library | Bluetooth LE address structure (address type byte + 6-byte address) written by bt_addr_le_copy_828da. | D1+D2 verified
 * review: Verified against addr.h: bt_addr_le_t = { uint8_t type; bt_addr_t a; } with bt_addr_t = { uint8_t val[6]; }, so type@0x0 and a.val[0..5]@0x1-0x6. The observed writes (2 bytes @0x1, 1 byte @0x6) are chunks of the 6-byte a.val — offsets consistent, verified. */
struct __attribute__((packed)) g1_layout_bt_addr_le_t__param_0625 {
    uint8_t _pad_0x0[0x1];
    uint8_t a_val_lo[0x2]; /* catalog type: uint16_t; SDK member: a.val */
    uint8_t _pad_0x3[0x3];
    uint8_t a_val_hi[0x1]; /* catalog type: uint8_t; SDK member: a.val */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0625, a_val_lo) == 0x1, "g1_layout_bt_addr_le_t__param_0625.a_val_lo");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0625, a_val_hi) == 0x6, "g1_layout_bt_addr_le_t__param_0625.a_val_hi");
_Static_assert(sizeof(struct g1_layout_bt_addr_le_t__param_0625) >= 0x8, "g1_layout_bt_addr_le_t__param_0625.size");

/* param_0626 | library | Bluetooth LE address argument (param_2) copied by bt_addr_le_copy_828da. | D1+D2 verified
 * review: BLE address (type byte + 6 addr bytes = 7 bytes); the observed 2-byte read at 0x1 and byte at 0x6 fall within the a.val[] region but were not header-verified. */
struct __attribute__((packed)) g1_layout_bt_addr_le_t__param_0626 {
    uint8_t _pad_0x0[0x1];
    uint8_t addr_val_0_1[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x3[0x3];
    uint8_t addr_val_5[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0626, addr_val_0_1) == 0x1, "g1_layout_bt_addr_le_t__param_0626.addr_val_0_1");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0626, addr_val_5) == 0x6, "g1_layout_bt_addr_le_t__param_0626.addr_val_5");
_Static_assert(sizeof(struct g1_layout_bt_addr_le_t__param_0626) >= 0x8, "g1_layout_bt_addr_le_t__param_0626.size");

/* param_0627 | library | GATT Service Changed context cleared by gatt_sc_ctx_clear (two words). | D1+D2 verified
 * review: Service-Changed state lives in host/gatt.c (private static); 0x4/0x8 unverifiable. verified=false. */
struct __attribute__((packed)) g1_layout_gatt_sc_ctx__param_0627 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_sc_ctx__param_0627, field_0x4) == 0x4, "g1_layout_gatt_sc_ctx__param_0627.field_0x4");
_Static_assert(offsetof(struct g1_layout_gatt_sc_ctx__param_0627, field_0x8) == 0x8, "g1_layout_gatt_sc_ctx__param_0627.field_0x8");
_Static_assert(sizeof(struct g1_layout_gatt_sc_ctx__param_0627) >= 0xc, "g1_layout_gatt_sc_ctx__param_0627.size");

/* param_0635 | library | param_2 of bt_conn_security_sufficient: BT connection security fragment (sec level, enc key size, flags short). | D1+D2 verified
 * review: Partial bt_conn security view; layout config-dependent, unverified. */
struct __attribute__((packed)) g1_layout_bt_conn_sec_view__param_0635 {
    uint8_t _pad_0x0[0xc];
    uint8_t sec_level[0x1]; /* catalog type: uint8_t */
    uint8_t enc_key_size[0x1]; /* catalog type: uint8_t */
    uint8_t flags[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_bt_conn_sec_view__param_0635, sec_level) == 0xc, "g1_layout_bt_conn_sec_view__param_0635.sec_level");
_Static_assert(offsetof(struct g1_layout_bt_conn_sec_view__param_0635, enc_key_size) == 0xd, "g1_layout_bt_conn_sec_view__param_0635.enc_key_size");
_Static_assert(offsetof(struct g1_layout_bt_conn_sec_view__param_0635, flags) == 0xe, "g1_layout_bt_conn_sec_view__param_0635.flags");
_Static_assert(sizeof(struct g1_layout_bt_conn_sec_view__param_0635) >= 0x10, "g1_layout_bt_conn_sec_view__param_0635.size");

/* param_0636 | library | Bluetooth LE address (type + 6-byte address) written by a local bt_addr_le_copy reimplementation (bt_addr_le_copy_83062). | D1+D2 verified
 * review: VERIFIED same as param_0577 (bt_addr_le_t: type@0, a.val[6]@1). Separate footprint group / different copy helper, so emitted as its own struct; same underlying type as param_0577. */
struct __attribute__((packed)) g1_layout_bt_addr_le_t__param_0636 {
    uint8_t _pad_0x0[0x1];
    uint8_t addr_lo16[0x2]; /* catalog type: uint16_t; SDK member: a.val */
    uint8_t _pad_0x3[0x3];
    uint8_t addr_byte5[0x1]; /* catalog type: uint8_t; SDK member: a.val[5] */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0636, addr_lo16) == 0x1, "g1_layout_bt_addr_le_t__param_0636.addr_lo16");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0636, addr_byte5) == 0x6, "g1_layout_bt_addr_le_t__param_0636.addr_byte5");
_Static_assert(sizeof(struct g1_layout_bt_addr_le_t__param_0636) >= 0x8, "g1_layout_bt_addr_le_t__param_0636.size");

/* param_0637 | library | Zephyr Bluetooth LE address (type + 6-byte address) copied by bt_addr_le_copy_83062; accessed as a 2-byte slice at 0x1 and a byte at 0x6. | D1+D2 verified
 * review: Identical layout to param_0578 (a second bt_addr_le_copy variant). Verified against addr.h: type@0x0, a.val[6]@0x1. Kept as a separate record since it is a distinct cid/parameter, but note it is the same bt_addr_le_t type. Offsets match. */
struct __attribute__((packed)) g1_layout_bt_addr_le_t__param_0637 {
    uint8_t _pad_0x0[0x1];
    uint8_t addr_word_lo[0x1]; /* catalog type: uint8_t; SDK member: a.val[0] */
    uint8_t _pad_0x2[0x4];
    uint8_t addr_byte_hi[0x1]; /* catalog type: uint8_t; SDK member: a.val[5] */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0637, addr_word_lo) == 0x1, "g1_layout_bt_addr_le_t__param_0637.addr_word_lo");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0637, addr_byte_hi) == 0x6, "g1_layout_bt_addr_le_t__param_0637.addr_byte_hi");
_Static_assert(sizeof(struct g1_layout_bt_addr_le_t__param_0637) >= 0x8, "g1_layout_bt_addr_le_t__param_0637.size");

/* param_0639 | library | Bluetooth LE address (type + 6-byte address) parameter used inside smp_c1 confirm-value calculation. | D1+D2 verified
 * review: Same shape as verified bt_addr_le_t (type@0x0, a.val[6]@0x1). Observed 0x1 (2-byte) and 0x6 (byte) match a.val range; smp_c1 reads the 6-byte address. Verified layout. */
struct __attribute__((packed)) g1_layout_bt_addr_le__param_0639 {
    uint8_t _pad_0x0[0x1];
    uint8_t addr_lo[0x2]; /* catalog type: uint16_t; SDK member: a.val */
    uint8_t _pad_0x3[0x3];
    uint8_t addr_byte5[0x1]; /* catalog type: uint8_t; SDK member: a.val[5] */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le__param_0639, addr_lo) == 0x1, "g1_layout_bt_addr_le__param_0639.addr_lo");
_Static_assert(offsetof(struct g1_layout_bt_addr_le__param_0639, addr_byte5) == 0x6, "g1_layout_bt_addr_le__param_0639.addr_byte5");
_Static_assert(sizeof(struct g1_layout_bt_addr_le__param_0639) >= 0x8, "g1_layout_bt_addr_le__param_0639.size");

/* param_0640 | G1-original | Agent output missing for this cluster; mechanical Ghidra layout retained. | D1+D2 verified
 * review: MECHANICAL FALLBACK (no agent proposal) */
struct __attribute__((packed)) g1_layout_param_0640_mechanical__param_0640 {
    uint8_t _pad_0x0[0x1];
    uint8_t field_0x1[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x3[0x3];
    uint8_t field_0x6[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x1];
};
_Static_assert(offsetof(struct g1_layout_param_0640_mechanical__param_0640, field_0x1) == 0x1, "g1_layout_param_0640_mechanical__param_0640.field_0x1");
_Static_assert(offsetof(struct g1_layout_param_0640_mechanical__param_0640, field_0x6) == 0x6, "g1_layout_param_0640_mechanical__param_0640.field_0x6");
_Static_assert(sizeof(struct g1_layout_param_0640_mechanical__param_0640) >= 0x8, "g1_layout_param_0640_mechanical__param_0640.size");

/* param_0641 | library | SMP c1 confirm-value computation parameter block used by smp_c1 (param_6). | D1+D2 verified
 * review: Kept naming; offsets unchanged. Two fields at odd (unaligned) offsets 0x1/0x5, likely a packed pairing-data buffer; not header-verifiable. */
struct __attribute__((packed)) g1_layout_smp_c1_param__param_0641 {
    uint8_t _pad_0x0[0x1];
    uint8_t field_0x1[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x5[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_smp_c1_param__param_0641, field_0x1) == 0x1, "g1_layout_smp_c1_param__param_0641.field_0x1");
_Static_assert(offsetof(struct g1_layout_smp_c1_param__param_0641, field_0x5) == 0x5, "g1_layout_smp_c1_param__param_0641.field_0x5");
_Static_assert(sizeof(struct g1_layout_smp_c1_param__param_0641) >= 0x9, "g1_layout_smp_c1_param__param_0641.size");

/* param_0642 | library | Bluetooth LE device address argument to the SM 'c1' confirm-value function smp_c1 (type byte + 6-byte address). | D1+D2 verified
 * review: VERIFIED against addr.h: bt_addr_le_t = { uint8_t type@0x0; bt_addr_t a { uint8_t val[6] }@0x1..0x6 }. Observed reads at 0x1(4 bytes) + 0x5(2 bytes) exactly cover a.val[0..5]. Kept offsets. */
struct __attribute__((packed)) g1_layout_bt_addr_le_t__param_0642 {
    uint8_t _pad_0x0[0x1];
    uint8_t addr_lo[0x4]; /* catalog type: uint8_t[4]; SDK member: a.val[0..3] */
    uint8_t addr_hi[0x4]; /* catalog type: uint8_t[2]; SDK member: a.val[4..5] */
};
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0642, addr_lo) == 0x1, "g1_layout_bt_addr_le_t__param_0642.addr_lo");
_Static_assert(offsetof(struct g1_layout_bt_addr_le_t__param_0642, addr_hi) == 0x5, "g1_layout_bt_addr_le_t__param_0642.addr_hi");
_Static_assert(sizeof(struct g1_layout_bt_addr_le_t__param_0642) >= 0x9, "g1_layout_bt_addr_le_t__param_0642.size");

/* param_0643 | library | Byte buffer carrying key/material fragments passed as param_6 to bt_crypto_f6 (SM crypto f6 confirm-value function). | D1+D2 verified
 * review: Raw byte buffer argument to bt_crypto_f6 (not a named struct); unaligned undefined4/undefined2 reads at 0x1/0x5 are just buffer accesses. library_verified=false. */
struct __attribute__((packed)) g1_layout_smp_f6_input_buf__param_0643 {
    uint8_t _pad_0x0[0x1];
    uint8_t field_0x1[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x5[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_smp_f6_input_buf__param_0643, field_0x1) == 0x1, "g1_layout_smp_f6_input_buf__param_0643.field_0x1");
_Static_assert(offsetof(struct g1_layout_smp_f6_input_buf__param_0643, field_0x5) == 0x5, "g1_layout_smp_f6_input_buf__param_0643.field_0x5");
_Static_assert(sizeof(struct g1_layout_smp_f6_input_buf__param_0643) >= 0x9, "g1_layout_smp_f6_input_buf__param_0643.size");

/* param_0644 | library | 128-bit input value buffer (param_7) for the BLE SC f6 key-derivation function bt_crypto_f6, viewed as a byte buffer. | D1+D2 verified
 * review: Byte buffer accessed at sub-word offsets; not a named struct, treated as array input. */
struct __attribute__((packed)) g1_layout_bt_crypto_f6_input__param_0644 {
    uint8_t _pad_0x0[0x1];
    uint8_t bytes_1_4[0x4]; /* catalog type: uint32_t */
    uint8_t bytes_5_6[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_bt_crypto_f6_input__param_0644, bytes_1_4) == 0x1, "g1_layout_bt_crypto_f6_input__param_0644.bytes_1_4");
_Static_assert(offsetof(struct g1_layout_bt_crypto_f6_input__param_0644, bytes_5_6) == 0x5, "g1_layout_bt_crypto_f6_input__param_0644.bytes_5_6");
_Static_assert(sizeof(struct g1_layout_bt_crypto_f6_input__param_0644) >= 0x9, "g1_layout_bt_crypto_f6_input__param_0644.size");

/* param_0645 | library | Zephyr net_buf_simple initialized by net_buf_simple_init_with_data (len/size + backing __buf pointer). | D1+D2 verified
 * review: Checked net/buf.h: net_buf_simple = {uint8* data@0x0; uint16 len@0x4; uint16 size@0x6; uint8* __buf@0x8}. Observed 0x6->size and 0x8->__buf match exactly. Observed write at 0x1(u16) does NOT match len@0x4 (Ghidra decompiler artifact / unaligned store of the len write), so verified=false despite confident identification. */
struct __attribute__((packed)) g1_layout_net_buf_simple__param_0645 {
    uint8_t _pad_0x0[0x1];
    uint8_t len_write[0x2]; /* catalog type: uint16_t; SDK member: len */
    uint8_t _pad_0x3[0x3];
    uint8_t size[0x2]; /* catalog type: uint16_t; SDK member: size */
    uint8_t __buf[0x4]; /* catalog type: uint8_t *; SDK member: __buf */
};
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0645, len_write) == 0x1, "g1_layout_net_buf_simple__param_0645.len_write");
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0645, size) == 0x6, "g1_layout_net_buf_simple__param_0645.size");
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0645, __buf) == 0x8, "g1_layout_net_buf_simple__param_0645.__buf");
_Static_assert(sizeof(struct g1_layout_net_buf_simple__param_0645) >= 0xc, "g1_layout_net_buf_simple__param_0645.size");

/* param_0647 | library | Zephyr net_buf_simple header read by net_buf_simple_tailroom (a LIBRARY fn): current len, total size, and backing storage pointer __buf. | D1+D2 verified
 * review: Verified against net/buf.h: data@0, len@4, size@6, __buf@8. Observed size@0x6 and __buf@0x8 match exactly. The reported field_0x1 (2-byte) is an unaligned Ghidra artifact and does NOT correspond to len@0x4 - noted rather than trusted. */
struct __attribute__((packed)) g1_layout_net_buf_simple__param_0647 {
    uint8_t _pad_0x0[0x1];
    uint8_t field_0x1[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x3[0x3];
    uint8_t size[0x2]; /* catalog type: uint16_t; SDK member: size */
    uint8_t __buf[0x4]; /* catalog type: uint8_t *; SDK member: __buf */
};
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0647, field_0x1) == 0x1, "g1_layout_net_buf_simple__param_0647.field_0x1");
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0647, size) == 0x6, "g1_layout_net_buf_simple__param_0647.size");
_Static_assert(offsetof(struct g1_layout_net_buf_simple__param_0647, __buf) == 0x8, "g1_layout_net_buf_simple__param_0647.__buf");
_Static_assert(sizeof(struct g1_layout_net_buf_simple__param_0647) >= 0xc, "g1_layout_net_buf_simple__param_0647.size");

/* param_0649 | G1-original | G1-original start/end style pair (0x4 and 0x10) used within FUN_000837e8. | D1+D2 verified
 * review: G1-original; low naming signal. */
struct __attribute__((packed)) g1_layout_generic_range_pair__param_0649 {
    uint8_t _pad_0x0[0x4];
    uint8_t start[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t end[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_generic_range_pair__param_0649, start) == 0x4, "g1_layout_generic_range_pair__param_0649.start");
_Static_assert(offsetof(struct g1_layout_generic_range_pair__param_0649, end) == 0x10, "g1_layout_generic_range_pair__param_0649.end");
_Static_assert(sizeof(struct g1_layout_generic_range_pair__param_0649) >= 0x14, "g1_layout_generic_range_pair__param_0649.size");

/* param_0651 | library | Flash page descriptor filled by flash_get_page_info_by_offs (param_3): start_offset and size (matching Zephyr flash_map flash_pages_info). | D1+D2 verified
 * review: Header MISMATCH on base: flash_pages_info is {start_offset@0x0, size@0x4, index@0x8}, but observed writes are at 0x4 and 0x8 (with 0x0 unused) — shifted +4. Function name matches the Zephyr API so the type is likely right, but the observed access base does not align to the header; library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_flash_pages_info__param_0651 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_flash_pages_info__param_0651, field_0x4) == 0x4, "g1_layout_flash_pages_info__param_0651.field_0x4");
_Static_assert(offsetof(struct g1_layout_flash_pages_info__param_0651, field_0x8) == 0x8, "g1_layout_flash_pages_info__param_0651.field_0x8");
_Static_assert(sizeof(struct g1_layout_flash_pages_info__param_0651) >= 0xc, "g1_layout_flash_pages_info__param_0651.size");

/* param_0661 | library | Zephyr pinctrl state descriptor looked up by pinctrl_lookup_state (pins pointer/id + pin-count byte). | D1+D2 verified
 * review: pinctrl_state id kept (LIBRARY member); member offsets not cross-checked against pinctrl.h. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_pinctrl_state__param_0661 {
    uint8_t _pad_0x0[0x4];
    uint8_t pins_ptr_or_id[0x4]; /* catalog type: uint32_t */
    uint8_t pin_cnt[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_pinctrl_state__param_0661, pins_ptr_or_id) == 0x4, "g1_layout_pinctrl_state__param_0661.pins_ptr_or_id");
_Static_assert(offsetof(struct g1_layout_pinctrl_state__param_0661, pin_cnt) == 0x8, "g1_layout_pinctrl_state__param_0661.pin_cnt");
_Static_assert(sizeof(struct g1_layout_pinctrl_state__param_0661) >= 0xc, "g1_layout_pinctrl_state__param_0661.size");

/* param_0662 | library | Peripheral PUBLISH register block written by dppi_apply_channel_config_table (param_3) when wiring DPPI channel routing. | D1+D2 verified
 * review: Register-block object (offsets 0x508-0x56c), all write-only PUBLISH_xxx registers. Peripheral-specific; not a portable named struct, so verified=false. Kept all 16 observed offsets. */
struct __attribute__((packed)) g1_layout_nrf_periph_publish_regs__param_0662 {
    uint8_t _pad_0x0[0x508];
    uint8_t publish_0[0x4]; /* catalog type: uint32_t */
    uint8_t publish_1[0x4]; /* catalog type: uint32_t */
    uint8_t publish_2[0x4]; /* catalog type: uint32_t */
    uint8_t publish_3[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x518[0xc];
    uint8_t publish_4[0x4]; /* catalog type: uint32_t */
    uint8_t publish_5[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x52c[0x4];
    uint8_t publish_6[0x4]; /* catalog type: uint32_t */
    uint8_t publish_7[0x4]; /* catalog type: uint32_t */
    uint8_t publish_8[0x4]; /* catalog type: uint32_t */
    uint8_t publish_9[0x4]; /* catalog type: uint32_t */
    uint8_t publish_10[0x4]; /* catalog type: uint32_t */
    uint8_t publish_11[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x548[0x18];
    uint8_t publish_12[0x4]; /* catalog type: uint32_t */
    uint8_t publish_13[0x4]; /* catalog type: uint32_t */
    uint8_t publish_14[0x4]; /* catalog type: uint32_t */
    uint8_t publish_15[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_0) == 0x508, "g1_layout_nrf_periph_publish_regs__param_0662.publish_0");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_1) == 0x50c, "g1_layout_nrf_periph_publish_regs__param_0662.publish_1");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_2) == 0x510, "g1_layout_nrf_periph_publish_regs__param_0662.publish_2");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_3) == 0x514, "g1_layout_nrf_periph_publish_regs__param_0662.publish_3");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_4) == 0x524, "g1_layout_nrf_periph_publish_regs__param_0662.publish_4");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_5) == 0x528, "g1_layout_nrf_periph_publish_regs__param_0662.publish_5");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_6) == 0x530, "g1_layout_nrf_periph_publish_regs__param_0662.publish_6");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_7) == 0x534, "g1_layout_nrf_periph_publish_regs__param_0662.publish_7");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_8) == 0x538, "g1_layout_nrf_periph_publish_regs__param_0662.publish_8");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_9) == 0x53c, "g1_layout_nrf_periph_publish_regs__param_0662.publish_9");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_10) == 0x540, "g1_layout_nrf_periph_publish_regs__param_0662.publish_10");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_11) == 0x544, "g1_layout_nrf_periph_publish_regs__param_0662.publish_11");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_12) == 0x560, "g1_layout_nrf_periph_publish_regs__param_0662.publish_12");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_13) == 0x564, "g1_layout_nrf_periph_publish_regs__param_0662.publish_13");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_14) == 0x568, "g1_layout_nrf_periph_publish_regs__param_0662.publish_14");
_Static_assert(offsetof(struct g1_layout_nrf_periph_publish_regs__param_0662, publish_15) == 0x56c, "g1_layout_nrf_periph_publish_regs__param_0662.publish_15");
_Static_assert(sizeof(struct g1_layout_nrf_periph_publish_regs__param_0662) >= 0x570, "g1_layout_nrf_periph_publish_regs__param_0662.size");

/* param_0663 | G1-original | G1-original device channel descriptor shared across dev_channel_dispatch_range/validate_and_set/write_channel_mode/configure_channel: two table/handler pointers and a mode index. | D1+D2 verified
 * review: Kept naming; offsets unchanged. Four functions share this object (good cohesion). */
struct __attribute__((packed)) g1_layout_dev_channel_desc__param_0663 {
    uint8_t _pad_0x0[0x4];
    uint8_t range_or_table[0x4]; /* catalog type: void* */
    uint8_t handler_or_data[0x4]; /* catalog type: void* */
    uint8_t _pad_0xc[0x4];
    uint8_t mode[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_dev_channel_desc__param_0663, range_or_table) == 0x4, "g1_layout_dev_channel_desc__param_0663.range_or_table");
_Static_assert(offsetof(struct g1_layout_dev_channel_desc__param_0663, handler_or_data) == 0x8, "g1_layout_dev_channel_desc__param_0663.handler_or_data");
_Static_assert(offsetof(struct g1_layout_dev_channel_desc__param_0663, mode) == 0x10, "g1_layout_dev_channel_desc__param_0663.mode");
_Static_assert(sizeof(struct g1_layout_dev_channel_desc__param_0663) >= 0x14, "g1_layout_dev_channel_desc__param_0663.size");

/* param_0664 | G1-original | Dispatch-table entry read by dev_channel_dispatch_lookup (channel id + handler/index word). | D1+D2 verified
 * review: Kept offsets. */
struct __attribute__((packed)) g1_layout_dev_channel_dispatch_entry__param_0664 {
    uint8_t _pad_0x0[0x4];
    uint8_t channel_id[0x4]; /* catalog type: int32_t */
    uint8_t handler_or_index[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_dev_channel_dispatch_entry__param_0664, channel_id) == 0x4, "g1_layout_dev_channel_dispatch_entry__param_0664.channel_id");
_Static_assert(offsetof(struct g1_layout_dev_channel_dispatch_entry__param_0664, handler_or_index) == 0x8, "g1_layout_dev_channel_dispatch_entry__param_0664.handler_or_index");
_Static_assert(sizeof(struct g1_layout_dev_channel_dispatch_entry__param_0664) >= 0xc, "g1_layout_dev_channel_dispatch_entry__param_0664.size");

/* param_0669 | G1-original | Device channel-mode descriptor written by dev_write_channel_mode: a mode/index word. | D1+D2 verified
 * review: G1-original. is_union=true: the 0x4 field is read as width 4 over a gap of 2 to the 0x6 field (overlapping access). Offsets kept as ground truth. */
struct __attribute__((packed)) g1_layout_dev_channel_mode__param_0669 {
    uint8_t _pad_0x0[0x4];
    uint8_t mode[0x2]; /* catalog type: uint32_t */
    uint8_t field_0x6[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_dev_channel_mode__param_0669, mode) == 0x4, "g1_layout_dev_channel_mode__param_0669.mode");
_Static_assert(offsetof(struct g1_layout_dev_channel_mode__param_0669, field_0x6) == 0x6, "g1_layout_dev_channel_mode__param_0669.field_0x6");
_Static_assert(sizeof(struct g1_layout_dev_channel_mode__param_0669) >= 0xa, "g1_layout_dev_channel_mode__param_0669.size");

/* param_0673 | G1-original | Flash layout/region descriptor scanned by flash_page_index_lookup and layout_select_region. | D1+D2 verified
 * review: G1-original. 0x4 is accessed both 4-byte-wide and as an overlapping ushort at 0x5 -> union. Kept all observed offsets. */
struct __attribute__((packed)) g1_layout_flash_layout_region__param_0673 {
    uint8_t _pad_0x0[0x2];
    uint8_t field_0x2[0x2]; /* catalog type: uint16_t */
    uint8_t field_0x4[0x1]; /* catalog type: uint32_t */
    uint8_t field_0x5[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x7[0x3];
    uint8_t field_0xa[0x2]; /* catalog type: uint16_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x2];
    uint8_t field_0x16[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_flash_layout_region__param_0673, field_0x2) == 0x2, "g1_layout_flash_layout_region__param_0673.field_0x2");
_Static_assert(offsetof(struct g1_layout_flash_layout_region__param_0673, field_0x4) == 0x4, "g1_layout_flash_layout_region__param_0673.field_0x4");
_Static_assert(offsetof(struct g1_layout_flash_layout_region__param_0673, field_0x5) == 0x5, "g1_layout_flash_layout_region__param_0673.field_0x5");
_Static_assert(offsetof(struct g1_layout_flash_layout_region__param_0673, field_0xa) == 0xa, "g1_layout_flash_layout_region__param_0673.field_0xa");
_Static_assert(offsetof(struct g1_layout_flash_layout_region__param_0673, field_0xc) == 0xc, "g1_layout_flash_layout_region__param_0673.field_0xc");
_Static_assert(offsetof(struct g1_layout_flash_layout_region__param_0673, field_0x10) == 0x10, "g1_layout_flash_layout_region__param_0673.field_0x10");
_Static_assert(offsetof(struct g1_layout_flash_layout_region__param_0673, field_0x16) == 0x16, "g1_layout_flash_layout_region__param_0673.field_0x16");
_Static_assert(sizeof(struct g1_layout_flash_layout_region__param_0673) >= 0x1a, "g1_layout_flash_layout_region__param_0673.size");

/* param_0675 | G1-original | G1-original driver callback-registration context (callback ptr + word) used by driver_register_callback_locked. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_driver_cb_ctx__param_0675 {
    uint8_t _pad_0x0[0x4];
    uint8_t callback[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0x8];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_driver_cb_ctx__param_0675, callback) == 0x4, "g1_layout_driver_cb_ctx__param_0675.callback");
_Static_assert(offsetof(struct g1_layout_driver_cb_ctx__param_0675, field_0x10) == 0x10, "g1_layout_driver_cb_ctx__param_0675.field_0x10");
_Static_assert(sizeof(struct g1_layout_driver_cb_ctx__param_0675) >= 0x14, "g1_layout_driver_cb_ctx__param_0675.size");

/* param_0676 | G1-original | param_1 of channel_pull_one_byte: streaming byte-channel/ring-buffer context (backing buffer pointer + read index). | D1+D2 verified
 * review: Single-cid. */
struct __attribute__((packed)) g1_layout_byte_channel_ctx__param_0676 {
    uint8_t _pad_0x0[0x4];
    uint8_t buffer_ptr[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0x8];
    uint8_t read_index[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_byte_channel_ctx__param_0676, buffer_ptr) == 0x4, "g1_layout_byte_channel_ctx__param_0676.buffer_ptr");
_Static_assert(offsetof(struct g1_layout_byte_channel_ctx__param_0676, read_index) == 0x10, "g1_layout_byte_channel_ctx__param_0676.read_index");
_Static_assert(sizeof(struct g1_layout_byte_channel_ctx__param_0676) >= 0x14, "g1_layout_byte_channel_ctx__param_0676.size");

/* param_0680 | G1-original | G1-original driver context holding an active-timer handle/pointer and a related state word, used by driver_stop_active_timer. | D1+D2 verified
 * review: G1-original. */
struct __attribute__((packed)) g1_layout_driver_active_timer_ctx__param_0680 {
    uint8_t _pad_0x0[0x4];
    uint8_t timer_ptr[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0x8];
    uint8_t timer_state[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_driver_active_timer_ctx__param_0680, timer_ptr) == 0x4, "g1_layout_driver_active_timer_ctx__param_0680.timer_ptr");
_Static_assert(offsetof(struct g1_layout_driver_active_timer_ctx__param_0680, timer_state) == 0x10, "g1_layout_driver_active_timer_ctx__param_0680.timer_state");
_Static_assert(sizeof(struct g1_layout_driver_active_timer_ctx__param_0680) >= 0x14, "g1_layout_driver_active_timer_ctx__param_0680.size");

/* param_0682 | G1-original | Watchdog-disable work context passed to watchdog_disable_write_work: a device/callback pointer at 0x4 and a second pointer at 0x10. | D1+D2 verified
 * review: Single-cid G1 work ctx. Offsets kept. */
struct __attribute__((packed)) g1_layout_watchdog_disable_work_ctx__param_0682 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0x8];
    uint8_t field_0x10[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_watchdog_disable_work_ctx__param_0682, field_0x4) == 0x4, "g1_layout_watchdog_disable_work_ctx__param_0682.field_0x4");
_Static_assert(offsetof(struct g1_layout_watchdog_disable_work_ctx__param_0682, field_0x10) == 0x10, "g1_layout_watchdog_disable_work_ctx__param_0682.field_0x10");
_Static_assert(sizeof(struct g1_layout_watchdog_disable_work_ctx__param_0682) >= 0x14, "g1_layout_watchdog_disable_work_ctx__param_0682.size");

/* param_0683 | G1-original | PMIC driver context holding register-access/bus pointers, used by pmic_write_reg7_enable. | D1+D2 verified
 * review: G1-original driver context; offsets unchanged. */
struct __attribute__((packed)) g1_layout_pmic_ctx__param_0683 {
    uint8_t _pad_0x0[0x4];
    uint8_t i2c_dev[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0x8];
    uint8_t regmap[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_pmic_ctx__param_0683, i2c_dev) == 0x4, "g1_layout_pmic_ctx__param_0683.i2c_dev");
_Static_assert(offsetof(struct g1_layout_pmic_ctx__param_0683, regmap) == 0x10, "g1_layout_pmic_ctx__param_0683.regmap");
_Static_assert(sizeof(struct g1_layout_pmic_ctx__param_0683) >= 0x14, "g1_layout_pmic_ctx__param_0683.size");

/* param_0684 | library | Watchdog channel/instance handle fed by wdt_nrf_feed to reload the hardware watchdog. | D1+D2 verified
 * review: Library-class callee; channel_mask@0x4 and status@0x10 observed, offsets not header-verified. */
struct __attribute__((packed)) g1_layout_wdt_nrf_ctx__param_0684 {
    uint8_t _pad_0x0[0x4];
    uint8_t channel_mask[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t reload_status[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_wdt_nrf_ctx__param_0684, channel_mask) == 0x4, "g1_layout_wdt_nrf_ctx__param_0684.channel_mask");
_Static_assert(offsetof(struct g1_layout_wdt_nrf_ctx__param_0684, reload_status) == 0x10, "g1_layout_wdt_nrf_ctx__param_0684.reload_status");
_Static_assert(sizeof(struct g1_layout_wdt_nrf_ctx__param_0684) >= 0x14, "g1_layout_wdt_nrf_ctx__param_0684.size");

/* param_0685 | library | nRF watchdog driver config used by wdt_nrf_setup: a register/config pointer and a timeout/flags word. | D1+D2 verified
 * review: Accessor is a LIBRARY-class nRF wdt setup routine, but the config/data struct is driver-private and only two fields observed; library_verified=false. */
struct __attribute__((packed)) g1_layout_wdt_nrf_config__param_0685 {
    uint8_t _pad_0x0[0x4];
    uint8_t reg_base_or_cfg[0x4]; /* catalog type: void* */
    uint8_t _pad_0x8[0x8];
    uint8_t timeout_or_flags[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_wdt_nrf_config__param_0685, reg_base_or_cfg) == 0x4, "g1_layout_wdt_nrf_config__param_0685.reg_base_or_cfg");
_Static_assert(offsetof(struct g1_layout_wdt_nrf_config__param_0685, timeout_or_flags) == 0x10, "g1_layout_wdt_nrf_config__param_0685.timeout_or_flags");
_Static_assert(sizeof(struct g1_layout_wdt_nrf_config__param_0685) >= 0x14, "g1_layout_wdt_nrf_config__param_0685.size");

/* param_0688 | G1-original | Singly-linked-list node with a name pointer and id/hash, searched case-insensitively by sllist_find_by_name_ci. | D1+D2 verified
 * review: Kept offsets. */
struct __attribute__((packed)) g1_layout_sllist_named_node__param_0688 {
    uint8_t _pad_0x0[0x8];
    uint8_t name_ptr[0x4]; /* catalog type: const char * */
    uint8_t _pad_0xc[0x14];
    uint8_t id_or_hash[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_sllist_named_node__param_0688, name_ptr) == 0x8, "g1_layout_sllist_named_node__param_0688.name_ptr");
_Static_assert(offsetof(struct g1_layout_sllist_named_node__param_0688, id_or_hash) == 0x20, "g1_layout_sllist_named_node__param_0688.id_or_hash");
_Static_assert(sizeof(struct g1_layout_sllist_named_node__param_0688) >= 0x24, "g1_layout_sllist_named_node__param_0688.size");

/* param_0690 | library | nrfx SPIM driver control block accessed by spim_abort: a state/flags word and a trailing abort flag. | D1+D2 verified
 * review: spim_abort is a LIBRARY member; nrfx_spim control block is a file-local static (no header member offsets). Large 0x504 size consistent with the SPIM cb + DMA buffer. Unverified. */
struct __attribute__((packed)) g1_layout_nrfx_spim_cb__param_0690 {
    uint8_t _pad_0x0[0x14];
    uint8_t state_or_flags[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x4e8];
    uint8_t abort_flag[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_spim_cb__param_0690, state_or_flags) == 0x14, "g1_layout_nrfx_spim_cb__param_0690.state_or_flags");
_Static_assert(offsetof(struct g1_layout_nrfx_spim_cb__param_0690, abort_flag) == 0x500, "g1_layout_nrfx_spim_cb__param_0690.abort_flag");
_Static_assert(sizeof(struct g1_layout_nrfx_spim_cb__param_0690) >= 0x504, "g1_layout_nrfx_spim_cb__param_0690.size");

/* param_0692 | library | libmetal I/O region descriptor, param_1 of metal_io_init (a LIBRARY function): physmap/size/page_shift/page_mask/mem_flags followed by the embedded metal_io_ops table. | D1+D2 verified
 * review: Split from global_1152 collision (that one is ver_str). Verified against metal/io.h: virt@0x0 (unobserved/padded), physmap@0x4, size@0x8, page_shift@0xc, page_mask@0x10, mem_flags@0x14, then struct metal_io_ops ops@0x18-0x34. All 13 observed offsets line up. Corrected sonnet's off-by-one field naming (it labeled 0x4 as virt). */
struct __attribute__((packed)) g1_layout_metal_io_region__param_0692 {
    uint8_t _pad_0x0[0x4];
    uint8_t physmap[0x4]; /* catalog type: const void *; SDK member: physmap */
    uint8_t size[0x4]; /* catalog type: size_t; SDK member: size */
    uint8_t page_shift[0x4]; /* catalog type: unsigned long; SDK member: page_shift */
    uint8_t page_mask[0x4]; /* catalog type: uint32_t; SDK member: page_mask */
    uint8_t mem_flags[0x4]; /* catalog type: unsigned int; SDK member: mem_flags */
    uint8_t ops_0[0x4]; /* catalog type: void *; SDK member: ops */
    uint8_t ops_1[0x4]; /* catalog type: void *; SDK member: ops */
    uint8_t ops_2[0x4]; /* catalog type: void *; SDK member: ops */
    uint8_t ops_3[0x4]; /* catalog type: void *; SDK member: ops */
    uint8_t ops_4[0x4]; /* catalog type: void *; SDK member: ops */
    uint8_t ops_5[0x4]; /* catalog type: void *; SDK member: ops */
    uint8_t ops_6[0x4]; /* catalog type: void *; SDK member: ops */
    uint8_t ops_context[0x4]; /* catalog type: void *; SDK member: ops.context */
};
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, physmap) == 0x4, "g1_layout_metal_io_region__param_0692.physmap");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, size) == 0x8, "g1_layout_metal_io_region__param_0692.size");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, page_shift) == 0xc, "g1_layout_metal_io_region__param_0692.page_shift");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, page_mask) == 0x10, "g1_layout_metal_io_region__param_0692.page_mask");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, mem_flags) == 0x14, "g1_layout_metal_io_region__param_0692.mem_flags");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, ops_0) == 0x18, "g1_layout_metal_io_region__param_0692.ops_0");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, ops_1) == 0x1c, "g1_layout_metal_io_region__param_0692.ops_1");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, ops_2) == 0x20, "g1_layout_metal_io_region__param_0692.ops_2");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, ops_3) == 0x24, "g1_layout_metal_io_region__param_0692.ops_3");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, ops_4) == 0x28, "g1_layout_metal_io_region__param_0692.ops_4");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, ops_5) == 0x2c, "g1_layout_metal_io_region__param_0692.ops_5");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, ops_6) == 0x30, "g1_layout_metal_io_region__param_0692.ops_6");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0692, ops_context) == 0x34, "g1_layout_metal_io_region__param_0692.ops_context");
_Static_assert(sizeof(struct g1_layout_metal_io_region__param_0692) >= 0x38, "g1_layout_metal_io_region__param_0692.size");

/* param_0693 | library | libmetal I/O operations table (param_7 = const struct metal_io_ops *ops) passed to metal_io_init. | D1+D2 verified
 * review: SPLIT from collision group global_1358. CORRECTED sonnet: member is metal_io_init as param_7, which is the ops table pointer (const struct metal_io_ops*), NOT the metal_io_region (that is param_1). Function-pointer members do not match the generic idx4 word footprint, so library_verified=false. */
struct __attribute__((packed)) g1_layout_metal_io_ops__param_0693 {
    uint8_t _pad_0x0[0x4];
    uint8_t ops_field_0x4[0x4]; /* catalog type: void * */
    uint8_t ops_field_0x8[0x4]; /* catalog type: void * */
    uint8_t ops_field_0xc[0x4]; /* catalog type: void * */
    uint8_t ops_field_0x10[0x4]; /* catalog type: void * */
    uint8_t ops_field_0x14[0x4]; /* catalog type: void * */
    uint8_t ops_field_0x18[0x4]; /* catalog type: void * */
    uint8_t ops_field_0x1c[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_metal_io_ops__param_0693, ops_field_0x4) == 0x4, "g1_layout_metal_io_ops__param_0693.ops_field_0x4");
_Static_assert(offsetof(struct g1_layout_metal_io_ops__param_0693, ops_field_0x8) == 0x8, "g1_layout_metal_io_ops__param_0693.ops_field_0x8");
_Static_assert(offsetof(struct g1_layout_metal_io_ops__param_0693, ops_field_0xc) == 0xc, "g1_layout_metal_io_ops__param_0693.ops_field_0xc");
_Static_assert(offsetof(struct g1_layout_metal_io_ops__param_0693, ops_field_0x10) == 0x10, "g1_layout_metal_io_ops__param_0693.ops_field_0x10");
_Static_assert(offsetof(struct g1_layout_metal_io_ops__param_0693, ops_field_0x14) == 0x14, "g1_layout_metal_io_ops__param_0693.ops_field_0x14");
_Static_assert(offsetof(struct g1_layout_metal_io_ops__param_0693, ops_field_0x18) == 0x18, "g1_layout_metal_io_ops__param_0693.ops_field_0x18");
_Static_assert(offsetof(struct g1_layout_metal_io_ops__param_0693, ops_field_0x1c) == 0x1c, "g1_layout_metal_io_ops__param_0693.ops_field_0x1c");
_Static_assert(sizeof(struct g1_layout_metal_io_ops__param_0693) >= 0x20, "g1_layout_metal_io_ops__param_0693.size");

/* param_0695 | library | libmetal I/O region descriptor used by metal_io_block_read (virt base ptr, size, ops fn ptr). | D1+D2 verified
 * review: LIBRARY-class (libmetal/OpenAMP), not in pinned Zephyr tree, unverified. field_0x0 (virt) is code-typed due to indirect-call use. */
struct __attribute__((packed)) g1_layout_metal_io_region__param_0695 {
    uint8_t virt[0x4]; /* catalog type: void * */
    uint8_t _pad_0x4[0x4];
    uint8_t size[0x4]; /* catalog type: size_t */
    uint8_t _pad_0xc[0x14];
    uint8_t ops_fn[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0695, virt) == 0x0, "g1_layout_metal_io_region__param_0695.virt");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0695, size) == 0x8, "g1_layout_metal_io_region__param_0695.size");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0695, ops_fn) == 0x20, "g1_layout_metal_io_region__param_0695.ops_fn");
_Static_assert(sizeof(struct g1_layout_metal_io_region__param_0695) >= 0x24, "g1_layout_metal_io_region__param_0695.size");

/* param_0697 | library | libmetal I/O region descriptor passed to metal_io_block_write (ops/vtable ptr, size, mem flags). | D1+D2 verified
 * review: libmetal header not opened; 0x0/0x8/0x24 sparse fields unverifiable. verified=false. */
struct __attribute__((packed)) g1_layout_metal_io_region__param_0697 {
    uint8_t ops_or_vtable[0x4]; /* catalog type: void * */
    uint8_t _pad_0x4[0x4];
    uint8_t size[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x18];
    uint8_t mem_flags[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0697, ops_or_vtable) == 0x0, "g1_layout_metal_io_region__param_0697.ops_or_vtable");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0697, size) == 0x8, "g1_layout_metal_io_region__param_0697.size");
_Static_assert(offsetof(struct g1_layout_metal_io_region__param_0697, mem_flags) == 0x24, "g1_layout_metal_io_region__param_0697.mem_flags");
_Static_assert(sizeof(struct g1_layout_metal_io_region__param_0697) >= 0x28, "g1_layout_metal_io_region__param_0697.size");

/* param_0698 | G1-original | param_1 of FUN_000855e6: G1 context/config with four leading words plus a pointer at 0x30. | D1+D2 verified
 * review: Single-cid; caller unnamed. */
struct __attribute__((packed)) g1_layout_task_ctx_generic__param_0698 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: int32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x14[0x1c];
    uint8_t field_0x30[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_task_ctx_generic__param_0698, field_0x4) == 0x4, "g1_layout_task_ctx_generic__param_0698.field_0x4");
_Static_assert(offsetof(struct g1_layout_task_ctx_generic__param_0698, field_0x8) == 0x8, "g1_layout_task_ctx_generic__param_0698.field_0x8");
_Static_assert(offsetof(struct g1_layout_task_ctx_generic__param_0698, field_0xc) == 0xc, "g1_layout_task_ctx_generic__param_0698.field_0xc");
_Static_assert(offsetof(struct g1_layout_task_ctx_generic__param_0698, field_0x10) == 0x10, "g1_layout_task_ctx_generic__param_0698.field_0x10");
_Static_assert(offsetof(struct g1_layout_task_ctx_generic__param_0698, field_0x30) == 0x30, "g1_layout_task_ctx_generic__param_0698.field_0x30");
_Static_assert(sizeof(struct g1_layout_task_ctx_generic__param_0698) >= 0x34, "g1_layout_task_ctx_generic__param_0698.size");

/* param_0699 | library | OpenAMP/virtio virtqueue object built by virtqueue_create (param_7): queue index/device ptr plus a run of ring/descriptor-table configuration words. | D1+D2 verified
 * review: OpenAMP virtqueue plausible; is_union=true (width-2 write at 0x9 overlaps 0xa). Not offset-verified against a pinned OpenAMP header, so library_verified=false. */
struct __attribute__((packed)) g1_layout_virtqueue__param_0699 {
    uint8_t _pad_0x0[0x2];
    uint8_t vq_queue_index[0x2]; /* catalog type: uint16_t */
    uint8_t vq_dev_ptr[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x1];
    uint8_t vq_nentries[0x1]; /* catalog type: uint16_t */
    uint8_t field_0xa[0x2]; /* catalog type: uint16_t */
    uint8_t vq_ring_desc[0x4]; /* catalog type: uint32_t */
    uint8_t vq_ring_avail[0x4]; /* catalog type: uint32_t */
    uint8_t vq_ring_used[0x4]; /* catalog type: uint32_t */
    uint8_t vq_free_head[0x4]; /* catalog type: uint32_t */
    uint8_t vq_num_free[0x4]; /* catalog type: uint32_t */
    uint8_t vq_callback[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0699, vq_queue_index) == 0x2, "g1_layout_virtqueue__param_0699.vq_queue_index");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0699, vq_dev_ptr) == 0x4, "g1_layout_virtqueue__param_0699.vq_dev_ptr");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0699, vq_nentries) == 0x9, "g1_layout_virtqueue__param_0699.vq_nentries");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0699, field_0xa) == 0xa, "g1_layout_virtqueue__param_0699.field_0xa");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0699, vq_ring_desc) == 0xc, "g1_layout_virtqueue__param_0699.vq_ring_desc");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0699, vq_ring_avail) == 0x10, "g1_layout_virtqueue__param_0699.vq_ring_avail");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0699, vq_ring_used) == 0x14, "g1_layout_virtqueue__param_0699.vq_ring_used");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0699, vq_free_head) == 0x18, "g1_layout_virtqueue__param_0699.vq_free_head");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0699, vq_num_free) == 0x1c, "g1_layout_virtqueue__param_0699.vq_num_free");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0699, vq_callback) == 0x20, "g1_layout_virtqueue__param_0699.vq_callback");
_Static_assert(sizeof(struct g1_layout_virtqueue__param_0699) >= 0x24, "g1_layout_virtqueue__param_0699.size");

/* param_0700 | library | Small descriptor consumed by virtqueue_create (OpenAMP/virtio-style virtqueue setup): a num/id short at 0x2 and a flags/addr word at 0x4. | D1+D2 verified
 * review: OpenAMP virtqueue arg; no pinned header located to verify. library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_virtqueue_desc_info__param_0700 {
    uint8_t _pad_0x0[0x2];
    uint8_t num_or_id[0x2]; /* catalog type: uint16_t */
    uint8_t flags_or_addr[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_virtqueue_desc_info__param_0700, num_or_id) == 0x2, "g1_layout_virtqueue_desc_info__param_0700.num_or_id");
_Static_assert(offsetof(struct g1_layout_virtqueue_desc_info__param_0700, flags_or_addr) == 0x4, "g1_layout_virtqueue_desc_info__param_0700.flags_or_addr");
_Static_assert(sizeof(struct g1_layout_virtqueue_desc_info__param_0700) >= 0x8, "g1_layout_virtqueue_desc_info__param_0700.size");

/* param_0701 | library | OpenAMP/virtio virtqueue passed to virtqueue_add_buffer (ring size, descriptor table pointer, free/avail indices). | D1+D2 verified
 * review: struct virtqueue (OpenAMP) id kept; member offsets not verified against openamp headers. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_virtqueue__param_0701 {
    uint8_t _pad_0x0[0xa];
    uint8_t vq_nentries[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xc[0xc];
    uint8_t field_0x18[0x4]; /* catalog type: int32_t */
    uint8_t field_0x1c[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x20[0x4];
    uint8_t vq_free_head[0x2]; /* catalog type: uint16_t */
    uint8_t vq_num_free[0x2]; /* catalog type: uint16_t */
    uint8_t desc_table[0x4]; /* catalog type: void * */
    uint8_t field_0x2c[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0701, vq_nentries) == 0xa, "g1_layout_virtqueue__param_0701.vq_nentries");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0701, field_0x18) == 0x18, "g1_layout_virtqueue__param_0701.field_0x18");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0701, field_0x1c) == 0x1c, "g1_layout_virtqueue__param_0701.field_0x1c");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0701, vq_free_head) == 0x24, "g1_layout_virtqueue__param_0701.vq_free_head");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0701, vq_num_free) == 0x26, "g1_layout_virtqueue__param_0701.vq_num_free");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0701, desc_table) == 0x28, "g1_layout_virtqueue__param_0701.desc_table");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0701, field_0x2c) == 0x2c, "g1_layout_virtqueue__param_0701.field_0x2c");
_Static_assert(sizeof(struct g1_layout_virtqueue__param_0701) >= 0x30, "g1_layout_virtqueue__param_0701.size");

/* param_0702 | library | OpenAMP/libmetal virtqueue instance read by virtqueue_get_buffer: queue index, nentries, free count, and avail/used ring indices. | D1+D2 verified
 * review: Strong identity from callee and field pattern (vq_queue_index u16, vq_nentries, vq_free_cnt, ring avail/used indices). Offsets not header-verified. */
struct __attribute__((packed)) g1_layout_virtqueue__param_0702 {
    uint8_t _pad_0x0[0xa];
    uint8_t vq_queue_index[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xc[0xc];
    uint8_t vq_nentries[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x1c[0x4];
    uint8_t vq_free_cnt[0x4]; /* catalog type: int32_t */
    uint8_t vq_ring_avail_idx[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x26[0x6];
    uint8_t vq_ring_used_idx[0x2]; /* catalog type: uint16_t */
    uint8_t vq_queued_cnt[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0702, vq_queue_index) == 0xa, "g1_layout_virtqueue__param_0702.vq_queue_index");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0702, vq_nentries) == 0x18, "g1_layout_virtqueue__param_0702.vq_nentries");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0702, vq_free_cnt) == 0x20, "g1_layout_virtqueue__param_0702.vq_free_cnt");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0702, vq_ring_avail_idx) == 0x24, "g1_layout_virtqueue__param_0702.vq_ring_avail_idx");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0702, vq_ring_used_idx) == 0x2c, "g1_layout_virtqueue__param_0702.vq_ring_used_idx");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0702, vq_queued_cnt) == 0x2e, "g1_layout_virtqueue__param_0702.vq_queued_cnt");
_Static_assert(sizeof(struct g1_layout_virtqueue__param_0702) >= 0x32, "g1_layout_virtqueue__param_0702.size");

/* param_0704 | library | virtio/OpenAMP vring (virtqueue ring) memory layout used by virtqueue_ring_setup_flags: flags, idx, desc/avail pointers, element count. | D1+D2 verified
 * review: Downgraded confidence: accessor implies a virtio vring, but the observed offsets (flags@0,idx@0xa,...) do not cleanly match struct vring {num,desc,avail,used}; likely the in-memory avail/used ring region. Kept naming, offsets unchanged; library_verified=false. */
struct __attribute__((packed)) g1_layout_vring_layout__param_0704 {
    uint8_t flags[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x8];
    uint8_t idx[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0xc[0x8];
    uint8_t desc_or_ptr[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x4];
    uint8_t avail_or_ptr[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x20[0xe];
    uint8_t num[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_vring_layout__param_0704, flags) == 0x0, "g1_layout_vring_layout__param_0704.flags");
_Static_assert(offsetof(struct g1_layout_vring_layout__param_0704, idx) == 0xa, "g1_layout_vring_layout__param_0704.idx");
_Static_assert(offsetof(struct g1_layout_vring_layout__param_0704, desc_or_ptr) == 0x14, "g1_layout_vring_layout__param_0704.desc_or_ptr");
_Static_assert(offsetof(struct g1_layout_vring_layout__param_0704, avail_or_ptr) == 0x1c, "g1_layout_vring_layout__param_0704.avail_or_ptr");
_Static_assert(offsetof(struct g1_layout_vring_layout__param_0704, num) == 0x2e, "g1_layout_vring_layout__param_0704.num");
_Static_assert(sizeof(struct g1_layout_vring_layout__param_0704) >= 0x32, "g1_layout_vring_layout__param_0704.size");

/* param_0705 | G1-original | DMA transfer descriptor handled by dma_xfer_end_handler (leading callback/opcode word plus several state words). | D1+D2 verified
 * review: 0x0 read as both code-ptr and ushort; kept offsets. */
struct __attribute__((packed)) g1_layout_dma_xfer_desc__param_0705 {
    uint8_t cb_or_opcode[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0xc];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x18[0x4];
    uint8_t field_0x1c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x24[0x2];
    uint8_t field_0x26[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_dma_xfer_desc__param_0705, cb_or_opcode) == 0x0, "g1_layout_dma_xfer_desc__param_0705.cb_or_opcode");
_Static_assert(offsetof(struct g1_layout_dma_xfer_desc__param_0705, field_0x10) == 0x10, "g1_layout_dma_xfer_desc__param_0705.field_0x10");
_Static_assert(offsetof(struct g1_layout_dma_xfer_desc__param_0705, field_0x14) == 0x14, "g1_layout_dma_xfer_desc__param_0705.field_0x14");
_Static_assert(offsetof(struct g1_layout_dma_xfer_desc__param_0705, field_0x1c) == 0x1c, "g1_layout_dma_xfer_desc__param_0705.field_0x1c");
_Static_assert(offsetof(struct g1_layout_dma_xfer_desc__param_0705, field_0x20) == 0x20, "g1_layout_dma_xfer_desc__param_0705.field_0x20");
_Static_assert(offsetof(struct g1_layout_dma_xfer_desc__param_0705, field_0x26) == 0x26, "g1_layout_dma_xfer_desc__param_0705.field_0x26");
_Static_assert(sizeof(struct g1_layout_dma_xfer_desc__param_0705) >= 0x2a, "g1_layout_dma_xfer_desc__param_0705.size");

/* param_0711 | G1-original | G1-original context passed as param_2 to unnamed FUN_00085a04; two adjacent word fields. | D1+D2 verified
 * review: G1-original, unnamed caller; kept generic naming. */
struct __attribute__((packed)) g1_layout_unk_ctx_0711__param_0711 {
    uint8_t _pad_0x0[0x20];
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x24[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_unk_ctx_0711__param_0711, field_0x20) == 0x20, "g1_layout_unk_ctx_0711__param_0711.field_0x20");
_Static_assert(offsetof(struct g1_layout_unk_ctx_0711__param_0711, field_0x24) == 0x24, "g1_layout_unk_ctx_0711__param_0711.field_0x24");
_Static_assert(sizeof(struct g1_layout_unk_ctx_0711__param_0711) >= 0x28, "g1_layout_unk_ctx_0711__param_0711.size");

/* param_0712 | library | OpenAMP/virtio virtqueue whose tail fields (free count, last-used index) are read by virtqueue_return_rx_buffer. | D1+D2 verified
 * review: OpenAMP virtqueue; only 0xa0/0xa4 observed, not header-verified. */
struct __attribute__((packed)) g1_layout_virtqueue__param_0712 {
    uint8_t _pad_0x0[0xa0];
    uint8_t vq_free_cnt[0x4]; /* catalog type: uint32_t */
    uint8_t vq_last_used_idx[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0712, vq_free_cnt) == 0xa0, "g1_layout_virtqueue__param_0712.vq_free_cnt");
_Static_assert(offsetof(struct g1_layout_virtqueue__param_0712, vq_last_used_idx) == 0xa4, "g1_layout_virtqueue__param_0712.vq_last_used_idx");
_Static_assert(sizeof(struct g1_layout_virtqueue__param_0712) >= 0xa8, "g1_layout_virtqueue__param_0712.size");

/* param_0713 | library | OpenAMP rpmsg_virtio shared-memory pool descriptor (base + size) initialized by rpmsg_virtio_init_shm_pool. | D1+D2 verified
 * review: OpenAMP header not opened; 0x4/0x8 unverifiable. Standard struct has {void* base; size_t avail; size_t size} — observed only two fields. verified=false. */
struct __attribute__((packed)) g1_layout_rpmsg_virtio_shm_pool__param_0713 {
    uint8_t _pad_0x0[0x4];
    uint8_t base[0x4]; /* catalog type: void * */
    uint8_t size[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_rpmsg_virtio_shm_pool__param_0713, base) == 0x4, "g1_layout_rpmsg_virtio_shm_pool__param_0713.base");
_Static_assert(offsetof(struct g1_layout_rpmsg_virtio_shm_pool__param_0713, size) == 0x8, "g1_layout_rpmsg_virtio_shm_pool__param_0713.size");
_Static_assert(sizeof(struct g1_layout_rpmsg_virtio_shm_pool__param_0713) >= 0xc, "g1_layout_rpmsg_virtio_shm_pool__param_0713.size");

/* param_0714 | library | param_1 of rpmsg_deinit_vdev: OpenAMP rpmsg virtio device torn down; two adjacent words at 0xa4/0xa8 (vring/vdev handles). | D1+D2 verified
 * review: Same OpenAMP type family as param_0397 but a different, non-overlapping partial view (0xa4/0xa8 vs 0x94-0xb4) and a different function; kept SEPARATE since neither can be offset-verified to confirm identity. */
struct __attribute__((packed)) g1_layout_rpmsg_virtio_device__param_0714 {
    uint8_t _pad_0x0[0xa4];
    uint8_t field_0xa4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xa8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_rpmsg_virtio_device__param_0714, field_0xa4) == 0xa4, "g1_layout_rpmsg_virtio_device__param_0714.field_0xa4");
_Static_assert(offsetof(struct g1_layout_rpmsg_virtio_device__param_0714, field_0xa8) == 0xa8, "g1_layout_rpmsg_virtio_device__param_0714.field_0xa8");
_Static_assert(sizeof(struct g1_layout_rpmsg_virtio_device__param_0714) >= 0xac, "g1_layout_rpmsg_virtio_device__param_0714.size");

/* param_0715 | library | CBOR decoder cursor/state object checked by cbor_decoder_at_end for end-of-buffer: remaining-bytes word and a type/flags byte. | D1+D2 verified
 * review: CBOR decoder state plausible; not matched to a specific pinned header, so library_verified=false. */
struct __attribute__((packed)) g1_layout_cbor_decoder_state__param_0715 {
    uint8_t _pad_0x0[0xc];
    uint8_t remaining[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_cbor_decoder_state__param_0715, remaining) == 0xc, "g1_layout_cbor_decoder_state__param_0715.remaining");
_Static_assert(offsetof(struct g1_layout_cbor_decoder_state__param_0715, field_0x10) == 0x10, "g1_layout_cbor_decoder_state__param_0715.field_0x10");
_Static_assert(sizeof(struct g1_layout_cbor_decoder_state__param_0715) >= 0x14, "g1_layout_cbor_decoder_state__param_0715.size");

/* param_0716 | library | zcbor CBOR encode/decode state threaded through the cbor_decode_* /zcbor_* helper chain: payload pointer, payload_end/backup, elem_count, indefinite-length flags, error/constant-state bytes, backup/tag count. | D1+D2 verified
 * review: 12 cbor_decode_* members strongly indicate zcbor_state_t; its layout uses bitfields (payload_end, elem_count, flags) so exact offsets were not byte-verified. Ground-truth shows a 1/4-byte overlap at 0x4 → is_union=true. library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_zcbor_state_t__param_0716 {
    uint8_t payload[0x4]; /* catalog type: const uint8_t * */
    uint8_t payload_end_or_bak[0x4]; /* catalog type: uint32_t */
    uint8_t elem_count[0x4]; /* catalog type: uint32_t */
    uint8_t indefinite_length_array[0x4]; /* catalog type: uint32_t */
    uint8_t error_or_flag[0x1]; /* catalog type: uint8_t */
    uint8_t constant_state_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x12[0x2];
    uint8_t backup_count_or_tag[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0716, payload) == 0x0, "g1_layout_zcbor_state_t__param_0716.payload");
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0716, payload_end_or_bak) == 0x4, "g1_layout_zcbor_state_t__param_0716.payload_end_or_bak");
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0716, elem_count) == 0x8, "g1_layout_zcbor_state_t__param_0716.elem_count");
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0716, indefinite_length_array) == 0xc, "g1_layout_zcbor_state_t__param_0716.indefinite_length_array");
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0716, error_or_flag) == 0x10, "g1_layout_zcbor_state_t__param_0716.error_or_flag");
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0716, constant_state_flag) == 0x11, "g1_layout_zcbor_state_t__param_0716.constant_state_flag");
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0716, backup_count_or_tag) == 0x14, "g1_layout_zcbor_state_t__param_0716.backup_count_or_tag");
_Static_assert(sizeof(struct g1_layout_zcbor_state_t__param_0716) >= 0x18, "g1_layout_zcbor_state_t__param_0716.size");

/* param_0717 | G1-original | Buffer-pool freelist descriptor initialized by buffer_pool_freelist_init (head pointer, block size, counts). | D1+D2 verified
 * review: G1-original; offsets unchanged. */
struct __attribute__((packed)) g1_layout_buffer_pool_freelist__param_0717 {
    uint8_t free_head[0x4]; /* catalog type: void * */
    uint8_t block_size[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x6[0x2];
    uint8_t block_count[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x4];
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_buffer_pool_freelist__param_0717, free_head) == 0x0, "g1_layout_buffer_pool_freelist__param_0717.free_head");
_Static_assert(offsetof(struct g1_layout_buffer_pool_freelist__param_0717, block_size) == 0x4, "g1_layout_buffer_pool_freelist__param_0717.block_size");
_Static_assert(offsetof(struct g1_layout_buffer_pool_freelist__param_0717, block_count) == 0x8, "g1_layout_buffer_pool_freelist__param_0717.block_count");
_Static_assert(offsetof(struct g1_layout_buffer_pool_freelist__param_0717, field_0xc) == 0xc, "g1_layout_buffer_pool_freelist__param_0717.field_0xc");
_Static_assert(offsetof(struct g1_layout_buffer_pool_freelist__param_0717, field_0x14) == 0x14, "g1_layout_buffer_pool_freelist__param_0717.field_0x14");
_Static_assert(sizeof(struct g1_layout_buffer_pool_freelist__param_0717) >= 0x18, "g1_layout_buffer_pool_freelist__param_0717.size");

/* param_0718 | library | CBOR decoder cursor/value object examined by cbor_decode_is_break (param_1). | D1+D2 verified
 * review: Application-class callee; CborValue-style cursor. Byte@0x4 is likely the dereferenced byte at the payload pointer, remaining@0x8, packed type/flags@0xc. Offsets not header-verified. */
struct __attribute__((packed)) g1_layout_cbor_value__param_0718 {
    uint8_t _pad_0x0[0x4];
    uint8_t cur_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x5[0x3];
    uint8_t remaining[0x4]; /* catalog type: uint32_t */
    uint8_t extra_type_flags[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cbor_value__param_0718, cur_byte) == 0x4, "g1_layout_cbor_value__param_0718.cur_byte");
_Static_assert(offsetof(struct g1_layout_cbor_value__param_0718, remaining) == 0x8, "g1_layout_cbor_value__param_0718.remaining");
_Static_assert(offsetof(struct g1_layout_cbor_value__param_0718, extra_type_flags) == 0xc, "g1_layout_cbor_value__param_0718.extra_type_flags");
_Static_assert(sizeof(struct g1_layout_cbor_value__param_0718) >= 0x10, "g1_layout_cbor_value__param_0718.size");

/* param_0719 | library | zcbor CBOR decoder state checked for exhaustion by cbor_decode_is_exhausted. | D1+D2 verified
 * review: Verified against zcbor_common.h zcbor_state_t: payload@0, payload_bak@4, elem_count@8, payload_end@0xc, indefinite_length_array(bool)@0x10, payload_moved@0x11, constant_state@0x14. Observed 0xc=payload_end and 0x10=indefinite_length_array match exactly. Refined sonnet's generic names. */
struct __attribute__((packed)) g1_layout_zcbor_state_t__param_0719 {
    uint8_t _pad_0x0[0xc];
    uint8_t payload_end[0x4]; /* catalog type: uint8_t const*; SDK member: payload_end */
    uint8_t indefinite_length_array[0x4]; /* catalog type: bool; SDK member: indefinite_length_array */
};
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0719, payload_end) == 0xc, "g1_layout_zcbor_state_t__param_0719.payload_end");
_Static_assert(offsetof(struct g1_layout_zcbor_state_t__param_0719, indefinite_length_array) == 0x10, "g1_layout_zcbor_state_t__param_0719.indefinite_length_array");
_Static_assert(sizeof(struct g1_layout_zcbor_state_t__param_0719) >= 0x14, "g1_layout_zcbor_state_t__param_0719.size");

/* param_0721 | G1-original | CBOR encoder state checked by cbor_encode_check_ok (count/offset int + error/status byte). | D1+D2 verified
 * review: Function is G1-classed (library hint G1-original); may wrap zcbor_state_t but not confirmed. Marked is_library=false. Kept offsets. */
struct __attribute__((packed)) g1_layout_cbor_encode_state__param_0721 {
    uint8_t _pad_0x0[0xc];
    uint8_t remaining_or_offset[0x4]; /* catalog type: int32_t */
    uint8_t error_or_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_cbor_encode_state__param_0721, remaining_or_offset) == 0xc, "g1_layout_cbor_encode_state__param_0721.remaining_or_offset");
_Static_assert(offsetof(struct g1_layout_cbor_encode_state__param_0721, error_or_flag) == 0x10, "g1_layout_cbor_encode_state__param_0721.error_or_flag");
_Static_assert(sizeof(struct g1_layout_cbor_encode_state__param_0721) >= 0x14, "g1_layout_cbor_encode_state__param_0721.size");

/* param_0724 | G1-original | Heap descriptor initialized by g1_recon_k_heap_init: backing-memory pointer and byte size (k_heap/sys_heap init args). | D1+D2 verified
 * review: Ground-truth hint is G1-original; only the two init args (mem ptr @0xc, size @0x10) are touched, not a full k_heap layout. Corrected sonnet is_library=True to False (it is a G1 init wrapper, not the stock struct itself). */
struct __attribute__((packed)) g1_layout_k_heap_init_ctx__param_0724 {
    uint8_t _pad_0x0[0xc];
    uint8_t init_mem[0x4]; /* catalog type: void * */
    uint8_t init_bytes[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_k_heap_init_ctx__param_0724, init_mem) == 0xc, "g1_layout_k_heap_init_ctx__param_0724.init_mem");
_Static_assert(offsetof(struct g1_layout_k_heap_init_ctx__param_0724, init_bytes) == 0x10, "g1_layout_k_heap_init_ctx__param_0724.init_bytes");
_Static_assert(sizeof(struct g1_layout_k_heap_init_ctx__param_0724) >= 0x14, "g1_layout_k_heap_init_ctx__param_0724.size");

/* param_0725 | library | Zephyr message queue control block initialized by k_msgq_init / z_impl_k_msgq_alloc_init. | D1+D2 verified
 * review: VERIFIED against struct k_msgq under a CONFIG_SPIN_VALIDATE (4B k_spinlock) + CONFIG_POLL build: wait_q@0x0, lock@0x8, msg_size@0xc, max_msgs@0x10, buffer_start@0x14, buffer_end@0x18, read_ptr@0x1c, write_ptr@0x20, used_msgs@0x24, poll_events@0x28, flags@0x30 all match exactly. CORRECTED sonnet, which shifted every field up by starting lock at 0x0. */
struct __attribute__((packed)) g1_layout_k_msgq__param_0725 {
    uint8_t wait_q[0x4]; /* catalog type: _wait_q_t; SDK member: wait_q */
    uint8_t _pad_0x4[0x4];
    uint8_t lock[0x4]; /* catalog type: struct k_spinlock; SDK member: lock */
    uint8_t msg_size[0x4]; /* catalog type: size_t; SDK member: msg_size */
    uint8_t max_msgs[0x4]; /* catalog type: uint32_t; SDK member: max_msgs */
    uint8_t buffer_start[0x4]; /* catalog type: char *; SDK member: buffer_start */
    uint8_t buffer_end[0x4]; /* catalog type: char *; SDK member: buffer_end */
    uint8_t read_ptr[0x4]; /* catalog type: char *; SDK member: read_ptr */
    uint8_t write_ptr[0x4]; /* catalog type: char *; SDK member: write_ptr */
    uint8_t used_msgs[0x4]; /* catalog type: uint32_t; SDK member: used_msgs */
    uint8_t poll_events[0x4]; /* catalog type: sys_dlist_t; SDK member: poll_events */
    uint8_t poll_events_tail[0x4]; /* catalog type: sys_dnode_t; SDK member: poll_events */
    uint8_t flags[0x1]; /* catalog type: uint8_t; SDK member: flags */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0725, wait_q) == 0x0, "g1_layout_k_msgq__param_0725.wait_q");
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0725, lock) == 0x8, "g1_layout_k_msgq__param_0725.lock");
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0725, msg_size) == 0xc, "g1_layout_k_msgq__param_0725.msg_size");
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0725, max_msgs) == 0x10, "g1_layout_k_msgq__param_0725.max_msgs");
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0725, buffer_start) == 0x14, "g1_layout_k_msgq__param_0725.buffer_start");
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0725, buffer_end) == 0x18, "g1_layout_k_msgq__param_0725.buffer_end");
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0725, read_ptr) == 0x1c, "g1_layout_k_msgq__param_0725.read_ptr");
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0725, write_ptr) == 0x20, "g1_layout_k_msgq__param_0725.write_ptr");
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0725, used_msgs) == 0x24, "g1_layout_k_msgq__param_0725.used_msgs");
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0725, poll_events) == 0x28, "g1_layout_k_msgq__param_0725.poll_events");
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0725, poll_events_tail) == 0x2c, "g1_layout_k_msgq__param_0725.poll_events_tail");
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0725, flags) == 0x30, "g1_layout_k_msgq__param_0725.flags");
_Static_assert(sizeof(struct g1_layout_k_msgq__param_0725) >= 0x34, "g1_layout_k_msgq__param_0725.size");

/* param_0726 | library | Zephyr message queue cleaned up by k_msgq_cleanup. | D1+D2 verified
 * review: Checked kernel.h k_msgq {_wait_q_t wait_q(8); k_spinlock lock(0, empty on non-SMP); size_t msg_size@0x8; uint32 max_msgs@0xc; char* buffer_start@0x10; char* buffer_end@0x14; ...; uint32 used_msgs@0x20}. Observed 0x14 matches buffer_end; but the observed byte rw @0xc lands inside max_msgs (uint32), which k_msgq_cleanup does not naturally byte-access — so mapping is inconsistent and verified=false. Identification kept. */
struct __attribute__((packed)) g1_layout_k_msgq__param_0726 {
    uint8_t _pad_0x0[0xc];
    uint8_t field_0xc[0x1]; /* catalog type: uint8_t; SDK member: max_msgs */
    uint8_t _pad_0xd[0x7];
    uint8_t buffer_end[0x4]; /* catalog type: char *; SDK member: buffer_end */
};
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0726, field_0xc) == 0xc, "g1_layout_k_msgq__param_0726.field_0xc");
_Static_assert(offsetof(struct g1_layout_k_msgq__param_0726, buffer_end) == 0x14, "g1_layout_k_msgq__param_0726.buffer_end");
_Static_assert(sizeof(struct g1_layout_k_msgq__param_0726) >= 0x18, "g1_layout_k_msgq__param_0726.size");

/* param_0728 | G1-original | Doubly-linked-list node with mutex bookkeeping initialized by kmutex_dlist_init (next/prev link pointers + lock-count/owner words). | D1+D2 verified
 * review: SPLIT from footprint group param_0728: this 4-word signature coincidentally matched four unrelated stack locals; kept separate. Kept offsets; refined field names. */
struct __attribute__((packed)) g1_layout_kmutex_dlist_node__param_0728 {
    uint8_t next[0x4]; /* catalog type: void * */
    uint8_t prev[0x4]; /* catalog type: void * */
    uint8_t lock_count[0x4]; /* catalog type: uint32_t */
    uint8_t owner[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_kmutex_dlist_node__param_0728, next) == 0x0, "g1_layout_kmutex_dlist_node__param_0728.next");
_Static_assert(offsetof(struct g1_layout_kmutex_dlist_node__param_0728, prev) == 0x4, "g1_layout_kmutex_dlist_node__param_0728.prev");
_Static_assert(offsetof(struct g1_layout_kmutex_dlist_node__param_0728, lock_count) == 0x8, "g1_layout_kmutex_dlist_node__param_0728.lock_count");
_Static_assert(offsetof(struct g1_layout_kmutex_dlist_node__param_0728, owner) == 0xc, "g1_layout_kmutex_dlist_node__param_0728.owner");
_Static_assert(sizeof(struct g1_layout_kmutex_dlist_node__param_0728) >= 0x10, "g1_layout_kmutex_dlist_node__param_0728.size");

/* param_0730 | library | Zephyr k_queue kernel object initialized by z_impl_k_queue_init: sflist data_q, spinlock, wait_q, and poll-event list. | D1+D2 verified
 * review: SPLIT from param_0033 collision group and identified as real k_queue. Offsets line up: data_q(sys_sflist_t) head@0x0(unobserved)/tail@0x4, k_spinlock is zero-size, wait_q@0x8-0xf, _POLL_EVENT poll_events@0x10-0x17; 0x18 is the trailing trace-tracking word. */
struct __attribute__((packed)) g1_layout_k_queue__param_0730 {
    uint8_t _pad_0x0[0x4];
    uint8_t data_q_tail[0x4]; /* catalog type: void*; SDK member: data_q.tail */
    uint8_t wait_q_head[0x4]; /* catalog type: void*; SDK member: wait_q.waitq.head */
    uint8_t wait_q_tail[0x4]; /* catalog type: void*; SDK member: wait_q.waitq.tail */
    uint8_t poll_events_head[0x4]; /* catalog type: void*; SDK member: poll_events.head */
    uint8_t poll_events_tail[0x4]; /* catalog type: void*; SDK member: poll_events.tail */
    uint8_t trace_field[0x4]; /* catalog type: uint32_t; SDK member: _track_next (SYS_PORT_TRACING) */
};
_Static_assert(offsetof(struct g1_layout_k_queue__param_0730, data_q_tail) == 0x4, "g1_layout_k_queue__param_0730.data_q_tail");
_Static_assert(offsetof(struct g1_layout_k_queue__param_0730, wait_q_head) == 0x8, "g1_layout_k_queue__param_0730.wait_q_head");
_Static_assert(offsetof(struct g1_layout_k_queue__param_0730, wait_q_tail) == 0xc, "g1_layout_k_queue__param_0730.wait_q_tail");
_Static_assert(offsetof(struct g1_layout_k_queue__param_0730, poll_events_head) == 0x10, "g1_layout_k_queue__param_0730.poll_events_head");
_Static_assert(offsetof(struct g1_layout_k_queue__param_0730, poll_events_tail) == 0x14, "g1_layout_k_queue__param_0730.poll_events_tail");
_Static_assert(offsetof(struct g1_layout_k_queue__param_0730, trace_field) == 0x18, "g1_layout_k_queue__param_0730.trace_field");
_Static_assert(sizeof(struct g1_layout_k_queue__param_0730) >= 0x1c, "g1_layout_k_queue__param_0730.size");

/* param_0731 | library | Zephyr kernel semaphore object initialized by z_impl_k_sem_init: wait queue, current count, max limit, and CONFIG_POLL event list. | D1+D2 verified
 * review: Split out of the param_0023 footprint-collision group. Verified against kernel.h struct k_sem: _wait_q_t wait_q (sys_dlist head/tail) @0x0/0x4, count @0x8, limit @0xc, _POLL_EVENT (sys_dlist head/tail) @0x10/0x14 — all offsets match exactly. */
struct __attribute__((packed)) g1_layout_k_sem__param_0731 {
    uint8_t wait_q_head[0x4]; /* catalog type: void *; SDK member: wait_q */
    uint8_t wait_q_tail[0x4]; /* catalog type: void *; SDK member: wait_q */
    uint8_t count[0x4]; /* catalog type: unsigned int; SDK member: count */
    uint8_t limit[0x4]; /* catalog type: unsigned int; SDK member: limit */
    uint8_t poll_events_head[0x4]; /* catalog type: void *; SDK member: poll_events */
    uint8_t poll_events_tail[0x4]; /* catalog type: void *; SDK member: poll_events */
};
_Static_assert(offsetof(struct g1_layout_k_sem__param_0731, wait_q_head) == 0x0, "g1_layout_k_sem__param_0731.wait_q_head");
_Static_assert(offsetof(struct g1_layout_k_sem__param_0731, wait_q_tail) == 0x4, "g1_layout_k_sem__param_0731.wait_q_tail");
_Static_assert(offsetof(struct g1_layout_k_sem__param_0731, count) == 0x8, "g1_layout_k_sem__param_0731.count");
_Static_assert(offsetof(struct g1_layout_k_sem__param_0731, limit) == 0xc, "g1_layout_k_sem__param_0731.limit");
_Static_assert(offsetof(struct g1_layout_k_sem__param_0731, poll_events_head) == 0x10, "g1_layout_k_sem__param_0731.poll_events_head");
_Static_assert(offsetof(struct g1_layout_k_sem__param_0731, poll_events_tail) == 0x14, "g1_layout_k_sem__param_0731.poll_events_tail");
_Static_assert(sizeof(struct g1_layout_k_sem__param_0731) >= 0x18, "g1_layout_k_sem__param_0731.size");

/* param_0734 | library | Zephyr circular doubly-linked list head initialized by sys_dlist_init (head/tail == next/prev pointers). | D1+D2 verified
 * review: Verified against sys/dlist.h: struct _dnode { union{head,next}@0; union{tail,prev}@4 }. Observed two writes at 0x0/0x4 match sys_dlist_init. is_union set because each member is a head/next (and tail/prev) union in the header. */
struct __attribute__((packed)) g1_layout_sys_dlist_t__param_0734 {
    uint8_t head_next[0x4]; /* catalog type: struct _dnode *; SDK member: head/next */
    uint8_t tail_prev[0x4]; /* catalog type: struct _dnode *; SDK member: tail/prev */
};
_Static_assert(offsetof(struct g1_layout_sys_dlist_t__param_0734, head_next) == 0x0, "g1_layout_sys_dlist_t__param_0734.head_next");
_Static_assert(offsetof(struct g1_layout_sys_dlist_t__param_0734, tail_prev) == 0x4, "g1_layout_sys_dlist_t__param_0734.tail_prev");
_Static_assert(sizeof(struct g1_layout_sys_dlist_t__param_0734) >= 0x8, "g1_layout_sys_dlist_t__param_0734.size");

/* param_0736 | library | Zephyr k_timer object initialized by k_timer_init: wait-queue, expiry/stop function pointers, status, and user-data. | D1+D2 verified
 * review: VERIFIED against kernel.h (CONFIG_TIMEOUT_64BIT=y). k_timer{timeout@0, wait_q(sys_dlist head@18/tail@1c), expiry_fn@20, stop_fn@24, period@28, status@30, user_data@34}. CORRECTED sonnet, which was shifted by one slot (it called 0x18=expiry_fn etc.): 0x18/0x1c are wait_q head/tail, 0x20=expiry_fn, 0x24=stop_fn, 0x30=status, 0x34=user_data. */
struct __attribute__((packed)) g1_layout_k_timer__param_0736 {
    uint8_t _pad_0x0[0x4];
    uint8_t timeout_node_prev[0x4]; /* catalog type: void *; SDK member: timeout.node.prev */
    uint8_t _pad_0x8[0x10];
    uint8_t wait_q_head[0x4]; /* catalog type: void *; SDK member: wait_q.waitq.head */
    uint8_t wait_q_tail[0x4]; /* catalog type: void *; SDK member: wait_q.waitq.tail */
    uint8_t expiry_fn[0x4]; /* catalog type: void *; SDK member: expiry_fn */
    uint8_t stop_fn[0x4]; /* catalog type: void *; SDK member: stop_fn */
    uint8_t _pad_0x28[0x8];
    uint8_t status[0x4]; /* catalog type: uint32_t; SDK member: status */
    uint8_t user_data[0x4]; /* catalog type: void *; SDK member: user_data */
};
_Static_assert(offsetof(struct g1_layout_k_timer__param_0736, timeout_node_prev) == 0x4, "g1_layout_k_timer__param_0736.timeout_node_prev");
_Static_assert(offsetof(struct g1_layout_k_timer__param_0736, wait_q_head) == 0x18, "g1_layout_k_timer__param_0736.wait_q_head");
_Static_assert(offsetof(struct g1_layout_k_timer__param_0736, wait_q_tail) == 0x1c, "g1_layout_k_timer__param_0736.wait_q_tail");
_Static_assert(offsetof(struct g1_layout_k_timer__param_0736, expiry_fn) == 0x20, "g1_layout_k_timer__param_0736.expiry_fn");
_Static_assert(offsetof(struct g1_layout_k_timer__param_0736, stop_fn) == 0x24, "g1_layout_k_timer__param_0736.stop_fn");
_Static_assert(offsetof(struct g1_layout_k_timer__param_0736, status) == 0x30, "g1_layout_k_timer__param_0736.status");
_Static_assert(offsetof(struct g1_layout_k_timer__param_0736, user_data) == 0x34, "g1_layout_k_timer__param_0736.user_data");
_Static_assert(sizeof(struct g1_layout_k_timer__param_0736) >= 0x38, "g1_layout_k_timer__param_0736.size");

/* param_0739 | library | Zephyr k_poll event object used by signal_poll_event: a poller/obj pointer at 0x8 and a state/result word at 0xc. | D1+D2 verified
 * review: Plausible k_poll_event (poller@0x8, bitfield type/state/mode word@0xc; obj is actually at 0x10, not observed). Not byte-verified against kernel.h; library_verified=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_k_poll_event__param_0739 {
    uint8_t _pad_0x0[0x8];
    uint8_t poller_or_obj[0x4]; /* catalog type: void * */
    uint8_t state_word[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_k_poll_event__param_0739, poller_or_obj) == 0x8, "g1_layout_k_poll_event__param_0739.poller_or_obj");
_Static_assert(offsetof(struct g1_layout_k_poll_event__param_0739, state_word) == 0xc, "g1_layout_k_poll_event__param_0739.state_word");
_Static_assert(sizeof(struct g1_layout_k_poll_event__param_0739) >= 0x10, "g1_layout_k_poll_event__param_0739.size");

/* param_0740 | library | Zephyr kernel poll-signal object initialized by z_impl_k_poll_signal_init. | D1+D2 verified
 * review: Verified against kernel.h: init writes sys_dlist_init(&poll_events) -> head@0x0, tail@0x4, then signaled@0x8. Observed 0x0/0x4/0x8 writes match exactly (result@0xc set but beyond captured size). */
struct __attribute__((packed)) g1_layout_k_poll_signal__param_0740 {
    uint8_t poll_events_head[0x4]; /* catalog type: void *; SDK member: poll_events.head */
    uint8_t poll_events_tail[0x4]; /* catalog type: void *; SDK member: poll_events.tail */
    uint8_t signaled[0x4]; /* catalog type: uint32_t; SDK member: signaled */
};
_Static_assert(offsetof(struct g1_layout_k_poll_signal__param_0740, poll_events_head) == 0x0, "g1_layout_k_poll_signal__param_0740.poll_events_head");
_Static_assert(offsetof(struct g1_layout_k_poll_signal__param_0740, poll_events_tail) == 0x4, "g1_layout_k_poll_signal__param_0740.poll_events_tail");
_Static_assert(offsetof(struct g1_layout_k_poll_signal__param_0740, signaled) == 0x8, "g1_layout_k_poll_signal__param_0740.signaled");
_Static_assert(sizeof(struct g1_layout_k_poll_signal__param_0740) >= 0xc, "g1_layout_k_poll_signal__param_0740.size");

/* param_0741 | G1-original | itoa-with-signed-exponent formatting context/buffer used by itoa_signed_exponent (param_1). | D1+D2 verified
 * review: G1-original formatting helper; three idx4 words. */
struct __attribute__((packed)) g1_layout_itoa_ctx__param_0741 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_itoa_ctx__param_0741, field_0x4) == 0x4, "g1_layout_itoa_ctx__param_0741.field_0x4");
_Static_assert(offsetof(struct g1_layout_itoa_ctx__param_0741, field_0x8) == 0x8, "g1_layout_itoa_ctx__param_0741.field_0x8");
_Static_assert(offsetof(struct g1_layout_itoa_ctx__param_0741, field_0xc) == 0xc, "g1_layout_itoa_ctx__param_0741.field_0xc");
_Static_assert(sizeof(struct g1_layout_itoa_ctx__param_0741) >= 0x10, "g1_layout_itoa_ctx__param_0741.size");

/* param_0742 | library | C library FILE-like stream whose flag/state ushort fields are accessed by libc_stream_write_syscall. | D1+D2 verified
 * review: Kept naming; offsets unchanged. picolibc FILE flag layout not header-verifiable; library_verified=false. */
struct __attribute__((packed)) g1_layout_libc_FILE_stream__param_0742 {
    uint8_t _pad_0x0[0xc];
    uint8_t flags[0x2]; /* catalog type: uint16_t */
    uint8_t unget_or_state[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_libc_FILE_stream__param_0742, flags) == 0xc, "g1_layout_libc_FILE_stream__param_0742.flags");
_Static_assert(offsetof(struct g1_layout_libc_FILE_stream__param_0742, unget_or_state) == 0xe, "g1_layout_libc_FILE_stream__param_0742.unget_or_state");
_Static_assert(sizeof(struct g1_layout_libc_FILE_stream__param_0742) >= 0x10, "g1_layout_libc_FILE_stream__param_0742.size");

/* param_0743 | library | Zephyr GATT subscription context in gatt_sub_resolve_handle (value/ccc handle pair + trailing result word). | D1+D2 verified
 * review: Per gatt.h, value_handle@0xc(u16) and ccc_handle@0xe(u16) match observed 0xc/0xe — corrected sonnet's start_handle/end_handle labels. 0x54 lies beyond the core members and could not be mapped, so verified=false. */
struct __attribute__((packed)) g1_layout_bt_gatt_subscribe_params__param_0743 {
    uint8_t _pad_0x0[0xc];
    uint8_t value_handle[0x2]; /* catalog type: uint16_t; SDK member: value_handle */
    uint8_t ccc_handle[0x2]; /* catalog type: uint16_t; SDK member: ccc_handle */
    uint8_t _pad_0x10[0x44];
    uint8_t resolve_result[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_subscribe_params__param_0743, value_handle) == 0xc, "g1_layout_bt_gatt_subscribe_params__param_0743.value_handle");
_Static_assert(offsetof(struct g1_layout_bt_gatt_subscribe_params__param_0743, ccc_handle) == 0xe, "g1_layout_bt_gatt_subscribe_params__param_0743.ccc_handle");
_Static_assert(offsetof(struct g1_layout_bt_gatt_subscribe_params__param_0743, resolve_result) == 0x54, "g1_layout_bt_gatt_subscribe_params__param_0743.resolve_result");
_Static_assert(sizeof(struct g1_layout_bt_gatt_subscribe_params__param_0743) >= 0x58, "g1_layout_bt_gatt_subscribe_params__param_0743.size");

/* param_0745 | G1-original | mbedTLS bignum (mpi) limb data accessed by bignum_shift_right_bits: two adjacent 32-bit limbs during a right-shift. | D1+D2 verified
 * review: Ground-truth hint is G1-original and the access is just two adjacent limb words, not the mbedtls_mpi header struct (which is {sign, n, limbs*}). Corrected sonnet is_library=True to False; this is a limb buffer view. */
struct __attribute__((packed)) g1_layout_mbedtls_mpi_limbs__param_0745 {
    uint8_t _pad_0x0[0x10];
    uint8_t limb_n[0x4]; /* catalog type: uint32_t */
    uint8_t limb_n_plus_1[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_mbedtls_mpi_limbs__param_0745, limb_n) == 0x10, "g1_layout_mbedtls_mpi_limbs__param_0745.limb_n");
_Static_assert(offsetof(struct g1_layout_mbedtls_mpi_limbs__param_0745, limb_n_plus_1) == 0x14, "g1_layout_mbedtls_mpi_limbs__param_0745.limb_n_plus_1");
_Static_assert(sizeof(struct g1_layout_mbedtls_mpi_limbs__param_0745) >= 0x18, "g1_layout_mbedtls_mpi_limbs__param_0745.size");

/* param_0749 | library | picolibc/newlib FILE stream whose ungetc buffer is reset by stdio_reset_ungetc_buffer. | D1+D2 verified
 * review: picolibc FILE; 0x3 is a 2-byte flags access overlapping the prior byte region (union/bitfield). Offsets not verified against the picolibc header. is_union for the 0x3 overlap. */
struct __attribute__((packed)) g1_layout_FILE__param_0749 {
    uint8_t _pad_0x0[0x3];
    uint8_t flags[0x1]; /* catalog type: uint16_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x8];
    uint8_t read_ptr[0x4]; /* catalog type: void * */
    uint8_t _pad_0x14[0x20];
    uint8_t field_0x34[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x38[0x4];
    uint8_t field_0x3c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x40[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_FILE__param_0749, flags) == 0x3, "g1_layout_FILE__param_0749.flags");
_Static_assert(offsetof(struct g1_layout_FILE__param_0749, field_0x4) == 0x4, "g1_layout_FILE__param_0749.field_0x4");
_Static_assert(offsetof(struct g1_layout_FILE__param_0749, read_ptr) == 0x10, "g1_layout_FILE__param_0749.read_ptr");
_Static_assert(offsetof(struct g1_layout_FILE__param_0749, field_0x34) == 0x34, "g1_layout_FILE__param_0749.field_0x34");
_Static_assert(offsetof(struct g1_layout_FILE__param_0749, field_0x3c) == 0x3c, "g1_layout_FILE__param_0749.field_0x3c");
_Static_assert(offsetof(struct g1_layout_FILE__param_0749, field_0x40) == 0x40, "g1_layout_FILE__param_0749.field_0x40");
_Static_assert(sizeof(struct g1_layout_FILE__param_0749) >= 0x44, "g1_layout_FILE__param_0749.size");

/* param_0750 | G1-original | G1-original growable byte buffer used by dynbuf_push_byte_grow (data ptr, len, cap). | D1+D2 verified
 * review: 0x44 accessed width 4 into gap 1 (overlaps 0x45/0x46) => is_union=true. Kept offsets verbatim. */
struct __attribute__((packed)) g1_layout_dynbuf_t__param_0750 {
    uint8_t _pad_0x0[0x34];
    uint8_t data[0x4]; /* catalog type: uint8_t * */
    uint8_t len[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x3c[0x8];
    uint8_t cap[0x1]; /* catalog type: uint32_t */
    uint8_t field_0x45[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x46[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_dynbuf_t__param_0750, data) == 0x34, "g1_layout_dynbuf_t__param_0750.data");
_Static_assert(offsetof(struct g1_layout_dynbuf_t__param_0750, len) == 0x38, "g1_layout_dynbuf_t__param_0750.len");
_Static_assert(offsetof(struct g1_layout_dynbuf_t__param_0750, cap) == 0x44, "g1_layout_dynbuf_t__param_0750.cap");
_Static_assert(offsetof(struct g1_layout_dynbuf_t__param_0750, field_0x45) == 0x45, "g1_layout_dynbuf_t__param_0750.field_0x45");
_Static_assert(offsetof(struct g1_layout_dynbuf_t__param_0750, field_0x46) == 0x46, "g1_layout_dynbuf_t__param_0750.field_0x46");
_Static_assert(sizeof(struct g1_layout_dynbuf_t__param_0750) >= 0x4a, "g1_layout_dynbuf_t__param_0750.size");

/* stack_0751 | G1-original | Stack local (local_258) in battery_model_state_update: intermediate battery-model sample bytes. | D1+D2 verified
 * review: Single-cid stack local. */
struct __attribute__((packed)) g1_layout_battery_model_sample__stack_0751 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x1[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x1];
    uint8_t field_0x4[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_battery_model_sample__stack_0751, field_0x0) == 0x0, "g1_layout_battery_model_sample__stack_0751.field_0x0");
_Static_assert(offsetof(struct g1_layout_battery_model_sample__stack_0751, field_0x1) == 0x1, "g1_layout_battery_model_sample__stack_0751.field_0x1");
_Static_assert(offsetof(struct g1_layout_battery_model_sample__stack_0751, field_0x2) == 0x2, "g1_layout_battery_model_sample__stack_0751.field_0x2");
_Static_assert(offsetof(struct g1_layout_battery_model_sample__stack_0751, field_0x4) == 0x4, "g1_layout_battery_model_sample__stack_0751.field_0x4");
_Static_assert(sizeof(struct g1_layout_battery_model_sample__stack_0751) >= 0x5, "g1_layout_battery_model_sample__stack_0751.size");

/* stack_0752 | G1-original | Stack-local temporary pair inside battery_model_state_update (intermediate SOC/voltage calculation results). | D1+D2 verified
 * review: G1-original function-local scratch (local_254); not a named library type. */
struct __attribute__((packed)) g1_layout_batt_soc_calc_tmp__stack_0752 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_batt_soc_calc_tmp__stack_0752, field_0x0) == 0x0, "g1_layout_batt_soc_calc_tmp__stack_0752.field_0x0");
_Static_assert(offsetof(struct g1_layout_batt_soc_calc_tmp__stack_0752, field_0x8) == 0x8, "g1_layout_batt_soc_calc_tmp__stack_0752.field_0x8");
_Static_assert(sizeof(struct g1_layout_batt_soc_calc_tmp__stack_0752) >= 0xc, "g1_layout_batt_soc_calc_tmp__stack_0752.size");

/* stack_0754 | G1-original | Stack-local scratch struct in battery_model_state_update holding intermediate SOC/curve calculation values. | D1+D2 verified
 * review: Single-cid stack local (not shared). Offsets kept. */
struct __attribute__((packed)) g1_layout_battery_model_update_locals__stack_0754 {
    uint8_t local_val0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x8];
    uint8_t local_val1[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0x8];
    uint8_t local_val2[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1c[0x14];
    uint8_t local_val3[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_battery_model_update_locals__stack_0754, local_val0) == 0x0, "g1_layout_battery_model_update_locals__stack_0754.local_val0");
_Static_assert(offsetof(struct g1_layout_battery_model_update_locals__stack_0754, local_val1) == 0xc, "g1_layout_battery_model_update_locals__stack_0754.local_val1");
_Static_assert(offsetof(struct g1_layout_battery_model_update_locals__stack_0754, local_val2) == 0x18, "g1_layout_battery_model_update_locals__stack_0754.local_val2");
_Static_assert(offsetof(struct g1_layout_battery_model_update_locals__stack_0754, local_val3) == 0x30, "g1_layout_battery_model_update_locals__stack_0754.local_val3");
_Static_assert(sizeof(struct g1_layout_battery_model_update_locals__stack_0754) >= 0x34, "g1_layout_battery_model_update_locals__stack_0754.size");

/* stack_0756 | G1-original | Stack-local working array of intermediate 32-bit readings in battery_model_state_update (local_200), read uniformly as idx4. | D1+D2 verified
 * review: Separated from param_0150: coincidental footprint collision with a library param object; this is a single-function stack local (battery_model_state_update). All 9 words read as idx4 -> treated as a uint32 array. */
struct __attribute__((packed)) g1_layout_battery_model_sample_buf__stack_0756 {
    uint8_t sample_0[0x4]; /* catalog type: uint32_t */
    uint8_t sample_1[0x4]; /* catalog type: uint32_t */
    uint8_t sample_2[0x4]; /* catalog type: uint32_t */
    uint8_t sample_3[0x4]; /* catalog type: uint32_t */
    uint8_t sample_4[0x4]; /* catalog type: uint32_t */
    uint8_t sample_5[0x4]; /* catalog type: uint32_t */
    uint8_t sample_6[0x4]; /* catalog type: uint32_t */
    uint8_t sample_7[0x4]; /* catalog type: uint32_t */
    uint8_t sample_8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_battery_model_sample_buf__stack_0756, sample_0) == 0x0, "g1_layout_battery_model_sample_buf__stack_0756.sample_0");
_Static_assert(offsetof(struct g1_layout_battery_model_sample_buf__stack_0756, sample_1) == 0x4, "g1_layout_battery_model_sample_buf__stack_0756.sample_1");
_Static_assert(offsetof(struct g1_layout_battery_model_sample_buf__stack_0756, sample_2) == 0x8, "g1_layout_battery_model_sample_buf__stack_0756.sample_2");
_Static_assert(offsetof(struct g1_layout_battery_model_sample_buf__stack_0756, sample_3) == 0xc, "g1_layout_battery_model_sample_buf__stack_0756.sample_3");
_Static_assert(offsetof(struct g1_layout_battery_model_sample_buf__stack_0756, sample_4) == 0x10, "g1_layout_battery_model_sample_buf__stack_0756.sample_4");
_Static_assert(offsetof(struct g1_layout_battery_model_sample_buf__stack_0756, sample_5) == 0x14, "g1_layout_battery_model_sample_buf__stack_0756.sample_5");
_Static_assert(offsetof(struct g1_layout_battery_model_sample_buf__stack_0756, sample_6) == 0x18, "g1_layout_battery_model_sample_buf__stack_0756.sample_6");
_Static_assert(offsetof(struct g1_layout_battery_model_sample_buf__stack_0756, sample_7) == 0x1c, "g1_layout_battery_model_sample_buf__stack_0756.sample_7");
_Static_assert(offsetof(struct g1_layout_battery_model_sample_buf__stack_0756, sample_8) == 0x20, "g1_layout_battery_model_sample_buf__stack_0756.sample_8");
_Static_assert(sizeof(struct g1_layout_battery_model_sample_buf__stack_0756) >= 0x24, "g1_layout_battery_model_sample_buf__stack_0756.size");

/* stack_0757 | G1-original | Stack scratch array of five uint32 read as idx4 inside battery_model_state_update (local_1e0). | D1+D2 verified
 * review: Footprint collision only: this generic 5x uint32 scratch shares a signature with 12 other unrelated stack locals; kept SEPARATE. Not merged. */
struct __attribute__((packed)) g1_layout_batt_model_calc_scratch5__stack_0757 {
    uint8_t v0[0x4]; /* catalog type: uint32_t */
    uint8_t v1[0x4]; /* catalog type: uint32_t */
    uint8_t v2[0x4]; /* catalog type: uint32_t */
    uint8_t v3[0x4]; /* catalog type: uint32_t */
    uint8_t v4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5__stack_0757, v0) == 0x0, "g1_layout_batt_model_calc_scratch5__stack_0757.v0");
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5__stack_0757, v1) == 0x4, "g1_layout_batt_model_calc_scratch5__stack_0757.v1");
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5__stack_0757, v2) == 0x8, "g1_layout_batt_model_calc_scratch5__stack_0757.v2");
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5__stack_0757, v3) == 0xc, "g1_layout_batt_model_calc_scratch5__stack_0757.v3");
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5__stack_0757, v4) == 0x10, "g1_layout_batt_model_calc_scratch5__stack_0757.v4");
_Static_assert(sizeof(struct g1_layout_batt_model_calc_scratch5__stack_0757) >= 0x14, "g1_layout_batt_model_calc_scratch5__stack_0757.size");

/* stack_0758 | G1-original | Stack-frame scratch (local_1d0) in battery_model_state_update: an initial reading and a final computed value. | D1+D2 verified
 * review: Function-local scratch; offsets unchanged. */
struct __attribute__((packed)) g1_layout_battery_calc_locals__stack_0758 {
    uint8_t initial_reading[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x14];
    uint8_t computed_value[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_battery_calc_locals__stack_0758, initial_reading) == 0x0, "g1_layout_battery_calc_locals__stack_0758.initial_reading");
_Static_assert(offsetof(struct g1_layout_battery_calc_locals__stack_0758, computed_value) == 0x18, "g1_layout_battery_calc_locals__stack_0758.computed_value");
_Static_assert(sizeof(struct g1_layout_battery_calc_locals__stack_0758) >= 0x1c, "g1_layout_battery_calc_locals__stack_0758.size");

/* stack_0759 | G1-original | Local pair of measurement values in battery_model_state_update (local_1b8). | D1+D2 verified
 * review: Stack local; two idx4 words at 0x0 and 0x18. */
struct __attribute__((packed)) g1_layout_batt_sample_pair__stack_0759 {
    uint8_t sample_a[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x4[0x14];
    uint8_t sample_b[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_batt_sample_pair__stack_0759, sample_a) == 0x0, "g1_layout_batt_sample_pair__stack_0759.sample_a");
_Static_assert(offsetof(struct g1_layout_batt_sample_pair__stack_0759, sample_b) == 0x18, "g1_layout_batt_sample_pair__stack_0759.sample_b");
_Static_assert(sizeof(struct g1_layout_batt_sample_pair__stack_0759) >= 0x1c, "g1_layout_batt_sample_pair__stack_0759.size");

/* stack_0760 | G1-original | Second 5x uint32 stack scratch in battery_model_state_update (local_1a0). | D1+D2 verified
 * review: Coincidental footprint match with stack_0757 group; distinct stack slot in same function. SEPARATE. */
struct __attribute__((packed)) g1_layout_batt_model_calc_scratch5_b__stack_0760 {
    uint8_t v0[0x4]; /* catalog type: uint32_t */
    uint8_t v1[0x4]; /* catalog type: uint32_t */
    uint8_t v2[0x4]; /* catalog type: uint32_t */
    uint8_t v3[0x4]; /* catalog type: uint32_t */
    uint8_t v4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5_b__stack_0760, v0) == 0x0, "g1_layout_batt_model_calc_scratch5_b__stack_0760.v0");
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5_b__stack_0760, v1) == 0x4, "g1_layout_batt_model_calc_scratch5_b__stack_0760.v1");
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5_b__stack_0760, v2) == 0x8, "g1_layout_batt_model_calc_scratch5_b__stack_0760.v2");
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5_b__stack_0760, v3) == 0xc, "g1_layout_batt_model_calc_scratch5_b__stack_0760.v3");
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5_b__stack_0760, v4) == 0x10, "g1_layout_batt_model_calc_scratch5_b__stack_0760.v4");
_Static_assert(sizeof(struct g1_layout_batt_model_calc_scratch5_b__stack_0760) >= 0x14, "g1_layout_batt_model_calc_scratch5_b__stack_0760.size");

/* stack_0761 | G1-original | Third 5x uint32 stack scratch in battery_model_state_update (local_190). | D1+D2 verified
 * review: Coincidental footprint match; distinct slot. SEPARATE. */
struct __attribute__((packed)) g1_layout_batt_model_calc_scratch5_c__stack_0761 {
    uint8_t v0[0x4]; /* catalog type: uint32_t */
    uint8_t v1[0x4]; /* catalog type: uint32_t */
    uint8_t v2[0x4]; /* catalog type: uint32_t */
    uint8_t v3[0x4]; /* catalog type: uint32_t */
    uint8_t v4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5_c__stack_0761, v0) == 0x0, "g1_layout_batt_model_calc_scratch5_c__stack_0761.v0");
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5_c__stack_0761, v1) == 0x4, "g1_layout_batt_model_calc_scratch5_c__stack_0761.v1");
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5_c__stack_0761, v2) == 0x8, "g1_layout_batt_model_calc_scratch5_c__stack_0761.v2");
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5_c__stack_0761, v3) == 0xc, "g1_layout_batt_model_calc_scratch5_c__stack_0761.v3");
_Static_assert(offsetof(struct g1_layout_batt_model_calc_scratch5_c__stack_0761, v4) == 0x10, "g1_layout_batt_model_calc_scratch5_c__stack_0761.v4");
_Static_assert(sizeof(struct g1_layout_batt_model_calc_scratch5_c__stack_0761) >= 0x14, "g1_layout_batt_model_calc_scratch5_c__stack_0761.size");

/* stack_0763 | G1-original | Stack-local scratch words in battery_model_state_update (OCV/current/resistance/SOC intermediates). | D1+D2 verified
 * review: Function-local frame; kept naming, offsets unchanged. */
struct __attribute__((packed)) g1_layout_batt_calc_locals__stack_0763 {
    uint8_t val_0[0x4]; /* catalog type: uint32_t */
    uint8_t val_1[0x4]; /* catalog type: uint32_t */
    uint8_t val_2[0x4]; /* catalog type: uint32_t */
    uint8_t val_3[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x10[0xc];
    uint8_t val_4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_batt_calc_locals__stack_0763, val_0) == 0x0, "g1_layout_batt_calc_locals__stack_0763.val_0");
_Static_assert(offsetof(struct g1_layout_batt_calc_locals__stack_0763, val_1) == 0x4, "g1_layout_batt_calc_locals__stack_0763.val_1");
_Static_assert(offsetof(struct g1_layout_batt_calc_locals__stack_0763, val_2) == 0x8, "g1_layout_batt_calc_locals__stack_0763.val_2");
_Static_assert(offsetof(struct g1_layout_batt_calc_locals__stack_0763, val_3) == 0xc, "g1_layout_batt_calc_locals__stack_0763.val_3");
_Static_assert(offsetof(struct g1_layout_batt_calc_locals__stack_0763, val_4) == 0x1c, "g1_layout_batt_calc_locals__stack_0763.val_4");
_Static_assert(sizeof(struct g1_layout_batt_calc_locals__stack_0763) >= 0x20, "g1_layout_batt_calc_locals__stack_0763.size");

/* stack_0776 | G1-original | Stack-local (soc_idx, value) pair (local_48) built while constructing the battery SOC curve table. | D1+D2 verified
 * review: Local scratch; kept offsets. */
struct __attribute__((packed)) g1_layout_soc_curve_point_local__stack_0776 {
    uint8_t soc_idx[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x8];
    uint8_t value[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_soc_curve_point_local__stack_0776, soc_idx) == 0x0, "g1_layout_soc_curve_point_local__stack_0776.soc_idx");
_Static_assert(offsetof(struct g1_layout_soc_curve_point_local__stack_0776, value) == 0xc, "g1_layout_soc_curve_point_local__stack_0776.value");
_Static_assert(sizeof(struct g1_layout_soc_curve_point_local__stack_0776) >= 0x10, "g1_layout_soc_curve_point_local__stack_0776.size");

/* stack_0778 | G1-original | Five control-point/coefficient words on stack in spline_interp_pair_2out (local_58). | D1+D2 verified
 * review: Unrelated function; footprint collision with battery/LC3 scratch. SEPARATE. */
struct __attribute__((packed)) g1_layout_spline_interp_scratch5__stack_0778 {
    uint8_t p0[0x4]; /* catalog type: uint32_t */
    uint8_t p1[0x4]; /* catalog type: uint32_t */
    uint8_t p2[0x4]; /* catalog type: uint32_t */
    uint8_t p3[0x4]; /* catalog type: uint32_t */
    uint8_t p4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_spline_interp_scratch5__stack_0778, p0) == 0x0, "g1_layout_spline_interp_scratch5__stack_0778.p0");
_Static_assert(offsetof(struct g1_layout_spline_interp_scratch5__stack_0778, p1) == 0x4, "g1_layout_spline_interp_scratch5__stack_0778.p1");
_Static_assert(offsetof(struct g1_layout_spline_interp_scratch5__stack_0778, p2) == 0x8, "g1_layout_spline_interp_scratch5__stack_0778.p2");
_Static_assert(offsetof(struct g1_layout_spline_interp_scratch5__stack_0778, p3) == 0xc, "g1_layout_spline_interp_scratch5__stack_0778.p3");
_Static_assert(offsetof(struct g1_layout_spline_interp_scratch5__stack_0778, p4) == 0x10, "g1_layout_spline_interp_scratch5__stack_0778.p4");
_Static_assert(sizeof(struct g1_layout_spline_interp_scratch5__stack_0778) >= 0x14, "g1_layout_spline_interp_scratch5__stack_0778.size");

/* stack_0782 | G1-original | Stack-local working array in imu_fusion_thread: 10 uniform 32-bit values (fused orientation/quaternion state or accel+gyro sample buffer). | D1+D2 verified
 * review: G1-original stack local; uniform idx4 array. Offsets kept. */
struct __attribute__((packed)) g1_layout_imu_fusion_state_vector__stack_0782 {
    uint8_t v0[0x4]; /* catalog type: uint32_t */
    uint8_t v1[0x4]; /* catalog type: uint32_t */
    uint8_t v2[0x4]; /* catalog type: uint32_t */
    uint8_t v3[0x4]; /* catalog type: uint32_t */
    uint8_t v4[0x4]; /* catalog type: uint32_t */
    uint8_t v5[0x4]; /* catalog type: uint32_t */
    uint8_t v6[0x4]; /* catalog type: uint32_t */
    uint8_t v7[0x4]; /* catalog type: uint32_t */
    uint8_t v8[0x4]; /* catalog type: uint32_t */
    uint8_t v9[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_imu_fusion_state_vector__stack_0782, v0) == 0x0, "g1_layout_imu_fusion_state_vector__stack_0782.v0");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state_vector__stack_0782, v1) == 0x4, "g1_layout_imu_fusion_state_vector__stack_0782.v1");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state_vector__stack_0782, v2) == 0x8, "g1_layout_imu_fusion_state_vector__stack_0782.v2");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state_vector__stack_0782, v3) == 0xc, "g1_layout_imu_fusion_state_vector__stack_0782.v3");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state_vector__stack_0782, v4) == 0x10, "g1_layout_imu_fusion_state_vector__stack_0782.v4");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state_vector__stack_0782, v5) == 0x14, "g1_layout_imu_fusion_state_vector__stack_0782.v5");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state_vector__stack_0782, v6) == 0x18, "g1_layout_imu_fusion_state_vector__stack_0782.v6");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state_vector__stack_0782, v7) == 0x1c, "g1_layout_imu_fusion_state_vector__stack_0782.v7");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state_vector__stack_0782, v8) == 0x20, "g1_layout_imu_fusion_state_vector__stack_0782.v8");
_Static_assert(offsetof(struct g1_layout_imu_fusion_state_vector__stack_0782, v9) == 0x24, "g1_layout_imu_fusion_state_vector__stack_0782.v9");
_Static_assert(sizeof(struct g1_layout_imu_fusion_state_vector__stack_0782) >= 0x28, "g1_layout_imu_fusion_state_vector__stack_0782.size");

/* stack_0783 | G1-original | Stack-local index/value pair in fuel_gauge_update (local_3c). | D1+D2 verified
 * review: G1-original single-function local. */
struct __attribute__((packed)) g1_layout_fuel_gauge_reading__stack_0783 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_fuel_gauge_reading__stack_0783, field_0x0) == 0x0, "g1_layout_fuel_gauge_reading__stack_0783.field_0x0");
_Static_assert(offsetof(struct g1_layout_fuel_gauge_reading__stack_0783, field_0x8) == 0x8, "g1_layout_fuel_gauge_reading__stack_0783.field_0x8");
_Static_assert(sizeof(struct g1_layout_fuel_gauge_reading__stack_0783) >= 0xc, "g1_layout_fuel_gauge_reading__stack_0783.size");

/* stack_0784 | G1-original | Compiler-generated local pair (pointer + counter) inside z_cbvprintf_impl formatting loop. | D1+D2 verified
 * review: Local scratch, not a stock struct; is_library corrected to false. 0x0 written as both short and ptr => is_union=true. */
struct __attribute__((packed)) g1_layout_cbvprintf_ptr_counter__stack_0784 {
    uint8_t ptr[0x4]; /* catalog type: void * */
    uint8_t counter[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cbvprintf_ptr_counter__stack_0784, ptr) == 0x0, "g1_layout_cbvprintf_ptr_counter__stack_0784.ptr");
_Static_assert(offsetof(struct g1_layout_cbvprintf_ptr_counter__stack_0784, counter) == 0x4, "g1_layout_cbvprintf_ptr_counter__stack_0784.counter");
_Static_assert(sizeof(struct g1_layout_cbvprintf_ptr_counter__stack_0784) >= 0x8, "g1_layout_cbvprintf_ptr_counter__stack_0784.size");

/* stack_0785 | library | Stack local (local_44) in z_cbvprintf_impl: internal scratch while walking a cbprintf package/varargs stream. | D1+D2 verified
 * review: Compiler-generated stack frame of a Zephyr fn; not a named public struct, unverified. */
struct __attribute__((packed)) g1_layout_cbvprintf_scratch__stack_0785 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x1[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x16];
    uint8_t field_0x19[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_cbvprintf_scratch__stack_0785, field_0x0) == 0x0, "g1_layout_cbvprintf_scratch__stack_0785.field_0x0");
_Static_assert(offsetof(struct g1_layout_cbvprintf_scratch__stack_0785, field_0x1) == 0x1, "g1_layout_cbvprintf_scratch__stack_0785.field_0x1");
_Static_assert(offsetof(struct g1_layout_cbvprintf_scratch__stack_0785, field_0x2) == 0x2, "g1_layout_cbvprintf_scratch__stack_0785.field_0x2");
_Static_assert(offsetof(struct g1_layout_cbvprintf_scratch__stack_0785, field_0x19) == 0x19, "g1_layout_cbvprintf_scratch__stack_0785.field_0x19");
_Static_assert(sizeof(struct g1_layout_cbvprintf_scratch__stack_0785) >= 0x1a, "g1_layout_cbvprintf_scratch__stack_0785.size");

/* stack_0790 | G1-original | Stack-local temporaries in hci_vs_init used to build a Bluetooth HCI vendor-specific command. | D1+D2 verified
 * review: Function-local scratch (local_30); the aggregate itself is not a stock struct, so is_library=false. */
struct __attribute__((packed)) g1_layout_hci_vs_init_locals__stack_0790 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0xc];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_hci_vs_init_locals__stack_0790, field_0x0) == 0x0, "g1_layout_hci_vs_init_locals__stack_0790.field_0x0");
_Static_assert(offsetof(struct g1_layout_hci_vs_init_locals__stack_0790, field_0x10) == 0x10, "g1_layout_hci_vs_init_locals__stack_0790.field_0x10");
_Static_assert(sizeof(struct g1_layout_hci_vs_init_locals__stack_0790) >= 0x14, "g1_layout_hci_vs_init_locals__stack_0790.size");

/* stack_0792 | G1-original | Stack-local scratch in dtoa_r holding intermediate double-to-ASCII conversion words (newlib). | D1+D2 verified
 * review: Anonymous local frame of newlib dtoa_r; not a named library struct, so is_library=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_dtoa_r_locals__stack_0792 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_dtoa_r_locals__stack_0792, field_0x0) == 0x0, "g1_layout_dtoa_r_locals__stack_0792.field_0x0");
_Static_assert(offsetof(struct g1_layout_dtoa_r_locals__stack_0792, field_0x8) == 0x8, "g1_layout_dtoa_r_locals__stack_0792.field_0x8");
_Static_assert(sizeof(struct g1_layout_dtoa_r_locals__stack_0792) >= 0xc, "g1_layout_dtoa_r_locals__stack_0792.size");

/* stack_0841 | G1-original | Stack-local ANCS notification frame parsed in ancs_notification_forward (notification UID + category/flags). | D1+D2 verified
 * review: Function-local; offsets unchanged. */
struct __attribute__((packed)) g1_layout_ancs_notify_frame__stack_0841 {
    uint8_t notif_uid[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t category_or_flags[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ancs_notify_frame__stack_0841, notif_uid) == 0x0, "g1_layout_ancs_notify_frame__stack_0841.notif_uid");
_Static_assert(offsetof(struct g1_layout_ancs_notify_frame__stack_0841, category_or_flags) == 0x8, "g1_layout_ancs_notify_frame__stack_0841.category_or_flags");
_Static_assert(sizeof(struct g1_layout_ancs_notify_frame__stack_0841) >= 0xc, "g1_layout_ancs_notify_frame__stack_0841.size");

/* stack_0842 | G1-original | Local ANCS message payload buffer in ancs_notification_forward (local_1b4): leading tag byte and trailing terminator across ~0x181 bytes. | D1+D2 verified
 * review: Stack local byte buffer; only first/last byte observed. */
struct __attribute__((packed)) g1_layout_ancs_notify_buf__stack_0842 {
    uint8_t msg_tag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x17f];
    uint8_t msg_terminator[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_ancs_notify_buf__stack_0842, msg_tag) == 0x0, "g1_layout_ancs_notify_buf__stack_0842.msg_tag");
_Static_assert(offsetof(struct g1_layout_ancs_notify_buf__stack_0842, msg_terminator) == 0x180, "g1_layout_ancs_notify_buf__stack_0842.msg_terminator");
_Static_assert(sizeof(struct g1_layout_ancs_notify_buf__stack_0842) >= 0x181, "g1_layout_ancs_notify_buf__stack_0842.size");

/* stack_0846 | G1-original | Stack-local formatting buffer in debug_print (~0xc9 bytes) used to build a debug message string. | D1+D2 verified
 * review: Function-local char buffer; only first and last accessed byte observed. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_debug_print_buf__stack_0846 {
    uint8_t buf_start[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0xc7];
    uint8_t buf_end[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_debug_print_buf__stack_0846, buf_start) == 0x0, "g1_layout_debug_print_buf__stack_0846.buf_start");
_Static_assert(offsetof(struct g1_layout_debug_print_buf__stack_0846, buf_end) == 0xc8, "g1_layout_debug_print_buf__stack_0846.buf_end");
_Static_assert(sizeof(struct g1_layout_debug_print_buf__stack_0846) >= 0xc9, "g1_layout_debug_print_buf__stack_0846.size");

/* stack_0848 | G1-original | Stack-local parsed header bytes (local_1fa) in ble_process_get_req (command/sub-id + later flag byte). | D1+D2 verified
 * review: Local scratch; kept offsets. */
struct __attribute__((packed)) g1_layout_ble_get_req_hdr_tmp__stack_0848 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t field_0x1[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x2[0x4];
    uint8_t field_0x6[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_ble_get_req_hdr_tmp__stack_0848, field_0x0) == 0x0, "g1_layout_ble_get_req_hdr_tmp__stack_0848.field_0x0");
_Static_assert(offsetof(struct g1_layout_ble_get_req_hdr_tmp__stack_0848, field_0x1) == 0x1, "g1_layout_ble_get_req_hdr_tmp__stack_0848.field_0x1");
_Static_assert(offsetof(struct g1_layout_ble_get_req_hdr_tmp__stack_0848, field_0x6) == 0x6, "g1_layout_ble_get_req_hdr_tmp__stack_0848.field_0x6");
_Static_assert(sizeof(struct g1_layout_ble_get_req_hdr_tmp__stack_0848) >= 0x7, "g1_layout_ble_get_req_hdr_tmp__stack_0848.size");

/* stack_0850 | G1-original | Stack-local response/parse buffer in ble_process_get_req with leading header byte and a trailing marker byte. | D1+D2 verified
 * review: G1-original stack buffer; only the two end markers of a ~0xf5 byte buffer are observed. */
struct __attribute__((packed)) g1_layout_ble_get_req_locals__stack_0850 {
    uint8_t header_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0xf3];
    uint8_t trailer_byte[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_ble_get_req_locals__stack_0850, header_byte) == 0x0, "g1_layout_ble_get_req_locals__stack_0850.header_byte");
_Static_assert(offsetof(struct g1_layout_ble_get_req_locals__stack_0850, trailer_byte) == 0xf4, "g1_layout_ble_get_req_locals__stack_0850.trailer_byte");
_Static_assert(sizeof(struct g1_layout_ble_get_req_locals__stack_0850) >= 0xf5, "g1_layout_ble_get_req_locals__stack_0850.size");

/* stack_0851 | G1-original | Stack scratch in build_status_notify_packet holding header/trailer bytes of an outgoing status-notify BLE packet. | D1+D2 verified
 * review: G1-original local. */
struct __attribute__((packed)) g1_layout_status_notify_packet_locals__stack_0851 {
    uint8_t packet_header_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x13];
    uint8_t packet_trailer_byte[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_status_notify_packet_locals__stack_0851, packet_header_byte) == 0x0, "g1_layout_status_notify_packet_locals__stack_0851.packet_header_byte");
_Static_assert(offsetof(struct g1_layout_status_notify_packet_locals__stack_0851, packet_trailer_byte) == 0x14, "g1_layout_status_notify_packet_locals__stack_0851.packet_trailer_byte");
_Static_assert(sizeof(struct g1_layout_status_notify_packet_locals__stack_0851) >= 0x15, "g1_layout_status_notify_packet_locals__stack_0851.size");

/* stack_0852 | G1-original | Local scratch in ble_process_req_dispatch: request-type byte + trailing status byte. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_ble_req_dispatch_locals__stack_0852 {
    uint8_t req_type[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0xf];
    uint8_t status[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_ble_req_dispatch_locals__stack_0852, req_type) == 0x0, "g1_layout_ble_req_dispatch_locals__stack_0852.req_type");
_Static_assert(offsetof(struct g1_layout_ble_req_dispatch_locals__stack_0852, status) == 0x10, "g1_layout_ble_req_dispatch_locals__stack_0852.status");
_Static_assert(sizeof(struct g1_layout_ble_req_dispatch_locals__stack_0852) >= 0x11, "g1_layout_ble_req_dispatch_locals__stack_0852.size");

/* stack_0860 | G1-original | Stack local (local_428) in calc_flash_crc: small header/index bytes plus a 0x400-byte streaming buffer with a trailing byte. | D1+D2 verified
 * review: Single-cid; large byte buffer -> is_array. */
struct __attribute__((packed)) g1_layout_crc_scratch_buffer__stack_0860 {
    uint8_t idx_b0[0x1]; /* catalog type: uint8_t */
    uint8_t idx_b1[0x1]; /* catalog type: uint8_t */
    uint8_t idx_b2[0x1]; /* catalog type: uint8_t */
    uint8_t idx_b3[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x4[0x400];
    uint8_t tail_byte[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_crc_scratch_buffer__stack_0860, idx_b0) == 0x0, "g1_layout_crc_scratch_buffer__stack_0860.idx_b0");
_Static_assert(offsetof(struct g1_layout_crc_scratch_buffer__stack_0860, idx_b1) == 0x1, "g1_layout_crc_scratch_buffer__stack_0860.idx_b1");
_Static_assert(offsetof(struct g1_layout_crc_scratch_buffer__stack_0860, idx_b2) == 0x2, "g1_layout_crc_scratch_buffer__stack_0860.idx_b2");
_Static_assert(offsetof(struct g1_layout_crc_scratch_buffer__stack_0860, idx_b3) == 0x3, "g1_layout_crc_scratch_buffer__stack_0860.idx_b3");
_Static_assert(offsetof(struct g1_layout_crc_scratch_buffer__stack_0860, tail_byte) == 0x404, "g1_layout_crc_scratch_buffer__stack_0860.tail_byte");
_Static_assert(sizeof(struct g1_layout_crc_scratch_buffer__stack_0860) >= 0x405, "g1_layout_crc_scratch_buffer__stack_0860.size");

/* stack_0864 | G1-original | Stack-local id/value staging pair inside load_sys_setting while reading a setting. | D1+D2 verified
 * review: G1-original function-local scratch (local_9c). */
struct __attribute__((packed)) g1_layout_settings_read_stage__stack_0864 {
    uint8_t field_0x0[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_settings_read_stage__stack_0864, field_0x0) == 0x0, "g1_layout_settings_read_stage__stack_0864.field_0x0");
_Static_assert(offsetof(struct g1_layout_settings_read_stage__stack_0864, field_0x8) == 0x8, "g1_layout_settings_read_stage__stack_0864.field_0x8");
_Static_assert(sizeof(struct g1_layout_settings_read_stage__stack_0864) >= 0xc, "g1_layout_settings_read_stage__stack_0864.size");

/* stack_0865 | G1-original | Stack-local key/value byte pair in load_sys_setting separated by a 15-byte name/scratch gap. | D1+D2 verified
 * review: Single-cid stack local. Offsets kept. */
struct __attribute__((packed)) g1_layout_load_sys_setting_locals__stack_0865 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0xf];
    uint8_t field_0x10[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_load_sys_setting_locals__stack_0865, field_0x0) == 0x0, "g1_layout_load_sys_setting_locals__stack_0865.field_0x0");
_Static_assert(offsetof(struct g1_layout_load_sys_setting_locals__stack_0865, field_0x10) == 0x10, "g1_layout_load_sys_setting_locals__stack_0865.field_0x10");
_Static_assert(sizeof(struct g1_layout_load_sys_setting_locals__stack_0865) >= 0x11, "g1_layout_load_sys_setting_locals__stack_0865.size");

/* stack_0867 | G1-original | Stack-local scratch (local_67) in load_sys_setting holding a leading key/status byte and a trailing result byte. | D1+D2 verified
 * review: Function-local; offsets unchanged. */
struct __attribute__((packed)) g1_layout_sys_setting_read_buf__stack_0867 {
    uint8_t lead_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0xf];
    uint8_t tail_byte[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_sys_setting_read_buf__stack_0867, lead_byte) == 0x0, "g1_layout_sys_setting_read_buf__stack_0867.lead_byte");
_Static_assert(offsetof(struct g1_layout_sys_setting_read_buf__stack_0867, tail_byte) == 0x10, "g1_layout_sys_setting_read_buf__stack_0867.tail_byte");
_Static_assert(sizeof(struct g1_layout_sys_setting_read_buf__stack_0867) >= 0x11, "g1_layout_sys_setting_read_buf__stack_0867.size");

/* stack_0870 | G1-original | Local temp holding a flash address/length pair in read_sys_settting_from_flash (local_94). | D1+D2 verified
 * review: Stack local; addr@0x0, len@0x8. */
struct __attribute__((packed)) g1_layout_flash_addr_len_tmp__stack_0870 {
    uint8_t flash_addr[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t read_len[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_flash_addr_len_tmp__stack_0870, flash_addr) == 0x0, "g1_layout_flash_addr_len_tmp__stack_0870.flash_addr");
_Static_assert(offsetof(struct g1_layout_flash_addr_len_tmp__stack_0870, read_len) == 0x8, "g1_layout_flash_addr_len_tmp__stack_0870.read_len");
_Static_assert(sizeof(struct g1_layout_flash_addr_len_tmp__stack_0870) >= 0xc, "g1_layout_flash_addr_len_tmp__stack_0870.size");

/* stack_0871 | G1-original | Stack-local scan-state byte pair (start/end id) in read_sys_settting_from_flash. | D1+D2 verified
 * review: Function-local; kept naming, offsets unchanged. */
struct __attribute__((packed)) g1_layout_sys_setting_scan_locals__stack_0871 {
    uint8_t start_id[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0xf];
    uint8_t end_id[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_sys_setting_scan_locals__stack_0871, start_id) == 0x0, "g1_layout_sys_setting_scan_locals__stack_0871.start_id");
_Static_assert(offsetof(struct g1_layout_sys_setting_scan_locals__stack_0871, end_id) == 0x10, "g1_layout_sys_setting_scan_locals__stack_0871.end_id");
_Static_assert(sizeof(struct g1_layout_sys_setting_scan_locals__stack_0871) >= 0x11, "g1_layout_sys_setting_scan_locals__stack_0871.size");

/* stack_0873 | G1-original | Stack-local settings record (local_5f) read by read_sys_settting_from_flash (leading key byte, value byte at +0x10). | D1+D2 verified
 * review: Local scratch; kept offsets. */
struct __attribute__((packed)) g1_layout_flash_setting_record_local__stack_0873 {
    uint8_t setting_key[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0xf];
    uint8_t setting_value[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_flash_setting_record_local__stack_0873, setting_key) == 0x0, "g1_layout_flash_setting_record_local__stack_0873.setting_key");
_Static_assert(offsetof(struct g1_layout_flash_setting_record_local__stack_0873, setting_value) == 0x10, "g1_layout_flash_setting_record_local__stack_0873.setting_value");
_Static_assert(sizeof(struct g1_layout_flash_setting_record_local__stack_0873) >= 0x11, "g1_layout_flash_setting_record_local__stack_0873.size");

/* stack_0887 | G1-original | Stack-local context in SettingStoreHandler: a key/type index byte and a status/result index byte. | D1+D2 verified
 * review: G1-original stack local; kept naming. */
struct __attribute__((packed)) g1_layout_setting_store_ctx__stack_0887 {
    uint8_t key_idx[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x3];
    uint8_t status_idx[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_setting_store_ctx__stack_0887, key_idx) == 0x0, "g1_layout_setting_store_ctx__stack_0887.key_idx");
_Static_assert(offsetof(struct g1_layout_setting_store_ctx__stack_0887, status_idx) == 0x4, "g1_layout_setting_store_ctx__stack_0887.status_idx");
_Static_assert(sizeof(struct g1_layout_setting_store_ctx__stack_0887) >= 0x5, "g1_layout_setting_store_ctx__stack_0887.size");

/* stack_0896 | G1-original | Five-word scratch used building NDEF records in st25dv_build_and_write_ndef_records (local_88). | D1+D2 verified
 * review: Unrelated NFC function; footprint collision. SEPARATE. */
struct __attribute__((packed)) g1_layout_ndef_build_scratch5__stack_0896 {
    uint8_t w0[0x4]; /* catalog type: uint32_t */
    uint8_t w1[0x4]; /* catalog type: uint32_t */
    uint8_t w2[0x4]; /* catalog type: uint32_t */
    uint8_t w3[0x4]; /* catalog type: uint32_t */
    uint8_t w4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ndef_build_scratch5__stack_0896, w0) == 0x0, "g1_layout_ndef_build_scratch5__stack_0896.w0");
_Static_assert(offsetof(struct g1_layout_ndef_build_scratch5__stack_0896, w1) == 0x4, "g1_layout_ndef_build_scratch5__stack_0896.w1");
_Static_assert(offsetof(struct g1_layout_ndef_build_scratch5__stack_0896, w2) == 0x8, "g1_layout_ndef_build_scratch5__stack_0896.w2");
_Static_assert(offsetof(struct g1_layout_ndef_build_scratch5__stack_0896, w3) == 0xc, "g1_layout_ndef_build_scratch5__stack_0896.w3");
_Static_assert(offsetof(struct g1_layout_ndef_build_scratch5__stack_0896, w4) == 0x10, "g1_layout_ndef_build_scratch5__stack_0896.w4");
_Static_assert(sizeof(struct g1_layout_ndef_build_scratch5__stack_0896) >= 0x14, "g1_layout_ndef_build_scratch5__stack_0896.size");

/* stack_0897 | G1-original | Stack scratch buffer in st25dv_build_and_write_ndef_records used to assemble NFC NDEF record fields before writing to the ST25DV tag. | D1+D2 verified
 * review: G1-original local; contiguous idx4 words -> array-like. */
struct __attribute__((packed)) g1_layout_ndef_record_scratch__stack_0897 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x18[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x1c[0x38];
    uint8_t field_0x54[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ndef_record_scratch__stack_0897, field_0x0) == 0x0, "g1_layout_ndef_record_scratch__stack_0897.field_0x0");
_Static_assert(offsetof(struct g1_layout_ndef_record_scratch__stack_0897, field_0x4) == 0x4, "g1_layout_ndef_record_scratch__stack_0897.field_0x4");
_Static_assert(offsetof(struct g1_layout_ndef_record_scratch__stack_0897, field_0x8) == 0x8, "g1_layout_ndef_record_scratch__stack_0897.field_0x8");
_Static_assert(offsetof(struct g1_layout_ndef_record_scratch__stack_0897, field_0xc) == 0xc, "g1_layout_ndef_record_scratch__stack_0897.field_0xc");
_Static_assert(offsetof(struct g1_layout_ndef_record_scratch__stack_0897, field_0x10) == 0x10, "g1_layout_ndef_record_scratch__stack_0897.field_0x10");
_Static_assert(offsetof(struct g1_layout_ndef_record_scratch__stack_0897, field_0x14) == 0x14, "g1_layout_ndef_record_scratch__stack_0897.field_0x14");
_Static_assert(offsetof(struct g1_layout_ndef_record_scratch__stack_0897, field_0x18) == 0x18, "g1_layout_ndef_record_scratch__stack_0897.field_0x18");
_Static_assert(offsetof(struct g1_layout_ndef_record_scratch__stack_0897, field_0x54) == 0x54, "g1_layout_ndef_record_scratch__stack_0897.field_0x54");
_Static_assert(sizeof(struct g1_layout_ndef_record_scratch__stack_0897) >= 0x58, "g1_layout_ndef_record_scratch__stack_0897.size");

/* stack_0900 | G1-original | Length-prefixed IPC packet header built on stack by ipc_send_len_prefixed_packet (length + type). | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_len_prefixed_pkt_hdr__stack_0900 {
    uint8_t length[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x2];
    uint8_t type[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_len_prefixed_pkt_hdr__stack_0900, length) == 0x0, "g1_layout_len_prefixed_pkt_hdr__stack_0900.length");
_Static_assert(offsetof(struct g1_layout_len_prefixed_pkt_hdr__stack_0900, type) == 0x4, "g1_layout_len_prefixed_pkt_hdr__stack_0900.type");
_Static_assert(sizeof(struct g1_layout_len_prefixed_pkt_hdr__stack_0900) >= 0x6, "g1_layout_len_prefixed_pkt_hdr__stack_0900.size");

/* stack_0910 | G1-original | Stack local (local_2c) in process_for_new_task: two related index/id words. | D1+D2 verified
 * review: Single-cid stack local. */
struct __attribute__((packed)) g1_layout_new_task_locals__stack_0910 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_new_task_locals__stack_0910, field_0x0) == 0x0, "g1_layout_new_task_locals__stack_0910.field_0x0");
_Static_assert(offsetof(struct g1_layout_new_task_locals__stack_0910, field_0x8) == 0x8, "g1_layout_new_task_locals__stack_0910.field_0x8");
_Static_assert(sizeof(struct g1_layout_new_task_locals__stack_0910) >= 0xc, "g1_layout_new_task_locals__stack_0910.size");

/* stack_0911 | G1-original | Stack-local scratch bytes in opt3001_reg_read for the I2C register/value pair of an OPT3001 ambient-light sensor read. | D1+D2 verified
 * review: G1-original function-local scratch (local_38). */
struct __attribute__((packed)) g1_layout_opt3001_i2c_xfer_bytes__stack_0911 {
    uint8_t reg_or_status[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x3];
    uint8_t value_byte[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_opt3001_i2c_xfer_bytes__stack_0911, reg_or_status) == 0x0, "g1_layout_opt3001_i2c_xfer_bytes__stack_0911.reg_or_status");
_Static_assert(offsetof(struct g1_layout_opt3001_i2c_xfer_bytes__stack_0911, value_byte) == 0x4, "g1_layout_opt3001_i2c_xfer_bytes__stack_0911.value_byte");
_Static_assert(sizeof(struct g1_layout_opt3001_i2c_xfer_bytes__stack_0911) >= 0x5, "g1_layout_opt3001_i2c_xfer_bytes__stack_0911.size");

/* stack_0912 | G1-original | Stack-local pair of 16-bit register values used while reading the OPT3001 ambient-light sensor register. | D1+D2 verified
 * review: Single-cid stack local. Offsets kept. */
struct __attribute__((packed)) g1_layout_opt3001_reg_read_locals__stack_0912 {
    uint8_t reg_value[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x2];
    uint8_t reg_addr_or_status[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_opt3001_reg_read_locals__stack_0912, reg_value) == 0x0, "g1_layout_opt3001_reg_read_locals__stack_0912.reg_value");
_Static_assert(offsetof(struct g1_layout_opt3001_reg_read_locals__stack_0912, reg_addr_or_status) == 0x4, "g1_layout_opt3001_reg_read_locals__stack_0912.reg_addr_or_status");
_Static_assert(sizeof(struct g1_layout_opt3001_reg_read_locals__stack_0912) >= 0x6, "g1_layout_opt3001_reg_read_locals__stack_0912.size");

/* stack_0931 | G1-original | Stack-local flag pair (local_dc) in sendAudioStram2Cache controlling audio-stream-to-cache buffering. | D1+D2 verified
 * review: Function-local; offsets unchanged. */
struct __attribute__((packed)) g1_layout_audio_stream_cache_flags__stack_0931 {
    uint8_t cache_flag0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t cache_flag1[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_audio_stream_cache_flags__stack_0931, cache_flag0) == 0x0, "g1_layout_audio_stream_cache_flags__stack_0931.cache_flag0");
_Static_assert(offsetof(struct g1_layout_audio_stream_cache_flags__stack_0931, cache_flag1) == 0x2, "g1_layout_audio_stream_cache_flags__stack_0931.cache_flag1");
_Static_assert(sizeof(struct g1_layout_audio_stream_cache_flags__stack_0931) >= 0x3, "g1_layout_audio_stream_cache_flags__stack_0931.size");

/* stack_0934 | G1-original | Local struct in startAudioStreamRecord (local_d8) holding two 16-bit audio parameters. | D1+D2 verified
 * review: Stack local; two idx2 halfwords. */
struct __attribute__((packed)) g1_layout_audio_stream_params__stack_0934 {
    uint8_t field_0x0[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x2];
    uint8_t field_0x4[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_audio_stream_params__stack_0934, field_0x0) == 0x0, "g1_layout_audio_stream_params__stack_0934.field_0x0");
_Static_assert(offsetof(struct g1_layout_audio_stream_params__stack_0934, field_0x4) == 0x4, "g1_layout_audio_stream_params__stack_0934.field_0x4");
_Static_assert(sizeof(struct g1_layout_audio_stream_params__stack_0934) >= 0x6, "g1_layout_audio_stream_params__stack_0934.size");

/* stack_0939 | G1-original | Stack-local 16-bit pair (file/segment id and offset) in audioStreamFileManagerHandler. | D1+D2 verified
 * review: Function-local; kept naming, offsets unchanged. */
struct __attribute__((packed)) g1_layout_audio_file_mgr_locals__stack_0939 {
    uint8_t id[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x2];
    uint8_t offset[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_audio_file_mgr_locals__stack_0939, id) == 0x0, "g1_layout_audio_file_mgr_locals__stack_0939.id");
_Static_assert(offsetof(struct g1_layout_audio_file_mgr_locals__stack_0939, offset) == 0x4, "g1_layout_audio_file_mgr_locals__stack_0939.offset");
_Static_assert(sizeof(struct g1_layout_audio_file_mgr_locals__stack_0939) >= 0x6, "g1_layout_audio_file_mgr_locals__stack_0939.size");

/* stack_0940 | G1-original | Stack-local flag pair (local_f4) in audioStreamFileManagerHandler. | D1+D2 verified
 * review: Local scratch; kept offsets. */
struct __attribute__((packed)) g1_layout_audio_file_mgr_flags__stack_0940 {
    uint8_t flag_a[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t flag_b[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_audio_file_mgr_flags__stack_0940, flag_a) == 0x0, "g1_layout_audio_file_mgr_flags__stack_0940.flag_a");
_Static_assert(offsetof(struct g1_layout_audio_file_mgr_flags__stack_0940, flag_b) == 0x2, "g1_layout_audio_file_mgr_flags__stack_0940.flag_b");
_Static_assert(sizeof(struct g1_layout_audio_file_mgr_flags__stack_0940) >= 0x3, "g1_layout_audio_file_mgr_flags__stack_0940.size");

/* stack_0941 | G1-original | Stack-local scratch buffer in audioStreamFileManagerHandler (likely a filename/path buffer) with leading and trailing bytes observed. | D1+D2 verified
 * review: G1-original stack buffer; only the two end markers observed. */
struct __attribute__((packed)) g1_layout_audio_stream_file_locals__stack_0941 {
    uint8_t first_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0xcb];
    uint8_t last_byte[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_audio_stream_file_locals__stack_0941, first_byte) == 0x0, "g1_layout_audio_stream_file_locals__stack_0941.first_byte");
_Static_assert(offsetof(struct g1_layout_audio_stream_file_locals__stack_0941, last_byte) == 0xcc, "g1_layout_audio_stream_file_locals__stack_0941.last_byte");
_Static_assert(sizeof(struct g1_layout_audio_stream_file_locals__stack_0941) >= 0xcd, "g1_layout_audio_stream_file_locals__stack_0941.size");

/* stack_0942 | G1-original | Stack scratch in commit_default_config_record (record id byte + flag byte). | D1+D2 verified
 * review: G1-original local. */
struct __attribute__((packed)) g1_layout_config_record_locals__stack_0942 {
    uint8_t record_id[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x3];
    uint8_t flag[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_config_record_locals__stack_0942, record_id) == 0x0, "g1_layout_config_record_locals__stack_0942.record_id");
_Static_assert(offsetof(struct g1_layout_config_record_locals__stack_0942, flag) == 0x4, "g1_layout_config_record_locals__stack_0942.flag");
_Static_assert(sizeof(struct g1_layout_config_record_locals__stack_0942) >= 0x5, "g1_layout_config_record_locals__stack_0942.size");

/* stack_0960 | G1-original | Local id/value pair read in process_pt_data. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_pt_data_pair__stack_0960 {
    uint8_t pt_id[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t pt_value[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_pt_data_pair__stack_0960, pt_id) == 0x0, "g1_layout_pt_data_pair__stack_0960.pt_id");
_Static_assert(offsetof(struct g1_layout_pt_data_pair__stack_0960, pt_value) == 0x8, "g1_layout_pt_data_pair__stack_0960.pt_value");
_Static_assert(sizeof(struct g1_layout_pt_data_pair__stack_0960) >= 0xc, "g1_layout_pt_data_pair__stack_0960.size");

/* stack_0964 | G1-original | Five-word scratch used splitting BLE notification chunks in send_data_in_ble_chunks (local_3c). | D1+D2 verified
 * review: Unrelated BLE function; footprint collision. SEPARATE. */
struct __attribute__((packed)) g1_layout_ble_chunk_scratch5__stack_0964 {
    uint8_t w0[0x4]; /* catalog type: uint32_t */
    uint8_t w1[0x4]; /* catalog type: uint32_t */
    uint8_t w2[0x4]; /* catalog type: uint32_t */
    uint8_t w3[0x4]; /* catalog type: uint32_t */
    uint8_t w4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ble_chunk_scratch5__stack_0964, w0) == 0x0, "g1_layout_ble_chunk_scratch5__stack_0964.w0");
_Static_assert(offsetof(struct g1_layout_ble_chunk_scratch5__stack_0964, w1) == 0x4, "g1_layout_ble_chunk_scratch5__stack_0964.w1");
_Static_assert(offsetof(struct g1_layout_ble_chunk_scratch5__stack_0964, w2) == 0x8, "g1_layout_ble_chunk_scratch5__stack_0964.w2");
_Static_assert(offsetof(struct g1_layout_ble_chunk_scratch5__stack_0964, w3) == 0xc, "g1_layout_ble_chunk_scratch5__stack_0964.w3");
_Static_assert(offsetof(struct g1_layout_ble_chunk_scratch5__stack_0964, w4) == 0x10, "g1_layout_ble_chunk_scratch5__stack_0964.w4");
_Static_assert(sizeof(struct g1_layout_ble_chunk_scratch5__stack_0964) >= 0x14, "g1_layout_ble_chunk_scratch5__stack_0964.size");

/* stack_0979 | G1-original | Stack local (local_38) in render_device_info_float_screen: three float render parameters (position/dimension). | D1+D2 verified
 * review: Types refined to float per the float-screen render context (Ghidra saw idx4). */
struct __attribute__((packed)) g1_layout_float_render_params__stack_0979 {
    uint8_t param_x[0x4]; /* catalog type: float */
    uint8_t param_y[0x4]; /* catalog type: float */
    uint8_t param_z[0x4]; /* catalog type: float */
};
_Static_assert(offsetof(struct g1_layout_float_render_params__stack_0979, param_x) == 0x0, "g1_layout_float_render_params__stack_0979.param_x");
_Static_assert(offsetof(struct g1_layout_float_render_params__stack_0979, param_y) == 0x4, "g1_layout_float_render_params__stack_0979.param_y");
_Static_assert(offsetof(struct g1_layout_float_render_params__stack_0979, param_z) == 0x8, "g1_layout_float_render_params__stack_0979.param_z");
_Static_assert(sizeof(struct g1_layout_float_render_params__stack_0979) >= 0xc, "g1_layout_float_render_params__stack_0979.size");

/* stack_0980 | G1-original | Stack-local 4-word layout/coordinate record (local_2c) in render_device_info_float_screen. | D1+D2 verified
 * review: SPLIT from coincidental 4-word footprint group; unrelated to param_0728. Local scratch, not shared. */
struct __attribute__((packed)) g1_layout_device_info_float_layout__stack_0980 {
    uint8_t word_0[0x4]; /* catalog type: uint32_t */
    uint8_t word_1[0x4]; /* catalog type: uint32_t */
    uint8_t word_2[0x4]; /* catalog type: uint32_t */
    uint8_t word_3[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_device_info_float_layout__stack_0980, word_0) == 0x0, "g1_layout_device_info_float_layout__stack_0980.word_0");
_Static_assert(offsetof(struct g1_layout_device_info_float_layout__stack_0980, word_1) == 0x4, "g1_layout_device_info_float_layout__stack_0980.word_1");
_Static_assert(offsetof(struct g1_layout_device_info_float_layout__stack_0980, word_2) == 0x8, "g1_layout_device_info_float_layout__stack_0980.word_2");
_Static_assert(offsetof(struct g1_layout_device_info_float_layout__stack_0980, word_3) == 0xc, "g1_layout_device_info_float_layout__stack_0980.word_3");
_Static_assert(sizeof(struct g1_layout_device_info_float_layout__stack_0980) >= 0x10, "g1_layout_device_info_float_layout__stack_0980.size");

/* stack_0981 | G1-original | Stack-local pair of 16-bit values used while drawing an h:m:s timer widget in gui_draw_timer_hms. | D1+D2 verified
 * review: G1-original function-local scratch (local_2a). */
struct __attribute__((packed)) g1_layout_timer_hms_draw_tmp__stack_0981 {
    uint8_t value_a[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x4];
    uint8_t value_b[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_timer_hms_draw_tmp__stack_0981, value_a) == 0x0, "g1_layout_timer_hms_draw_tmp__stack_0981.value_a");
_Static_assert(offsetof(struct g1_layout_timer_hms_draw_tmp__stack_0981, value_b) == 0x6, "g1_layout_timer_hms_draw_tmp__stack_0981.value_b");
_Static_assert(sizeof(struct g1_layout_timer_hms_draw_tmp__stack_0981) >= 0x8, "g1_layout_timer_hms_draw_tmp__stack_0981.size");

/* stack_1001 | G1-original | Stack-local state used while rebuilding the dashboard display buffer in DashBoard_Reflash: three leading index words and one trailing word. | D1+D2 verified
 * review: Single-cid stack local. Offsets kept. */
struct __attribute__((packed)) g1_layout_dashboard_reflash_locals__stack_1001 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x4c];
    uint8_t field_0x58[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_locals__stack_1001, field_0x0) == 0x0, "g1_layout_dashboard_reflash_locals__stack_1001.field_0x0");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_locals__stack_1001, field_0x4) == 0x4, "g1_layout_dashboard_reflash_locals__stack_1001.field_0x4");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_locals__stack_1001, field_0x8) == 0x8, "g1_layout_dashboard_reflash_locals__stack_1001.field_0x8");
_Static_assert(offsetof(struct g1_layout_dashboard_reflash_locals__stack_1001, field_0x58) == 0x58, "g1_layout_dashboard_reflash_locals__stack_1001.field_0x58");
_Static_assert(sizeof(struct g1_layout_dashboard_reflash_locals__stack_1001) >= 0x5c, "g1_layout_dashboard_reflash_locals__stack_1001.size");

/* stack_1014 | G1-original | Stack-local bitmap draw descriptor (local_24) in gui_bmp_dynamic_bitmap_draw (two words: pointer/dimension pair). | D1+D2 verified
 * review: Function-local; offsets unchanged. */
struct __attribute__((packed)) g1_layout_bmp_draw_desc__stack_1014 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bmp_draw_desc__stack_1014, field_0x0) == 0x0, "g1_layout_bmp_draw_desc__stack_1014.field_0x0");
_Static_assert(offsetof(struct g1_layout_bmp_draw_desc__stack_1014, field_0x8) == 0x8, "g1_layout_bmp_draw_desc__stack_1014.field_0x8");
_Static_assert(sizeof(struct g1_layout_bmp_draw_desc__stack_1014) >= 0xc, "g1_layout_bmp_draw_desc__stack_1014.size");

/* stack_1015 | G1-original | Local index pair in gui_bitmap_draw (local_2c), likely a width/stride or x/y pair. | D1+D2 verified
 * review: Stack local; two idx4 words. */
struct __attribute__((packed)) g1_layout_gui_bitmap_draw_args__stack_1015 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gui_bitmap_draw_args__stack_1015, field_0x0) == 0x0, "g1_layout_gui_bitmap_draw_args__stack_1015.field_0x0");
_Static_assert(offsetof(struct g1_layout_gui_bitmap_draw_args__stack_1015, field_0x8) == 0x8, "g1_layout_gui_bitmap_draw_args__stack_1015.field_0x8");
_Static_assert(sizeof(struct g1_layout_gui_bitmap_draw_args__stack_1015) >= 0xc, "g1_layout_gui_bitmap_draw_args__stack_1015.size");

/* stack_1016 | G1-original | Stack-local word pair (likely coordinate/size) in gui_bitmps_merge_draw. | D1+D2 verified
 * review: Function-local; kept naming, offsets unchanged. */
struct __attribute__((packed)) g1_layout_bitmap_merge_locals__stack_1016 {
    uint8_t val_0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t val_1[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bitmap_merge_locals__stack_1016, val_0) == 0x0, "g1_layout_bitmap_merge_locals__stack_1016.val_0");
_Static_assert(offsetof(struct g1_layout_bitmap_merge_locals__stack_1016, val_1) == 0x8, "g1_layout_bitmap_merge_locals__stack_1016.val_1");
_Static_assert(sizeof(struct g1_layout_bitmap_merge_locals__stack_1016) >= 0xc, "g1_layout_bitmap_merge_locals__stack_1016.size");

/* stack_1018 | G1-original | Stack-local frame-render scratch (local_4c) of index/offset words in ui_render_scroll_text_frame. | D1+D2 verified
 * review: Local scratch; kept offsets. */
struct __attribute__((packed)) g1_layout_scroll_text_frame_ctx__stack_1018 {
    uint8_t word_0[0x4]; /* catalog type: uint32_t */
    uint8_t word_1[0x4]; /* catalog type: uint32_t */
    uint8_t word_2[0x4]; /* catalog type: uint32_t */
    uint8_t word_3[0x4]; /* catalog type: uint32_t */
    uint8_t word_4[0x4]; /* catalog type: uint32_t */
    uint8_t word_5[0x4]; /* catalog type: uint32_t */
    uint8_t word_6[0x4]; /* catalog type: uint32_t */
    uint8_t word_7[0x4]; /* catalog type: uint32_t */
    uint8_t word_8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x24[0x4];
    uint8_t word_9[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_ctx__stack_1018, word_0) == 0x0, "g1_layout_scroll_text_frame_ctx__stack_1018.word_0");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_ctx__stack_1018, word_1) == 0x4, "g1_layout_scroll_text_frame_ctx__stack_1018.word_1");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_ctx__stack_1018, word_2) == 0x8, "g1_layout_scroll_text_frame_ctx__stack_1018.word_2");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_ctx__stack_1018, word_3) == 0xc, "g1_layout_scroll_text_frame_ctx__stack_1018.word_3");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_ctx__stack_1018, word_4) == 0x10, "g1_layout_scroll_text_frame_ctx__stack_1018.word_4");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_ctx__stack_1018, word_5) == 0x14, "g1_layout_scroll_text_frame_ctx__stack_1018.word_5");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_ctx__stack_1018, word_6) == 0x18, "g1_layout_scroll_text_frame_ctx__stack_1018.word_6");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_ctx__stack_1018, word_7) == 0x1c, "g1_layout_scroll_text_frame_ctx__stack_1018.word_7");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_ctx__stack_1018, word_8) == 0x20, "g1_layout_scroll_text_frame_ctx__stack_1018.word_8");
_Static_assert(offsetof(struct g1_layout_scroll_text_frame_ctx__stack_1018, word_9) == 0x28, "g1_layout_scroll_text_frame_ctx__stack_1018.word_9");
_Static_assert(sizeof(struct g1_layout_scroll_text_frame_ctx__stack_1018) >= 0x2c, "g1_layout_scroll_text_frame_ctx__stack_1018.size");

/* stack_1021 | G1-original | Stack-local formatted clock-digit buffer in gui_clock_draw: 16 individually-read character/digit bytes plus a trailing separator byte, used to render the on-screen clock. | D1+D2 verified
 * review: G1-original; contiguous 16-byte read run + trailing byte. Kept array interpretation. */
struct __attribute__((packed)) g1_layout_clock_digit_buf__stack_1021 {
    uint8_t digit_0[0x1]; /* catalog type: uint8_t */
    uint8_t digit_1[0x1]; /* catalog type: uint8_t */
    uint8_t digit_2[0x1]; /* catalog type: uint8_t */
    uint8_t digit_3[0x1]; /* catalog type: uint8_t */
    uint8_t digit_4[0x1]; /* catalog type: uint8_t */
    uint8_t digit_5[0x1]; /* catalog type: uint8_t */
    uint8_t digit_6[0x1]; /* catalog type: uint8_t */
    uint8_t digit_7[0x1]; /* catalog type: uint8_t */
    uint8_t digit_8[0x1]; /* catalog type: uint8_t */
    uint8_t digit_9[0x1]; /* catalog type: uint8_t */
    uint8_t digit_10[0x1]; /* catalog type: uint8_t */
    uint8_t digit_11[0x1]; /* catalog type: uint8_t */
    uint8_t digit_12[0x1]; /* catalog type: uint8_t */
    uint8_t digit_13[0x1]; /* catalog type: uint8_t */
    uint8_t digit_14[0x1]; /* catalog type: uint8_t */
    uint8_t digit_15[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x10[0x4];
    uint8_t trailing_byte[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_0) == 0x0, "g1_layout_clock_digit_buf__stack_1021.digit_0");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_1) == 0x1, "g1_layout_clock_digit_buf__stack_1021.digit_1");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_2) == 0x2, "g1_layout_clock_digit_buf__stack_1021.digit_2");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_3) == 0x3, "g1_layout_clock_digit_buf__stack_1021.digit_3");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_4) == 0x4, "g1_layout_clock_digit_buf__stack_1021.digit_4");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_5) == 0x5, "g1_layout_clock_digit_buf__stack_1021.digit_5");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_6) == 0x6, "g1_layout_clock_digit_buf__stack_1021.digit_6");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_7) == 0x7, "g1_layout_clock_digit_buf__stack_1021.digit_7");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_8) == 0x8, "g1_layout_clock_digit_buf__stack_1021.digit_8");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_9) == 0x9, "g1_layout_clock_digit_buf__stack_1021.digit_9");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_10) == 0xa, "g1_layout_clock_digit_buf__stack_1021.digit_10");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_11) == 0xb, "g1_layout_clock_digit_buf__stack_1021.digit_11");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_12) == 0xc, "g1_layout_clock_digit_buf__stack_1021.digit_12");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_13) == 0xd, "g1_layout_clock_digit_buf__stack_1021.digit_13");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_14) == 0xe, "g1_layout_clock_digit_buf__stack_1021.digit_14");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, digit_15) == 0xf, "g1_layout_clock_digit_buf__stack_1021.digit_15");
_Static_assert(offsetof(struct g1_layout_clock_digit_buf__stack_1021, trailing_byte) == 0x14, "g1_layout_clock_digit_buf__stack_1021.trailing_byte");
_Static_assert(sizeof(struct g1_layout_clock_digit_buf__stack_1021) >= 0x15, "g1_layout_clock_digit_buf__stack_1021.size");

/* stack_1027 | G1-original | Stack scratch in gui_utf_Wordwrap_draw (three cursor/width words for text layout). | D1+D2 verified
 * review: G1-original local. */
struct __attribute__((packed)) g1_layout_utf_wordwrap_locals__stack_1027 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_utf_wordwrap_locals__stack_1027, field_0x0) == 0x0, "g1_layout_utf_wordwrap_locals__stack_1027.field_0x0");
_Static_assert(offsetof(struct g1_layout_utf_wordwrap_locals__stack_1027, field_0x4) == 0x4, "g1_layout_utf_wordwrap_locals__stack_1027.field_0x4");
_Static_assert(offsetof(struct g1_layout_utf_wordwrap_locals__stack_1027, field_0x8) == 0x8, "g1_layout_utf_wordwrap_locals__stack_1027.field_0x8");
_Static_assert(sizeof(struct g1_layout_utf_wordwrap_locals__stack_1027) >= 0xc, "g1_layout_utf_wordwrap_locals__stack_1027.size");

/* stack_1033 | G1-original | Local coordinate pair used by gui_string_draw when positioning glyphs. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_gui_draw_point__stack_1033 {
    uint8_t x[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t y[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gui_draw_point__stack_1033, x) == 0x0, "g1_layout_gui_draw_point__stack_1033.x");
_Static_assert(offsetof(struct g1_layout_gui_draw_point__stack_1033, y) == 0x8, "g1_layout_gui_draw_point__stack_1033.y");
_Static_assert(sizeof(struct g1_layout_gui_draw_point__stack_1033) >= 0xc, "g1_layout_gui_draw_point__stack_1033.size");

/* stack_1036 | G1-original | Stack local (local_38) in reflash_fb_data_to_lcd: pair of status/index bytes during framebuffer-to-LCD transfer. | D1+D2 verified
 * review: Single-cid stack local. */
struct __attribute__((packed)) g1_layout_lcd_fb_xfer_local__stack_1036 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x3];
    uint8_t field_0x4[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_lcd_fb_xfer_local__stack_1036, field_0x0) == 0x0, "g1_layout_lcd_fb_xfer_local__stack_1036.field_0x0");
_Static_assert(offsetof(struct g1_layout_lcd_fb_xfer_local__stack_1036, field_0x4) == 0x4, "g1_layout_lcd_fb_xfer_local__stack_1036.field_0x4");
_Static_assert(sizeof(struct g1_layout_lcd_fb_xfer_local__stack_1036) >= 0x5, "g1_layout_lcd_fb_xfer_local__stack_1036.size");

/* stack_1037 | G1-original | Stack-local status pair in reflash_fb_data_to_lcd_ex tracking framebuffer-to-LCD reflash progress. | D1+D2 verified
 * review: G1-original function-local scratch (local_38). */
struct __attribute__((packed)) g1_layout_lcd_reflash_local_state__stack_1037 {
    uint8_t reflash_status[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x3];
    uint8_t reflash_flag[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_lcd_reflash_local_state__stack_1037, reflash_status) == 0x0, "g1_layout_lcd_reflash_local_state__stack_1037.reflash_status");
_Static_assert(offsetof(struct g1_layout_lcd_reflash_local_state__stack_1037, reflash_flag) == 0x4, "g1_layout_lcd_reflash_local_state__stack_1037.reflash_flag");
_Static_assert(sizeof(struct g1_layout_lcd_reflash_local_state__stack_1037) >= 0x5, "g1_layout_lcd_reflash_local_state__stack_1037.size");

/* stack_1042 | G1-original | Stack-local struct in proxy_thread_handler holding two state/flag bytes. | D1+D2 verified
 * review: Single-cid stack local. Offsets kept. */
struct __attribute__((packed)) g1_layout_proxy_thread_locals__stack_1042 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_proxy_thread_locals__stack_1042, field_0x0) == 0x0, "g1_layout_proxy_thread_locals__stack_1042.field_0x0");
_Static_assert(offsetof(struct g1_layout_proxy_thread_locals__stack_1042, field_0x2) == 0x2, "g1_layout_proxy_thread_locals__stack_1042.field_0x2");
_Static_assert(sizeof(struct g1_layout_proxy_thread_locals__stack_1042) >= 0x3, "g1_layout_proxy_thread_locals__stack_1042.size");

/* stack_1044 | G1-original | Stack-local flag-byte pair at the tail of a local buffer (local_24) in ui_refalsh_warp. | D1+D2 verified
 * review: Function-local; offsets unchanged. */
struct __attribute__((packed)) g1_layout_ui_warp_flags_tmp__stack_1044 {
    uint8_t _pad_0x0[0xe];
    uint8_t field_0xe[0x1]; /* catalog type: uint8_t */
    uint8_t field_0xf[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_ui_warp_flags_tmp__stack_1044, field_0xe) == 0xe, "g1_layout_ui_warp_flags_tmp__stack_1044.field_0xe");
_Static_assert(offsetof(struct g1_layout_ui_warp_flags_tmp__stack_1044, field_0xf) == 0xf, "g1_layout_ui_warp_flags_tmp__stack_1044.field_0xf");
_Static_assert(sizeof(struct g1_layout_ui_warp_flags_tmp__stack_1044) >= 0x10, "g1_layout_ui_warp_flags_tmp__stack_1044.size");

/* stack_1048 | G1-original | Small local flag pair in display_thread_handler (local_40). | D1+D2 verified
 * review: Stack local; two idx1 bytes. */
struct __attribute__((packed)) g1_layout_display_thread_locals__stack_1048 {
    uint8_t flag_a[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t flag_b[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_display_thread_locals__stack_1048, flag_a) == 0x0, "g1_layout_display_thread_locals__stack_1048.flag_a");
_Static_assert(offsetof(struct g1_layout_display_thread_locals__stack_1048, flag_b) == 0x2, "g1_layout_display_thread_locals__stack_1048.flag_b");
_Static_assert(sizeof(struct g1_layout_display_thread_locals__stack_1048) >= 0x3, "g1_layout_display_thread_locals__stack_1048.size");

/* stack_1050 | G1-original | Small stack-local status/flag byte pair in display_close. | D1+D2 verified
 * review: Function-local; kept naming, offsets unchanged. */
struct __attribute__((packed)) g1_layout_display_close_locals__stack_1050 {
    uint8_t flag_0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t flag_2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_display_close_locals__stack_1050, flag_0) == 0x0, "g1_layout_display_close_locals__stack_1050.flag_0");
_Static_assert(offsetof(struct g1_layout_display_close_locals__stack_1050, flag_2) == 0x2, "g1_layout_display_close_locals__stack_1050.flag_2");
_Static_assert(sizeof(struct g1_layout_display_close_locals__stack_1050) >= 0x3, "g1_layout_display_close_locals__stack_1050.size");

/* stack_1053 | G1-original | Stack-local scratch (local_28) in display_powerEvent (event-type byte + trailing result byte). | D1+D2 verified
 * review: Local scratch; kept offsets. */
struct __attribute__((packed)) g1_layout_display_power_event_locals__stack_1053 {
    uint8_t event_type[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1b];
    uint8_t result[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_display_power_event_locals__stack_1053, event_type) == 0x0, "g1_layout_display_power_event_locals__stack_1053.event_type");
_Static_assert(offsetof(struct g1_layout_display_power_event_locals__stack_1053, result) == 0x1c, "g1_layout_display_power_event_locals__stack_1053.result");
_Static_assert(sizeof(struct g1_layout_display_power_event_locals__stack_1053) >= 0x1d, "g1_layout_display_power_event_locals__stack_1053.size");

/* stack_1055 | G1-original | Stack-local character buffer holding formatted ASCII digits produced by float_to_ascii_signed_2dp. | D1+D2 verified
 * review: G1-original ASCII digit scratch buffer; kept array interpretation. */
struct __attribute__((packed)) g1_layout_ascii_digit_buffer__stack_1055 {
    uint8_t _pad_0x0[0x1];
    uint8_t digit_0[0x1]; /* catalog type: uint8_t */
    uint8_t digit_1[0x1]; /* catalog type: uint8_t */
    uint8_t digit_2[0x1]; /* catalog type: uint8_t */
    uint8_t digit_3[0x1]; /* catalog type: uint8_t */
    uint8_t digit_4[0x1]; /* catalog type: uint8_t */
    uint8_t digit_5[0x1]; /* catalog type: uint8_t */
    uint8_t digit_6[0x1]; /* catalog type: uint8_t */
    uint8_t digit_7[0x1]; /* catalog type: uint8_t */
    uint8_t digit_8[0x1]; /* catalog type: uint8_t */
    uint8_t digit_9[0x1]; /* catalog type: uint8_t */
    uint8_t digit_10[0x1]; /* catalog type: uint8_t */
    uint8_t digit_11[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xd[0x4];
    uint8_t digit_tail[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_0) == 0x1, "g1_layout_ascii_digit_buffer__stack_1055.digit_0");
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_1) == 0x2, "g1_layout_ascii_digit_buffer__stack_1055.digit_1");
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_2) == 0x3, "g1_layout_ascii_digit_buffer__stack_1055.digit_2");
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_3) == 0x4, "g1_layout_ascii_digit_buffer__stack_1055.digit_3");
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_4) == 0x5, "g1_layout_ascii_digit_buffer__stack_1055.digit_4");
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_5) == 0x6, "g1_layout_ascii_digit_buffer__stack_1055.digit_5");
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_6) == 0x7, "g1_layout_ascii_digit_buffer__stack_1055.digit_6");
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_7) == 0x8, "g1_layout_ascii_digit_buffer__stack_1055.digit_7");
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_8) == 0x9, "g1_layout_ascii_digit_buffer__stack_1055.digit_8");
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_9) == 0xa, "g1_layout_ascii_digit_buffer__stack_1055.digit_9");
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_10) == 0xb, "g1_layout_ascii_digit_buffer__stack_1055.digit_10");
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_11) == 0xc, "g1_layout_ascii_digit_buffer__stack_1055.digit_11");
_Static_assert(offsetof(struct g1_layout_ascii_digit_buffer__stack_1055, digit_tail) == 0x11, "g1_layout_ascii_digit_buffer__stack_1055.digit_tail");
_Static_assert(sizeof(struct g1_layout_ascii_digit_buffer__stack_1055) >= 0x12, "g1_layout_ascii_digit_buffer__stack_1055.size");

/* stack_1060 | G1-original | Stack local (id/len halfword pair) used while mounting the NVS filesystem in nvs_mount; likely a partial NVS allocation-table entry. | D1+D2 verified
 * review: Kept as a function-local frame (not the shared library struct type). Possibly a struct nvs_ate id/len pair, but only a stack scratch here, so is_library=false. */
struct __attribute__((packed)) g1_layout_nvs_mount_ate_local__stack_1060 {
    uint8_t id[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x2];
    uint8_t len[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_nvs_mount_ate_local__stack_1060, id) == 0x0, "g1_layout_nvs_mount_ate_local__stack_1060.id");
_Static_assert(offsetof(struct g1_layout_nvs_mount_ate_local__stack_1060, len) == 0x4, "g1_layout_nvs_mount_ate_local__stack_1060.len");
_Static_assert(sizeof(struct g1_layout_nvs_mount_ate_local__stack_1060) >= 0x6, "g1_layout_nvs_mount_ate_local__stack_1060.size");

/* stack_1062 | G1-original | Local scratch aggregate in FUN_0004cf78: a write-only status byte + three read-only words across a large frame. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_scratch_ctx_0004cf78__stack_1062 {
    uint8_t _pad_0x0[0x19];
    uint8_t field_0x19[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1a[0x22];
    uint8_t field_0x3c[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x40[0x28];
    uint8_t field_0x68[0x4]; /* catalog type: int32_t */
    uint8_t field_0x6c[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_scratch_ctx_0004cf78__stack_1062, field_0x19) == 0x19, "g1_layout_scratch_ctx_0004cf78__stack_1062.field_0x19");
_Static_assert(offsetof(struct g1_layout_scratch_ctx_0004cf78__stack_1062, field_0x3c) == 0x3c, "g1_layout_scratch_ctx_0004cf78__stack_1062.field_0x3c");
_Static_assert(offsetof(struct g1_layout_scratch_ctx_0004cf78__stack_1062, field_0x68) == 0x68, "g1_layout_scratch_ctx_0004cf78__stack_1062.field_0x68");
_Static_assert(offsetof(struct g1_layout_scratch_ctx_0004cf78__stack_1062, field_0x6c) == 0x6c, "g1_layout_scratch_ctx_0004cf78__stack_1062.field_0x6c");
_Static_assert(sizeof(struct g1_layout_scratch_ctx_0004cf78__stack_1062) >= 0x70, "g1_layout_scratch_ctx_0004cf78__stack_1062.size");

/* stack_1066 | G1-original | Stack local (local_2c) in g1_recon_z_log_msg_alloc: a size/id word plus a length/pointer word, mirroring a Zephyr log message allocation descriptor. | D1+D2 verified
 * review: Corrected sonnet is_library flagging (it left false); a local frame, not a public struct. */
struct __attribute__((packed)) g1_layout_log_msg_desc_local__stack_1066 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_log_msg_desc_local__stack_1066, field_0x0) == 0x0, "g1_layout_log_msg_desc_local__stack_1066.field_0x0");
_Static_assert(offsetof(struct g1_layout_log_msg_desc_local__stack_1066, field_0x8) == 0x8, "g1_layout_log_msg_desc_local__stack_1066.field_0x8");
_Static_assert(sizeof(struct g1_layout_log_msg_desc_local__stack_1066) >= 0xc, "g1_layout_log_msg_desc_local__stack_1066.size");

/* stack_1070 | library | Local flash sector descriptor (offset/size + running count) built while walking flash_area_get_sectors. | D1+D2 verified
 * review: struct flash_sector is {off_t fs_off; uint32_t fs_size} (8 bytes). Observed adds a third word (0xc, a loop count), so this is the sector-descriptor plus a counter in the loop scratch, not a bare flash_sector; library_verified=false. */
struct __attribute__((packed)) g1_layout_flash_sector__stack_1070 {
    uint8_t _pad_0x0[0x4];
    uint8_t sector_off[0x4]; /* catalog type: uint32_t; SDK member: fs_off */
    uint8_t sector_size[0x4]; /* catalog type: uint32_t; SDK member: fs_size */
    uint8_t sector_count[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_flash_sector__stack_1070, sector_off) == 0x4, "g1_layout_flash_sector__stack_1070.sector_off");
_Static_assert(offsetof(struct g1_layout_flash_sector__stack_1070, sector_size) == 0x8, "g1_layout_flash_sector__stack_1070.sector_size");
_Static_assert(offsetof(struct g1_layout_flash_sector__stack_1070, sector_count) == 0xc, "g1_layout_flash_sector__stack_1070.sector_count");
_Static_assert(sizeof(struct g1_layout_flash_sector__stack_1070) >= 0x10, "g1_layout_flash_sector__stack_1070.size");

/* stack_1074 | G1-original | Stack-local 4-word scratch (local_20) in settings_nvs_backend_mount; bookkeeping temporaries, NOT the heap-resident struct nvs_fs. | D1+D2 verified
 * review: SPLIT from coincidental footprint group. Corrected sonnet: this is a 16-byte stack scratch, not struct nvs_fs (which is much larger and heap-held). */
struct __attribute__((packed)) g1_layout_nvs_mount_scratch__stack_1074 {
    uint8_t word_0[0x4]; /* catalog type: uint32_t */
    uint8_t word_1[0x4]; /* catalog type: uint32_t */
    uint8_t word_2[0x4]; /* catalog type: uint32_t */
    uint8_t word_3[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_nvs_mount_scratch__stack_1074, word_0) == 0x0, "g1_layout_nvs_mount_scratch__stack_1074.word_0");
_Static_assert(offsetof(struct g1_layout_nvs_mount_scratch__stack_1074, word_1) == 0x4, "g1_layout_nvs_mount_scratch__stack_1074.word_1");
_Static_assert(offsetof(struct g1_layout_nvs_mount_scratch__stack_1074, word_2) == 0x8, "g1_layout_nvs_mount_scratch__stack_1074.word_2");
_Static_assert(offsetof(struct g1_layout_nvs_mount_scratch__stack_1074, word_3) == 0xc, "g1_layout_nvs_mount_scratch__stack_1074.word_3");
_Static_assert(sizeof(struct g1_layout_nvs_mount_scratch__stack_1074) >= 0x10, "g1_layout_nvs_mount_scratch__stack_1074.size");

/* stack_1078 | G1-original | Stack-local pair of status/flag bytes read in discovery_callback after a BLE GATT discovery operation. | D1+D2 verified
 * review: Single-cid stack local. Offsets kept. */
struct __attribute__((packed)) g1_layout_discovery_callback_locals__stack_1078 {
    uint8_t status[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t flags[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_discovery_callback_locals__stack_1078, status) == 0x0, "g1_layout_discovery_callback_locals__stack_1078.status");
_Static_assert(offsetof(struct g1_layout_discovery_callback_locals__stack_1078, flags) == 0x2, "g1_layout_discovery_callback_locals__stack_1078.flags");
_Static_assert(sizeof(struct g1_layout_discovery_callback_locals__stack_1078) >= 0x3, "g1_layout_discovery_callback_locals__stack_1078.size");

/* stack_1079 | G1-original | Stack-local index-byte pair (local_38) in discovery_callback describing a discovered BLE attribute (type + length/flags). | D1+D2 verified
 * review: Function-local; offsets unchanged. */
struct __attribute__((packed)) g1_layout_discovery_result_flags__stack_1079 {
    uint8_t type_idx[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t len_idx[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_discovery_result_flags__stack_1079, type_idx) == 0x0, "g1_layout_discovery_result_flags__stack_1079.type_idx");
_Static_assert(offsetof(struct g1_layout_discovery_result_flags__stack_1079, len_idx) == 0x2, "g1_layout_discovery_result_flags__stack_1079.len_idx");
_Static_assert(sizeof(struct g1_layout_discovery_result_flags__stack_1079) >= 0x3, "g1_layout_discovery_result_flags__stack_1079.size");

/* stack_1080 | G1-original | Stack-local byte pair used while assigning ANCS GATT discovery-manager handles (ancs_gatt_dm_assign_handles local_a0). | D1+D2 verified
 * review: Stack local; two idx1 bytes. */
struct __attribute__((packed)) g1_layout_ancs_handle_pair__stack_1080 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_ancs_handle_pair__stack_1080, field_0x0) == 0x0, "g1_layout_ancs_handle_pair__stack_1080.field_0x0");
_Static_assert(offsetof(struct g1_layout_ancs_handle_pair__stack_1080, field_0x2) == 0x2, "g1_layout_ancs_handle_pair__stack_1080.field_0x2");
_Static_assert(sizeof(struct g1_layout_ancs_handle_pair__stack_1080) >= 0x3, "g1_layout_ancs_handle_pair__stack_1080.size");

/* stack_1081 | G1-original | Small stack-local scratch (two index bytes) in ancs_gatt_dm_assign_handles. | D1+D2 verified
 * review: Function-local; kept naming, offsets unchanged. */
struct __attribute__((packed)) g1_layout_ancs_handle_locals__stack_1081 {
    uint8_t idx_0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t idx_2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_ancs_handle_locals__stack_1081, idx_0) == 0x0, "g1_layout_ancs_handle_locals__stack_1081.idx_0");
_Static_assert(offsetof(struct g1_layout_ancs_handle_locals__stack_1081, idx_2) == 0x2, "g1_layout_ancs_handle_locals__stack_1081.idx_2");
_Static_assert(sizeof(struct g1_layout_ancs_handle_locals__stack_1081) >= 0x3, "g1_layout_ancs_handle_locals__stack_1081.size");

/* stack_1097 | G1-original | Local 5-word scratch inside tc_aes128_set_encrypt_key (TinyCrypt). Not the full 44-word key schedule struct, just a loop scratch. | D1+D2 verified
 * review: Sonnet tagged as tc_aes_key_sched_struct; corrected to is_library=false. The tc_aes_key_sched_struct is 176 bytes (44 words); this 5-word local is only a computation scratch, not that stock struct. Footprint collision. SEPARATE. */
struct __attribute__((packed)) g1_layout_aes_key_setup_scratch5__stack_1097 {
    uint8_t w0[0x4]; /* catalog type: uint32_t */
    uint8_t w1[0x4]; /* catalog type: uint32_t */
    uint8_t w2[0x4]; /* catalog type: uint32_t */
    uint8_t w3[0x4]; /* catalog type: uint32_t */
    uint8_t w4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_aes_key_setup_scratch5__stack_1097, w0) == 0x0, "g1_layout_aes_key_setup_scratch5__stack_1097.w0");
_Static_assert(offsetof(struct g1_layout_aes_key_setup_scratch5__stack_1097, w1) == 0x4, "g1_layout_aes_key_setup_scratch5__stack_1097.w1");
_Static_assert(offsetof(struct g1_layout_aes_key_setup_scratch5__stack_1097, w2) == 0x8, "g1_layout_aes_key_setup_scratch5__stack_1097.w2");
_Static_assert(offsetof(struct g1_layout_aes_key_setup_scratch5__stack_1097, w3) == 0xc, "g1_layout_aes_key_setup_scratch5__stack_1097.w3");
_Static_assert(offsetof(struct g1_layout_aes_key_setup_scratch5__stack_1097, w4) == 0x10, "g1_layout_aes_key_setup_scratch5__stack_1097.w4");
_Static_assert(sizeof(struct g1_layout_aes_key_setup_scratch5__stack_1097) >= 0x14, "g1_layout_aes_key_setup_scratch5__stack_1097.size");

/* stack_1112 | G1-original | Stack-local MPU region-config temporaries (local_38) in arm_core_mpu_configure. | D1+D2 verified
 * review: Local scratch; kept offsets. */
struct __attribute__((packed)) g1_layout_arm_mpu_configure_locals__stack_1112 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_arm_mpu_configure_locals__stack_1112, field_0x0) == 0x0, "g1_layout_arm_mpu_configure_locals__stack_1112.field_0x0");
_Static_assert(offsetof(struct g1_layout_arm_mpu_configure_locals__stack_1112, field_0x8) == 0x8, "g1_layout_arm_mpu_configure_locals__stack_1112.field_0x8");
_Static_assert(sizeof(struct g1_layout_arm_mpu_configure_locals__stack_1112) >= 0xc, "g1_layout_arm_mpu_configure_locals__stack_1112.size");

/* stack_1118 | library | Stack-local copy of flash-area offset/size fields used by img_mgmt_erased_val to read the erased-value setting for an image slot. | D1+D2 verified
 * review: Ground-truth hint is G1-original and only two words (fa_off-like @0x0, fa_size-like @0x8) are seen; the real struct flash_area has fa_off@0x8/fa_size@0xc (with fa_id/fa_device_id ahead), so these do NOT line up. Kept is_library True as a weak hint but library_verified=false due to offset mismatch. */
struct __attribute__((packed)) g1_layout_flash_area_info__stack_1118 {
    uint8_t fa_off_local[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t fa_size_local[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_flash_area_info__stack_1118, fa_off_local) == 0x0, "g1_layout_flash_area_info__stack_1118.fa_off_local");
_Static_assert(offsetof(struct g1_layout_flash_area_info__stack_1118, fa_size_local) == 0x8, "g1_layout_flash_area_info__stack_1118.fa_size_local");
_Static_assert(sizeof(struct g1_layout_flash_area_info__stack_1118) >= 0xc, "g1_layout_flash_area_info__stack_1118.size");

/* stack_1124 | G1-original | Stack-local pair (e.g. hash ptr + length/slot) in img_mgmt_read_info. | D1+D2 verified
 * review: G1-original local frame. */
struct __attribute__((packed)) g1_layout_img_mgmt_info_local__stack_1124 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_img_mgmt_info_local__stack_1124, field_0x0) == 0x0, "g1_layout_img_mgmt_info_local__stack_1124.field_0x0");
_Static_assert(offsetof(struct g1_layout_img_mgmt_info_local__stack_1124, field_0x8) == 0x8, "g1_layout_img_mgmt_info_local__stack_1124.field_0x8");
_Static_assert(sizeof(struct g1_layout_img_mgmt_info_local__stack_1124) >= 0xc, "g1_layout_img_mgmt_info_local__stack_1124.size");

/* stack_1126 | G1-original | Local offset/size pair in img_mgmt_upload describing the current firmware upload chunk. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_img_upload_chunk__stack_1126 {
    uint8_t chunk_offset[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t chunk_size[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_img_upload_chunk__stack_1126, chunk_offset) == 0x0, "g1_layout_img_upload_chunk__stack_1126.chunk_offset");
_Static_assert(offsetof(struct g1_layout_img_upload_chunk__stack_1126, chunk_size) == 0x8, "g1_layout_img_upload_chunk__stack_1126.chunk_size");
_Static_assert(sizeof(struct g1_layout_img_upload_chunk__stack_1126) >= 0xc, "g1_layout_img_upload_chunk__stack_1126.size");

/* stack_1128 | G1-original | Stack-local 4-word scratch (local_d4) in img_mgmt_upload holding upload state temporaries (offset/size/len/flags). | D1+D2 verified
 * review: SPLIT from coincidental footprint group. Corrected sonnet library guess: this is a local scratch, not a stock mcumgr struct. */
struct __attribute__((packed)) g1_layout_img_mgmt_upload_scratch__stack_1128 {
    uint8_t word_0[0x4]; /* catalog type: uint32_t */
    uint8_t word_1[0x4]; /* catalog type: uint32_t */
    uint8_t word_2[0x4]; /* catalog type: uint32_t */
    uint8_t word_3[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_scratch__stack_1128, word_0) == 0x0, "g1_layout_img_mgmt_upload_scratch__stack_1128.word_0");
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_scratch__stack_1128, word_1) == 0x4, "g1_layout_img_mgmt_upload_scratch__stack_1128.word_1");
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_scratch__stack_1128, word_2) == 0x8, "g1_layout_img_mgmt_upload_scratch__stack_1128.word_2");
_Static_assert(offsetof(struct g1_layout_img_mgmt_upload_scratch__stack_1128, word_3) == 0xc, "g1_layout_img_mgmt_upload_scratch__stack_1128.word_3");
_Static_assert(sizeof(struct g1_layout_img_mgmt_upload_scratch__stack_1128) >= 0x10, "g1_layout_img_mgmt_upload_scratch__stack_1128.size");

/* stack_1131 | G1-original | Stack local (local_2c) in storage_erase_handler: erase range (address/size style pair). | D1+D2 verified
 * review: Single-cid stack local. */
struct __attribute__((packed)) g1_layout_storage_erase_range_tmp__stack_1131 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x10];
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_storage_erase_range_tmp__stack_1131, field_0x0) == 0x0, "g1_layout_storage_erase_range_tmp__stack_1131.field_0x0");
_Static_assert(offsetof(struct g1_layout_storage_erase_range_tmp__stack_1131, field_0x14) == 0x14, "g1_layout_storage_erase_range_tmp__stack_1131.field_0x14");
_Static_assert(sizeof(struct g1_layout_storage_erase_range_tmp__stack_1131) >= 0x18, "g1_layout_storage_erase_range_tmp__stack_1131.size");

/* stack_1136 | G1-original | Stack-local flag pair in gatt_register_service (Zephyr GATT service registration path). | D1+D2 verified
 * review: Downgraded from sonnet's bt_gatt_service: these are two local flag bytes (local_44), not a stock struct, so is_library=false. */
struct __attribute__((packed)) g1_layout_gatt_register_service_locals__stack_1136 {
    uint8_t flag_a[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t flag_b[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_register_service_locals__stack_1136, flag_a) == 0x0, "g1_layout_gatt_register_service_locals__stack_1136.flag_a");
_Static_assert(offsetof(struct g1_layout_gatt_register_service_locals__stack_1136, flag_b) == 0x2, "g1_layout_gatt_register_service_locals__stack_1136.flag_b");
_Static_assert(sizeof(struct g1_layout_gatt_register_service_locals__stack_1136) >= 0x3, "g1_layout_gatt_register_service_locals__stack_1136.size");

/* stack_1151 | G1-original | Stack-local char buffer in ver_str building a formatted image version string (mcumgr/MCUboot), accessed as 15 contiguous words. | D1+D2 verified
 * review: Anonymous local char[0x3c] buffer, not a named library struct → is_library=false. Represented as a byte buffer; the 15 word 'fields' are just word-granular writes into one char array. Offsets kept as the array base. */
struct __attribute__((packed)) g1_layout_ver_str_buf__stack_1151 {
    uint8_t version_string[0x4]; /* catalog type: char[0x3c] */
    uint8_t _tail_pad[0x38];
};
_Static_assert(offsetof(struct g1_layout_ver_str_buf__stack_1151, version_string) == 0x0, "g1_layout_ver_str_buf__stack_1151.version_string");
_Static_assert(sizeof(struct g1_layout_ver_str_buf__stack_1151) >= 0x3c, "g1_layout_ver_str_buf__stack_1151.size");

/* stack_1170 | G1-original | Stack-local scratch (local_34) in ble_privacy_request_random_address for resolvable-private-address generation (state word + result word). | D1+D2 verified
 * review: Function-local; offsets unchanged. */
struct __attribute__((packed)) g1_layout_ble_rpa_gen_locals__stack_1170 {
    uint8_t state_word[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x10];
    uint8_t result_word[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_ble_rpa_gen_locals__stack_1170, state_word) == 0x0, "g1_layout_ble_rpa_gen_locals__stack_1170.state_word");
_Static_assert(offsetof(struct g1_layout_ble_rpa_gen_locals__stack_1170, result_word) == 0x14, "g1_layout_ble_rpa_gen_locals__stack_1170.result_word");
_Static_assert(sizeof(struct g1_layout_ble_rpa_gen_locals__stack_1170) >= 0x18, "g1_layout_ble_rpa_gen_locals__stack_1170.size");

/* stack_1173 | G1-original | Local buffer holding an HCI static-address response record in hci_read_static_addresses (local_34). | D1+D2 verified
 * review: Callee is application-class despite hci prefix; a stack local, not a stock struct. Two idx4 words. */
struct __attribute__((packed)) g1_layout_hci_static_addr_locals__stack_1173 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x10];
    uint8_t field_0x14[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_hci_static_addr_locals__stack_1173, field_0x0) == 0x0, "g1_layout_hci_static_addr_locals__stack_1173.field_0x0");
_Static_assert(offsetof(struct g1_layout_hci_static_addr_locals__stack_1173, field_0x14) == 0x14, "g1_layout_hci_static_addr_locals__stack_1173.field_0x14");
_Static_assert(sizeof(struct g1_layout_hci_static_addr_locals__stack_1173) >= 0x18, "g1_layout_hci_static_addr_locals__stack_1173.size");

/* stack_1186 | G1-original | Stack-local pair used while unref-ing a BLE connection in ble_conn_unref. | D1+D2 verified
 * review: Function-local; kept naming, offsets unchanged. */
struct __attribute__((packed)) g1_layout_conn_unref_locals__stack_1186 {
    uint8_t conn_ptr[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x8];
    uint8_t refcount_or_flag[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_conn_unref_locals__stack_1186, conn_ptr) == 0x0, "g1_layout_conn_unref_locals__stack_1186.conn_ptr");
_Static_assert(offsetof(struct g1_layout_conn_unref_locals__stack_1186, refcount_or_flag) == 0xc, "g1_layout_conn_unref_locals__stack_1186.refcount_or_flag");
_Static_assert(sizeof(struct g1_layout_conn_unref_locals__stack_1186) >= 0x10, "g1_layout_conn_unref_locals__stack_1186.size");

/* stack_1191 | G1-original | Stack-local L2CAP LE channel setup values (local_14) in bt_l2cap_connected (channel pointer, MTU word, two 16-bit fields). | D1+D2 verified
 * review: Stack local scratch (not the bt_l2cap_le_chan object itself); related to L2CAP setup. Kept offsets. */
struct __attribute__((packed)) g1_layout_l2cap_connected_locals__stack_1191 {
    uint8_t _pad_0x0[0x4];
    uint8_t chan[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0x8];
    uint8_t mtu[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x14[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x16[0xe];
    uint8_t field_0x24[0x2]; /* catalog type: uint16_t */
    uint8_t _tail_pad[0x2];
};
_Static_assert(offsetof(struct g1_layout_l2cap_connected_locals__stack_1191, chan) == 0x4, "g1_layout_l2cap_connected_locals__stack_1191.chan");
_Static_assert(offsetof(struct g1_layout_l2cap_connected_locals__stack_1191, mtu) == 0x10, "g1_layout_l2cap_connected_locals__stack_1191.mtu");
_Static_assert(offsetof(struct g1_layout_l2cap_connected_locals__stack_1191, field_0x14) == 0x14, "g1_layout_l2cap_connected_locals__stack_1191.field_0x14");
_Static_assert(offsetof(struct g1_layout_l2cap_connected_locals__stack_1191, field_0x24) == 0x24, "g1_layout_l2cap_connected_locals__stack_1191.field_0x24");
_Static_assert(sizeof(struct g1_layout_l2cap_connected_locals__stack_1191) >= 0x28, "g1_layout_l2cap_connected_locals__stack_1191.size");

/* stack_1192 | library | Stack-local L2CAP receive-path channel state in l2cap_recv: channel pointer, MTU/MPS/credits triple, an SDU length, and two later flag bytes — a local copy of bt_l2cap_le_chan rx fields. | D1+D2 verified
 * review: bt_l2cap_le_chan is a private-header host struct (l2cap_internal.h, not in the pinned tree); MTU/MPS/credits/SDU pattern is consistent but offsets unverified. */
struct __attribute__((packed)) g1_layout_bt_l2cap_le_chan_rx_local__stack_1192 {
    uint8_t _pad_0x0[0x4];
    uint8_t chan_ptr[0x4]; /* catalog type: void * */
    uint8_t _pad_0x8[0xc];
    uint8_t rx_mtu[0x2]; /* catalog type: uint16_t */
    uint8_t rx_mps[0x2]; /* catalog type: uint16_t */
    uint8_t rx_credits[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x1a[0x2];
    uint8_t sdu_len[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x20[0x94];
    uint8_t flag_b4[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0xb5[0x4];
    uint8_t flag_b9[0x1]; /* catalog type: uint8_t */
    uint8_t _tail_pad[0x3];
};
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan_rx_local__stack_1192, chan_ptr) == 0x4, "g1_layout_bt_l2cap_le_chan_rx_local__stack_1192.chan_ptr");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan_rx_local__stack_1192, rx_mtu) == 0x14, "g1_layout_bt_l2cap_le_chan_rx_local__stack_1192.rx_mtu");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan_rx_local__stack_1192, rx_mps) == 0x16, "g1_layout_bt_l2cap_le_chan_rx_local__stack_1192.rx_mps");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan_rx_local__stack_1192, rx_credits) == 0x18, "g1_layout_bt_l2cap_le_chan_rx_local__stack_1192.rx_credits");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan_rx_local__stack_1192, sdu_len) == 0x1c, "g1_layout_bt_l2cap_le_chan_rx_local__stack_1192.sdu_len");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan_rx_local__stack_1192, flag_b4) == 0xb4, "g1_layout_bt_l2cap_le_chan_rx_local__stack_1192.flag_b4");
_Static_assert(offsetof(struct g1_layout_bt_l2cap_le_chan_rx_local__stack_1192, flag_b9) == 0xb9, "g1_layout_bt_l2cap_le_chan_rx_local__stack_1192.flag_b9");
_Static_assert(sizeof(struct g1_layout_bt_l2cap_le_chan_rx_local__stack_1192) >= 0xbd, "g1_layout_bt_l2cap_le_chan_rx_local__stack_1192.size");

/* stack_1195 | G1-original | Stack (type,flag) pair in find_type_cb while scanning BLE advertising-data entries. | D1+D2 verified
 * review: G1-original local. */
struct __attribute__((packed)) g1_layout_ad_type_match_locals__stack_1195 {
    uint8_t ad_type[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t match_flag[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_ad_type_match_locals__stack_1195, ad_type) == 0x0, "g1_layout_ad_type_match_locals__stack_1195.ad_type");
_Static_assert(offsetof(struct g1_layout_ad_type_match_locals__stack_1195, match_flag) == 0x2, "g1_layout_ad_type_match_locals__stack_1195.match_flag");
_Static_assert(sizeof(struct g1_layout_ad_type_match_locals__stack_1195) >= 0x3, "g1_layout_ad_type_match_locals__stack_1195.size");

/* stack_1196 | G1-original | Large local frame in bt_att_accept setting up an incoming ATT connection (two 16-bit setup fields + trailing word). | D1+D2 verified
 * review: Function-local stack frame, not a nameable stock struct; is_library corrected to false. */
struct __attribute__((packed)) g1_layout_bt_att_accept_locals__stack_1196 {
    uint8_t _pad_0x0[0x1e];
    uint8_t field_0x1e[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x20[0xe];
    uint8_t field_0x2e[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x30[0xf0];
    uint8_t field_0x120[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_att_accept_locals__stack_1196, field_0x1e) == 0x1e, "g1_layout_bt_att_accept_locals__stack_1196.field_0x1e");
_Static_assert(offsetof(struct g1_layout_bt_att_accept_locals__stack_1196, field_0x2e) == 0x2e, "g1_layout_bt_att_accept_locals__stack_1196.field_0x2e");
_Static_assert(offsetof(struct g1_layout_bt_att_accept_locals__stack_1196, field_0x120) == 0x120, "g1_layout_bt_att_accept_locals__stack_1196.field_0x120");
_Static_assert(sizeof(struct g1_layout_bt_att_accept_locals__stack_1196) >= 0x124, "g1_layout_bt_att_accept_locals__stack_1196.size");

/* stack_1197 | library | Stack local (local_20) in bt_att_accept: on-stack channel/context object populated before the accept path (two early words + a block at 0x28-0x34). | D1+D2 verified
 * review: Stack frame consistent with an on-stack ATT channel init; layout config-dependent, unverified. */
struct __attribute__((packed)) g1_layout_bt_att_accept_local__stack_1197 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x1c];
    uint8_t field_0x28[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x2c[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x30[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x34[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_bt_att_accept_local__stack_1197, field_0x4) == 0x4, "g1_layout_bt_att_accept_local__stack_1197.field_0x4");
_Static_assert(offsetof(struct g1_layout_bt_att_accept_local__stack_1197, field_0x8) == 0x8, "g1_layout_bt_att_accept_local__stack_1197.field_0x8");
_Static_assert(offsetof(struct g1_layout_bt_att_accept_local__stack_1197, field_0x28) == 0x28, "g1_layout_bt_att_accept_local__stack_1197.field_0x28");
_Static_assert(offsetof(struct g1_layout_bt_att_accept_local__stack_1197, field_0x2c) == 0x2c, "g1_layout_bt_att_accept_local__stack_1197.field_0x2c");
_Static_assert(offsetof(struct g1_layout_bt_att_accept_local__stack_1197, field_0x30) == 0x30, "g1_layout_bt_att_accept_local__stack_1197.field_0x30");
_Static_assert(offsetof(struct g1_layout_bt_att_accept_local__stack_1197, field_0x34) == 0x34, "g1_layout_bt_att_accept_local__stack_1197.field_0x34");
_Static_assert(sizeof(struct g1_layout_bt_att_accept_local__stack_1197) >= 0x38, "g1_layout_bt_att_accept_local__stack_1197.size");

/* stack_1202 | G1-original | Stack-local ATT Read-By-Group-Type request scratch bytes in att_read_group_req. | D1+D2 verified
 * review: Function-local PDU scratch (local_44); not a distinct library struct, so is_library=false. */
struct __attribute__((packed)) g1_layout_att_read_group_req_locals__stack_1202 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_att_read_group_req_locals__stack_1202, field_0x0) == 0x0, "g1_layout_att_read_group_req_locals__stack_1202.field_0x0");
_Static_assert(offsetof(struct g1_layout_att_read_group_req_locals__stack_1202, field_0x2) == 0x2, "g1_layout_att_read_group_req_locals__stack_1202.field_0x2");
_Static_assert(sizeof(struct g1_layout_att_read_group_req_locals__stack_1202) >= 0x3, "g1_layout_att_read_group_req_locals__stack_1202.size");

/* stack_1205 | G1-original | Stack-local pair of index words in FUN_0005929c. | D1+D2 verified
 * review: Single-cid stack local in an unnamed function. Offsets kept. */
struct __attribute__((packed)) g1_layout_fun_0005929c_locals__stack_1205 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_fun_0005929c_locals__stack_1205, field_0x0) == 0x0, "g1_layout_fun_0005929c_locals__stack_1205.field_0x0");
_Static_assert(offsetof(struct g1_layout_fun_0005929c_locals__stack_1205, field_0x8) == 0x8, "g1_layout_fun_0005929c_locals__stack_1205.field_0x8");
_Static_assert(sizeof(struct g1_layout_fun_0005929c_locals__stack_1205) >= 0xc, "g1_layout_fun_0005929c_locals__stack_1205.size");

/* stack_1207 | G1-original | Stack-local scratch pair (local_30) inside FUN_00059344. | D1+D2 verified
 * review: Function-local, low signal; offsets unchanged. */
struct __attribute__((packed)) g1_layout_unk_stack_1207__stack_1207 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_unk_stack_1207__stack_1207, field_0x0) == 0x0, "g1_layout_unk_stack_1207__stack_1207.field_0x0");
_Static_assert(offsetof(struct g1_layout_unk_stack_1207__stack_1207, field_0x8) == 0x8, "g1_layout_unk_stack_1207__stack_1207.field_0x8");
_Static_assert(sizeof(struct g1_layout_unk_stack_1207__stack_1207) >= 0xc, "g1_layout_unk_stack_1207__stack_1207.size");

/* stack_1212 | G1-original | Local fragment in att_find_type_req (local_38): an attribute-type byte plus a second byte. | D1+D2 verified
 * review: Function is library-class (att_find_type_req) but this is a per-function stack local, not a stock struct type. Two idx1 bytes. */
struct __attribute__((packed)) g1_layout_att_find_type_req_locals__stack_1212 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_att_find_type_req_locals__stack_1212, field_0x0) == 0x0, "g1_layout_att_find_type_req_locals__stack_1212.field_0x0");
_Static_assert(offsetof(struct g1_layout_att_find_type_req_locals__stack_1212, field_0x2) == 0x2, "g1_layout_att_find_type_req_locals__stack_1212.field_0x2");
_Static_assert(sizeof(struct g1_layout_att_find_type_req_locals__stack_1212) >= 0x3, "g1_layout_att_find_type_req_locals__stack_1212.size");

/* stack_1219 | G1-original | Stack-local start/end handle pair in bt_gatt_foreach_attr_type. | D1+D2 verified
 * review: Corrected sonnet's is_library=True: this is a function-local frame (temporaries), not a stock struct. is_library=false. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_gatt_foreach_attr_locals__stack_1219 {
    uint8_t start_handle[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x4];
    uint8_t end_handle[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_foreach_attr_locals__stack_1219, start_handle) == 0x0, "g1_layout_gatt_foreach_attr_locals__stack_1219.start_handle");
_Static_assert(offsetof(struct g1_layout_gatt_foreach_attr_locals__stack_1219, end_handle) == 0x6, "g1_layout_gatt_foreach_attr_locals__stack_1219.end_handle");
_Static_assert(sizeof(struct g1_layout_gatt_foreach_attr_locals__stack_1219) >= 0x8, "g1_layout_gatt_foreach_attr_locals__stack_1219.size");

/* stack_1224 | G1-original | Stack-local flag bytes (local_28) in bt_gatt_indicate. | D1+D2 verified
 * review: Local scratch, not a stock struct (corrected sonnet is_library=true). Kept offsets. */
struct __attribute__((packed)) g1_layout_bt_gatt_indicate_locals__stack_1224 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_indicate_locals__stack_1224, field_0x0) == 0x0, "g1_layout_bt_gatt_indicate_locals__stack_1224.field_0x0");
_Static_assert(offsetof(struct g1_layout_bt_gatt_indicate_locals__stack_1224, field_0x2) == 0x2, "g1_layout_bt_gatt_indicate_locals__stack_1224.field_0x2");
_Static_assert(sizeof(struct g1_layout_bt_gatt_indicate_locals__stack_1224) >= 0x3, "g1_layout_bt_gatt_indicate_locals__stack_1224.size");

/* stack_1226 | library | Stack-local pair of bytes in bt_gatt_notify_cb, likely a result/error code and a state/flags byte. | D1+D2 verified
 * review: Function-local scratch inside a host GATT function, not a named struct; library_verified=false. */
struct __attribute__((packed)) g1_layout_gatt_notify_cb_locals__stack_1226 {
    uint8_t result_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t state_byte[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_notify_cb_locals__stack_1226, result_byte) == 0x0, "g1_layout_gatt_notify_cb_locals__stack_1226.result_byte");
_Static_assert(offsetof(struct g1_layout_gatt_notify_cb_locals__stack_1226, state_byte) == 0x2, "g1_layout_gatt_notify_cb_locals__stack_1226.state_byte");
_Static_assert(sizeof(struct g1_layout_gatt_notify_cb_locals__stack_1226) >= 0x3, "g1_layout_gatt_notify_cb_locals__stack_1226.size");

/* stack_1228 | G1-original | Stack scratch pair in bt_gatt_discover while iterating ATT discovery responses. | D1+D2 verified
 * review: Function-local frame inside a library function; not the library struct itself, so is_library=false. */
struct __attribute__((packed)) g1_layout_gatt_discover_locals__stack_1228 {
    uint8_t attr_type_or_flag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t attr_len_or_flag[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_discover_locals__stack_1228, attr_type_or_flag) == 0x0, "g1_layout_gatt_discover_locals__stack_1228.attr_type_or_flag");
_Static_assert(offsetof(struct g1_layout_gatt_discover_locals__stack_1228, attr_len_or_flag) == 0x2, "g1_layout_gatt_discover_locals__stack_1228.attr_len_or_flag");
_Static_assert(sizeof(struct g1_layout_gatt_discover_locals__stack_1228) >= 0x3, "g1_layout_gatt_discover_locals__stack_1228.size");

/* stack_1229 | G1-original | Local scratch in bt_gatt_discover holding two byte fields (state/type). | D1+D2 verified
 * review: Function-local frame, not a stock struct; is_library corrected to false. */
struct __attribute__((packed)) g1_layout_gatt_discover_locals__stack_1229 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_discover_locals__stack_1229, field_0x0) == 0x0, "g1_layout_gatt_discover_locals__stack_1229.field_0x0");
_Static_assert(offsetof(struct g1_layout_gatt_discover_locals__stack_1229, field_0x2) == 0x2, "g1_layout_gatt_discover_locals__stack_1229.field_0x2");
_Static_assert(sizeof(struct g1_layout_gatt_discover_locals__stack_1229) >= 0x3, "g1_layout_gatt_discover_locals__stack_1229.size");

/* stack_1230 | library | Stack local (local_20) in bt_gatt_discover: small parameter/state bytes for the discovery request. | D1+D2 verified
 * review: Compiler stack frame; not a public struct, unverified. */
struct __attribute__((packed)) g1_layout_bt_gatt_discover_tmp__stack_1230 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_discover_tmp__stack_1230, field_0x0) == 0x0, "g1_layout_bt_gatt_discover_tmp__stack_1230.field_0x0");
_Static_assert(offsetof(struct g1_layout_bt_gatt_discover_tmp__stack_1230, field_0x2) == 0x2, "g1_layout_bt_gatt_discover_tmp__stack_1230.field_0x2");
_Static_assert(sizeof(struct g1_layout_bt_gatt_discover_tmp__stack_1230) >= 0x3, "g1_layout_bt_gatt_discover_tmp__stack_1230.size");

/* stack_1231 | G1-original | Stack-local flag pair in bt_gatt_discover (Zephyr GATT discovery). | D1+D2 verified
 * review: Downgraded from sonnet's bt_gatt_discover_params: two local flag bytes (local_1c), not a stock struct. */
struct __attribute__((packed)) g1_layout_bt_gatt_discover_locals__stack_1231 {
    uint8_t flag_a[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t flag_b[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_discover_locals__stack_1231, flag_a) == 0x0, "g1_layout_bt_gatt_discover_locals__stack_1231.flag_a");
_Static_assert(offsetof(struct g1_layout_bt_gatt_discover_locals__stack_1231, flag_b) == 0x2, "g1_layout_bt_gatt_discover_locals__stack_1231.flag_b");
_Static_assert(sizeof(struct g1_layout_bt_gatt_discover_locals__stack_1231) >= 0x3, "g1_layout_bt_gatt_discover_locals__stack_1231.size");

/* stack_1232 | G1-original | Stack-local scratch in gatt_parse_find_by_type_rsp holding a start/end handle byte pair. | D1+D2 verified
 * review: Anonymous local frame in a GATT parser; not a named library struct → is_library=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_gatt_find_by_type_rsp_locals__stack_1232 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_find_by_type_rsp_locals__stack_1232, field_0x0) == 0x0, "g1_layout_gatt_find_by_type_rsp_locals__stack_1232.field_0x0");
_Static_assert(offsetof(struct g1_layout_gatt_find_by_type_rsp_locals__stack_1232, field_0x2) == 0x2, "g1_layout_gatt_find_by_type_rsp_locals__stack_1232.field_0x2");
_Static_assert(sizeof(struct g1_layout_gatt_find_by_type_rsp_locals__stack_1232) >= 0x3, "g1_layout_gatt_find_by_type_rsp_locals__stack_1232.size");

/* stack_1233 | G1-original | Stack-local ATT start/end handle pair (local_3c) parsed from a Find-By-Type-Value response entry in gatt_parse_find_by_type_rsp. | D1+D2 verified
 * review: Function-local parse scratch, not a stock header type; offsets unchanged. */
struct __attribute__((packed)) g1_layout_gatt_handle_range__stack_1233 {
    uint8_t start_handle[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x8];
    uint8_t end_handle[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_handle_range__stack_1233, start_handle) == 0x0, "g1_layout_gatt_handle_range__stack_1233.start_handle");
_Static_assert(offsetof(struct g1_layout_gatt_handle_range__stack_1233, end_handle) == 0xc, "g1_layout_gatt_handle_range__stack_1233.end_handle");
_Static_assert(sizeof(struct g1_layout_gatt_handle_range__stack_1233) >= 0x10, "g1_layout_gatt_handle_range__stack_1233.size");

/* stack_1234 | G1-original | Local state (length/type bytes) while parsing a GATT Read-By-Type response in gatt_parse_read_by_type_rsp (local_5c). | D1+D2 verified
 * review: Per-function stack local, not a stock struct. Two idx1 bytes. */
struct __attribute__((packed)) g1_layout_gatt_read_by_type_locals__stack_1234 {
    uint8_t elem_len[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t elem_flag[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_read_by_type_locals__stack_1234, elem_len) == 0x0, "g1_layout_gatt_read_by_type_locals__stack_1234.elem_len");
_Static_assert(offsetof(struct g1_layout_gatt_read_by_type_locals__stack_1234, elem_flag) == 0x2, "g1_layout_gatt_read_by_type_locals__stack_1234.elem_flag");
_Static_assert(sizeof(struct g1_layout_gatt_read_by_type_locals__stack_1234) >= 0x3, "g1_layout_gatt_read_by_type_locals__stack_1234.size");

/* stack_1235 | G1-original | Stack-local byte pair (entry length/flags) parsed in gatt_parse_read_by_type_rsp. | D1+D2 verified
 * review: Corrected sonnet's is_library=True: function-local temporaries, not a stock struct. is_library=false. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_read_by_type_locals__stack_1235 {
    uint8_t entry_len[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t entry_flags[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_read_by_type_locals__stack_1235, entry_len) == 0x0, "g1_layout_read_by_type_locals__stack_1235.entry_len");
_Static_assert(offsetof(struct g1_layout_read_by_type_locals__stack_1235, entry_flags) == 0x2, "g1_layout_read_by_type_locals__stack_1235.entry_flags");
_Static_assert(sizeof(struct g1_layout_read_by_type_locals__stack_1235) >= 0x3, "g1_layout_read_by_type_locals__stack_1235.size");

/* stack_1237 | G1-original | Stack-local parse cursor (local_4c) in gatt_parse_read_by_type_rsp_128 (type-length byte + following byte). | D1+D2 verified
 * review: Local scratch, not a stock struct (corrected sonnet is_library=true). Kept offsets. */
struct __attribute__((packed)) g1_layout_gatt_rbt_rsp_cursor__stack_1237 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_rbt_rsp_cursor__stack_1237, field_0x0) == 0x0, "g1_layout_gatt_rbt_rsp_cursor__stack_1237.field_0x0");
_Static_assert(offsetof(struct g1_layout_gatt_rbt_rsp_cursor__stack_1237, field_0x2) == 0x2, "g1_layout_gatt_rbt_rsp_cursor__stack_1237.field_0x2");
_Static_assert(sizeof(struct g1_layout_gatt_rbt_rsp_cursor__stack_1237) >= 0x3, "g1_layout_gatt_rbt_rsp_cursor__stack_1237.size");

/* stack_1240 | library | Stack-local ATT Find-Information-Response element in gatt_parse_find_info_rsp: a handle/format byte and a following type byte. | D1+D2 verified
 * review: Local parse scratch inside a host GATT function; not a header struct, library_verified=false. */
struct __attribute__((packed)) g1_layout_gatt_find_info_elem__stack_1240 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_gatt_find_info_elem__stack_1240, field_0x0) == 0x0, "g1_layout_gatt_find_info_elem__stack_1240.field_0x0");
_Static_assert(offsetof(struct g1_layout_gatt_find_info_elem__stack_1240, field_0x2) == 0x2, "g1_layout_gatt_find_info_elem__stack_1240.field_0x2");
_Static_assert(sizeof(struct g1_layout_gatt_find_info_elem__stack_1240) >= 0x3, "g1_layout_gatt_find_info_elem__stack_1240.size");

/* stack_1241 | G1-original | Stack (format,count) pair parsed from an ATT Find Information Response in gatt_parse_find_info_rsp. | D1+D2 verified
 * review: Function-local frame; is_library=false. */
struct __attribute__((packed)) g1_layout_find_info_rsp_locals__stack_1241 {
    uint8_t fmt[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t count_or_len[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_find_info_rsp_locals__stack_1241, fmt) == 0x0, "g1_layout_find_info_rsp_locals__stack_1241.fmt");
_Static_assert(offsetof(struct g1_layout_find_info_rsp_locals__stack_1241, count_or_len) == 0x2, "g1_layout_find_info_rsp_locals__stack_1241.count_or_len");
_Static_assert(sizeof(struct g1_layout_find_info_rsp_locals__stack_1241) >= 0x3, "g1_layout_find_info_rsp_locals__stack_1241.size");

/* stack_1248 | G1-original | Local 0x24-byte buffer in smp_dhkey_check_generate (two chained values at start/end). | D1+D2 verified
 * review: Stack buffer local, not a stock struct; is_library corrected to false. */
struct __attribute__((packed)) g1_layout_smp_dhkey_check_buf__stack_1248 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x1c];
    uint8_t field_0x20[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_smp_dhkey_check_buf__stack_1248, field_0x0) == 0x0, "g1_layout_smp_dhkey_check_buf__stack_1248.field_0x0");
_Static_assert(offsetof(struct g1_layout_smp_dhkey_check_buf__stack_1248, field_0x20) == 0x20, "g1_layout_smp_dhkey_check_buf__stack_1248.field_0x20");
_Static_assert(sizeof(struct g1_layout_smp_dhkey_check_buf__stack_1248) >= 0x24, "g1_layout_smp_dhkey_check_buf__stack_1248.size");

/* stack_1249 | library | Stack local (local_38) in smp_pairing_req: partial view of an SMP pairing-request PDU (io_capability byte at 0, key-distribution/reserved word at 0x10). | D1+D2 verified
 * review: On-stack SMP PDU fragment; too sparse to verify against bt_smp_pairing. */
struct __attribute__((packed)) g1_layout_smp_pairing_req_local__stack_1249 {
    uint8_t io_capability[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0xf];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_smp_pairing_req_local__stack_1249, io_capability) == 0x0, "g1_layout_smp_pairing_req_local__stack_1249.io_capability");
_Static_assert(offsetof(struct g1_layout_smp_pairing_req_local__stack_1249, field_0x10) == 0x10, "g1_layout_smp_pairing_req_local__stack_1249.field_0x10");
_Static_assert(sizeof(struct g1_layout_smp_pairing_req_local__stack_1249) >= 0x14, "g1_layout_smp_pairing_req_local__stack_1249.size");

/* stack_1273 | G1-original | Stack-local PDM microphone event data in pdm_mic_event_handler: a buffer pointer/index and a size/status word. | D1+D2 verified
 * review: G1-original function-local scratch (local_30). */
struct __attribute__((packed)) g1_layout_pdm_mic_event_data__stack_1273 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0xc];
    uint8_t field_0x10[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_pdm_mic_event_data__stack_1273, field_0x0) == 0x0, "g1_layout_pdm_mic_event_data__stack_1273.field_0x0");
_Static_assert(offsetof(struct g1_layout_pdm_mic_event_data__stack_1273, field_0x10) == 0x10, "g1_layout_pdm_mic_event_data__stack_1273.field_0x10");
_Static_assert(sizeof(struct g1_layout_pdm_mic_event_data__stack_1273) >= 0x14, "g1_layout_pdm_mic_event_data__stack_1273.size");

/* stack_1277 | G1-original | Stack-local pair of 16-bit indices used during panel temperature calibration init. | D1+D2 verified
 * review: Single-cid stack local. Offsets kept. */
struct __attribute__((packed)) g1_layout_panel_temp_calibration_locals__stack_1277 {
    uint8_t field_0x0[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x4];
    uint8_t field_0x6[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_panel_temp_calibration_locals__stack_1277, field_0x0) == 0x0, "g1_layout_panel_temp_calibration_locals__stack_1277.field_0x0");
_Static_assert(offsetof(struct g1_layout_panel_temp_calibration_locals__stack_1277, field_0x6) == 0x6, "g1_layout_panel_temp_calibration_locals__stack_1277.field_0x6");
_Static_assert(sizeof(struct g1_layout_panel_temp_calibration_locals__stack_1277) >= 0x8, "g1_layout_panel_temp_calibration_locals__stack_1277.size");

/* stack_1278 | G1-original | Stack-local status/error scratch bytes (local_2c) inside uarte_nrfx_isr. | D1+D2 verified
 * review: Function-local; offsets unchanged. */
struct __attribute__((packed)) g1_layout_uarte_isr_scratch__stack_1278 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x3];
    uint8_t field_0x4[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_uarte_isr_scratch__stack_1278, field_0x0) == 0x0, "g1_layout_uarte_isr_scratch__stack_1278.field_0x0");
_Static_assert(offsetof(struct g1_layout_uarte_isr_scratch__stack_1278, field_0x4) == 0x4, "g1_layout_uarte_isr_scratch__stack_1278.field_0x4");
_Static_assert(sizeof(struct g1_layout_uarte_isr_scratch__stack_1278) >= 0x5, "g1_layout_uarte_isr_scratch__stack_1278.size");

/* stack_1292 | G1-original | cJSON serialization local (printbuffer/format state) inside cjson_print_value (local_40). | D1+D2 verified
 * review: Per-function stack local, not a stock struct. Two idx2 halfwords. */
struct __attribute__((packed)) g1_layout_cjson_print_value_locals__stack_1292 {
    uint8_t format_flags[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x1a];
    uint8_t trailing_field[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_cjson_print_value_locals__stack_1292, format_flags) == 0x0, "g1_layout_cjson_print_value_locals__stack_1292.format_flags");
_Static_assert(offsetof(struct g1_layout_cjson_print_value_locals__stack_1292, trailing_field) == 0x1c, "g1_layout_cjson_print_value_locals__stack_1292.trailing_field");
_Static_assert(sizeof(struct g1_layout_cjson_print_value_locals__stack_1292) >= 0x1e, "g1_layout_cjson_print_value_locals__stack_1292.size");

/* stack_1302 | G1-original | Stack-local scratch bytes (pin index and trigger mode) in gpiote_trigger_enable. | D1+D2 verified
 * review: Function-local; kept naming, offsets unchanged. */
struct __attribute__((packed)) g1_layout_gpiote_trigger_locals__stack_1302 {
    uint8_t pin_idx[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x4];
    uint8_t trigger_mode[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_gpiote_trigger_locals__stack_1302, pin_idx) == 0x0, "g1_layout_gpiote_trigger_locals__stack_1302.pin_idx");
_Static_assert(offsetof(struct g1_layout_gpiote_trigger_locals__stack_1302, trigger_mode) == 0x5, "g1_layout_gpiote_trigger_locals__stack_1302.trigger_mode");
_Static_assert(sizeof(struct g1_layout_gpiote_trigger_locals__stack_1302) >= 0x6, "g1_layout_gpiote_trigger_locals__stack_1302.size");

/* stack_1312 | G1-original | Stack-local GPIOTE event info (local_30) in gpiote_irq_handler (pin/event pair + third word). | D1+D2 verified
 * review: Local scratch; kept offsets. */
struct __attribute__((packed)) g1_layout_gpiote_evt_info__stack_1312 {
    uint8_t pin[0x4]; /* catalog type: uint32_t */
    uint8_t event_or_action[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x4];
    uint8_t field_0xc[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_gpiote_evt_info__stack_1312, pin) == 0x0, "g1_layout_gpiote_evt_info__stack_1312.pin");
_Static_assert(offsetof(struct g1_layout_gpiote_evt_info__stack_1312, event_or_action) == 0x4, "g1_layout_gpiote_evt_info__stack_1312.event_or_action");
_Static_assert(offsetof(struct g1_layout_gpiote_evt_info__stack_1312, field_0xc) == 0xc, "g1_layout_gpiote_evt_info__stack_1312.field_0xc");
_Static_assert(sizeof(struct g1_layout_gpiote_evt_info__stack_1312) >= 0x10, "g1_layout_gpiote_evt_info__stack_1312.size");

/* stack_1351 | G1-original | Stack-local pair of bytes used inside nrfx_twim_irq_handler while servicing a TWIM interrupt (event/status bytes). | D1+D2 verified
 * review: Function-local scratch, not a named struct; corrected sonnet is_library=True to False. */
struct __attribute__((packed)) g1_layout_nrfx_twim_irq_locals__stack_1351 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x3];
    uint8_t field_0x4[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_nrfx_twim_irq_locals__stack_1351, field_0x0) == 0x0, "g1_layout_nrfx_twim_irq_locals__stack_1351.field_0x0");
_Static_assert(offsetof(struct g1_layout_nrfx_twim_irq_locals__stack_1351, field_0x4) == 0x4, "g1_layout_nrfx_twim_irq_locals__stack_1351.field_0x4");
_Static_assert(sizeof(struct g1_layout_nrfx_twim_irq_locals__stack_1351) >= 0x5, "g1_layout_nrfx_twim_irq_locals__stack_1351.size");

/* stack_1356 | G1-original | Five int32 energy/attack-detection metrics in lc3_attdet_run (local_58). | D1+D2 verified
 * review: LC3 codec local scratch; not a named liblc3 struct. Corrected is_library to false. Footprint collision. SEPARATE. */
struct __attribute__((packed)) g1_layout_lc3_attdet_scratch5__stack_1356 {
    uint8_t e0[0x4]; /* catalog type: int32_t */
    uint8_t e1[0x4]; /* catalog type: int32_t */
    uint8_t e2[0x4]; /* catalog type: int32_t */
    uint8_t e3[0x4]; /* catalog type: int32_t */
    uint8_t e4[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_attdet_scratch5__stack_1356, e0) == 0x0, "g1_layout_lc3_attdet_scratch5__stack_1356.e0");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_scratch5__stack_1356, e1) == 0x4, "g1_layout_lc3_attdet_scratch5__stack_1356.e1");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_scratch5__stack_1356, e2) == 0x8, "g1_layout_lc3_attdet_scratch5__stack_1356.e2");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_scratch5__stack_1356, e3) == 0xc, "g1_layout_lc3_attdet_scratch5__stack_1356.e3");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_scratch5__stack_1356, e4) == 0x10, "g1_layout_lc3_attdet_scratch5__stack_1356.e4");
_Static_assert(sizeof(struct g1_layout_lc3_attdet_scratch5__stack_1356) >= 0x14, "g1_layout_lc3_attdet_scratch5__stack_1356.size");

/* stack_1357 | G1-original | Second five-word scratch in lc3_attdet_run (local_48). | D1+D2 verified
 * review: LC3 local scratch, not a stock struct. is_library corrected to false. SEPARATE. */
struct __attribute__((packed)) g1_layout_lc3_attdet_scratch5_b__stack_1357 {
    uint8_t v0[0x4]; /* catalog type: uint32_t */
    uint8_t v1[0x4]; /* catalog type: uint32_t */
    uint8_t v2[0x4]; /* catalog type: uint32_t */
    uint8_t v3[0x4]; /* catalog type: uint32_t */
    uint8_t v4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_attdet_scratch5_b__stack_1357, v0) == 0x0, "g1_layout_lc3_attdet_scratch5_b__stack_1357.v0");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_scratch5_b__stack_1357, v1) == 0x4, "g1_layout_lc3_attdet_scratch5_b__stack_1357.v1");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_scratch5_b__stack_1357, v2) == 0x8, "g1_layout_lc3_attdet_scratch5_b__stack_1357.v2");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_scratch5_b__stack_1357, v3) == 0xc, "g1_layout_lc3_attdet_scratch5_b__stack_1357.v3");
_Static_assert(offsetof(struct g1_layout_lc3_attdet_scratch5_b__stack_1357, v4) == 0x10, "g1_layout_lc3_attdet_scratch5_b__stack_1357.v4");
_Static_assert(sizeof(struct g1_layout_lc3_attdet_scratch5_b__stack_1357) >= 0x14, "g1_layout_lc3_attdet_scratch5_b__stack_1357.size");

/* stack_1359 | G1-original | Stack-local array of subband energy accumulators in the LC3 bandwidth detector lc3_bwdet_run (afStack_30). | D1+D2 verified
 * review: Function-local float array (Ghidra af-prefix). Not the library struct type itself, so is_library=false; is_array=true. Gap at 0x10 kept as observed. */
struct __attribute__((packed)) g1_layout_lc3_bwdet_energy_array__stack_1359 {
    uint8_t energy_0[0x4]; /* catalog type: float */
    uint8_t energy_1[0x4]; /* catalog type: float */
    uint8_t energy_2[0x4]; /* catalog type: float */
    uint8_t energy_3[0x4]; /* catalog type: float */
    uint8_t _pad_0x10[0x4];
    uint8_t energy_4[0x4]; /* catalog type: float */
};
_Static_assert(offsetof(struct g1_layout_lc3_bwdet_energy_array__stack_1359, energy_0) == 0x0, "g1_layout_lc3_bwdet_energy_array__stack_1359.energy_0");
_Static_assert(offsetof(struct g1_layout_lc3_bwdet_energy_array__stack_1359, energy_1) == 0x4, "g1_layout_lc3_bwdet_energy_array__stack_1359.energy_1");
_Static_assert(offsetof(struct g1_layout_lc3_bwdet_energy_array__stack_1359, energy_2) == 0x8, "g1_layout_lc3_bwdet_energy_array__stack_1359.energy_2");
_Static_assert(offsetof(struct g1_layout_lc3_bwdet_energy_array__stack_1359, energy_3) == 0xc, "g1_layout_lc3_bwdet_energy_array__stack_1359.energy_3");
_Static_assert(offsetof(struct g1_layout_lc3_bwdet_energy_array__stack_1359, energy_4) == 0x14, "g1_layout_lc3_bwdet_energy_array__stack_1359.energy_4");
_Static_assert(sizeof(struct g1_layout_lc3_bwdet_energy_array__stack_1359) >= 0x18, "g1_layout_lc3_bwdet_energy_array__stack_1359.size");

/* stack_1361 | G1-original | Local three-accumulator array in lc3_energy_compute (spectral energy). | D1+D2 verified
 * review: LC3 function-local scratch, not a stock struct; is_library corrected to false. */
struct __attribute__((packed)) g1_layout_lc3_energy_locals__stack_1361 {
    uint8_t energy_0[0x4]; /* catalog type: uint32_t */
    uint8_t energy_1[0x4]; /* catalog type: uint32_t */
    uint8_t energy_2[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_energy_locals__stack_1361, energy_0) == 0x0, "g1_layout_lc3_energy_locals__stack_1361.energy_0");
_Static_assert(offsetof(struct g1_layout_lc3_energy_locals__stack_1361, energy_1) == 0x4, "g1_layout_lc3_energy_locals__stack_1361.energy_1");
_Static_assert(offsetof(struct g1_layout_lc3_energy_locals__stack_1361, energy_2) == 0x8, "g1_layout_lc3_energy_locals__stack_1361.energy_2");
_Static_assert(sizeof(struct g1_layout_lc3_energy_locals__stack_1361) >= 0xc, "g1_layout_lc3_energy_locals__stack_1361.size");

/* stack_1370 | library | Stack local (local_1b0) in lc3_ltpf_detect_pitch: LC3 long-term pitch prediction working buffer (correlation/energy array). | D1+D2 verified
 * review: Working buffer within a liblc3 routine; array-like, unverified. */
struct __attribute__((packed)) g1_layout_lc3_ltpf_pitch_buf__stack_1370 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x188];
    uint8_t field_0x18c[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_ltpf_pitch_buf__stack_1370, field_0x0) == 0x0, "g1_layout_lc3_ltpf_pitch_buf__stack_1370.field_0x0");
_Static_assert(offsetof(struct g1_layout_lc3_ltpf_pitch_buf__stack_1370, field_0x18c) == 0x18c, "g1_layout_lc3_ltpf_pitch_buf__stack_1370.field_0x18c");
_Static_assert(sizeof(struct g1_layout_lc3_ltpf_pitch_buf__stack_1370) >= 0x190, "g1_layout_lc3_ltpf_pitch_buf__stack_1370.size");

/* stack_1373 | G1-original | Stack-local scratch in lc3_ltpf_analyse (LC3 Long-Term Postfilter analysis) holding pitch-lag/gain/correlation intermediates. | D1+D2 verified
 * review: Function-local scratch (local_7c); an aggregate of temporaries, not a named library type. */
struct __attribute__((packed)) g1_layout_lc3_ltpf_locals__stack_1373 {
    uint8_t pitch_lag[0x4]; /* catalog type: uint32_t */
    uint8_t gain[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x8[0x4];
    uint8_t correlation[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_ltpf_locals__stack_1373, pitch_lag) == 0x0, "g1_layout_lc3_ltpf_locals__stack_1373.pitch_lag");
_Static_assert(offsetof(struct g1_layout_lc3_ltpf_locals__stack_1373, gain) == 0x4, "g1_layout_lc3_ltpf_locals__stack_1373.gain");
_Static_assert(offsetof(struct g1_layout_lc3_ltpf_locals__stack_1373, correlation) == 0xc, "g1_layout_lc3_ltpf_locals__stack_1373.correlation");
_Static_assert(sizeof(struct g1_layout_lc3_ltpf_locals__stack_1373) >= 0x10, "g1_layout_lc3_ltpf_locals__stack_1373.size");

/* stack_1374 | G1-original | Stack-local float array (autocorrelation/pitch buffer) used by lc3_ltpf_analyse during LC3 long-term post-filter analysis. | D1+D2 verified
 * review: Anonymous local afStack_70 float array (not a named struct) → is_library=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_lc3_ltpf_analyse_locals__stack_1374 {
    uint8_t _pad_0x0[0xc];
    uint8_t buf_elem_0[0x4]; /* catalog type: float */
    uint8_t _pad_0x10[0x34];
    uint8_t buf_elem_last[0x4]; /* catalog type: float */
};
_Static_assert(offsetof(struct g1_layout_lc3_ltpf_analyse_locals__stack_1374, buf_elem_0) == 0xc, "g1_layout_lc3_ltpf_analyse_locals__stack_1374.buf_elem_0");
_Static_assert(offsetof(struct g1_layout_lc3_ltpf_analyse_locals__stack_1374, buf_elem_last) == 0x44, "g1_layout_lc3_ltpf_analyse_locals__stack_1374.buf_elem_last");
_Static_assert(sizeof(struct g1_layout_lc3_ltpf_analyse_locals__stack_1374) >= 0x48, "g1_layout_lc3_ltpf_analyse_locals__stack_1374.size");

/* stack_1375 | G1-original | Stack-local FFT workspace params (local_60) inside lc3_mdct_fft (size/scale/data-pointer). | D1+D2 verified
 * review: Function-local liblc3 scratch; offsets unchanged. */
struct __attribute__((packed)) g1_layout_lc3_mdct_fft_workspace__stack_1375 {
    uint8_t fft_n[0x4]; /* catalog type: int32_t */
    uint8_t fft_scale[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x8[0x4];
    uint8_t fft_data_ptr[0x4]; /* catalog type: void * */
};
_Static_assert(offsetof(struct g1_layout_lc3_mdct_fft_workspace__stack_1375, fft_n) == 0x0, "g1_layout_lc3_mdct_fft_workspace__stack_1375.fft_n");
_Static_assert(offsetof(struct g1_layout_lc3_mdct_fft_workspace__stack_1375, fft_scale) == 0x4, "g1_layout_lc3_mdct_fft_workspace__stack_1375.fft_scale");
_Static_assert(offsetof(struct g1_layout_lc3_mdct_fft_workspace__stack_1375, fft_data_ptr) == 0xc, "g1_layout_lc3_mdct_fft_workspace__stack_1375.fft_data_ptr");
_Static_assert(sizeof(struct g1_layout_lc3_mdct_fft_workspace__stack_1375) >= 0x10, "g1_layout_lc3_mdct_fft_workspace__stack_1375.size");

/* stack_1377 | library | Stack-local array of six spectral-shaping coefficients used in lc3_sns_spectral_shaping (LC3 SNS quantization). | D1+D2 verified
 * review: Split out of the param_0023 footprint-collision group — a 6-word local array, not a k_sem or cJSON buffer. liblc3 internal, no pinned header to verify offsets against. */
struct __attribute__((packed)) g1_layout_lc3_sns_shaping_coeffs__stack_1377 {
    uint8_t coeff_0[0x4]; /* catalog type: int32_t */
    uint8_t coeff_1[0x4]; /* catalog type: int32_t */
    uint8_t coeff_2[0x4]; /* catalog type: int32_t */
    uint8_t coeff_3[0x4]; /* catalog type: int32_t */
    uint8_t coeff_4[0x4]; /* catalog type: int32_t */
    uint8_t coeff_5[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_sns_shaping_coeffs__stack_1377, coeff_0) == 0x0, "g1_layout_lc3_sns_shaping_coeffs__stack_1377.coeff_0");
_Static_assert(offsetof(struct g1_layout_lc3_sns_shaping_coeffs__stack_1377, coeff_1) == 0x4, "g1_layout_lc3_sns_shaping_coeffs__stack_1377.coeff_1");
_Static_assert(offsetof(struct g1_layout_lc3_sns_shaping_coeffs__stack_1377, coeff_2) == 0x8, "g1_layout_lc3_sns_shaping_coeffs__stack_1377.coeff_2");
_Static_assert(offsetof(struct g1_layout_lc3_sns_shaping_coeffs__stack_1377, coeff_3) == 0xc, "g1_layout_lc3_sns_shaping_coeffs__stack_1377.coeff_3");
_Static_assert(offsetof(struct g1_layout_lc3_sns_shaping_coeffs__stack_1377, coeff_4) == 0x10, "g1_layout_lc3_sns_shaping_coeffs__stack_1377.coeff_4");
_Static_assert(offsetof(struct g1_layout_lc3_sns_shaping_coeffs__stack_1377, coeff_5) == 0x14, "g1_layout_lc3_sns_shaping_coeffs__stack_1377.coeff_5");
_Static_assert(sizeof(struct g1_layout_lc3_sns_shaping_coeffs__stack_1377) >= 0x18, "g1_layout_lc3_sns_shaping_coeffs__stack_1377.size");

/* stack_1378 | G1-original | Five-word SNS analysis scratch in lc3_sns_analyze (local_2e8). | D1+D2 verified
 * review: LC3 SNS local scratch, not a stock struct. is_library corrected to false. SEPARATE. */
struct __attribute__((packed)) g1_layout_lc3_sns_scratch5__stack_1378 {
    uint8_t v0[0x4]; /* catalog type: uint32_t */
    uint8_t v1[0x4]; /* catalog type: uint32_t */
    uint8_t v2[0x4]; /* catalog type: uint32_t */
    uint8_t v3[0x4]; /* catalog type: uint32_t */
    uint8_t v4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_sns_scratch5__stack_1378, v0) == 0x0, "g1_layout_lc3_sns_scratch5__stack_1378.v0");
_Static_assert(offsetof(struct g1_layout_lc3_sns_scratch5__stack_1378, v1) == 0x4, "g1_layout_lc3_sns_scratch5__stack_1378.v1");
_Static_assert(offsetof(struct g1_layout_lc3_sns_scratch5__stack_1378, v2) == 0x8, "g1_layout_lc3_sns_scratch5__stack_1378.v2");
_Static_assert(offsetof(struct g1_layout_lc3_sns_scratch5__stack_1378, v3) == 0xc, "g1_layout_lc3_sns_scratch5__stack_1378.v3");
_Static_assert(offsetof(struct g1_layout_lc3_sns_scratch5__stack_1378, v4) == 0x10, "g1_layout_lc3_sns_scratch5__stack_1378.v4");
_Static_assert(sizeof(struct g1_layout_lc3_sns_scratch5__stack_1378) >= 0x14, "g1_layout_lc3_sns_scratch5__stack_1378.size");

/* stack_1379 | G1-original | Second five-word band-energy scratch in lc3_sns_analyze (local_2a8). | D1+D2 verified
 * review: LC3 SNS local scratch. is_library corrected to false. SEPARATE. */
struct __attribute__((packed)) g1_layout_lc3_sns_scratch5_b__stack_1379 {
    uint8_t v0[0x4]; /* catalog type: uint32_t */
    uint8_t v1[0x4]; /* catalog type: uint32_t */
    uint8_t v2[0x4]; /* catalog type: uint32_t */
    uint8_t v3[0x4]; /* catalog type: uint32_t */
    uint8_t v4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_sns_scratch5_b__stack_1379, v0) == 0x0, "g1_layout_lc3_sns_scratch5_b__stack_1379.v0");
_Static_assert(offsetof(struct g1_layout_lc3_sns_scratch5_b__stack_1379, v1) == 0x4, "g1_layout_lc3_sns_scratch5_b__stack_1379.v1");
_Static_assert(offsetof(struct g1_layout_lc3_sns_scratch5_b__stack_1379, v2) == 0x8, "g1_layout_lc3_sns_scratch5_b__stack_1379.v2");
_Static_assert(offsetof(struct g1_layout_lc3_sns_scratch5_b__stack_1379, v3) == 0xc, "g1_layout_lc3_sns_scratch5_b__stack_1379.v3");
_Static_assert(offsetof(struct g1_layout_lc3_sns_scratch5_b__stack_1379, v4) == 0x10, "g1_layout_lc3_sns_scratch5_b__stack_1379.v4");
_Static_assert(sizeof(struct g1_layout_lc3_sns_scratch5_b__stack_1379) >= 0x14, "g1_layout_lc3_sns_scratch5_b__stack_1379.size");

/* stack_1380 | G1-original | Local 0xfc-byte SNS analysis buffer in lc3_sns_analyze (local_268): leading index and trailing result. | D1+D2 verified
 * review: Per-function stack scratch buffer, not a stock struct. Two idx4 words observed. */
struct __attribute__((packed)) g1_layout_lc3_sns_analyze_buf__stack_1380 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0xf4];
    uint8_t field_0xf8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_sns_analyze_buf__stack_1380, field_0x0) == 0x0, "g1_layout_lc3_sns_analyze_buf__stack_1380.field_0x0");
_Static_assert(offsetof(struct g1_layout_lc3_sns_analyze_buf__stack_1380, field_0xf8) == 0xf8, "g1_layout_lc3_sns_analyze_buf__stack_1380.field_0xf8");
_Static_assert(sizeof(struct g1_layout_lc3_sns_analyze_buf__stack_1380) >= 0xfc, "g1_layout_lc3_sns_analyze_buf__stack_1380.size");

/* stack_1382 | library | Large stack-local array (65 words, 0x104 bytes) of spectral/energy coefficients read during lc3_sns_analyze (LC3 SNS analysis). | D1+D2 verified
 * review: Function-local uniform working array (idx4 reads). Kept as array; offsets unchanged. Not a fixed liblc3 struct; library_verified=false. */
struct __attribute__((packed)) g1_layout_lc3_sns_analysis_buffer__stack_1382 {
    uint8_t coef_0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x3c];
    uint8_t coef_16[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x44[0x3c];
    uint8_t coef_32[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x84[0x3c];
    uint8_t coef_48[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc4[0x3c];
    uint8_t coef_64[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_sns_analysis_buffer__stack_1382, coef_0) == 0x0, "g1_layout_lc3_sns_analysis_buffer__stack_1382.coef_0");
_Static_assert(offsetof(struct g1_layout_lc3_sns_analysis_buffer__stack_1382, coef_16) == 0x40, "g1_layout_lc3_sns_analysis_buffer__stack_1382.coef_16");
_Static_assert(offsetof(struct g1_layout_lc3_sns_analysis_buffer__stack_1382, coef_32) == 0x80, "g1_layout_lc3_sns_analysis_buffer__stack_1382.coef_32");
_Static_assert(offsetof(struct g1_layout_lc3_sns_analysis_buffer__stack_1382, coef_48) == 0xc0, "g1_layout_lc3_sns_analysis_buffer__stack_1382.coef_48");
_Static_assert(offsetof(struct g1_layout_lc3_sns_analysis_buffer__stack_1382, coef_64) == 0x100, "g1_layout_lc3_sns_analysis_buffer__stack_1382.coef_64");
_Static_assert(sizeof(struct g1_layout_lc3_sns_analysis_buffer__stack_1382) >= 0x104, "g1_layout_lc3_sns_analysis_buffer__stack_1382.size");

/* stack_1385 | G1-original | Five-word spectral-analysis workspace in lc3_spec_analyze (local_6c). | D1+D2 verified
 * review: LC3 local scratch. is_library corrected to false. SEPARATE. */
struct __attribute__((packed)) g1_layout_lc3_spec_scratch5__stack_1385 {
    uint8_t v0[0x4]; /* catalog type: uint32_t */
    uint8_t v1[0x4]; /* catalog type: uint32_t */
    uint8_t v2[0x4]; /* catalog type: uint32_t */
    uint8_t v3[0x4]; /* catalog type: uint32_t */
    uint8_t v4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_spec_scratch5__stack_1385, v0) == 0x0, "g1_layout_lc3_spec_scratch5__stack_1385.v0");
_Static_assert(offsetof(struct g1_layout_lc3_spec_scratch5__stack_1385, v1) == 0x4, "g1_layout_lc3_spec_scratch5__stack_1385.v1");
_Static_assert(offsetof(struct g1_layout_lc3_spec_scratch5__stack_1385, v2) == 0x8, "g1_layout_lc3_spec_scratch5__stack_1385.v2");
_Static_assert(offsetof(struct g1_layout_lc3_spec_scratch5__stack_1385, v3) == 0xc, "g1_layout_lc3_spec_scratch5__stack_1385.v3");
_Static_assert(offsetof(struct g1_layout_lc3_spec_scratch5__stack_1385, v4) == 0x10, "g1_layout_lc3_spec_scratch5__stack_1385.v4");
_Static_assert(sizeof(struct g1_layout_lc3_spec_scratch5__stack_1385) >= 0x14, "g1_layout_lc3_spec_scratch5__stack_1385.size");

/* stack_1387 | G1-original | Stack-local 5-word scratch buffer (local_154) used in lc3_tns_analyze (TNS filter analysis). | D1+D2 verified
 * review: Local scratch buffer (not the liblc3 struct itself). Kept offsets. */
struct __attribute__((packed)) g1_layout_lc3_tns_analyze_local__stack_1387 {
    uint8_t _pad_0x0[0x18];
    uint8_t word_0[0x4]; /* catalog type: uint32_t */
    uint8_t word_1[0x4]; /* catalog type: uint32_t */
    uint8_t word_2[0x4]; /* catalog type: uint32_t */
    uint8_t word_3[0x4]; /* catalog type: uint32_t */
    uint8_t word_4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_tns_analyze_local__stack_1387, word_0) == 0x18, "g1_layout_lc3_tns_analyze_local__stack_1387.word_0");
_Static_assert(offsetof(struct g1_layout_lc3_tns_analyze_local__stack_1387, word_1) == 0x1c, "g1_layout_lc3_tns_analyze_local__stack_1387.word_1");
_Static_assert(offsetof(struct g1_layout_lc3_tns_analyze_local__stack_1387, word_2) == 0x20, "g1_layout_lc3_tns_analyze_local__stack_1387.word_2");
_Static_assert(offsetof(struct g1_layout_lc3_tns_analyze_local__stack_1387, word_3) == 0x24, "g1_layout_lc3_tns_analyze_local__stack_1387.word_3");
_Static_assert(offsetof(struct g1_layout_lc3_tns_analyze_local__stack_1387, word_4) == 0x28, "g1_layout_lc3_tns_analyze_local__stack_1387.word_4");
_Static_assert(sizeof(struct g1_layout_lc3_tns_analyze_local__stack_1387) >= 0x2c, "g1_layout_lc3_tns_analyze_local__stack_1387.size");

/* stack_1388 | G1-original | Five-word coefficient scratch in lc3_tns_analyze (local_11c). | D1+D2 verified
 * review: LC3 TNS local scratch. is_library corrected to false. SEPARATE. */
struct __attribute__((packed)) g1_layout_lc3_tns_scratch5__stack_1388 {
    uint8_t v0[0x4]; /* catalog type: uint32_t */
    uint8_t v1[0x4]; /* catalog type: uint32_t */
    uint8_t v2[0x4]; /* catalog type: uint32_t */
    uint8_t v3[0x4]; /* catalog type: uint32_t */
    uint8_t v4[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_lc3_tns_scratch5__stack_1388, v0) == 0x0, "g1_layout_lc3_tns_scratch5__stack_1388.v0");
_Static_assert(offsetof(struct g1_layout_lc3_tns_scratch5__stack_1388, v1) == 0x4, "g1_layout_lc3_tns_scratch5__stack_1388.v1");
_Static_assert(offsetof(struct g1_layout_lc3_tns_scratch5__stack_1388, v2) == 0x8, "g1_layout_lc3_tns_scratch5__stack_1388.v2");
_Static_assert(offsetof(struct g1_layout_lc3_tns_scratch5__stack_1388, v3) == 0xc, "g1_layout_lc3_tns_scratch5__stack_1388.v3");
_Static_assert(offsetof(struct g1_layout_lc3_tns_scratch5__stack_1388, v4) == 0x10, "g1_layout_lc3_tns_scratch5__stack_1388.v4");
_Static_assert(sizeof(struct g1_layout_lc3_tns_scratch5__stack_1388) >= 0x14, "g1_layout_lc3_tns_scratch5__stack_1388.size");

/* stack_1422 | G1-original | Stack-local mantissa/exponent pair used by printf_render_float while formatting a floating-point value. | D1+D2 verified
 * review: G1-original stack local; kept naming. */
struct __attribute__((packed)) g1_layout_float_render_locals__stack_1422 {
    uint8_t mantissa[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t exponent[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_float_render_locals__stack_1422, mantissa) == 0x0, "g1_layout_float_render_locals__stack_1422.mantissa");
_Static_assert(offsetof(struct g1_layout_float_render_locals__stack_1422, exponent) == 0x8, "g1_layout_float_render_locals__stack_1422.exponent");
_Static_assert(sizeof(struct g1_layout_float_render_locals__stack_1422) >= 0xc, "g1_layout_float_render_locals__stack_1422.size");

/* stack_1423 | G1-original | Stack scratch (two format-state words) inside snprintf. | D1+D2 verified
 * review: Ground-truth marks G1-original; function-local frame, is_library=false. */
struct __attribute__((packed)) g1_layout_snprintf_locals__stack_1423 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_snprintf_locals__stack_1423, field_0x0) == 0x0, "g1_layout_snprintf_locals__stack_1423.field_0x0");
_Static_assert(offsetof(struct g1_layout_snprintf_locals__stack_1423, field_0x8) == 0x8, "g1_layout_snprintf_locals__stack_1423.field_0x8");
_Static_assert(sizeof(struct g1_layout_snprintf_locals__stack_1423) >= 0xc, "g1_layout_snprintf_locals__stack_1423.size");

/* stack_1424 | G1-original | Local buffer-pointer/length state used by format_string_to_buffer. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_fmt_buf_state__stack_1424 {
    uint8_t buf_ptr_or_pos[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t len_or_remaining[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_fmt_buf_state__stack_1424, buf_ptr_or_pos) == 0x0, "g1_layout_fmt_buf_state__stack_1424.buf_ptr_or_pos");
_Static_assert(offsetof(struct g1_layout_fmt_buf_state__stack_1424, len_or_remaining) == 0x8, "g1_layout_fmt_buf_state__stack_1424.len_or_remaining");
_Static_assert(sizeof(struct g1_layout_fmt_buf_state__stack_1424) >= 0xc, "g1_layout_fmt_buf_state__stack_1424.size");

/* stack_1425 | library | Stack local (local_7c) in strtod: big-integer/decimal conversion scratch (exponent/digit accumulator + scratch values). | D1+D2 verified
 * review: Compiler-generated locals of libc strtod; not a public struct, unverified. */
struct __attribute__((packed)) g1_layout_strtod_bigint_scratch__stack_1425 {
    uint8_t _pad_0x0[0xc];
    uint8_t field_0xc[0x4]; /* catalog type: int32_t */
    uint8_t field_0x10[0x4]; /* catalog type: int32_t */
    uint8_t field_0x14[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_strtod_bigint_scratch__stack_1425, field_0xc) == 0xc, "g1_layout_strtod_bigint_scratch__stack_1425.field_0xc");
_Static_assert(offsetof(struct g1_layout_strtod_bigint_scratch__stack_1425, field_0x10) == 0x10, "g1_layout_strtod_bigint_scratch__stack_1425.field_0x10");
_Static_assert(offsetof(struct g1_layout_strtod_bigint_scratch__stack_1425, field_0x14) == 0x14, "g1_layout_strtod_bigint_scratch__stack_1425.field_0x14");
_Static_assert(sizeof(struct g1_layout_strtod_bigint_scratch__stack_1425) >= 0x18, "g1_layout_strtod_bigint_scratch__stack_1425.size");

/* stack_1426 | G1-original | Stack-local scratch state used by strtod() during string-to-double conversion. | D1+D2 verified
 * review: Function-local scratch (local_30); libc strtod internals but the local aggregate is not a stock struct. */
struct __attribute__((packed)) g1_layout_strtod_scratch__stack_1426 {
    uint8_t scratch_word0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x8];
    uint8_t scratch_word1[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_strtod_scratch__stack_1426, scratch_word0) == 0x0, "g1_layout_strtod_scratch__stack_1426.scratch_word0");
_Static_assert(offsetof(struct g1_layout_strtod_scratch__stack_1426, scratch_word1) == 0xc, "g1_layout_strtod_scratch__stack_1426.scratch_word1");
_Static_assert(sizeof(struct g1_layout_strtod_scratch__stack_1426) >= 0x10, "g1_layout_strtod_scratch__stack_1426.size");

/* stack_1427 | G1-original | Stack-local scratch in strtod holding two intermediate parsing words (mantissa/exponent) (newlib). | D1+D2 verified
 * review: Anonymous newlib strtod local frame, not a named struct → is_library=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_strtod_locals__stack_1427 {
    uint8_t _pad_0x0[0x4];
    uint8_t field_0x4[0x4]; /* catalog type: uint32_t */
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_strtod_locals__stack_1427, field_0x4) == 0x4, "g1_layout_strtod_locals__stack_1427.field_0x4");
_Static_assert(offsetof(struct g1_layout_strtod_locals__stack_1427, field_0x8) == 0x8, "g1_layout_strtod_locals__stack_1427.field_0x8");
_Static_assert(sizeof(struct g1_layout_strtod_locals__stack_1427) >= 0xc, "g1_layout_strtod_locals__stack_1427.size");

/* stack_1428 | G1-original | Stack-local 32-bit pair (local_70) inside vsprintf_impl (format width/precision or arg pointer/count). | D1+D2 verified
 * review: Function-local; offsets unchanged. */
struct __attribute__((packed)) g1_layout_vsprintf_fmt_state_tmp__stack_1428 {
    uint8_t field_0x0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t field_0x8[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_vsprintf_fmt_state_tmp__stack_1428, field_0x0) == 0x0, "g1_layout_vsprintf_fmt_state_tmp__stack_1428.field_0x0");
_Static_assert(offsetof(struct g1_layout_vsprintf_fmt_state_tmp__stack_1428, field_0x8) == 0x8, "g1_layout_vsprintf_fmt_state_tmp__stack_1428.field_0x8");
_Static_assert(sizeof(struct g1_layout_vsprintf_fmt_state_tmp__stack_1428) >= 0xc, "g1_layout_vsprintf_fmt_state_tmp__stack_1428.size");

/* stack_1430 | G1-original | Local scratch values used by scanf_convert_integer_field (local_34) while parsing an integer field. | D1+D2 verified
 * review: G1/newlib scanf helper stack local; four idx4 words. */
struct __attribute__((packed)) g1_layout_scanf_int_convert_locals__stack_1430 {
    uint8_t val_0[0x4]; /* catalog type: uint32_t */
    uint8_t val_1[0x4]; /* catalog type: uint32_t */
    uint8_t val_2[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0xc[0x4];
    uint8_t val_3[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_scanf_int_convert_locals__stack_1430, val_0) == 0x0, "g1_layout_scanf_int_convert_locals__stack_1430.val_0");
_Static_assert(offsetof(struct g1_layout_scanf_int_convert_locals__stack_1430, val_1) == 0x4, "g1_layout_scanf_int_convert_locals__stack_1430.val_1");
_Static_assert(offsetof(struct g1_layout_scanf_int_convert_locals__stack_1430, val_2) == 0x8, "g1_layout_scanf_int_convert_locals__stack_1430.val_2");
_Static_assert(offsetof(struct g1_layout_scanf_int_convert_locals__stack_1430, val_3) == 0x10, "g1_layout_scanf_int_convert_locals__stack_1430.val_3");
_Static_assert(sizeof(struct g1_layout_scanf_int_convert_locals__stack_1430) >= 0x14, "g1_layout_scanf_int_convert_locals__stack_1430.size");

/* stack_1469 | G1-original | Stack-local scratch in mbedtls_hardware_poll (entropy source callback): a temp RNG word and an output-length word. | D1+D2 verified
 * review: Corrected sonnet's is_library=True: function-local temporaries inside a library function are not themselves a stock struct. is_library=false. Offsets unchanged. */
struct __attribute__((packed)) g1_layout_mbedtls_hw_poll_locals__stack_1469 {
    uint8_t val_0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t olen_or_val[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_mbedtls_hw_poll_locals__stack_1469, val_0) == 0x0, "g1_layout_mbedtls_hw_poll_locals__stack_1469.val_0");
_Static_assert(offsetof(struct g1_layout_mbedtls_hw_poll_locals__stack_1469, olen_or_val) == 0x8, "g1_layout_mbedtls_hw_poll_locals__stack_1469.olen_or_val");
_Static_assert(sizeof(struct g1_layout_mbedtls_hw_poll_locals__stack_1469) >= 0xc, "g1_layout_mbedtls_hw_poll_locals__stack_1469.size");

/* stack_1496 | G1-original | Stack-local 6-byte command buffer (local_11) built in projector_send_cmd_immediate before sending to the AR projector. | D1+D2 verified
 * review: Local scratch; kept offsets. */
struct __attribute__((packed)) g1_layout_projector_cmd_local__stack_1496 {
    uint8_t cmd_id[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x4];
    uint8_t param_or_checksum[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_projector_cmd_local__stack_1496, cmd_id) == 0x0, "g1_layout_projector_cmd_local__stack_1496.cmd_id");
_Static_assert(offsetof(struct g1_layout_projector_cmd_local__stack_1496, param_or_checksum) == 0x5, "g1_layout_projector_cmd_local__stack_1496.param_or_checksum");
_Static_assert(sizeof(struct g1_layout_projector_cmd_local__stack_1496) >= 0x6, "g1_layout_projector_cmd_local__stack_1496.size");

/* stack_1497 | G1-original | Stack-local command/parameter byte pair built by projector_send_cmd_immediate before sending to the projector. | D1+D2 verified
 * review: G1-original stack local; kept naming. */
struct __attribute__((packed)) g1_layout_proj_cmd_locals__stack_1497 {
    uint8_t cmd_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x3];
    uint8_t param_byte[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_proj_cmd_locals__stack_1497, cmd_byte) == 0x0, "g1_layout_proj_cmd_locals__stack_1497.cmd_byte");
_Static_assert(offsetof(struct g1_layout_proj_cmd_locals__stack_1497, param_byte) == 0x4, "g1_layout_proj_cmd_locals__stack_1497.param_byte");
_Static_assert(sizeof(struct g1_layout_proj_cmd_locals__stack_1497) >= 0x5, "g1_layout_proj_cmd_locals__stack_1497.size");

/* stack_1498 | G1-original | Stack chunk-index/flag pair while writing SPI data to the projector display in chunks. | D1+D2 verified
 * review: G1-original local. */
struct __attribute__((packed)) g1_layout_spi_chunk_state__stack_1498 {
    uint8_t chunk_idx[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x7];
    uint8_t chunk_flag[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_spi_chunk_state__stack_1498, chunk_idx) == 0x0, "g1_layout_spi_chunk_state__stack_1498.chunk_idx");
_Static_assert(offsetof(struct g1_layout_spi_chunk_state__stack_1498, chunk_flag) == 0x8, "g1_layout_spi_chunk_state__stack_1498.chunk_flag");
_Static_assert(sizeof(struct g1_layout_spi_chunk_state__stack_1498) >= 0x9, "g1_layout_spi_chunk_state__stack_1498.size");

/* stack_1505 | G1-original | Local pair of 16-bit index values in FUN_0007e83a. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_scratch_pair_0007e83a__stack_1505 {
    uint8_t field_0x0[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x6];
    uint8_t field_0x8[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_scratch_pair_0007e83a__stack_1505, field_0x0) == 0x0, "g1_layout_scratch_pair_0007e83a__stack_1505.field_0x0");
_Static_assert(offsetof(struct g1_layout_scratch_pair_0007e83a__stack_1505, field_0x8) == 0x8, "g1_layout_scratch_pair_0007e83a__stack_1505.field_0x8");
_Static_assert(sizeof(struct g1_layout_scratch_pair_0007e83a__stack_1505) >= 0xa, "g1_layout_scratch_pair_0007e83a__stack_1505.size");

/* stack_1521 | G1-original | Stack local (local_20) in mpu_configure_region: ARM MPU region config (RBAR base word + RLAR/attribute word at 0x8). | D1+D2 verified
 * review: On-stack RBAR/RLAR pair built inline; treated as G1 local (not a named public struct). */
struct __attribute__((packed)) g1_layout_mpu_region_cfg_local__stack_1521 {
    uint8_t base_or_rbar[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t limit_or_rlar[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_mpu_region_cfg_local__stack_1521, base_or_rbar) == 0x0, "g1_layout_mpu_region_cfg_local__stack_1521.base_or_rbar");
_Static_assert(offsetof(struct g1_layout_mpu_region_cfg_local__stack_1521, limit_or_rlar) == 0x8, "g1_layout_mpu_region_cfg_local__stack_1521.limit_or_rlar");
_Static_assert(sizeof(struct g1_layout_mpu_region_cfg_local__stack_1521) >= 0xc, "g1_layout_mpu_region_cfg_local__stack_1521.size");

/* stack_1525 | G1-original | 16-byte AES-ECB output buffer (plus trailing byte) used by bt_smp_ah to compute a resolvable-address hash. | D1+D2 verified
 * review: Function-local output buffer (auStack_1d); a byte array, not a named struct, so is_library=false. */
struct __attribute__((packed)) g1_layout_smp_ah_output_buf__stack_1525 {
    uint8_t byte_0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x10];
    uint8_t byte_last[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_smp_ah_output_buf__stack_1525, byte_0) == 0x0, "g1_layout_smp_ah_output_buf__stack_1525.byte_0");
_Static_assert(offsetof(struct g1_layout_smp_ah_output_buf__stack_1525, byte_last) == 0x11, "g1_layout_smp_ah_output_buf__stack_1525.byte_last");
_Static_assert(sizeof(struct g1_layout_smp_ah_output_buf__stack_1525) >= 0x12, "g1_layout_smp_ah_output_buf__stack_1525.size");

/* stack_1532 | G1-original | Stack-local pair of 16-bit fields (handle and CCC value) used while reading a CCC attribute in bt_gatt_attr_read_ccc. | D1+D2 verified
 * review: Anonymous local frame in a GATT read handler; not a named struct → is_library=false. Offsets kept. */
struct __attribute__((packed)) g1_layout_bt_gatt_attr_read_ccc_locals__stack_1532 {
    uint8_t field_0x0[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x4];
    uint8_t field_0x6[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_bt_gatt_attr_read_ccc_locals__stack_1532, field_0x0) == 0x0, "g1_layout_bt_gatt_attr_read_ccc_locals__stack_1532.field_0x0");
_Static_assert(offsetof(struct g1_layout_bt_gatt_attr_read_ccc_locals__stack_1532, field_0x6) == 0x6, "g1_layout_bt_gatt_attr_read_ccc_locals__stack_1532.field_0x6");
_Static_assert(sizeof(struct g1_layout_bt_gatt_attr_read_ccc_locals__stack_1532) >= 0x8, "g1_layout_bt_gatt_attr_read_ccc_locals__stack_1532.size");

/* stack_1533 | G1-original | Stack-local parse-state pair (local_14) used by cf_read (status/type byte + value byte). | D1+D2 verified
 * review: Function-local; offsets unchanged. */
struct __attribute__((packed)) g1_layout_cf_read_state__stack_1533 {
    uint8_t status_or_type[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x7];
    uint8_t value[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_cf_read_state__stack_1533, status_or_type) == 0x0, "g1_layout_cf_read_state__stack_1533.status_or_type");
_Static_assert(offsetof(struct g1_layout_cf_read_state__stack_1533, value) == 0x8, "g1_layout_cf_read_state__stack_1533.value");
_Static_assert(sizeof(struct g1_layout_cf_read_state__stack_1533) >= 0x9, "g1_layout_cf_read_state__stack_1533.size");

/* stack_1534 | G1-original | Local response buffer in read_appearance (local_12): a 16-bit appearance value and a second halfword. | D1+D2 verified
 * review: Per-function stack local for the GAP appearance read handler. Two idx2 halfwords. */
struct __attribute__((packed)) g1_layout_ble_appearance_rsp__stack_1534 {
    uint8_t appearance[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x4];
    uint8_t field_0x6[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_ble_appearance_rsp__stack_1534, appearance) == 0x0, "g1_layout_ble_appearance_rsp__stack_1534.appearance");
_Static_assert(offsetof(struct g1_layout_ble_appearance_rsp__stack_1534, field_0x6) == 0x6, "g1_layout_ble_appearance_rsp__stack_1534.field_0x6");
_Static_assert(sizeof(struct g1_layout_ble_appearance_rsp__stack_1534) >= 0x8, "g1_layout_ble_appearance_rsp__stack_1534.size");

/* stack_1535 | G1-original | Stack-local pair of index words in FUN_00082c48 (unidentified function). | D1+D2 verified
 * review: Function-local; kept naming, offsets unchanged. */
struct __attribute__((packed)) g1_layout_local_pair_82c48__stack_1535 {
    uint8_t val_0[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0xc];
    uint8_t val_1[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_local_pair_82c48__stack_1535, val_0) == 0x0, "g1_layout_local_pair_82c48__stack_1535.val_0");
_Static_assert(offsetof(struct g1_layout_local_pair_82c48__stack_1535, val_1) == 0x10, "g1_layout_local_pair_82c48__stack_1535.val_1");
_Static_assert(sizeof(struct g1_layout_local_pair_82c48__stack_1535) >= 0x14, "g1_layout_local_pair_82c48__stack_1535.size");

/* stack_1536 | G1-original | Stack-local byte-pair scratch (local_48) in unnamed FUN_00082d6a. | D1+D2 verified
 * review: Unidentified local scratch; kept offsets. */
struct __attribute__((packed)) g1_layout_unk_stack_1536__stack_1536 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x1];
    uint8_t field_0x2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_unk_stack_1536__stack_1536, field_0x0) == 0x0, "g1_layout_unk_stack_1536__stack_1536.field_0x0");
_Static_assert(offsetof(struct g1_layout_unk_stack_1536__stack_1536, field_0x2) == 0x2, "g1_layout_unk_stack_1536__stack_1536.field_0x2");
_Static_assert(sizeof(struct g1_layout_unk_stack_1536__stack_1536) >= 0x3, "g1_layout_unk_stack_1536__stack_1536.size");

/* stack_1538 | library | Stack-local bytes in smp_c1 (BT SMP 'c1' confirm-value computation): p1/p2 pre-authentication buffer bytes. | D1+D2 verified
 * review: Function-local byte buffer inside smp_c1, not a named struct; library_verified=false. */
struct __attribute__((packed)) g1_layout_smp_c1_locals__stack_1538 {
    uint8_t byte_0[0x1]; /* catalog type: uint8_t */
    uint8_t byte_1[0x1]; /* catalog type: uint8_t */
    uint8_t byte_2[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_smp_c1_locals__stack_1538, byte_0) == 0x0, "g1_layout_smp_c1_locals__stack_1538.byte_0");
_Static_assert(offsetof(struct g1_layout_smp_c1_locals__stack_1538, byte_1) == 0x1, "g1_layout_smp_c1_locals__stack_1538.byte_1");
_Static_assert(offsetof(struct g1_layout_smp_c1_locals__stack_1538, byte_2) == 0x2, "g1_layout_smp_c1_locals__stack_1538.byte_2");
_Static_assert(sizeof(struct g1_layout_smp_c1_locals__stack_1538) >= 0x3, "g1_layout_smp_c1_locals__stack_1538.size");

/* stack_1552 | G1-original | Stack scratch bytes in dev_write_reg4 building a register/value pair for a device write helper. | D1+D2 verified
 * review: G1-original local. */
struct __attribute__((packed)) g1_layout_dev_write_reg4_locals__stack_1552 {
    uint8_t _pad_0x0[0x2];
    uint8_t reg_addr[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x3[0x1];
    uint8_t reg_value[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_dev_write_reg4_locals__stack_1552, reg_addr) == 0x2, "g1_layout_dev_write_reg4_locals__stack_1552.reg_addr");
_Static_assert(offsetof(struct g1_layout_dev_write_reg4_locals__stack_1552, reg_value) == 0x4, "g1_layout_dev_write_reg4_locals__stack_1552.reg_value");
_Static_assert(sizeof(struct g1_layout_dev_write_reg4_locals__stack_1552) >= 0x5, "g1_layout_dev_write_reg4_locals__stack_1552.size");

/* stack_1553 | G1-original | Local DPPI channel/config pair read by dppi_apply_channel_config_table while iterating the config table. | D1+D2 verified
 * review:  */
struct __attribute__((packed)) g1_layout_dppi_channel_cfg_entry__stack_1553 {
    uint8_t channel[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t config[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_dppi_channel_cfg_entry__stack_1553, channel) == 0x0, "g1_layout_dppi_channel_cfg_entry__stack_1553.channel");
_Static_assert(offsetof(struct g1_layout_dppi_channel_cfg_entry__stack_1553, config) == 0x8, "g1_layout_dppi_channel_cfg_entry__stack_1553.config");
_Static_assert(sizeof(struct g1_layout_dppi_channel_cfg_entry__stack_1553) >= 0xc, "g1_layout_dppi_channel_cfg_entry__stack_1553.size");

/* stack_1554 | G1-original | Stack local (local_12) in regulator_set_voltage_range: min/max index bytes while validating a voltage range. | D1+D2 verified
 * review: Compiler stack local; G1-original. */
struct __attribute__((packed)) g1_layout_regulator_volt_range_local__stack_1554 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x5];
    uint8_t field_0x6[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_regulator_volt_range_local__stack_1554, field_0x0) == 0x0, "g1_layout_regulator_volt_range_local__stack_1554.field_0x0");
_Static_assert(offsetof(struct g1_layout_regulator_volt_range_local__stack_1554, field_0x6) == 0x6, "g1_layout_regulator_volt_range_local__stack_1554.field_0x6");
_Static_assert(sizeof(struct g1_layout_regulator_volt_range_local__stack_1554) >= 0x7, "g1_layout_regulator_volt_range_local__stack_1554.size");

/* stack_1555 | G1-original | Stack-local register-address/value pair in i2c_read_reg16_be for big-endian 16-bit I2C register reads. | D1+D2 verified
 * review: G1-original function-local scratch (local_2c). */
struct __attribute__((packed)) g1_layout_i2c_reg16_xfer__stack_1555 {
    uint8_t reg_addr[0x2]; /* catalog type: uint16_t */
    uint8_t _pad_0x2[0x2];
    uint8_t reg_value[0x2]; /* catalog type: uint16_t */
};
_Static_assert(offsetof(struct g1_layout_i2c_reg16_xfer__stack_1555, reg_addr) == 0x0, "g1_layout_i2c_reg16_xfer__stack_1555.reg_addr");
_Static_assert(offsetof(struct g1_layout_i2c_reg16_xfer__stack_1555, reg_value) == 0x4, "g1_layout_i2c_reg16_xfer__stack_1555.reg_value");
_Static_assert(sizeof(struct g1_layout_i2c_reg16_xfer__stack_1555) >= 0x6, "g1_layout_i2c_reg16_xfer__stack_1555.size");

/* stack_1556 | G1-original | Stack-local struct in post_event_tag2_from_node holding a tag byte and a payload byte. | D1+D2 verified
 * review: Single-cid stack local. Offsets kept. */
struct __attribute__((packed)) g1_layout_post_event_tag2_locals__stack_1556 {
    uint8_t tag[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x3];
    uint8_t payload[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_post_event_tag2_locals__stack_1556, tag) == 0x0, "g1_layout_post_event_tag2_locals__stack_1556.tag");
_Static_assert(offsetof(struct g1_layout_post_event_tag2_locals__stack_1556, payload) == 0x4, "g1_layout_post_event_tag2_locals__stack_1556.payload");
_Static_assert(sizeof(struct g1_layout_post_event_tag2_locals__stack_1556) >= 0x5, "g1_layout_post_event_tag2_locals__stack_1556.size");

/* stack_1557 | G1-original | Stack-local tag/flag pair (local_24) inside post_event_tag4_and_clear. | D1+D2 verified
 * review: Function-local; offsets unchanged. */
struct __attribute__((packed)) g1_layout_event_tag4_clear_tmp__stack_1557 {
    uint8_t field_0x0[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x3];
    uint8_t field_0x4[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_event_tag4_clear_tmp__stack_1557, field_0x0) == 0x0, "g1_layout_event_tag4_clear_tmp__stack_1557.field_0x0");
_Static_assert(offsetof(struct g1_layout_event_tag4_clear_tmp__stack_1557, field_0x4) == 0x4, "g1_layout_event_tag4_clear_tmp__stack_1557.field_0x4");
_Static_assert(sizeof(struct g1_layout_event_tag4_clear_tmp__stack_1557) >= 0x5, "g1_layout_event_tag4_clear_tmp__stack_1557.size");

/* stack_1558 | G1-original | Local event-tag buffer in post_event_tag5 (local_1c): header byte and trailer byte across a 0x15-byte scratch area. | D1+D2 verified
 * review: G1-original stack local; first/last byte observed. */
struct __attribute__((packed)) g1_layout_post_event_tag5_locals__stack_1558 {
    uint8_t header_byte[0x1]; /* catalog type: uint8_t */
    uint8_t _pad_0x1[0x13];
    uint8_t trailer_byte[0x1]; /* catalog type: uint8_t */
};
_Static_assert(offsetof(struct g1_layout_post_event_tag5_locals__stack_1558, header_byte) == 0x0, "g1_layout_post_event_tag5_locals__stack_1558.header_byte");
_Static_assert(offsetof(struct g1_layout_post_event_tag5_locals__stack_1558, trailer_byte) == 0x14, "g1_layout_post_event_tag5_locals__stack_1558.trailer_byte");
_Static_assert(sizeof(struct g1_layout_post_event_tag5_locals__stack_1558) >= 0x15, "g1_layout_post_event_tag5_locals__stack_1558.size");

/* stack_1560 | G1-original | Stack-local 16-byte buffer (auStack_28) in flash_write_padded_entry used to assemble a padded NVS/settings flash record before writing. | D1+D2 verified
 * review: SPLIT from coincidental 4-word footprint group. Buffer, not a shared typed object. */
struct __attribute__((packed)) g1_layout_flash_padded_entry_buf__stack_1560 {
    uint8_t word_0[0x4]; /* catalog type: uint32_t */
    uint8_t word_1[0x4]; /* catalog type: uint32_t */
    uint8_t word_2[0x4]; /* catalog type: uint32_t */
    uint8_t word_3[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_flash_padded_entry_buf__stack_1560, word_0) == 0x0, "g1_layout_flash_padded_entry_buf__stack_1560.word_0");
_Static_assert(offsetof(struct g1_layout_flash_padded_entry_buf__stack_1560, word_1) == 0x4, "g1_layout_flash_padded_entry_buf__stack_1560.word_1");
_Static_assert(offsetof(struct g1_layout_flash_padded_entry_buf__stack_1560, word_2) == 0x8, "g1_layout_flash_padded_entry_buf__stack_1560.word_2");
_Static_assert(offsetof(struct g1_layout_flash_padded_entry_buf__stack_1560, word_3) == 0xc, "g1_layout_flash_padded_entry_buf__stack_1560.word_3");
_Static_assert(sizeof(struct g1_layout_flash_padded_entry_buf__stack_1560) >= 0x10, "g1_layout_flash_padded_entry_buf__stack_1560.size");

/* stack_1568 | G1-original | Stack-local scratch in cbor_decode_skip_value: item length/count and a trailing type/remaining word used while recursively skipping a CBOR value. | D1+D2 verified
 * review: Function-local; kept naming, offsets unchanged. */
struct __attribute__((packed)) g1_layout_cbor_skip_locals__stack_1568 {
    uint8_t item_len[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t remaining_or_type[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_cbor_skip_locals__stack_1568, item_len) == 0x0, "g1_layout_cbor_skip_locals__stack_1568.item_len");
_Static_assert(offsetof(struct g1_layout_cbor_skip_locals__stack_1568, remaining_or_type) == 0x8, "g1_layout_cbor_skip_locals__stack_1568.remaining_or_type");
_Static_assert(sizeof(struct g1_layout_cbor_skip_locals__stack_1568) >= 0xc, "g1_layout_cbor_skip_locals__stack_1568.size");

/* stack_1571 | G1-original | Stack-local integer pair (local_2c) used by dtoa_format_cvt during double-to-ASCII conversion (e.g. exponent + digit count). | D1+D2 verified
 * review: Local scratch; kept offsets. */
struct __attribute__((packed)) g1_layout_dtoa_locals__stack_1571 {
    uint8_t exponent[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t digit_count[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_dtoa_locals__stack_1571, exponent) == 0x0, "g1_layout_dtoa_locals__stack_1571.exponent");
_Static_assert(offsetof(struct g1_layout_dtoa_locals__stack_1571, digit_count) == 0x8, "g1_layout_dtoa_locals__stack_1571.digit_count");
_Static_assert(sizeof(struct g1_layout_dtoa_locals__stack_1571) >= 0xc, "g1_layout_dtoa_locals__stack_1571.size");

/* stack_1572 | G1-original | Stack-local write-position/limit pair used inside snprintf_engine_bounded to track buffer bounds. | D1+D2 verified
 * review: G1-original stack local; kept naming. */
struct __attribute__((packed)) g1_layout_snprintf_bounds__stack_1572 {
    uint8_t write_pos[0x4]; /* catalog type: uint32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t limit[0x4]; /* catalog type: uint32_t */
};
_Static_assert(offsetof(struct g1_layout_snprintf_bounds__stack_1572, write_pos) == 0x0, "g1_layout_snprintf_bounds__stack_1572.write_pos");
_Static_assert(offsetof(struct g1_layout_snprintf_bounds__stack_1572, limit) == 0x8, "g1_layout_snprintf_bounds__stack_1572.limit");
_Static_assert(sizeof(struct g1_layout_snprintf_bounds__stack_1572) >= 0xc, "g1_layout_snprintf_bounds__stack_1572.size");

/* stack_1573 | G1-original | Stack-local small int array (aiStack_2c) used in bignum_compare_estimate for magnitude estimation. | D1+D2 verified
 * review: G1-original local int array. */
struct __attribute__((packed)) g1_layout_bignum_estimate_ints__stack_1573 {
    uint8_t arr_0[0x4]; /* catalog type: int32_t */
    uint8_t _pad_0x4[0x4];
    uint8_t arr_2[0x4]; /* catalog type: int32_t */
};
_Static_assert(offsetof(struct g1_layout_bignum_estimate_ints__stack_1573, arr_0) == 0x0, "g1_layout_bignum_estimate_ints__stack_1573.arr_0");
_Static_assert(offsetof(struct g1_layout_bignum_estimate_ints__stack_1573, arr_2) == 0x8, "g1_layout_bignum_estimate_ints__stack_1573.arr_2");
_Static_assert(sizeof(struct g1_layout_bignum_estimate_ints__stack_1573) >= 0xc, "g1_layout_bignum_estimate_ints__stack_1573.size");

#endif
