### cluster global_1337  (global, 1 members, 2 fields, size>=0x640)

Global object at fixed address 0x0006671c.

library hint: LIKELY LIBRARY (prefixes: nrf; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrf_qspi_cinstrdata_get @ 0x666e0  as 0x0006671c  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1337 {
    uint8_t    _pad_0x0[0x638];   /* +0x0 pad */
    uint32_t   field_0x638;   /* +0x638  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x63c;   /* +0x63c  sz=4 rw=r types=undefined4 */
};
```