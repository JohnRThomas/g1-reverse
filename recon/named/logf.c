/* readable reconstruction; identity: FUN_00075d5c @ 0x00075d5c
 * public-name: logf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   logf                                     <= FUN_00075d5c @ 0x00075d5c
 *   log2f                                    <= FUN_00076718 @ 0x00076718
 *   nanf                                     <= FUN_00076a88 @ 0x00076a88
 *   thunk_FUN_00071678                       <= FUN_000807f2 @ 0x000807f2
 * address symbols (name @ address):
 *   rodata_a8ea0                             @ 0x000a8ea0
 *   g_libm_ieee_mode_flag                    @ 0x200035af
 */
/* Reconstructed FUN_00075d5c @ 0x75d5c  (parity: 300/300 trials, PROVEN) */

extern float log2f(void);
extern unsigned* thunk_FUN_00071678(void);
extern float nanf(unsigned);
float logf(float param_1){
  float result = log2f();
  if((*(signed char*)0x200035afUL != -1) && (param_1 <= 0.0f)){
    if(param_1 != 0.0f){
      unsigned *error = thunk_FUN_00071678();
      *error = 0x21;
      return nanf(0x000a8ea0);
    }
    unsigned *error = thunk_FUN_00071678();
    *error = 0x22;
    return -__builtin_inff();
  }
  return result;
}
