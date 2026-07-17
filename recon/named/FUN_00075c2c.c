/* readable reconstruction; identity: FUN_00075c2c @ 0x00075c2c
 * public-name: FUN_00075c2c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   thunk_FUN_00071678                       <= FUN_000807f2 @ 0x000807f2
 * address symbols (name @ address):
 *   rodata_a8ea0                             @ 0x000a8ea0
 *   g_libm_ieee_mode_flag                    @ 0x200035af
 */
/* Reconstructed FUN_00075c2c @ 0x75c2c  (parity: 300/300 trials, PROVEN) */
extern float FUN_00075f88(void);
extern float FUN_000868ee(float);
extern int *thunk_FUN_00071678(void);
extern float FUN_00076a88(unsigned int descriptor);

float FUN_00075c2c(float value)
{
    float fallback = FUN_00075f88();

    if (*(volatile signed char *)0x200035afUL != -1 && value == value) {
        float converted = FUN_000868ee(value);
        if (converted > 1.0f) {
            int *error_number = thunk_FUN_00071678();
            *error_number = 0x21;
            return FUN_00076a88(0x000a8ea0u);
        }
    }
    return fallback;
}
