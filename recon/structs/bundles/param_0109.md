### cluster param_0109  (param, 1 members, 8 fields, size>=0x6a)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - DashBoard_Reflash @ 0x3727c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0109 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=byte,char */
    uint8_t    field_0x5;   /* +0x5  sz=1 rw=r types=char */
    uint8_t    _pad_0x6[0x59];   /* +0x6 pad */
    uint8_t    field_0x5f;   /* +0x5f  sz=1 rw=r types=char */
    uint8_t    _pad_0x60[0x4];   /* +0x60 pad */
    uint8_t    field_0x64;   /* +0x64  sz=1 rw=r types=undefined1 */
    uint8_t    field_0x65;   /* +0x65  sz=1 rw=r types=char,undefined1 */
    uint8_t    field_0x66;   /* +0x66  sz=1 rw=r types=char */
    uint8_t    _pad_0x67[0x1];   /* +0x67 pad */
    uint8_t    field_0x68;   /* +0x68  sz=1 rw=r types=byte,char */
    uint8_t    field_0x69;   /* +0x69  sz=1 rw=r types=char */
};
```