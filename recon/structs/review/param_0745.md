## review group param_0745  (1 cluster(s), kinds=param)

### proposal for param_0745
struct_name: mbedtls_mpi_limb_view | is_library: True | library_name: mbedtls_mpi (limb buffer, partial) | is_array: True | confidence: low
purpose: mbedTLS bignum (mpi) limb data accessed by bignum_shift_right_bits during a right-shift operation.
fields:
  0x10  uint32_t     limb_n  
  0x14  uint32_t     limb_n_plus_1  

<ground-truth bundle for param_0745>
### cluster param_0745  (param, 1 members, 2 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - bignum_shift_right_bits @ 0x8729e  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0745 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=w types=undefined4 */
};
```
