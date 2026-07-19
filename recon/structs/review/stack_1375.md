## review group stack_1375  (1 cluster(s), kinds=stack)

### proposal for stack_1375
struct_name: lc3_mdct_fft_workspace | is_library: True | library_name: liblc3 internal FFT workspace (exact header unverified) | is_array: False | confidence: low
purpose: Local FFT workspace parameters (size/scale/pointer) used inside the LC3 MDCT FFT routine.
fields:
  0x0  int32_t      fft_n  
  0x4  int32_t      fft_scale  
  0xc  void *       fft_data_ptr  

<ground-truth bundle for stack_1375>
### cluster stack_1375  (stack, 1 members, 3 fields, size>=0x10)

Stack-frame local local_60 in lc3_mdct_fft (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_mdct_fft @ 0x6b3c8  as local_60  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1375 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x4];   /* +0x8 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
