## review group param_0571  (1 cluster(s), kinds=param)

### proposal for param_0571
struct_name: bt_conn_security | is_library: True | library_name: bt_conn | is_array: None | confidence: medium
purpose: Zephyr bt_conn security-level related fields updated by update_sec_level (part of bt_conn/security manager state)
fields:
  0x9  uint8_t      sec_level  written byte
  0xa  uint8_t      required_sec_level  read byte
  0xc0  int32_t      field_0xc0  int

<ground-truth bundle for param_0571>
### cluster param_0571  (param, 1 members, 3 fields, size>=0xc4)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - update_sec_level @ 0x80e38  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0571 {
    uint8_t    _pad_0x0[0x9];   /* +0x0 pad */
    uint8_t    field_0x9;   /* +0x9  sz=1 rw=w types=byte */
    uint8_t    field_0xa;   /* +0xa  sz=1 rw=r types=byte */
    uint8_t    _pad_0xb[0xb5];   /* +0xb pad */
    uint32_t   field_0xc0;   /* +0xc0  sz=4 rw=r types=int */
};
```
