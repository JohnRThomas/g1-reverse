## review group global_1328  (1 cluster(s), kinds=global)

### proposal for global_1328
struct_name: nrfx_pdm_cb_state | is_library: True | library_name: nrfx_pdm_cb_t | is_array: False | confidence: medium
purpose: Global nrfx PDM driver control block flags touched by nrfx_pdm_buffer_set.
fields:
  0x10  uint8_t      buffer_requested  boolean flag
  0x11  uint8_t      error_occurred  boolean flag

<ground-truth bundle for global_1328>
### cluster global_1328  (global, 1 members, 2 fields, size>=0x12)

Global object at fixed address 0x000662e8.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_pdm_buffer_set @ 0x66270  as 0x000662e8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1328 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=r types=char */
    uint8_t    field_0x11;   /* +0x11  sz=1 rw=r types=char */
};
```
