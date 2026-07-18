/*
 * app_objects.c  --  Reconciled RTOS kernel-object wiring for the Even G1
 *                    app-core firmware (link base 0xC200).
 *
 * SOURCE OF TRUTH: every entry below is transcribed from a parity-PROVEN body
 * cited by `recon/modules/<mod>/wiring.md`, which in turn cites
 * recon/verified/src*/ and recon/named/. Addresses are SRAM control-block
 * addresses; the "@fn" citation is the init/spawn function the object is
 * created in.
 *
 * Zephyr primitive wrappers (Ghidra FUN_ names) used across the tree:
 *   k_thread_create        = FUN_00071eac
 *   k_msgq_init            = FUN_00086420 / FUN_00086448 (== z_impl_k_msgq_alloc_init)
 *   z_impl_k_sem_init      = FUN_00086534
 *   k_timer_init           = FUN_00086726
 *   k_work_init_delayable  = FUN_000732d4
 *   k_mutex init/lock      = FUN_000723b8 (lock) / FUN_00072558 (unlock)
 *   k_sem_give-style wake  = FUN_00072880
 *
 * Where a proven body did not expose a parameter it is marked UNRECOVERED and
 * MUST NOT be guessed downstream. Objects created dynamically at runtime are
 * shown as their static K_*_DEFINE equivalent with a note.
 *
 * DEDUP: g_uid_pipe and g_file_msg_pipe each appear in two module wiring docs
 * (audio+ipc_core, audio+misc); listed once, at their defining init fn.
 */

/* ======================================================================= *
 *  MESSAGE QUEUES                                                          *
 * ======================================================================= */

/* --- ancs_notify ------------------------------------------------------- */
/* @ init_msgq_ancs 0x18b6c : k_msgq_init(0x20006a6c, 0x1b4, 10)           */
K_MSGQ_DEFINE(g_ancs_msgq,        /*msg_size=*/436,  /*max_msgs=*/10, 4);  /* 0x20006a6c */

/* --- audio ------------------------------------------------------------- */
/* @ init_dmic_msgq 0x2ebd8 : k_msgq_alloc_init(0x20007b7c, 200, 8) [dyn]  */
K_MSGQ_DEFINE(g_dmic_msgq,        /*msg_size=*/200,  /*max_msgs=*/8,  4);  /* 0x20007b7c */
/* Static initializer copied from ROM 0x000fa5f4: 204-byte record x 18.     */
/* The 204-byte size also equals sizeof(audio_cache_record) in              */
/* sendAudioStram2Cache 0x2f6b0; +0x24 used-count guard proves depth 18.     */
K_MSGQ_DEFINE(g_audio_msgq,       /*msg_size=*/204,  /*max_msgs=*/18, 4);  /* 0x20003890 */

/* --- ipc_core (shared with audio) -------------------------------------- */
/* @ init_msgq_uid 0x18e04 : k_msgq_alloc_init(0x20006a38, 8, 10) [dyn]     */
K_MSGQ_DEFINE(g_uid_pipe,         /*msg_size=*/8,    /*max_msgs=*/10, 4);  /* 0x20006a38 */

/* --- misc (shared with audio: file_subsystem_queue_init) --------------- */
/* @ file_subsystem_queue_init 0x234e8 : k_msgq_alloc_init(0x200079a0,201,30) [dyn] */
K_MSGQ_DEFINE(g_file_msg_pipe,    /*msg_size=*/201,  /*max_msgs=*/30, 4);  /* 0x200079a0 */
/* @ debug_log_queue_init 0x19bd0 : k_msgq_alloc_init(0x2000751c,200,20) [dyn] */
K_MSGQ_DEFINE(g_debug_msg_pipe,   /*msg_size=*/200,  /*max_msgs=*/20, 4);  /* 0x2000751c */

/* --- display ----------------------------------------------------------- */
/* Static ROM initializer 0x000fa628: msg_size=24, max_msgs=30, buffer       */
/* [0x2004ca90,0x2004cd60). Producers and consumer independently prove 24.  */
K_MSGQ_DEFINE(g_display_msgq,     /*msg_size=*/24,   /*max_msgs=*/30, 4);  /* 0x200038c4 */

/* --- flash_store ------------------------------------------------------- */
/* Static ROM initializers copied at reset. The queue API copies the exact   */
/* six-byte slot even where a consumer's local scratch object is larger.     */
/* 0x000fa6f8: buffer [0x20045320,0x2004533e), 6 bytes x 5.                  */
K_MSGQ_DEFINE(g_flash_store_cmd_msgq, /*msg_size=*/6, /*max_msgs=*/5, 4); /* 0x20003994 */
/* 0x000fa6c4: buffer [0x20045340,0x200453b8), 6 bytes x 20.                 */
K_MSGQ_DEFINE(g_quicknote_flash_msgq, /*msg_size=*/6, /*max_msgs=*/20, 4); /* 0x20003960 */


/* ======================================================================= *
 *  THREADS  (all via k_thread_create = FUN_00071eac; prio signed, <0 coop) *
 * ======================================================================= */

