### cluster stack_1070  (stack, 1 members, 3 fields, size>=0x10)

Stack-frame local local_30 in flash_area_get_sectors (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - flash_area_get_sectors @ 0x4e098  as local_30  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1070 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=int */
};
```