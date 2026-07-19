### struct utf_wordwrap_locals  (G1-original)  cid=stack_1027

purpose: Stack scratch in gui_utf_Wordwrap_draw (three cursor/width words for text layout).

This object is accessed by these functions (read their fully-named source):
  - gui_utf_Wordwrap_draw  (as local_2f4)  ->  recon/readable_sources/app/g1/gui_utf_Wordwrap_draw.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct utf_wordwrap_locals {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```