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

/* Iteration 21: the SAME session's request call.  FUN_0102b810 opens the
 * timeslot session with 0x01021a38, requests with 0x0102a122 and closes with
 * 0x0102a0e6, all on the one session id.  Two of the three were already the
 * library's; the third was not, and the recovered body reaches MPSL's private
 * session array through the original-image absolutes 0x210016e4 (table base)
 * and 0x210016e8 (count) via FUN_01021ac0.  Nothing in this build owns that
 * pair -- the genuine libmpsl.a keeps the table at its own layout, and NCS's
 * mpsl_init hands it `timeslot_context` through the LIBRARY
 * mpsl_timeslot_session_count_set().  Measured (iteration 21): after a
 * successful library session_open, *(uint32_t *)0x210016e4 read 0x00000001, so
 * FUN_01021ac0(0) returned 0x1, the session state was read from address 0x27
 * as 0, mpsl_timeslot_request returned -NRF_EAGAIN (-35) and the recovered
 * worker's fatal `svc 2` (K_ERR_KERNEL_OOPS) reset the SoC.  The return-code
 * set of the reconstruction (-NRF_ENOENT / -NRF_EAGAIN / -NRF_EINVAL) is
 * exactly the documented set of mpsl_timeslot_request. */
PROVIDE(FUN_0102a122 = mpsl_timeslot_request);
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

/* Iteration 19: the CPUNET subsys/bluetooth/host/hci_raw.c SINGLETON.
 *
 * FUN_0102fcec is bt_enable_raw (its three log strings, read out of
 * netcore_image.bin at runtime 0x0103dde1 / 0x0103ddfa / 0x0103de16, are
 * verbatim hci_raw.c's "No HCI driver registered" / "HCI driver open failed
 * (%d)" / "Bluetooth enabled in RAW mode", in that order, and it stores its
 * argument then calls drv->open at +12 and returns -ENODEV on a null driver).
 * hci_raw.c is already the linked owner of bt_send and bt_recv, and its
 * `raw_rx` file-static is written ONLY by bt_enable_raw.  The retained
 * reconstruction wrote its own original-image pin instead, so the stock
 * raw_rx stayed NULL, bt_recv() had nowhere to queue and the app core's first
 * HCI Reset was never answered.  Evidence:
 * recon/ownership/net_hci_raw_singleton_adoption.json. */
PROVIDE(FUN_0102fcec = bt_enable_raw);

/* Iteration 19: FUN_0102fc30 is bt_buf_get_tx from the same singleton unit.
 * It selects hci_raw.c's FILE-STATIC hci_cmd_pool / hci_acl_pool by their
 * original absolute addresses (0x210009c8 / 0x21000994).  Those statics are
 * not linkable, and in the cohesive link 0x210009c8 lands inside the stock
 * hci_rx_pool, so every HCI command allocation corrupted the pool that
 * bt_buf_get_evt() uses -- measured as "<err> bt_sdc_hci_driver: No event
 * buffer available" the moment the app core's HCI Reset arrived.  Evidence:
 * recon/ownership/net_hci_raw_bt_buf_get_tx_adoption.json. */
PROVIDE(FUN_0102fc30 = bt_buf_get_tx);

/* Iteration 19: FUN_0102e974 is z_isr_install (its __ASSERT prints
 * "WEST_TOPDIR/zephyr/arch/common/sw_isr_common.c":85, which is exactly
 * `__ASSERT(!irq_is_enabled(irq), ...)`, and its guard callee reads NVIC->ISER).
 * It addressed _sw_isr_table through the ORIGINAL image base 0x2100076c, which
 * in the cohesive link falls 0x64 bytes INSIDE the linker-generated table, so
 * every dynamically installed ISR overwrote entries 12/13 instead of its own.
 * Evidence: recon/ownership/net_sw_isr_common_adoption.json. */
PROVIDE(FUN_0102e974 = z_isr_install);

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

/* Iteration 26: the CPUNET nrf/subsys/bluetooth/controller/hci_ecdh.c
 * SINGLETON.  FUN_01032680 is hci_ecdh_init: it k_poll_signal_init()s one
 * signal, k_thread_create()s one 0x388-byte "BT CTLR ECDH" worker at priority
 * 10 and k_thread_name_set()s it -- the stock body exactly.  The stock unit is
 * unconditionally linked here (ecdh_thread 0x01034fc4, ecdh_cmd_process
 * 0x01034eb4, hci_ecdh_init 0x01035004, ecdh_thread_stack 0x388 B,
 * ecdh_signal, log_const_bt_sdc_ecdh), so retaining the reconstruction would
 * start a SECOND ECDH thread on a second signal -- and start it at
 * `rodata_1032e41` = 0x01032e41, an ORIGINAL-IMAGE code address (runtime ->
 * analysis 0x01032640 | 1 = ecdh_thread).  Identification comes from the
 * literal pools of the gap functions it reaches: 0x01032530 and 0x01032488
 * both hold the 32-byte Bluetooth debug public key (analysis 0x0103db93) and
 * the "Unknown command" / "BT CTLR ECDH" strings (analysis 0x0103db76), and
 * 0x01032440 is sys_memcpy_swap specialised to length 0x20.  Evidence:
 * recon/ownership/net_hci_ecdh_singleton_adoption.json. */
PROVIDE(FUN_01032680 = hci_ecdh_init);

