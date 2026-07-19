### struct spinlock_validate_state  (library:k_spinlock validation aux (kernel/spinlock))  cid=global_1394

purpose: Zephyr spinlock-validation bookkeeping global accessed by z_spin_unlock_valid to detect double-unlock / wrong-owner errors (CONFIG_SPIN_VALIDATE).

This object is accessed by these functions (read their fully-named source):
  - z_spin_unlock_valid  (as 0x00072074)  ->  recon/readable_sources/app/library/z_spin_unlock_valid.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct spinlock_validate_state {
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0x10;  /* +0x10  rw=r sz=1 */   <-- NAME ME
};
```