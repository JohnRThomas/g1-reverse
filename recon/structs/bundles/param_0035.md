### cluster param_0035  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_ancs_data_source_handler @ 0x18c48  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0035 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
};
```