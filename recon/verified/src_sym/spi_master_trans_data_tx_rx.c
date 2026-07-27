/* Reconstructed spi_master_trans_data_tx_rx @ 0x262ac  (parity: 300/300 trials, PROVEN) */

extern int FUN_00067304(void*, void*, int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

unsigned int spi_master_trans_data_tx_rx(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4, unsigned int param_5)
{
    int iVar1;
    unsigned int local_18, uStack_14, local_10, local_c;
    local_c = param_5;
    local_18 = param_2;
    uStack_14 = param_3;
    local_10 = param_4;
    if (*(volatile int*)(param_1 + 0x14) == 0) {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0x9fb42, 0x9fc5d);
            } else {
                debug_print(0x9fb42, 0x9fc5d);
            }
        }
    } else {
        iVar1 = FUN_00067304((void*)(param_1+0xc), &local_18, 0);
        if ((unsigned int)iVar1 == 0x0bad0000) {
            return 0;
        }
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0x9fb59, 0x9fc5d, *(volatile unsigned char*)(param_1+0x18), iVar1, 0x0bad0000);
            } else {
                debug_print(0x9fb59, 0x9fc5d, *(volatile unsigned char*)(param_1+0x18), iVar1, 0x0bad0000);
            }
        }
    }
    return 0xffffffff;
}

