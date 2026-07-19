### cluster param_0246  (param, 1 members, 4 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_ccc_write_store_cb @ 0x59dec  as param_3  [APPLICATION]

layout notes: 0x0: access width 2 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0246 {
    uint8_t    field_0x0;   /* +0x0  sz=2 rw=r types=ushort */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=undefined1 */
    uint8_t    _pad_0x2[0x6];   /* +0x2 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```