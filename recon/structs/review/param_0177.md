## review group param_0177  (1 cluster(s), kinds=param)

### proposal for param_0177
struct_name: img_mgmt_ver_info | is_library: True | library_name: img_mgmt_image_version | is_array: None | confidence: medium
purpose: Firmware image version info struct read by img_mgmt_ver_str (mcumgr img_mgmt)
fields:
  0x2  uint16_t     revision  
  0x4  uint32_t     build_num  

<ground-truth bundle for param_0177>
### cluster param_0177  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - img_mgmt_ver_str @ 0x51f88  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0177 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=ushort */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,int */
};
```
