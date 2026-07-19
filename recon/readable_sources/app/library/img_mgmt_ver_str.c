#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_image_version__param_0177              [param_0177; library]
 * Raw function identity: 0x00051f88.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00051f88 @ 0x00051f88
 * public-name: img_mgmt_ver_str
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   img_mgmt_ver_str                         <= FUN_00051f88 @ 0x00051f88
 *   snprintf                                 <= FUN_00077914 @ 0x00077914
 * address symbols (name @ address):
 *   rodata_f27cf                             @ 0x000f27cf
 *   rodata_f27db                             @ 0x000f27db
 */
/* Reconstructed FUN_00051f88 @ 0x51f88  (parity: 300/300 trials, PROVEN) */

extern int snprintf(int, int, unsigned int, unsigned int, unsigned int, unsigned int);

int img_mgmt_ver_str(unsigned char *param_1, int param_2)
{
    unsigned int uVar2 = *(volatile unsigned short*)(param_1 + 2);
    unsigned int uVar3 = *(volatile unsigned char*)(param_1 + 1);
    unsigned char p0 = *(volatile unsigned char*)(param_1 + 0);
    int iVar1 = snprintf(param_2, 0x19, ((unsigned long)&rodata_f27cf) /*=0xf27cf*/, p0, uVar3, uVar2);
    int iVar4 = *(volatile int*)(param_1 + 4);
    if (iVar4 != 0) {
        iVar4 = snprintf(param_2 + iVar1, 0x19 - iVar1, ((unsigned long)&rodata_f27db) /*=0xf27db*/, iVar4, uVar3, uVar2);
    }
    return iVar1 + iVar4;
}
