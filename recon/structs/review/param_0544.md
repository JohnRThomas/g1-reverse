## review group param_0544  (1 cluster(s), kinds=param)

### proposal for param_0544
struct_name: settings_read_result | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Result/id pair populated by the 6-byte settings id-28 reader wrapper.
fields:
  0x4  uint32_t     setting_id  
  0x8  uint32_t     setting_value  

<ground-truth bundle for param_0544>
### cluster param_0544  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: settings; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - settings_read_6byte_id28 @ 0x7fae4  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0544 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
