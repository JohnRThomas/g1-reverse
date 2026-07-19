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