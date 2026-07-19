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