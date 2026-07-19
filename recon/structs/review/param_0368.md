## review group param_0368  (1 cluster(s), kinds=param)

### proposal for param_0368
struct_name: lc3_bwdet_state | is_library: True | library_name: lc3_bwdet_state | is_array: None | confidence: medium
purpose: LC3 audio codec bandwidth-detector running state updated by lc3_bwdet_put_bw
fields:
  0x1c  uint32_t     nbits_bw  rw
  0x20  uint32_t     bw_band_idx  rw

<ground-truth bundle for param_0368>
### cluster param_0368  (param, 1 members, 2 fields, size>=0x24)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_bwdet_put_bw @ 0x68b2c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0368 {
    uint8_t    _pad_0x0[0x1c];   /* +0x0 pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=rw types=uint */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=rw types=int,uint */
};
```
