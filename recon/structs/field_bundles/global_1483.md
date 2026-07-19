### struct cc3xx_aes_drv_ctx  (library:nrf_cc3xx AES driver context)  cid=global_1483

purpose: CryptoCell/CC3xx AES driver context/register-shadow at 0x7b9a8 used by ProcessAesDrv (sparse control/status words across a ~0xc2c region).

This object is accessed by these functions (read their fully-named source):
  - ProcessAesDrv  (as 0x0007b9a8)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct cc3xx_aes_drv_ctx {
    uint32_t     field_0x400;  /* +0x400  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x440;  /* +0x440  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x460;  /* +0x460  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x810;  /* +0x810  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xb0c;  /* +0xb0c  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xc28;  /* +0xc28  rw=w sz=4 */   <-- NAME ME
};
```