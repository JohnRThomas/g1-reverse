#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00075c2c @ 0x00075c2c
 * public-name: asinf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   asinf                                    <= FUN_00075c2c @ 0x00075c2c
 *   __ieee754_asinf                          <= FUN_00075f88 @ 0x00075f88
 *   nanf                                     <= FUN_00076a88 @ 0x00076a88
 *   thunk_FUN_00071678                       <= FUN_000807f2 @ 0x000807f2
 *   fabsf                                    <= FUN_000868ee @ 0x000868ee
 * address symbols (name @ address):
 *   rodata_a8ea0                             @ 0x000a8ea0
 *   g_libm_ieee_mode_flag                    @ 0x200035af
 */
/* Reconstructed FUN_00075c2c @ 0x75c2c  (parity: 300/300 trials, PROVEN) */
extern float __ieee754_asinf(void);
extern float fabsf(float);
extern int *thunk_FUN_00071678(void);
extern float nanf(unsigned int descriptor);

float asinf(float value)
{
    float fallback = __ieee754_asinf();

    if (*(volatile signed char *)((unsigned long)&g_libm_ieee_mode_flag) /*=0x200035af*/ != -1 && value == value) {
        float converted = fabsf(value);
        if (converted > 1.0f) {
            int *error_number = thunk_FUN_00071678();
            *error_number = 0x21;
            return nanf(((unsigned long)&rodata_a8ea0) /*=0xa8ea0*/);
        }
    }
    return fallback;
}