/* --- ancs_notify ------------------------------------------------------- */
/* @ start_ancs_work_thread 0x198cc. Self-respawns from ancs_main 0x19950.  */
/* Guard: get_device_info()[0]==2 (iOS) && !is_battery_critical().          */
K_THREAD_DEFINE(ancs_thread, /*stack=*/0x1400 /*5120*/,
                /*entry=*/0x19950 /*ancs_main*/, /*arg=*/runtime_ancs_conn, 0, 0,
                /*prio=*/-11, 0, 0);
                /* tcb=0x20003c50  stack_base=0x2001d568 */

/* --- flash_store / display co-spawn ------------------------------------ */
/* @ spawn_flash_ops_and_brightness_threads 0x23a54 (a.k.a. FUN_00023a54;   */
/*   cited by flash_store AND display AND ble_proto #1/#2). Two threads:     */
K_THREAD_DEFINE(flash_ops_thread, /*stack=*/0x800 /*2048*/,
                /*entry=*/0x23480, /*arg=*/device_context, 0, 0, /*prio=*/-12, 0, 0);
                /* tcb=0x20003e38  stack_base=0x20021968 */
K_THREAD_DEFINE(brightness_thread, /*stack=*/0x1400 /*5120*/,
                /*entry=*/0x23844, /*arg=*/device_context, 0, 0, /*prio=*/-11, 0, 0);
                /* tcb=0x20003f10  stack_base=0x20022168 */

/* --- flash_store projector/settings thread ----------------------------- */
/* @ FUN_0002201c 0x2201c (settings/projector init). Also inits g_proj dlist */
/* 0x20007574 and k_timer 0x20003d28 (below).                                */
K_THREAD_DEFINE(projector_settings_thread, /*stack=*/0x3000 /*12288*/,
                /*entry=*/0x21da8, /*arg=*/device_context_plus_0x77c, 0, 0, /*prio=*/-15, 0, 0);
                /* tcb=0x20003d60  stack_base=0x2001e968 */

/* --- ble_proto (spawn tree rooted at run_main_dispatch_thread 0x2a65c) --- */
/* #1/#2 == flash_ops/brightness above (same 0x23a54). #3..#6 below.         */
K_THREAD_DEFINE(ble_worker_3, /*stack=*/0xc00 /*3072*/,
                /*entry=*/0x32420, /*arg=*/NULL, 0, 0, /*prio=*/-12, 0, 0);
                /* @ FUN_00032fe8 0x32fe8; tcb=0x20004870 stack=0x20027a68   */
                /* guard FUN_00032ee4()!=0; sets flag 0x20019ef1=1 on success */
K_THREAD_DEFINE(ble_worker_4, /*stack=*/0x400 /*1024*/,
                /*entry=*/0x324bc, /*arg=*/NULL, 0, 0, /*prio=*/-12, 0, 0);
                /* @ FUN_0003304c 0x3304c; tcb=0x20004798 stack=0x20027668   */
K_THREAD_DEFINE(ble_worker_5, /*stack=*/0x800 /*2048*/,
                /*entry=*/0x47c48, /*arg=*/device_context, 0, 0, /*prio=*/-12, 0, 0);
                /* @ FUN_00047ad0 0x47ad0; tcb=0x20004c08 stack=0x20028668   */
                /* guard mode byte==1; tid stored @0x2000a090                 */

/* --- display dispatch / reflash worker (== ble_proto #6) --------------- */
/* @ FUN_00049638 0x49638 (called from app-init FUN_0002a65c). Drains        */
/* g_display_msgq 0x200038c4. tid -> g_display_thread_id 0x2000a09c.         */
/* stack_size/prio: from ble_proto proven body = 0x1400 / -14.               */
K_THREAD_DEFINE(display_dispatch_thread, /*stack=*/0x1400 /*5120*/,
                /*entry=*/0x49090, /*arg=*/device_context, 0, 0, /*prio=*/-14, 0, 0);
                /* tcb=0x20004d18  stack_base=0x20028e68 */

/* --- Runtime pool created by run_main_dispatch_thread 0x2a65c. The body is *
 * CFG-verified and exposes every stack size, priority and arg0 exactly.       *
 * All arg0 values below are device_context except the explicit NULL row.      *
 * Conditional rows share a TCB/stack and are mutually exclusive.              *
 * tcb 0x200046b8 stack 0x20026a68 size 0xc00 prio -10 entry 0x2a8d8 or 0x2685c
 * tcb 0x200041a8 stack 0x20024868 size 0x400 prio -10 entry 0x286f8
 * tcb 0x200040d0 stack 0x20023c68 size 0xc00 prio -9  entry 0x2a4f4 arg0=NULL
 * tcb 0x200045e0 stack 0x20026268 size 0x800 prio -13 entry 0x28bec
 * tcb 0x20004508 stack 0x20025a68 size 0x800 prio -12 entry 0x2692c
 * tcb 0x20004430 stack 0x20025468 size 0x600 prio -11 entry 0x27cfc (mode 2)
 * tcb 0x20004358 stack 0x20025068 size 0x400 prio -14 entry 0x2a0d8 or 0x28a1c
 * tcb 0x20004280 stack 0x20024c68 size 0x400 prio -13 entry 0x2955c.            */


