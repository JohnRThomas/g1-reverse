## review group param_0260  (1 cluster(s), kinds=param)

### proposal for param_0260
struct_name: gatt_ccc_update_ctx | is_library: True | library_name: bt gatt ccc-related struct (unidentified exact type) | is_array: None | confidence: low
purpose: CCC (Client Characteristic Configuration) update context passed to gatt_send_ccc_update: handle/value pairs.
fields:
  0x4  uint16_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint16_t     field_0xc  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for param_0260>
### cluster param_0260  (param, 1 members, 4 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_send_ccc_update @ 0x5b890  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0260 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint16_t   field_0x4;   /* +0x4  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x6[0x2];   /* +0x6 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=w types=int,uint,undefined4 */
    uint16_t   field_0xc;   /* +0xc  sz=2 rw=r types=short */
    uint8_t    _pad_0xe[0x2];   /* +0xe pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int,undefined4 */
};
```
