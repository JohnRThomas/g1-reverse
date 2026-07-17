/* readable reconstruction; identity: FUN_00051164 @ 0x00051164
 * public-name: FUN_00051164
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fd_table_dispatch_op2                    <= FUN_0004b0dc @ 0x0004b0dc
 * address symbols (name @ address):
 *   rodata_f2432                             @ 0x000f2432
 */
/* Reconstructed FUN_00051164 @ 0x51164  (parity: 300/300 trials, PROVEN) */
extern void fd_table_dispatch_op2(unsigned int,unsigned int,unsigned int);
/* Zephyr architecture boundary; implemented by ARCH_EXCEPT(reason). */
extern void ARCH_EXCEPT(unsigned int reason);
void FUN_00051164(void)
{
  fd_table_dispatch_op2(2,0xf2432,0x1d);
  ARCH_EXCEPT(3);
}
