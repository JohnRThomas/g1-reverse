/* ---------------------------------------------------------------------------
 * BRING-UP WIRING TU (P4 iteration 7) — relocated CPUAPP serialization/IPC
 * objects (the `ipc0` endpoint registration state).
 *
 * WHY THIS EXISTS
 * ---------------
 * `serialization_init` (0x25c54) registers the app's rpmsg endpoint with
 *
 *     serialization_register_endpoint(&rodata_87c08,            /- instance -/
 *                                     &g_serialization_ipc_ept, /- ept      -/
 *                                     &g_serialization_ipc_ept_ctx); /- cfg -/
 *
 * i.e. Zephyr's `ipc_service_register_endpoint(instance, ept, cfg)`.  All three
 * operands are pinned at their ORIGINAL absolute addresses, and in our build
 * every one of them lands inside a live object of a DIFFERENT allocation:
 *
 *   pin                          original VA   our build's object at that VA
 *   g_serialization_ipc_ept_ctx  0x200023dc    fdtable            (0x20002218, 640 B)
 *   g_serialization_ipc_mutex    0x200039c8    posix_thread_pool  (0x20003938, 1240 B)
 *   g_ipc_send_fail_cnt          0x20007a74    smp_work_queue_stack (0x200075a0, 2048 B)
 *   g_serialization_ipc_ept      0x20007a78    smp_work_queue_stack
 *   g_serialization_ipc_ready    0x20007a80    smp_work_queue_stack
 *   g_ipc0_endpoint              0x20007a84    smp_work_queue_stack
 *
 * (measured with readelf -sW on /private/tmp/g1-i6f-app/zephyr/zephyr.elf —
 * the same "absolute RAM-pin collision" class iteration 6 §3 catalogued.)
 *
 * Two of them are not merely mis-placed, they are *uninitialised*: in the
 * shipped image both live in `.data` and carry a real initialiser that the
 * recovered code never writes.  A bare linker PROVIDE cannot express that, so
 * — exactly like the `gpio_dt_spec` tables of iteration 5 §2 — they have to be
 * EMITTED by the build.  `recon/symbols/g1_app_globals.ld` rebinds the six pin
 * names onto the definitions below; the canonical parity bodies in
 * recon/app/src are untouched (they all take `&name`).
 *
 * DECODED FROM THE SHIPPED IMAGE
 * ------------------------------
 * The app image's `.data` load image starts at flash VA 0xf6d64 and is copied
 * to RAM 0x20000000 (length 0x3e29, ending exactly at the image end 0xfab8d).
 * That mapping is PROVEN by the semaphore below: at flash 0xfa72c
 * (= 0xf6d64 + 0x39c8) the bytes are
 *
 *     +0x00 0x200039c8   wait_q.head  -> self          (empty sys_dlist_t)
 *     +0x04 0x200039c8   wait_q.tail  -> self
 *     +0x08 0x00000000   count = 0
 *     +0x0c 0x00000001   limit = 1
 *     +0x10 0x200039d8   poll_events.head -> self      (CONFIG_POLL=y)
 *     +0x14 0x200039d8   poll_events.tail -> self
 *
 * — a self-consistent `struct k_sem` whose two self-pointers can only be right
 * if the load base is 0xf6d64.  Hence `K_SEM_DEFINE(g_serialization_ipc_mutex,
 * 0, 1)` in the original sources.
 *
 * With that mapping, `g_serialization_ipc_ept_ctx` (0x200023dc) loads from
 * flash VA 0xf9140, and the 24 bytes there are a textbook `struct ipc_ept_cfg`:
 *
 *     +0x00 0x0009f71c   .name     -> the C string "ipc0"
 *     +0x04 0x00000000   .prio     = 0
 *     +0x08 0x00025b6d   .cb.bound    -> 0x25b6c (Thumb)
 *     +0x0c 0x00025a49   .cb.received -> 0x25a48 = ipc0_ept_recv
 *     +0x10 0x00000000   .cb.error = NULL
 *     +0x14 0x00000000   .priv     = NULL
 *
 * Corroboration for each field:
 *   * 0x9f71c is the ONLY "ipc0" string in app_update.bin, and the only other
 *     pointer to it is the `struct device` at 0x87c08 (= the ipc0 device, our
 *     __device_dts_ord_29) — i.e. this record announces the same endpoint name
 *     the CPUNET core sends in its rpmsg name-service message.
 *   * 0x25a48 is the durable-map identity `ipc0_ept_recv`
 *     (recon/catalogs/function_names_app.json), the recovered receive handler.
 *   * 0x25b6c is an 8-byte uncatalogued function in the Ghidra gap
 *     0x25b6c..0x25b78; disassembled from the image it is exactly
 *         25b6c: ldr r0,[pc,#4]      ; literal 0x200039c8 = the semaphore above
 *         25b6e: b.w 0x72880         ; k_sem_give
 *     i.e. `bound(priv) { k_sem_give(&g_serialization_ipc_mutex); }`, which is
 *     precisely the semaphore `serialization_init` then k_sem_take()s.  It is
 *     re-emitted below as g1_ipc0_ept_bound rather than pinned, because its
 *     literal has to relocate with the semaphore.
 *
 * See recon/emulator/reports/our_boot_bringup.md §Iteration 7.
 * ------------------------------------------------------------------------- */
#include <zephyr/kernel.h>
#include <zephyr/ipc/ipc_service.h>

/* Recovered receive handler, original 0x25a48.  Its reconstruction takes
 * (data, len) and ignores `priv`, matching the original's own prototype. */
extern void ipc0_ept_recv(unsigned char *data, int len);

/* was g_serialization_ipc_mutex (original 0x200039c8, .data, K_SEM_DEFINE(0,1)) */
K_SEM_DEFINE(g1_serialization_ipc_sem, 0, 1);

/* was the anonymous 8-byte function at original 0x25b6c (see header comment) */
static void g1_ipc0_ept_bound(void *priv)
{
	ARG_UNUSED(priv);
	k_sem_give(&g1_serialization_ipc_sem);
}

/* Thin adapter onto the recovered handler.  The original stored the raw
 * pointer 0x25a49; C needs the exact `received` prototype, and on AAPCS the
 * two are call-compatible (r0 = data, r1 = len, r2 = priv, unused). */
static void g1_ipc0_ept_received(const void *data, size_t len, void *priv)
{
	ARG_UNUSED(priv);
	ipc0_ept_recv((unsigned char *)data, (int)len);
}

/* was g_serialization_ipc_ept_ctx (original 0x200023dc, .data image 0xf9140) */
struct ipc_ept_cfg g1_serialization_ipc_ept_cfg = {
	.name = "ipc0",
	.prio = 0,
	.cb = {
		.bound = g1_ipc0_ept_bound,
		.received = g1_ipc0_ept_received,
		.error = NULL,
	},
	.priv = NULL,
};

/* .bss companions of the same registration (all above the 0x20003e29 .data
 * end in the original, i.e. zero-initialised there too). */
struct ipc_ept        g1_serialization_ipc_ept;   /* was g_serialization_ipc_ept   0x20007a78 */
volatile unsigned int g1_serialization_ipc_ready; /* was g_serialization_ipc_ready 0x20007a80 */
void *volatile        g1_ipc0_endpoint;           /* was g_ipc0_endpoint           0x20007a84 */
volatile unsigned int g1_ipc_send_fail_cnt;       /* was g_ipc_send_fail_cnt       0x20007a74 */
