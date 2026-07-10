/* Reconstructed FUN_00082bb8 @ 0x82bb8  (parity: 300/300 trials, PROVEN) */

extern int set_change_aware_no_store(void);
extern void FUN_00059d24(unsigned char,unsigned char*,unsigned int);
void set_change_aware(unsigned char *param_1)
{
  int iVar1 = set_change_aware_no_store();
  if (iVar1 != 0) {
    FUN_00059d24(*(volatile unsigned char *)param_1, param_1 + 1, 1);
  }
}

