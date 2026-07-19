## review group param_0714  (1 cluster(s), kinds=param)

### proposal for param_0714
struct_name: rpmsg_virtio_device_ctx | is_library: True | library_name: struct rpmsg_virtio_device (OpenAMP, partial) | is_array: None | confidence: low
purpose: OpenAMP rpmsg virtio device object torn down by rpmsg_deinit_vdev, with two adjacent uint32 fields deep in the structure (likely vring or vdev status handles).
fields:
  0xa4  uint32_t     field_0xa4  
  0xa8  uint32_t     field_0xa8  

<ground-truth bundle for param_0714>
### cluster param_0714  (param, 1 members, 2 fields, size>=0xac)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - rpmsg_deinit_vdev @ 0x85bf6  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0714 {
    uint8_t    _pad_0x0[0xa4];   /* +0x0 pad */
    uint32_t   field_0xa4;   /* +0xa4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xa8;   /* +0xa8  sz=4 rw=r types=idx4 */
};
```
