### struct curve_table_201pt  (G1-original)  cid=param_0006

purpose: 201-point interpolation curve table passed to curve_table_interp_201pt (point_count + tail coefficient words).

This object is accessed by these functions (read their fully-named source):
  - curve_table_interp_201pt  (as param_5)  ->  recon/readable_sources/app/g1/curve_table_interp_201pt.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct curve_table_201pt {
    uint32_t     point_count;  /* +0x4  rw=r sz=4 */
    uint32_t     field_0x31c;  /* +0x31c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x320;  /* +0x320  rw=r sz=4 */   <-- NAME ME
};
```