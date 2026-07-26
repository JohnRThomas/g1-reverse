#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002ead8 @ 0x0002ead8
 * public-name: dev_read_status_bit_reg34
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_read_status_bit_reg34                <= FUN_0002ead8 @ 0x0002ead8
 *   dev_ctrl_read1                           <= FUN_00083dba @ 0x00083dba
 * address symbols (name @ address):
 *   rodata_a3e62                             @ 0x000a3e62   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0002ead8 @ 0x2ead8  (parity: 300/300 trials, PROVEN) */

extern void log_message(int);
extern int dev_ctrl_read1(int,int,int,void*,int);

unsigned int dev_read_status_bit_reg34(int param_1, unsigned int param_2)
{
    unsigned char byte7 = 0;
    int base = *(volatile int*)(0x00087ce0UL + 4);
    int arg0 = *(volatile int*)(base + 0x1c);
    int iVar1 = dev_ctrl_read1(arg0, 3, 0x34, &byte7, param_1);
    unsigned int uVar2;
    if (iVar1 < 0) {
        log_message(((unsigned long)"Could not get charger status\n") /*=0xa3e62*/);
        uVar2 = 0xffffffff;
    } else {
        unsigned int combined = (byte7 >> 3) | (byte7 >> 2);
        if (combined & 1) {
            uVar2 = 0;
        } else {
            uVar2 = (~(unsigned int)(byte7 >> 4)) & 1;
        }
    }
    return uVar2;
}
