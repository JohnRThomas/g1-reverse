### cluster global_1452  (global, 1 members, 2 fields, size>=0xa0c)

Global object at fixed address 0x0007a3c8.

library hint: likely G1-original

members (1 shown of 1):
  - cc_crypto_dispatch_or_error @ 0x7a2b8  as 0x0007a3c8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1452 {
    uint8_t    _pad_0x0[0xa00];   /* +0x0 pad */
    uint32_t   field_0xa00;   /* +0xa00  sz=4 rw=r types=uint */
    uint8_t    _pad_0xa04[0x4];   /* +0xa04 pad */
    uint32_t   field_0xa08;   /* +0xa08  sz=4 rw=w types=uint */
};
```