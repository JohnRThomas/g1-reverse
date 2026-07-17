#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01033a60 @ 0x01033a60
 * public-name: FUN_01033a60
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_crc_scratch                  @ 0x21000684
 *   g_net_radio_busy_flag                    @ 0x21006458
 */
/* net-core FUN_01033a60 @ 0x1033a60  (parity 300 trials PROVEN) */

extern void FUN_0103b614(void *dst, unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_01032930(void);

unsigned int FUN_01033a60(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned char flag = *(volatile unsigned char*)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/;
    unsigned int uVar2;
    if (flag == 0) {
        if (param_1 == 0 || param_2 > 8) {
            uVar2 = 0xffffffea;
        } else {
            FUN_0103b614((void*)0x2100068c, param_1, param_2, 0, param_4);
            *(volatile unsigned char*)(((unsigned long)&g_net_radio_crc_scratch) /*=0x21000684*/+0x10) = (unsigned char)param_2;
            *(volatile unsigned char*)(((unsigned long)&g_net_radio_crc_scratch) /*=0x21000684*/+0x12) = (unsigned char)(0xff >> ((8-param_2)&0xff));
            FUN_01032930();
            uVar2 = 0;
        }
    } else {
        uVar2 = 0xfffffff0;
    }
    return uVar2;
}
