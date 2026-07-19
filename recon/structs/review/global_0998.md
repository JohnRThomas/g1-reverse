## review group global_0998  (1 cluster(s), kinds=global)

### proposal for global_0998
struct_name: dashboard_reflash_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Global state block used by DashBoard_Reflash to track reflash progress flags and a counter/status value.
fields:
  0x19  uint8_t      field_0x19  flag/char read by reflash routine
  0x1a  uint8_t      field_0x1a  flag/char read by reflash routine
  0x1c  uint32_t     reflash_counter_or_status  

<ground-truth bundle for global_0998>
### cluster global_0998  (global, 1 members, 3 fields, size>=0x20)

Global object at fixed address 0x000374dc.

library hint: likely G1-original

members (1 shown of 1):
  - DashBoard_Reflash @ 0x3727c  as 0x000374dc  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0998 {
    uint8_t    _pad_0x0[0x19];   /* +0x0 pad */
    uint8_t    field_0x19;   /* +0x19  sz=1 rw=r types=char */
    uint8_t    field_0x1a;   /* +0x1a  sz=1 rw=r types=char */
    uint8_t    _pad_0x1b[0x1];   /* +0x1b pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=int */
};
```
