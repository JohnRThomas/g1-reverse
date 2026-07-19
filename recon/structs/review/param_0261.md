## review group param_0261  (1 cluster(s), kinds=param)

### proposal for param_0261
struct_name: gatt_att_buf | is_library: True | library_name: net_buf / net_buf_simple (best guess) | is_array: None | confidence: low
purpose: Shared object across bt_gatt_discover/write, GATT response parsers, and l2cap_reassemble_frag; consistent with a Bluetooth net_buf-style PDU buffer (function/vtable ptr, data pointer, length, capacity, flags byte).
fields:
  0x0  void *       field_0x0  typed code
  0x4  void *       data  
  0x8  uint32_t     len  
  0xc  uint32_t     size  
  0x10  uint8_t      flags  

<ground-truth bundle for param_0261>
### cluster param_0261  (param, 9 members, 10 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt,gatt,l2cap; 1/9 members are LIBRARY-class)

members (9 shown of 9):
  - bt_gatt_discover @ 0x5b9cc  as param_2  [APPLICATION]
  - gatt_parse_find_by_type_rsp @ 0x5bbf4  as param_5  [APPLICATION]
  - gatt_parse_read_by_type_rsp @ 0x5bd18  as param_5  [APPLICATION]
  - gatt_parse_read_by_type_rsp_128 @ 0x5c004  as param_5  [APPLICATION]
  - gatt_parse_find_info_rsp @ 0x5c0bc  as param_5  [APPLICATION]
  - bt_gatt_write @ 0x5c22c  as param_2  [APPLICATION]
  - gatt_discover_next @ 0x82d2e  as param_3  [LIBRARY]
  - FUN_00082d6a @ 0x82d6a  as param_5  [APPLICATION]
  - l2cap_reassemble_frag @ 0x82e04  as param_5  [APPLICATION]

layout notes: 0x0: access width 4 exceeds gap 2 to next field (overlap/union); 0x2: access width 2 exceeds gap 1 to next field (overlap/union); 0x3: access width 2 exceeds gap 1 to next field (overlap/union); 0x4: access width 4 exceeds gap 2 to next field (overlap/union); 0x8: access width 4 exceeds gap 2 to next field (overlap/union); 0xc: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0261 {
    uint16_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint8_t    field_0x2;   /* +0x2  sz=2 rw=rw types=short,ushort */
    uint8_t    field_0x3;   /* +0x3  sz=2 rw=rw types=short,undefined2,ushort */
    uint16_t   field_0x4;   /* +0x4  sz=1,4 rw=r types=byte,char,idx4,ptr */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=rw types=short */
    uint16_t   field_0x8;   /* +0x8  sz=2,4 rw=rw types=idx4,short,undefined2 */
    uint16_t   field_0xa;   /* +0xa  sz=2 rw=rw types=undefined2 */
    uint16_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=r types=ushort */
    uint32_t   field_0x10;   /* +0x10  sz=1,4 rw=r types=char,idx4 */
};
```
