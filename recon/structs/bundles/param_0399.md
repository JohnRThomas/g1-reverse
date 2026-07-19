### cluster param_0399  (param, 1 members, 4 fields, size>=0x30)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - rpmsg_virtqueue_channel_init @ 0x71358  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0399 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x18[0xc];   /* +0x18 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=w types=int */
    uint8_t    _pad_0x28[0x4];   /* +0x28 pad */
    void *     field_0x2c;   /* +0x2c  sz=4 rw=r types=int,ptr */
};
```