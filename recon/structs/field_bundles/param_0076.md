### struct audio_fw_load_notify_ctx  (G1-original)  cid=param_0076

purpose: Request/response context shared by master_process_audio_fw_load_req and post_notification_cmd_response: command header (type/len) + firmware-load params + trailing status word.

This object is accessed by these functions (read their fully-named source):
  - master_process_audio_fw_load_req  (as param_2)  ->  recon/readable_sources/app/g1/master_process_audio_fw_load_req.c
  - post_notification_cmd_response  (as param_4)  ->  recon/readable_sources/app/g1/post_notification_cmd_response.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct audio_fw_load_notify_ctx {
    uint8_t      cmd_type;  /* +0x1  rw=r sz=1 */
    uint16_t     payload_len;  /* +0x2  rw=r sz=2 */
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x24;  /* +0x24  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x28;  /* +0x28  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x2c;  /* +0x2c  rw=r sz=4 */   <-- NAME ME
    uint32_t     status_or_result;  /* +0x1b4  rw=r sz=4 */
};
```