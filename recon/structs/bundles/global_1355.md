### cluster global_1355  (global, 1 members, 2 fields, size>=0x2c)

Global object at fixed address 0x000682b0.

library hint: likely G1-original

members (1 shown of 1):
  - metal_generic_bus_unregister @ 0x682a8  as 0x000682b0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1355 {
    uint8_t    _pad_0x0[0x24];   /* +0x0 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
};
```