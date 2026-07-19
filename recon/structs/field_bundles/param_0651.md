### struct flash_pages_info  (library:flash_pages_info)  cid=param_0651

purpose: Flash page descriptor filled by flash_get_page_info_by_offs (param_3): start_offset and size (matching Zephyr flash_map flash_pages_info).

This object is accessed by these functions (read their fully-named source):
  - flash_get_page_info_by_offs  (as param_3)  ->  recon/readable_sources/app/g1/flash_get_page_info_by_offs.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct flash_pages_info {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```