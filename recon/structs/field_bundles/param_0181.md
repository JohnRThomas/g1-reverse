### struct k_work_delayable  (library:k_work_delayable)  cid=param_0181

purpose: Zephyr delayable work item passed to k_work_schedule/reschedule/cancel and internal cancel/submit helpers (embeds k_work + _timeout + queue ptr).

This object is accessed by these functions (read their fully-named source):
  - smp_rx_remove_invalid  (as param_1)  ->  recon/readable_sources/app/library/smp_rx_remove_invalid.c
  - k_work_schedule_at_ticks  (as param_1)  ->  recon/readable_sources/app/library/k_work_schedule_at_ticks.c
  - reschedule_on_sys_work_q  (as param_1)  ->  recon/readable_sources/app/g1/reschedule_on_sys_work_q.c
  - cancel_sync_locked  (as param_1)  ->  recon/readable_sources/app/library/cancel_sync_locked.c
  - submit_to_queue_locked  (as param_1)  ->  recon/readable_sources/app/library/submit_to_queue_locked.c
  - k_work_cancel  (as param_1)  ->  recon/readable_sources/app/library/k_work_cancel.c
  - k_work_schedule  (as param_1)  ->  recon/readable_sources/app/library/k_work_schedule.c
  - k_work_reschedule  (as param_1)  ->  recon/readable_sources/app/library/k_work_reschedule.c
  - k_work_cancel_delayable_sync  (as param_1)  ->  recon/readable_sources/app/library/k_work_cancel_delayable_sync.c
  - smp_free_buf  (as param_2)  ->  recon/readable_sources/app/library/smp_free_buf.c
  - cancel_async_locked  (as param_1)  ->  recon/readable_sources/app/library/cancel_async_locked.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct k_work_delayable {
    void*        queue;  /* +0x8  rw=r sz=4 */
    uint32_t     flags;  /* +0xc  rw=rw sz=4 */
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x28;  /* +0x28  rw=w sz=4 */   <-- NAME ME
    void*        field_0x38;  /* +0x38  rw=r sz=4 */   <-- NAME ME
    void*        field_0x3c;  /* +0x3c  rw=r sz=4 */   <-- NAME ME
};
```