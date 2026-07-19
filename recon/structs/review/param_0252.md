## review group param_0252  (1 cluster(s), kinds=param)

### proposal for param_0252
struct_name: bt_gatt_attr | is_library: True | library_name: bt_gatt_attr | is_array: False | confidence: medium
purpose: GATT attribute descriptor (uuid/read/write/user_data/handle/perm) passed to bt_gatt_check_perm and used by CCC write/restore/update paths.
fields:
  0x4  int32_t      read  function-pointer-shaped field (read callback) though typed int here
  0x8  void *       write  write callback pointer
  0xc  void *       user_data  
  0x12  uint16_t     perm  real struct has u16 handle @0x10 + u8 perm @0x12; only the perm-adjacent u16 read is observed here

<ground-truth bundle for param_0252>
### cluster param_0252  (param, 5 members, 4 fields, size>=0x16)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt,gatt; 1/5 members are LIBRARY-class)

members (5 shown of 5):
  - gatt_ccc_write @ 0x5a464  as param_2  [APPLICATION]
  - sc_restore @ 0x5b554  as param_1  [APPLICATION]
  - gatt_send_ccc_update @ 0x5b890  as param_1  [APPLICATION]
  - FUN_00081c8c @ 0x81c8c  as param_1  [APPLICATION]
  - bt_gatt_check_perm @ 0x82cba  as param_2  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0252 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    void *     field_0x8;   /* +0x8  sz=4 rw=r types=int,ptr */
    void *     field_0xc;   /* +0xc  sz=4 rw=r types=int,ptr */
    uint8_t    _pad_0x10[0x2];   /* +0x10 pad */
    uint16_t   field_0x12;   /* +0x12  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x14[0x2];   /* +0x14 pad */
};
```
