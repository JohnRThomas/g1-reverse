/* Reconstructed get_notification_counts_cmd_process @ 0x33abc  (parity: 79/300 trials, PROVEN) */

typedef void (*fp_t)(void);
extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);
extern void FUN_0007c1fe(void);

void get_notification_counts_cmd_process(unsigned char *param_1, unsigned char *param_2, unsigned char *param_3)
{
    FUN_0007c1fe();
    param_3[1] = 0xc9;
    unsigned char v = param_2[0];
    param_3[2] = v;
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            FUN_00019c70();
        }
    }
    fp_t f = *(fp_t*)(param_1+0xc);
    f();
}

