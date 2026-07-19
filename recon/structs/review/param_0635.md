## review group param_0635  (1 cluster(s), kinds=param)

### proposal for param_0635
struct_name: bt_conn_sec_info | is_library: True | library_name: bt_conn (partial) | is_array: None | confidence: low
purpose: Bluetooth connection security-level fragment inspected by bt_conn_security_sufficient (encryption key size, security level, and an associated ushort field).
fields:
  0xc  uint8_t      sec_level  read-only byte
  0xd  uint8_t      enc_key_size  read-only byte
  0xe  uint16_t     flags  read-only ushort

<ground-truth bundle for param_0635>
### cluster param_0635  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_conn_security_sufficient @ 0x83002  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0635 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint8_t    field_0xc;   /* +0xc  sz=1 rw=r types=byte */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=r types=byte */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=r types=ushort */
};
```
