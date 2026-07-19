## review group param_0644  (1 cluster(s), kinds=param)

### proposal for param_0644
struct_name: bt_crypto_f6_input | is_library: True | library_name: bt_crypto (SMP f6 function) input buffer | is_array: True | confidence: low
purpose: Parameter block for bt_crypto_f6 (Bluetooth LE Secure Connections f6 key-derivation function), likely a 128-bit input value viewed as a byte buffer.
fields:
  0x1  uint32_t     field_0x1  
  0x5  uint16_t     field_0x5  

<ground-truth bundle for param_0644>
### cluster param_0644  (param, 1 members, 2 fields, size>=0x9)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_crypto_f6 @ 0x83634  as param_7  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0644 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint32_t   field_0x1;   /* +0x1  sz=4 rw=r types=undefined4 */
    uint16_t   field_0x5;   /* +0x5  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x7[0x2];   /* +0x7 pad */
};
```
