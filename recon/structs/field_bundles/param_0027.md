### struct g1_device_runtime_state  (G1-original)  cid=param_0027

purpose: Central G1-original device runtime/context object (~0x4244 bytes) threaded as param_1/param_2 through 31 functions: runtime_info_sync, user-setting load/save, ESB comms, display/key/touch dispatch threads, screen-state and task/message-queue processing. The shared global device-state struct. Includes a dense task/message dispatch callback pointer table at 0xfec-0x102c.

This object is accessed by these functions (read their fully-named source):
  - runtime_info_sync  (as param_1)  ->  recon/readable_sources/app/g1/runtime_info_sync.c
  - reset_usr_setting  (as param_1)  ->  recon/readable_sources/app/g1/reset_usr_setting.c
  - load_usr_setting  (as param_1)  ->  recon/readable_sources/app/g1/load_usr_setting.c
  - try_to_save_file  (as param_1)  ->  recon/readable_sources/app/g1/try_to_save_file.c
  - brightness_level  (as param_1)  ->  recon/readable_sources/app/g1/brightness_level.c
  - check_bind_status  (as param_1)  ->  recon/readable_sources/app/g1/check_bind_status.c
  - sync_to_slave  (as param_1)  ->  recon/readable_sources/app/g1/sync_to_slave.c
  - esb_send_command_and_wait_ack  (as param_1)  ->  recon/readable_sources/app/g1/esb_send_command_and_wait_ack.c
  - FUN_00027cfe  (as param_1)  [no source file]
  - display_dispatch_thread  (as param_1)  ->  recon/readable_sources/app/g1/display_dispatch_thread.c
  - key_event_thread  (as param_1)  ->  recon/readable_sources/app/g1/key_event_thread.c
  - touch_key_thread  (as param_1)  ->  recon/readable_sources/app/g1/touch_key_thread.c
  - low_speed_peripheral_dispatch_thread  (as param_1)  ->  recon/readable_sources/app/g1/low_speed_peripheral_dispatch_thread.c
  - master_process_audio_fw_load_req  (as param_1)  ->  recon/readable_sources/app/g1/master_process_audio_fw_load_req.c
  - trigger_screen_state_change  (as param_2)  ->  recon/readable_sources/app/g1/trigger_screen_state_change.c
  - update_imu_trigger_status  (as param_2)  ->  recon/readable_sources/app/g1/update_imu_trigger_status.c
  - now_has_persist_task  (as param_1)  ->  recon/readable_sources/app/g1/now_has_persist_task.c
  - display_panel_is_secondary  (as param_1)  ->  recon/readable_sources/app/g1/display_panel_is_secondary.c
  - update_persist_task_status  (as param_1)  ->  recon/readable_sources/app/g1/update_persist_task_status.c
  - update_temp_task_status  (as param_1)  ->  recon/readable_sources/app/g1/update_temp_task_status.c
  - update_persist_task_status_to_idle  (as param_1)  ->  recon/readable_sources/app/g1/update_persist_task_status_to_idle.c
  - process_for_new_message_come_on  (as param_1)  ->  recon/readable_sources/app/g1/process_for_new_message_come_on.c
  - process_for_message_show  (as param_1)  ->  recon/readable_sources/app/g1/process_for_message_show.c
  - process_for_new_task  (as param_1)  ->  recon/readable_sources/app/g1/process_for_new_task.c
  - post_notification_cmd_response  (as param_1)  ->  recon/readable_sources/app/g1/post_notification_cmd_response.c
  - onboarding_ble_process  (as param_4)  ->  recon/readable_sources/app/g1/onboarding_ble_process.c
  - save_usr_setting  (as param_1)  ->  recon/readable_sources/app/g1/save_usr_setting.c
  - set_shutdown_flag  (as param_1)  ->  recon/readable_sources/app/g1/set_shutdown_flag.c
  - update_display_status  (as param_1)  ->  recon/readable_sources/app/g1/update_display_status.c
  - prepare_quick_note_mode  (as param_1)  ->  recon/readable_sources/app/g1/prepare_quick_note_mode.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct g1_device_runtime_state {
    uint8_t      field_0x1;  /* +0x1  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0x2;  /* +0x2  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x3;  /* +0x3  rw=rw sz=1 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x40;  /* +0x40  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x58;  /* +0x58  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc9;  /* +0xc9  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xcd;  /* +0xcd  rw=rw sz=1,4 */   <-- NAME ME
    uint16_t     field_0xd1;  /* +0xd1  rw=r sz=2 */   <-- NAME ME
    uint8_t      field_0xd4;  /* +0xd4  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0xd5;  /* +0xd5  rw=rw sz=1 */   <-- NAME ME
    uint16_t     field_0xd6;  /* +0xd6  rw=w sz=2 */   <-- NAME ME
    uint16_t     brightness_level;  /* +0xd8  rw=w sz=2 */
    uint32_t     field_0xdf;  /* +0xdf  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xe5;  /* +0xe5  rw=rw sz=1,4 */   <-- NAME ME
    uint8_t      field_0xec;  /* +0xec  rw=w sz=1 */   <-- NAME ME
    uint16_t     field_0xed;  /* +0xed  rw=w sz=2 */   <-- NAME ME
    uint8_t      screen_state_flag;  /* +0x6cc  rw=w sz=1 */
    uint32_t     field_0x6d8;  /* +0x6d8  rw=w sz=4 */   <-- NAME ME
    uint16_t     field_0x6dc;  /* +0x6dc  rw=w sz=2 */   <-- NAME ME
    uint8_t      persist_task_status;  /* +0x6e1  rw=rw sz=1 */
    void *       field_0x774;  /* +0x774  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x9b4;  /* +0x9b4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xae4;  /* +0xae4  rw=rw sz=4 */   <-- NAME ME
    uint8_t      field_0xb0c;  /* +0xb0c  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xb0d;  /* +0xb0d  rw=w sz=1 */   <-- NAME ME
    void *       field_0xb8c;  /* +0xb8c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xeb4;  /* +0xeb4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xeb8;  /* +0xeb8  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0xec0;  /* +0xec0  rw=rw sz=1,2 */   <-- NAME ME
    uint32_t     field_0xec8;  /* +0xec8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xee8;  /* +0xee8  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xf68;  /* +0xf68  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xf6c;  /* +0xf6c  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xf90;  /* +0xf90  rw=r sz=4 */   <-- NAME ME
    void *       task_cb_0;  /* +0xfec  rw=rw sz=4 */
    void *       task_cb_1;  /* +0xff0  rw=rw sz=4 */
    void *       task_cb_2;  /* +0xff4  rw=r sz=4 */
    void *       task_cb_3;  /* +0xff8  rw=r sz=4 */
    void *       task_cb_4;  /* +0xffc  rw=r sz=4 */
    void *       task_cb_5;  /* +0x1000  rw=rw sz=4 */
    void *       task_cb_6;  /* +0x1004  rw=r sz=4 */
    void *       task_cb_7;  /* +0x1008  rw=r sz=4 */
    void *       task_cb_8;  /* +0x100c  rw=r sz=4 */
    void *       task_cb_9;  /* +0x1010  rw=rw sz=4 */
    void *       task_cb_10;  /* +0x1014  rw=rw sz=4 */
    void *       task_cb_11;  /* +0x1018  rw=rw sz=4 */
    void *       task_cb_12;  /* +0x101c  rw=r sz=4 */
    void *       task_cb_13;  /* +0x1020  rw=rw sz=4 */
    void *       task_cb_14;  /* +0x1024  rw=r sz=4 */
    void *       task_cb_15;  /* +0x1028  rw=r sz=4 */
    void *       task_cb_16;  /* +0x102c  rw=r sz=4 */
    void *       field_0x1040;  /* +0x1040  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x104c;  /* +0x104c  rw=rw sz=4 */   <-- NAME ME
    void *       field_0x1054;  /* +0x1054  rw=rw sz=4 */   <-- NAME ME
    uint64_t     field_0x1060;  /* +0x1060  rw=rw sz=8 */   <-- NAME ME
    uint32_t     field_0x1078;  /* +0x1078  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x1090;  /* +0x1090  rw=rw sz=1,2 */   <-- NAME ME
    uint32_t     field_0x1b78;  /* +0x1b78  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x2b88;  /* +0x2b88  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x3ad0;  /* +0x3ad0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x4238;  /* +0x4238  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x423c;  /* +0x423c  rw=r sz=4 */   <-- NAME ME
};
```