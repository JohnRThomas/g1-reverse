## review group param_0454  (1 cluster(s), kinds=param)

### proposal for param_0454
struct_name: aes_key_context | is_library: True | library_name: Nordic CryptoCell AES context (CRYS_AESUserContext_t or mbedtls_aes_context) | is_array: None | confidence: low
purpose: AES key-loading context read by LoadAesKey: nine consecutive key/round words, a status byte, and a trailing word.
fields:
  0x10  uint32_t     key_word_0  read-only undefined4
  0x14  uint32_t     key_word_1  read-only undefined4
  0x18  uint32_t     key_word_2  read-only undefined4
  0x1c  uint32_t     key_word_3  read-only undefined4
  0x20  uint32_t     key_word_4  read-only undefined4
  0x24  uint32_t     key_word_5  read-only undefined4
  0x28  uint32_t     key_word_6  read-only undefined4
  0x2c  uint32_t     key_word_7  read-only undefined4
  0x30  uint32_t     rounds_or_len  read-only int/undefined4
  0x3c  uint8_t      status  read-only char
  0x40  uint32_t     field_0x40  read-only undefined4

<ground-truth bundle for param_0454>
### cluster param_0454  (param, 1 members, 11 fields, size>=0x44)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - LoadAesKey @ 0x7b530  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0454 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=int,undefined4 */
    uint8_t    _pad_0x34[0x8];   /* +0x34 pad */
    uint8_t    field_0x3c;   /* +0x3c  sz=1 rw=r types=char */
    uint8_t    _pad_0x3d[0x3];   /* +0x3d pad */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=undefined4 */
};
```
