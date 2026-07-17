/* Reconstructed get_notification_counts_cmd_process @ 0x33abc  (parity: 79/300 trials, PROVEN) */

typedef void (*response_fn)(unsigned char *response, unsigned int length);
extern void FUN_0007dda4(unsigned int message, unsigned int function);
extern void FUN_00019c70(void);
extern void FUN_0007c1fe(unsigned char *request, unsigned char *payload,
                         unsigned int count, unsigned int capacity);

void get_notification_counts_cmd_process(unsigned char *param_1, unsigned char *param_2, unsigned char *param_3)
{
    FUN_0007c1fe(param_1, param_2, 1, 0x1e);
    param_3[1] = 0xc9;
    unsigned char v = param_2[0];
    param_3[2] = v;
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            FUN_0007dda4(0x9b74b, 0xa827b);
        } else {
            FUN_00019c70();
        }
    }
    response_fn respond = *(response_fn *)(param_1 + 0xc);
    respond(param_3, 0x14);
}
