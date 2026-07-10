/* Reconstructed FUN_0007f8dc @ 0x7f8dc  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004ed3c(unsigned a, void*b);
extern unsigned FUN_0007f460(void);
extern unsigned FUN_0007f4c8(unsigned a);
extern void FUN_0007f4d2(void);
extern int FUN_0007f570(unsigned a, int b, void*c);
extern int FUN_00080d3e(unsigned a, void*b);
unsigned FUN_0007f8dc(unsigned param_1, unsigned *param_2, unsigned param_3, unsigned param_4){
    unsigned char local_24[4], local_20[4], local_1c[4];
    volatile unsigned *p2 = (volatile unsigned*)param_2;
    FUN_0007f4d2();
    unsigned *puVar2 = (unsigned*)FUN_0007f460();
    unsigned pv = *(volatile unsigned*)puVar2;
    local_1c[0] = 0;
    *(volatile unsigned short*)(local_1c + 2) = 0x1801;
    int iVar3 = FUN_00080d3e(pv, local_1c);
    if (iVar3 != 0) return 0xffffff7au;
    p2[0] = 0; p2[1] = 0; p2[10] = 0;
    local_24[0] = 0;
    *(volatile unsigned short*)(local_24 + 2) = 0x2a05;
    int h = FUN_0004ed3c(param_1, local_24);
    if (h == 0) return 0xffffffeau;
    local_20[0] = 0;
    *(volatile unsigned short*)(local_20 + 2) = 0x2a05;
    int iVar4 = FUN_0007f570(param_1, h, local_20);
    if (iVar4 == 0) return 0xffffffeau;
    *(volatile unsigned short*)((char*)param_2 + 4) = *(volatile unsigned short*)(iVar4 + 4);
    local_1c[0] = 0;
    *(volatile unsigned short*)(local_1c + 2) = 0x2902;
    int iVar3b = FUN_0007f570(param_1, h, local_1c);
    if (iVar3b == 0) return 0xffffffeau;
    *(volatile unsigned short*)((char*)param_2 + 6) = *(volatile unsigned short*)(iVar3b + 4);
    unsigned uVar5 = FUN_0007f4c8(param_1);
    p2[0] = uVar5;
    return 0;
}

