## review group param_0391  (1 cluster(s), kinds=param)

### proposal for param_0391
struct_name: lc3_tns_state | is_library: True | library_name: lc3 internal TNS data | is_array: None | confidence: low
purpose: LC3 audio codec Temporal Noise Shaping (TNS) analysis parameter block passed into lc3_tns_analyze.
fields:
  0x1  uint8_t      num_filters  write-only
  0x4  uint32_t     rc_order_or_bits  read as idx4

<ground-truth bundle for param_0391>
### cluster param_0391  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_tns_analyze @ 0x6ffd8  as param_5  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0391 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x2[0x2];   /* +0x2 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
