### struct fw_version_info_table  (G1-original)  cid=global_1152

purpose: Fixed global at 0x53378 consumed by ver_str: a 13-word version/build-info record concatenated into a version string.

This object is accessed by these functions (read their fully-named source):
  - ver_str  (as 0x00053378)  ->  recon/readable_sources/app/library/ver_str.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct fw_version_info_table {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
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
};
```