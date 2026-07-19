### cluster global_1562  (global, 1 members, 2 fields, size>=0x3c)

Global object at fixed address 0x0006661c.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_qspi_write @ 0x85200  as 0x0006661c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1562 {
    uint8_t    _pad_0x0[0x30];   /* +0x0 pad */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x34[0x4];   /* +0x34 pad */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
};
```