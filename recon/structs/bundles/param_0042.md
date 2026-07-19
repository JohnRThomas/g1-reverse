### cluster param_0042  (param, 2 members, 18 fields, size>=0x1078)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - build_and_send_device_status_report @ 0x22b00  as param_1  [APPLICATION]
  - load_sys_setting @ 0x22bd0  as param_1  [APPLICATION]

layout notes: overlap at 0xede (prev field ends 0xee0)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0042 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=rw types=undefined1 */
    uint8_t    field_0x3;   /* +0x3  sz=1 rw=rw types=undefined1 */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=rw types=undefined1 */
    uint8_t    _pad_0x5[0xecf];   /* +0x5 pad */
    uint8_t    field_0xed4;   /* +0xed4  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0xed5[0x5];   /* +0xed5 pad */
    uint16_t   field_0xeda;   /* +0xeda  sz=2 rw=rw types=undefined2 */
    uint32_t   field_0xedc;   /* +0xedc  sz=2,4 rw=rw types=undefined2,undefined4 */
    uint8_t    _pad_0xee0[0x84];   /* +0xee0 pad */
    uint32_t   field_0xf64;   /* +0xf64  sz=4 rw=rw types=undefined4 */
    uint8_t    _pad_0xf68[0x2c];   /* +0xf68 pad */
    uint32_t   field_0xf94;   /* +0xf94  sz=4 rw=rw types=undefined4 */
    uint8_t    _pad_0xf98[0x8];   /* +0xf98 pad */
    uint32_t   field_0xfa0;   /* +0xfa0  sz=4 rw=rw types=undefined4 */
    uint32_t   field_0xfa4;   /* +0xfa4  sz=4 rw=rw types=undefined4 */
    uint32_t   field_0xfa8;   /* +0xfa8  sz=4 rw=rw types=undefined4 */
    uint32_t   field_0xfac;   /* +0xfac  sz=4 rw=rw types=undefined4 */
    uint32_t   field_0xfb0;   /* +0xfb0  sz=4 rw=rw types=int,uint,undefined4 */
    uint32_t   field_0xfb4;   /* +0xfb4  sz=4 rw=rw types=undefined4 */
    uint8_t    _pad_0xfb8[0x98];   /* +0xfb8 pad */
    uint32_t   field_0x1050;   /* +0x1050  sz=4 rw=w types=int,undefined4 */
    uint8_t    _pad_0x1054[0x1e];   /* +0x1054 pad */
    uint16_t   field_0x1072;   /* +0x1072  sz=2 rw=rw types=short,undefined2,ushort */
    uint16_t   field_0x1074;   /* +0x1074  sz=2 rw=rw types=undefined2,ushort */
    uint8_t    _pad_0x1076[0x2];   /* +0x1076 pad */
};
```