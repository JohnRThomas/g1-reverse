## review group global_1152  (2 cluster(s), kinds=global,param)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for global_1152
struct_name: fw_version_info_table | is_library: True | library_name:  | is_array: True | confidence: low
purpose: Fixed global table of 12 uint32 values consumed by ver_str formatting code; likely a version/build-info record (component versions or numeric fields concatenated into a version string).
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x18  uint32_t     field_0x18  
  0x1c  uint32_t     field_0x1c  
  0x20  uint32_t     field_0x20  
  0x24  uint32_t     field_0x24  
  0x28  uint32_t     field_0x28  
  0x2c  uint32_t     field_0x2c  
  0x30  uint32_t     field_0x30  
  0x34  uint32_t     field_0x34  

<ground-truth bundle for global_1152>
### cluster global_1152  (global, 1 members, 13 fields, size>=0x38)

Global object at fixed address 0x00053378.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - ver_str @ 0x53344  as 0x00053378  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1152 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0692
struct_name: metal_io_region | is_library: True | library_name: metal_io_region | is_array: False | confidence: medium
purpose: libmetal I/O region descriptor initialized by metal_io_init: physical/virtual base, size, page shift/mask and ops table.
fields:
  0x4  uint32_t     virt  virtual base
  0x8  uint32_t     physmap  physical map
  0xc  uint32_t     size  
  0x10  uint32_t     page_shift  
  0x14  uint32_t     page_mask  
  0x18  uint32_t     mem_flags  
  0x1c  uint32_t     ops_0  
  0x20  uint32_t     ops_1  
  0x24  uint32_t     ops_2  
  0x28  uint32_t     ops_3  
  0x2c  uint32_t     device  
  0x30  uint32_t     field_0x30  
  0x34  uint32_t     field_0x34  

<ground-truth bundle for param_0692>
### cluster param_0692  (param, 1 members, 13 fields, size>=0x38)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - metal_io_init @ 0x85442  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0692 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
};
```
