## review group global_1253  (1 cluster(s), kinds=global)

### proposal for global_1253
struct_name: bt_bond_iter_ctx | is_library: True | library_name: bt_keys | is_array: None | confidence: low
purpose: Global scratch object touched by bt_foreach_bond during bonded-device iteration (likely a partial view into a bt_keys/bt_addr_le style record).
fields:
  0x1  uint32_t     field_0x1  unaligned 4-byte read, likely part of a key/id
  0xe  uint16_t     field_0xe  unaligned 2-byte read

<ground-truth bundle for global_1253>
### cluster global_1253  (global, 1 members, 2 fields, size>=0x12)

Global object at fixed address 0x0005e750.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_foreach_bond @ 0x5e6d4  as 0x0005e750  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1253 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint32_t   field_0x1;   /* +0x1  sz=4 rw=r types=uint */
    uint8_t    _pad_0x5[0x9];   /* +0x5 pad */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=r types=short */
    uint8_t    _pad_0x10[0x2];   /* +0x10 pad */
};
```
