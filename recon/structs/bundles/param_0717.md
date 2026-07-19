### cluster param_0717  (param, 1 members, 5 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - buffer_pool_freelist_init @ 0x85cf2  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0717 {
    void *     field_0x0;   /* +0x0  sz=4 rw=r types=ptr */
    uint16_t   field_0x4;   /* +0x4  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x6[0x2];   /* +0x6 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x4];   /* +0x10 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```