/* readable reconstruction; identity: FUN_0002e8b4 @ 0x0002e8b4
 * public-name: opt3007_chip_deinit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a3cb9                             @ 0x000a3cb9
 *   rodata_a3cda                             @ 0x000a3cda
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_opt3007_dev                            @ 0x20007b6c
 *   g_opt3007_chip_ready                     @ 0x20018da1
 */
/* Reconstructed opt3007_chip_deinit @ 0x2e8b4  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(unsigned int,...);
void opt3007_chip_deinit(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    unsigned int v = *(volatile unsigned int*)0x20007b6cUL;
    if(v != 0){
        param_3 = 0;
        *(volatile unsigned int*)(v + 0x10) = 0;
    }
    if(*(volatile int*)0x2000230cUL > 2){
        if(*(volatile unsigned int*)0x20007554UL==0){
            log_message(0x000a3cb9UL,0x000a3cdaUL,param_3,0,param_4);
        } else {
            debug_print(0x000a3cb9UL,0x000a3cdaUL,param_3,0,param_4);
        }
    }
    *(volatile unsigned char*)0x20018da1UL = 0;
}
