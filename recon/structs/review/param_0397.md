## review group param_0397  (1 cluster(s), kinds=param)

### proposal for param_0397
struct_name: rpmsg_virtio_device | is_library: True | library_name: struct rpmsg_virtio_device | is_array: False | confidence: medium
purpose: OpenAMP rpmsg-over-virtio device object accessed by rpmsg_virtio_tx_enqueue/send_copy/get_tx_buffer_wait: tx virtqueue fields and buffer pointers.
fields:
  0x94  int          tx_vq_field  
  0xa0  int          config_field  
  0xa8  int          buf_size_or_count  
  0xac  void *       buf_ptr  
  0xb0  uint32_t     buf_len  
  0xb4  void *       notify_or_shbuf_ptr  

<ground-truth bundle for param_0397>
### cluster param_0397  (param, 3 members, 6 fields, size>=0xb8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (3 shown of 3):
  - rpmsg_virtio_tx_enqueue @ 0x710b4  as param_1  [APPLICATION]
  - rpmsg_virtio_send_copy @ 0x71294  as param_1  [APPLICATION]
  - rpmsg_virtio_get_tx_buffer_wait @ 0x85b0c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0397 {
    uint8_t    _pad_0x0[0x94];   /* +0x0 pad */
    uint32_t   field_0x94;   /* +0x94  sz=4 rw=r types=int,undefined4 */
    uint8_t    _pad_0x98[0x8];   /* +0x98 pad */
    uint32_t   field_0xa0;   /* +0xa0  sz=4 rw=r types=int */
    uint8_t    _pad_0xa4[0x4];   /* +0xa4 pad */
    uint32_t   field_0xa8;   /* +0xa8  sz=4 rw=r types=int,undefined4 */
    void *     field_0xac;   /* +0xac  sz=4 rw=r types=ptr */
    uint32_t   field_0xb0;   /* +0xb0  sz=4 rw=r types=undefined4 */
    void *     field_0xb4;   /* +0xb4  sz=4 rw=r types=ptr */
};
```
