/* Reconstructed pull_message @ 0x342e0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void debug_print(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern unsigned int get_device_info(void);

unsigned char pull_message(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int iVar3;

    if (param_1 == (int *)0) {
        if (0 < *(int *)0x2000230cUL) {
            if (*(int *)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0xa804bU, 0xa822eU, 0xa8221U, 0x3bdU, param_4);
            } else {
                debug_print(0xa804bU, 0xa822eU, 0xa8221U, 0x3bdU);
            }
        }
    } else {
        iVar3 = get_device_info();
        if (*(unsigned char *)(iVar3 + 0xdd) <= 0xa) {
            *param_1 = (unsigned int)(*(unsigned char *)0x2001a22aUL) * 0x1b4 + 0x20007dacU /* device_info_t+0x13b0 (unmapped region) */;
            if (*(int *)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0xa80bcU, 0, 0, 0, 0);
            } else {
                debug_print(0xa80bcU, 0, 0, 0);
            }
            return *(unsigned char *)0x2001a22aUL;
        }
        if (*(int *)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
            iVar3 = get_device_info();
            DEBUG_PRINT(0xa806cU, (unsigned int)*(unsigned char *)(iVar3 + 0xdd), 0, 0, 0);
        } else {
            iVar3 = get_device_info();
            debug_print(0xa806cU, *(unsigned char *)(iVar3 + 0xdd), 0, 0);
        }
    }
    return 10;
}

