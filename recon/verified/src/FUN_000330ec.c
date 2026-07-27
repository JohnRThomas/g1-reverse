/* Reconstructed FUN_000330ec @ 0x330ec  (parity: 300/300 trials, PROVEN) */
extern void FUN_0007dda4(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_0002a4d8(int,...);
extern int FUN_0002eaa8(void);
extern int FUN_0002eb28(int,...);
extern int FUN_0002f008(void);
extern int FUN_00030cb8(void);
extern int FUN_00030cc4(void);
extern int FUN_00030cd0(int,...);
extern int FUN_00032b24(int,...);
extern int FUN_0004c0a8(int,...);
extern int FUN_0007d0e8(int,...);
extern int FUN_0007d194(int,...);
extern int change_work_mode_to(int,...);

unsigned FUN_000330ec(unsigned param_1)
{
    unsigned uVar6 = 0x20019ff5;
    unsigned uVar4;
    int iVar3;
    unsigned char *pbVar5;
    unsigned char *L = (unsigned char *)0x2001a0f5UL;
    unsigned local_28 = 0;
    unsigned local_24 = 0;
    unsigned local_20 = 0x20019ff5u;
    unsigned char *local_1c = L;
    unsigned int mode;
    int channel;

    if ((*(volatile int *)0x20002424UL == 0) || (*(volatile int *)0x20002428UL == 0) ||
        ((char)*(volatile unsigned char *)0x2000242cUL == 2)) {
        FUN_0007dda4(0x000a776c);
        return 0xffffffff;
    }

    FUN_00030cb8();
    mode = *(volatile unsigned char *)0x2000242cu;
    channel = *(volatile int *)0x20002424u;
    if (mode != 0)
        channel = *(volatile int *)0x20002428u;
    iVar3 = FUN_0007d0e8(mode, channel, &local_20, &local_24);
    if (iVar3 != 0) { FUN_00030cc4(); return 0xfffffffe; }

    iVar3 = FUN_00032b24(mode, uVar6, local_24 & 0xff,
                         &local_1c, &local_28, param_1);
    if (iVar3 != 0) { FUN_0007dda4(0x000a7780); FUN_00030cc4(); return 0xfffffffd; }

    channel = *(volatile int *)0x20002424u;
    if (mode != 0)
        channel = *(volatile int *)0x20002428u;
    iVar3 = FUN_00030cd0(mode, channel, local_1c, local_28 & 0xff);
    if (iVar3 != 0) { FUN_0007dda4(0x000a779f); FUN_00030cc4(); return 0xfffffffc; }

    FUN_00030cc4();
    if (local_1c[9] == 0x80) {
        FUN_0007d194(1000);
        local_1c[9] = 0;
        FUN_00030cb8();
        FUN_00030cd0(mode, *(volatile int *)0x20002424u,
                     local_1c, local_28 & 0xff);
        FUN_00030cc4();
    }

    pbVar5 = local_1c;
    if (mode != 0) pbVar5 = local_1c + 4;
    uVar4 = (unsigned)*pbVar5;
    uVar6 = 0;
    if (uVar4 == 0x1b) {
        if (pbVar5[8] != 0) FUN_0002f008();
    } else if (uVar4 == 0x13) {
        if (((pbVar5[4] & 0xfb) == 0) && (iVar3 = FUN_0002eaa8(), iVar3 != 0)) uVar6 = 0xfffffffb;
    } else {
        if (uVar4 != 6) {
            if (uVar4 != 0xb) goto LAB_0003325a;
            pbVar5 = (unsigned char *)*(volatile int *)0x2000230cUL;
            if ((int)pbVar5 < 1) goto LAB_0003324c;
            pbVar5 = (unsigned char *)*(volatile int *)0x20007554UL;
            do {
                if (pbVar5 == 0) FUN_0007dda4(0x000a77cc, 0x000a7882);
                else FUN_00019c70(0x000a77cc, 0x000a7882);
LAB_0003324c:
                do {
                    while (1) {
                        FUN_0007d194(300);
                        FUN_0004c0a8(1);
LAB_0003325a:
                        if (uVar4 != 0x3c) break;
                        if (pbVar5[4] != 0) return 0;
                        pbVar5 = (unsigned char *)*(volatile int *)0x2000230cUL;
                        if (0 < (int)pbVar5) {
                            pbVar5 = (unsigned char *)*(volatile int *)0x20007554UL;
                            if (pbVar5 == 0) FUN_0007dda4(0x000a780d, 0x000a7882);
                            else FUN_00019c70(0x000a780d, 0x000a7882);
                        }
                    }
                    if (uVar4 != 1) return 0;
                    if (pbVar5[4] != 0) return 0;
                    pbVar5 = (unsigned char *)*(volatile int *)0x2000230cUL;
                } while ((int)pbVar5 < 1);
                pbVar5 = (unsigned char *)*(volatile int *)0x20007554UL;
            } while (1);
        }
        if (pbVar5[2] == 2) {
            *(volatile unsigned char *)0x20018d94UL = 1;
            FUN_0002eb28(1);
            FUN_0002a4d8(10000);
        } else {
            FUN_0007dda4(0x000a77b5);
            FUN_0007d194(10000);
            change_work_mode_to(7);
        }
    }
    return uVar6;
}
