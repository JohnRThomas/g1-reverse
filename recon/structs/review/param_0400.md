## review group param_0400  (1 cluster(s), kinds=param)

### proposal for param_0400
struct_name: rpmsg_vq_alloc_info | is_library: True | library_name: open-amp rpmsg/virtqueue alloc_info (best guess) | is_array: None | confidence: low
purpose: Virtqueue allocation descriptor passed into rpmsg_virtqueue_channel_init: a flag/id byte and a pointer + size pair for the vring allocation.
fields:
  0x2  uint8_t      flags_or_id  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for param_0400>
### cluster param_0400  (param, 1 members, 3 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - rpmsg_virtqueue_channel_init @ 0x71358  as param_6  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0400 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=char */
    uint8_t    _pad_0x3[0x1];   /* +0x3 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
