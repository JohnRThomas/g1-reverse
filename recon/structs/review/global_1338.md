## review group global_1338  (1 cluster(s), kinds=global)

### proposal for global_1338
struct_name: NRF_QSPI_Type_cinstrdat | is_library: True | library_name: NRF_QSPI_Type | is_array: None | confidence: high
purpose: Memory-mapped nRF5340 QSPI peripheral register block; the two trailing words are CINSTRDAT0/CINSTRDAT1 custom-instruction data registers.
fields:
  0x638  uint32_t     CINSTRDAT0  write-only, set by nrf_qspi_cinstrdata_set
  0x63c  uint32_t     CINSTRDAT1  write-only

<ground-truth bundle for global_1338>
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
