## review group global_1272  (1 cluster(s), kinds=global)

### proposal for global_1272
struct_name: pdm_mic_event_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Global state for PDM microphone driver event handler (small config/status region + flag byte)
fields:
  0x14  uint32_t     field_0x14  
  0x52  uint8_t      status_flag  single byte flag read near end of struct

<ground-truth bundle for global_1272>
### cluster global_1272  (global, 1 members, 2 fields, size>=0x56)

Global object at fixed address 0x000600e0.

library hint: likely G1-original

members (1 shown of 1):
  - pdm_mic_event_handler @ 0x5ffa4  as 0x000600e0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1272 {
    uint8_t    _pad_0x0[0x14];   /* +0x0 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x3a];   /* +0x18 pad */
    uint8_t    field_0x52;   /* +0x52  sz=1 rw=r types=char */
    uint8_t    _pad_0x53[0x3];   /* +0x53 pad */
};
```
