## review group param_0399  (1 cluster(s), kinds=param)

### proposal for param_0399
struct_name: rpmsg_vring_channel_cfg | is_library: True | library_name: OpenAMP rpmsg vring config (exact type unresolved) | is_array: None | confidence: low
purpose: rpmsg/OpenAMP virtqueue channel configuration passed to rpmsg_virtqueue_channel_init: numbers of descriptors/align and a callback or vring pointer.
fields:
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x24  int          field_0x24  
  0x2c  void *       field_0x2c  

<ground-truth bundle for param_0399>
### cluster param_0399  (param, 1 members, 4 fields, size>=0x30)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - rpmsg_virtqueue_channel_init @ 0x71358  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0399 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x18[0xc];   /* +0x18 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=w types=int */
    uint8_t    _pad_0x28[0x4];   /* +0x28 pad */
    void *     field_0x2c;   /* +0x2c  sz=4 rw=r types=int,ptr */
};
```
