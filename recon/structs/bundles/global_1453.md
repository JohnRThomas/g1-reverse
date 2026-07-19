### cluster global_1453  (global, 1 members, 3 fields, size>=0xa0c)

Global object at fixed address 0x0007a3a0.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - CC_HalWaitInterruptRND @ 0x7a2c4  as 0x0007a3a0  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1453 {
    uint8_t    _pad_0x0[0x104];   /* +0x0 pad */
    uint32_t   field_0x104;   /* +0x104  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x108[0x8f8];   /* +0x108 pad */
    uint32_t   field_0xa00;   /* +0xa00  sz=4 rw=r types=uint */
    uint8_t    _pad_0xa04[0x4];   /* +0xa04 pad */
    uint32_t   field_0xa08;   /* +0xa08  sz=4 rw=w types=uint */
};
```