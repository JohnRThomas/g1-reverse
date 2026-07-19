### cluster param_0415  (param, 2 members, 5 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - register_events @ 0x751d0  as param_1  [APPLICATION]
  - add_event @ 0x86778  as param_2  [APPLICATION]

layout notes: overlap at 0xd (prev field ends 0x10)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0415 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    void *     field_0x8;   /* +0x8  sz=4 rw=w types=ptr,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=uint */
    void *     field_0x10;   /* +0x10  sz=4 rw=r types=int,ptr */
};
```