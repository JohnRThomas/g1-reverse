## review group param_0662  (1 cluster(s), kinds=param)

### proposal for param_0662
struct_name: dppi_periph_publish_regs | is_library: True | library_name:  | is_array: None | confidence: low
purpose: Peripheral register block whose PUBLISH/SUBSCRIBE-style fields are written by dppi_apply_channel_config_table while wiring up DPPI channel routing
fields:
  0x508  uint32_t     pub_0  w
  0x50c  uint32_t     pub_1  w
  0x510  uint32_t     pub_2  w
  0x514  uint32_t     pub_3  w
  0x524  uint32_t     pub_4  w
  0x528  uint32_t     pub_5  w
  0x530  uint32_t     pub_6  w
  0x534  uint32_t     pub_7  w
  0x538  uint32_t     pub_8  w
  0x53c  uint32_t     pub_9  w
  0x540  uint32_t     pub_10  w
  0x544  uint32_t     pub_11  w
  0x560  uint32_t     pub_12  w
  0x564  uint32_t     pub_13  w
  0x568  uint32_t     pub_14  w
  0x56c  uint32_t     pub_15  w

<ground-truth bundle for param_0662>
### cluster param_0662  (param, 1 members, 16 fields, size>=0x570)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - dppi_apply_channel_config_table @ 0x83ede  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0662 {
    uint8_t    _pad_0x0[0x508];   /* +0x0 pad */
    uint32_t   field_0x508;   /* +0x508  sz=4 rw=w types=uint */
    uint32_t   field_0x50c;   /* +0x50c  sz=4 rw=w types=uint */
    uint32_t   field_0x510;   /* +0x510  sz=4 rw=w types=uint */
    uint32_t   field_0x514;   /* +0x514  sz=4 rw=w types=uint */
    uint8_t    _pad_0x518[0xc];   /* +0x518 pad */
    uint32_t   field_0x524;   /* +0x524  sz=4 rw=w types=uint */
    uint32_t   field_0x528;   /* +0x528  sz=4 rw=w types=uint */
    uint8_t    _pad_0x52c[0x4];   /* +0x52c pad */
    uint32_t   field_0x530;   /* +0x530  sz=4 rw=w types=uint */
    uint32_t   field_0x534;   /* +0x534  sz=4 rw=w types=uint */
    uint32_t   field_0x538;   /* +0x538  sz=4 rw=w types=uint */
    uint32_t   field_0x53c;   /* +0x53c  sz=4 rw=w types=uint */
    uint32_t   field_0x540;   /* +0x540  sz=4 rw=w types=uint */
    uint32_t   field_0x544;   /* +0x544  sz=4 rw=w types=uint */
    uint8_t    _pad_0x548[0x18];   /* +0x548 pad */
    uint32_t   field_0x560;   /* +0x560  sz=4 rw=w types=uint */
    uint32_t   field_0x564;   /* +0x564  sz=4 rw=w types=uint */
    uint32_t   field_0x568;   /* +0x568  sz=4 rw=w types=uint */
    uint32_t   field_0x56c;   /* +0x56c  sz=4 rw=w types=uint */
};
```
