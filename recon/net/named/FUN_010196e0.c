/* readable reconstruction; identity: FUN_010196e0 @ 0x010196e0
 * public-name: FUN_010196e0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_work_submit                          <= FUN_0100ef88 @ 0x0100ef88
 * address symbols (name @ address):
 *   g_ll_conn_default_ctx                    @ 0x21001058
 */
/* net-core FUN_010196e0 @ 0x10196e0  (parity 300 trials PROVEN) */

extern unsigned int FUN_0100a5a0(void);
extern void FUN_0102714a(unsigned int, void*, void*);
extern int FUN_010270d2(unsigned int);
extern void sdc_work_submit(int, unsigned int, int);
extern void FUN_01019660(void);

void FUN_010196e0(void)
{
    unsigned char buf[12];
    unsigned int uVar3;
    int iVar4, iVar2;
    uVar3 = FUN_0100a5a0();
    FUN_0102714a(uVar3, (void*)(buf+4), (void*)(buf+2));
    iVar4 = FUN_010270d2(*(unsigned int*)(buf+4));
    iVar2 = 0x21001058;
    if (*(volatile char*)(iVar4+0x1f) != 0) {
        iVar4 = *(volatile int*)(iVar2+0x40);
        if (iVar4 != 0) {
            char cVar1 = *(volatile char*)(iVar2+0x46);
            unsigned char r3 = *(volatile unsigned char*)(iVar4+0x1c);
            r3 = (r3 & 0x9f) | 0x40;
            *(volatile unsigned char*)(iVar4+0x1c) = r3;
            *(volatile unsigned char*)(iVar4+8) = 0;
            sdc_work_submit(iVar4, 0x1019a9d, 6);
            if (cVar1 != 0) {
                *(volatile unsigned char*)(iVar4+0x11) = 0;
                sdc_work_submit(iVar4+9, 0x1019a9d, 6);
            }
            *(volatile unsigned int*)(iVar2+0x40) = 0;
            *(volatile unsigned char*)(iVar2+0x46) = 0;
        }
        FUN_01019660();
        return;
    }
    return;
}
