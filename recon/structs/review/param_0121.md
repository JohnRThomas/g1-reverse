## review group param_0121  (1 cluster(s), kinds=param)

### proposal for param_0121
struct_name: utf8_decode_cursor | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: UTF-8 to Unicode decode cursor/context used by utf8_to_unicode
fields:
  0x4  const uint8_t* src_ptr_or_pos  
  0x8  uint32_t*    dst_ptr_or_len  

<ground-truth bundle for param_0121>
### cluster param_0121  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - utf8_to_unicode @ 0x477a0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0121 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
