### struct k_thread  (library:k_thread)  cid=param_0168

purpose: Zephyr thread control block (struct k_thread; _thread_base embedded at offset 0) accessed by scheduler internals: qnode, pended_on, user_options/thread_state/prio, timeout node.

This object is accessed by these functions (read their fully-named source):
  - arm_mpu_configure_partition_region  (as param_1)  ->  recon/readable_sources/app/library/arm_mpu_configure_partition_region.c
  - abort_thread_timeout_locked  (as param_1)  ->  recon/readable_sources/app/g1/abort_thread_timeout_locked.c
  - dlist_unlink_node  (as param_2)  ->  recon/readable_sources/app/g1/dlist_unlink_node.c
  - sched_requeue_by_prio  (as param_1)  ->  recon/readable_sources/app/library/sched_requeue_by_prio.c
  - unready_thread  (as param_1)  ->  recon/readable_sources/app/library/unready_thread.c
  - z_sched_set_prio_and_requeue  (as param_1)  ->  recon/readable_sources/app/library/z_sched_set_prio_and_requeue.c
  - z_thread_suspend  (as param_1)  ->  recon/readable_sources/app/library/z_thread_suspend.c
  - z_abort_thread_timeout  (as param_1)  ->  recon/readable_sources/app/library/z_abort_thread_timeout.c
  - unpend_thread  (as param_1)  ->  recon/readable_sources/app/g1/unpend_thread.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct k_thread {
    void*        qnode_dlist_next;  /* +0x4  rw=r sz=4 */
    void*        pended_on;  /* +0x8  rw=rw sz=4 */
    uint8_t      user_options;  /* +0xc  rw=r sz=1 */
    uint8_t      thread_state;  /* +0xd  rw=rw sz=1 */
    uint8_t      prio;  /* +0xe  rw=rw sz=1 */
    void*        timeout_node;  /* +0x18  rw=r sz=4 */
    uint32_t     field_0x58;  /* +0x58  rw=r sz=4 */   <-- NAME ME
};
```