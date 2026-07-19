## review group param_0186  (1 cluster(s), kinds=param)

### proposal for param_0186
struct_name: bt_uuid_128_buf | is_library: True | library_name: struct bt_uuid_128 | is_array: False | confidence: medium
purpose: 128-bit Bluetooth UUID expansion buffer built by bt_uuid_expand_to_128: a leading type/marker word followed by the 16-byte UUID value stored as four 32-bit words.
fields:
  0x0  uint32_t     uuid_type  
  0x34  uint32_t     val_word0  
  0x38  uint32_t     val_word1  
  0x3c  uint32_t     val_word2  
  0x40  uint32_t     val_word3  

<ground-truth bundle for param_0186>
### cluster param_0186  (param, 1 members, 5 fields, size>=0x44)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_uuid_expand_to_128 @ 0x531e4  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0186 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x4[0x30];   /* +0x4 pad */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=idx4 */
};
```
