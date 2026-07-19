## review group param_0292  (1 cluster(s), kinds=param)

### proposal for param_0292
struct_name: pdm_start_state | is_library: True | library_name: nrfx_pdm_cb_t | is_array: False | confidence: low
purpose: nrfx PDM driver state flags checked/set by pdm_start_and_check while starting the microphone stream.
fields:
  0x14  uint8_t      started_flag  read byte flag
  0x51  uint8_t      error_flag  write-only byte flag

<ground-truth bundle for param_0292>
### cluster param_0292  (param, 1 members, 2 fields, size>=0x52)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - pdm_start_and_check @ 0x5fb30  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0292 {
    uint8_t    _pad_0x0[0x14];   /* +0x0 pad */
    uint8_t    field_0x14;   /* +0x14  sz=1 rw=r types=byte */
    uint8_t    _pad_0x15[0x3c];   /* +0x15 pad */
    uint8_t    field_0x51;   /* +0x51  sz=1 rw=w types=undefined1 */
};
```
