/* named: get_active_message_count */
/* globals referenced:
//   0x20007dac  g_message_pool               
//   0x2001a22a  g_message_pool_index         
*/
/* Reconstructed get_active_message_count @ 0x33cb0  (parity: 300/300 trials, PROVEN) */

unsigned int get_active_message_count(void)
{
  unsigned char uVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  int iVar4;

  uVar2 = 9;
  iVar4 = 0x20007dac;
  do {
    if (*(volatile char *)(iVar4 + 0xf63) != 0) {
      uVar3 = uVar2 & 0xff;
      uVar1 = (unsigned char)uVar2;
      goto LAB_00033cc6;
    }
    uVar2 = uVar2 - 1;
    iVar4 = iVar4 + -0x1b4;
  } while (uVar2 != 0xffffffff);
  uVar3 = 0xff;
  uVar1 = 0;
LAB_00033cc6:
  *(volatile unsigned char *)0x2001a22aUL = uVar1;
  return uVar3;
}

