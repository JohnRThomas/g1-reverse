## review group param_0614  (1 cluster(s), kinds=param)

### proposal for param_0614
struct_name: generic_kv_entry | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Small key/value-style entry (length, data pointer, value) accessed inside FUN_000822bc.
fields:
  0x4  uint16_t     len  
  0x8  void *       data_ptr  
  0xc  uint32_t     value  

<ground-truth bundle for param_0614>
### cluster param_0614  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - FUN_000822bc @ 0x822bc  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0614 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint16_t   field_0x4;   /* +0x4  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x6[0x2];   /* +0x6 pad */
    void *     field_0x8;   /* +0x8  sz=4 rw=r types=ptr */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
};
```
