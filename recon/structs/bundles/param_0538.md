### cluster param_0538  (param, 1 members, 3 fields, size>=0x878)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_ancs_register_attr @ 0x7f772  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0538 {
    uint8_t    _pad_0x0[0x868];   /* +0x0 pad */
    uint8_t    field_0x868;   /* +0x868  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x869[0x7];   /* +0x869 pad */
    uint16_t   field_0x870;   /* +0x870  sz=2 rw=w types=short */
    uint8_t    _pad_0x872[0x2];   /* +0x872 pad */
    uint32_t   field_0x874;   /* +0x874  sz=4 rw=w types=int */
};
```