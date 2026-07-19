### struct msg_show_item  (G1-original)  cid=param_0080

purpose: Message-display record consumed by process_for_message_show (param_2).

This object is accessed by these functions (read their fully-named source):
  - process_for_message_show  (as param_2)  ->  recon/readable_sources/app/g1/process_for_message_show.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct msg_show_item {
    uint8_t      msg_type;  /* +0x1  rw=r sz=1 */
    uint8_t      status_flag;  /* +0x7  rw=rw sz=1 */
    uint8_t      state_flag;  /* +0x8  rw=rw sz=1 */
    uint8_t      field_0x9;  /* +0x9  rw=r sz=1 */   <-- NAME ME
    uint32_t     payload;  /* +0xb  rw=r sz=4 */
    uint8_t      field_0xf;  /* +0xf  rw=r sz=1 */   <-- NAME ME
};
```