/* readable reconstruction; identity: FUN_01036fcc @ 0x01036fcc
 * public-name: FUN_01036fcc
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103704c                           @ 0x0103704c
 *   rodata_1037050                           @ 0x01037050
 *   rodata_1037054                           @ 0x01037054
 *   rodata_1037058                           @ 0x01037058
 */
/* net-core FUN_01036fcc @ 0x1036fcc  (parity 300 trials PROVEN) */

typedef unsigned char undefined1;
typedef unsigned int undefined4;

extern void FUN_01036f74(int param);
extern void FUN_01039bb0(void *a, int b);
extern void FUN_01039bbe(void *a, void *b, int c);

#define DAT_0103704c (*(int * volatile *)0x103704c)
#define DAT_01037050 (*(void * volatile *)0x1037050)
#define DAT_01037054 (*(void * volatile *)0x1037054)
#define DAT_01037058 (*(int volatile *)0x1037058)

void FUN_01036fcc(int *param_1)
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;

  if (((*(char *)((int)param_1 + 0xd) < 0) || ((*(unsigned char *)((int)param_1 + 0xd) & 0x1f) != 0)) ||
     (param_1[6] != 0)) {
    return;
  }
  *(unsigned char *)((int)param_1 + 0xd) = *(unsigned char *)((int)param_1 + 0xd) | 0x80;
  iVar1 = DAT_01037058;
  if ((void*)param_1 == (void*)DAT_0103704c) {
    FUN_01039bbe(DAT_01037054, DAT_01037050, 0xc1);
    FUN_01039bb0(DAT_01037050, 0xc1);
    for(;;){}
  }
  puVar2 = (undefined4 *)(DAT_01037058 + 0x18);
  puVar3 = (undefined4 *)0x0;
  if ((undefined4 *)*puVar2 != puVar2) {
    puVar3 = (undefined4 *)*puVar2;
  }
  puVar4 = *(undefined4 **)(DAT_01037058 + 0x1c);
  for (; puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)*puVar3) {
    if ((*(char *)((int)param_1 + 0xe) != *(char *)((int)puVar3 + 0xe)) &&
       (*(char *)((int)param_1 + 0xe) < *(char *)((int)puVar3 + 0xe))) {
      puVar2 = (undefined4 *)puVar3[1];
      *param_1 = (int)puVar3;
      param_1[1] = (int)puVar2;
      *puVar2 = (undefined4)(int)param_1;
      puVar3[1] = (undefined4)(int)param_1;
      goto LAB_01037036;
    }
    if (puVar3 == puVar4) break;
  }
  *param_1 = (int)puVar2;
  param_1[1] = (int)puVar4;
  *puVar4 = (undefined4)(int)param_1;
  *(int *)(iVar1 + 0x1c) = (int)param_1;
LAB_01037036:
  FUN_01036f74(0);
  return;
}
