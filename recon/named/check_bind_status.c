/* readable reconstruction; identity: FUN_00026b88 @ 0x00026b88
 * public-name: check_bind_status
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9fce4                             @ 0x0009fce4
 *   rodata_9fd02                             @ 0x0009fd02
 *   rodata_a1ad8                             @ 0x000a1ad8
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_bind_status_log_debounce_cnt           @ 0x20018d83
 */
/* Reconstructed check_bind_status @ 0x26b88  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
typedef unsigned int u32;
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int);

void check_bind_status(int param_1, int param_2, int param_3)
{
    volatile char *pcVar2 = (volatile char*)0x20018d83UL;
    char cVar1;
    char *base;

    if (param_2 == 0) {
        cVar1 = *pcVar2;
        if (cVar1 != 0) {
            char nv = (char)(cVar1 - 1);
            *pcVar2 = nv;
            if (nv != 0) return;
        }
        base = (char*)(param_1 + 0x1000);
        if (base[0x71] != 1) return;
        base[0x71] = 0;
        if (*(volatile int*)0x2000230cUL <= 0) return;
        if (*(volatile u32*)0x20007554UL == 0) {
            DEBUG_PRINT(0x9fd02U, 0xa1ad8U);
        } else {
            debug_print(0x9fd02U, 0xa1ad8U);
        }
        return;
    } else {
        base = (char*)(param_1 + 0x1000);
        if (param_3 == 0) {
            if (base[0x71] == 0) {
                base[0x71] = 1;
                if (*(volatile int*)0x2000230cUL > 0) {
                    if (*(volatile u32*)0x20007554UL == 0) {
                        DEBUG_PRINT(0x9fce4U, 0xa1ad8U);
                    } else {
                        debug_print(0x9fce4U, 0xa1ad8U);
                    }
                }
            }
        } else {
            base[0x71] = 0;
        }
        *pcVar2 = 3;
    }
}
