#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0000e2b4 @ 0x0000e2b4
 * public-name: batt_soc_curve_estimate
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   batt_soc_curve_estimate                  <= FUN_0000e2b4 @ 0x0000e2b4
 *   battery_soc_curve_model_init             <= FUN_0000e53c @ 0x0000e53c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_88570                             @ 0x00088570
 *   g_batt_soc_curve_charge_lo               @ 0x20002d14
 *   g_batt_soc_curve_charge_hi               @ 0x20002d18
 *   g_batt_soc_curve_interp_buf              @ 0x2000b4a4
 */
/* Full ABI-faithful reconstruction @ 0x0000e2b4, exact extent 122 bytes.
 * CFG_VERIFY_CALL_ARITIES=3,4
 */
#include <stdint.h>

typedef struct {
    float sample_0;
    float sample_1;
    float sample_2;
    uint32_t sample_count;
} fuel_curve_request_t;

typedef struct {
    uint32_t word[16];
} interpolation_table_t;

extern void memset_bytes(void*, int, int);
extern void battery_soc_curve_model_init(float, float, float, float, float, const void*, const float*, volatile float*, float*);

int batt_soc_curve_estimate(const fuel_curve_request_t *request, float *result)
{
    interpolation_table_t table;
    float interpolated;

    if (request == 0 || request->sample_count == 0)
        return -22;

    memset_bytes((void *)((unsigned long)&g_batt_soc_curve_interp_buf) /*=0x2000b4a4*/, 0, 0x1778u);
    table = *(const interpolation_table_t *)((unsigned long)&rodata_88570) /*=0x88570*/;

    battery_soc_curve_model_init(request->sample_0, request->sample_1, request->sample_2,
                 *(volatile float *)((unsigned long)&g_batt_soc_curve_charge_hi) /*=0x20002d18*/,
                 *(volatile float *)((unsigned long)&g_batt_soc_curve_charge_lo) /*=0x20002d14*/,
                 &table, request->sample_count, (void *)((unsigned long)&g_batt_soc_curve_interp_buf) /*=0x2000b4a4*/,
                 &interpolated);
    if (result != 0)
        *result = interpolated;

    return 0;
}
