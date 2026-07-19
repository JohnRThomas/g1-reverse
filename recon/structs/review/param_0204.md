## review group param_0204  (1 cluster(s), kinds=param)

### proposal for param_0204
struct_name: net_buf | is_library: True | library_name: net_buf | is_array: None | confidence: medium
purpose: Zephyr net_buf structure passed to net_buf_destroy: pool pointer, ref/user-data words
fields:
  0x4  void *       pool  rw pointer to net_buf_pool
  0x8  uint32_t     field_0x8  rw, possibly frags/ref
  0xc  uint32_t     field_0xc  write-only

<ground-truth bundle for param_0204>
### cluster param_0204  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: net_buf; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - net_buf_destroy @ 0x56080  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0204 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=rw types=ptr,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=undefined4 */
};
```
