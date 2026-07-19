## review group param_0446  (1 cluster(s), kinds=param)

### proposal for param_0446
struct_name: aes_drv_ctx | is_library: True | library_name: mbedtls_aes_context | is_array: None | confidence: medium
purpose: AES driver/CryptoCell context shared by cc_mbedtls_aes_crypt_ecb, InitAes, ProcessAesDrv and FinishAesDrv
fields:
  0x4  uint32_t     field_0x4  idx4
  0x8  uint32_t     field_0x8  idx4
  0xc  uint32_t     field_0xc  idx4
  0x30  uint32_t     field_0x30  idx4/uint
  0x34  uint32_t     field_0x34  rw idx4/int/uint
  0x38  uint32_t     field_0x38  int/uint
  0x40  uint32_t     field_0x40  idx4
  0x44  uint32_t     field_0x44  idx4
  0x48  uint32_t     field_0x48  idx4
  0x4c  uint32_t     field_0x4c  idx4
  0x50  uint32_t     field_0x50  idx4
  0x58  uint32_t     field_0x58  idx4
  0x5c  uint32_t     field_0x5c  idx4/uint
  0x60  uint32_t     field_0x60  idx4/uint
  0x64  uint32_t     field_0x64  idx4
  0x68  uint32_t     field_0x68  idx4
  0x6c  uint32_t     field_0x6c  idx4
  0x70  uint32_t     field_0x70  idx4

<ground-truth bundle for param_0446>
### cluster param_0446  (param, 4 members, 19 fields, size>=0x74)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 4/4 members are LIBRARY-class)

members (4 shown of 4):
  - cc_mbedtls_aes_crypt_ecb @ 0x7ab70  as param_1  [LIBRARY]
  - InitAes @ 0x7b468  as param_1  [LIBRARY]
  - ProcessAesDrv @ 0x7b694  as param_1  [LIBRARY]
  - FinishAesDrv @ 0x7b9cc  as param_1  [LIBRARY]

layout notes: 0xc: access width 4 exceeds gap 3 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0446 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    field_0xc[0x3];   /* +0xc pad */
    uint8_t    field_0xf;   /* +0xf  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0x10[0x20];   /* +0x10 pad */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4,uint */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=rw types=idx4,int,uint,undefined4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=int,uint */
    uint8_t    _pad_0x3c[0x4];   /* +0x3c pad */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=idx4 */
    uint32_t   field_0x44;   /* +0x44  sz=4 rw=r types=idx4 */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x50;   /* +0x50  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x54[0x4];   /* +0x54 pad */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=r types=idx4 */
    uint32_t   field_0x5c;   /* +0x5c  sz=4 rw=r types=idx4,uint */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=r types=idx4,uint */
    uint32_t   field_0x64;   /* +0x64  sz=4 rw=r types=idx4 */
    uint32_t   field_0x68;   /* +0x68  sz=4 rw=r types=idx4 */
    uint32_t   field_0x6c;   /* +0x6c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x70;   /* +0x70  sz=4 rw=r types=idx4 */
};
```
