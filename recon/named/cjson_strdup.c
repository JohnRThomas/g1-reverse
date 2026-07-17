/* readable reconstruction; identity: FUN_00064640 @ 0x00064640
 * public-name: cjson_strdup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   cjson_strdup                             <= FUN_00064640 @ 0x00064640
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   g_cjson_hooks                            @ 0x20002bac
 */
/* Reconstructed FUN_00064640 @ 0x64640  (parity: 300/300 trials, PROVEN) */

extern int strlen(void);
extern int memcpy(int a, int b, int c);

int cjson_strdup(int param_1)
{
    int iVar1;
    int iVar2;
    if (param_1 != 0) {
        iVar1 = strlen();
        iVar2 = ((int(*)(int))(*(volatile unsigned int*)0x20002bacUL))(iVar1 + 1);
        if (iVar2 != 0) {
            memcpy(iVar2, param_1, iVar1 + 1);
            return iVar2;
        }
    }
    return 0;
}
