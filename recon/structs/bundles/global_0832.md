### cluster global_0832  (global, 1 members, 2 fields, size>=0x28)

Global object at fixed address 0x00018c30.

library hint: likely G1-original

members (1 shown of 1):
  - enqueue_ancs @ 0x18bb4  as 0x00018c30  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0832 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
    uint8_t    _pad_0x14[0x10];   /* +0x14 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=int */
};
```