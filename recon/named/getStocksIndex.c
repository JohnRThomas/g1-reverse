/* readable reconstruction; identity: FUN_000370bc @ 0x000370bc
 * public-name: getStocksIndex
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a8ff3                             @ 0x000a8ff3
 *   rodata_a95d8                             @ 0x000a95d8
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_widget_state                 @ 0x20004950
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_stocks_widget_index_raw                @ 0x2001b815
 */
/* Reconstructed getStocksIndex @ 0x370bc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int,unsigned int,unsigned int);

unsigned char getStocksIndex(void)
{
    volatile unsigned char *base = (volatile unsigned char*)0x20004950UL;
    int iVar2 = *(volatile int*)0x2000230cUL;
    unsigned char b = *(volatile unsigned char*)0x2001b815UL;
    base[3] = b;
    if (iVar2 > 2) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x000a8ff3UL, 0x000a95d8UL, 0x000a95d8UL, b);
        } else {
            debug_print(0x000a8ff3UL, 0x000a95d8UL, 0x000a95d8UL, b);
        }
    }
    return base[3];
}
