/* named: sbrk_impl */
/* globals referenced:
//   0x2000a808  g_heap_brk                   
//   0x2005314c  g_heap_base                  
*/
/* Reconstructed sbrk_impl @ 0x51074  (parity: 300/300 trials, PROVEN) */

int sbrk_impl(int param_1)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  iVar1 = 0x2005314c;
  uVar3 = *(volatile unsigned int*)0x2000a808UL;
  uVar2 = (unsigned int)param_1 + uVar3;
  if (uVar2 < (unsigned int)(0x20070000UL - 0x2005314cUL)) {
    *(volatile unsigned int*)0x2000a808UL = uVar2;
    iVar1 = iVar1 + uVar3;
  } else {
    iVar1 = -1;
  }
  return iVar1;
}

