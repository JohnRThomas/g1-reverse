## review group global_1360  (1 cluster(s), kinds=global)

### proposal for global_1360
struct_name: lc3_bwdet_tables | is_library: True | library_name: lc3 (bwdet internal tables) | is_array: True | confidence: medium
purpose: LC3 codec bandwidth-detection lookup table referenced by lc3_bwdet_run (three parallel index/threshold arrays).
fields:
  0x4  uint32_t     field_0x4  table entry / threshold index
  0x8  uint32_t     field_0x8  table entry / threshold index
  0xc  uint32_t     field_0xc  table entry / threshold index

<ground-truth bundle for global_1360>
### cluster global_1360  (global, 1 members, 3 fields, size>=0x10)

Global object at fixed address 0x00068b0c.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_bwdet_run @ 0x68a10  as 0x00068b0c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1360 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
