## review group param_0559  (1 cluster(s), kinds=param)

### proposal for param_0559
struct_name: smp_transport_reassembly_ctx | is_library: True | library_name: struct smp_transport (Zephyr mcumgr, .reassembly) | is_array: None | confidence: medium
purpose: MCUmgr SMP transport object; smp_reassembly_expected reads the expected-length field of its embedded reassembly state.
fields:
  0x40  uint32_t     reassembly_expected  
  0x44  uint16_t     field_0x44  

<ground-truth bundle for param_0559>
### cluster param_0559  (param, 1 members, 2 fields, size>=0x48)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: smp; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - smp_reassembly_expected @ 0x80b32  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0559 {
    uint8_t    _pad_0x0[0x40];   /* +0x0 pad */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=int */
    uint16_t   field_0x44;   /* +0x44  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x46[0x2];   /* +0x46 pad */
};
```
