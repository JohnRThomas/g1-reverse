### cluster global_1077  (global, 1 members, 3 fields, size>=0x138)

Global object at fixed address 0x0004ecf8.

library hint: likely G1-original

members (1 shown of 1):
  - discovery_callback @ 0x4ea78  as 0x0004ecf8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1077 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint16_t   field_0x4;   /* +0x4  sz=2 rw=w types=short */
    uint8_t    _pad_0x6[0x1a];   /* +0x6 pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x24[0x110];   /* +0x24 pad */
    uint32_t   field_0x134;   /* +0x134  sz=4 rw=r types=idx4 */
};
```