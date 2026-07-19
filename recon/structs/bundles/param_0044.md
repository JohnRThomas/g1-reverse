### cluster param_0044  (param, 1 members, 3 fields, size>=0x1044)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - device_info_register_persistent_fields @ 0x23230  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0044 {
    uint8_t    _pad_0x0[0xfec];   /* +0x0 pad */
    uint32_t   field_0xfec;   /* +0xfec  sz=4 rw=r types=undefined4 */
    uint32_t   field_0xff0;   /* +0xff0  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0xff4[0x4c];   /* +0xff4 pad */
    void *     field_0x1040;   /* +0x1040  sz=4 rw=r types=ptr */
};
```