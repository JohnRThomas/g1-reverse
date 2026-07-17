#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00012c80 @ 0x00012c80
 * public-name: FUN_00012c80
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_dcmplt                           <= FUN_0000dddc @ 0x0000dddc
 *   __aeabi_dcmpgt                           <= FUN_0000de18 @ 0x0000de18
 *   thunk_FUN_00071678                       <= FUN_000807f2 @ 0x000807f2
 * address symbols (name @ address):
 *   g_libm_ieee_mode_flag                    @ 0x200035af
 */
/* Reconstructed FUN_00012c80 @ 0x12c80 */
#include <stdint.h>

extern double FUN_00012db0(uint32_t, uint32_t, uint32_t, uint32_t);
extern int FUN_000869dc(double);
extern int __aeabi_dcmpgt(uint32_t, uint32_t, uint32_t, uint32_t);
extern int __aeabi_dcmplt(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint32_t *thunk_FUN_00071678(void);

double FUN_00012c80(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3,
                    double argument)
{
    double result = FUN_00012db0(r0, r1, r2, r3);
    if (*(volatile int8_t *)((unsigned long)&g_libm_ieee_mode_flag) /*=0x200035af*/ != -1 && FUN_000869dc(argument)) {
        union { double d; uint64_t u; } bits = { .d = argument };
        if (__aeabi_dcmpgt((uint32_t)bits.u, (uint32_t)(bits.u >> 32),
                         0xfefa39efu, 0x40862e42u)) {
            *thunk_FUN_00071678() = 0x22;
            result = 0.0;
        } else if (__aeabi_dcmplt((uint32_t)bits.u, (uint32_t)(bits.u >> 32),
                                0xd52d3051u, 0xc0874910u)) {
            *thunk_FUN_00071678() = 0x22;
            result = 0.0;
        }
    }
    return result;
}
