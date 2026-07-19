## review group param_0297  (1 cluster(s), kinds=param)

### proposal for param_0297
struct_name: clock_control_async_data | is_library: True | library_name: onoff_client / clock control internal state (best-effort) | is_array: False | confidence: low
purpose: nRF clock control on/off driver-side state: an initial status word and a completion/result word, accessed by clock_control_nrf_on.
fields:
  0x4  int          status  
  0x10  int          result  

<ground-truth bundle for param_0297>
### cluster param_0297  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - clock_control_nrf_on @ 0x604e4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0297 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```
