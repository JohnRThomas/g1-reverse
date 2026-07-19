## review group param_0699  (1 cluster(s), kinds=param)

### proposal for param_0699
struct_name: virtqueue | is_library: True | library_name: struct virtqueue | is_array: False | confidence: medium
purpose: OpenAMP/virtio virtqueue object built by virtqueue_create: id/flags fields plus a run of ring/descriptor table configuration words.
fields:
  0x2  uint16_t     vq_queue_index  
  0x4  uint32_t     vq_dev_ptr  
  0x9  uint16_t     vq_nentries  
  0xc  uint32_t     vq_ring_desc  
  0x10  uint32_t     vq_ring_avail  
  0x14  uint32_t     vq_ring_used  
  0x18  uint32_t     vq_free_head  
  0x1c  uint32_t     vq_num_free  
  0x20  uint32_t     vq_callback  

<ground-truth bundle for param_0699>
### cluster param_0699  (param, 1 members, 10 fields, size>=0x24)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - virtqueue_create @ 0x85622  as param_7  [LIBRARY]

layout notes: 0x9: access width 2 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0699 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=w types=undefined2 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x1];   /* +0x8 pad */
    uint8_t    field_0x9;   /* +0x9  sz=2 rw=w types=ushort */
    uint16_t   field_0xa;   /* +0xa  sz=2 rw=w types=ushort */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
};
```
