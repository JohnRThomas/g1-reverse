/* Reconstructed FUN_00075d5c @ 0x75d5c  (parity: 300/300 trials, PROVEN) */

extern float FUN_00076718(void);
extern unsigned* FUN_000807f2(void);
extern float FUN_00076a88(unsigned);
float FUN_00075d5c(float param_1){
  float result = FUN_00076718();
  if((*(signed char*)0x200035afUL != -1) && (param_1 <= 0.0f)){
    if(param_1 != 0.0f){
      unsigned *error = FUN_000807f2();
      *error = 0x21;
      return FUN_00076a88(0x000a8ea0);
    }
    unsigned *error = FUN_000807f2();
    *error = 0x22;
    return -__builtin_inff();
  }
  return result;
}
