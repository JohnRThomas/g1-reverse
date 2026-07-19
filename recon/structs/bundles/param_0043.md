### cluster param_0043  (param, 1 members, 3 fields, size>=0x10e0)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - load_burial_point @ 0x230e0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0043 {
    uint8_t    _pad_0x0[0x10c6];   /* +0x0 pad */
    uint32_t   field_0x10c6;   /* +0x10c6  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x10ca[0x10];   /* +0x10ca pad */
    uint16_t   field_0x10da;   /* +0x10da  sz=1,2 rw=rw types=short,undefined1 */
    uint8_t    field_0x10dc;   /* +0x10dc  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0x10dd[0x3];   /* +0x10dd pad */
};
```