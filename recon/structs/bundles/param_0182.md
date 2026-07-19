### cluster param_0182  (param, 2 members, 4 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att,gatt; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - gatt_notify_send_chunked @ 0x52880  as param_1  [APPLICATION]
  - att_get_max_payload_len @ 0x80c7c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0182 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=int */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x12[0x6];   /* +0x12 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=int,uint */
    uint8_t    field_0x1c;   /* +0x1c  sz=1 rw=r types=char */
    uint8_t    _pad_0x1d[0x3];   /* +0x1d pad */
};
```