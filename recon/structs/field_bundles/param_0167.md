### struct kernel_obj_shared_param  (library:k_thread (approx; mixed))  cid=param_0167

purpose: Heterogeneous cluster: one param_1 slot shared by many distinct Zephyr kernel objects (k_mutex/k_sem/k_msgq wait-q fields at low offsets; k_thread stack/entry fields at 0x50-0xd4 via arch_new_thread/z_setup_new_thread).

This object is accessed by these functions (read their fully-named source):
  - arch_new_thread  (as param_1)  ->  recon/readable_sources/app/library/arch_new_thread.c
  - bt_gatt_discover  (as param_1)  ->  recon/readable_sources/app/library/bt_gatt_discover.c
  - bt_gatt_write  (as param_1)  ->  recon/readable_sources/app/library/bt_gatt_write.c
  - k_mem_slab_alloc  (as param_1)  ->  recon/readable_sources/app/library/k_mem_slab_alloc.c
  - z_setup_new_thread  (as param_1)  ->  recon/readable_sources/app/library/z_setup_new_thread.c
  - k_msgq_put  (as param_1)  ->  recon/readable_sources/app/library/k_msgq_put.c
  - k_msgq_get  (as param_1)  ->  recon/readable_sources/app/library/k_msgq_get.c
  - k_mutex_lock  (as param_1)  ->  recon/readable_sources/app/library/k_mutex_lock.c
  - k_mutex_unlock  (as param_1)  ->  recon/readable_sources/app/library/k_mutex_unlock.c
  - k_sem_give  (as param_1)  ->  recon/readable_sources/app/library/k_sem_give.c
  - z_impl_k_sem_take  (as param_1)  ->  recon/readable_sources/app/library/z_impl_k_sem_take.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct kernel_obj_shared_param {
    uint32_t     field_0x8;  /* +0x8  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=rw sz=1,4 */   <-- NAME ME
    uint8_t      field_0xd;  /* +0xd  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0xe;  /* +0xe  rw=w sz=1 */   <-- NAME ME
    uint8_t      field_0xf;  /* +0xf  rw=w sz=1 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    void *       field_0x18;  /* +0x18  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x24;  /* +0x24  rw=rw sz=4 */   <-- NAME ME
    uint32_t     thread_field_0x50;  /* +0x50  rw=w sz=4 */
    uint32_t     thread_field_0x54;  /* +0x54  rw=w sz=4 */
    uint32_t     thread_field_0x58;  /* +0x58  rw=w sz=4 */
    uint32_t     thread_field_0x5c;  /* +0x5c  rw=w sz=4 */
    uint8_t      thread_field_0x70;  /* +0x70  rw=w sz=1 */
    uint32_t     thread_field_0x74;  /* +0x74  rw=w sz=4 */
    uint32_t     thread_field_0x7c;  /* +0x7c  rw=w sz=4 */
    uint32_t     thread_field_0x80;  /* +0x80  rw=w sz=4 */
    uint32_t     thread_field_0x84;  /* +0x84  rw=w sz=4 */
    uint32_t     thread_field_0x88;  /* +0x88  rw=w sz=4 */
    uint32_t     thread_field_0x8c;  /* +0x8c  rw=w sz=4 */
    uint32_t     thread_field_0xd4;  /* +0xd4  rw=w sz=4 */
};
```