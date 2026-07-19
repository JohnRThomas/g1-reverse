### struct aes_drv_ctx  (library:mbedtls_aes_context)  cid=param_0446

purpose: AES driver/CryptoCell context shared by cc_mbedtls_aes_crypt_ecb, InitAes, ProcessAesDrv and FinishAesDrv (key schedule + state words).

This object is accessed by these functions (read their fully-named source):
  - cc_mbedtls_aes_crypt_ecb  (as param_1)  [no source file]
  - InitAes  (as param_1)  [no source file]
  - ProcessAesDrv  (as param_1)  [no source file]
  - FinishAesDrv  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct aes_drv_ctx {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0xf;  /* +0xf  rw=rw sz=1 */   <-- NAME ME
    uint32_t     field_0x30;  /* +0x30  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x34;  /* +0x34  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x38;  /* +0x38  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x40;  /* +0x40  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x44;  /* +0x44  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x48;  /* +0x48  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x4c;  /* +0x4c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x50;  /* +0x50  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x58;  /* +0x58  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x5c;  /* +0x5c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x60;  /* +0x60  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x64;  /* +0x64  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x68;  /* +0x68  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x6c;  /* +0x6c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x70;  /* +0x70  rw=r sz=4 */   <-- NAME ME
};
```