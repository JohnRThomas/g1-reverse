/* readable reconstruction; identity: FUN_0004a51c @ 0x0004a51c
 * public-name: get_boot_seconds
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_ldivmod                          <= FUN_0000e1a4 @ 0x0000e1a4
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_uptime_get_9                           <= FUN_0007d9a4 @ 0x0007d9a4
 * address symbols (name @ address):
 *   rodata_f02ad                             @ 0x000f02ad   [INLINED -- G6 literal batch]
 *   rodata_f02ff                             @ 0x000f02ff   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_boot_uptime_s                          @ 0x2000a0b0
 */
/* Reconstructed get_boot_seconds @ 0x4a51c  (parity: 300/300 trials, PROVEN) */

extern unsigned long long k_uptime_get_9(void);
extern int __aeabi_ldivmod(unsigned int,unsigned int,unsigned int,unsigned int);
extern void log_message(unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int,unsigned int,unsigned int);

int get_boot_seconds(void)
{
    unsigned long long uVar3 = k_uptime_get_9();
    int iVar1 = __aeabi_ldivmod((unsigned int)uVar3,
                             (unsigned int)(uVar3 >> 32),1000,0);
    int iVar2 = *(volatile int*)0x2000a0b0UL;
    int diff = iVar1 - iVar2;
    if (*(volatile int*)0x2000230cUL > 2) {
        unsigned int sink = *(volatile unsigned int*)0x20007554UL;
        if (sink == 0) {
            log_message(0x000f02adUL,0x000f02ffUL,(unsigned int)diff,sink);
        } else {
            debug_print(0x000f02adUL,0x000f02ffUL,(unsigned int)diff,sink);
        }
    }
    return diff;
}
