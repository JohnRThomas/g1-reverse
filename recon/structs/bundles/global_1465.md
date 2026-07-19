### cluster global_1465  (global, 1 members, 2 fields, size>=0x13c)

Global object at fixed address 0x0007a9ac.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - getTrngSource @ 0x7a720  as 0x0007a9ac  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1465 {
    uint8_t    _pad_0x0[0x130];   /* +0x0 pad */
    uint32_t   field_0x130;   /* +0x130  sz=4 rw=r types=int */
    uint8_t    _pad_0x134[0x4];   /* +0x134 pad */
    uint32_t   field_0x138;   /* +0x138  sz=4 rw=r types=int */
};
```