## review group param_0586  (1 cluster(s), kinds=param)

### proposal for param_0586
struct_name: bt_le_conn_param | is_library: True | library_name: bt_le_conn_param | is_array: None | confidence: medium
purpose: BLE connection parameter set passed to bt_conn_le_param_update: interval/latency/timeout fields.
fields:
  0x4  uint32_t     interval_min_max  
  0x8  uint32_t     latency  
  0xc  uint32_t     timeout  

<ground-truth bundle for param_0586>
### cluster param_0586  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_conn_le_param_update @ 0x8157a  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0586 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
