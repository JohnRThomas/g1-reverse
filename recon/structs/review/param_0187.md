## review group param_0187  (1 cluster(s), kinds=param)

### proposal for param_0187
struct_name: net_buf_hdr | is_library: True | library_name: net_buf | is_array: None | confidence: low
purpose: Zephyr net_buf header fields accessed while logging an unhandled HCI event
fields:
  0xc  uint32_t     data_ptr_or_len  r
  0x10  uint16_t     len  r

<ground-truth bundle for param_0187>
### cluster param_0187  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: log; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - log_unhandled_hci_event @ 0x53580  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0187 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
};
```
