/* Reconstructed start_ancs_work_thread @ 0x198cc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_00032ee4(void);
extern int FUN_00071eac(unsigned,unsigned,int,unsigned,unsigned,int,int,int,int);
void start_ancs_work_thread(unsigned param_1){
  char* pcVar1; int iVar2;
  pcVar1 = (char*)FUN_000167a8();
  if((*(unsigned char*)pcVar1==2) && (iVar2=FUN_00032ee4(), iVar2!=1)){
    FUN_00071eac(0x20003c50, 0x2001d568, 0x1400, 0x19719, param_1, 0,0,0xfffffff5,0);
    if(2 < *(volatile int*)0x2000230cUL){
      if(*(volatile int*)0x20007554UL != 0){
        FUN_00019c70(0x9af2e, 0x9b0f1);
        return;
      }
      DEBUG_PRINT(0x9af2e, 0x9b0f1);
      return;
    }
  }
  return;
}

