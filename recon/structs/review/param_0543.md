## review group param_0543  (1 cluster(s), kinds=param)

### proposal for param_0543
struct_name: id_words_pair | is_library: False | library_name:  | is_array: True | confidence: low
purpose: 6-byte device ID accessed as two 32-bit words by read_6byte_id_words.
fields:
  0x4  uint32_t     id_lo  low word of 6-byte id
  0x8  uint32_t     id_hi  high word of 6-byte id

<ground-truth bundle for param_0543>
### cluster param_0543  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - read_6byte_id_words @ 0x7faa8  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0543 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
