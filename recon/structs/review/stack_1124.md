## review group stack_1124  (1 cluster(s), kinds=stack)

### proposal for stack_1124
struct_name: img_mgmt_info_local | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Stack-local pair of 32-bit values (e.g. hash pointer and length) used inside img_mgmt_read_info.
fields:
  0x0  uint32_t     field_0x0  pointer or handle value
  0x8  uint32_t     field_0x8  length or slot index

<ground-truth bundle for stack_1124>
### cluster stack_1124  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_40 in img_mgmt_read_info (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - img_mgmt_read_info @ 0x52038  as local_40  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1124 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
