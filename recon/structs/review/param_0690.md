## review group param_0690  (1 cluster(s), kinds=param)

### proposal for param_0690
struct_name: nrfx_spim_cb | is_library: True | library_name: nrfx_spim_cb_t | is_array: None | confidence: medium
purpose: nrfx SPIM driver control block accessed by spim_abort
fields:
  0x14  uint32_t     state_or_flags  written undefined4
  0x500  uint32_t     abort_flag  written undefined4, trailer field

<ground-truth bundle for param_0690>
### cluster param_0690  (param, 1 members, 2 fields, size>=0x504)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - spim_abort @ 0x852ba  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0690 {
    uint8_t    _pad_0x0[0x14];   /* +0x0 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x18[0x4e8];   /* +0x18 pad */
    uint32_t   field_0x500;   /* +0x500  sz=4 rw=w types=undefined4 */
};
```
