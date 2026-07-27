/* Reconstructed FUN_0004f564 @ 0x4f564  (parity: 300/300 trials, PROVEN) */

extern void FUN_0004d944(void);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(unsigned long, unsigned long);
extern int FUN_000868c2(void);

void FUN_0004f564(int param_1,int param_2,int param_3,int param_4)
{
  int iVar1;
  iVar1 = FUN_000868c2();
  if (iVar1 == 0) {
    FUN_0004d944();
    FUN_0007e2fa(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"0"), ((unsigned long)"WEST_TOPDIR/nrf/subsys/app_event_manager/app_event_manager.c"), 123);
    FUN_0007e2ec(((unsigned long)"WEST_TOPDIR/nrf/subsys/app_event_manager/app_event_manager.c"), 123);
  }
}

