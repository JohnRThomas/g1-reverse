/* readable reconstruction; identity: FUN_00055fb4 @ 0x00055fb4
 * public-name: FUN_00055fb4
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_ble_conn_cb_list_head                  @ 0x2000ad1c
 */
/* Reconstructed FUN_00055fb4 @ 0x55fb4  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(int, unsigned char);

void FUN_00055fb4(int param_1)
{
    unsigned int *puVar2;
    unsigned char b = *(unsigned char *)(param_1 + 0xc);

    puVar2 = *(unsigned int **)0x2000ad1cUL;
    while (puVar2 != (unsigned int *)0) {
        fn_t f = (fn_t)(*puVar2);
        if (f != (fn_t)0) {
            f(param_1, b);
        }
        puVar2 = (unsigned int *)puVar2[8];
    }
}
