### cluster param_0063  (param, 1 members, 4 fields, size>=0x9c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - register_imu_funsion_context @ 0x26250  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0063 {
    uint8_t    _pad_0x0[0x8c];   /* +0x0 pad */
    uint32_t   field_0x8c;   /* +0x8c  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x90;   /* +0x90  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x94;   /* +0x94  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x98;   /* +0x98  sz=4 rw=w types=undefined4 */
};
```