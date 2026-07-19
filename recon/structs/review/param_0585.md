## review group param_0585  (1 cluster(s), kinds=param)

### proposal for param_0585
struct_name: bt_conn | is_library: True | library_name: struct bt_conn | is_array: None | confidence: medium
purpose: Zephyr Bluetooth connection object; enc_key_size-style byte field and a later uint accessed by bt_conn_enc_key_size.
fields:
  0xb  uint8_t      field_0xb  
  0xc0  uint32_t     field_0xc0  

<ground-truth bundle for param_0585>
### cluster param_0585  (param, 1 members, 2 fields, size>=0xc4)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_conn_enc_key_size @ 0x8148a  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0585 {
    uint8_t    _pad_0x0[0xb];   /* +0x0 pad */
    uint8_t    field_0xb;   /* +0xb  sz=1 rw=r types=byte */
    uint8_t    _pad_0xc[0xb4];   /* +0xc pad */
    uint32_t   field_0xc0;   /* +0xc0  sz=4 rw=r types=uint */
};
```
