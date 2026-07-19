## review group param_0427  (1 cluster(s), kinds=param)

### proposal for param_0427
struct_name: bignum_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: G1-original arbitrary-precision integer state used by bigint_diff/bignum_div_trial_subtract/bignum_compare_abs (sign and length/scratch fields).
fields:
  0x4  int32_t      sign_or_len  
  0x10  int32_t      scratch  

<ground-truth bundle for param_0427>
### cluster param_0427  (param, 3 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (3 shown of 3):
  - bigint_diff @ 0x78ac8  as param_2  [APPLICATION]
  - bignum_div_trial_subtract @ 0x87184  as param_1  [APPLICATION]
  - bignum_compare_abs @ 0x875ae  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0427 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=int */
};
```
