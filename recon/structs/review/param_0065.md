## review group param_0065  (2 cluster(s), kinds=param)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for param_0065
struct_name: spim_instance_config | is_library: False | library_name:  | is_array: False | confidence: medium
purpose: SPIM peripheral instance configuration/state selected by mode in spim_select_instance_by_mode; holds two output pointers/values, a mode word, and six raw config bytes (likely pin numbers).
fields:
  0xc  uint32_t     reg_base_or_handle  write-only
  0x10  uint32_t     irq_or_handle2  write-only
  0x14  int32_t      mode  
  0x18  uint8_t      pin_sck  
  0x19  uint8_t      pin_mosi  
  0x1a  uint8_t      pin_miso  
  0x1b  uint8_t      pin_cs  
  0x1c  uint8_t      pin_extra1  
  0x1d  uint8_t      pin_extra2  

<ground-truth bundle for param_0065>
### cluster param_0065  (param, 1 members, 9 fields, size>=0x21)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - spim_select_instance_by_mode @ 0x26338  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0065 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=rw types=int,undefined4 */
    uint8_t    field_0x18;   /* +0x18  sz=1 rw=r types=byte */
    uint8_t    field_0x19;   /* +0x19  sz=1 rw=r types=byte */
    uint8_t    field_0x1a;   /* +0x1a  sz=1 rw=r types=byte */
    uint8_t    field_0x1b;   /* +0x1b  sz=1 rw=r types=byte */
    uint8_t    field_0x1c;   /* +0x1c  sz=1 rw=r types=byte */
    uint8_t    field_0x1d;   /* +0x1d  sz=1 rw=r types=byte */
    uint8_t    _pad_0x1e[0x3];   /* +0x1e pad */
};
```

### proposal for param_0066
struct_name: spi_master_config | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: SPI master peripheral configuration/state passed to spi_master_init: frequency/mode words followed by pin assignment bytes.
fields:
  0xc  uint32_t     freq_hz  write-only, likely clock frequency
  0x10  uint32_t     config_flags  write-only config word
  0x14  uint32_t     mode  read/write mode/state word
  0x18  uint8_t      sck_pin  pin assignment byte
  0x19  uint8_t      mosi_pin  pin assignment byte
  0x1a  uint8_t      miso_pin  pin assignment byte
  0x1b  uint8_t      cs_pin  pin assignment byte
  0x1c  uint8_t      bit_order  config byte
  0x1d  uint8_t      cpol_cpha  config byte

<ground-truth bundle for param_0066>
### cluster param_0066  (param, 1 members, 9 fields, size>=0x21)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - spi_master_init @ 0x26418  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0066 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=rw types=int,undefined4 */
    uint8_t    field_0x18;   /* +0x18  sz=1 rw=r types=byte,char */
    uint8_t    field_0x19;   /* +0x19  sz=1 rw=r types=byte */
    uint8_t    field_0x1a;   /* +0x1a  sz=1 rw=r types=byte */
    uint8_t    field_0x1b;   /* +0x1b  sz=1 rw=r types=byte */
    uint8_t    field_0x1c;   /* +0x1c  sz=1 rw=r types=byte */
    uint8_t    field_0x1d;   /* +0x1d  sz=1 rw=r types=byte */
    uint8_t    _pad_0x1e[0x3];   /* +0x1e pad */
};
```
