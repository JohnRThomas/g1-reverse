/* readable reconstruction; identity: FUN_000839fe @ 0x000839fe
 * public-name: mem_read_validated
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   is_regular_addr_valid                    <= FUN_000839dc @ 0x000839dc
 *   mem_read_validated                       <= FUN_000839fe @ 0x000839fe
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* Reconstructed FUN_000839fe @ 0x839fe  (parity: 300/300 trials, PROVEN) */
extern int is_regular_addr_valid(int a, int b);
extern int tail_61200(int a, int b);
extern void memcpy(int a, int b, int c);
unsigned mem_read_validated(int param_1, int param_2, int param_3, int param_4){
    int iVar1 = is_regular_addr_valid(param_2, param_4);
    if (iVar1 == 0){
        return tail_61200(param_2, param_4);
    }
    if (param_4 != 0){
        memcpy(param_3, param_2, param_4);
    }
    return 0;
}
