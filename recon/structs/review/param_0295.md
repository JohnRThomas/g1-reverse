## review group param_0295  (1 cluster(s), kinds=param)

### proposal for param_0295
struct_name: nrfx_pdm_config | is_library: True | library_name: nrfx_pdm_config_t (Nordic nrfx PDM driver) | is_array: None | confidence: medium
purpose: nrfx PDM microphone peripheral configuration passed to pdm_configure_clock_and_init: pin/clock word followed by six consecutive configuration words (pins, mode, edge, gain).
fields:
  0x4  uint32_t     pin_clk  idx4
  0x10  uint32_t     pin_din  idx4
  0x14  uint32_t     mode  idx4
  0x18  uint32_t     edge  idx4
  0x1c  uint32_t     clock_freq  idx4
  0x20  uint32_t     gain_l  idx4
  0x24  uint32_t     gain_r  idx4

<ground-truth bundle for param_0295>
### cluster param_0295  (param, 1 members, 10 fields, size>=0x2b)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - pdm_configure_clock_and_init @ 0x5fc7c  as param_2  [APPLICATION]

layout notes: 0x24: access width 4 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0295 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint8_t    field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint8_t    field_0x25;   /* +0x25  sz=1 rw=w types=byte,undefined1 */
    uint8_t    field_0x26;   /* +0x26  sz=1 rw=r types=char */
    uint8_t    field_0x27;   /* +0x27  sz=1 rw=w types=byte,undefined1 */
    uint8_t    _pad_0x28[0x3];   /* +0x28 pad */
};
```
