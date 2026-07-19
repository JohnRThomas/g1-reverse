### cluster global_0809  (global, 1 members, 3 fields, size>=0x14)

Global object at fixed address 0x000179cc.

library hint: likely G1-original

members (1 shown of 1):
  - gpio_pin_get_checked @ 0x17980  as 0x000179cc  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0809 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
    uint8_t    _pad_0xc[0x4];   /* +0xc pad */
    void *     field_0x10;   /* +0x10  sz=4 rw=r types=ptr */
};
```