### cluster global_1068  (global, 1 members, 4 fields, size>=0x28)

Global object at fixed address 0x0004d590.

library hint: LIKELY LIBRARY (prefixes: log; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - log_process @ 0x4d594  as 0x0004d590  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1068 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=uint */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint */
    uint8_t    _pad_0xc[0x4];   /* +0xc pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
    uint8_t    _pad_0x14[0x10];   /* +0x14 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=uint */
};
```