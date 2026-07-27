/* Reconstructed sendAudioStram2Cache @ 0x2f6b0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern int FUN_000720d0(int a, void *b, int c, int d);
extern void FUN_00072880(void *a);
extern void memcpy(void *dst, void *src, int n);
extern void memset_bytes(void *dst, int val, int n);

unsigned int sendAudioStram2Cache(void *param_1)
{
    unsigned char local_buf[204];
    int iVar1;

    memset_bytes(local_buf, 0, 0xcc);
    iVar1 = 0x20003890;
    if (*(int *)(0x20003890 + 0x24) == 0x12) {
        if (0 < *(int *)0x2000230cUL) {
            if (*(int *)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0xa42cfU, 0xa4986U);
            } else {
                debug_print(0xa42cfU, 0xa4986U);
            }
        }
    } else {
        unsigned char *hdr = local_buf + 4;
        memcpy(hdr, param_1, 200);
        *(unsigned short *)(local_buf + 2) = 200;
        local_buf[0] = 2;
        iVar1 = FUN_000720d0(iVar1, local_buf, 0, 0);
        if (iVar1 == 0) {
            FUN_00072880((void*)0x200079e4UL /* device_info_t+0xfe8 (unmapped region) */);
            return 0;
        }
        if (0 < *(int *)0x2000230cUL) {
            if (*(int *)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0xa3f45U, 0xa4986U);
            } else {
                debug_print(0xa3f45U, 0xa4986U);
            }
        }
    }
    return 0xffffffff;
}

