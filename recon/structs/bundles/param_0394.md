### cluster param_0394  (param, 2 members, 4 fields, size>=0x30)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 2/2 members are LIBRARY-class)

members (2 shown of 2):
  - virtio_create_virtqueues @ 0x70e28  as param_1  [LIBRARY]
  - virtqueue_create @ 0x85622  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0394 {
    uint8_t    _pad_0x0[0x18];   /* +0x0 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=int */
    uint8_t    _pad_0x1c[0x4];   /* +0x1c pad */
    void *     field_0x20;   /* +0x20  sz=4 rw=r types=int,ptr */
    uint8_t    _pad_0x24[0x4];   /* +0x24 pad */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=uint */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=int */
};
```