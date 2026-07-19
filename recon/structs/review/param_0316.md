## review group param_0316  (1 cluster(s), kinds=param)

### proposal for param_0316
struct_name: wdt_timeout_cfg | is_library: True | library_name: wdt_timeout_cfg | is_array: None | confidence: medium
purpose: Zephyr watchdog driver timeout configuration structure passed to wdt_install_timeout.
fields:
  0x3  uint8_t      flags  watchdog flags/window byte
  0x4  uint32_t     window_max  callback pointer or window value

<ground-truth bundle for param_0316>
### cluster param_0316  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - wdt_install_timeout @ 0x63984  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0316 {
    uint8_t    _pad_0x0[0x3];   /* +0x0 pad */
    uint8_t    field_0x3;   /* +0x3  sz=1 rw=r types=byte */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
