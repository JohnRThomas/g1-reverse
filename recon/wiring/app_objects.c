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
/* static compile-time K_MSGQ (no init call); depth 18 inferred from the    */
/* +0x24 used-count guard in sendAudioStram2Cache 0x2f6b0                    */
K_MSGQ_DEFINE(g_audio_msgq,       /*msg_size=*/208,  /*max_msgs=*/18, 4);  /* 0x20003890 */

/* --- ipc_core (shared with audio) -------------------------------------- */
/* @ init_msgq_uid 0x18e04 : k_msgq_alloc_init(0x20006a38, 8, 10) [dyn]     */
K_MSGQ_DEFINE(g_uid_pipe,         /*msg_size=*/8,    /*max_msgs=*/10, 4);  /* 0x20006a38 */

/* --- misc (shared with audio: file_subsystem_queue_init) --------------- */
/* @ file_subsystem_queue_init 0x234e8 : k_msgq_alloc_init(0x200079a0,201,30) [dyn] */
K_MSGQ_DEFINE(g_file_msg_pipe,    /*msg_size=*/201,  /*max_msgs=*/30, 4);  /* 0x200079a0 */
/* @ debug_log_queue_init 0x19bd0 : k_msgq_alloc_init(0x2000751c,200,20) [dyn] */
K_MSGQ_DEFINE(g_debug_msg_pipe,   /*msg_size=*/200,  /*max_msgs=*/20, 4);  /* 0x2000751c */

/* --- display ----------------------------------------------------------- */
/* static K_MSGQ (no runtime init targets 0x200038c4). msg_size 24 CONFIRMED */
/* from every producer; depth UNRECOVERED (buffer/depth in unreconstructed   */
/* data section). Producers: display_reflash/close/DelayClose/inputEvent/    */
/* powerEvent 0x4967c..0x49a28; consumer FUN_00049090.                       */
K_MSGQ_DEFINE(g_display_msgq,     /*msg_size=*/24,   /*max_msgs=*/UNRECOVERED, 4); /* 0x200038c4 */

/* --- flash_store ------------------------------------------------------- */
/* Three static K_MSGQ_DEFINEs drained by flash_ops_thread (used-count +0x24).*/
/* No runtime k_msgq_init for any -> compile-time; msg_size/depth in data.    */
/* g_flash_store_cmd_msgq: 4-byte settings cmd (SettingStoreHandler 0x23f04). */
K_MSGQ_DEFINE(g_flash_store_cmd_msgq, /*msg_size=*/4, /*max_msgs=*/UNRECOVERED, 4); /* 0x20003994 */
/* g_quicknote_flash_msgq: 12-byte (3xu32) note cmd (getQuickNoteBKPQueueCacheData 0x24684). */
K_MSGQ_DEFINE(g_quicknote_flash_msgq, /*msg_size=*/12, /*max_msgs=*/UNRECOVERED, 4); /* 0x20003960 */


/* ======================================================================= *
 *  THREADS  (all via k_thread_create = FUN_00071eac; prio signed, <0 coop) *
 * ======================================================================= */

/* --- ancs_notify ------------------------------------------------------- */
/* @ start_ancs_work_thread 0x198cc. Self-respawns from ancs_main 0x19950.  */
/* Guard: get_device_info()[0]==2 (iOS) && !is_battery_critical().          */
K_THREAD_DEFINE(ancs_thread, /*stack=*/0x1400 /*5120*/,
                /*entry=*/0x19950 /*ancs_main*/, /*arg=*/conn, 0, 0,
                /*prio=*/-11, 0, 0);
                /* tcb=0x20003c50  stack_base=0x2001d568 */

/* --- flash_store / display co-spawn ------------------------------------ */
/* @ spawn_flash_ops_and_brightness_threads 0x23a54 (a.k.a. FUN_00023a54;   */
/*   cited by flash_store AND display AND ble_proto #1/#2). Two threads:     */
K_THREAD_DEFINE(flash_ops_thread, /*stack=*/0x800 /*2048*/,
                /*entry=*/0x23480, /*arg=*/param_1, 0, 0, /*prio=*/-12, 0, 0);
                /* tcb=0x20003e38  stack_base=0x20021968 */
K_THREAD_DEFINE(brightness_thread, /*stack=*/0x1400 /*5120*/,
                /*entry=*/0x23844, /*arg=*/param_1, 0, 0, /*prio=*/-11, 0, 0);
                /* tcb=0x20003f10  stack_base=0x20022168 */

