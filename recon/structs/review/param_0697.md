## review group param_0697  (1 cluster(s), kinds=param)

### proposal for param_0697
struct_name: metal_io_region | is_library: True | library_name: struct metal_io_region | is_array: False | confidence: low
purpose: libmetal I/O region descriptor (ops vtable, physical/size fields) passed to metal_io_block_write for shared-memory IPC access.
fields:
  0x0  void *       ops_or_vtable  code-typed field, likely function pointer into metal_io_ops
  0x8  uint32_t     size  
  0x24  uint32_t     mem_flags  

<ground-truth bundle for param_0697>
### cluster param_0697  (param, 1 members, 3 fields, size>=0x28)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - metal_io_block_write @ 0x85508  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0697 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x18];   /* +0xc pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
};
```
