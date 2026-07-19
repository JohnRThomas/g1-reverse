## review group param_0185  (1 cluster(s), kinds=param)

### proposal for param_0185
struct_name: bt_uuid_32 | is_library: True | library_name: Zephyr Bluetooth: struct bt_uuid / bt_uuid_32 | is_array: None | confidence: low
purpose: Zephyr Bluetooth UUID object used by bt_uuid_expand_to_128 and bt_uuid_cmp; a type/format field followed by a 32-bit UUID value.
fields:
  0x2  uint16_t     field_0x2  read-only short, possibly overlapping uuid16 value
  0x4  uint32_t     val  read-only uint, 32-bit UUID value

<ground-truth bundle for param_0185>
### cluster param_0185  (param, 3 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 2/3 members are LIBRARY-class)

members (3 shown of 3):
  - bt_uuid_expand_to_128 @ 0x531e4  as param_1  [APPLICATION]
  - bt_uuid_cmp @ 0x80d3e  as param_1  [LIBRARY]
  - bt_uuid_cmp @ 0x80d3e  as param_2  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0185 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=undefined2,ushort */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=uint,undefined4 */
};
```
