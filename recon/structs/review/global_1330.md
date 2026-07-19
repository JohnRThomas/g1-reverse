## review group global_1330  (1 cluster(s), kinds=global)

### proposal for global_1330
struct_name: pdm_capture_buffer_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Static PDM (pulse density modulation) microphone capture buffer/state used around nrfx_pdm_stop; a large opaque buffer (~0x4f8 bytes) bracketed by a status/count word at each end.
fields:
  0x4  uint32_t     field_0x4  write-only uint, possibly sample counter or state flag
  0x500  uint32_t     field_0x500  write-only, possibly completion flag/index after buffer

<ground-truth bundle for global_1330>
### cluster global_1330  (global, 1 members, 2 fields, size>=0x504)

Global object at fixed address 0x00066360.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_pdm_stop @ 0x66300  as 0x00066360  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1330 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=w types=uint */
    uint8_t    _pad_0x8[0x4f8];   /* +0x8 pad */
    uint32_t   field_0x500;   /* +0x500  sz=4 rw=w types=undefined4 */
};
```
