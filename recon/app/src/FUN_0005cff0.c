/* Reconstructed FUN_0005cff0 @ 0x5cff0  owned extent: 0xae bytes */

extern int  FUN_0005cac0(void);
extern int  FUN_00055cf0(void);
extern void FUN_00083074(unsigned a, unsigned b, void *c);
extern int  FUN_00083090(unsigned a, unsigned b);
extern unsigned FUN_0005e6a8(unsigned char a, unsigned b);
extern int  FUN_0005ce6c(int p);

int FUN_0005cff0(int param_1, int param_2){
    unsigned *src, *dst, *end;
    int iVar4;
    FUN_0005cac0();
    src = *(unsigned **)(param_2 + 0xc);
    dst = (unsigned *)(param_1 + 0x57);
    end = src + 8;
    do { *dst++ = *src++; } while (src != end);
    { unsigned *s2 = src, *d2 = (unsigned*)(param_1 + 0x77), *e2 = s2 + 8;
      do { *d2++ = *s2++; } while (s2 != e2); }
    iVar4 = FUN_00055cf0();
    if (iVar4 != 0){
        int local_18 = 2; unsigned local_14 = 0xf4eb1u; (void)local_14;
        FUN_00083074(0x88180u, 0x10c0u, &local_18);
        FUN_00083090((unsigned)(param_1 + 4), 0xe);
        {
            int p = *(int*)(param_1 + 0xf0);
            if (*(int*)(p + 0xc0) == 0){
                unsigned uVar5 = FUN_0005e6a8(*(unsigned char*)(p + 8), (unsigned)(p + 0x90));
                *(unsigned*)(p + 0xc0) = uVar5;
            }
            {
                int q = *(int*)(p + 0xc0);
                if (q != 0 && (*(unsigned short*)(q + 0xe) & 0x24) != 0
                    && (int)((unsigned)*(unsigned char*)(q + 0xd) << 0x1e) >= 0){
                    return 3;
                }
            }
        }
    }
    if (*(int*)0x2000af48 == 0){
        FUN_00083090((unsigned)(param_1 + 4), 6);
        return 0;
    }
    return FUN_0005ce6c(param_1);
}
