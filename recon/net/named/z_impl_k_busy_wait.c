/* readable reconstruction; identity: FUN_0103b0e8 @ 0x0103b0e8
 * public-name: z_impl_k_busy_wait
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   arch_busy_wait                           <= FUN_0102d25c @ 0x0102d25c
 *   z_impl_k_busy_wait                       <= FUN_0103b0e8 @ 0x0103b0e8
 */
/* net-core FUN_0103b0e8 @ 0x103b0e8 — true CFG extent 8 bytes (ends 0x103b0f0) */

extern void arch_busy_wait(int);
void z_impl_k_busy_wait(int param_1) {
  if (param_1 != 0) {
    arch_busy_wait(param_1);
  }
}
