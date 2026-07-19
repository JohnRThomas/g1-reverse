### struct gui_bitmap_draw_args  (G1-original)  cid=stack_1015

purpose: Local index pair in gui_bitmap_draw (local_2c), likely a width/stride or x/y pair.

This object is accessed by these functions (read their fully-named source):
  - gui_bitmap_draw  (as local_2c)  ->  recon/readable_sources/app/g1/gui_bitmap_draw.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct gui_bitmap_draw_args {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```