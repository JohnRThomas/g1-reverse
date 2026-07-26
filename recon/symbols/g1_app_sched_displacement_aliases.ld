/* P4 iteration 32 -- coherent zephyr/kernel/sched.c displacement.
 *
 * sched.c was a SPLIT unit in the cohesive app link: Batch 2b adopted 20
 * upstream identities while 11 duplicate reconstruction bodies stayed retained
 * over the SAME `_kernel` object.  The iteration-32 app-core duplicate-singleton
 * sweep re-proved all 11 relocation-masked byte-identical to this link's own
 * zephyr/kernel/CMakeFiles/kernel.dir/sched.c.obj, and attributed the shipped
 * RAM word 0x2000b484 (our arena pin `g_pend_locked_thread_tmp`) to sched.c's
 * `.bss.pending_current` -- a duplicated file-static singleton that the stock
 * half of the same unit reads through its own copy.  A unit may only be
 * displaced whole, so the whole family moves and the manifest excludes all 11.
 *
 * Four of the eleven are still called by their historical recovered spelling
 * from retained Even translation units.  Each recovered spelling is bound here
 * onto the genuine upstream owner; every one of these upstream symbols has
 * GLOBAL linkage in sched.c, so the binding is exact and no body is copied.
 * The remaining seven upstream owners are translation-unit-local statics with
 * no retained referrer left after the exclusion, so they need no alias.
 *
 * GNU ld evaluates PROVIDE in script order, so this fragment carries a sort key
 * that orders BEFORE g1_app_function_aliases.ld / g1_app_veneer_aliases.ld,
 * which chain further spellings onto the names defined here
 * (`FUN_0007c0a4 = k_sleep`, `process_touch_event = mutex_unlock_syscall_handler`,
 * `FUN_0008641c = sched_thread_ready`, ...).
 */

/* 0x00074844 -> zephyr/kernel/sched.c :: z_impl_k_sleep (global) */
PROVIDE(k_sleep = z_impl_k_sleep);

/* 0x000745c8 -> zephyr/kernel/sched.c :: z_impl_k_yield (global) */
PROVIDE(mutex_unlock_syscall_handler = z_impl_k_yield);

/* 0x00074554 -> zephyr/kernel/sched.c :: z_impl_k_thread_priority_set (global) */
PROVIDE(k_thread_priority_set = z_impl_k_thread_priority_set);

/* 0x00073a78 -> zephyr/kernel/sched.c :: z_sched_start (global) */
PROVIDE(sched_thread_ready = z_sched_start);

/* 0x00073cdc -> zephyr/kernel/sched.c :: z_priq_dumb_remove (global).
 * No retained referrer remains after the exclusion; the binding is kept so a
 * later retained caller cannot silently resurrect a second body. */
PROVIDE(dlist_unlink_node = z_priq_dumb_remove);
