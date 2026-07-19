## review group param_0064  (1 cluster(s), kinds=param)

### proposal for param_0064
struct_name: spi_trans_desc | is_library: False | library_name:  | is_array: False | confidence: low
purpose: SPI master transaction descriptor used by spi_master_trans_data_tx_rx to describe transfer length and mode.
fields:
  0x14  int32_t      xfer_len  transfer length/count
  0x18  uint8_t      xfer_flags  mode/flag byte

<ground-truth bundle for param_0064>
### cluster param_0064  (param, 1 members, 2 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - spi_master_trans_data_tx_rx @ 0x262ac  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0064 {
    uint8_t    _pad_0x0[0x14];   /* +0x0 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=int */
    uint8_t    field_0x18;   /* +0x18  sz=1 rw=r types=byte */
    uint8_t    _pad_0x19[0x3];   /* +0x19 pad */
};
```
