### cluster param_0228  (param, 2 members, 6 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att; 1/2 members are LIBRARY-class)

members (2 shown of 2):
  - read_group_cb @ 0x58750  as param_3  [LIBRARY]
  - att_read_type_iter_cb @ 0x58808  as param_3  [APPLICATION]

layout notes: overlap at 0x5 (prev field ends 0x8)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0228 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=byte,char */
    uint8_t    _pad_0x1[0x3];   /* +0x1 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```