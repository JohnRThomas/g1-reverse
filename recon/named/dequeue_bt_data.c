/* readable reconstruction; identity: FUN_000181b8 @ 0x000181b8
 * public-name: dequeue_bt_data
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dequeue_bt_data                          <= FUN_000181b8 @ 0x000181b8
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_bt_data_pipe                           @ 0x200038f8
 */
/* Reconstructed FUN_000181b8 @ 0x181b8  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern int k_msgq_get(int, unsigned int, int, int);
extern void memcpy(int, int, int);

int dequeue_bt_data(unsigned int param_1)
{
    unsigned char storage[264];
    unsigned char *buffer = storage + 4;
    memset_bytes(buffer, 0, 0x101);
    int iVar1 = k_msgq_get(0x200038f8UL, buffer, 0, 0);
    if (iVar1 == 0) {
        memcpy(param_1, buffer, 0x101);
    }
    return iVar1;
}
