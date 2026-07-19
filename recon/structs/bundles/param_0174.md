### cluster param_0174  (param, 6 members, 5 fields, size>=0x36)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: smp; 0/6 members are LIBRARY-class)

members (6 shown of 6):
  - smp_add_cmd_err @ 0x5160c  as param_1  [APPLICATION]
  - cbor_encode_set_error @ 0x861c2  as param_1  [APPLICATION]
  - cbor_encode_put_type_byte @ 0x861d4  as param_1  [APPLICATION]
  - cbor_encode_length_header @ 0x86208  as param_1  [APPLICATION]
  - zcbor_bstr_encode @ 0x86338  as param_1  [APPLICATION]
  - cbor_encode_bstr @ 0x8633e  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0174 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x4];   /* +0x10 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4,int */
    uint8_t    _pad_0x18[0x18];   /* +0x18 pad */
    uint16_t   field_0x30;   /* +0x30  sz=2 rw=w types=short */
    uint16_t   field_0x32;   /* +0x32  sz=2 rw=w types=short */
    uint8_t    _pad_0x34[0x2];   /* +0x34 pad */
};
```