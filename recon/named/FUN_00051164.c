/* readable reconstruction; identity: FUN_00051164 @ 0x00051164
 * public-name: FUN_00051164
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   write                                    <= FUN_0004b0dc @ 0x0004b0dc
 * address symbols (name @ address):
 *   rodata_f2432                             @ 0x000f2432
 */
/* Reconstructed FUN_00051164 @ 0x51164  (parity: 300/300 trials, PROVEN) */
extern void write(unsigned int,unsigned int,unsigned int);
/* NCS v2.5.1 Zephyr ARCH_EXCEPT() for ARMv8-M Mainline.  This is an
 * in-body exception sequence, not a callable firmware symbol. */
#define ARCH_EXCEPT(reason) do { \
  __asm__ volatile ( \
    "eors.n r0, r0\n\t" \
    "msr BASEPRI, r0\n\t" \
    "mov r0, %[why]\n\t" \
    "svc %[id]\n\t" \
    : : [why] "i" (reason), [id] "i" (2) : "memory"); \
} while (0)
void FUN_00051164(void)
{
  write(2,0xf2432,0x1d);
  ARCH_EXCEPT(3);
}
