### cluster param_0395  (param, 1 members, 3 fields, size>=0x28)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - virtqueue_free @ 0x70ee4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0395 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x8[0x2];   /* +0x8 pad */
    uint16_t   field_0xa;   /* +0xa  sz=2 rw=r types=short */
    uint8_t    _pad_0xc[0x18];   /* +0xc pad */
    uint16_t   field_0x24;   /* +0x24  sz=2 rw=r types=short */
    uint8_t    _pad_0x26[0x2];   /* +0x26 pad */
};
```