/* Reconstructed dequeue_uid @ 0x18ff8  (parity: 300/300 trials, PROVEN) */

extern int FUN_00072240(unsigned int a, void *b, unsigned int c, unsigned int d);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

int dequeue_uid(unsigned int *param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;
  struct uid_record {
    unsigned int first;
    unsigned int second;
  } record;

  record.first = 0;
  record.second = 0;
  (void)param_2;
  (void)param_3;
  if (*(volatile int *)(0x20006a38UL + 0x10) == 0) {
    iVar1 = 1;
  } else {
    iVar1 = FUN_00072240(0x20006a38UL, &record, 0, 0);
    if (iVar1 == 0) {
      *param_1 = record.first;
      param_1[1] = record.second;
    } else if (0 < *(volatile int *)0x2000230cUL) {
      if (*(volatile int *)0x20007554UL == 0) {
        DEBUG_PRINT(0x9aafd, 0x9b16a);
      } else {
        FUN_00019c70(0x9aafd, 0x9b16a);
      }
    }
  }
  return iVar1;
}
