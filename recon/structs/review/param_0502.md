## review group param_0502  (1 cluster(s), kinds=param)

### proposal for param_0502
struct_name: nvs_ate_record | is_library: True | library_name: struct nvs_ate (Zephyr NVS subsystem) | is_array: False | confidence: medium
purpose: Zephyr NVS allocation table entry (ATE) whose fields are folded into the CRC8 computed by nvs_ate_crc8_update.
fields:
  0x2  uint16_t     len_or_offset  16-bit ATE field (len/offset)
  0x7  uint8_t      crc8  trailing crc8 byte of the ATE

<ground-truth bundle for param_0502>
### cluster param_0502  (param, 2 members, 2 fields, size>=0x9)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/2 members are LIBRARY-class)

members (2 shown of 2):
  - nvs_ate_crc8_update @ 0x7e5c8  as param_1  [LIBRARY]
  - FUN_0007e672 @ 0x7e672  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0502 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x4[0x3];   /* +0x4 pad */
    uint8_t    field_0x7;   /* +0x7  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    _pad_0x8[0x1];   /* +0x8 pad */
};
```
