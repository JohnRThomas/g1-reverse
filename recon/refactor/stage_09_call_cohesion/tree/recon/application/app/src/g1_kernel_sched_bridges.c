/* Library-displacement Batch 2b call-identity bridges (iteration 9).
 *
 * Batch 2b displaces recovered `zephyr_kernel` duplicates onto their genuine
 * upstream bodies in zephyr/kernel/{sched,poll}.c.  Five of the displaced
 * identities are still called by name from recovered translation units that
 * are NOT part of the sub-batch, so the link needs the historical spelling.
 * Each one forwards to the public upstream entry point; no recovered caller
 * source is edited.  Argument lists are taken from the proven reconstruction
 * prototypes in recon/symbolized/app/<name>.c; the trailing Ghidra-artifact
 * parameters that the shipped bodies never read are accepted and dropped.
 * AAPCS makes each forward exact.
 *
 * (`z_tick_sleep` and `unready_thread` are the two other referenced identities
 * in this sub-batch; both upstream bodies are file-static in sched.c with no
 * linkable symbol, so their rows are reverted instead of bridged.)
 */
#include <stdint.h>

struct k_thread;
struct k_poll_signal;

extern void z_reset_time_slice(struct k_thread *thread);
extern void z_ready_thread(struct k_thread *thread);
extern int  z_set_prio(struct k_thread *thread, int prio);
extern void z_impl_k_thread_suspend(struct k_thread *thread);
extern int  z_impl_k_poll_signal_raise(struct k_poll_signal *sig, int result);

/* 0x00073788 -> zephyr/kernel/sched.c :: z_reset_time_slice */
void sched_switch_handle_timeout(int thread)
{
    z_reset_time_slice((struct k_thread *)(uintptr_t)thread);
}

/* 0x000738d4 -> zephyr/kernel/sched.c :: z_ready_thread */
void z_ready_thread_locked(int thread, uint32_t p2, uint32_t p3, uint32_t p4)
{
    (void)p2; (void)p3; (void)p4;
    z_ready_thread((struct k_thread *)(uintptr_t)thread);
}

/* 0x00074060 -> zephyr/kernel/sched.c :: z_set_prio */
int z_sched_set_prio_and_requeue(int *thread, char prio, unsigned p3, unsigned p4)
{
    (void)p3; (void)p4;
    return z_set_prio((struct k_thread *)thread, (int)prio);
}

/* 0x000741a4 -> zephyr/kernel/sched.c :: z_impl_k_thread_suspend */
void z_thread_suspend(uint8_t *thread)
{
    z_impl_k_thread_suspend((struct k_thread *)thread);
}

/* 0x000757b0 -> zephyr/kernel/poll.c :: z_impl_k_poll_signal_raise */
uint32_t poll_signal_event_locked(int *sig, int result)
{
    return (uint32_t)z_impl_k_poll_signal_raise((struct k_poll_signal *)sig,
                                                result);
}
