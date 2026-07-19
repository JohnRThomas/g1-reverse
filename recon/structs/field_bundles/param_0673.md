### struct flash_layout_region  (G1-original)  cid=param_0673

purpose: Flash layout/region descriptor scanned by flash_page_index_lookup and layout_select_region.

This object is accessed by these functions (read their fully-named source):
  - flash_page_index_lookup  (as param_1)  ->  recon/readable_sources/app/g1/flash_page_index_lookup.c
  - layout_select_region  (as param_1)  ->  recon/readable_sources/app/g1/layout_select_region.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct flash_layout_region {
    uint16_t     field_0x2;  /* +0x2  rw=r sz=2 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x5;  /* +0x5  rw=r sz=2 */   <-- NAME ME
    uint16_t     field_0xa;  /* +0xa  rw=r sz=2 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x16;  /* +0x16  rw=r sz=2 */   <-- NAME ME
};
```