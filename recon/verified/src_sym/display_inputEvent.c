/* Reconstructed display_inputEvent @ 0x49938  (parity: 300/300 trials, PROVEN) */
extern void memset_bytes(void *a0, unsigned int a1, unsigned int a2);
extern void DEBUG_PRINT(unsigned int a0, unsigned int a1);
extern void debug_print(void);
extern int FUN_000720d0(unsigned int a0, void *a1, unsigned int a2, unsigned int a3);

unsigned int display_inputEvent(unsigned char param_1, unsigned char param_2)
{
    unsigned char buf[6];
    int iVar1;
    unsigned int uVar2;
    memset_bytes(buf + 1, 0, 0x17);
    buf[0] = 5;
    *(unsigned short*)(buf + 2) = 2;
    buf[4] = param_1;
    buf[5] = param_2;
    iVar1 = FUN_000720d0(0x200038c4UL, buf, 0UL, 0UL);
    if (iVar1 == 0) {
        uVar2 = 0;
        if (2 < *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */) {
            if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0)
                DEBUG_PRINT(0xf00bbUL, 0xf0151UL);
            else
                debug_print();
        }
    } else {
        DEBUG_PRINT(0xef058UL, 0xf0151UL);
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

