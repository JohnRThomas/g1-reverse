### cluster param_0725  (param, 2 members, 13 fields, size>=0x34)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: k,z; 1/2 members are LIBRARY-class)

members (2 shown of 2):
  - k_msgq_init @ 0x86420  as param_1  [APPLICATION]
  - z_impl_k_msgq_alloc_init @ 0x86448  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0725 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=w types=int */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=w types=int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=int */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=int */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=w types=int */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=w types=int */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=w types=int */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=w types=int */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=w types=int */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=w types=int */
    uint8_t    field_0x30;   /* +0x30  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x31[0x3];   /* +0x31 pad */
};
```