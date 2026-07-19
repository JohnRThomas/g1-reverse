## review group param_0067  (1 cluster(s), kinds=param)

### proposal for param_0067
struct_name: spi_master_ops | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Small struct passed to spi_master_install_ops() holding two operation-table/context words (likely function-pointer or ops-index slots for the SPI master driver).
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for param_0067>
### cluster param_0067  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - spi_master_install_ops @ 0x2659c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0067 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
