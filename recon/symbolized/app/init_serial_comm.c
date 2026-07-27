#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00033340 @ 0x00033340
 * public-name: init_serial_comm
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fuel_gauge_dev_register                  <= FUN_00033088 @ 0x00033088
 *   process_pt_data                          <= FUN_000330ec @ 0x000330ec
 *   init_serial_port                         <= FUN_000332dc @ 0x000332dc
 *   init_serial_comm                         <= FUN_00033340 @ 0x00033340
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 * address symbols (name @ address):
 *   rodata_87bc0                             @ 0x00087bc0
 *   rodata_a7907                             @ 0x000a7907   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00033340 @ 0x33340  (parity: 300/300 trials, PROVEN) */

extern int fuel_gauge_dev_register(unsigned int a);
extern int process_pt_data(void);
extern unsigned int init_serial_port(void);
extern void k_sleep(unsigned int a, unsigned int b);

int init_serial_comm(void)
{
    int iVar1;

    iVar1 = init_serial_port();
    if (iVar1 == 0) {
        iVar1 = fuel_gauge_dev_register(((unsigned long)&rodata_87bc0) /*=0x87bc0*/);
        if (iVar1 == 0) {
            iVar1 = process_pt_data();
            if (iVar1 != 0) {
                iVar1 = -3;
            }
        } else {
            log_message(((unsigned long)"init_serial_comm is failed\n") /*=0xa7907*/);
            k_sleep(0x4000, 0);
            iVar1 = -2;
        }
    } else {
        iVar1 = -1;
    }
    return iVar1;
}
