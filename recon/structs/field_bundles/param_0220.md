### struct att_l2cap_frag_ctx  (library:bt L2CAP/ATT send context (internal))  cid=param_0220

purpose: Fragmentation/buffer context shared by l2cap_chan_le_send_seg and att_send_data_frags (total_len, mtu/flags, data ptr, remaining_len).

This object is accessed by these functions (read their fully-named source):
  - l2cap_chan_le_send_seg  (as param_1)  ->  recon/readable_sources/app/library/l2cap_chan_le_send_seg.c
  - att_send_data_frags  (as param_1)  ->  recon/readable_sources/app/library/att_send_data_frags.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct att_l2cap_frag_ctx {
    uint32_t     total_len;  /* +0x4  rw=r sz=4 */
    uint16_t     field_0x9;  /* +0x9  rw=r sz=2 */   <-- NAME ME
    uint16_t     field_0xa;  /* +0xa  rw=r sz=2 */   <-- NAME ME
    uint32_t     data_ptr_or_len;  /* +0x10  rw=r sz=4 */
    uint16_t     remaining_len;  /* +0x26  rw=r sz=2 */
};
```