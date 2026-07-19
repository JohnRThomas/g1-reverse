## review group param_0365  (1 cluster(s), kinds=param)

### proposal for param_0365
struct_name: lc3_bit_budget_ctx | is_library: True | library_name: liblc3 internal bit-budget/side_data structure (exact header unverified) | is_array: False | confidence: low
purpose: LC3 audio codec bit-allocation context used by lc3_setup_bits when computing per-frame bit budget.
fields:
  0x4  int32_t      nbits_budget  
  0x8  int32_t      nbits_used  

<ground-truth bundle for param_0365>
### cluster param_0365  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_setup_bits @ 0x684a8  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0365 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
