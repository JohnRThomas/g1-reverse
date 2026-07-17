/* readable reconstruction; identity: FUN_0102185c @ 0x0102185c
 * public-name: FUN_0102185c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_net_res_reg_key                        @ 0x210016b4
 *   g_net_res_reg_handle                     @ 0x210016bc
 *   g_net_res_reg_param16                    @ 0x210016c0
 */
/* net-core FUN_0102185c @ 0x102185c  (parity 300 trials PROVEN) */
/* net-core FUN_0102185c @ 0x102185c  (parity 300 trials PROVEN) */
/* net-core FUN_0102185c @ 0x102185c  (parity 300 trials PROVEN) */

static volatile int *const P_10218a8 = (volatile int *)0x210016bc;
static volatile int *const P_10218ac = (volatile int *)0x210016b4;
static volatile unsigned short *const P_10218b0 = (volatile unsigned short *)0x210016c0;
extern void sdc_assertion_fail(int,int);
extern int FUN_01027a4a(int);
void FUN_0102185c(int param_1, unsigned short param_2)
{
  if (*P_10218a8 == 0) {
    *P_10218ac = param_1;
    int iVar1 = FUN_01027a4a(*P_10218ac);
    *P_10218a8 = iVar1;
    if (*P_10218a8 == 0) {
      sdc_assertion_fail(0x84, 0x22);
    }
    *P_10218b0 = param_2;
  }
}
