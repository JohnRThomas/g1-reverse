## review group param_0045  (1 cluster(s), kinds=param)

### proposal for param_0045
struct_name: sys_settings_record | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: On-flash system settings record read by read_sys_settting_from_flash
fields:
  0x2  uint8_t      valid_flag  w
  0x5  uint8_t      version  w
  0xc  uint32_t     magic_or_crc_a  r, idx4
  0x10  uint32_t     magic_or_crc_b  r, idx4
  0x1e  uint16_t     length  w
  0x55  uint8_t      flag_a  w
  0x56  uint8_t      flag_b  w
  0x60  uint32_t     field_0  r, idx4
  0x64  uint32_t     field_1  r, idx4
  0x68  uint32_t     field_2  r, idx4
  0x6c  uint32_t     field_3  r, idx4
  0x70  uint32_t     field_4  r, idx4
  0x74  uint32_t     field_5  r, idx4
  0x7c  uint32_t     tail_0  r, idx4
  0x80  uint32_t     tail_1  r, idx4

<ground-truth bundle for param_0045>
### cluster param_0045  (param, 1 members, 15 fields, size>=0x84)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - read_sys_settting_from_flash @ 0x232f8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0045 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x3[0x2];   /* +0x3 pad */
    uint8_t    field_0x5;   /* +0x5  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x6[0x6];   /* +0x6 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x14[0xa];   /* +0x14 pad */
    uint16_t   field_0x1e;   /* +0x1e  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x20[0x35];   /* +0x20 pad */
    uint8_t    field_0x55;   /* +0x55  sz=1 rw=w types=undefined1 */
    uint8_t    field_0x56;   /* +0x56  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x57[0x9];   /* +0x57 pad */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=r types=idx4 */
    uint32_t   field_0x64;   /* +0x64  sz=4 rw=r types=idx4 */
    uint32_t   field_0x68;   /* +0x68  sz=4 rw=r types=idx4 */
    uint32_t   field_0x6c;   /* +0x6c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x70;   /* +0x70  sz=4 rw=r types=idx4 */
    uint32_t   field_0x74;   /* +0x74  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x78[0x4];   /* +0x78 pad */
    uint32_t   field_0x7c;   /* +0x7c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x80;   /* +0x80  sz=4 rw=r types=idx4 */
};
```
