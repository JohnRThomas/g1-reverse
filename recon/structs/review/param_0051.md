## review group param_0051  (1 cluster(s), kinds=param)

### proposal for param_0051
struct_name: record_type8 | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Output record structure filled by fill_record_type8 with five leading fields and a trailing index at 0x60
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x60  uint32_t     field_0x60  

<ground-truth bundle for param_0051>
### cluster param_0051  (param, 1 members, 6 fields, size>=0x64)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - fill_record_type8 @ 0x250c4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0051 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x18[0x48];   /* +0x18 pad */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=r types=idx4 */
};
```
