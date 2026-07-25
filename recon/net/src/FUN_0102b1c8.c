/* net-core FUN_0102b1c8 @ 0x102b1c8  (parity 300 trials PROVEN) */

/* P4 iteration 18 — three findings recorded here, two fixed and one deferred.
 *
 * (1) STORAGE COLLISION (fixed).  The shipped thread object 0x21001e38 and its
 *     0x600-byte stack 0x21007300 land, in the cohesive link, inside
 *     `backend_data_0` (the ipc_rpmsg_static_vrings instance) and inside
 *     `sdc_mempool`.  Measured with a Renode watchpoint: z_setup_new_thread
 *     writing thread+0x54 hit 0x21001e8c = rpmsg_inst.endpoint[0].ep.cb, after
 *     which rpmsg_virtio_rx_callback did `blx` on a zeroed callback and took a
 *     USAGE FAULT at t = 1.455 s (iteration 18 §18.4).  Real storage now comes
 *     from recon/application/net/src/g1_product_endpoints.c.
 *
 * (2) DROPPED 64-bit `k_timeout_t delay` (same class as FUN_0102afbc, and as
 *     app-core iteration 12).  FUN_01035fa0 is z_impl_k_thread_create; the
 *     nine-parameter declaration below never wrote the outgoing delay words,
 *     so the callee read an uninitialised stack slot.
 *
 * (3) DEFERRED — the thread ENTRY POINT IS NOT RECONSTRUCTED.  0x0102ba05 is a
 *     runtime Thumb pointer; its analysis address is 0x0102b204, which lies
 *     INSIDE FUN_0102b1c8's declared Ghidra extent (next catalogued entry is
 *     FUN_0102b2ac at 0x0102b2ac).  It is therefore an eighth instance of the
 *     "Ghidra folded a sibling function into the tail of the preceding symbol"
 *     class: 0x0102b204..0x0102b2ac (168 B) is a separate function that has no
 *     reconstruction and no catalogue entry, so `rodata_102ba05` still resolves
 *     to the raw original-image address and points at unrelated text in our
 *     link.  Starting the thread would jump there.
 *
 * Until (3) is reconstructed the delay is passed as **K_FOREVER**
 * (ticks = -1), i.e. the thread is created but never scheduled.  This is a
 * DELIBERATE, DOCUMENTED DIVERGENCE from the shipped firmware (which passes
 * K_NO_WAIT): it is deterministic, it cannot corrupt anything, and it is
 * strictly better than reading an uninitialised delay.  Restore K_NO_WAIT
 * (`0, 0, 0`) at the same time as the 0x0102b204 reconstruction. */

extern void FUN_01035fa0(unsigned int, unsigned int, unsigned int, unsigned int,
                          unsigned int, unsigned int, unsigned int, unsigned int,
                          unsigned int, unsigned int, int, int);

#ifdef G1_COHESIVE_BUILD
#include <zephyr/kernel.h>
extern struct k_thread g1_esb_worker_thread;
extern k_thread_stack_t g1_esb_worker_stack[];
/* P4 iteration 30 - deferral (3) above is CLOSED.  0x0102b204 is reconstructed
 * in recon/net/src/FUN_0102b204.c (g1_esb_uplink_worker_thread), so the entry
 * is now the linker-resolved address and the shipped K_NO_WAIT delay is
 * restored.  Until this iteration the thread was created with a raw
 * original-image entry AND K_FOREVER, i.e. it never ran, which is why the
 * {0x0d, 0x02} sync-ack relay FUN_0102a408 -- its only caller -- had never
 * executed and device_info[0x105a] never reached 2. */
extern void FUN_0102b204(void *p1, void *p2, void *p3);
#define C_ESB_WORKER_OBJ   ((unsigned int)(unsigned long)&g1_esb_worker_thread) /*=0x21001e38*/
#define C_ESB_WORKER_STACK ((unsigned int)(unsigned long)g1_esb_worker_stack)   /*=0x21007300*/
#define C_ESB_WORKER_ENTRY ((unsigned int)(unsigned long)&FUN_0102b204)         /*=0x0102ba05*/
#define C_ESB_WORKER_DELAY_HI 0
#define C_ESB_WORKER_DELAY_LO 0
#else
#define C_ESB_WORKER_OBJ   0x21001e38u
#define C_ESB_WORKER_STACK 0x21007300u
#define C_ESB_WORKER_ENTRY 0x0102ba05u
#define C_ESB_WORKER_DELAY_HI 0
#define C_ESB_WORKER_DELAY_LO 0
#endif

void FUN_0102b1c8(void)
{
  FUN_01035fa0(C_ESB_WORKER_OBJ, C_ESB_WORKER_STACK, 0x600, C_ESB_WORKER_ENTRY,
               0, 0, 0, 0xfffffff5u, 0,
               0, C_ESB_WORKER_DELAY_HI, C_ESB_WORKER_DELAY_LO);
  return;
}
