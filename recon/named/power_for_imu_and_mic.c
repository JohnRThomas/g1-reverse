/* readable reconstruction; identity: FUN_00015f80 @ 0x00015f80
 * public-name: power_for_imu_and_mic
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 * address symbols (name @ address):
 *   rodata_9945a                             @ 0x0009945a   [INLINED -- G6 literal batch]
 *   rodata_99c28                             @ 0x00099c28   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
#include "../headers/g1_log.h"
/* Reconstructed power_for_imu_and_mic @ 0x15f80  (parity: 300/300 trials, PROVEN) */

extern int dev_write_reg3(unsigned int,unsigned int,unsigned int,unsigned int);

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
        log_message(iVar1 < 0 ? ((unsigned long)"%s(): Could not set ldsw2.\n") : ((unsigned long)"%s(): enable ldsw2 for imu and mic\n") /*=0x99476*/, ((unsigned long)"power_for_imu_and_mic"));
    } else {
        debug_print(iVar1 < 0 ? ((unsigned long)"%s(): Could not set ldsw2.\n") : ((unsigned long)"%s(): enable ldsw2 for imu and mic\n") /*=0x99476*/, ((unsigned long)"power_for_imu_and_mic"));
    }
    return 0;
}
