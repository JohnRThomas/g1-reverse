## review group global_1341  (5 cluster(s), kinds=global,param)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for global_1341
struct_name: nrf_qspi_regs | is_library: True | library_name: NRF_QSPI_Type | is_array: None | confidence: medium
purpose: Memory-mapped NRF QSPI peripheral register block accessed by the QSPI silicon-anomaly workaround routine
fields:
  0x4  uint32_t     field_0x4  peripheral register (idx4 read)
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  

<ground-truth bundle for global_1341>
### cluster global_1341  (global, 1 members, 5 fields, size>=0x18)

Global object at fixed address 0x00066848.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - qspi_workaround_apply @ 0x667e0  as 0x00066848  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1341 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0124
struct_name: md5_context | is_library: True | library_name: MD5_CTX / md5_context | is_array: None | confidence: medium
purpose: Classic MD5 hashing context passed to md5_init: bit-count word plus the four 32-bit chaining state words (A,B,C,D).
fields:
  0x4  uint32_t     total_hi  upper bit-count word
  0x8  uint32_t     state_a  MD5 state word A
  0xc  uint32_t     state_b  MD5 state word B
  0x10  uint32_t     state_c  MD5 state word C
  0x14  uint32_t     state_d  MD5 state word D

<ground-truth bundle for param_0124>
### cluster param_0124  (param, 1 members, 5 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - md5_init @ 0x49aa0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0124 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0126
struct_name: unix_datetime_fields | is_library: False | library_name:  | is_array: False | confidence: medium
purpose: Output datetime breakdown (year/month/day/hour/minute) written by unix_timestamp_to_datetime.
fields:
  0x4  int32_t      year  
  0x8  int32_t      month  
  0xc  int32_t      day  
  0x10  int32_t      hour  
  0x14  int32_t      minute  

<ground-truth bundle for param_0126>
### cluster param_0126  (param, 1 members, 5 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - unix_timestamp_to_datetime @ 0x4a1b8  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0126 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0337
struct_name: nrf_qspi_pins_t | is_library: True | library_name: nrf_qspi_pins_t | is_array: None | confidence: high
purpose: nrfx QSPI pin assignment structure (sck/csn/io0-io3) passed to nrf_qspi_pins_set.
fields:
  0x4  uint32_t     csn_pin  
  0x8  uint32_t     io0_pin  
  0xc  uint32_t     io1_pin  
  0x10  uint32_t     io2_pin  
  0x14  uint32_t     io3_pin  

<ground-truth bundle for param_0337>
### cluster param_0337  (param, 1 members, 5 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrf; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrf_qspi_pins_set @ 0x66784  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0337 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0339
struct_name: nrfx_qspi_cinstr_config_t | is_library: True | library_name: nrfx_qspi_cinstr_config_t | is_array: None | confidence: high
purpose: nrfx QSPI custom-instruction transfer configuration (opcode, length, IO2/IO3 levels, WREN flag, address) consumed by nrfx_qspi_cinstr_xfer
fields:
  0x4  uint32_t     field_0x4  idx4 read, opcode/length
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  

<ground-truth bundle for param_0339>
### cluster param_0339  (param, 1 members, 5 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_qspi_cinstr_xfer @ 0x669f4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0339 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```
