### cluster param_0208  (param, 1 members, 7 fields, size>=0xb4)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - ble_notify_le_param_updated @ 0x56ae0  as param_1  [APPLICATION]

layout notes: overlap at 0xae (prev field ends 0xb0)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0208 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint8_t    _pad_0x8[0x9e];   /* +0x8 pad */
    uint16_t   field_0xa6;   /* +0xa6  sz=2 rw=r types=undefined2,ushort */
    uint16_t   field_0xa8;   /* +0xa8  sz=2 rw=r types=ushort */
    uint16_t   field_0xaa;   /* +0xaa  sz=2 rw=r types=ushort */
    uint32_t   field_0xac;   /* +0xac  sz=2,4 rw=r types=int,undefined2 */
    uint32_t   field_0xb0;   /* +0xb0  sz=4 rw=r types=int */
};
```