/* Iteration 28, BATCH 1 -- nrfx_timer.c is a STOCK, UNMODIFIED unit and it owns
 * the singleton control block `m_cb` (12 B, one enabled instance = TIMER2).
 * All six nrfx_timer.c functions the shipped image contains are
 * relocation-masked byte-identical to the stock sections over 472
 * distinguishing bytes (evidence:
 * recon/ownership/net_nrfx_timer_singleton_adoption.json).  The
 * reconstructions reached m_cb through the pin `g_net_gpiote_evt_handler_table`
 * (shipped 0x21004af8 -- a mis-name; the object is nrfx's timer control block),
 * which iteration 26 relocated into g1_net_ram_blk_21004ae8 + 0x10.  MEASURED
 * (iteration 28, Renode watchpoint): nrfx_timer_init succeeded and wrote
 * state = 1, and memcpy from FUN_0102b3f0+0x66 -- copying into
 * g_net_ctrl_status_byte, 0xb1 bytes away in the COMPRESSED block space but far
 * away in the shipped space -- zeroed it again, so nrfx_timer_disable's
 * NRFX_ASSERT (nrfx_timer.c:202) fired and k_oops reset the SoC at ~5.8 s.
 * Displacing the unit takes m_cb out of the relocation-block space entirely.
 * It also repairs a transcription defect the parity harness cannot see: the
 * recovered timer_configure carried base frequency 0x000f4240 (1 MHz) where the
 * shipped bytes carry 0x00f42400 (16 MHz), so the ESB timer was clocked 16x too
 * fast. */
PROVIDE(FUN_01034fa8 = nrfx_timer_init);
PROVIDE(FUN_01035028 = nrfx_timer_disable);
PROVIDE(FUN_01035068 = nrfx_timer_uninit);
PROVIDE(FUN_010350a4 = nrfx_timer_2_irq_handler);
PROVIDE(FUN_0103a9dc = nrfx_timer_compare);
/* FUN_01034f24 = timer_configure is file-local in the stock object, so it
 * cannot be named by a PROVIDE.  Its only recovered referrer, FUN_01034fa8, is
 * displaced in this same batch, so the exclusion leaves no undefined symbol. */

/* Iteration 28, BATCH 2 -- esb_dppi.c is a STOCK, UNMODIFIED unit and it owns
 * seven ESB DPPI channel/group singletons (shipped 0x2100645a..0x21006460).
 * All twelve esb_dppi.c functions the shipped image contains are
 * relocation-masked byte-identical to the stock sections over 996
 * distinguishing bytes, in the object's own section order, over the contiguous
 * VA run 0x01033b18..0x01033ff8 (evidence:
 * recon/ownership/net_esb_dppi_singleton_adoption.json).  The sweep's
 * cross-reference proves no RETAINED reconstruction reaches that state -- the
 * vendored esb.c only calls the esb_ppi_* accessors -- so the displacement is
 * total for the unit and leaves no second copy.  Note the CONTRAST with esb.c
 * in the same archive: only 32 of its 53 sections are byte-identical, so esb.c
 * is genuinely vendored/reconfigured by Even and its reconstruction is KEPT. */
PROVIDE(FUN_01033b18 = esb_ppi_for_txrx_set);
PROVIDE(FUN_01033bf0 = esb_ppi_for_txrx_clear);
PROVIDE(FUN_01033c74 = esb_ppi_for_fem_set);
PROVIDE(FUN_01033ca4 = esb_ppi_for_fem_clear);
PROVIDE(FUN_01033cd0 = esb_ppi_for_retransmission_set);
PROVIDE(FUN_01033d20 = esb_ppi_for_retransmission_clear);
PROVIDE(FUN_01033d54 = esb_ppi_for_wait_for_ack_set);
PROVIDE(FUN_01033da0 = esb_ppi_for_wait_for_ack_clear);
PROVIDE(FUN_01033de4 = esb_ppi_radio_disabled_get);
PROVIDE(FUN_01033df0 = esb_ppi_init);
PROVIDE(FUN_01033ee4 = esb_ppi_disable_all);
PROVIDE(FUN_01033f38 = esb_ppi_deinit);

/* Iteration 28, BATCH 3 -- nrfx_ipc.c.  The stock unit is ALREADY linked
 * unconditionally in this build and owns the singleton IPC control block m_cb;
 * the two reconstructions read a private relocation block bound from the pin
 * `g_sdc_radio_context_area` (shipped 0x21004aec -- another mis-name; the
 * object is nrfx's IPC control block).  All five nrfx_ipc.c functions the
 * shipped image contains are relocation-masked byte-identical to the stock
 * sections and tile the 408-byte run 0x01034d8c..0x01034f24 exactly, so the
 * unit is stock and unmodified (evidence:
 * recon/ownership/net_nrfx_ipc_singleton_adoption.json).  NOTE: iteration 27
 * named this file as the source of the ~5.8 s assert; that identification was
 * WRONG -- 0x0103e73b is the nrfx_TIMER.c path string (the nrfx_ipc.c string
 * ends at 0x0103e73a) and nrfx_timer.c:202 is nrfx_timer_disable's
 * NRFX_ASSERT.  The real nrfx_ipc hazard is this one, and it is latent: both
 * reconstructions are already --gc-sections'd out of the link. */
PROVIDE(FUN_01034d8c = nrfx_ipc_init);
PROVIDE(FUN_01034dd8 = nrfx_ipc_config_load);
