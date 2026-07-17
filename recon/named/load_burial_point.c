/* readable reconstruction; identity: FUN_000230e0 @ 0x000230e0
 * public-name: load_burial_point
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   flash_settings_read                      <= FUN_000225b4 @ 0x000225b4
 *   sys_rand32_get                           <= FUN_00052c40 @ 0x00052c40
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9e67c                             @ 0x0009e67c
 *   rodata_9e777                             @ 0x0009e777
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed load_burial_point @ 0x230e0  (parity: 300/300 trials, PROVEN) */

extern int flash_settings_read(unsigned int, void*, int, unsigned int, unsigned int);
extern unsigned int sys_rand32_get(void);
extern void memset_bytes(void*, int, int);
extern void log_message(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int,unsigned int);

unsigned int load_burial_point(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned char *base = (unsigned char*)(param_1 + 0x1000);

    iVar1 = flash_settings_read(0x135000, (void*)(param_1 + 0x10c6), 0xc0, param_4, param_4);
    if (iVar1 == 0) {
        uVar3 = 0;
        if ((*(volatile short*)(base + 0xda) == -1) || (*(volatile char*)(base + 0xdc) == 0)) {
            uVar2 = sys_rand32_get();
            memset_bytes(base + 0xca, 0, 0xbc);
            *(volatile unsigned char*)(base + 0xda) = 7;
            *(volatile unsigned int*)(base + 0xc6) = uVar2;
            *(volatile unsigned char*)(base + 0xdc) = 1;
        }
    } else {
        if (1 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                log_message(0x9e67c, 0x9e777);
            } else {
                debug_print(0x9e67c, 0x9e777);
            }
        }
        uVar3 = 0xffffffff;
    }
    return uVar3;
}
