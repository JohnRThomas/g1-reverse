/* readable reconstruction; identity: FUN_00035608 @ 0x00035608
 * public-name: store_whitelist
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   flash_write_paged                        <= FUN_000227d0 @ 0x000227d0
 *   revalidate_whitelist_json                <= FUN_000355b4 @ 0x000355b4
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 * address symbols (name @ address):
 *   rodata_a896c                             @ 0x000a896c   [INLINED -- G6 literal batch]
 *   rodata_a8994                             @ 0x000a8994   [INLINED -- G6 literal batch]
 *   rodata_a8ab7                             @ 0x000a8ab7   [INLINED -- G6 literal batch]
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_whitelist_buffer                   @ 0x2001a22c
 */
/* Reconstructed store_whitelist @ 0x35608  (parity: 300/300 trials, PROVEN) */
extern int flash_write_paged(unsigned int a0, unsigned int a1, unsigned int a2);
extern void revalidate_whitelist_json(void);
extern void k_sleep(unsigned int a0, unsigned int a1);
extern void log_message(unsigned int a0, ...);
extern void debug_print(unsigned int a0, ...);

int store_whitelist(void)
{
    int iVar4;
    unsigned char cVar5 = 3;
    do {
        iVar4 = flash_write_paged(0x131000UL, 0x2001a22cUL, 0x15e2UL);
        if (iVar4 == 0) {
            revalidate_whitelist_json();
            break;
        }
        k_sleep(0xa4UL, 0UL);
        if (*(volatile int*)0x20007554UL == 0)
            log_message(0xa896cUL);
        else
            debug_print(0);
        cVar5 = cVar5 - 1;
    } while (cVar5 != 0);
    if (*(volatile int*)0x20007554UL == 0)
        log_message(0xa8994UL, 0xa8ab7UL, 0x24UL, iVar4);
    else
        debug_print(0xa8994UL, 0xa8ab7UL, 0x24UL, iVar4);
    return iVar4;
}
