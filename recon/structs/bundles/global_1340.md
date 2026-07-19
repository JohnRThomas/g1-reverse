### cluster global_1340  (global, 1 members, 6 fields, size>=0x540)

Global object at fixed address 0x0006684c.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - qspi_workaround_apply @ 0x667e0  as 0x0006684c  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1340 {
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