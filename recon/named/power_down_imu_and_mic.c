/* readable reconstruction; identity: FUN_000160b4 @ 0x000160b4
 * public-name: power_down_imu_and_mic
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 * address symbols (name @ address):
 *   rodata_9945a                             @ 0x0009945a
 *   rodata_99c00                             @ 0x00099c00
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed power_down_imu_and_mic @ 0x160b4  (parity: 300/300 trials, PROVEN) */

extern int dev_write_reg3(unsigned int,unsigned int,unsigned int,unsigned int);
extern void DEBUG_PRINT(unsigned int,...);
extern void debug_print(unsigned int,...);

unsigned int power_down_imu_and_mic(void)
{
    int iVar1 = dev_write_reg3(
        *(volatile unsigned int *)(*(volatile unsigned int *)(0x00087ce0 + 4) + 0x1c),
        8, 3, 1);
    if (*(volatile int*)0x2000230cUL < 1) {
        return 0;
    }
    int flag = *(volatile int*)0x20007554UL;
    if (flag == 0) {
        DEBUG_PRINT(iVar1 < 0 ? 0x0009945a : 0x000994f7, 0x00099c00);
    } else {
        debug_print(iVar1 < 0 ? 0x0009945a : 0x000994f7, 0x00099c00);
    }
    return 0;
}
