#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080ae6 @ 0x00080ae6
 * public-name: smp_alloc_rsp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_packet_alloc                         <= FUN_000526e4 @ 0x000526e4
 *   smp_alloc_rsp                            <= FUN_00080ae6 @ 0x00080ae6
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* Reconstructed FUN_00080ae6 @ 0x80ae6  (parity: 300/300 trials, PROVEN) */

extern int smp_packet_alloc(void);
extern void memcpy(int, int, int);

int smp_alloc_rsp(char *param_1, char *param_2)
{
    int iVar1;
    unsigned int fptr;
    iVar1 = smp_packet_alloc();
    if (iVar1 != 0) {
        fptr = *(volatile unsigned int*)(param_2 + 0x34);
        if (fptr == 0) {
            memcpy(iVar1 + 0x18, (int)(long)(param_1 + 0x18), *(volatile signed char*)(param_1 + 0xb));
        } else {
            ((void(*)(int,char*))fptr)(iVar1, param_1);
        }
    }
    return iVar1;
}
