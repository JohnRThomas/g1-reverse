## review group param_0331  (1 cluster(s), kinds=param)

### proposal for param_0331
struct_name: gpiote_trigger_ctx | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Small context struct passed to gpiote_trigger_enable identifying a GPIOTE channel/pin pair.
fields:
  0x4  uint32_t     channel_or_pin  index value
  0x8  uint32_t     config_word  index/config value

<ground-truth bundle for param_0331>
### cluster param_0331  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - gpiote_trigger_enable @ 0x657e4  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0331 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
