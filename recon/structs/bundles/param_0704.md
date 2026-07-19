### cluster param_0704  (param, 1 members, 5 fields, size>=0x32)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - virtqueue_ring_setup_flags @ 0x857b2  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0704 {
    uint16_t   field_0x0;   /* +0x0  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x2[0x8];   /* +0x2 pad */
    uint16_t   field_0xa;   /* +0xa  sz=2 rw=r types=short */
    uint8_t    _pad_0xc[0x8];   /* +0xc pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x4];   /* +0x18 pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x20[0xe];   /* +0x20 pad */
    uint16_t   field_0x2e;   /* +0x2e  sz=2 rw=r types=short */
    uint8_t    _pad_0x30[0x2];   /* +0x30 pad */
};
```