### cluster global_1480  (global, 1 members, 2 fields, size>=0x914)

Global object at fixed address 0x0007b518.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - InitAes @ 0x7b468  as 0x0007b518  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1480 {
    uint8_t    _pad_0x0[0x4c0];   /* +0x0 pad */
    uint32_t   field_0x4c0;   /* +0x4c0  sz=4 rw=w types=uint */
    uint8_t    _pad_0x4c4[0x44c];   /* +0x4c4 pad */
    uint32_t   field_0x910;   /* +0x910  sz=4 rw=r types=int */
};
```