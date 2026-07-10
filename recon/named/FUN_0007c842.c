/* named: FUN_0007c842 */
/* Reconstructed FUN_0007c842 @ 0x7c842  (parity: 300/300 trials, PROVEN) */

extern int get_box_field_state(void);
void FUN_0007c842(int param_1)
{
  int iVar1 = get_box_field_state();
  unsigned char uVar2;
  if (iVar1 == 1) { uVar2 = 4; }
  else if (iVar1 == 0) { uVar2 = 1; }
  else { uVar2 = 2; }
  *(volatile unsigned char *)(param_1 + 2) = uVar2;
}

