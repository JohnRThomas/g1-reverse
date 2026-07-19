## review group param_0715  (1 cluster(s), kinds=param)

### proposal for param_0715
struct_name: cbor_decoder_state | is_library: True | library_name: CborValue / zcbor_state_t | is_array: None | confidence: medium
purpose: CBOR decoder cursor/state object (tinycbor/zcbor CborValue-like) checked by cbor_decoder_at_end for end-of-buffer.
fields:
  0xc  uint32_t     remaining  bytes remaining in the CBOR buffer
  0x10  uint8_t      field_0x10  type/flags byte

<ground-truth bundle for param_0715>
### cluster param_0715  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - cbor_decoder_at_end @ 0x85c12  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0715 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=int */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=r types=char */
    uint8_t    _pad_0x11[0x3];   /* +0x11 pad */
};
```