/* --- flash_store projector/settings thread ----------------------------- */
/* @ FUN_0002201c 0x2201c (settings/projector init). Also inits g_proj dlist */
/* 0x20007574 and k_timer 0x20003d28 (below).                                */
K_THREAD_DEFINE(projector_settings_thread, /*stack=*/0x3000 /*12288*/,
                /*entry=*/0x21da8, /*arg=*/param_1, 0, 0, /*prio=*/-15, 0, 0);
                /* tcb=0x20003d60  stack_base=0x2001e968 */

/* --- ble_proto (spawn tree rooted at run_main_dispatch_thread 0x2a65c) --- */
/* #1/#2 == flash_ops/brightness above (same 0x23a54). #3..#6 below.         */
K_THREAD_DEFINE(ble_worker_3, /*stack=*/0xc00 /*3072*/,
                /*entry=*/0x32420, /*arg=*/param_1, 0, 0, /*prio=*/-12, 0, 0);
                /* @ FUN_00032fe8 0x32fe8; tcb=0x20004870 stack=0x20027a68   */
                /* guard FUN_00032ee4()!=0; sets flag 0x20019ef1=1 on success */
K_THREAD_DEFINE(ble_worker_4, /*stack=*/0x400 /*1024*/,
                /*entry=*/0x324bc, /*arg=*/param_1, 0, 0, /*prio=*/-12, 0, 0);
                /* @ FUN_0003304c 0x3304c; tcb=0x20004798 stack=0x20027668   */
K_THREAD_DEFINE(ble_worker_5, /*stack=*/0x800 /*2048*/,
                /*entry=*/0x47c48, /*arg=*/param_1, 0, 0, /*prio=*/-12, 0, 0);
                /* @ FUN_00047ad0 0x47ad0; tcb=0x20004c08 stack=0x20028668   */
                /* guard mode byte==1; tid stored @0x2000a090                 */

/* --- display dispatch / reflash worker (== ble_proto #6) --------------- */
/* @ FUN_00049638 0x49638 (called from app-init FUN_0002a65c). Drains        */
/* g_display_msgq 0x200038c4. tid -> g_display_thread_id 0x2000a09c.         */
/* stack_size/prio: from ble_proto proven body = 0x1400 / -14.               */
K_THREAD_DEFINE(display_dispatch_thread, /*stack=*/0x1400 /*5120*/,
                /*entry=*/0x49090, /*arg=*/param_1, 0, 0, /*prio=*/-14, 0, 0);
                /* tcb=0x20004d18  stack_base=0x20028e68 */

/* --- STATIC K_THREAD_DEFINE entries (callers:[] -> static), params in a    *
 *     data section not reconstructed. Recorded so the owner is not lost.     */
/* touch_key: touch_key_thread 0x2a0d8 (arg=device_info base; k_sem_take     */
/*   device_info+0xb0, k_msleep 5000/500). stack/prio/tcb UNRECOVERED.       */
/* touch_key: click_event_dispatch_loop 0x28a1c (same arg contract).         */
/*   NOTE: system/wiring.md names 0x28a1c FUN_00028a1c as its own THREAD MAIN */
/*   (key/click interaction loop) -- same body, owned by touch_key/system.   */
/* app-main orchestrator FUN_0002a65c 0x2a65c spawns a thread pool           */
/*   (tcb 0x200040d0..0x200046b8 stride 0xd8; stacks 0x20023c68,0x20024868,  */
/*   0x20024c68,0x20025068,0x20025468,0x20025a68,0x20026268,0x20026a68) whose */
/*   entries include display_dispatch_thread 0x28bec, key_event_thread       */
/*   0x2955c, slave_display_thread 0x27cfe, main system thread 0x2a8d8,       */
/*   mode/state worker 0x2c99c. Per-entry stack/prio UNRECOVERED (body 0x2a65c*/
/*   not reconstructed).                                                      */


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

/* No app module's proven body contains a k_work_init/K_WORK_DEFINE for an    *
 * application work item. The FUN_00072880 "submit/wake" calls in imu_motion, *
 * display (submit_display_reflash_work 0x4904c) etc. target k_poll/sem-style *
 * objects inside device_info_t or the g_app_language_sem above, not a k_work *
 * created here. See GAPS.md: WS2 reports several standalone k_work objects    *
 * (0x20004df0, 0x20002c30, 0x20006448, 0x20009fc0, 0x2000cc24, +delayable    *
 * 0x20002144) that have NO definition in any module wiring.md.               */


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
