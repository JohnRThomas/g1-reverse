## review group param_0050  (1 cluster(s), kinds=param)

### proposal for param_0050
struct_name: event_record_desc | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Small descriptor passed to event_record_init: a 16-bit tag/type field followed by a 32-bit index/id
fields:
  0x2  uint16_t     tag  read-only, undefined2
  0x4  uint32_t     id  read-only idx4

<ground-truth bundle for param_0050>
### cluster param_0050  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - event_record_init @ 0x25090  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0050 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=undefined2 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
