/* readable reconstruction; identity: FUN_0002ea28 @ 0x0002ea28
 * public-name: fuel_gauge_sample_init_timestamp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fuel_gauge_read_voltage_current_temp     <= FUN_0002e988 @ 0x0002e988
 *   fuel_gauge_sample_init_timestamp         <= FUN_0002ea28 @ 0x0002ea28
 *   k_uptime_get_3                           <= FUN_0007ceda @ 0x0007ceda
 *   sensor_channel_get_trampoline            <= FUN_0007cef6 @ 0x0007cef6
 * address symbols (name @ address):
 *   g_fuel_gauge_init_timestamp              @ 0x20004790
 */
/* Reconstructed FUN_0002ea28 @ 0x2ea28  (parity: 300/300 trials, PROVEN) */

extern int FUN_0000e2b4(void*, int);
extern int fuel_gauge_read_voltage_current_temp(int, void*, void*, void*);
extern unsigned long long k_uptime_get_3(void);
extern void sensor_channel_get_trampoline(int, int, void*);

int fuel_gauge_sample_init_timestamp(int param_1)
{
    struct {
        unsigned char event[8];
        int first;
        int second;
        int third;
    } frame;
    int iVar1;

    frame.first = 0;
    frame.second = 0;
    frame.third = 0;
    iVar1 = fuel_gauge_read_voltage_current_temp(param_1, &frame.first, &frame.second, &frame.third);
    if (iVar1 >= 0) {
        sensor_channel_get_trampoline(param_1, 0x39, frame.event);
        iVar1 = FUN_0000e2b4(&frame.first, 0);
        if (iVar1 >= 0) {
            unsigned long long uVar2 = k_uptime_get_3();
            *(volatile unsigned long long*)0x20004790UL = uVar2;
            iVar1 = 0;
        }
    }
    return iVar1;
}
