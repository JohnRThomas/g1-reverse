### struct box_render_desc  (G1-original)  cid=param_0603

purpose: Small descriptor passed to FUN_00081c8c (likely a UI element/box render descriptor: type/id, size, pointer/index, coordinate).

This object is accessed by these functions (read their fully-named source):
  - FUN_00081c8c  (as param_3)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct box_render_desc {
    uint8_t      type_id;  /* +0x2  rw=r sz=1 */
    uint16_t     size;  /* +0x4  rw=r sz=2 */
    uint8_t      field_0x5;  /* +0x5  rw=w sz=1 */   <-- NAME ME
    uint32_t     ptr_or_index;  /* +0xc  rw=r sz=4 */
    uint16_t     coord_or_count;  /* +0x12  rw=r sz=2 */
};
```