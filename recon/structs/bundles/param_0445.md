### cluster param_0445  (param, 1 members, 3 fields, size>=0x40)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - cc_mbedtls_aes_setkey_enc @ 0x7ab2c  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0445 {
    uint8_t    _pad_0x0[0x30];   /* +0x0 pad */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x34[0x4];   /* +0x34 pad */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=w types=undefined4 */
    uint8_t    field_0x3c;   /* +0x3c  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x3d[0x3];   /* +0x3d pad */
};
```