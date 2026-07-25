/* Reconstructed start_ancs_work_thread @ 0x198cc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(int,...);
extern int FUN_000167a8(void);
extern int FUN_00019c70(void);
extern int FUN_00032ee4(void);
/* CONFIG_TIMEOUT_64BIT: z_impl_k_thread_create's 10th parameter is a
 * 64-bit k_timeout_t delay, AAPCS-placed 8-byte aligned at sp+0x18.
 * The original writes it (strd r,r,[sp,#0x18]); it must be passed. */
extern int FUN_00071eac(unsigned,unsigned,int,unsigned,unsigned,int,int,int,int,unsigned long long);
void start_ancs_work_thread(unsigned param_1){
  char* pcVar1; int iVar2;
  pcVar1 = (char*)FUN_000167a8();
  if((*(unsigned char*)pcVar1==2) && (iVar2=FUN_00032ee4(), iVar2!=1)){
    FUN_00071eac(0x20003c50, 0x2001d568, 0x1400, 0x19719, param_1, 0,0,0xfffffff5,0,0ULL);
    if(2 < *(volatile int*)0x2000230cUL){
      if(*(volatile int*)0x20007554UL != 0){
        FUN_00019c70();
        return;
      }
      DEBUG_PRINT(0x9af2e, 0x9b0f1);
      return;
    }
  }
  return;
}

