/* readable reconstruction; identity: FUN_00015f80 @ 0x00015f80
 * public-name: power_for_imu_and_mic
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 * address symbols (name @ address):
 *   rodata_9945a                             @ 0x0009945a
 *   rodata_99c28                             @ 0x00099c28
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed power_for_imu_and_mic @ 0x15f80  (parity: 300/300 trials, PROVEN) */

extern int dev_write_reg3(unsigned int,unsigned int,unsigned int,unsigned int);
extern void log_message(unsigned int,...);
extern void debug_print(unsigned int,...);

unsigned int power_for_imu_and_mic(void)
{
    int iVar1 = dev_write_reg3(
        *(volatile unsigned int *)(*(volatile unsigned int *)(0x00087ce0 + 4) + 0x1c),
        8, 2, 1);
    if (*(volatile int*)0x2000230cUL < 1) {
        return 0;
    }
    int flag = *(volatile int*)0x20007554UL;
    if (flag == 0) {
        log_message(iVar1 < 0 ? 0x0009945a : 0x00099476, 0x00099c28);
    } else {
        debug_print(iVar1 < 0 ? 0x0009945a : 0x00099476, 0x00099c28);
    }
    return 0;
}
