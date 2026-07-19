## review group param_0423  (1 cluster(s), kinds=param)

### proposal for param_0423
struct_name: dtoa_scratch | is_library: True | library_name: libc dtoa() internal Bigint/scratch state | is_array: None | confidence: low
purpose: Internal scratch state for dtoa (double-to-ASCII, David Gay's algorithm) third parameter: three index-typed words used during conversion.
fields:
  0x4  int32_t      field_0x4  read-only idx4
  0x8  int32_t      field_0x8  read-only idx4
  0xc  int32_t      field_0xc  read-only idx4

<ground-truth bundle for param_0423>
### cluster param_0423  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - dtoa @ 0x78110  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0423 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
