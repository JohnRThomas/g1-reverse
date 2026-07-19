## review group param_0290  (1 cluster(s), kinds=param)

### proposal for param_0290
struct_name: adc_channel_cfg | is_library: True | library_name: adc_channel_cfg | is_array: None | confidence: medium
purpose: ADC channel configuration descriptor passed to adc_channel_config (gain/reference/acquisition-time/input pin fields).
fields:
  0x2  uint16_t     gain_ref_bits  read, packed gain/reference bitfield
  0x4  uint32_t     acquisition_time  read as idx4
  0x10  uint32_t     channel_id  read as idx4
  0x14  uint32_t     input_positive  read as idx4
  0x18  uint32_t     input_negative  read as idx4

<ground-truth bundle for param_0290>
### cluster param_0290  (param, 1 members, 5 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - adc_channel_config @ 0x5f654  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0290 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=ushort */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
};
```
