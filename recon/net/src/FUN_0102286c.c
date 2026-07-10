/* net-core FUN_0102286c @ 0x102286c  (parity 300 trials PROVEN) */
extern int FUN_01021ee0(int,int,int,int);
extern unsigned int FUN_01022774(int);
extern unsigned long long FUN_01024778(void);
extern unsigned long long FUN_01025084(void);
extern void FUN_0102524c(int);
extern void FUN_01025344(void);

#define G 0x210016f0u

unsigned int FUN_0102286c(unsigned int param_1, int param_2)
{
    unsigned int base = G;
    unsigned char bVar1 = *(volatile unsigned char*)(base + param_2*3 + 0x30);
    unsigned int uVar8 = bVar1;
    unsigned int uVar9;

    if (uVar8 != 0x20) {
        uVar9 = FUN_01022774(param_2);
        if (uVar8 != uVar9) return 0;
    }

    {
        unsigned long long lVar10 = FUN_01025084();
        unsigned char f4b = *(volatile unsigned char*)(base+0x4b);
        int ok = (f4b == ' ');
        if (!ok) {
            unsigned int hi = (unsigned int)((lVar10 + 2) >> 32);
            unsigned int f14 = *(volatile unsigned int*)(base+0x14);
            unsigned int f10 = *(volatile unsigned int*)(base+0x10);
            unsigned int lo = (unsigned int)(lVar10 + 2);
            ok = (hi < f14) || ((f14 - hi) < (unsigned int)(lo <= f10));
        }
        if (!ok) return 0;

        if (uVar8 == 0x20) {
            char cVar2;
            int f44 = *(volatile int*)(base+0x44);
            int f40 = *(volatile int*)(base+0x40);
            if (f44 == -1 && f40 == -1) {
                cVar2 = *(volatile char*)(base+0x48);
            } else {
                FUN_01024778();
                *(volatile unsigned int*)(base+0x40) = 0xffffffff;
                *(volatile unsigned int*)(base+0x44) = 0xffffffff;
                cVar2 = *(volatile char*)(base+0x48);
            }
            if (cVar2 != 0) {
                FUN_0102524c(5);
                *(volatile unsigned char*)(base+0x48) = 0;
            }
            FUN_0102524c(4);
            FUN_01025344();
            *(volatile unsigned char*)(base+0x4b) = 0x20;
            **(volatile unsigned int **)(base+0x4d4) = 0;
            return 1;
        } else {
            int r = FUN_01021ee0((int)lVar10, (int)(lVar10>>32), (int)param_1, uVar8);
            if (r != 0) {
                *(volatile unsigned char*)(base+0x4b) = (unsigned char)uVar8;
                return 2;
            }
            {
                unsigned int iVar6 = (unsigned int)param_2 * 0x20;
                unsigned int iVar7 = (unsigned int)param_2*3;
                unsigned char b1, b4, b3 = 0;
                unsigned int off2;

                b1 = *(volatile unsigned char*)(base+iVar7+0x30);
                *(volatile unsigned char*)(base+iVar7+0x30) = *(volatile unsigned char*)(base + (uVar8+(unsigned int)param_2*0x20)*2 + 0x51);
                b4 = b1;
                do {
                    b3 = b4;
                    uVar9 = b3;
                    off2 = base + (iVar6+uVar9)*2;
                    *(volatile unsigned char*)(off2+0x50) = 4;
                    b4 = *(volatile unsigned char*)(off2+0x51);
                } while (uVar8 != uVar9);

                iVar7 = (unsigned int)param_2*3;
                b4 = *(volatile unsigned char*)(base+iVar7+0x32);
                if (b4 == 0x20) {
                    *(volatile unsigned char*)(base+iVar7+0x31) = b1;
                } else {
                    *(volatile unsigned char*)(base + ((unsigned int)b4+iVar6)*2 + 0x51) = b1;
                }
                *(volatile unsigned char*)(base+(unsigned int)param_2*3+0x32) = b3;
                *(volatile unsigned char*)(base+(iVar6+uVar9)*2+0x51) = 0x20;
                return 0;
            }
        }
    }
}

