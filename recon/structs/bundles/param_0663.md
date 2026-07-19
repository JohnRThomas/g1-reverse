### cluster param_0663  (param, 4 members, 3 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (4 shown of 4):
  - dev_channel_dispatch_range @ 0x84068  as param_1  [APPLICATION]
  - dev_channel_validate_and_set @ 0x840cc  as param_1  [APPLICATION]
  - dev_write_channel_mode @ 0x843ba  as param_1  [APPLICATION]
  - dev_configure_channel @ 0x84418  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0663 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=int,ptr */
    void *     field_0x8;   /* +0x8  sz=4 rw=r types=int,ptr */
    uint8_t    _pad_0xc[0x4];   /* +0xc pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```