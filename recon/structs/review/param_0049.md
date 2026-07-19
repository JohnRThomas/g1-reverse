## review group param_0049  (1 cluster(s), kinds=param)

### proposal for param_0049
struct_name: event_record | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: G1-original event record initialized by event_record_init: five 32-bit payload/timestamp words plus a 16-bit type/id field.
fields:
  0x4  uint32_t     field1  
  0x8  uint32_t     field2  
  0xc  uint32_t     field3  
  0x10  uint32_t     field4  
  0x14  uint32_t     field5  
  0x18  uint16_t     record_type  

<ground-truth bundle for param_0049>
### cluster param_0049  (param, 1 members, 6 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - event_record_init @ 0x25090  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0049 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=w types=undefined4 */
    uint16_t   field_0x18;   /* +0x18  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x1a[0x2];   /* +0x1a pad */
};
```
