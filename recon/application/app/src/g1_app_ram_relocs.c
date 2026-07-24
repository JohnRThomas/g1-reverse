/* ---------------------------------------------------------------------------
 * BRING-UP WIRING TU (P4 iteration 6) — relocated ABSOLUTE RAM globals.
 *
 * The recon convention pins every recovered global to its ORIGINAL absolute
 * address (`PROVIDE(name = 0x2000xxxx)` in recon/symbols/g1_app_globals.ld).
 * The original image's globals cover essentially the whole 512 KiB SRAM
 * (0x20000000 .. 0x2007fc70), so those addresses cannot be reserved away from
 * Zephyr — our build's kernel objects necessarily overlap them.  Where a pin
 * happens to land inside an object OUR build actually uses, the recovered code
 * silently corrupts that object.
 *
 * This TU gives real, linker-allocated storage to the pins that were MEASURED
 * to corrupt a live object, and `g1_app_globals.ld` rebinds those pin names
 * here.  Canonical parity bodies in recon/app/src are untouched: the recovered
 * code takes `&name`, so a linker rebind is sufficient and no source changes.
 *
 * GROUP 1 — `logging_stack` (our ELF: 0x20006d58, 2048 B, the Zephyr log
 * thread's stack).  Five pins land in its TOP 68 bytes:
 *
 *   0x20007514 g_bonded_count       u32
 *   0x20007518 g_ancs_conn          u32 (struct bt_conn *)
 *   0x2000751c g_debug_msg_pipe     struct k_msgq (52 B: next pin is +0x34;
 *                                   debug_log_queue_init does
 *                                   k_msgq_alloc_init(&it, 200, 0x14) and
 *                                   enqueue_debug reads used_msgs at +0x24)
 *   0x20007550 g_ring_log_pending   u32
 *   0x20007554 g_log_use_alt_sink   u32  (ends exactly at 0x20007558 =
 *                                   logging_stack end)
 *
 * MEASURED FAILURE (iteration 6, before this fix): the log thread is created
 * at instruction 613,974 with entry z_thread_entry; arch_new_thread writes its
 * initial exception frame to 0x20007538..0x20007558, i.e. the TOP of
 * logging_stack, which is exactly where these pins sit.  At instruction
 * 4,978,573 the (newly reachable) `debug_print` path runs and
 * `debug_print+0x4a` executes `str r2,[r3]` with r3 = 0x20007550 — the
 * frame's stacked PC slot — writing 1 over z_thread_entry.  Proven with a
 * Renode write-watchpoint on 0x20007550:
 *     WROTE_PC_SLOT pc=0x0004e0bc val=0x00077a8e   (arch_new_thread, correct)
 *     WROTE_PC_SLOT pc=0x00017aea val=0x00000001   (debug_print, corruption)
 * and with a hook on z_arm_pendsv's exception return:
 *     BADSWITCH th=0x20003420 psp=0x20007538 stackedpc=0x00000001
 * The next context switch to the log thread therefore resumed at PC=1, slid
 * through the unmapped 0..0xC200 MCUboot window, and took a usage fault ->
 * z_fatal_error -> SYSRESETREQ.
 *
 * See recon/emulator/reports/our_boot_bringup.md, Iteration 6.
 * ------------------------------------------------------------------------- */
#include <zephyr/kernel.h>

/* --- group 1: pins that overlapped `logging_stack` -------------------- */
volatile unsigned int g1_bonded_count;
volatile unsigned int g1_ancs_conn;
struct k_msgq         g1_debug_msg_pipe;
volatile unsigned int g1_ring_log_pending;
volatile unsigned int g1_log_use_alt_sink;

/* --- group 2 (P4 iteration 7): the Application Event Manager state ------
 *
 * `app_event_manager_submit` (original 0x4f770) submits the k_work pinned at
 * 0x20002838 after linking the event onto the slist at 0x2000a2c8 under the
 * spinlock at 0x2000a2c4.  In OUR build:
 *   0x20002838 lands inside nrfx_gpiote's `.data.m_cb` (0x200027ec, 0x7c B)
 *   0x2000a2c4/0x2000a2c8 land inside `z_main_stack` (0x20008dd0, 16 KiB)
 *
 * The k_work is `.data` in the shipped image: its load image (flash
 * 0xf6d64 + 0x2838 = 0xf959c) reads
 *     { .node.next = 0, .handler = 0x0004f5b1, .queue = 0, .flags = 0 }
 * and 0x4f5b0 is the durable-map identity `app_event_manager_process_events`.
 * Nothing in the recovered corpus writes that handler, so with the pin the
 * work item's handler word was simply whatever nrfx_gpiote had at that offset.
 *
 * MEASURED (iteration 7 Step A, first build /private/tmp/g1-i7a-app): the
 * 64 bytes of RAM this iteration added shifted every object by 0x30-0x40, so
 * 0x20002838 moved from m_cb+0x30 to m_cb+0x4c.  The handler word stopped
 * reading a nonzero value, `work_queue_main` hit its
 * `__ASSERT(handler != NULL)` at instruction 4,669,670 and the boot took an
 * _oops -> z_fatal_error -> SYSRESETREQ.  The collision itself is NOT new; it
 * was latent in iterations 5-6 only because the garbage flags word happened to
 * make k_work_submit believe the item was already queued.
 *
 * Emitting the work item also relocates the handler, which pulls the (until
 * now garbage-collected) recovered `app_event_manager_process_events` into the
 * link — i.e. the event manager actually runs for the first time. */
extern void app_event_manager_process_events(void);

K_WORK_DEFINE(g1_app_event_processor_work, app_event_manager_process_events);

struct k_spinlock g1_notify_pending_lock;
sys_slist_t       g1_notify_pending_slist;
/* Bitmap indexed by (event_type_index >> 5); the shipped event-type section
 * 0xfa9b4..0xfaa14 holds (0x60 / 24) = 4 descriptors, so one word is enough.
 * Four are allocated so the index cannot leave the object if the section
 * bounds are ever relocated. */
volatile unsigned int g1_notify_pending_flags_bitmap[4];
