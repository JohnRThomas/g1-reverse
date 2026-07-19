### cluster param_0091  (param, 1 members, 3 fields, size>=0x7)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - get_assign_channel_info @ 0x31fd8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0091 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=char,undefined1 */
    uint8_t    field_0x5;   /* +0x5  sz=1 rw=r types=char,undefined1 */
    uint8_t    field_0x6;   /* +0x6  sz=1 rw=r types=char,undefined1 */
};
```