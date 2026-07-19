## review group param_0362  (1 cluster(s), kinds=param)

### proposal for param_0362
struct_name: metal_bus | is_library: True | library_name: metal_bus | is_array: None | confidence: low
purpose: libmetal bus descriptor registered via metal_bus_register_device (name pointer near the front, ops/device-list pointers near the end).
fields:
  0x4  const char * name  read as idx4 (pointer)
  0x8  void *       ops_or_next  read as idx4
  0x44  void *       dev_list_head  read as idx4
  0x48  void *       dev_list_tail_or_flags  read as idx4

<ground-truth bundle for param_0362>
### cluster param_0362  (param, 1 members, 4 fields, size>=0x4c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - metal_bus_register_device @ 0x68204  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0362 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x38];   /* +0xc pad */
    uint32_t   field_0x44;   /* +0x44  sz=4 rw=r types=idx4 */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=r types=idx4 */
};
```
