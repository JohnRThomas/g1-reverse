### struct audio_fw_load_msg  (G1-original)  cid=param_0039

purpose: Wire-format command/message context threaded through audio firmware-load handling, UART callback, notification response building, and uint32_to_little_endian serialization.

This object is accessed by these functions (read their fully-named source):
  - audio_fw_load_get_wrapper  (as param_2)  ->  recon/readable_sources/app/g1/audio_fw_load_get_wrapper.c
  - master_process_audio_fw_load_req  (as param_3)  ->  recon/readable_sources/app/g1/master_process_audio_fw_load_req.c
  - uart_callback  (as param_3)  ->  recon/readable_sources/app/g1/uart_callback.c
  - post_notification_cmd_response  (as param_6)  ->  recon/readable_sources/app/g1/post_notification_cmd_response.c
  - uint32_to_little_endian  (as param_1)  ->  recon/readable_sources/app/g1/uint32_to_little_endian.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct audio_fw_load_msg {
    uint32_t     field_0x0;  /* +0x0  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=rw sz=2,4 */   <-- NAME ME
    uint16_t     field_0x6;  /* +0x6  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0xa;  /* +0xa  rw=w sz=2 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x24;  /* +0x24  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x28;  /* +0x28  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x2c;  /* +0x2c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x30;  /* +0x30  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x34;  /* +0x34  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x38;  /* +0x38  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x3c;  /* +0x3c  rw=r sz=4 */   <-- NAME ME
};
```