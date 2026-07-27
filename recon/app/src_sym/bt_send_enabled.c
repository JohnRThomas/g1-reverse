/* Reconstructed bt_send_enabled @ 0x17e3c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

void bt_send_enabled(int param_1)
{
    if (*(volatile int*)0x2000230cUL /* unknown global 0x2000230c */ > 2) {
        if (*(volatile int*)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0) {
            DEBUG_PRINT(0x9a143UL, 0x9a2cdUL, param_1);
        } else {
            debug_print(0x9a143UL, 0x9a2cdUL, param_1);
        }
    }
    int *p = *(int* volatile*)0x20006a30UL /* device_info+0x34 (gap near gap_0003+0x31, name best-effort) */;
    *(volatile unsigned char*)((char*)p + 0x366) = (param_1 == 0);
}

