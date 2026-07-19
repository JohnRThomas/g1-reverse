## review group param_0179  (1 cluster(s), kinds=param)

### proposal for param_0179
struct_name: img_mgmt_upload_ctx | is_library: True | library_name: img_mgmt_upload_action | is_array: None | confidence: medium
purpose: MCUmgr img_mgmt image-upload action/context struct used by img_mgmt_upload
fields:
  0x4  int32_t      offset_or_len  int
  0x8  int32_t      total_or_status  int/undefined4

<ground-truth bundle for param_0179>
### cluster param_0179  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - img_mgmt_upload @ 0x521fc  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0179 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int,undefined4 */
};
```
