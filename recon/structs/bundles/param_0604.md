### cluster param_0604  (param, 5 members, 7 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 5/5 members are LIBRARY-class)

members (5 shown of 5):
  - find_info_cb @ 0x81d24  as param_3  [LIBRARY]
  - gatt_read_group_encode @ 0x827ae  as param_3  [LIBRARY]
  - gatt_read_type_encode @ 0x827de  as param_3  [LIBRARY]
  - gatt_prepare_write_encode @ 0x82856  as param_3  [LIBRARY]
  - gatt_write_ccc_buf @ 0x82b6e  as param_3  [LIBRARY]

layout notes: overlap at 0x6 (prev field ends 0x8); overlap at 0xe (prev field ends 0x10)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0604 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=char */
    uint8_t    _pad_0x1[0x3];   /* +0x1 pad */
    uint32_t   field_0x4;   /* +0x4  sz=2,4 rw=r types=idx4,undefined2 */
    uint32_t   field_0x8;   /* +0x8  sz=2,4 rw=r types=idx4,undefined2,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=1,2,4 rw=r types=char,idx4,undefined2 */
};
```