/* readable reconstruction; identity: FUN_00033f24 @ 0x00033f24
 * public-name: message_table_contains_id
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   message_table_contains_id                <= FUN_00033f24 @ 0x00033f24
 * address symbols (name @ address):
 *   g_message_pool                           @ 0x20007dac
 */
/* Reconstructed FUN_00033f24 @ 0x33f24  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint;

uint message_table_contains_id(uint param_1, int param_2)
{
    unsigned char bVar1;
    int iVar2;
    bVar1 = 0;
    while (1) {
        if (param_1 <= bVar1) {
            return 0;
        }
        iVar2 = (int)bVar1 * 0x1b4 + 0x20007dac;
        if ((*(volatile char*)(iVar2 + 0x10) != 0) && (*(volatile int*)(iVar2 + 8) == param_2)) {
            break;
        }
        bVar1 = bVar1 + 1;
    }
    return 1;
}
