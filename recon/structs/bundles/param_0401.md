### cluster param_0401  (param, 2 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/2 members are LIBRARY-class)

members (2 shown of 2):
  - rpmsg_virtqueue_channel_init @ 0x71358  as param_5  [APPLICATION]
  - rpmsg_virtio_shm_pool_get_buffer @ 0x85aee  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0401 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4,int */
};
```