/* Reconstructed FUN_00058bfc @ 0x58bfc  (parity: 300/300 trials, PROVEN) */
extern void FUN_00081c22(int*);
extern void FUN_000732d4(int,int);
extern void ext5c6c8(int);
void FUN_00058bfc(int *param_1){
  *(volatile unsigned*)((char*)param_1+0x118) |= 4;
  FUN_00081c22(param_1 - 2);
  FUN_000732d4((int)(param_1 + 0x56), 0x00059921);
  ext5c6c8(*param_1);
}

