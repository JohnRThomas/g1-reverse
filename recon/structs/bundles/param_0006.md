### cluster param_0006  (param, 1 members, 3 fields, size>=0x324)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - curve_table_interp_201pt @ 0xe3a0  as param_5  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0006 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x314];   /* +0x8 pad */
    uint32_t   field_0x31c;   /* +0x31c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x320;   /* +0x320  sz=4 rw=r types=idx4 */
};
```