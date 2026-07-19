## review group param_0664  (1 cluster(s), kinds=param)

### proposal for param_0664
struct_name: dev_channel_dispatch_entry | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Dispatch-table entry read by dev_channel_dispatch_lookup: channel id and associated handler/index word.
fields:
  0x4  int32_t      channel_id  
  0x8  int32_t      handler_or_index  

<ground-truth bundle for param_0664>
### cluster param_0664  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - dev_channel_dispatch_lookup @ 0x84090  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0664 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
};
```
