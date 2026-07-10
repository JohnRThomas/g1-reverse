/* named: init_nfc_comm */
/* globals referenced:
//   0x20007a44  g_st25dv_dev                 
*/
/* Reconstructed init_nfc_comm @ 0x2560c  (parity: 300/300 trials, PROVEN) */

extern int FUN_000330a8(unsigned int a0);
extern int process_pt_data(void);
extern void DEBUG_PRINT(unsigned int a0);

int init_nfc_comm(void)
{
  int iVar1;
  iVar1 = FUN_000330a8(*(volatile unsigned int*)0x20007a44UL);
  if (iVar1 == 0) {
    iVar1 = process_pt_data();
    if (iVar1 != 0) { iVar1 = -2; }
  } else {
    DEBUG_PRINT(0x0009f196);
    iVar1 = -1;
  }
  return iVar1;
}

