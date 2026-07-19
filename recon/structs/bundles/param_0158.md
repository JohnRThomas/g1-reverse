### cluster param_0158  (param, 3 members, 17 fields, size>=0x90c)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/3 members are LIBRARY-class)

members (3 shown of 3):
  - bt_ancs_cp_write @ 0x4f198  as param_1  [APPLICATION]
  - bt_ancs_request_attrs @ 0x7f6b6  as param_1  [APPLICATION]
  - bt_ancs_app_attr_request @ 0x7f7d2  as param_1  [APPLICATION]

layout notes: 0x4: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0158 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=undefined2 */
    uint16_t   field_0x4;   /* +0x4  sz=4 rw=rw types=uint */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=w types=undefined2 */
    uint16_t   field_0x8;   /* +0x8  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0xa[0xa];   /* +0xa pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x2];   /* +0x18 pad */
    uint16_t   field_0x1a;   /* +0x1a  sz=2 rw=w types=undefined2 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x20[0x4];   /* +0x20 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint8_t    field_0x28;   /* +0x28  sz=1 rw=w types=undefined1 */
    uint8_t    field_0x29;   /* +0x29  sz=1 rw=w types=char */
    uint8_t    field_0x2a;   /* +0x2a  sz=1 rw=w types=char */
    uint8_t    field_0x2b;   /* +0x2b  sz=1 rw=w types=char */
    uint8_t    field_0x2c;   /* +0x2c  sz=1 rw=w types=char */
    uint8_t    _pad_0x2d[0x8bb];   /* +0x2d pad */
    uint8_t    field_0x8e8;   /* +0x8e8  sz=1 rw=r types=char */
    uint8_t    _pad_0x8e9[0xf];   /* +0x8e9 pad */
    uint32_t   field_0x8f8;   /* +0x8f8  sz=4 rw=rw types=int,undefined4 */
    uint8_t    _pad_0x8fc[0x8];   /* +0x8fc pad */
    uint32_t   field_0x904;   /* +0x904  sz=4 rw=w types=undefined4 */
    uint8_t    field_0x908;   /* +0x908  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x909[0x3];   /* +0x909 pad */
};
```