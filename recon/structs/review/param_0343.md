## review group param_0343  (1 cluster(s), kinds=param)

### proposal for param_0343
struct_name: nrfx_spim_config_t | is_library: True | library_name: nrfx_spim_config_t | is_array: None | confidence: medium
purpose: nrfx SPIM peripheral configuration struct passed to nrfx_spim_configure (pin selects, IRQ priority, ORC, frequency/mode/bit-order flags).
fields:
  0x4  uint32_t     sck_pin  pin number, byte-or-word read
  0x8  uint32_t     mosi_pin  pin number
  0xc  uint32_t     miso_pin  pin number
  0x12  uint8_t      ss_active_high  bool flag byte
  0x14  uint32_t     irq_priority  read-only word
  0x19  uint8_t      orc  over-run character byte
  0x1a  uint8_t      frequency  enum byte
  0x1c  uint32_t     mode_or_ss_pin  read-only word
  0x21  uint8_t      bit_order  enum byte
  0x22  uint8_t      skip_gpio_cfg  bool flag byte
  0x23  uint8_t      skip_psel_cfg  bool flag byte

<ground-truth bundle for param_0343>
### cluster param_0343  (param, 1 members, 13 fields, size>=0x27)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_spim_configure @ 0x66ec0  as param_2  [APPLICATION]

layout notes: 0x4: access width 4 exceeds gap 2 to next field (overlap/union); 0x8: access width 4 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0343 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint16_t   field_0x4;   /* +0x4  sz=1,4 rw=r types=byte,idx4,undefined1 */
    uint8_t    field_0x6;   /* +0x6  sz=1 rw=r types=byte,char */
    uint8_t    _pad_0x7[0x1];   /* +0x7 pad */
    uint8_t    field_0x8;   /* +0x8  sz=1,4 rw=r types=byte,idx4 */
    uint8_t    field_0x9;   /* +0x9  sz=1 rw=r types=char */
    uint8_t    _pad_0xa[0x2];   /* +0xa pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x2];   /* +0x10 pad */
    uint8_t    field_0x12;   /* +0x12  sz=1 rw=r types=byte */
    uint8_t    _pad_0x13[0x1];   /* +0x13 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x1];   /* +0x18 pad */
    uint8_t    field_0x19;   /* +0x19  sz=1 rw=r types=byte */
    uint8_t    field_0x1a;   /* +0x1a  sz=1 rw=r types=undefined1 */
    uint8_t    _pad_0x1b[0x1];   /* +0x1b pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x20[0x1];   /* +0x20 pad */
    uint8_t    field_0x21;   /* +0x21  sz=1 rw=r types=char */
    uint8_t    field_0x22;   /* +0x22  sz=1 rw=r types=byte */
    uint8_t    field_0x23;   /* +0x23  sz=1 rw=r types=byte,char */
    uint8_t    _pad_0x24[0x3];   /* +0x24 pad */
};
```
