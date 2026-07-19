## review group param_0035  (1 cluster(s), kinds=param)

### proposal for param_0035
struct_name: bt_ancs_attr_data | is_library: True | library_name: bt_ancs_c (nRF Connect SDK ANCS client) | is_array: None | confidence: low
purpose: ANCS (Apple Notification Center Service) attribute data-source record passed through bt_ancs_data_source_handler
fields:
  0x4  uint32_t     attr_id  
  0x8  uint32_t     attr_len  
  0xc  void*        attr_data_ptr  

<ground-truth bundle for param_0035>
### cluster param_0035  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_ancs_data_source_handler @ 0x18c48  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0035 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
};
```
