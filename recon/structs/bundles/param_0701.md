### cluster param_0701  (param, 1 members, 7 fields, size>=0x30)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - virtqueue_add_buffer @ 0x8567c  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0701 {
    uint8_t    _pad_0x0[0xa];   /* +0x0 pad */
    uint16_t   field_0xa;   /* +0xa  sz=2 rw=r types=ushort */
    uint8_t    _pad_0xc[0xc];   /* +0xc pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=int */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=int */
    uint8_t    _pad_0x20[0x4];   /* +0x20 pad */
    uint16_t   field_0x24;   /* +0x24  sz=2 rw=rw types=short */
    uint16_t   field_0x26;   /* +0x26  sz=2 rw=rw types=short */
    void *     field_0x28;   /* +0x28  sz=4 rw=r types=ptr */
    uint16_t   field_0x2c;   /* +0x2c  sz=2 rw=rw types=short,ushort */
    uint8_t    _pad_0x2e[0x2];   /* +0x2e pad */
};
```