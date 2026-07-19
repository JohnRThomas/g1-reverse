## review group param_0539  (1 cluster(s), kinds=param)

### proposal for param_0539
struct_name: bt_ancs_app_attr_ctx | is_library: True | library_name: bt_ancs_client app-attribute registration context | is_array: False | confidence: low
purpose: Large context (>=0x8f8) passed to bt_ancs_register_app_attr (ANCS app-attribute registration); holds a byte flag and two trailing fields likely representing a registered attribute list count/handle.
fields:
  0x8e8  uint8_t      field_0x8e8  write-only flag
  0x8f0  uint16_t     field_0x8f0  write-only, count/length
  0x8f4  int32_t      field_0x8f4  write-only status

<ground-truth bundle for param_0539>
### cluster param_0539  (param, 1 members, 3 fields, size>=0x8f8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_ancs_register_app_attr @ 0x7f79e  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0539 {
    uint8_t    _pad_0x0[0x8e8];   /* +0x0 pad */
    uint8_t    field_0x8e8;   /* +0x8e8  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x8e9[0x7];   /* +0x8e9 pad */
    uint16_t   field_0x8f0;   /* +0x8f0  sz=2 rw=w types=short */
    uint8_t    _pad_0x8f2[0x2];   /* +0x8f2 pad */
    uint32_t   field_0x8f4;   /* +0x8f4  sz=4 rw=w types=int */
};
```
