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

layout notes: overlap at 0x2 (prev field ends 0x4); overlap at 0x3 (prev field ends 0x4); overlap at 0x6 (prev field ends 0x8); overlap at 0xa (prev field ends 0xc); overlap at 0xe (prev field ends 0x10)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0261 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    void *     field_0x4;   /* +0x4  sz=1,4 rw=r types=byte,char,idx4,ptr */
    uint32_t   field_0x8;   /* +0x8  sz=2,4 rw=rw types=idx4,short,undefined2 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=1,4 rw=r types=char,idx4 */
};
```