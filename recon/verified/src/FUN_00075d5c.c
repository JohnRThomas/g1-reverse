/* Reconstructed FUN_00075d5c @ 0x75d5c  (parity: 300/300 trials, PROVEN) */

extern unsigned* FUN_00076718(void);
extern unsigned* thunk_FUN_00071678(void);
extern unsigned* FUN_00076a88(void);
unsigned* FUN_00075d5c(float param_1){
  unsigned* puVar1 = FUN_00076718();
  if((*(signed char*)0x200035afUL != -1) && (param_1 <= 0.0f)){
    if(param_1 != 0.0f){
      puVar1 = thunk_FUN_00071678();
      *puVar1 = 0x21;
      return FUN_00076a88();
    }
    puVar1 = thunk_FUN_00071678();
    *puVar1 = 0x22;
  }
  return puVar1;
}

