### cluster param_0135  (param, 16 members, 10 fields, size>=0x30)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 2/16 members are LIBRARY-class)

members (16 shown of 16):
  - FUN_0004c4e4 @ 0x4c4e4  as param_1  [APPLICATION]
  - nvs_mount @ 0x4c548  as param_1  [APPLICATION]
  - nvs_write @ 0x4c8f8  as param_1  [APPLICATION]
  - nvs_read_hist @ 0x4cab4  as param_1  [APPLICATION]
  - FUN_0007e53e @ 0x7e53e  as param_1  [APPLICATION]
  - nvs_sector_advance @ 0x7e55a  as param_1  [LIBRARY]
  - FUN_0007e574 @ 0x7e574  as param_1  [APPLICATION]
  - FUN_0007e5da @ 0x7e5da  as param_1  [APPLICATION]
  - FUN_0007e624 @ 0x7e624  as param_1  [APPLICATION]
  - FUN_0007e672 @ 0x7e672  as param_1  [APPLICATION]
  - FUN_0007e6a6 @ 0x7e6a6  as param_1  [APPLICATION]
  - FUN_0007e6e2 @ 0x7e6e2  as param_1  [APPLICATION]
  - FUN_0007e776 @ 0x7e776  as param_1  [APPLICATION]
  - FUN_0007e7ea @ 0x7e7ea  as param_1  [APPLICATION]
  - nvs_add_gc_done_ate @ 0x7e80c  as param_1  [LIBRARY]
  - FUN_0007e83a @ 0x7e83a  as param_1  [APPLICATION]

layout notes: 0x0: access width 4 exceeds gap 1 to next field (overlap/union); 0x3: access width 2 exceeds gap 1 to next field (overlap/union); 0xc: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0135 {
    uint8_t    field_0x0;   /* +0x0  sz=4 rw=r types=int */
    uint16_t   field_0x1;   /* +0x1  sz=2 rw=r types=ushort */
    uint8_t    field_0x3;   /* +0x3  sz=2 rw=r types=undefined2,ushort */
    uint32_t   field_0x4;   /* +0x4  sz=1,4 rw=rw types=idx4,int,uint,undefined1,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=idx4,int,uint,undefined4 */
    uint16_t   field_0xc;   /* +0xc  sz=2,4 rw=r types=idx4,ushort */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=r types=ushort */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=r types=char */
    uint8_t    _pad_0x11[0x17];   /* +0x11 pad */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    void *     field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4,int,ptr,undefined4 */
};
```