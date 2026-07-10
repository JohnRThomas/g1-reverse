/* Reconstructed set_shutdown_flag @ 0x7cbfe  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0002bed0(void);
extern void FUN_0002c0e8(int);
extern void FUN_0002efc0(void);
extern void FUN_0007ce60(int);
extern void FUN_00086c78(int,int,int);
extern void send_event_status(int);
void set_shutdown_flag(int param_1, int param_2)
{
  int iVar1; char *pcVar2; char cVar3;
  iVar1 = FUN_0002bed0();
  if (iVar1 == 0) return;
  if ((*(volatile char*)(*(int*)(param_1+0x1004)+6) != 0) ||
      (cVar3 = *(volatile char*)(*(int*)(param_1+0x1008)+6), cVar3 != 0)) {
    FUN_0002efc0();
    FUN_00086c78(*(int*)(param_1+0x1008)+6, 0, 400);
    FUN_00086c78(*(int*)(param_1+0x1004)+6, 0, 400);
    cVar3 = 1;
  }
  if (**(char**)(param_1+0x1000) != 0) { **(volatile char**)(param_1+0x1000) = 0; cVar3 = 1; }
  if (*(char*)(*(int*)(param_1+0xffc)+1) != 0) { FUN_0002efc0(); *(volatile char*)(*(int*)(param_1+0xffc)+1) = 0; cVar3 = 1; }
  if (**(char**)(param_1+0x1020) != 0) { FUN_0002efc0(); **(volatile char**)(param_1+0x1020) = 0; cVar3 = 1; }
  if (*(char*)(param_1+0xd5) == 6) { cVar3 = 1; }
  else if (*(char*)(param_1+0xd5) == 4) { cVar3 = 1; }
  if (**(char**)(param_1+0x1014) != 0) { **(volatile char**)(param_1+0x1014) = 0; cVar3 = 1; }
  if (**(char**)(param_1+0x1018) != 0) { **(volatile char**)(param_1+0x1018) = 0; cVar3 = 1; }
  if (*(char*)(*(int*)(param_1+0x100c)+7) == 0) {
    pcVar2 = *(char**)(param_1+0x101c);
    if (*pcVar2 == 0) {
      if (cVar3 == 0) return;
      goto LAB;
    }
  } else {
    FUN_0002efc0();
    FUN_0007ce60(1);
    pcVar2 = *(char**)(param_1+0x101c);
    if (*pcVar2 == 0) goto LAB;
  }
  *(volatile char*)pcVar2 = 0;
LAB:
  if (param_2 != 0) send_event_status(0);
  FUN_0002c0e8(param_1);
  FUN_00086c78(param_1+0xef, 0, 0x5dc);
  return;
}

