/* Reconstructed update_persist_task_status_to_wait_blow_head @ 0x2c180  (parity: 300/300 trials, PROVEN) */

extern void FUN_00019c70(void);
extern void FUN_00049858(unsigned char);
extern void FUN_0007cdf8(void);
extern int DEBUG_PRINT(int, ...);

unsigned int update_persist_task_status_to_wait_blow_head(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned char *pcVar1 = (unsigned char*)0x20018d9cUL;
  unsigned char *puVar2;
  unsigned char *iVar3;

  while (*pcVar1 != 0) {
    FUN_0007cdf8();
  }
  *pcVar1 = 1;
  if (param_1[0xd5] != 0 && param_1[0xd5] != 1) {
    FUN_00049858(param_1[0xd5]);
  }
  if (*(int*)0x2000230cUL > 0) {
    if (*(int*)0x20007554UL == 0) {
      DEBUG_PRINT(0xa25d9, 0xa25f8, 1, 0, param_4);
    } else {
      FUN_00019c70();
    }
  }
  param_1[0xd5] = 1;
  puVar2 = *(unsigned char**)(param_1 + 0x1054);
  puVar2[0] = 1;
  puVar2[1] = 0;
  puVar2[2] = 0;
  puVar2[3] = 0;
  iVar3 = *(unsigned char**)(param_1 + 0x1054);
  *pcVar1 = 0;
  iVar3[4] = 1;
  return 0;
}

