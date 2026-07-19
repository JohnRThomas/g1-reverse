### struct _reent  (library:struct _reent (newlib/picolibc))  cid=param_0420

purpose: Newlib/Picolibc per-task reentrancy struct (_reent) initialized by __sinit to set up the standard I/O streams.

This object is accessed by these functions (read their fully-named source):
  - __sinit  (as param_1)  ->  recon/readable_sources/app/library/__sinit.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct _reent {
    uint32_t     field_0x4;  /* +0x4  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=rw sz=4 */   <-- NAME ME
    int32_t      field_0x18;  /* +0x18  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x28;  /* +0x28  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x48;  /* +0x48  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x4c;  /* +0x4c  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x50;  /* +0x50  rw=w sz=4 */   <-- NAME ME
};
```