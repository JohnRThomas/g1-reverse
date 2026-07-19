## review group global_1324  (1 cluster(s), kinds=global)

### proposal for global_1324
struct_name: pdm_init_state | is_library: True | library_name: nrfx_pdm_t (driver instance state) | is_array: False | confidence: low
purpose: Global config/state touched by nrfx_pdm_init (PDM microphone driver init), holding index handles.
fields:
  0x4  uint32_t     field_0x4  idx4, likely instance/channel index
  0x10  uint32_t     field_0x10  idx4, likely instance/channel index

<ground-truth bundle for global_1324>
### cluster global_1324  (global, 1 members, 2 fields, size>=0x14)

Global object at fixed address 0x000661cc.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_pdm_init @ 0x6615c  as 0x000661cc  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1324 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```
