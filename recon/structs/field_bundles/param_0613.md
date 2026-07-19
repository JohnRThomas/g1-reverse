### struct att_write_req_view  (library:bt_att write-req ctx)  cid=param_0613

purpose: param_2 of att_write_req_recv: ATT Write Request PDU/context view (length/ctx word + attribute handle).

This object is accessed by these functions (read their fully-named source):
  - att_write_req_recv  (as param_2)  ->  recon/readable_sources/app/library/att_write_req_recv.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct att_write_req_view {
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint16_t     attr_handle;  /* +0x10  rw=r sz=2 */
};
```