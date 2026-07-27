/* Reconstructed burial_point_record_info_init @ 0x4ab3c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern int get_device_info(void);
extern void memset_bytes(void);

void burial_point_record_info_init(void)
{
    if (*(volatile int*)0x2000230cUL /* unknown global 0x2000230c */ > 2) {
        if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    int iVar1 = get_device_info();
    (void)iVar1;
    memset_bytes();
    iVar1 = get_device_info();
    (void)iVar1;
    memset_bytes();
}

