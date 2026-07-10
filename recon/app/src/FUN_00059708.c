/* Reconstructed FUN_00059708 @ 0x59708  (parity: 300/300 trials, PROVEN) */

extern void FUN_0005833c(int a);
extern void FUN_0005f24c(int a);
extern void FUN_00071cf4(int a, int b);
void FUN_00059708(int param_1)
{
  if (*(volatile int *)(param_1 + 8) != 0) {
    FUN_0005833c(*(volatile int *)(*(volatile int *)(param_1 + 8) + 0x18));
    FUN_0005f24c(*(volatile int *)(param_1 + 8));
    *(volatile int *)(param_1 + 8) = 0;
  }
  FUN_00071cf4(0x20003798, param_1);
}

