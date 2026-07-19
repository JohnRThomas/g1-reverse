## review group param_0300  (1 cluster(s), kinds=param)

### proposal for param_0300
struct_name: qspi_cinstr_req | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: G1-original wrapper around a QSPI custom-instruction request, carrying tx/rx buffer pointers passed to qspi_nor_send_cinstr.
fields:
  0x4  const void * tx_buf  
  0x8  void *       rx_buf  

<ground-truth bundle for param_0300>
### cluster param_0300  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - qspi_nor_send_cinstr @ 0x60ab0  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0300 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    void *     field_0x8;   /* +0x8  sz=4 rw=r types=ptr */
};
```
