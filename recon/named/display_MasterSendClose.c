/* readable reconstruction; identity: FUN_000499b8 @ 0x000499b8
 * public-name: display_MasterSendClose
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_f008c                             @ 0x000f008c   [INLINED -- G6 literal batch]
 *   rodata_f0139                             @ 0x000f0139   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_display_msgq                           @ 0x200038c4
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed display_MasterSendClose @ 0x499b8  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *destination, int value, unsigned int length);
extern int k_msgq_put(unsigned int queue, void *record,
                       unsigned int wait, unsigned int flags);
extern void log_message(unsigned int format, unsigned int context);
extern void debug_print(unsigned int format, unsigned int context, ...);

unsigned int display_MasterSendClose(void)
{
    unsigned char record[24];

    memset_bytes(record + 1, 0, 23);
    record[0] = 6;
    int iVar1 = k_msgq_put(0x200038c4UL, record, 0, 0);
    unsigned int uVar2;
    if (iVar1 == 0) {
        uVar2 = 0;
        if (*(volatile int*)0x2000230cUL > 2) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                log_message(0x000f008cUL, 0x000f0139UL);
            } else {
                debug_print(0x000f008cUL, 0x000f0139UL);
            }
        }
    } else {
        log_message(((unsigned long)"message queue send failed %s\r\n"), 0x000f0139UL);
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}
