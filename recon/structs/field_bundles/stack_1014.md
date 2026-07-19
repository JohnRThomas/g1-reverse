### struct bmp_draw_desc  (G1-original)  cid=stack_1014

purpose: Stack-local bitmap draw descriptor (local_24) in gui_bmp_dynamic_bitmap_draw (two words: pointer/dimension pair).

This object is accessed by these functions (read their fully-named source):
  - gui_bmp_dynamic_bitmap_draw  (as local_24)  ->  recon/readable_sources/app/g1/gui_bmp_dynamic_bitmap_draw.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bmp_draw_desc {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```