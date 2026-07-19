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