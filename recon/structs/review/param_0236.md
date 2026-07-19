## review group param_0236  (1 cluster(s), kinds=param)

### proposal for param_0236
struct_name: att_pdu_buf_ctx | is_library: True | library_name: struct net_buf (Zephyr, partial) | is_array: None | confidence: low
purpose: ATT prepare-write-request buffer/PDU object (likely a Zephyr net_buf view) read by att_prepare_write_req for a length/size word and a handle-ish short.
fields:
  0xc  uint32_t     field_0xc  
  0x10  uint16_t     field_0x10  

<ground-truth bundle for param_0236>
### cluster param_0236  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - att_prepare_write_req @ 0x590bc  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0236 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
};
```
