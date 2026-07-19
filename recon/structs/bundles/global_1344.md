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