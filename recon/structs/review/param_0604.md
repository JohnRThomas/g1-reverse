## review group param_0604  (1 cluster(s), kinds=param)

### proposal for param_0604
struct_name: net_buf_simple_view | is_library: True | library_name: net_buf_simple | is_array: False | confidence: low
purpose: Zephyr Bluetooth net_buf_simple-style buffer cursor shared by ATT/GATT encode helpers (find_info_cb, gatt_read_group_encode, gatt_read_type_encode, gatt_prepare_write_encode, gatt_write_ccc_buf); overlapping offsets indicate mixed 16/32-bit accesses typical of a data/len/size buffer descriptor
fields:
  0x0  uint8_t      type_or_flag  
  0x4  uint32_t     data_or_len  
  0x8  uint32_t     size_or_off  
  0xc  uint32_t     attr_handle_or_uuid  
  0x10  uint32_t     tail_field  

<ground-truth bundle for param_0604>
### cluster param_0604  (param, 5 members, 7 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 5/5 members are LIBRARY-class)

members (5 shown of 5):
  - find_info_cb @ 0x81d24  as param_3  [LIBRARY]
  - gatt_read_group_encode @ 0x827ae  as param_3  [LIBRARY]
  - gatt_read_type_encode @ 0x827de  as param_3  [LIBRARY]
  - gatt_prepare_write_encode @ 0x82856  as param_3  [LIBRARY]
  - gatt_write_ccc_buf @ 0x82b6e  as param_3  [LIBRARY]

layout notes: 0x4: access width 4 exceeds gap 2 to next field (overlap/union); 0xc: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0604 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=char */
    uint8_t    _pad_0x1[0x3];   /* +0x1 pad */
    uint16_t   field_0x4;   /* +0x4  sz=2,4 rw=r types=idx4,undefined2 */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=r types=undefined2 */
    uint32_t   field_0x8;   /* +0x8  sz=2,4 rw=r types=idx4,undefined2,undefined4 */
    uint16_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=r types=undefined2 */
    uint32_t   field_0x10;   /* +0x10  sz=1,2,4 rw=r types=char,idx4,undefined2 */
};
```
