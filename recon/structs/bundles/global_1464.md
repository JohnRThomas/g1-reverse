### cluster global_1464  (global, 1 members, 2 fields, size>=0x1dc)

Global object at fixed address 0x0007a62c.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - startTrngHW @ 0x7a50c  as 0x0007a62c  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1464 {
    uint8_t    _pad_0x0[0x1c4];   /* +0x0 pad */
    uint32_t   field_0x1c4;   /* +0x1c4  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x1c8[0x10];   /* +0x1c8 pad */
    uint32_t   field_0x1d8;   /* +0x1d8  sz=4 rw=w types=uint */
};
```