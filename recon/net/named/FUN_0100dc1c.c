/* readable reconstruction; identity: FUN_0100dc1c @ 0x0100dc1c
 * public-name: FUN_0100dc1c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100dc1c @ 0x100dc1c  (parity 300 trials PROVEN) */
extern unsigned char FUN_0100d878(void *a0, unsigned int a1, unsigned short a2);

unsigned int FUN_0100dc1c(int param_1, int param_2, int param_3)
{
    unsigned char uVar1;
    char cVar2;
    int iVar3;
    unsigned int uVar4;
    unsigned int uVar5;
    unsigned int uVar6;

    uVar6 = (unsigned int)*(volatile unsigned char *)(param_1 + 0x30);
    if (0x24 < uVar6 - 1) {
        return 0x12;
    }
    if (param_3 == 0) {
        return 0;
    }
    if (*(volatile char *)(param_1 + 0x25) != 0) {
        if (*(volatile char *)(param_1 + 0x25) != 1) {
            return 0x1f;
        }
        uVar1 = FUN_0100d878((void *)(param_1 + 0x25), *(volatile unsigned int *)(param_2 + 0x18),
                              *(volatile unsigned short *)(param_1 + 0x14));
        *(volatile unsigned char *)(param_1 + 0x33) = uVar1;
        return 0;
    }
    iVar3 = param_3 * (unsigned int)*(volatile unsigned char *)(param_1 + 0x31) + (unsigned int)*(volatile unsigned char *)(param_1 + 0x32);
    uVar4 = iVar3 + ((int)(((long long)(int)0xdd67c8a7 * (long long)iVar3) >> 0x20) + iVar3 >> 5) * -0x25;
    uVar5 = uVar4 & 0xff;
    *(volatile char *)(param_1 + 0x32) = (char)uVar4;
    if (((unsigned int)*(volatile unsigned char *)(param_1 + (uVar5 >> 3) + 0x26) & (1u << (uVar4 & 7))) != 0) {
        *(volatile char *)(param_1 + 0x33) = (char)uVar4;
        return 0;
    }
    uVar4 = (uVar5 - uVar6 * (uVar5 / uVar6)) & 0xff;
    uVar6 = (uVar4 + 1) & 0xff;
    if (*(volatile unsigned char *)(param_1 + 0x2b) < uVar6) {
        uVar6 = (uVar6 - *(volatile unsigned char *)(param_1 + 0x2b)) & 0xff;
LAB_0100dcae:
        if (*(volatile unsigned char *)(param_1 + 0x2c) < uVar6) {
            uVar6 = (uVar6 - *(volatile unsigned char *)(param_1 + 0x2c)) & 0xff;
        } else {
            uVar5 = (unsigned int)*(volatile unsigned char *)(param_1 + 0x27);
            uVar4 = uVar5 & 1;
            if (((*(volatile unsigned char *)(param_1 + 0x27) & 1) != 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0))
                goto LAB_0100df5e;
            if (((int)(uVar5 << 0x1e) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 1; goto LAB_0100df3a; }
            if (((int)(uVar5 << 0x1d) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 1; goto LAB_0100df40; }
            if (((int)(uVar5 << 0x1c) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 1; goto LAB_0100df46; }
            if (((int)(uVar5 << 0x1b) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 1; goto LAB_0100df4c; }
            if (((int)(uVar5 << 0x1a) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 1; goto LAB_0100df52; }
            if (((int)(uVar5 << 0x19) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 1; goto LAB_0100df58; }
            if (((int)(uVar5 << 0x18) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar4 = 1; goto LAB_0100dd54; }
        }
        if (*(volatile unsigned char *)(param_1 + 0x2d) < uVar6) {
            uVar6 = (uVar6 - *(volatile unsigned char *)(param_1 + 0x2d)) & 0xff;
        } else {
            uVar4 = (unsigned int)*(volatile unsigned char *)(param_1 + 0x28);
            if (((int)(uVar4 << 0x1f) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar4 = 2; goto LAB_0100df5e; }
            if (((int)(uVar4 << 0x1e) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 2; goto LAB_0100df3a; }
            if (((int)(uVar4 << 0x1d) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 2; goto LAB_0100df40; }
            if (((int)(uVar4 << 0x1c) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 2; goto LAB_0100df46; }
            if (((int)(uVar4 << 0x1b) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 2; goto LAB_0100df4c; }
            if (((int)(uVar4 << 0x1a) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 2; goto LAB_0100df52; }
            if (((int)(uVar4 << 0x19) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 2; goto LAB_0100df58; }
            if (((int)(uVar4 << 0x18) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar4 = 2; goto LAB_0100dd54; }
        }
        if (*(volatile unsigned char *)(param_1 + 0x2e) < uVar6) {
            uVar6 = (uVar6 - *(volatile unsigned char *)(param_1 + 0x2e)) & 0xff;
        } else {
            uVar4 = (unsigned int)*(volatile unsigned char *)(param_1 + 0x29);
            if (((int)(uVar4 << 0x1f) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar4 = 3; goto LAB_0100df5e; }
            if (((int)(uVar4 << 0x1e) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 3; goto LAB_0100df3a; }
            if (((int)(uVar4 << 0x1d) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 3; goto LAB_0100df40; }
            if (((int)(uVar4 << 0x1c) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 3; goto LAB_0100df46; }
            if (((int)(uVar4 << 0x1b) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 3; goto LAB_0100df4c; }
            if (((int)(uVar4 << 0x1a) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 3; goto LAB_0100df52; }
            if (((int)(uVar4 << 0x19) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar6 = 3; goto LAB_0100df58; }
            if (((int)(uVar4 << 0x18) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) { uVar4 = 3; goto LAB_0100dd54; }
        }
        if (*(volatile unsigned char *)(param_1 + 0x2f) < uVar6) {
            return 0x1f;
        }
        uVar4 = (unsigned int)*(volatile unsigned char *)(param_1 + 0x2a);
        if (((int)(uVar4 << 0x1f) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) {
            uVar4 = 4;
LAB_0100df5e:
            cVar2 = 0;
            goto LAB_0100dd56;
        }
        if (((int)(uVar4 << 0x1e) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) {
            uVar6 = 4;
LAB_0100df3a:
            cVar2 = 1;
            uVar4 = uVar6;
            goto LAB_0100dd56;
        }
        if (((int)(uVar4 << 0x1d) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) {
            uVar6 = 4;
LAB_0100df40:
            cVar2 = 2;
            uVar4 = uVar6;
            goto LAB_0100dd56;
        }
        if (((int)(uVar4 << 0x1c) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) {
            uVar6 = 4;
LAB_0100df46:
            cVar2 = 3;
            uVar4 = uVar6;
            goto LAB_0100dd56;
        }
        if (((int)(uVar4 << 0x1b) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) {
            uVar6 = 4;
LAB_0100df4c:
            cVar2 = 4;
            uVar4 = uVar6;
            goto LAB_0100dd56;
        }
        if (((int)(uVar4 << 0x1a) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) {
            uVar6 = 4;
LAB_0100df52:
            cVar2 = 5;
            uVar4 = uVar6;
            goto LAB_0100dd56;
        }
        if (((int)(uVar4 << 0x19) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) {
            uVar6 = 4;
LAB_0100df58:
            cVar2 = 6;
            uVar4 = uVar6;
            goto LAB_0100dd56;
        }
        if (-1 < (int)(uVar4 << 0x18)) {
            return 0x1f;
        }
        if (uVar6 != 1) {
            return 0x1f;
        }
        uVar4 = 4;
    } else {
        uVar5 = (unsigned int)*(volatile unsigned char *)(param_1 + 0x26);
        if (((*(volatile unsigned char *)(param_1 + 0x26) & 1) != 0) && (uVar6 = uVar4, uVar4 == 0)) {
            uVar4 = 0;
            goto LAB_0100df5e;
        }
        if (((int)(uVar5 << 0x1e) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) goto LAB_0100df3a;
        if (((int)(uVar5 << 0x1d) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) goto LAB_0100df40;
        if (((int)(uVar5 << 0x1c) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) goto LAB_0100df46;
        if (((int)(uVar5 << 0x1b) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) goto LAB_0100df4c;
        if (((int)(uVar5 << 0x1a) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) goto LAB_0100df52;
        if (((int)(uVar5 << 0x19) < 0) && (uVar6 = (uVar6 - 1) & 0xff, uVar6 == 0)) goto LAB_0100df58;
        if ((-1 < (int)(uVar5 << 0x18)) || (uVar6 = (uVar6 - 1) & 0xff, uVar6 != 0)) goto LAB_0100dcae;
        uVar4 = 0;
    }
LAB_0100dd54:
    cVar2 = 7;
LAB_0100dd56:
    *(volatile char *)(param_1 + 0x33) = cVar2 + (char)(uVar4 << 3);
    return 0;
}
