## review group param_0432  (1 cluster(s), kinds=param)

### proposal for param_0432
struct_name: vfprintf_scan_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Format-field scanning context used by vfprintf_field_scan_match: callback function pointer plus a run of index fields and a trailing flag near the end of a large buffer
fields:
  0x0  void (*)(void) out_fn  code/function pointer
  0x8  uint32_t     field_0x8  idx4
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x18  uint32_t     field_0x18  
  0x180  uint32_t     field_0x180  idx4, likely tail flag/count

<ground-truth bundle for param_0432>
### cluster param_0432  (param, 1 members, 7 fields, size>=0x184)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - vfprintf_field_scan_match @ 0x79278  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0432 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x1c[0x164];   /* +0x1c pad */
    uint32_t   field_0x180;   /* +0x180  sz=4 rw=r types=idx4 */
};
```
