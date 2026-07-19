## review group param_0384  (2 cluster(s), kinds=param)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for param_0384
struct_name: lc3_sns_state | is_library: True | library_name: lc3_sns_data | is_array: None | confidence: medium
purpose: LC3 codec sensitivity/attack-detection analysis state used by lc3_sns_analyze
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x19  uint8_t      flag_byte  

<ground-truth bundle for param_0384>
### cluster param_0384  (param, 1 members, 7 fields, size>=0x1d)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_sns_analyze @ 0x6c778  as param_5  [APPLICATION]

layout notes: 0x4: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0384 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint16_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    field_0x6;   /* +0x6  sz=1 rw=rw types=byte */
    uint8_t    _pad_0x7[0x1];   /* +0x7 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x1];   /* +0x18 pad */
    uint8_t    field_0x19;   /* +0x19  sz=1 rw=rw types=byte */
    uint8_t    _pad_0x1a[0x3];   /* +0x1a pad */
};
```

### proposal for param_0385
struct_name: lc3_sns_state | is_library: True | library_name: lc3 (Bluetooth LE Audio codec) | is_array: None | confidence: low
purpose: LC3 audio codec Spectral Noise Shaping (SNS) internal state, written by lc3_sns_put_data
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x19  uint8_t      field_0x19  

<ground-truth bundle for param_0385>
### cluster param_0385  (param, 1 members, 7 fields, size>=0x1d)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_sns_put_data @ 0x6efdc  as param_2  [APPLICATION]

layout notes: 0x4: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0385 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint16_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    field_0x6;   /* +0x6  sz=1 rw=r types=byte */
    uint8_t    _pad_0x7[0x1];   /* +0x7 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x1];   /* +0x18 pad */
    uint8_t    field_0x19;   /* +0x19  sz=1 rw=r types=byte */
    uint8_t    _pad_0x1a[0x3];   /* +0x1a pad */
};
```
