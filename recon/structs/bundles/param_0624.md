### cluster param_0624  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_write_encode @ 0x8281a  as param_3  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0624 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint16_t   field_0x4;   /* +0x4  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x6[0x2];   /* +0x6 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=undefined4 */
    uint16_t   field_0xc;   /* +0xc  sz=2 rw=r types=undefined2,ushort */
    uint8_t    _pad_0xe[0x2];   /* +0xe pad */
};
```