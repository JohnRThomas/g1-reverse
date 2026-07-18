/* readable reconstruction; identity: FUN_0103aff2 @ 0x0103aff2
 * public-name: FUN_0103aff2
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   virtqueue_get_available_buffer           <= FUN_0103ac50 @ 0x0103ac50
 */
/* net-core FUN_0103aff2 @ 0x103aff2  (parity 300 trials PROVEN) */

extern int FUN_0103aec6(int a);
extern void thunk_FUN_01036824(int a);
extern int *virtqueue_get_available_buffer(int a, void *b, int *c, int d, int e);
extern int FUN_0103ac46(int a);
extern void FUN_01037c64(int a, int b);

typedef int (*fnptr_t)(void *);

int *FUN_0103aff2(int param_1, int *param_2, int param_3)
{
  int iVar2 = param_1;
  int iVar1;
  int iVar4;
  int *piVar3, *piVar5;
  int addrA;
  unsigned short hword;
  void *obj, *p1;
  fnptr_t fn;

  obj = *(void **)(param_1 + 0xa0);
  p1 = *(void **)((char *)obj + 0x20);
  fn = *(fnptr_t *)((char *)p1 + 8);
  iVar1 = fn(obj);
  if (-1 < (iVar1 << 0x1d)) {
    return (int *)0;
  }
  if (param_3 != 0) {
    param_3 = 15000;
  }
  addrA = param_1 + 0x58;
  for (;;) {
    FUN_0103aec6(addrA);
    piVar5 = *(int **)(param_1 + 0xb4);
    iVar4 = *(int *)(*(int *)(param_1 + 0xa0) + 0x18);
    if (piVar5 != (int *)(param_1 + 0xb4) && piVar5 != (int *)0) {
      break;
    }
    if (iVar4 == 1) {
      piVar5 = virtqueue_get_available_buffer(*(int *)(param_1 + 0xa8), &hword, param_2, 1, iVar2);
      thunk_FUN_01036824(addrA);
      if (piVar5 != (int *)0) {
        goto LAB_0103b052;
      }
    } else {
      thunk_FUN_01036824(addrA);
    }
    if (param_3 == 0) {
      return (int *)0;
    }
    FUN_01037c64(0x21, 0);
    param_3 = param_3 - 1;
  }
  piVar3 = (int *)piVar5[1];
  *(int **)(*piVar5 + 4) = piVar3;
  *piVar3 = *piVar5;
  *piVar5 = (int)piVar5;
  piVar5[1] = (int)piVar5;
  if (iVar4 == 1) {
    hword = (unsigned short)piVar5[2];
    iVar2 = FUN_0103ac46(*(int *)(param_1 + 0xa8));
    *param_2 = iVar2;
  }
  thunk_FUN_01036824(addrA);
LAB_0103b052:
  piVar5[2] = (unsigned int)hword;
  *param_2 = *param_2 + -0x10;
  return piVar5 + 4;
}
