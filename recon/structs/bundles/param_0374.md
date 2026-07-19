### cluster param_0374  (param, 2 members, 4 fields, size>=0x488)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - lc3_ltpf_detect_pitch @ 0x698d0  as param_1  [APPLICATION]
  - lc3_ltpf_analyse @ 0x6ab80  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0374 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=rw types=int,uint */
    float      field_0x8;   /* +0x8  sz=4 rw=rw types=float,undefined4 */
    float      field_0xc;   /* +0xc  sz=4 rw=rw types=float,undefined4 */
    uint8_t    _pad_0x10[0x474];   /* +0x10 pad */
    uint32_t   field_0x484;   /* +0x484  sz=4 rw=rw types=int */
};
```