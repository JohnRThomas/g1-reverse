## review group param_0625  (1 cluster(s), kinds=param)

### proposal for param_0625
struct_name: bt_addr_le_t | is_library: True | library_name: bt_addr_le_t | is_array: None | confidence: medium
purpose: Bluetooth LE address structure (type byte + 6-byte address) written by bt_addr_le_copy_828da
fields:
  0x1  uint16_t     val_lo  write-only, low 2 bytes of 6-byte address
  0x6  uint8_t      val_hi  write-only, part of address tail

<ground-truth bundle for param_0625>
### cluster param_0625  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_addr_le_copy_828da @ 0x828da  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0625 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint16_t   field_0x1;   /* +0x1  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x3[0x3];   /* +0x3 pad */
    uint8_t    field_0x6;   /* +0x6  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x7[0x1];   /* +0x7 pad */
};
```
