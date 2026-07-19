## review group param_0695  (1 cluster(s), kinds=param)

### proposal for param_0695
struct_name: metal_io_region_view | is_library: True | library_name: struct metal_io_region (libmetal/OpenAMP) | is_array: False | confidence: low
purpose: libmetal I/O region descriptor used by metal_io_block_read to perform a bounded remote-memory block read.
fields:
  0x0  void*        virt  virtual base pointer, mistyped as code due to indirect call usage
  0x8  size_t       size  region size
  0x20  void*        ops_fn  function pointer inside metal_io_ops (e.g. block_read op)

<ground-truth bundle for param_0695>
### cluster param_0695  (param, 1 members, 3 fields, size>=0x24)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - metal_io_block_read @ 0x85496  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0695 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x14];   /* +0xc pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
};
```
