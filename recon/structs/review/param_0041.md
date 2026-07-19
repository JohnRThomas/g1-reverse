## review group param_0041  (1 cluster(s), kinds=param)

### proposal for param_0041
struct_name: settings_init_params | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Initialization parameter block consumed by sett_init to configure a settings entry.
fields:
  0x4  uint32_t     field_0x4  init param, purpose unclear
  0x8  uint32_t     field_0x8  init param, purpose unclear
  0xc  uint32_t     field_0xc  init param, purpose unclear

<ground-truth bundle for param_0041>
### cluster param_0041  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - sett_init @ 0x22518  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0041 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
