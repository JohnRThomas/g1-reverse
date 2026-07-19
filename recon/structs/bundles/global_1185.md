### cluster global_1185  (global, 1 members, 2 fields, size>=0x114)

Global object at fixed address 0x0005664c.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_conn_prepare_tx_events @ 0x565c4  as 0x0005664c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1185 {
    uint8_t    _pad_0x0[0x104];   /* +0x0 pad */
    uint16_t   field_0x104;   /* +0x104  sz=2 rw=r types=short */
    uint8_t    _pad_0x106[0xa];   /* +0x106 pad */
    uint32_t   field_0x110;   /* +0x110  sz=4 rw=r types=int */
};
```