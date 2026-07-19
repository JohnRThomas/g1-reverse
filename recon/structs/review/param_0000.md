## review group param_0000  (1 cluster(s), kinds=param)

### proposal for param_0000
struct_name: battery_model_state | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Large G1-original battery model/state structure passed into battery_model_state_update, holding voltage/current/capacity model coefficients and history across several sub-regions.
fields:
  0x4  uint32_t     field_0x4  
  0x48  uint32_t     field_0x48  
  0x4c  uint32_t     field_0x4c  
  0x50  uint32_t     field_0x50  
  0x54  uint32_t     field_0x54  
  0x5c  uint32_t     field_0x5c  
  0x128  uint32_t     field_0x128  
  0x12c  uint32_t     field_0x12c  
  0x130  uint32_t     field_0x130  
  0x134  uint32_t     field_0x134  
  0x138  uint32_t     field_0x138  
  0x13c  uint32_t     field_0x13c  
  0x140  uint32_t     field_0x140  
  0x144  uint32_t     field_0x144  
  0x148  uint32_t     field_0x148  
  0x464  uint32_t     field_0x464  
  0x5d3  uint8_t      field_0x5d3  
  0x65c  uint32_t     field_0x65c  
  0x660  uint32_t     field_0x660  
  0x978  uint32_t     field_0x978  
  0x97c  uint32_t     field_0x97c  
  0x980  uint32_t     field_0x980  
  0x984  uint32_t     field_0x984  
  0xc9c  uint32_t     field_0xc9c  
  0xca0  uint32_t     field_0xca0  
  0x1744  uint32_t     field_0x1744  
  0x1748  uint32_t     field_0x1748  
  0x1750  uint32_t     field_0x1750  
  0x1754  uint32_t     field_0x1754  
  0x1758  uint32_t     field_0x1758  
  0x175c  uint32_t     field_0x175c  
  0x1760  uint32_t     field_0x1760  
  0x1764  uint32_t     field_0x1764  
  0x1768  uint32_t     field_0x1768  
  0x176c  uint32_t     field_0x176c  
  0x1770  uint32_t     field_0x1770  
  0x1774  uint32_t     field_0x1774  

<ground-truth bundle for param_0000>
### cluster param_0000  (param, 1 members, 37 fields, size>=0x1778)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - battery_model_state_update @ 0xc358  as param_5  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0000 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x40];   /* +0x8 pad */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x50;   /* +0x50  sz=4 rw=r types=idx4 */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x58[0x4];   /* +0x58 pad */
    uint32_t   field_0x5c;   /* +0x5c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x60[0xc8];   /* +0x60 pad */
    uint32_t   field_0x128;   /* +0x128  sz=4 rw=r types=idx4 */
    uint32_t   field_0x12c;   /* +0x12c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x130;   /* +0x130  sz=4 rw=r types=idx4 */
    uint32_t   field_0x134;   /* +0x134  sz=4 rw=r types=idx4 */
    uint32_t   field_0x138;   /* +0x138  sz=4 rw=r types=idx4 */
    uint32_t   field_0x13c;   /* +0x13c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x140;   /* +0x140  sz=4 rw=r types=idx4 */
    uint32_t   field_0x144;   /* +0x144  sz=4 rw=r types=idx4 */
    uint32_t   field_0x148;   /* +0x148  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x14c[0x318];   /* +0x14c pad */
    uint32_t   field_0x464;   /* +0x464  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x468[0x16b];   /* +0x468 pad */
    uint8_t    field_0x5d3;   /* +0x5d3  sz=1 rw=r types=char */
    uint8_t    _pad_0x5d4[0x88];   /* +0x5d4 pad */
    uint32_t   field_0x65c;   /* +0x65c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x660;   /* +0x660  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x664[0x314];   /* +0x664 pad */
    uint32_t   field_0x978;   /* +0x978  sz=4 rw=r types=idx4 */
    uint32_t   field_0x97c;   /* +0x97c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x980;   /* +0x980  sz=4 rw=r types=idx4 */
    uint32_t   field_0x984;   /* +0x984  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x988[0x314];   /* +0x988 pad */
    uint32_t   field_0xc9c;   /* +0xc9c  sz=4 rw=r types=idx4 */
    uint32_t   field_0xca0;   /* +0xca0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xca4[0xaa0];   /* +0xca4 pad */
    uint32_t   field_0x1744;   /* +0x1744  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1748;   /* +0x1748  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x174c[0x4];   /* +0x174c pad */
    uint32_t   field_0x1750;   /* +0x1750  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1754;   /* +0x1754  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1758;   /* +0x1758  sz=4 rw=r types=idx4 */
    uint32_t   field_0x175c;   /* +0x175c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1760;   /* +0x1760  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1764;   /* +0x1764  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1768;   /* +0x1768  sz=4 rw=r types=idx4 */
    uint32_t   field_0x176c;   /* +0x176c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1770;   /* +0x1770  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1774;   /* +0x1774  sz=4 rw=r types=idx4 */
};
```
