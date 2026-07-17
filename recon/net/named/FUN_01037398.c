/* readable reconstruction; identity: FUN_01037398 @ 0x01037398
 * public-name: FUN_01037398
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103eb0e                           @ 0x0103eb0e
 *   g_zephyr_sched_thread_field              @ 0x21004b40
 */
/* net-core FUN_01037398 @ 0x1037398  (parity 300 trials PROVEN) */
#define P_01037424 0x21004b40
#define P_01037428 0x210043a8
#define P_0103742c 0x0103eb0e
#define P_01037430 0x0103d2a7
#define P_01037434 0x21004b28

extern void FUN_01036f74(int);
extern void FUN_0103735c(int, int *);
extern void FUN_01039bbe(int, int, unsigned int);
extern void FUN_01039bb0(int, unsigned int);

void FUN_01037398(int *param_1)
{
  int iVar1;
  unsigned int *puVar2;
  unsigned int *puVar3;
  unsigned int *puVar4;

  if (*(signed char *)((int)param_1 + 0xd) < 0) {
    *(unsigned char *)((int)param_1 + 0xd) = *(unsigned char *)((int)param_1 + 0xd) & 0x7f;
    FUN_0103735c(P_01037424, param_1);
  }
  *(unsigned char *)((int)param_1 + 0xd) = *(unsigned char *)((int)param_1 + 0xd) | 0x80;
  iVar1 = P_01037434;
  if (param_1 == (int *)P_01037428) {
    FUN_01039bbe(P_01037430, P_0103742c, 0xc1);
    FUN_01039bb0(P_0103742c, 0xc1);
    return;
  }
  puVar3 = (unsigned int *)(P_01037434 + 0x18);
  puVar4 = (unsigned int *)*puVar3;
  puVar2 = *(unsigned int **)(P_01037434 + 0x1c);
  if (puVar4 == puVar3) {
    puVar4 = (unsigned int *)0;
  }
  for (; puVar4 != (unsigned int *)0; puVar4 = (unsigned int *)*puVar4) {
    if ((*(signed char *)((int)param_1 + 0xe) != *(signed char *)((int)puVar4 + 0xe)) &&
        (*(signed char *)((int)param_1 + 0xe) < *(signed char *)((int)puVar4 + 0xe))) {
      puVar3 = (unsigned int *)puVar4[1];
      *param_1 = (int)puVar4;
      param_1[1] = (int)puVar3;
      *puVar3 = (unsigned int)param_1;
      puVar4[1] = (unsigned int)param_1;
      goto LAB_end;
    }
    if (puVar2 == puVar4) break;
  }
  *param_1 = (int)puVar3;
  param_1[1] = (int)puVar2;
  *puVar2 = (unsigned int)param_1;
  *(int **)(iVar1 + 0x1c) = param_1;
LAB_end:
  FUN_01036f74((*(int **)(iVar1 + 8) == param_1) ? 1 : 0);
  return;
}
