## review group param_0568  (1 cluster(s), kinds=param)

### proposal for param_0568
struct_name: bt_uuid_generic | is_library: True | library_name: bt_uuid_16 / bt_uuid_32 | is_array: None | confidence: high
purpose: Bluetooth UUID object (16-bit or 32-bit variant) initialized by bt_uuid_create
fields:
  0x2  uint16_t     val16  matches bt_uuid_16.val offset
  0x4  uint32_t     val32  matches bt_uuid_32.val offset (overlapping variant)

<ground-truth bundle for param_0568>
### cluster param_0568  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_uuid_create @ 0x80d9a  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0568 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=w types=undefined2 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=w types=undefined4 */
};
```
