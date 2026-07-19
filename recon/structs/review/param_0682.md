## review group param_0682  (1 cluster(s), kinds=param)

### proposal for param_0682
struct_name: watchdog_disable_work_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Watchdog-disable work context passed to watchdog_disable_write_work, holding a callback/device pointer and a second pointer further in (mirrors param_0315's wdt_timeout_cfg shape).
fields:
  0x4  void*        field_0x4  
  0x10  void*        field_0x10  

<ground-truth bundle for param_0682>
### cluster param_0682  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - watchdog_disable_write_work @ 0x84c94  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0682 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    void *     field_0x10;   /* +0x10  sz=4 rw=r types=ptr */
};
```
