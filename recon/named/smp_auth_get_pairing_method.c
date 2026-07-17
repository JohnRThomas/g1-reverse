/* readable reconstruction; identity: FUN_0005caec @ 0x0005caec
 * public-name: smp_auth_get_pairing_method
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_auth_get_pairing_method              <= FUN_0005caec @ 0x0005caec
 * address symbols (name @ address):
 *   g_bt_settings_load_done                  @ 0x2001d532
 */
/* Reconstructed FUN_0005caec @ 0x5caec  (parity: 300/300 trials, PROVEN) */
extern int FUN_0005cac0(void);

int smp_auth_get_pairing_method(void)
{
    int *piVar1 = (int *)(long)FUN_0005cac0();
    if (piVar1 == 0) return 3;
    int iVar2 = piVar1[1];
    if (piVar1[0] == 0) {
        return (iVar2 == 0) ? 3 : 2;
    }
    if (iVar2 == 0) {
        if (*(volatile unsigned char*)0x2001d532UL == 0) return 0;
        if (piVar1[2] != 0) return 1;
    } else {
        if (piVar1[2] != 0 || *(volatile unsigned char*)0x2001d532UL == 0) return 4;
    }
    if (iVar2 != 0) iVar2 = 1;
    return iVar2 << 1;
}
