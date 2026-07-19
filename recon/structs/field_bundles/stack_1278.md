### struct uarte_isr_scratch  (G1-original)  cid=stack_1278

purpose: Stack-local status/error scratch bytes (local_2c) inside uarte_nrfx_isr.

This object is accessed by these functions (read their fully-named source):
  - uarte_nrfx_isr  (as local_2c)  ->  recon/readable_sources/app/g1/uarte_nrfx_isr.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct uarte_isr_scratch {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x4;  /* +0x4  rw=r sz=1 */   <-- NAME ME
};
```