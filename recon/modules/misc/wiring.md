# misc — RTOS object wiring

RTOS objects that the `misc` group **defines**, read out of its proven init
functions. `misc` defines **no threads** (no `k_thread_create`/`K_THREAD_DEFINE`
appears in any misc function) and **no work queues**. It defines message queues
(dynamically allocated) and one counting semaphore. Note that `misc` also
*contains* the Zephyr kernel primitive implementations themselves
(`k_msgq_init` 0x86420, `z_impl_k_sem_init` 0x86534, `k_timer_init` 0x86726,
`k_work_init` 0x72e50, `k_msgq_cleanup` 0x86480, `k_fifo_peek_head_impl` 0x8652c)
— those are the machinery, not app object definitions, and are listed here only
to explain why the classifier pooled them.

## Message queues (dynamic, via `z_impl_k_msgq_alloc_init(msgq, msg_size, max_msgs)`)

| Object (global) | Address | msg_size | max_msgs | Defined in |
|---|---|---|---|---|
| `g_debug_msg_pipe` | 0x2000751c | 200 (0xC8) | 20 (0x14) | `debug_log_queue_init` @ 0x19bd0 |
| `g_file_msg_pipe`  | 0x200079a0 | 201 (0xC9) | 30 (0x1E) | `file_subsystem_queue_init` @ 0x234e8 |

Both call `z_impl_k_msgq_alloc_init` (heap-backed ring buffer) and set a
DEBUG_PRINT status message on the return code. Equivalent static form:

    /* debug_log_queue_init @ 0x19bd0 */
    K_MSGQ_DEFINE(g_debug_msg_pipe, /*msg_size=*/200, /*max_msgs=*/20, /*align=*/4);
    /* file_subsystem_queue_init @ 0x234e8 */
    K_MSGQ_DEFINE(g_file_msg_pipe,  /*msg_size=*/201, /*max_msgs=*/30, /*align=*/4);

(They are dynamically allocated in the firmware, so no compile-time alignment is
pinned; 4-byte alignment is the Zephyr default assumption.)

## Semaphores (via `z_impl_k_sem_init(sem, initial, limit)`)

| Object (global) | Address | initial | limit | Defined in |
|---|---|---|---|---|
| `g_some_module_sem` | 0x20007b1c | 0 | 5 | `some_module_sem_init` @ 0x2953c |

    /* some_module_sem_init @ 0x2953c */
    z_impl_k_sem_init(0x20007b1c, /*initial_count=*/0, /*limit=*/5);
    /* on success sets g_some_module_init_done_flag (0x20018d8a) = 1 */
    /* K_SEM_DEFINE(g_some_module_sem, 0, 5); */

### Generic semaphore-init wrapper (not an object definition)
`FUN_0007c030` @ 0x7c030 is a thin forwarder:
`z_impl_k_sem_init(param_1, 0, param_2)` — initializes a caller-supplied
semaphore to count 0 with a caller-supplied limit. It defines no fixed object;
callers pass the sem pointer and limit.

## Related init-flag pair (same 0x20007b00 region)
`FUN_0002a4c0` @ 0x2a4c0 guards on `g_some_module_init_done_flag`-style byte at
0x20018d88 and, when set, calls `thunk_FUN_00072880((void*)0x20007b00)` — i.e. a
give/take-style operation on an object at 0x20007b00 adjacent to
`g_some_module_sem`. The object's k_*_init was not located within the misc set
(likely defined in another module); recorded here as a loose end for the wiring
reconstruction.
