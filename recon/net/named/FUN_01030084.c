/* readable reconstruction; identity: FUN_01030084 @ 0x01030084
 * public-name: FUN_01030084
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 *   net_buf_simple_tailroom                  <= FUN_0103a468 @ 0x0103a468
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103de6b                           @ 0x0103de6b
 */
/* net-core FUN_01030084 @ 0x1030084  (parity 300 trials PROVEN) */

extern unsigned int net_buf_simple_tailroom(void);
extern void assert_print(unsigned int a, unsigned int b, unsigned int c);
extern void FUN_01039bb0(unsigned int a, unsigned int b);

int FUN_01030084(int *param_1, unsigned int param_2)
{
  unsigned short uVar1;
  unsigned int uVar2;
  int iVar3;

  uVar1 = *(unsigned short *)(param_1 + 1);
  iVar3 = *param_1;
  uVar2 = net_buf_simple_tailroom();
  if (uVar2 < param_2) {
    assert_print(0x0103d2a7u, 0x0103de6bu, 0x3e);
    FUN_01039bb0(0x0103de6bu, 0x3e);
  }
  *(unsigned short *)(param_1 + 1) = uVar1 + (short)param_2;
  return iVar3 + (unsigned int)uVar1;
}
