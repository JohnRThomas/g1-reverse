### cluster param_0086  (param, 1 members, 4 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - flash_write_and_verify_blob @ 0x30528  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0086 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=2,4 rw=r types=int,ushort */
    void *     field_0x10;   /* +0x10  sz=4 rw=r types=int,ptr */
};
```