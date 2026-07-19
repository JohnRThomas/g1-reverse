### cluster param_0506  (param, 5 members, 3 fields, size>=0xb4)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (5 shown of 5):
  - FUN_0007eb7e @ 0x7eb7e  as param_1  [APPLICATION]
  - dev_write_reg3 @ 0x83dc8  as param_1  [APPLICATION]
  - dev_write_reg4 @ 0x83de6  as param_1  [APPLICATION]
  - dev_reg_modify_bits @ 0x83e0e  as param_1  [APPLICATION]
  - dev_set_threshold_and_arm @ 0x83e70  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0506 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x14[0x9c];   /* +0x14 pad */
    uint32_t   field_0xb0;   /* +0xb0  sz=4 rw=r types=int */
};
```