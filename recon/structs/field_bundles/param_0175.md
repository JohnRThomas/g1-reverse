### struct img_mgmt_upload_req  (library:img_mgmt_upload_req (mcumgr))  cid=param_0175

purpose: MCUmgr image-upload request descriptor inspected by img_mgmt_upload_inspect (offset/size/chunk fields of a firmware upload chunk).

This object is accessed by these functions (read their fully-named source):
  - img_mgmt_upload_inspect  (as param_1)  ->  recon/readable_sources/app/library/img_mgmt_upload_inspect.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct img_mgmt_upload_req {
    uint32_t     off;  /* +0x4  rw=r sz=4 */
    uint32_t     size;  /* +0x8  rw=r sz=4 */
    uint32_t     data_len;  /* +0xc  rw=r sz=4 */
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
};
```