/* Reconstructed startAudioStreamRecord @ 0x2f764  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b);
extern void debug_print(void);
extern unsigned int get_device_info(void);
extern void display_DelayClose(unsigned int ms);
extern int FUN_000720d0(int a, void *b, int c, int d);
extern void FUN_00072880(void *a);
extern void memset_bytes(void *dst, int val, int n);
extern void sync_to_slave(unsigned int a, unsigned int b, void *c, unsigned int d);

unsigned int startAudioStreamRecord(void)
{
    unsigned char buf[208];
    int iVar2;
    unsigned int uVar3;

    memset_bytes(buf + 5, 0, 0xcb);
    buf[4] = 1;
    iVar2 = FUN_000720d0(0x20003890, buf + 4, 0, 0);
    if (iVar2 == 0) {
        FUN_00072880((void*)0x200079e4UL /* device_info_t+0xfe8 (unmapped region) */);
        uVar3 = 0;
    } else {
        if (0 < *(int *)0x2000230cUL) {
            if (*(int *)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0xa4304U, 0xa496fU);
            } else {
                debug_print();
            }
        }
        *(unsigned short *)buf = 1;
        uVar3 = get_device_info();
        sync_to_slave(uVar3, 6, buf, 2);
        display_DelayClose(10000);
        if (0 < *(int *)0x2000230cUL) {
            if (*(int *)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0xa432aU, 0xa496fU);
            } else {
                debug_print();
            }
        }
        uVar3 = 0xffffffff;
    }
    return uVar3;
}

