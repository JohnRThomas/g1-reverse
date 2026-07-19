### cluster param_0046  (param, 1 members, 2 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - read_usr_settting_from_flash @ 0x23400  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0046 {
    uint8_t    _pad_0x0[0x15];   /* +0x0 pad */
    uint8_t    field_0x15;   /* +0x15  sz=1 rw=w types=undefined1 */
    uint16_t   field_0x16;   /* +0x16  sz=2 rw=w types=undefined2 */
};
```