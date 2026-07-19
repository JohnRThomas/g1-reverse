### cluster param_0168  (param, 9 members, 7 fields, size>=0x5c)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: z; 1/9 members are LIBRARY-class)

members (9 shown of 9):
  - arm_mpu_configure_partition_region @ 0x50b8c  as param_1  [APPLICATION]
  - abort_thread_timeout_locked @ 0x73960  as param_1  [APPLICATION]
  - dlist_unlink_node @ 0x73cdc  as param_2  [APPLICATION]
  - sched_requeue_by_prio @ 0x73d1c  as param_1  [APPLICATION]
  - unready_thread @ 0x73e88  as param_1  [LIBRARY]
  - z_sched_set_prio_and_requeue @ 0x74060  as param_1  [APPLICATION]
  - z_thread_suspend @ 0x741a4  as param_1  [APPLICATION]
  - z_abort_thread_timeout @ 0x74274  as param_1  [APPLICATION]
  - unpend_thread @ 0x742b4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0168 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=int,undefined4 */
    uint8_t    field_0xc;   /* +0xc  sz=1 rw=r types=byte */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=rw types=byte,char */
    uint8_t    field_0xe;   /* +0xe  sz=1 rw=rw types=char */
    uint8_t    _pad_0xf[0x9];   /* +0xf pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x1c[0x3c];   /* +0x1c pad */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=r types=int */
};
```