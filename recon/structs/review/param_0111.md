## review group param_0111  (1 cluster(s), kinds=param)

### proposal for param_0111
struct_name: nav_overview_map_ctx | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Navigation overview map display context passed to navigation_overview_map_display.
fields:
  0x1  uint8_t      field_0x1  
  0xb1  uint32_t     field_0xb1  

<ground-truth bundle for param_0111>
### cluster param_0111  (param, 1 members, 2 fields, size>=0xb5)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - navigation_overview_map_display @ 0x3e05c  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0111 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=undefined1 */
    uint8_t    _pad_0x2[0xaf];   /* +0x2 pad */
    uint32_t   field_0xb1;   /* +0xb1  sz=4 rw=r types=int,undefined4 */
};
```
