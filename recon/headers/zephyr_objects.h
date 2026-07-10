/*
 * zephyr_objects.h  —  Even G1 app-core: Zephyr kernel object typedefs.
 *
 * The reconstructed firmware is a Zephyr / NCS 2.5.1 application. Its bodies
 * call the standard kernel API (k_msgq_*, k_sem_*, k_mutex_*, k_thread_*,
 * k_work_*, k_timer_*, k_queue_*, k_heap_*, k_mem_slab_*, k_poll_*). The REAL
 * definitions of these types come from Zephyr's <zephyr/kernel.h>; this header
 * only provides forward/opaque typedefs so the recovered units compile stand-
 * alone (outside a full Zephyr tree) without redefining the kernel structs.
 *
 * When compiling INSIDE a Zephyr build, define G1_HAVE_ZEPHYR_KERNEL before
 * including this file (or simply include <zephyr/kernel.h> first) and these
 * opaque typedefs are suppressed so the genuine kernel definitions win.
 *
 * The kernel API set actually used (from a scan of recon/named +
 * recon/verified/src) is, by frequency:
 *   k_msgq_put/get/alloc_init/init/cleanup, k_mutex_lock/unlock,
 *   k_sem_init, k_queue_init/insert_with_timeout/prepend/lock/unlock,
 *   k_heap_alloc, k_mem_slab_alloc/free, k_timer_init/start/stop,
 *   k_work_init/submit_to_queue/schedule, k_work_queue_init/start,
 *   k_thread_*, k_poll_signal_init, k_fifo_peek_head.
 */
#ifndef G1_ZEPHYR_OBJECTS_H
#define G1_ZEPHYR_OBJECTS_H

#include <stdint.h>

#if !defined(G1_HAVE_ZEPHYR_KERNEL) && !defined(ZEPHYR_INCLUDE_KERNEL_H_)

/* Opaque kernel object types — names only. Real layouts live in Zephyr.
 * They are declared as incomplete structs so code may only hold POINTERS to
 * them here; the genuine sized definitions arrive with <zephyr/kernel.h>. */
struct k_msgq;         typedef struct k_msgq        k_msgq;
struct k_sem;          typedef struct k_sem         k_sem;
struct k_mutex;        typedef struct k_mutex       k_mutex;
struct k_thread;       typedef struct k_thread      k_thread;
struct k_timer;        typedef struct k_timer       k_timer;
struct k_work;         typedef struct k_work        k_work;
struct k_work_q;       typedef struct k_work_q      k_work_q;
struct k_work_queue_config; typedef struct k_work_queue_config k_work_queue_config;
struct k_work_delayable;    typedef struct k_work_delayable    k_work_delayable;
struct k_queue;        typedef struct k_queue       k_queue;
struct k_fifo;         typedef struct k_fifo        k_fifo;
struct k_lifo;         typedef struct k_lifo        k_lifo;
struct k_stack;        typedef struct k_stack       k_stack;
struct k_heap;         typedef struct k_heap        k_heap;
struct k_mem_slab;     typedef struct k_mem_slab    k_mem_slab;
struct k_pipe;         typedef struct k_pipe        k_pipe;
struct k_poll_signal;  typedef struct k_poll_signal k_poll_signal;
struct k_poll_event;   typedef struct k_poll_event  k_poll_event;
struct k_event;        typedef struct k_event       k_event;
struct k_condvar;      typedef struct k_condvar     k_condvar;
struct k_spinlock;     typedef struct k_spinlock    k_spinlock;

/* Common kernel scalar aliases used in the reconstructed signatures. */
typedef int32_t  k_timeout_t_ticks;   /* placeholder for k_timeout_t         */
typedef void (*k_work_handler_t)(struct k_work *work);
typedef void (*k_timer_expiry_t)(struct k_timer *timer);
typedef void (*k_thread_entry_t)(void *p1, void *p2, void *p3);
typedef uintptr_t k_tid_t_placeholder; /* placeholder for k_tid_t            */

#endif /* !G1_HAVE_ZEPHYR_KERNEL */

/* ---- Named kernel objects referenced by the reconstructed bodies ---------
 * These live at fixed RAM addresses in the image; declared as externs so the
 * transport units resolve against them. Real storage is defined by the boot/
 * init sequence (K_MSGQ_DEFINE etc.) inside Zephyr's linker sections. */
extern k_msgq  g_dashboard_response_msgq;  /* @0x2000392c  ipc_core response queue */
extern k_pipe  g_uid_pipe;                 /* init_msgq_uid(): k_msgq_alloc_init(...,8,10) */

#endif /* G1_ZEPHYR_OBJECTS_H */
