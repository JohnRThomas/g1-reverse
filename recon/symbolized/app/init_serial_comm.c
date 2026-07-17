#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033340 @ 0x00033340
 * public-name: init_serial_comm
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   process_pt_data                          <= FUN_000330ec @ 0x000330ec
 *   init_serial_port                         <= FUN_000332dc @ 0x000332dc
 *   init_serial_comm                         <= FUN_00033340 @ 0x00033340
 * address symbols (name @ address):
 *   rodata_87bc0                             @ 0x00087bc0
 *   rodata_a7907                             @ 0x000a7907
 */
/* Reconstructed FUN_00033340 @ 0x33340  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a);
extern int FUN_00033088(unsigned int a);
extern int process_pt_data(void);
extern int init_serial_port(void);
extern void FUN_00074844(unsigned int a, unsigned int b);

int init_serial_comm(void)
{
    int iVar1;

    iVar1 = init_serial_port();
    if (iVar1 == 0) {
        iVar1 = FUN_00033088(((unsigned long)&rodata_87bc0) /*=0x87bc0*/);
        if (iVar1 == 0) {
            iVar1 = process_pt_data();
            if (iVar1 != 0) {
                iVar1 = -3;
            }
        } else {
            DEBUG_PRINT(((unsigned long)&rodata_a7907) /*=0xa7907*/);
            FUN_00074844(0x4000, 0);
            iVar1 = -2;
        }
    } else {
        iVar1 = -1;
    }
    return iVar1;
}
