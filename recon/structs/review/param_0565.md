## review group param_0565  (1 cluster(s), kinds=param)

### proposal for param_0565
struct_name: conn_id_addr | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Connection identity/address matching record used by conn_match_id_and_addr
fields:
  0x18  uint32_t     conn_id  
  0x1c  uint8_t      addr_type  

<ground-truth bundle for param_0565>
### cluster param_0565  (param, 1 members, 2 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - conn_match_id_and_addr @ 0x80c20  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0565 {
    uint8_t    _pad_0x0[0x18];   /* +0x0 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=int */
    uint8_t    field_0x1c;   /* +0x1c  sz=1 rw=r types=char */
    uint8_t    _pad_0x1d[0x3];   /* +0x1d pad */
};
```
