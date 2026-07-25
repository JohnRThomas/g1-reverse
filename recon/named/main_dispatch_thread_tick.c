/* readable reconstruction; identity: FUN_0007cb66 @ 0x0007cb66
 * public-name: main_dispatch_thread_tick
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 *   main_dispatch_thread_tick                <= FUN_0007cb66 @ 0x0007cb66
 */
/* Reconstructed FUN_0007cb66 @ 0x7cb66 */

/* Thin forwarding veneer over z_impl_k_thread_create.  It takes the four
 * register arguments plus three stack arguments of its own -- p1 at sp+0x00,
 * prio at sp+0x04 and a 64-bit k_timeout_t delay at sp+0x08 -- and re-lays them
 * as the callee's ten-argument frame with p2, p3 and options hard-coded to 0
 * (original 0x7cb66: ldrd r4,r5,[sp,#0x38] ; strd r4,r5,[sp,#0x18] ; ...).
 * The previous reconstruction declared both sides as taking no arguments and so
 * compiled to a bare `b.w`, forwarding the caller's 4-word block verbatim. */
extern void z_impl_k_thread_create(void*, void*, unsigned int, void*,
                                   void*, void*, void*, int, unsigned int,
                                   unsigned long long);

void main_dispatch_thread_tick(void *thread, void *stack,
                               unsigned int stack_size, void *entry,
                               void *p1, int prio, unsigned long long delay)
{
  z_impl_k_thread_create(thread, stack, stack_size, entry, p1, 0, 0,
                         prio, 0, delay);
}
