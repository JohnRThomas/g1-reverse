/* Cohesive CPUNET call-identity bridge for exact pinned NCS 2.5.1 owners.
 *
 * These aliases do not pin code to original firmware addresses.  They map the
 * reversible raw spellings left in retained callers to public symbols emitted
 * by the exact Zephyr/toolchain source owner selected by prj.conf.  The two
 * file-static scheduler helpers use their public Zephyr wrappers; both wrappers
 * preserve the required operation under this UP/SCHED_DUMB configuration.
 */
PROVIDE(FUN_0100823c = __aeabi_uldivmod);
PROVIDE(FUN_0102a244 = strcmp);
PROVIDE(FUN_0102def4 = z_log_msg_alloc);
PROVIDE(FUN_0102e000 = z_impl_log_panic);
PROVIDE(FUN_0102e9bc = arch_cpu_idle);
PROVIDE(FUN_0103175c = sys_clock_set_timeout);
PROVIDE(FUN_01039722 = printk);
PROVIDE(FUN_01036198 = z_impl_k_msgq_put);
PROVIDE(FUN_010362d0 = z_impl_k_msgq_get);
PROVIDE(FUN_0102a0e6 = mpsl_timeslot_session_close);
/* Iteration 9: the product timeslot worker's session-open call.  The shipped
 * call site (0x0102b84a..0x0102b850) passes the signal callback in r0 and a
 * one-byte session-id out parameter in r1, and the reconstruction's return set
 * (-22 / -12) matches mpsl_timeslot.h.  The reconstruction additionally waited
 * on MPSL's private clock state through original-image absolute RAM addresses
 * that this build never initialises, so it spun forever on CLOCK.LFCLKSTAT even
 * though the low-frequency clock was running. */
PROVIDE(FUN_01021a38 = mpsl_timeslot_session_open);
PROVIDE(FUN_0103b300 = thunk_FUN_01038284);
PROVIDE(FUN_0103b224 = z_impl_k_sem_init);
PROVIDE(FUN_01036fcc = z_ready_thread);
PROVIDE(FUN_0103705c = z_ready_thread);
PROVIDE(FUN_01037130 = z_reschedule);
PROVIDE(FUN_0103719c = z_sched_start);
PROVIDE(FUN_0103721c = k_sched_lock);
PROVIDE(FUN_010372b4 = k_sched_unlock);
PROVIDE(FUN_01037438 = z_time_slice);
PROVIDE(FUN_010375b8 = z_pend_curr);
PROVIDE(FUN_01037670 = z_set_prio);
PROVIDE(FUN_01037814 = z_unpend_thread_no_timeout);
PROVIDE(FUN_010379d4 = z_unpend_first_thread);
PROVIDE(FUN_01037c64 = z_impl_k_sleep);
PROVIDE(FUN_0103a2a6 = z_log_vprintk);
PROVIDE(FUN_0103a2c8 = z_log_get_tag);
PROVIDE(FUN_0103b1fa = k_queue_append);
PROVIDE(FUN_0103b210 = k_queue_prepend);
PROVIDE(FUN_0103b522 = k_free);
PROVIDE(FUN_0103b530 = k_malloc);
PROVIDE(FUN_0103b53a = __memcpy_chk);
PROVIDE(FUN_0103b5c4 = strnlen);
PROVIDE(FUN_0103b614 = __aeabi_memcpy4);
PROVIDE(FUN_0103b62e = memset);

/* Iteration 18: the CPUNET kernel/timeout.c SINGLETON.
 *
 * `kernel/timeout.c` owns exactly one `timeout_list` / `curr_tick` /
 * `announce_remaining` / `timeout_lock`, and the stock unit is unconditionally
 * linked here (sys_clock_announce is reached from the stock `rtc_nrf_isr`).
 * The reconstruction of the same unit was ALSO retained, and it addressed its
 * private state through raw original-image RAM pins:
 *
 *     timeout_list        0x21000750  -> lands inside `_sw_isr_table`
 *     curr_tick           0x210044f0  -> lands inside `sdc_mempool`
 *     announce_remaining  0x21004b6c  -> lands inside `sdc_mempool`
 *     last_count          0x21002b80  -> lands inside `sdc_mempool`   (rtc)
 *
 * so the recovered z_add_timeout walked the software ISR table as if it were a
 * dlist of `struct _timeout` and wrote through those wild links.  Measured
 * with a Renode watchpoint (iteration 18 §18.1): FUN_01037f8c+0x68 and +0xfa
 * wrote 0x21001d30 and 0x21001e14, i.e. `backend_data_0`'s rpmsg endpoint
 * list, which is why `rpmsg_get_endpoint` never terminated and the HCI
 * endpoint never bound.  Two lists also mean a recovered caller's timeout is
 * never announced by the stock ISR.
 *
 * The reconstructions are therefore excluded (adoption_manifest.json, evidence
 * recon/ownership/net_kernel_timeout_singleton_adoption.json) and every raw
 * caller identity is mapped onto the single stock owner. */
PROVIDE(FUN_010317c0 = sys_clock_elapsed);
PROVIDE(FUN_01037f8c = z_add_timeout);
PROVIDE(FUN_010380d8 = z_abort_timeout);
PROVIDE(FUN_0103814c = sys_clock_announce);
PROVIDE(FUN_01038284 = sys_clock_tick_get);

PROVIDE(assert_report = assert_print);
PROVIDE(controller_connection_config_get = FUN_010282a6);
PROVIDE(controller_handle_lookup = FUN_0100cfc0);
PROVIDE(controller_object_get = FUN_010282a2);
PROVIDE(net_buf_destroy_from_pool = k_queue_prepend);
PROVIDE(net_buf_free_get = z_impl_k_queue_get);
PROVIDE(spinlock_validate = z_spin_lock_valid);
PROVIDE(spinlock_acquire = z_spin_lock_set_owner);
PROVIDE(spinlock_release = z_spin_unlock_valid);

/* The recovered product main emits its reversible raw identity.  Assign the
 * Zephyr ABI entry directly, avoiding a synthetic wrapper function. */
main = FUN_0102a720;
