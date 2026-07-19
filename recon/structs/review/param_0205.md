## review group param_0205  (1 cluster(s), kinds=param)

### proposal for param_0205
struct_name: conn_tx_saadc_shared_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Shared context object used by both conn_tx_send_to_driver and saadc_start_read, holding a small header and three data words
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for param_0205>
### cluster param_0205  (param, 2 members, 5 fields, size>=0x15)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - conn_tx_send_to_driver @ 0x560cc  as param_2  [APPLICATION]
  - saadc_start_read @ 0x5f760  as param_2  [APPLICATION]

layout notes: 0x10: access width 4 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0205 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=1,4 rw=r types=byte,idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4,undefined4 */
    uint8_t    field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint8_t    field_0x11;   /* +0x11  sz=1 rw=r types=byte */
    uint8_t    _pad_0x12[0x3];   /* +0x12 pad */
};
```
