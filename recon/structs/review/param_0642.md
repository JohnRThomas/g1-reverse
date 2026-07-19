## review group param_0642  (1 cluster(s), kinds=param)

### proposal for param_0642
struct_name: bt_addr_le | is_library: True | library_name: bt_addr_le_t | is_array: None | confidence: medium
purpose: Bluetooth LE address (identity address) argument to the SM 'c1' pairing confirm-value function smp_c1
fields:
  0x1  uint32_t     addr_lo  low 4 bytes of the 6-byte device address
  0x5  uint16_t     addr_hi  high 2 bytes of the 6-byte device address

<ground-truth bundle for param_0642>
### cluster param_0642  (param, 1 members, 2 fields, size>=0x9)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: smp; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - smp_c1 @ 0x8323a  as param_5  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0642 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint32_t   field_0x1;   /* +0x1  sz=4 rw=r types=undefined4 */
    uint16_t   field_0x5;   /* +0x5  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x7[0x2];   /* +0x7 pad */
};
```
