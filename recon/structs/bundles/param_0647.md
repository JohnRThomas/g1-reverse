### cluster param_0647  (param, 1 members, 3 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: net_buf; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - net_buf_simple_tailroom @ 0x83730  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0647 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint16_t   field_0x1;   /* +0x1  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x3[0x3];   /* +0x3 pad */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=r types=ushort */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```