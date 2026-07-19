## review group param_0461  (1 cluster(s), kinds=param)

### proposal for param_0461
struct_name: opt_record | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: G1-original option/attribute record with three settable option-field slots (opt_field1/2/3_set write 0x4/0x8/0xc-0x18/0x1c) and a trailing four-word tail (0x60-0x6c) read back by opt_record_decode.
fields:
  0x4  uint32_t     field1  
  0x8  uint32_t     field2  
  0xc  uint32_t     field3  
  0x10  uint32_t     field4  
  0x14  uint32_t     field5  
  0x18  uint32_t     field6  
  0x1c  uint32_t     field7  
  0x60  uint32_t     decoded_a  
  0x64  uint32_t     decoded_b  
  0x68  uint32_t     decoded_c  
  0x6c  uint32_t     decoded_d  

<ground-truth bundle for param_0461>
### cluster param_0461  (param, 5 members, 11 fields, size>=0x70)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (5 shown of 5):
  - opt_field1_set @ 0x7c430  as param_1  [APPLICATION]
  - opt_field2_set @ 0x7c456  as param_1  [APPLICATION]
  - opt_field3_set @ 0x7c48a  as param_1  [APPLICATION]
  - opt_record_init @ 0x7c4b6  as param_1  [APPLICATION]
  - opt_record_decode @ 0x7c4f4  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0461 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=rw types=idx4,int,uint */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=idx4,int,uint */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=int,uint */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=idx4,int,uint */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=rw types=idx4,undefined4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=rw types=idx4,undefined4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x20[0x40];   /* +0x20 pad */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=r types=idx4 */
    uint32_t   field_0x64;   /* +0x64  sz=4 rw=r types=idx4 */
    uint32_t   field_0x68;   /* +0x68  sz=4 rw=r types=idx4 */
    uint32_t   field_0x6c;   /* +0x6c  sz=4 rw=r types=idx4 */
};
```
