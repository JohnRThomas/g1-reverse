### struct img_mgmt_erase_ctx  (G1-original)  cid=param_0178

purpose: Context object for img_mgmt_erase (mcumgr image-management erase op); two int fields.

This object is accessed by these functions (read their fully-named source):
  - img_mgmt_erase  (as param_1)  ->  recon/readable_sources/app/library/img_mgmt_erase.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct img_mgmt_erase_ctx {
    int32_t      field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```