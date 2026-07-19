## review group param_0364  (1 cluster(s), kinds=param)

### proposal for param_0364
struct_name: lc3_attdet_state | is_library: True | library_name: lc3 codec internal (attack detector state) | is_array: False | confidence: low
purpose: LC3 codec attack-detector substate accessed by lc3_attdet_run.
fields:
  0x4  int32_t      field_0x4  index/state value
  0x8  int32_t      field_0x8  index/state value

<ground-truth bundle for param_0364>
### cluster param_0364  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_attdet_run @ 0x682f0  as param_4  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0364 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
