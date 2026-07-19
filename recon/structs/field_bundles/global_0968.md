### struct resend_pending_msg_state  (G1-original)  cid=global_0968

purpose: G1-original global at 0x33bbc tracking a pending BLE message queued for resend (flag/status bytes).

This object is accessed by these functions (read their fully-named source):
  - stage_pending_message_for_resend  (as 0x00033bbc)  ->  recon/readable_sources/app/g1/stage_pending_message_for_resend.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct resend_pending_msg_state {
    uint8_t      resend_flag;  /* +0x114  rw=w sz=1 */
    uint8_t      field_0x115;  /* +0x115  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x116;  /* +0x116  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x118;  /* +0x118  rw=r sz=1 */   <-- NAME ME
};
```