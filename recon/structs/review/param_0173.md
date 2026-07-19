## review group param_0173  (1 cluster(s), kinds=param)

### proposal for param_0173
struct_name: smp_pkt_ctx | is_library: True | library_name: smp_hdr | is_array: None | confidence: low
purpose: MCUmgr SMP request-packet processing context (net_buf-like: length/data fields)
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for param_0173>
### cluster param_0173  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: smp; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - smp_process_request_packet @ 0x513e8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0173 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
