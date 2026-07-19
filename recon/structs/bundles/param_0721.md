### cluster param_0721  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - cbor_encode_check_ok @ 0x861ae  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0721 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=int */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=r types=char */
    uint8_t    _pad_0x11[0x3];   /* +0x11 pad */
};
```