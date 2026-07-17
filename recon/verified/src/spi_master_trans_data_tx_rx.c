/* Reconstructed spi_master_trans_data_tx_rx @ 0x262ac  (parity: 300/300 trials, PROVEN) */

extern int FUN_00067304(void*, void*, int);
extern void FUN_0007dda4(unsigned int, unsigned int, ...);
extern void FUN_00019c70(unsigned int, unsigned int, ...);

unsigned int spi_master_trans_data_tx_rx(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4, unsigned int param_5)
{
    int iVar1;
    struct {
        unsigned int tx_buffer;
        unsigned int tx_length;
        unsigned int rx_buffer;
        unsigned int rx_length;
    } transfer = { param_2, param_3, param_4, param_5 };
    if (*(volatile int*)(param_1 + 0x14) == 0) {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                FUN_0007dda4(0x9fb42, 0x9fc5d);
            } else {
                FUN_00019c70(0x9fb42, 0x9fc5d);
            }
        }
    } else {
        iVar1 = FUN_00067304((void*)(param_1+0xc), &transfer, 0);
        if ((unsigned int)iVar1 == 0x0bad0000) {
            return 0;
        }
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                FUN_0007dda4(0x9fb59, 0x9fc5d, *(volatile unsigned char*)(param_1+0x18), iVar1, 0x0bad0000);
            } else {
                FUN_00019c70(0x9fb59, 0x9fc5d, *(volatile unsigned char*)(param_1+0x18), iVar1, 0x0bad0000);
            }
        }
    }
    return 0xffffffff;
}
