/* readable reconstruction; identity: FUN_0101124c @ 0x0101124c
 * public-name: FUN_0101124c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_own_addr_info                      @ 0x21000f20
 */
/* net-core FUN_0101124c @ 0x101124c  (parity 300 trials PROVEN) */
#define P_010112d8 0x21000f20

extern int FUN_0100ca68(unsigned char);
extern int FUN_0100bc04(unsigned char);
extern void FUN_0100ab14(int, int, unsigned int);
extern void FUN_0100cbe4(int, unsigned char);
extern int FUN_0100ca80(unsigned char);
extern int FUN_0100bbec(unsigned char);
extern void FUN_0100e028(int, int);
extern void FUN_0100e054(int, int);

void FUN_0101124c(int param_1, unsigned int param_2)
{
  int iVar2;
  int iVar3;
  int *puVar1;

  iVar2 = FUN_0100ca68(*(unsigned char *)(param_1 + 0x1b));
  if ((*(signed char *)(param_1 + 0x1a) != 0) && (iVar2 != 0) &&
      ((iVar3 = FUN_0100bc04(*(unsigned char *)(param_1 + 0x1b))) == 0)) {
    *(unsigned char *)(param_1 + 0x60) = 1;
    FUN_0100ab14(iVar2, param_1 + 0x61, param_2);
    FUN_0100cbe4(param_1 + 0x61, *(unsigned char *)(param_1 + 0x1b));
  }
  if ((((int)((unsigned int)*(unsigned short *)(param_1 + 2) << 0x1d)) < 0) &&
      ((iVar2 = FUN_0100ca80(*(unsigned char *)(param_1 + 0x1b))) != 0) &&
      ((iVar3 = FUN_0100bbec(*(unsigned char *)(param_1 + 0x1b))) == 0)) {
    *(unsigned char *)(param_1 + 0x6e) = 1;
    puVar1 = (int *)P_010112d8;
    FUN_0100ab14(iVar2, param_1 + 0x6f, param_2);
    FUN_0100e028(*puVar1, param_1 + 0x6f);
    FUN_0100e054(*puVar1, 1);
    return;
  }
  return;
}
