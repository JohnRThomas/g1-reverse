### cluster param_0366  (param, 8 members, 11 fields, size>=0x38)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/8 members are LIBRARY-class)

members (8 shown of 8):
  - lc3_get_bits_left @ 0x68590  as param_1  [APPLICATION]
  - lc3_put_bits_generic @ 0x68908  as param_1  [APPLICATION]
  - lc3_ac_write_renorm @ 0x6897c  as param_1  [APPLICATION]
  - lc3_ltpf_put_data @ 0x6b378  as param_1  [APPLICATION]
  - lc3_sns_put_data @ 0x6efdc  as param_1  [APPLICATION]
  - lc3_spec_put_side @ 0x6f91c  as param_1  [APPLICATION]
  - lc3_spec_encode @ 0x6f9c0  as param_1  [APPLICATION]
  - lc3_tns_put_data @ 0x70b38  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0366 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=rw types=int,uint */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=uint */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=int,uint */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=int,uint,undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=rw types=int,undefined4 */
    uint8_t    _pad_0x18[0x4];   /* +0x18 pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=rw types=uint,undefined4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=rw types=int,uint */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=int */
    uint8_t    _pad_0x28[0x4];   /* +0x28 pad */
    void *     field_0x2c;   /* +0x2c  sz=4 rw=r types=ptr */
    void *     field_0x30;   /* +0x30  sz=4 rw=rw types=int,ptr,uint */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=rw types=int,uint */
};
```