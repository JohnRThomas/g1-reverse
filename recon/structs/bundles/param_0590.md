### cluster param_0590  (param, 1 members, 3 fields, size>=0x30)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - atomic_counter_add_and_signal @ 0x8174c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0590 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=uint */
    uint8_t    _pad_0x14[0x18];   /* +0x14 pad */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=rw types=int */
};
```