## review group param_0119  (1 cluster(s), kinds=param)

### proposal for param_0119
struct_name: quicknote_buffer_pool | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Quicknote subsystem buffer pool descriptor initialized by quicknote_buffer_pool_init, holding pool metadata and a large buffer region
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x18  uint32_t     field_0x18  
  0x1c  uint32_t     field_0x1c  
  0x20  uint32_t     field_0x20  
  0x344  uint32_t     field_0x344  
  0x350  uint32_t     field_0x350  

<ground-truth bundle for param_0119>
### cluster param_0119  (param, 1 members, 10 fields, size>=0x354)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - quicknote_buffer_pool_init @ 0x47148  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0119 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x24[0x320];   /* +0x24 pad */
    uint32_t   field_0x344;   /* +0x344  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x348[0x8];   /* +0x348 pad */
    uint32_t   field_0x350;   /* +0x350  sz=4 rw=r types=idx4 */
};
```
