### cluster global_1347  (global, 1 members, 6 fields, size>=0x540)

Global object at fixed address 0x00066bc0.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_qspi_uninit @ 0x66b24  as 0x00066bc0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1347 {
    uint8_t    _pad_0x0[0x524];   /* +0x0 pad */
    uint32_t   field_0x524;   /* +0x524  sz=4 rw=r types=uint */
    uint32_t   field_0x528;   /* +0x528  sz=4 rw=r types=uint */
    uint8_t    _pad_0x52c[0x4];   /* +0x52c pad */
    uint32_t   field_0x530;   /* +0x530  sz=4 rw=r types=uint */
    uint32_t   field_0x534;   /* +0x534  sz=4 rw=r types=uint */
    uint32_t   field_0x538;   /* +0x538  sz=4 rw=r types=uint */
    uint32_t   field_0x53c;   /* +0x53c  sz=4 rw=r types=uint */
};
```