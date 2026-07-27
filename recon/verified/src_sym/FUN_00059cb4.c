/* Reconstructed FUN_00059cb4 @ 0x59cb4  (parity: 300/300 trials, PROVEN) */

extern unsigned long long atomic_or_0(int a, int b);
extern void printk(unsigned long, ...);
extern void assert_post_action(int a, int b);

void FUN_00059cb4(void)
{
    unsigned long long uVar5;
    unsigned short sVar2;
    int bVar3;
    unsigned int uVar4;

    uVar5 = atomic_or_0(0x2000af04, 2);
    if (((unsigned int)uVar5 & (unsigned int)(uVar5 >> 32)) == 0) {
        sVar2 = *(volatile unsigned short *)0x2000ff3cUL;
        bVar3 = 0;
        uVar4 = 0x88058;
        while (1) {
            if (0x88070 < uVar4) {
                if (bVar3) {
                    *(volatile unsigned short *)0x2000ff3cUL = sVar2;
                }
                printk(0x99cbd, 0xf49ac, 0xf46b8, 0x5ad);
                printk(0xf0d20, 0, 0, 0);
                assert_post_action(0xf46b8, 0x5ad);
            }
            if (0x88070 <= uVar4) break;
            sVar2 = (unsigned short)(sVar2 + *(int *)(uVar4 + 4));
            uVar4 = uVar4 + 8;
            bVar3 = 1;
        }
        if (bVar3) {
            *(volatile unsigned short *)0x2000ff3cUL = sVar2;
        }
    }
}

