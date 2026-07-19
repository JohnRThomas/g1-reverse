## review group param_0712  (1 cluster(s), kinds=param)

### proposal for param_0712
struct_name: virtqueue | is_library: True | library_name: virtqueue | is_array: None | confidence: medium
purpose: OpenAMP/virtio virtqueue object whose tail fields (free count, used index) are read by virtqueue_return_rx_buffer when recycling an RX buffer.
fields:
  0xa0  uint32_t     vq_free_cnt  read-only int
  0xa4  uint32_t     vq_last_used_idx  read-only word

<ground-truth bundle for param_0712>
### cluster param_0712  (param, 1 members, 2 fields, size>=0xa8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - virtqueue_return_rx_buffer @ 0x85a9c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0712 {
    uint8_t    _pad_0x0[0xa0];   /* +0x0 pad */
    uint32_t   field_0xa0;   /* +0xa0  sz=4 rw=r types=int */
    uint32_t   field_0xa4;   /* +0xa4  sz=4 rw=r types=undefined4 */
};
```
