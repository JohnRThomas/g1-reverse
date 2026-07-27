/* Reconstructed delAudioStreamRecord @ 0x2f878  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void FUN_00072880(unsigned int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

unsigned int delAudioStreamRecord(unsigned char param_1)
{
    int iVar2;
    unsigned int uVar3;
    unsigned char buf[204];

    if (2 < *(volatile int*)0x2000230cUL /* unknown global 0x2000230c */) {
        if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0) {
            DEBUG_PRINT(0xa420e, 0xa4944);
        } else {
            debug_print(0xa420e, 0xa4944);
        }
    }
    memset_bytes(buf + 1, 0, 0xcb);
    *(unsigned short*)(buf + 2) = 1;
    buf[0] = 4;
    buf[4] = param_1;
    iVar2 = FUN_000720d0(*(volatile unsigned int*)0x20003890UL /* unknown global 0x20003890 */, buf, 0, 0);
    if (iVar2 == 0) {
        FUN_00072880(*(volatile unsigned int*)0x200079e4UL /* device_info+0xfe8 (gap near gap_0FDB+0x2, name best-effort) */);
        uVar3 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL /* unknown global 0x2000230c */) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0) {
                DEBUG_PRINT(0xa3f45, 0xa4944);
            } else {
                debug_print(0xa3f45, 0xa4944);
            }
        }
        uVar3 = 0xffffffff;
    }
    return uVar3;
}

