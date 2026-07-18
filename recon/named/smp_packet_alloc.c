/* readable reconstruction; identity: FUN_000526e4 @ 0x000526e4
 * public-name: smp_packet_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_packet_alloc                         <= FUN_000526e4 @ 0x000526e4
 * address symbols (name @ address):
 *   g_ancs_notify_3be8                       @ 0x20003be8
 */
/* Reconstructed FUN_000526e4 @ 0x526e4  (parity: 300/300 trials, PROVEN) */

extern void FUN_000836de(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
void smp_packet_alloc(unsigned int param_1, unsigned int param_2)
{
  FUN_000836de(0x20003be8UL, param_2, 0, 0);
}
