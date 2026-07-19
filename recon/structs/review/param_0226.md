## review group param_0226  (1 cluster(s), kinds=param)

### proposal for param_0226
struct_name: find_type_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Search/callback context used by find_type_cb: a type/index field, two lookup indices, and a found/match flag byte
fields:
  0x4  uint32_t     field_0x4  mixed byte/idx4 read
  0x8  uint32_t     field_0x8  idx4 read
  0xc  uint32_t     field_0xc  idx4 read
  0x11  uint8_t      match_flag  write-only

<ground-truth bundle for param_0226>
### cluster param_0226  (param, 1 members, 4 fields, size>=0x15)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - find_type_cb @ 0x583d0  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0226 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=1,4 rw=r types=byte,idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x1];   /* +0x10 pad */
    uint8_t    field_0x11;   /* +0x11  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x12[0x3];   /* +0x12 pad */
};
```
