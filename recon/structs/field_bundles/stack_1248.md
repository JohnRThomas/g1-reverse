### struct smp_dhkey_check_buf  (G1-original)  cid=stack_1248

purpose: Local 0x24-byte buffer in smp_dhkey_check_generate (two chained values at start/end).

This object is accessed by these functions (read their fully-named source):
  - smp_dhkey_check_generate  (as local_48)  ->  recon/readable_sources/app/library/smp_dhkey_check_generate.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct smp_dhkey_check_buf {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=r sz=4 */   <-- NAME ME
};
```