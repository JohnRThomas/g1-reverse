### cluster param_0221  (param, 5 members, 16 fields, size>=0xbc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt,l2cap; 0/5 members are LIBRARY-class)

members (5 shown of 5):
  - l2cap_chan_send_disconnect @ 0x5774c  as param_1  [APPLICATION]
  - l2cap_chan_le_recv_seg @ 0x57a04  as param_1  [APPLICATION]
  - l2cap_le_recv_pdu @ 0x57b60  as param_1  [APPLICATION]
  - gatt_notify_send @ 0x8199a  as param_1  [APPLICATION]
  - gatt_send_service_changed_ind @ 0x81b30  as param_1  [APPLICATION]

layout notes: overlap at 0x5 (prev field ends 0x8); overlap at 0x16 (prev field ends 0x18)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0221 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,int */
    uint8_t    _pad_0x8[0xc];   /* +0x8 pad */
    uint32_t   field_0x14;   /* +0x14  sz=2,4 rw=r types=idx4,undefined2 */
    uint16_t   field_0x18;   /* +0x18  sz=2 rw=r types=undefined2,ushort */
    uint8_t    _pad_0x1a[0x2];   /* +0x1a pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x20[0x1];   /* +0x20 pad */
    uint16_t   field_0x21;   /* +0x21  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x23[0x1];   /* +0x23 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x28[0x5];   /* +0x28 pad */
    uint8_t    field_0x2d;   /* +0x2d  sz=1 rw=rw types=char,undefined1 */
    uint8_t    field_0x2e;   /* +0x2e  sz=1 rw=w types=char */
    uint8_t    _pad_0x2f[0x1d];   /* +0x2f pad */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x50[0x30];   /* +0x50 pad */
    uint32_t   field_0x80;   /* +0x80  sz=4 rw=rw types=idx4,int,undefined4 */
    uint16_t   field_0x84;   /* +0x84  sz=2 rw=rw types=short,undefined2,ushort */
    uint8_t    _pad_0x86[0x2e];   /* +0x86 pad */
    uint8_t    field_0xb4;   /* +0xb4  sz=1 rw=r types=byte,char */
    uint8_t    _pad_0xb5[0x1];   /* +0xb5 pad */
    uint16_t   field_0xb6;   /* +0xb6  sz=2 rw=r types=undefined2 */
    uint8_t    field_0xb8;   /* +0xb8  sz=1 rw=w types=char */
    uint8_t    _pad_0xb9[0x3];   /* +0xb9 pad */
};
```