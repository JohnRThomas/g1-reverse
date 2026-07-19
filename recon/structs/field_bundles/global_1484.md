### struct aes_drv_ctx  (library:nrf_cc3xx AES driver context)  cid=global_1484

purpose: Large CryptoCell/nrf_cc3xx AES hardware-driver context (global 0x7bbb0, >=0x814 bytes); FinishAesDrv (a LIBRARY fn) reads status/config near front, writes completion flags near end.

This object is accessed by these functions (read their fully-named source):
  - FinishAesDrv  (as 0x0007bbb0)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct aes_drv_ctx {
    uint32_t     field_0x440;  /* +0x440  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x460;  /* +0x460  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x47c;  /* +0x47c  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x810;  /* +0x810  rw=w sz=4 */   <-- NAME ME
};
```