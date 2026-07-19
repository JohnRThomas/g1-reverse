## review group param_0537  (1 cluster(s), kinds=param)

### proposal for param_0537
struct_name: bt_ancs_attr_request | is_library: True | library_name: bt_ancs_c | is_array: None | confidence: low
purpose: ANCS attribute request record used by bt_ancs_request_attrs
fields:
  0x1  uint8_t      attr_id  
  0x6  uint8_t      get_all_flag  

<ground-truth bundle for param_0537>
### cluster param_0537  (param, 1 members, 2 fields, size>=0x7)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_ancs_request_attrs @ 0x7f6b6  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0537 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=byte */
    uint8_t    _pad_0x2[0x4];   /* +0x2 pad */
    uint8_t    field_0x6;   /* +0x6  sz=1 rw=r types=byte */
};
```
