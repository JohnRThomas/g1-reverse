## review group param_0001  (1 cluster(s), kinds=param)

### proposal for param_0001
struct_name: battery_model_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Battery fuel-gauge model state passed to battery_model_state_update holding raw ADC/lookup-table indices.
fields:
  0x4  uint32_t     voltage_idx  read-only, idx4 access
  0x8  uint32_t     current_idx  read-only, idx4 access
  0xc  uint32_t     temp_idx  read-only, idx4 access

<ground-truth bundle for param_0001>
### cluster param_0001  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - battery_model_state_update @ 0xc358  as param_8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0001 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
