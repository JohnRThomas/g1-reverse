## review group param_0680  (1 cluster(s), kinds=param)

### proposal for param_0680
struct_name: driver_active_timer_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Driver context holding an active timer handle/pointer and a related state word, used by driver_stop_active_timer
fields:
  0x4  void *       timer_ptr  
  0x10  uint32_t     timer_state  

<ground-truth bundle for param_0680>
### cluster param_0680  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - driver_stop_active_timer @ 0x84c2c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0680 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```
