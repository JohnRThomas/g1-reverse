### cluster global_1166  (global, 1 members, 2 fields, size>=0x122)

Global object at fixed address 0x00055090.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_id_add @ 0x5505c  as 0x00055090  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1166 {
    uint8_t    _pad_0x0[0x120];   /* +0x0 pad */
    uint8_t    field_0x120;   /* +0x120  sz=1 rw=r types=byte */
    uint8_t    field_0x121;   /* +0x121  sz=1 rw=rw types=byte */
};
```