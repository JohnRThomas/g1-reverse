### struct img_mgmt_info_local  (G1-original)  cid=stack_1124

purpose: Stack-local pair (e.g. hash ptr + length/slot) in img_mgmt_read_info.

This object is accessed by these functions (read their fully-named source):
  - img_mgmt_read_info  (as local_40)  ->  recon/readable_sources/app/library/img_mgmt_read_info.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct img_mgmt_info_local {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```