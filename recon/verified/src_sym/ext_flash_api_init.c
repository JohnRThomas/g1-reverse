/* Reconstructed ext_flash_api_init @ 0x2e4e8  (parity: 300/300 trials, PROVEN) */

extern void FUN_000864c2(unsigned int);
extern unsigned int z_device_is_ready(unsigned int);
extern unsigned short z_impl_flash_get_page_count(unsigned int);
extern unsigned int get_device_info(void);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

unsigned int ext_flash_api_init(unsigned int *param_1, unsigned int *param_2, unsigned int *param_3, unsigned int param_4)
{
    int iVar4;
    unsigned int uVar5;
    unsigned short uVar3;

    FUN_000864c2(0x20007b54UL /* device_info+0x1158 (ext-flash device object / mutex) */);
    uVar5 = 0x87bf0;                 /* ext-flash struct device *dev (rodata) */
    iVar4 = z_device_is_ready(0x87bf0);  /* Zephyr device_is_ready(dev) */
    if (iVar4 == 0) {
        if (0 < *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                DEBUG_PRINT(0xa3aa6, 0xa3ae5);
            } else {
                debug_print();
            }
        }
        uVar5 = 0xffffffff;
    } else {
        *param_1 = 0x2e399;
        *param_2 = 0x2e441;
        *param_3 = 0x2e301;
        iVar4 = *(volatile int*)0x2000230cUL;
        *(volatile unsigned int*)0x20007b68UL /* device_info+0x116C (ext-flash device handle) */ = uVar5;
        if (2 < iVar4) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xa3a8b, 0xa3ae5, 0x87bf0, 0, param_4);
            } else {
                debug_print();
            }
        }
        uVar3 = z_impl_flash_get_page_count(0x87bf0);
        iVar4 = get_device_info();
        uVar5 = 0;
        *(volatile unsigned short*)(iVar4 + 0x108a) = uVar3;
    }
    return uVar5;
}

