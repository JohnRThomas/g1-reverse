### cluster global_1338  (global, 1 members, 2 fields, size>=0x640)

Global object at fixed address 0x00066780.

library hint: LIKELY LIBRARY (prefixes: nrf; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrf_qspi_cinstrdata_set @ 0x66720  as 0x00066780  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1338 {
    uint8_t    _pad_0x0[0x638];   /* +0x0 pad */
    uint32_t   field_0x638;   /* +0x638  sz=4 rw=w types=uint */
    uint32_t   field_0x63c;   /* +0x63c  sz=4 rw=w types=uint */
};
```