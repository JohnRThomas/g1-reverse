#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_000167f4 @ 0x000167f4
 * public-name: enable_ship_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   power_down_panel                         <= FUN_00015fdc @ 0x00015fdc
 *   power_down_imu_and_mic                   <= FUN_000160b4 @ 0x000160b4
 *   enable_ship_mode                         <= FUN_000167f4 @ 0x000167f4
 *   app_msleep_thunk_a                       <= FUN_0007c038 @ 0x0007c038
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 */
/* Reconstructed FUN_000167f4 @ 0x167f4  (parity: 300/300 trials, PROVEN) */

extern unsigned int power_down_panel(void);
extern unsigned int power_down_imu_and_mic(void);
extern void app_msleep_thunk_a(unsigned int a);
extern int dev_write_reg3(unsigned int a, unsigned int b,
                        unsigned int c, unsigned int d);

unsigned int enable_ship_mode(void)
{
    unsigned int format_string;
    power_down_panel();
    power_down_imu_and_mic();
    app_msleep_thunk_a(2000);
    int base = *(volatile int*)((unsigned long)&rodata_87d10 + 4) /*=0x87d10*/;
    unsigned int arg0 = *(volatile unsigned int*)(base + 0x1c);
    int status = dev_write_reg3(arg0, 0xb, 2, 1);
    if (status < 0) {
        format_string = 0x0009973dUL;
    } else {
        format_string = 0x00099756UL;
    }
    log_message(format_string);
    return 0;
}
