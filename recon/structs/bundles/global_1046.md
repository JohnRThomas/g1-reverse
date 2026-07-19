### cluster global_1046  (global, 1 members, 2 fields, size>=0x20)

Global object at fixed address 0x00040190.

library hint: likely G1-original

members (1 shown of 1):
  - ui_refalsh_warp @ 0x48b5c  as 0x00040190  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1046 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x10];   /* +0xc pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
};
```