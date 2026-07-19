## review group param_0607  (1 cluster(s), kinds=param)

### proposal for param_0607
struct_name: generic_cmd_ctx_0607 | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Unidentified small G1-original context struct used inside FUN_00081fbe
fields:
  0x3  uint8_t      field_0x3  write-only
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for param_0607>
### cluster param_0607  (param, 1 members, 3 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - FUN_00081fbe @ 0x81fbe  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0607 {
    uint8_t    _pad_0x0[0x3];   /* +0x0 pad */
    uint8_t    field_0x3;   /* +0x3  sz=1 rw=w types=char,undefined1 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
