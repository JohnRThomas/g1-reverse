/* readable reconstruction; identity: FUN_01010ff0 @ 0x01010ff0
 * public-name: FUN_01010ff0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_work_submit                          <= FUN_0100ef88 @ 0x0100ef88
 * address symbols (name @ address):
 *   rodata_101113d                           @ 0x0101113d
 *   g_net_own_addr_info                      @ 0x21000f20
 */
/* net-core FUN_01010ff0 @ 0x1010ff0  (parity 300 trials PROVEN) */

extern void sdc_assertion_fail(unsigned int, unsigned int);
extern int FUN_0100ca98(int, void*, void*);
extern void sdc_work_submit(void*, unsigned int, unsigned int);

void FUN_01010ff0(unsigned char *param_1, int param_2)
{
    if (param_1[200] != 0) {
        return;
    }
    param_1[0xc9] = param_1[0];
    if (param_2 == 0xff) {
        unsigned char *pbVar2 = *(unsigned char**)0x21000f20;
        param_1[0xca] = (unsigned char)(((unsigned int)pbVar2[0] << 0x19) >> 0x1f);
        *(unsigned int*)(param_1 + 0xcb) = *(unsigned int*)(pbVar2 + 3);
        *(unsigned short*)(param_1 + 0xcf) = *(unsigned short*)(pbVar2 + 7);
    } else {
        int iVar1 = FUN_0100ca98(param_2, param_1 + 0xca, param_1 + 0xcb);
        if (iVar1 == 0) {
            sdc_assertion_fail(0x2d, 0xfc2);
        }
        param_1[0xca] = param_1[0xca] | 2;
    }
    sdc_work_submit(param_1 + 0xc0, 0x0101113d, 2);
}
