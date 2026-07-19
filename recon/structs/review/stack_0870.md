## review group stack_0870  (1 cluster(s), kinds=stack)

### proposal for stack_0870
struct_name: flash_read_tmp | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Local temp holding a flash address/length pair inside read_sys_settting_from_flash
fields:
  0x0  uint32_t     flash_addr  r, idx4
  0x8  uint32_t     read_len  r, idx4

<ground-truth bundle for stack_0870>
### cluster stack_0870  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_94 in read_sys_settting_from_flash (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - read_sys_settting_from_flash @ 0x232f8  as local_94  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0870 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
