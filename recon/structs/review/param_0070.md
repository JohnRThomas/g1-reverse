## review group param_0070  (1 cluster(s), kinds=param)

### proposal for param_0070
struct_name: orientation_filter_state | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Tail of an orientation/IMU filter state struct; orientation_filter_update_dt updates a tick counter and writes the computed delta-time as float.
fields:
  0x38  uint32_t     last_update_tick  
  0x3c  uint32_t     tick_delta  
  0x40  float        dt_seconds  

<ground-truth bundle for param_0070>
### cluster param_0070  (param, 1 members, 3 fields, size>=0x44)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - orientation_filter_update_dt @ 0x267ac  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0070 {
    uint8_t    _pad_0x0[0x38];   /* +0x0 pad */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=w types=uint */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=rw types=int,uint */
    float      field_0x40;   /* +0x40  sz=4 rw=w types=float */
};
```
