## review group global_1561  (1 cluster(s), kinds=global)

### proposal for global_1561
struct_name: nrf_qspi_regs_ext | is_library: True | library_name: NRF_QSPI_Type | is_array: None | confidence: medium
purpose: Extended NRF QSPI peripheral register block / EasyDMA buffer region written by nrfx_qspi_write (task trigger + status/config registers spread across a 0x514-byte region)
fields:
  0x100  uint32_t     field_0x100  write-only task/trigger register
  0x504  uint32_t     field_0x504  write-only config/status register
  0x510  uint32_t     field_0x510  write-only config register

<ground-truth bundle for global_1561>
### cluster global_1561  (global, 1 members, 3 fields, size>=0x514)

Global object at fixed address 0x00066630.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_qspi_write @ 0x85200  as 0x00066630  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1561 {
    uint8_t    _pad_0x0[0x100];   /* +0x0 pad */
    uint32_t   field_0x100;   /* +0x100  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x104[0x400];   /* +0x104 pad */
    uint32_t   field_0x504;   /* +0x504  sz=4 rw=w types=int */
    uint8_t    _pad_0x508[0x8];   /* +0x508 pad */
    uint32_t   field_0x510;   /* +0x510  sz=4 rw=w types=int */
};
```
