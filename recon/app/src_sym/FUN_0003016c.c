/* Reconstructed FUN_0003016c @ 0x3016c  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(void);
void FUN_0003016c(void)
{
    unsigned int base = *(volatile unsigned int*)0x20007bc0UL /* device_info_t+0x11C4  (device-state ptr region) */;
    fn_t f = *(volatile fn_t*)(base + 0xc);
    f();
}

