## review group param_0402  (1 cluster(s), kinds=param)

### proposal for param_0402
struct_name: metal_io_region | is_library: True | library_name: metal_io_region | is_array: None | confidence: medium
purpose: Libmetal/OpenAMP I/O region descriptor used by rpmsg_virtqueue_channel_init and metal_io_block_set
fields:
  0x0  void*        ops_or_vaddr  
  0x8  uint32_t     field_0x8  
  0x28  uint32_t     field_0x28  

<ground-truth bundle for param_0402>
### cluster param_0402  (param, 2 members, 3 fields, size>=0x2c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - rpmsg_virtqueue_channel_init @ 0x71358  as param_4  [APPLICATION]
  - metal_io_block_set @ 0x8557c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0402 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x1c];   /* +0xc pad */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
};
```
