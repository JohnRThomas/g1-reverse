### cluster param_0421  (param, 3 members, 12 fields, size>=0x5c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (3 shown of 3):
  - printf_render_float @ 0x7712c  as param_2  [APPLICATION]
  - vfprintf_format_engine @ 0x77594  as param_2  [APPLICATION]
  - vfprintf_emit_padded_field @ 0x86e1c  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0421 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x1c[0x26];   /* +0x1c pad */
    uint8_t    field_0x42;   /* +0x42  sz=1 rw=w types=byte,char */
    uint8_t    field_0x43;   /* +0x43  sz=1 rw=rw types=byte,char,undefined1 */
    uint8_t    _pad_0x44[0x1];   /* +0x44 pad */
    uint8_t    field_0x45;   /* +0x45  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    _pad_0x46[0x2];   /* +0x46 pad */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x50[0x8];   /* +0x50 pad */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=r types=idx4 */
};
```