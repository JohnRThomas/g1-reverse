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
