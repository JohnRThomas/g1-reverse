## review group param_0206  (1 cluster(s), kinds=param)

### proposal for param_0206
struct_name: conn_tx_ctx | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Connection TX driver-submission context used by conn_tx_send_to_driver (BLE controller TX path).
fields:
  0x10  uint16_t     field_0x10  
  0x18  void *       field_0x18  

<ground-truth bundle for param_0206>
### cluster param_0206  (param, 1 members, 2 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - conn_tx_send_to_driver @ 0x560cc  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0206 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=r types=short */
    uint8_t    _pad_0x12[0x6];   /* +0x12 pad */
    void *     field_0x18;   /* +0x18  sz=1,4 rw=rw types=ptr,undefined1,undefined4 */
};
```
