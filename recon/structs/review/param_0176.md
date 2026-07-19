## review group param_0176  (1 cluster(s), kinds=param)

### proposal for param_0176
struct_name: img_mgmt_state_ctx | is_library: True | library_name: img_mgmt (mcumgr) | is_array: False | confidence: low
purpose: mcumgr img_mgmt subsystem state object read/written by img_mgmt_state_read/write handlers
fields:
  0x4  int32_t      field_0x4  unclear specific mcumgr field
  0x8  int32_t      field_0x8  

<ground-truth bundle for param_0176>
### cluster param_0176  (param, 2 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - img_mgmt_state_read @ 0x51c98  as param_1  [APPLICATION]
  - img_mgmt_state_write @ 0x51e9c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0176 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
};
```
