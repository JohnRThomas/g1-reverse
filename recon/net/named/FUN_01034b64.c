/* readable reconstruction; identity: FUN_01034b64 @ 0x01034b64
 * public-name: FUN_01034b64
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_sdc_res_pool_slot_tbl                  @ 0x210006a8
 */
#include "../../headers/g1_nrf_regs.h"
/* net-core FUN_01034b64 @ 0x1034b64  (parity 300 trials PROVEN) */

extern int FUN_010344a8(int);
extern int FUN_010344bc(void);
extern int FUN_010344d4(int);
extern int FUN_01034520(int);
extern void FUN_01034578(int);
extern int FUN_010345f4(int*);
extern void FUN_01034b18(int);

unsigned int FUN_01034b64(int param_1, int param_2)
{
    int local_c = param_2;
    int iVar1 = FUN_010344bc();
    unsigned int uVar2 = 0x0bad0004;
    if (iVar1 != 0) {
        FUN_01034b18(param_1);
        iVar1 = FUN_010344d4(param_1);
        if (iVar1 != 0) {
            iVar1 = FUN_01034520(param_1);
            volatile unsigned int *vp = (volatile unsigned int*)(iVar1 * 4 + (G1_NRF_GPIOTE_NS_BASE + 0x510));
            *vp = 0;
            *vp = 0;
        }
        FUN_01034578(param_1);
        iVar1 = FUN_010344a8(param_1);
        *(unsigned short*)(0x210006a8 + (iVar1 + 8) * 2) = 0;
        local_c = param_1;
        iVar1 = FUN_010345f4(&local_c);
        iVar1 = iVar1 + local_c * 4;
        *(unsigned int*)(iVar1 + 0x200) = 0xfffcf0f0 & *(unsigned int*)(iVar1 + 0x200) | 2;
        uVar2 = 0x0bad0000;
    }
    return uVar2;
}
