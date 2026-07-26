/* readable reconstruction; identity: FUN_0004a568 @ 0x0004a568
 * public-name: uint32_to_little_endian
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_f02d2                             @ 0x000f02d2   [INLINED -- G6 literal batch]
 *   rodata_f02e7                             @ 0x000f02e7   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed uint32_to_little_endian @ 0x4a568  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);

unsigned int uint32_to_little_endian(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;
    if (param_1 == 0) {
        if (*(volatile int*)0x2000230cUL > 1) {
            unsigned int sink=*(volatile unsigned int*)0x20007554UL;
            if (sink == 0) {
                log_message(((unsigned long)"%s(): buf is NULL !\n"),((unsigned long)"uint32_to_little_endian"),param_3,sink,param_4);
            } else {
                debug_print(((unsigned long)"%s(): buf is NULL !\n"),((unsigned long)"uint32_to_little_endian"),param_3,sink,param_4);
            }
        }
        uVar1 = 0;
    } else {
        param_1[0] = (unsigned char)param_2;
        param_1[1] = (unsigned char)(param_2 >> 8);
        param_1[2] = (unsigned char)(param_2 >> 16);
        param_1[3] = (unsigned char)(param_2 >> 24);
        uVar1 = 1;
    }
    return uVar1;
}
