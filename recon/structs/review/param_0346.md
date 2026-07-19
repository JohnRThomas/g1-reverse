## review group param_0346  (1 cluster(s), kinds=param)

### proposal for param_0346
struct_name: nrfx_spim_xfer_desc | is_library: True | library_name: nrfx_spim_xfer_desc_t | is_array: None | confidence: high
purpose: nrfx SPIM transfer descriptor (tx buffer/length, rx buffer/length) passed to nrfx_spim_xfer.
fields:
  0x4  const uint8_t* p_tx_buffer  
  0x8  uint32_t     tx_length  
  0xc  uint8_t*     p_rx_buffer  

<ground-truth bundle for param_0346>
### cluster param_0346  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_spim_xfer @ 0x67304  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0346 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
