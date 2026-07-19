## review group param_0055  (1 cluster(s), kinds=param)

### proposal for param_0055
struct_name: st25dv_ndef_record_desc | is_library: False | library_name:  | is_array: True | confidence: low
purpose: NDEF record descriptor (pointer/length style pair) consumed by st25dv_build_and_write_ndef_records when assembling NFC tag records.
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for param_0055>
### cluster param_0055  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - st25dv_build_and_write_ndef_records @ 0x250f8  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0055 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
