### cluster param_0007  (param, 8 members, 29 fields, size>=0x1578)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (8 shown of 8):
  - random @ 0x17f70  as param_2  [APPLICATION]
  - parse_receiver_pack_pkcs7 @ 0x19cd0  as param_2  [APPLICATION]
  - parse_receiver_msg_pack_pkcs7 @ 0x19da4  as param_2  [APPLICATION]
  - build_status_notify_packet @ 0x21334  as param_2  [APPLICATION]
  - ble_process_req_dispatch @ 0x21460  as param_3  [APPLICATION]
  - post_notification_cmd_process @ 0x338ec  as param_3  [APPLICATION]
  - push_message @ 0x33f54  as param_1  [APPLICATION]
  - battery_soc_curve_model_init @ 0xe53c  as param_7  [APPLICATION]

layout notes: overlap at 0x2 (prev field ends 0x3); overlap at 0x5 (prev field ends 0x8); overlap at 0x6 (prev field ends 0x8); overlap at 0x7 (prev field ends 0x8); overlap at 0xd (prev field ends 0x10); overlap at 0xe (prev field ends 0x10); overlap at 0xf (prev field ends 0x10)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0007 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint16_t   field_0x1;   /* +0x1  sz=1,2 rw=r types=byte,short,undefined1 */
    uint8_t    field_0x3;   /* +0x3  sz=1 rw=r types=byte,char,undefined1 */
    uint32_t   field_0x4;   /* +0x4  sz=1,4 rw=r types=byte,char,idx4,undefined1,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=1,4 rw=r types=idx4,undefined1,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=1,4 rw=rw types=byte,idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x198];   /* +0x18 pad */
    uint32_t   field_0x1b0;   /* +0x1b0  sz=4 rw=r types=int,undefined4 */
    uint8_t    _pad_0x1b4[0x170];   /* +0x1b4 pad */
    float      field_0x324;   /* +0x324  sz=4 rw=r types=float */
    float      field_0x328;   /* +0x328  sz=4 rw=r types=float */
    float      field_0x32c;   /* +0x32c  sz=4 rw=r types=float */
    float      field_0x330;   /* +0x330  sz=4 rw=r types=float */
    float      field_0x334;   /* +0x334  sz=4 rw=r types=float */
    uint8_t    _pad_0x338[0x1dc];   /* +0x338 pad */
    float      field_0x514;   /* +0x514  sz=4 rw=r types=float */
    uint8_t    _pad_0x518[0xc90];   /* +0x518 pad */
    float      field_0x11a8;   /* +0x11a8  sz=4 rw=r types=float */
    float      field_0x11ac;   /* +0x11ac  sz=4 rw=r types=float */
    uint8_t    _pad_0x11b0[0x1d8];   /* +0x11b0 pad */
    float      field_0x1388;   /* +0x1388  sz=4 rw=r types=float */
    float      field_0x138c;   /* +0x138c  sz=4 rw=r types=float */
    float      field_0x1390;   /* +0x1390  sz=4 rw=r types=float */
    float      field_0x1394;   /* +0x1394  sz=4 rw=r types=float */
    uint8_t    _pad_0x1398[0x1d8];   /* +0x1398 pad */
    float      field_0x1570;   /* +0x1570  sz=4 rw=r types=float */
    float      field_0x1574;   /* +0x1574  sz=4 rw=r types=float */
};
```