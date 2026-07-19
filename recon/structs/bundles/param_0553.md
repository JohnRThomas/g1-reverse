### cluster param_0553  (param, 1 members, 6 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: smp; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - smp_make_rsp_hdr @ 0x807f6  as param_2  [APPLICATION]

layout notes: 0x0: access width 4 exceeds gap 2 to next field (overlap/union); 0x4: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0553 {
    uint16_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=w types=ushort */
    uint16_t   field_0x4;   /* +0x4  sz=2,4 rw=rw types=idx4,ushort */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=w types=undefined2 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```