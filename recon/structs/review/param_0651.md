## review group param_0651  (1 cluster(s), kinds=param)

### proposal for param_0651
struct_name: flash_pages_info | is_library: True | library_name: Zephyr flash_map: struct flash_pages_info | is_array: None | confidence: medium
purpose: Flash page descriptor filled by flash_get_page_info_by_offs: start offset and size, matching Zephyr's flash_map API.
fields:
  0x4  uint32_t     start_offset  idx4
  0x8  uint32_t     size  idx4

<ground-truth bundle for param_0651>
### cluster param_0651  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - flash_get_page_info_by_offs @ 0x83a92  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0651 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
