### cluster param_0444  (param, 1 members, 4 fields, size>=0x64)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - cc_mbedtls_aes_init @ 0x7ab00  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0444 {
    uint8_t    _pad_0x0[0x54];   /* +0x0 pad */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x5c;   /* +0x5c  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=w types=undefined4 */
};
```