/* ======================================================================= *
 *  SEMAPHORES  (z_impl_k_sem_init = FUN_00086534)                          *
 * ======================================================================= */

/* --- flash_store / display / ble_proto (all cite 0x23a54) -------------- */
/* z_impl_k_sem_init(0x200079e4, 0, 0x14). Exported symbol name in the       */
/* binary is "g_app_language_msgq" but it IS a counting semaphore. Signalled */
/* (k_sem_give via FUN_00072880) by many producers to wake flash_ops_thread. */
K_SEM_DEFINE(g_app_language_sem,  /*initial=*/0, /*limit=*/20);            /* 0x200079e4 */

/* --- misc / touch_key -------------------------------------------------- */
/* @ some_module_sem_init 0x2953c : z_impl_k_sem_init(0x20007b1c, 0, 5).     */
/* Called from key_event_thread 0x2955c bring-up; sets init-done flag         */
/* 0x20018d8a=1. Giver trigger_touch_key_hw_reset 0x2a0c0. Taker UNRECOVERED. */
K_SEM_DEFINE(g_some_module_sem,   /*initial=*/0, /*limit=*/5);             /* 0x20007b1c */

/* In-struct semaphores (NOT module-static; live inside device_info_t, so no  *
 * K_SEM_DEFINE owns them -- init happens wherever device_info is built):      *
 *  - device_info+0xb0  : touch IRQ signal sem. give: touch_key_gpio_isr       *
 *    0x1793c; take: touch_key_thread 0x2a0d8. init/limit UNRECOVERED.         *
 *  - device_info+0xaf4 : IMU trigger k_work/k_poll object. submit via         *
 *    FUN_00072880 in update_imu_trigger_status 0x2bcbc. Owned by system.      */


/* ======================================================================= *
 *  MUTEXES                                                                 *
 * ======================================================================= */

/* --- flash_store ------------------------------------------------------- */
/* @ ext_flash_api_init 0x2e4e8 : k_mutex init (sys_dlist_init 0x20007b54).  */
/* lock/unlock in ext_flash_read 0x2e398 / ext_flash_write 0x2e440.          */
K_MUTEX_DEFINE(g_ext_flash_mutex);                                        /* 0x20007b54 */

/* Referenced-but-defined-elsewhere: the Even-AI text-buffer mutex locked in  *
 * gui_text ui_even_ai_task 0x3bfe0 (DAT_0003c648). Its k_mutex_init lives in  *
 * the Even-AI text-pipeline module and is NOT in any reconstructed body.      */


/* ======================================================================= *
 *  TIMERS  (k_timer_init = FUN_00086726)                                   *
 * ======================================================================= */

/* --- flash_store ------------------------------------------------------- */
/* @ FUN_0002201c 0x2201c : k_timer_init(0x20003d28, expiry=0x19ff0, stop=0).*/
K_TIMER_DEFINE(g_projector_timer, /*expiry=*/0x19ff0, /*stop=*/NULL);      /* 0x20003d28 */


/* ======================================================================= *
 *  WORK ITEMS                                                              *
 * ======================================================================= */

/* No recovered APPLICATION module owns a standalone K_WORK_DEFINE here.     *
 * The six WS2 work guesses have been resolved and all are false positives:   *
 *  0x20004df0 clock baseline; 0x20002c30 nrfx GPIOTE allocation mask;        *
 *  0x20006448 gatt_sc atomic flags; 0x20009fc0 uptime scalar;                 *
 *  0x2000cc24 errno; 0x20002144 bt_dev.rx_queue sys_slist.                    *
 * See GAPS.md and ownership/app_kernel_object_gap_resolution.json.           *
 *                                                                             *
 * Stock Zephyr gatt.c DOES own three private delayable-work members, all      *
 * initialized by bt_gatt_init (FUN_0005a954):                                 *
 *  gatt_delayed_store.work 0x20006350 handler 0x00082fa7                      *
 *  db_hash.work           0x200063a0 handler 0x00082cb3                      *
 *  gatt_sc.work            0x20006418 handler 0x0005b4bd                      *
 * They must come from the stock GATT translation unit; defining them again   *
 * here would duplicate private struct storage.                               */


/* ======================================================================= *
 *  DRIVER / TRANSPORT OBJECTS (not classic K_* kernel objects, listed for  *
 *  completeness -- watchdog, IPC endpoint, PDM ctrl)                        *
 * ======================================================================= */
/*  - system: hardware watchdog, struct device @0x00087cc8, channel id       *
 *    stored @0x20007b50. install init_watchdog 0x2ace0; feed FUN_0002ae84.  */
/*  - ipc_core: g_ipc0_endpoint @0x20007a84 (register_ipc_service_context     *
 *    0x25d40); send ept @0x20007a78; RX ipc0_ept_recv 0x25a48.               */
/*  - audio: nrfx PDM ctrl block g_pdm_ctrl @0x2000b008; +0x14 -> a k_mem_slab*/
/*    and +0x1c/+0x24 (0x2000b024) -> a driver-owned k_msgq (not app-static). */
