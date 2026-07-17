/* readable reconstruction; identity: FUN_00047148 @ 0x00047148
 * public-name: quicknote_buffer_pool_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   quicknote_buffer_pool_init               <= FUN_00047148 @ 0x00047148
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   kmutex_dlist_init                        <= FUN_000864c2 @ 0x000864c2
 * address symbols (name @ address):
 *   rodata_fa08                              @ 0x0000fa08
 *   rodata_35775                             @ 0x00035775
 *   rodata_46ce9                             @ 0x00046ce9
 *   ADDR_panel_off_THUMB                     @ 0x00046d2d
 *   rodata_46d8d                             @ 0x00046d8d
 *   ADDR_panel_on_THUMB                      @ 0x00046dd9
 *   rodata_46f21                             @ 0x00046f21
 *   ADDR_jdb_panel_init_THUMB                @ 0x00046fc1
 *   rodata_7d4cb                             @ 0x0007d4cb
 *   rodata_7d4d7                             @ 0x0007d4d7
 *   g_projector_bus_lock                     @ 0x2000a060
 */
/* Reconstructed FUN_00047148 @ 0x47148  (parity: 300/300 trials, PROVEN) */
extern void kmutex_dlist_init(unsigned);
extern int malloc(unsigned);
void quicknote_buffer_pool_init(int* param_1){
    kmutex_dlist_init(0x2000a060);
    param_1[0] = 0x46fc1;
    param_1[1] = 0x46d8d;
    param_1[2] = 0x46f21;
    param_1[3] = 0x46d2d;
    param_1[4] = 0x46dd9;
    param_1[5] = 0x35775;
    param_1[6] = 0x7d4d7;
    param_1[7] = 0x7d4cb;
    param_1[8] = 0x46ce9;
    int iVar1 = malloc(0xfa08);
    int iVar3 = iVar1 + 5;
    param_1[0xd1] = iVar3;
    int* piVar2 = param_1 + 8;
    do {
        piVar2 = piVar2 + 1;
        *piVar2 = iVar3;
        iVar3 = iVar3 + 0x140;
    } while (iVar3 != iVar1 + 0xfa05);
    param_1[0xd4] = 64000;
}
