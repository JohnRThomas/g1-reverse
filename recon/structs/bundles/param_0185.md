### cluster param_0185  (param, 3 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 2/3 members are LIBRARY-class)

members (3 shown of 3):
  - bt_uuid_expand_to_128 @ 0x531e4  as param_1  [APPLICATION]
  - bt_uuid_cmp @ 0x80d3e  as param_1  [LIBRARY]
  - bt_uuid_cmp @ 0x80d3e  as param_2  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0185 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=undefined2,ushort */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=uint,undefined4 */
};
```