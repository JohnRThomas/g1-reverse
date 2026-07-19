### struct att_pdu_buf_view  (library:net_buf)  cid=param_0236

purpose: param_2 of att_prepare_write_req: ATT prepare-write buffer/PDU view (length word + handle short).

This object is accessed by these functions (read their fully-named source):
  - att_prepare_write_req  (as param_2)  ->  recon/readable_sources/app/library/att_prepare_write_req.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct att_pdu_buf_view {
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x10;  /* +0x10  rw=r sz=2 */   <-- NAME ME
};
```