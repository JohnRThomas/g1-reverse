## review group param_0556  (1 cluster(s), kinds=param)

### proposal for param_0556
struct_name: image_version | is_library: True | library_name: image_version | is_array: None | confidence: high
purpose: MCUboot/MCUmgr struct image_version (major.minor.revision.build) compared by img_mgmt_vercmp during firmware image management.
fields:
  0x2  uint16_t     iv_revision  revision field, read
  0x4  uint32_t     iv_build_num  build number, read

<ground-truth bundle for param_0556>
### cluster param_0556  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - img_mgmt_vercmp @ 0x80970  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0556 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=ushort */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
