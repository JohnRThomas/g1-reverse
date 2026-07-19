## review group param_0599  (1 cluster(s), kinds=param)

### proposal for param_0599
struct_name: bt_att_read_type_data | is_library: True | library_name: bt_att (internal read-type ctx) | is_array: None | confidence: low
purpose: Bluetooth ATT read-by-type response accumulation context used inside attr_read_type_cb (attribute list pointer plus running byte count).
fields:
  0xc  void *       attr_ptr  rw pointer, likely struct bt_gatt_attr* or list cursor
  0x10  uint32_t     count_or_len  write-only word

<ground-truth bundle for param_0599>
### cluster param_0599  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - attr_read_type_cb @ 0x81bd0  as param_3  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0599 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    void *     field_0xc;   /* +0xc  sz=4 rw=rw types=ptr */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=undefined4 */
};
```
