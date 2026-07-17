/* readable reconstruction; identity: FUN_0102470c @ 0x0102470c
 * public-name: FUN_0102470c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_154_critical_section_nest_cnt          @ 0x21001bd0
 *   REG_41005000                             @ 0x41005000
 */
/* net-core FUN_0102470c @ 0x102470c  (parity 300 trials PROVEN) */

typedef void (*fp0_t)(void);
extern void FUN_010246e4(void);
extern unsigned int FUN_01024ad0(void);

unsigned int FUN_0102470c(unsigned int param_1)
{
  unsigned int base = 0x21001bd0u;
  unsigned int iVar3;

  if (*(volatile unsigned char *)base == 0) {
    *(volatile unsigned int *)(base + 8) = param_1;
    *(volatile unsigned char *)base = 1;
    FUN_010246e4();
    iVar3 = FUN_01024ad0();
    if (iVar3 == 0) {
      *(volatile unsigned char *)(base + 0xc) = 1;
      *(volatile unsigned int *)(0x41005000u + 0x304) = 1;
    } else if (*(volatile fp0_t *)(base + 8) != (fp0_t)0) {
      (*(volatile fp0_t *)(base + 8))();
      *(volatile unsigned int *)(base + 8) = 0;
    }
  }
  return 0;
}
