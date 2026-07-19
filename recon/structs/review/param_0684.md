## review group param_0684  (1 cluster(s), kinds=param)

### proposal for param_0684
struct_name: wdt_channel_ctx | is_library: True | library_name: nrfx_wdt / WDT_Type | is_array: False | confidence: low
purpose: Watchdog timer channel/instance handle fed by wdt_nrf_feed to reload the hardware watchdog
fields:
  0x4  uint32_t     channel_mask  
  0x10  int32_t      reload_status  

<ground-truth bundle for param_0684>
### cluster param_0684  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - wdt_nrf_feed @ 0x84cda  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0684 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```
