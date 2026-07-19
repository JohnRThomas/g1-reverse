## review group param_0181  (1 cluster(s), kinds=param)

### proposal for param_0181
struct_name: k_work_delayable | is_library: True | library_name: k_work_delayable | is_array: False | confidence: high
purpose: Zephyr delayable work item: passed to k_work_schedule/k_work_reschedule/k_work_cancel/k_work_cancel_delayable_sync and internal cancel_sync_locked/cancel_async_locked/submit_to_queue_locked, matching Zephyr's struct k_work_delayable (embeds struct k_work + timeout + queue pointer).
fields:
  0x8  uint32_t     handler_or_flags  part of embedded k_work
  0xc  uint32_t     flags  k_work flags/atomic state
  0x10  int32_t      queue_thread_ref  queue-related field
  0x28  uint32_t     timeout_dticks  write-only, timeout deadline (embedded sys_timeout)
  0x38  void *       timeout_node_next  sys_timeout dnode pointer
  0x3c  void *       queue  struct k_work_q * target queue

<ground-truth bundle for param_0181>
### cluster param_0181  (param, 11 members, 6 fields, size>=0x40)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: k,smp; 1/11 members are LIBRARY-class)

members (11 shown of 11):
  - smp_rx_remove_invalid @ 0x52760  as param_1  [APPLICATION]
  - k_work_schedule_at_ticks @ 0x531cc  as param_1  [APPLICATION]
  - reschedule_on_sys_work_q @ 0x531d8  as param_1  [APPLICATION]
  - cancel_sync_locked @ 0x72c98  as param_1  [LIBRARY]
  - submit_to_queue_locked @ 0x72cd4  as param_1  [APPLICATION]
  - k_work_cancel @ 0x72fe8  as param_1  [APPLICATION]
  - k_work_schedule @ 0x73418  as param_1  [APPLICATION]
  - k_work_reschedule @ 0x7350c  as param_1  [APPLICATION]
  - k_work_cancel_delayable_sync @ 0x735cc  as param_1  [APPLICATION]
  - smp_free_buf @ 0x80b0e  as param_2  [APPLICATION]
  - cancel_async_locked @ 0x86596  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0181 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=idx4,int,uint */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
    uint8_t    _pad_0x14[0x14];   /* +0x14 pad */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x2c[0xc];   /* +0x2c pad */
    void *     field_0x38;   /* +0x38  sz=4 rw=r types=ptr */
    void *     field_0x3c;   /* +0x3c  sz=4 rw=r types=int,ptr */
};
```
