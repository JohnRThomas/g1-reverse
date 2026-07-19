### cluster param_0375  (param, 1 members, 63 fields, size>=0x100)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_ltpf_detect_pitch @ 0x698d0  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0375 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=idx4 */
    uint32_t   field_0x44;   /* +0x44  sz=4 rw=r types=idx4 */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x50;   /* +0x50  sz=4 rw=r types=idx4 */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=r types=idx4 */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=r types=idx4 */
    uint32_t   field_0x5c;   /* +0x5c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=r types=idx4 */
    uint32_t   field_0x64;   /* +0x64  sz=4 rw=r types=idx4 */
    uint32_t   field_0x68;   /* +0x68  sz=4 rw=r types=idx4 */
    uint32_t   field_0x6c;   /* +0x6c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x70;   /* +0x70  sz=4 rw=r types=idx4 */
    uint32_t   field_0x74;   /* +0x74  sz=4 rw=r types=idx4 */
    uint32_t   field_0x78;   /* +0x78  sz=4 rw=r types=idx4 */
    uint32_t   field_0x7c;   /* +0x7c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x80;   /* +0x80  sz=4 rw=r types=idx4 */
    uint32_t   field_0x84;   /* +0x84  sz=4 rw=r types=idx4 */
    uint32_t   field_0x88;   /* +0x88  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8c;   /* +0x8c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x90;   /* +0x90  sz=4 rw=r types=idx4 */
    uint32_t   field_0x94;   /* +0x94  sz=4 rw=r types=idx4 */
    uint32_t   field_0x98;   /* +0x98  sz=4 rw=r types=idx4 */
    uint32_t   field_0x9c;   /* +0x9c  sz=4 rw=r types=idx4 */
    uint32_t   field_0xa0;   /* +0xa0  sz=4 rw=r types=idx4 */
    uint32_t   field_0xa4;   /* +0xa4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xa8;   /* +0xa8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xac;   /* +0xac  sz=4 rw=r types=idx4 */
    uint32_t   field_0xb0;   /* +0xb0  sz=4 rw=r types=idx4 */
    uint32_t   field_0xb4;   /* +0xb4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xb8;   /* +0xb8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xbc;   /* +0xbc  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc0;   /* +0xc0  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc4;   /* +0xc4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc8;   /* +0xc8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xcc;   /* +0xcc  sz=4 rw=r types=idx4 */
    uint32_t   field_0xd0;   /* +0xd0  sz=4 rw=r types=idx4 */
    uint32_t   field_0xd4;   /* +0xd4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xd8;   /* +0xd8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xdc;   /* +0xdc  sz=4 rw=r types=idx4 */
    uint32_t   field_0xe0;   /* +0xe0  sz=4 rw=r types=idx4 */
    uint32_t   field_0xe4;   /* +0xe4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xe8;   /* +0xe8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xec;   /* +0xec  sz=4 rw=r types=idx4 */
    uint32_t   field_0xf0;   /* +0xf0  sz=4 rw=r types=idx4 */
    uint32_t   field_0xf4;   /* +0xf4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xf8;   /* +0xf8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xfc;   /* +0xfc  sz=4 rw=r types=idx4 */
};
```