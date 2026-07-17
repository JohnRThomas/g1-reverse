/* readable reconstruction; identity: FUN_00032784 @ 0x00032784
 * public-name: get_glassbox_charge_status
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a7411                             @ 0x000a7411
 *   rodata_a7751                             @ 0x000a7751
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_glassbox_charge_status_byte            @ 0x20019ef4
 */
/* Reconstructed get_glassbox_charge_status @ 0x32784  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int,unsigned int,unsigned int);
unsigned char get_glassbox_charge_status(void){
    volatile unsigned char *pbVar1 = (volatile unsigned char*)0x20019ef4UL;
    if(*(volatile int*)0x2000230cUL > 2){
        unsigned int sink = *(volatile unsigned int*)0x20007554UL;
        if(sink == 0){
            log_message(0x000a7411UL, 0x000a7751UL,
                        (unsigned int)(*pbVar1 >> 7),sink);
        } else {
            debug_print(0x000a7411UL, 0x000a7751UL,
                         (unsigned int)(*pbVar1 >> 7),sink);
        }
    }
    return *pbVar1 >> 7;
}
