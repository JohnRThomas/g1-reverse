### cluster param_0338  (param, 1 members, 16 fields, size>=0x2e)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - qspi_configure_pins_and_interface @ 0x66850  as param_1  [APPLICATION]

layout notes: 0x4: access width 4 exceeds gap 3 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0338 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint8_t    field_0x4[0x3];   /* +0x4 pad */
    uint8_t    field_0x7;   /* +0x7  sz=1 rw=r types=byte */
    uint32_t   field_0x8;   /* +0x8  sz=1,4 rw=r types=byte,idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x1c[0x1];   /* +0x1c pad */
    uint8_t    field_0x1d;   /* +0x1d  sz=1 rw=r types=byte */
    uint8_t    field_0x1e;   /* +0x1e  sz=1 rw=r types=byte */
    uint8_t    field_0x1f;   /* +0x1f  sz=1 rw=r types=byte */
    uint8_t    _pad_0x20[0x1];   /* +0x20 pad */
    uint8_t    field_0x21;   /* +0x21  sz=1 rw=r types=byte */
    uint8_t    field_0x22;   /* +0x22  sz=1 rw=r types=byte */
    uint8_t    field_0x23;   /* +0x23  sz=1 rw=r types=byte,char */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x28[0x1];   /* +0x28 pad */
    uint8_t    field_0x29;   /* +0x29  sz=1 rw=r types=char,undefined1 */
    uint8_t    field_0x2a;   /* +0x2a  sz=1 rw=r types=char */
    uint8_t    _pad_0x2b[0x3];   /* +0x2b pad */
};
```