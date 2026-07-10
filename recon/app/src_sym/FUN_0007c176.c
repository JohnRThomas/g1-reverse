/* Reconstructed FUN_0007c176 @ 0x7c176  (parity: 300/300 trials, PROVEN) */

extern char *get_device_info(void);
void FUN_0007c176(unsigned char param_1, unsigned char param_2) {
    char *p1 = get_device_info();
    *(volatile unsigned char*)(p1 + 0xce) = param_2;
    char *p2 = get_device_info();
    *(volatile unsigned char*)(p2 + 0xcc) = param_1;
}

