/* Reconstructed FUN_0008688e @ 0x8688e  (parity: 300/300 trials, PROVEN) */

extern void signal_poll_event(void);
void z_handle_obj_poll_events(int *param_1)
{
  int *piVar1 = (int *)*(volatile int *)param_1;
  if (param_1 != piVar1) {
    int iVar3 = *(volatile int *)piVar1;
    int *piVar2 = (int *)*(volatile int *)(piVar1 + 1);
    *(volatile int *)piVar2 = iVar3;
    *(volatile int *)(iVar3 + 4) = (int)piVar2;
    *(volatile int *)piVar1 = 0;
    *(volatile int *)(piVar1 + 1) = 0;
    signal_poll_event();
  }
}

