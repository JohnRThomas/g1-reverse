/* readable reconstruction; identity: FUN_00034274 @ 0x00034274
 * public-name: msg_count_dec
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 *   clear_timeout_message                    <= FUN_00033d58 @ 0x00033d58
 *   msg_count_dec                            <= FUN_00034274 @ 0x00034274
 * address symbols (name @ address):
 *   rodata_a8017                             @ 0x000a8017   [INLINED -- G6 literal batch]
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_message_pool                           @ 0x20007dac
 *   g_message_pool_index                     @ 0x2001a22a
 */
/* Reconstructed FUN_00034274 @ 0x34274  (parity: 300/300 trials, PROVEN) */
extern int get_device_info(void);
extern void clear_timeout_message(int);
extern void log_message(unsigned,int);
extern void debug_print(void);
extern unsigned char msg_content_recalc_unread(void);
unsigned char msg_count_dec(void){
    int iVar3 = get_device_info();
    unsigned char bVar1 = *(unsigned char*)(iVar3 + 0xdd);
    if (bVar1 != 0){
        int r5 = bVar1 - 1;
        int r3 = r5 * 0x1b4 + 0x20007dac;
        if (*(int*)(r3 + 4) != 0){
            clear_timeout_message(1);
            unsigned char cVar4;
            if (r5 == 0) cVar4 = 0;
            else cVar4 = (unsigned char)(bVar1 - 2);
            *(volatile unsigned char*)0x2001a22aUL = cVar4;
            if (*(volatile int*)0x20007554UL == 0){
                log_message(((unsigned long)"[csh_debug_msg]msg_count_dec unread_msg_num is %d \n"), r5);
            } else {
                debug_print();
            }
            iVar3 = get_device_info();
            unsigned char uVar2 = msg_content_recalc_unread();
            *(unsigned char*)(iVar3 + 0xdd) = uVar2;
        }
    }
    iVar3 = get_device_info();
    return *(unsigned char*)(iVar3 + 0xdd);
}
