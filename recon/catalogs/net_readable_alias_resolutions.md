# CPUNET readable alias resolutions

Every retained alias below is backed by a canonical declaration that
preserves its raw firmware VA. SDK owners require an existing manifest
exclusion; the private controller row remains report-only.

## Retained-body aliases

| Symbol | Target | VA |
|---|---|---:|
| `assert_post_action` | `FUN_01039bb0` | 0x01039bb0 |
| `assert_report` | `assert_print` | 0x01039bbe |
| `controller_connection_config_get` | `FUN_010282a6` | 0x010282a6 |
| `controller_handle_lookup` | `FUN_0100cfc0` | 0x0100cfc0 |
| `controller_object_get` | `FUN_010282a2` | 0x010282a2 |
| `k_heap_aligned_alloc` | `FUN_01035d18` | 0x01035d18 |
| `net_buf_free_get` | `FUN_01036774` | 0x01036774 |
| `prepare_thread_swap` | `FUN_01037398` | 0x01037398 |
| `ready_remove` | `FUN_0103735c` | 0x0103735c |
| `spin_lock` | `FUN_01036144` | 0x01036144 |
| `spin_unlock` | `FUN_01036128` | 0x01036128 |
| `spin_validate` | `FUN_0103610c` | 0x0103610c |
| `spinlock_acquire` | `FUN_01036144` | 0x01036144 |
| `spinlock_release` | `FUN_01036128` | 0x01036128 |
| `spinlock_validate` | `FUN_0103610c` | 0x0103610c |
| `swap_current` | `FUN_01036f24` | 0x01036f24 |
| `sys_heap_free` | `FUN_0102c470` | 0x0102c470 |
| `thread_can_swap` | `FUN_01036e90` | 0x01036e90 |
| `thread_ready` | `FUN_0103705c` | 0x0103705c |
| `thread_unpend` | `FUN_01037850` | 0x01037850 |
| `timeout_abort` | `FUN_010380d8` | 0x010380d8 |
| `trace_sched_unlock` | `FUN_0103b2b4` | 0x0103b2b4 |
| `update_cache` | `FUN_01036f74` | 0x01036f74 |
| `work_submit_to_queue` | `FUN_01036c2c` | 0x01036c2c |
| `z_heap_aligned_alloc` | `FUN_01038958` | 0x01038958 |
| `z_reschedule` | `FUN_01037130` | 0x01037130 |
| `alloc_chunk` | `FUN_01039874` | 0x01039874 |
| `assert_panic` | `FUN_01039bb0` | 0x01039bb0 |
| `atomic_inc` | `FUN_0103a294` | 0x0103a294 |
| `bytes_to_chunksz` | `FUN_010397c0` | 0x010397c0 |
| `chunk_size` | `FUN_01039768` | 0x01039768 |
| `free_list_add` | `FUN_01039972` | 0x01039972 |
| `k_sem_give` | `FUN_01036824` | 0x01036824 |
| `k_timer_start` | `FUN_01038448` | 0x01038448 |
| `log_process` | `FUN_0102df2c` | 0x0102df2c |
| `queue_insert` | `FUN_01036660` | 0x01036660 |
| `set_chunk_used` | `FUN_01039774` | 0x01039774 |
| `spin_lock_acquire` | `FUN_01036144` | 0x01036144 |
| `spin_lock_valid` | `FUN_0103610c` | 0x0103610c |
| `spin_unlock_valid` | `FUN_01036128` | 0x01036128 |
| `split_chunks` | `FUN_010398e8` | 0x010398e8 |
| `strlen` | `FUN_0102a268` | 0x0102a268 |

## Manifest-approved SDK owners

| Readable spelling | Upstream owner | VA |
|---|---|---:|
| `net_buf_destroy_from_pool` | `k_queue_prepend` | 0x0103b210 |
| `scheduler_priority_compare` | `z_sched_prio_cmp` | 0x0103b28a |
| `scheduler_reschedule_restore` | `z_reschedule_irqlock` | 0x0103b29c |
| `sys_timepoint_calc` | `sys_timepoint_calc` | 0x0103b304 |
| `sys_timepoint_timeout` | `sys_timepoint_timeout` | 0x0103b34c |
| `z_unpend_all` | `z_unpend_all` | 0x0103b2d0 |

## Deliberately unresolved

| Symbol | VA | Reason |
|---|---:|---|
| `controller_default_bounds_build` | 0x010282fc | exact identity: 126-byte FUN_010282fc; unique private SDC archive match remains report-only |
| `controller_timing_defaults_apply` | 0x0101e1e4 | exact unique private SDC archive match remains report-only |
