## review group param_0718  (1 cluster(s), kinds=param)

### proposal for param_0718
struct_name: cbor_value | is_library: True | library_name: CborValue (tinycbor/zcbor) | is_array: None | confidence: medium
purpose: CBOR decoder cursor/value object (tinycbor/zcbor CborValue-style) examined by cbor_decode_is_break
fields:
  0x4  const uint8_t* ptr_or_byte  possibly a dereferenced byte at the cursor pointer rather than the pointer field itself
  0x8  uint32_t     remaining  
  0xc  uint32_t     extra_type_flags  packed extra(u16)+type(u8)+flags(u8)

<ground-truth bundle for param_0718>
### cluster param_0718  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - cbor_decode_is_break @ 0x85d36  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0718 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=char */
    uint8_t    _pad_0x5[0x3];   /* +0x5 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
