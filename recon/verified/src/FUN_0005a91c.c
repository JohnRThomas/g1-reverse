/* Reconstructed FUN_0005a91c @ 0x5a91c  (parity: 300/300 trials, PROVEN) */

extern int FUN_000826b2(void *a, unsigned int b);
extern void FUN_00082b98(void *a, unsigned int b);
extern void FUN_0005a8bc(unsigned int a, void *b);

void FUN_0005a91c(void)
{
    unsigned int uVar1 = 0x000f2b3aUL;
    int iVar4 = 0;
    unsigned char *puVar3 = (unsigned char *)0x2000aed4UL;
    int iVar2;
    do {
        iVar2 = FUN_000826b2((void*)(puVar3+1), uVar1);
        if (iVar2 == 0) {
            FUN_00082b98((void*)puVar3, 0);
            FUN_0005a8bc(*(volatile unsigned char*)puVar3, (void*)(puVar3+1));
        }
        iVar4 = iVar4 + 1;
        puVar3 = puVar3 + 0x10;
    } while (iVar4 != 3);
}

