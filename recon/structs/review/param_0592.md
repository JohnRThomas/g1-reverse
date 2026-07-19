## review group param_0592  (1 cluster(s), kinds=param)

### proposal for param_0592
struct_name: context_release_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Context object released and notified via context_release_and_notify, spanning a work item/callback plus flags and a semaphore/event value near the end
fields:
  0x0  void*        callback_fn  
  0x4  uint32_t     field_0x4  
  0xc  uint32_t     field_0xc  
  0x2d  uint8_t      field_0x2d  
  0xb6  uint16_t     field_0xb6  

<ground-truth bundle for param_0592>
### cluster param_0592  (param, 1 members, 5 fields, size>=0xba)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - context_release_and_notify @ 0x817b6  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0592 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x4];   /* +0x8 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x1d];   /* +0x10 pad */
    uint8_t    field_0x2d;   /* +0x2d  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x2e[0x88];   /* +0x2e pad */
    uint16_t   field_0xb6;   /* +0xb6  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0xb8[0x2];   /* +0xb8 pad */
};
```
