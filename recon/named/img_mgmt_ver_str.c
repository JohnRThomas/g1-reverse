/* readable reconstruction; identity: FUN_00051f88 @ 0x00051f88
 * public-name: img_mgmt_ver_str
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   img_mgmt_ver_str                         <= FUN_00051f88 @ 0x00051f88
 * address symbols (name @ address):
 *   rodata_f27cf                             @ 0x000f27cf
 *   rodata_f27db                             @ 0x000f27db
 */
/* Reconstructed FUN_00051f88 @ 0x51f88  (parity: 300/300 trials, PROVEN) */

extern int FUN_00077914(int, int, unsigned int, unsigned int, unsigned int, unsigned int);

int img_mgmt_ver_str(unsigned char *param_1, int param_2)
{
    unsigned int uVar2 = *(volatile unsigned short*)(param_1 + 2);
    unsigned int uVar3 = *(volatile unsigned char*)(param_1 + 1);
    unsigned char p0 = *(volatile unsigned char*)(param_1 + 0);
    int iVar1 = FUN_00077914(param_2, 0x19, 0xf27cfUL, p0, uVar3, uVar2);
    int iVar4 = *(volatile int*)(param_1 + 4);
    if (iVar4 != 0) {
        iVar4 = FUN_00077914(param_2 + iVar1, 0x19 - iVar1, 0xf27dbUL, iVar4, uVar3, uVar2);
    }
    return iVar1 + iVar4;
}
