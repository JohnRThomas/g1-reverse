### struct app_ble_ctx_block  (G1-original)  cid=param_0038

purpose: Large shared application/BLE context (~0x84a) passed across ANCS, audio, DMIC, notification dispatch: node/link ptrs, length, status words and flag bytes.

This object is accessed by these functions (read their fully-named source):
  - ble_ancs_data_req_thread  (as param_1)  ->  recon/readable_sources/app/g1/ble_ancs_data_req_thread.c
  - audio_fw_load_get_wrapper  (as param_1)  ->  recon/readable_sources/app/g1/audio_fw_load_get_wrapper.c
  - send_dmic_msg  (as param_1)  ->  recon/readable_sources/app/g1/send_dmic_msg.c
  - build_status_notify_packet  (as param_1)  ->  recon/readable_sources/app/g1/build_status_notify_packet.c
  - ble_process_req_dispatch  (as param_1)  ->  recon/readable_sources/app/g1/ble_process_req_dispatch.c
  - post_notification_cmd_process  (as param_1)  ->  recon/readable_sources/app/g1/post_notification_cmd_process.c
  - ble_flush_queued_indications  (as param_1)  ->  recon/readable_sources/app/g1/ble_flush_queued_indications.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct app_ble_ctx_block {
    void*        field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    void*        link_next;  /* +0x10  rw=rw sz=4 */
    uint32_t     length_or_count;  /* +0x14  rw=rw sz=4 */
    uint32_t     status_0x3c;  /* +0x3c  rw=w sz=4 */
    uint8_t      flag_0x41;  /* +0x41  rw=w sz=1 */
    uint8_t      flag_0x42;  /* +0x42  rw=w sz=1 */
    uint8_t      flag_0x44;  /* +0x44  rw=w sz=1 */
    uint8_t      flag_0x64;  /* +0x64  rw=w sz=1 */
    uint32_t     status_0x1e4;  /* +0x1e4  rw=w sz=4 */
    uint8_t      field_0x759;  /* +0x759  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x844;  /* +0x844  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x846;  /* +0x846  rw=r sz=1 */   <-- NAME ME
};
```