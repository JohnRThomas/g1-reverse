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
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

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

/* --- group 3 (P4 iteration 10): the 20-slot message pool -----------------
 *
 * `msg_queue_init` (original 0x33c5c) clears the message pool with
 *
 *     iVar2 = g_message_pool;                     /- 0x20007dac -/
 *     do { iVar2 = memset_bytes(iVar2, 0, 0x1b4, ...); iVar2 += 0x1b4; }
 *     while (++iVar3 != 0x14);
 *
 * i.e. it zeroes 20 x 436 = 8720 bytes spanning the ORIGINAL absolute range
 * 0x20007dac .. 0x20009fbc.  That range is confirmed exactly by the pin
 * ledger: the next pinned global after the pool is g_whitelist_app_parse_buf
 * at 0x20009fbc, and the only three other pins inside it are the pool's own
 * interior views (g_notif_app_pkg_table_buf = pool+0x10,
 * g_message_table_mirror = pool+0x1108 = slot 10, and
 * g_message_table_mirror_ovfl_slot = pool+0x205c = slot 19).
 *
 * In OUR build that 8.5 KiB window covers SIX live Zephyr objects:
 *   smp_work_queue_stack (0x20007610), bt_lw_stack_area (0x20007e10),
 *   _k_mem_slab_buf_chan_slab (0x20008328), z_interrupt_stacks (0x200084c0),
 *   z_idle_stacks (0x20008cc0) and z_main_stack (0x20008e00).
 *
 * MEASURED FAILURE (iteration 9's blocker, diagnosed in iteration 10): with
 * the pin, `msg_queue_init` zeroed the idle thread's stack.  Renode
 * instrumentation on /private/tmp/g1-i9g-app:
 *     TCREATE/SETUP  thread=20004870 (z_idle_threads[0]) stack=20008cc0 320 B
 *     arch_new_thread wrote its initial frame: r0 slot 0x20008de0 = 0x0006d1b9
 *                     (idle entry), PC slot 0x20008df8 = 0x00077468
 *                     (z_thread_entry), callee_saved.psp = 0x20008de0
 *     byte watchpoint on 0x20008de8 -> "B pc=0007f22c val=00"  (memset+0xa)
 *     memset hook     -> "MEMSET dst=20008d00 len=436 val=0 lr=0002d479"
 *                        (= msg_queue_init+0x1c, pool slot 9)
 *     at the fault the whole window 0x20008dc0..0x20008e00 reads zero, so
 *     z_arm_pendsv restored the idle thread with a stacked PC of 0 ->
 *     "Attempt to execute undefined instruction" -> SYSRESETREQ at 0.048 s.
 *
 * The pool is above the shipped .data end (0x20003e29), so it is .bss in the
 * original too: plain zero-initialised storage reproduces it exactly.  All
 * four pins are rebound onto this one object at their original relative
 * offsets, so every recovered accessor keeps the original layout. */
/* `retain` (SHF_GNU_RETAIN): the four bindings are lazy linker-script
 * PROVIDE expressions, not relocations, so they do not root the section.
 * Iteration 10 measured a sibling block being silently discarded by
 * --gc-sections, after which every PROVIDE resolved against a base of 0. */
unsigned char g1_message_pool[20 * 436] __aligned(4)
	__attribute__((used, retain));
