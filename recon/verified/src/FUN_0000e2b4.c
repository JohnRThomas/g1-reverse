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

extern void FUN_00086c78(void *workspace, uint32_t value, uint32_t size);
extern void FUN_0000e53c(float sample_0, float sample_1, float sample_2,
                         float charge_high, float charge_low,
                         const interpolation_table_t *table,
                         uint32_t sample_count, void *workspace,
                         float *result);

int FUN_0000e2b4(const fuel_curve_request_t *request, float *result)
{
    interpolation_table_t table;
    float interpolated;

    if (request == 0 || request->sample_count == 0)
        return -22;

    FUN_00086c78((void *)0x2000b4a4u, 0, 0x1778u);
    table = *(const interpolation_table_t *)0x00088570u;

    FUN_0000e53c(request->sample_0, request->sample_1, request->sample_2,
                 *(volatile float *)0x20002d18u,
                 *(volatile float *)0x20002d14u,
                 &table, request->sample_count, (void *)0x2000b4a4u,
                 &interpolated);
    if (result != 0)
        *result = interpolated;

    return 0;
}
