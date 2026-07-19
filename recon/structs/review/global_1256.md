## review group global_1256  (1 cluster(s), kinds=global)

### proposal for global_1256
struct_name: bt_keys_pool | is_library: True | library_name: bt_keys | is_array: None | confidence: low
purpose: Zephyr Bluetooth bonded-keys storage pool (struct bt_keys array) queried by bt_keys_find_irk to resolve an IRK.
fields:
  0xe  uint16_t     field_0xe  likely key state/flags field of first bt_keys entry
  0x6a  uint16_t     field_0x6a  likely field inside a later bt_keys array element (id/flags)
  0x170  uint32_t     field_0x170  index-like field, possibly storage/id counter near array end

<ground-truth bundle for global_1256>
### cluster global_1256  (global, 1 members, 3 fields, size>=0x174)

Global object at fixed address 0x0005e928.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_keys_find_irk @ 0x5e83c  as 0x0005e928  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1256 {
    uint8_t    _pad_0x0[0xe];   /* +0x0 pad */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x10[0x5a];   /* +0x10 pad */
    uint16_t   field_0x6a;   /* +0x6a  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x6c[0x104];   /* +0x6c pad */
    uint32_t   field_0x170;   /* +0x170  sz=4 rw=r types=idx4 */
};
```
