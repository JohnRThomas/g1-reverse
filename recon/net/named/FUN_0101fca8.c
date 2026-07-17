/* readable reconstruction; identity: FUN_0101fca8 @ 0x0101fca8
 * public-name: FUN_0101fca8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ccm_op_status                      @ 0x210014d8
 *   REG_4100e000                             @ 0x4100e000
 */
/* net-core FUN_0101fca8 @ 0x101fca8  (parity 300 trials PROVEN) */

extern void FUN_01020088(unsigned int a);

void FUN_0101fca8(void)
{
    unsigned int base = 0x4100e000;
    volatile unsigned char *pcVar1 = (volatile unsigned char *)0x210014d8;
    unsigned char cVar4=0, cVar3;
    int iVar5;
    if (*pcVar1 != 0) {
        *(volatile unsigned int *)(base+0x80) = 0;
        iVar5 = *(volatile int *)(base+0x100);
        if (iVar5==0 || ( (iVar5=*(volatile int*)(base+0x104)) ==0)) {
            cVar4=(unsigned char)iVar5;
            cVar3=0x10;
        } else if (*(volatile int*)(base+0x108)==0) {
            cVar4=1;
            cVar3=(unsigned char)*(volatile unsigned int*)(base+0x400);
        } else {
            cVar3=0x10;
        }
        pcVar1[2]=cVar3;
        pcVar1[1]=cVar4;
        pcVar1[0]=0;
    }
    FUN_01020088(0);
}
