### cluster param_0603  (param, 1 members, 5 fields, size>=0x16)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - FUN_00081c8c @ 0x81c8c  as param_3  [APPLICATION]

layout notes: 0x4: access width 2 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0603 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=char */
    uint8_t    _pad_0x3[0x1];   /* +0x3 pad */
    uint8_t    field_0x4;   /* +0x4  sz=2 rw=r types=undefined2,ushort */
    uint8_t    field_0x5;   /* +0x5  sz=1 rw=w types=char,undefined1 */
    uint8_t    _pad_0x6[0x6];   /* +0x6 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x2];   /* +0x10 pad */
    uint16_t   field_0x12;   /* +0x12  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x14[0x2];   /* +0x14 pad */
};
```