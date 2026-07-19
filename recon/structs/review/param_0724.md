## review group param_0724  (1 cluster(s), kinds=param)

### proposal for param_0724
struct_name: k_heap_init_ctx | is_library: True | library_name: k_heap / sys_heap | is_array: None | confidence: low
purpose: Zephyr k_heap/sys_heap descriptor initialized by g1_recon_k_heap_init (backing memory pointer and byte size).
fields:
  0xc  void *       init_mem  read as idx4, backing memory pointer
  0x10  uint32_t     init_bytes  read as idx4, heap size

<ground-truth bundle for param_0724>
### cluster param_0724  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - g1_recon_k_heap_init @ 0x863aa  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0724 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```
