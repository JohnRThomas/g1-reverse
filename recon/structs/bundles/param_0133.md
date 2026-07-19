### cluster param_0133  (param, 7 members, 9 fields, size>=0x2c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (7 shown of 7):
  - mpsc_pbuf_commit @ 0x4be0c  as param_1  [APPLICATION]
  - idx_inc @ 0x7e35c  as param_1  [APPLICATION]
  - rd_idx_inc @ 0x7e378  as param_1  [APPLICATION]
  - add_skip_item @ 0x7e390  as param_1  [APPLICATION]
  - drop_item_locked @ 0x7e3ce  as param_1  [APPLICATION]
  - post_drop_action @ 0x7e4bc  as param_1  [APPLICATION]
  - max_utilization_update @ 0x7e4f2  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0133 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=rw types=idx4,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=idx4,undefined4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=idx4,int,uint */
    uint8_t    _pad_0x14[0x8];   /* +0x14 pad */
    void *     field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4,ptr */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=uint */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=rw types=uint */
};
```