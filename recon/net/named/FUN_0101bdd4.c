/* readable reconstruction; identity: FUN_0101bdd4 @ 0x0101bdd4
 * public-name: FUN_0101bdd4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c290                           @ 0x0103c290
 *   g_net_conn_teardown_busy_flag            @ 0x2100111c
 */
/* net-core FUN_0101bdd4 @ 0x101bdd4  (parity 300 trials PROVEN) */
extern void FUN_01008d00(unsigned int, unsigned int);
extern void FUN_0100f48c(int, unsigned int, int);
extern void FUN_0101b7e4(void*, int, int, int);
extern void FUN_01020634(void);
extern int FUN_010209f0(unsigned char);
extern void FUN_01022a84(void);
extern int FUN_010231c8(unsigned char, void*);

#define DAT_0101bee4 0x0103c290u
#define DAT_0101bee8 0x10624dd3u
#define DAT_0101beec 0x2100111cu

void FUN_0101bdd4(int param_1, unsigned int param_2)
{
  unsigned char bVar1;
  unsigned short uVar2;
  unsigned long long lVar3;
  int iVar4;
  int iVar5;
  unsigned char auStack_28[24];

  switch (param_2) {
  case 0:
    if (*(volatile char *)DAT_0101beec == 0) {
      FUN_0101b7e4(auStack_28, param_1, 1, 0);
      iVar4 = FUN_010231c8(*(volatile unsigned char *)(param_1 + 0x301), auStack_28);
      if (iVar4 == 0) {
        FUN_01008d00(0x35, 0x2d4);
        return;
      }
      *(volatile short *)(param_1 + 0xbc) = *(volatile short *)(param_1 + 0xbc) + 1;
      goto LAB_0101bdee;
    }
  case 2:
    *(volatile unsigned char *)(param_1 + 0x300) = 4;
LAB_0101bdee:
    FUN_01020634();
    FUN_01022a84();
    return;
  case 1:
    *(volatile unsigned char *)(param_1 + 0x300) = 3;
    return;
  case 3:
    *(volatile unsigned int *)(param_1 + 0x24) = *(volatile unsigned int *)(param_1 + 0x324);
    iVar4 = DAT_0101bee4;
    bVar1 = *(volatile unsigned char *)(param_1 + 0x6f);
    *(volatile unsigned int *)(param_1 + 0x308) = *(volatile unsigned int *)(param_1 + 0x14);
    *(volatile unsigned short *)(param_1 + 0x28) = *(volatile unsigned short *)(param_1 + 800);
    uVar2 = *(volatile unsigned short *)(iVar4 + (unsigned int)*(volatile unsigned char *)(param_1 + 0x6e) * 2);
    *(volatile unsigned int *)(param_1 + 0x14) = *(volatile unsigned int *)(param_1 + 0x328);
    *(volatile unsigned int *)(param_1 + 0x1c) = *(volatile unsigned int *)(param_1 + 0x32c);
    iVar4 = FUN_010209f0(bVar1);
    if ((bVar1 & 0xc) == 0) {
      iVar5 = 0;
    } else {
      iVar5 = 0x28;
    }
    lVar3 = (unsigned long long)DAT_0101bee8 * (unsigned long long)(unsigned int)(uVar2 + 0x79d + iVar4);
    FUN_0100f48c(param_1, iVar5 + (unsigned int)(lVar3 >> 0x26) + 199, (int)lVar3);
    *(volatile unsigned char *)(param_1 + 0x300) = 2;
    return;
  case 4:
    bVar1 = *(volatile unsigned char *)(param_1 + 0x6f);
    uVar2 = *(volatile unsigned short *)(DAT_0101bee4 + (unsigned int)*(volatile unsigned char *)(param_1 + 0x6e) * 2);
    iVar4 = FUN_010209f0(bVar1);
    if ((bVar1 & 0xc) == 0) {
      iVar5 = 0;
    } else {
      iVar5 = 0x28;
    }
    lVar3 = (unsigned long long)DAT_0101bee8 * (unsigned long long)(unsigned int)(uVar2 + 0x79d + iVar4);
    FUN_0100f48c(param_1, iVar5 + (unsigned int)(lVar3 >> 0x26) + 199, (int)lVar3);
    return;
  default:
    FUN_01008d00(0x35, 0x329);
    return;
  }
}
