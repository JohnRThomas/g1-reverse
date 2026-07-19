## review group global_1344  (1 cluster(s), kinds=global)

### proposal for global_1344
struct_name: nrfx_qspi_cinstr_ctx | is_library: True | library_name: nrfx_qspi (internal cinstr state) | is_array: None | confidence: low
purpose: Global context used by nrfx QSPI custom-instruction transfer
fields:
  0x30  char         field_0x30  
  0x38  char         field_0x38  

<ground-truth bundle for global_1344>
### cluster global_1344  (global, 1 members, 2 fields, size>=0x39)

Global object at fixed address 0x00066adc.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_qspi_cinstr_xfer @ 0x669f4  as 0x00066adc  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1344 {
    uint8_t    _pad_0x0[0x30];   /* +0x0 pad */
    uint8_t    field_0x30;   /* +0x30  sz=1 rw=r types=char */
    uint8_t    _pad_0x31[0x7];   /* +0x31 pad */
    uint8_t    field_0x38;   /* +0x38  sz=1 rw=r types=char */
};
```
