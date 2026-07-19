### cluster param_0623  (param, 1 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_find_info_encode @ 0x82772  as param_3  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0623 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint16_t   field_0x8;   /* +0x8  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0xa[0x4];   /* +0xa pad */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=r types=undefined2 */
};
```