### struct smp_c1_param  (library:smp c1 params (unresolved))  cid=param_0641

purpose: SMP c1 confirm-value computation parameter block used by smp_c1 (param_6).

This object is accessed by these functions (read their fully-named source):
  - smp_c1  (as param_6)  ->  recon/readable_sources/app/library/smp_c1.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct smp_c1_param {
    uint32_t     field_0x1;  /* +0x1  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x5;  /* +0x5  rw=r sz=2 */   <-- NAME ME
};
```