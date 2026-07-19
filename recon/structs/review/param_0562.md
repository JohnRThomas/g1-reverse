## review group param_0562  (1 cluster(s), kinds=param)

### proposal for param_0562
struct_name: smp_transport_reassembly | is_library: True | library_name: smp_transport | is_array: False | confidence: medium
purpose: mcumgr SMP transport reassembly state tracked by smp_reassembly_complete, holding accumulated length and expected length
fields:
  0x40  int32_t      reassembly_len  rw current accumulated length
  0x44  uint16_t     reassembly_expected_len  rw expected total length

<ground-truth bundle for param_0562>
### cluster param_0562  (param, 1 members, 2 fields, size>=0x48)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: smp; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - smp_reassembly_complete @ 0x80bb2  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0562 {
    uint8_t    _pad_0x0[0x40];   /* +0x0 pad */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=rw types=int,undefined4 */
    uint16_t   field_0x44;   /* +0x44  sz=2 rw=rw types=undefined2,ushort */
    uint8_t    _pad_0x46[0x2];   /* +0x46 pad */
};
```
