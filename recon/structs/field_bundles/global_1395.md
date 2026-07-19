### struct spinlock_owner_source  (library:)  cid=global_1395

purpose: Kernel object read by z_spin_lock_set_owner while stamping a k_spinlock owner (SPIN_VALIDATE build).

This object is accessed by these functions (read their fully-named source):
  - z_spin_lock_set_owner  (as 0x00072084)  ->  recon/readable_sources/app/library/z_spin_lock_set_owner.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct spinlock_owner_source {
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0x10;  /* +0x10  rw=r sz=1 */   <-- NAME ME
};
```