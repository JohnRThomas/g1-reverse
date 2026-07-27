#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00075d5c @ 0x00075d5c
 * public-name: log10f
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log10f                                   <= FUN_00075d5c @ 0x00075d5c
 *   __ieee754_log10f                         <= FUN_00076718 @ 0x00076718
 *   nanf                                     <= FUN_00076a88 @ 0x00076a88
 *   thunk_FUN_00071678                       <= FUN_000807f2 @ 0x000807f2
 * address symbols (name @ address):
 *   rodata_a8ea0                             @ 0x000a8ea0
 *   g_libm_ieee_mode_flag                    @ 0x200035af
 */
/* Reconstructed FUN_00075d5c @ 0x75d5c  (parity: 300/300 trials, PROVEN) */

extern float __ieee754_log10f(void);
extern int *thunk_FUN_00071678(void);
extern float nanf(const char *);
float log10f(float param_1){
  float result = __ieee754_log10f();
  if((*(signed char*)((unsigned long)&g_libm_ieee_mode_flag) /*=0x200035af*/ != -1) && (param_1 <= 0.0f)){
    if(param_1 != 0.0f){
      unsigned *error = thunk_FUN_00071678();
      *error = 0x21;
      return nanf(((unsigned long)&rodata_a8ea0) /*=0xa8ea0*/);
    }
    unsigned *error = thunk_FUN_00071678();
    *error = 0x22;
    return -__builtin_inff();
  }
  return result;
}
