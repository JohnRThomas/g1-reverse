### cluster param_0493  (param, 6 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 3/6 members are LIBRARY-class)

members (6 shown of 6):
  - chunk_field @ 0x7ddec  as param_1  [LIBRARY]
  - chunk_set @ 0x7de02  as param_1  [LIBRARY]
  - free_list_remove_bidx @ 0x7de9a  as param_1  [LIBRARY]
  - FUN_0007def6 @ 0x7def6  as param_1  [APPLICATION]
  - alloc_chunk @ 0x7df24  as param_1  [APPLICATION]
  - free_list_add @ 0x7e022  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0493 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=uint */
};
```