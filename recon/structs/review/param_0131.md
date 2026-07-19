## review group param_0131  (1 cluster(s), kinds=param)

### proposal for param_0131
struct_name: cbor_encode_cursor | is_library: False | library_name:  | is_array: None | confidence: low
purpose: CBOR/zcbor-style encoder cursor with current payload pointer and payload-end pointer, passed to encode_uint.
fields:
  0x8  uint8_t *    payload  
  0xc  uint8_t *    payload_end  

<ground-truth bundle for param_0131>
### cluster param_0131  (param, 1 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - encode_uint @ 0x4bb90  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0131 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
