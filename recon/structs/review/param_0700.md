## review group param_0700  (1 cluster(s), kinds=param)

### proposal for param_0700
struct_name: virtqueue_desc_info | is_library: True | library_name:  | is_array: None | confidence: low
purpose: Small descriptor consumed by virtqueue_create (OpenAMP/virtio-style virtqueue setup)
fields:
  0x2  uint16_t     num_desc_or_id  r
  0x4  uint32_t     flags_or_addr  r, idx4

<ground-truth bundle for param_0700>
### cluster param_0700  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - virtqueue_create @ 0x85622  as param_4  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0700 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=ushort */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
