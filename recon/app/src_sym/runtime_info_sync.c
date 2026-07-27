/* Reconstructed runtime_info_sync @ 0x16268  (parity: 300/300 trials, PROVEN) */

extern int global_ipc_service_send(void*, int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

unsigned int runtime_info_sync(unsigned short *param_1)
{
    unsigned int local_18;
    unsigned int local_14;
    unsigned int uVar1;
    unsigned char *b = (unsigned char*)param_1;

    local_18 = ((unsigned int)(*param_1) << 16) | 1;
    local_14 = (unsigned int)b[2] | ((unsigned int)b[3] << 8) | ((unsigned int)b[4] << 16);
    uVar1 = global_ipc_service_send(&local_18, 8);
    if (*(volatile unsigned char*)0x20002fe0UL != 0) {
        *(volatile unsigned char*)0x20002fe0UL = 0;
        if (1 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0x9957c, 0x99bee,
                    (local_18 >> 16) & 0xff, local_18 >> 24,
                    local_14 & 0xff, uVar1,
                    (unsigned int)b[3], (unsigned int)b[4]);
            } else {
                debug_print(0x9957c, 0x99bee,
                    (local_18 >> 16) & 0xff, local_18 >> 24,
                    local_14 & 0xff, uVar1,
                    (unsigned int)b[3], (unsigned int)b[4]);
            }
        }
    }
    return uVar1;
}

