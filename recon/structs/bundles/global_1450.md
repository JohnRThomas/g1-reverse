### cluster global_1450  (global, 1 members, 2 fields, size>=0xa0c)

Global object at fixed address 0x0007a2a8.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - CC_HalClearInterruptBit @ 0x7a290  as 0x0007a2a8  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1450 {
    uint8_t    _pad_0x0[0x108];   /* +0x0 pad */
    uint32_t   field_0x108;   /* +0x108  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x10c[0x8fc];   /* +0x10c pad */
    uint32_t   field_0xa08;   /* +0xa08  sz=4 rw=w types=int */
};
```