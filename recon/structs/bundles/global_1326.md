### cluster global_1326  (global, 1 members, 2 fields, size>=0x12)

Global object at fixed address 0x00066254.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_pdm_start @ 0x66214  as 0x00066254  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1326 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=r types=char */
    uint8_t    field_0x11;   /* +0x11  sz=1 rw=rw types=char,undefined1 */
};
```