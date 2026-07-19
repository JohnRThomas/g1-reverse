## review group param_0320  (1 cluster(s), kinds=param)

### proposal for param_0320
struct_name: flash_boot_swap_ate | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Flash boot-swap allocation table entry read by flash_read_boot_swap_ate
fields:
  0x4  uint32_t     field_0x4  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for param_0320>
### cluster param_0320  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - flash_read_boot_swap_ate @ 0x6403c  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0320 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```
