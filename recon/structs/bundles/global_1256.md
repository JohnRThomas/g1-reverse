### cluster global_1256  (global, 1 members, 3 fields, size>=0x174)

Global object at fixed address 0x0005e928.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_keys_find_irk @ 0x5e83c  as 0x0005e928  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1256 {
    uint8_t    _pad_0x0[0xe];   /* +0x0 pad */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x10[0x5a];   /* +0x10 pad */
    uint16_t   field_0x6a;   /* +0x6a  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x6c[0x104];   /* +0x6c pad */
    uint32_t   field_0x170;   /* +0x170  sz=4 rw=r types=idx4 */
};
```