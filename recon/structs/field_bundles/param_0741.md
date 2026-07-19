### struct itoa_ctx  (G1-original)  cid=param_0741

purpose: itoa-with-signed-exponent formatting context/buffer used by itoa_signed_exponent (param_1).

This object is accessed by these functions (read their fully-named source):
  - itoa_signed_exponent  (as param_1)  ->  recon/readable_sources/app/g1/itoa_signed_exponent.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct itoa_ctx {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
};
```