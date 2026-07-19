## review group param_0424  (1 cluster(s), kinds=param)

### proposal for param_0424
struct_name: bigint | is_library: True | library_name: struct Bigint (netlib dtoa) | is_array: False | confidence: high
purpose: David Gay's dtoa.c arbitrary-precision integer (Bigint) manipulated by Bfree/multadd/lshift: next pointer, exponent/word-count k, max words, and current word count wds.
fields:
  0x4  int          k  
  0x8  int          maxwds  
  0x10  int          wds  

<ground-truth bundle for param_0424>
### cluster param_0424  (param, 3 members, 3 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (3 shown of 3):
  - Bfree @ 0x78654  as param_2  [APPLICATION]
  - multadd @ 0x78698  as param_2  [APPLICATION]
  - lshift @ 0x789f0  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0424 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
    uint8_t    _pad_0xc[0x4];   /* +0xc pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```
