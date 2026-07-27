/* readable reconstruction; identity: FUN_00064c5c @ 0x00064c5c
 * public-name: cjson_create_string
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_strdup                             <= FUN_00064640 @ 0x00064640
 *   cjson_delete                             <= FUN_00064b1c @ 0x00064b1c
 *   cjson_create_string                      <= FUN_00064c5c @ 0x00064c5c
 *   alloc_zeroed_node                        <= FUN_00084fd4 @ 0x00084fd4
 * address symbols (name @ address):
 *   g_cjson_hooks                            @ 0x20002bac
 */
/* Reconstructed FUN_00064c5c @ 0x64c5c  (parity: 300/300 trials, PROVEN) */

extern int alloc_zeroed_node(unsigned int a);
extern int cjson_strdup(int);
extern void cjson_delete(unsigned int a);

int cjson_create_string(unsigned int param_1)
{
    int iVar1, iVar2;
    iVar1 = alloc_zeroed_node(*(volatile unsigned int*)0x20002bacUL);
    if (iVar1 != 0) {
        *(volatile int*)(iVar1 + 0xc) = 0x10;
        iVar2 = cjson_strdup(param_1);
        *(volatile int*)(iVar1 + 0x10) = iVar2;
        if (iVar2 != 0) {
            return iVar1;
        }
        cjson_delete(iVar1);
    }
    return 0;
}
