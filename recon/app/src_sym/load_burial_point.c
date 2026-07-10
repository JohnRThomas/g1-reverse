/* Reconstructed load_burial_point @ 0x230e0  (parity: 300/300 trials, PROVEN) */

extern int flash_settings_read(unsigned int, void*, int, unsigned int, unsigned int);
extern unsigned int FUN_00052c40(void);
extern void memset_bytes(void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

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
            uVar2 = FUN_00052c40();
            memset_bytes(base + 0xca, 0, 0xbc);
            *(volatile unsigned char*)(base + 0xda) = 7;
            *(volatile unsigned int*)(base + 0xc6) = uVar2;
            *(volatile unsigned char*)(base + 0xdc) = 1;
        }
    } else {
        if (1 < *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                DEBUG_PRINT(0x9e67c, 0x9e777);
            } else {
                debug_print();
            }
        }
        uVar3 = 0xffffffff;
    }
    return uVar3;
}

