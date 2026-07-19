## review group param_0313  (1 cluster(s), kinds=param)

### proposal for param_0313
struct_name: uarte_nrfx_data | is_library: True | library_name: uarte_nrfx_data | is_array: None | confidence: low
purpose: nrfx UARTE driver runtime-data struct accessed by the power-management action callback (uarte_nrfx_pm_action) for device suspend/resume handling.
fields:
  0x4  void *       callback_or_cfg_ptr  read-only pointer
  0x10  uint32_t     pm_state  read-only int, power state

<ground-truth bundle for param_0313>
### cluster param_0313  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - uarte_nrfx_pm_action @ 0x62c54  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0313 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr,undefined4 */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```
