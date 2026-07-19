## review group stack_1118  (1 cluster(s), kinds=stack)

### proposal for stack_1118
struct_name: img_mgmt_flash_area_info | is_library: True | library_name: struct flash_area (Zephyr, partial) | is_array: None | confidence: low
purpose: Local copy of flash-area fields (offset/size) used by img_mgmt_erased_val to read the erased-value setting for an image slot.
fields:
  0x0  uint32_t     fa_off  
  0x8  uint32_t     fa_size  

<ground-truth bundle for stack_1118>
### cluster stack_1118  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_1c in img_mgmt_erased_val (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - img_mgmt_erased_val @ 0x51a5c  as local_1c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1118 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
