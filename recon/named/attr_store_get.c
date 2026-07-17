/* readable reconstruction; identity: FUN_000302f8 @ 0x000302f8
 * public-name: attr_store_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_retry_delay                   <= FUN_0003016c @ 0x0003016c
 *   attr_store_get                           <= FUN_000302f8 @ 0x000302f8
 * address symbols (name @ address):
 *   g_pt_nfc_link_cfg                        @ 0x20007bc0
 */
/* Reconstructed FUN_000302f8 @ 0x302f8  (parity: 300/300 trials, PROVEN) */

extern int attr_store_retry_delay(int);
typedef int (*fp3_t)(void*, int, unsigned int*);

int attr_store_get(unsigned int param_1, unsigned int *param_2, int param_3)
{
    char cVar3 = 3;
    unsigned int local_1c = 0;
    unsigned short local_20 = (unsigned short)(((param_1 & 0xff) << 8) | ((param_1 >> 8) & 0xff));
    int iVar2;
    do {
        unsigned int puVar1 = *(volatile unsigned int*)0x20007bc0UL;
        fp3_t fp = (fp3_t)(*(volatile unsigned int*)puVar1);
        iVar2 = fp(&local_20, 2, &local_1c);
        if (iVar2 == 0) {
            *param_2 = (local_1c << 0x18) | ((local_1c >> 8 & 0xff) << 0x10) | ((local_1c >> 0x10 & 0xff) << 8) | (local_1c >> 0x18);
            return 0;
        }
        cVar3 = cVar3 - 1;
        attr_store_retry_delay(1);
    } while (cVar3 != 0);
    return 0xffffffff;
}
