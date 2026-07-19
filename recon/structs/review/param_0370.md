## review group param_0370  (1 cluster(s), kinds=param)

### proposal for param_0370
struct_name: lc3_pcm_buf_desc | is_library: True | library_name: liblc3 (internal buffer descriptor) | is_array: None | confidence: low
purpose: LC3 codec 24-bit PCM sample-buffer descriptor consumed by lc3_load_s24_3le: sample pointer/count pair.
fields:
  0x4  void *       samples_ptr  
  0x8  uint32_t     num_samples  

<ground-truth bundle for param_0370>
### cluster param_0370  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_load_s24_3le @ 0x68d2c  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0370 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
