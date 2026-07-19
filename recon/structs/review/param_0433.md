## review group param_0433  (1 cluster(s), kinds=param)

### proposal for param_0433
struct_name: scanf_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: scanf-style integer-field conversion context/state for scanf_convert_integer_field
fields:
  0x0  void*        callback_or_vtable  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x18  uint32_t     field_0x18  
  0x17c  uint32_t     field_0x17c  
  0x180  uint32_t     field_0x180  

<ground-truth bundle for param_0433>
### cluster param_0433  (param, 1 members, 9 fields, size>=0x184)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - scanf_convert_integer_field @ 0x7932c  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0433 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x1c[0x160];   /* +0x1c pad */
    uint32_t   field_0x17c;   /* +0x17c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x180;   /* +0x180  sz=4 rw=r types=idx4 */
};
```
