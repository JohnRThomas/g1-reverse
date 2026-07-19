### struct img_mgmt_req_ctx  (G1-original)  cid=param_0176

purpose: Parameter passed to img_mgmt_state_read/write (mcumgr image-management handlers); two int fields, likely a decode/encode context.

This object is accessed by these functions (read their fully-named source):
  - img_mgmt_state_read  (as param_1)  ->  recon/readable_sources/app/library/img_mgmt_state_read.c
  - img_mgmt_state_write  (as param_1)  ->  recon/readable_sources/app/library/img_mgmt_state_write.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct img_mgmt_req_ctx {
    int32_t      field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```