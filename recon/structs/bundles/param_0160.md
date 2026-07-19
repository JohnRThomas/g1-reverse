### cluster param_0160  (param, 2 members, 8 fields, size>=0x2c)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - gatt_subscribe_service_changed @ 0x4f418  as param_1  [APPLICATION]
  - gatt_service_changed_c_discovery_completed @ 0x7f8dc  as param_2  [APPLICATION]

layout notes: 0x4: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0160 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint16_t   field_0x1;   /* +0x1  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x3[0x1];   /* +0x3 pad */
    uint16_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=w types=undefined2 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x8];   /* +0xc pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x4];   /* +0x18 pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x20[0x4];   /* +0x20 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
};
```