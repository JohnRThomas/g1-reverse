## review group param_0315  (1 cluster(s), kinds=param)

### proposal for param_0315
struct_name: wdt_timeout_cfg_ctx | is_library: True | library_name: struct wdt_timeout_cfg (Zephyr, partial) | is_array: None | confidence: low
purpose: Watchdog timeout configuration passed to wdt_install_timeout, holding a callback/window pointer near the front and a second pointer further in.
fields:
  0x4  void*        callback_ptr  
  0x10  void*        field_0x10  

<ground-truth bundle for param_0315>
### cluster param_0315  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - wdt_install_timeout @ 0x63984  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0315 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    void *     field_0x10;   /* +0x10  sz=4 rw=r types=ptr */
};
```
