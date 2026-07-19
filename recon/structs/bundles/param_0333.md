### cluster param_0333  (param, 1 members, 9 fields, size>=0x5c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - pdm_configure_pins @ 0x66050  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0333 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,uint,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x10[0x30];   /* +0x10 pad */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=idx4 */
    uint32_t   field_0x44;   /* +0x44  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x48[0x4];   /* +0x48 pad */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x50;   /* +0x50  sz=4 rw=r types=idx4 */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=r types=idx4 */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=r types=idx4 */
};
```