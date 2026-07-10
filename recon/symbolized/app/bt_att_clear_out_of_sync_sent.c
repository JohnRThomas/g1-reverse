#include "g1_app_symbols.h"
/* named: bt_att_clear_out_of_sync_sent */
/* Reconstructed bt_att_clear_out_of_sync_sent @ 0x82572  (parity: 300/300 trials, PROVEN) */

extern int att_get(void);
extern void atomic_clear_bit_0(int *a, int b);
void bt_att_clear_out_of_sync_sent(void)
{
  int iVar1;
  int *piVar2;

  iVar1 = att_get();
  if (iVar1 != 0) {
    for (piVar2 = *(volatile int **)(iVar1 + 0x30); piVar2 != (int *)0; piVar2 = (int *)*(volatile int *)piVar2) {
      atomic_clear_bit_0(piVar2 + -0x1c, 5);
    }
  }
}

