/* named: cjson_create_bool */
/* globals referenced:
//   0x20002bac  g_cjson_hooks                
*/
/* Reconstructed cjson_create_bool @ 0x64c3c  (parity: 300/300 trials, PROVEN) */

extern int alloc_zeroed_node(unsigned int);
void cjson_create_bool(int param_1)
{
  int iVar1;
  unsigned int uVar2;
  iVar1 = alloc_zeroed_node(*(volatile unsigned int *)0x20002bacUL);
  if (iVar1 != 0) {
    if (param_1 == 0) {
      uVar2 = 1;
    } else {
      uVar2 = 2;
    }
    *(volatile unsigned int *)(iVar1 + 0xc) = uVar2;
  }
}

