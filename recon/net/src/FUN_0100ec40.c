/* net-core FUN_0100ec40 @ 0x100ec40  (parity 300 trials PROVEN) */

extern void FUN_0102583c(unsigned int a);

void FUN_0100ec40(void)
{
    unsigned char *puVar2 = (unsigned char *)0x21000ec8;
    unsigned int primask;
    unsigned int *puVar5;
    unsigned int uVar3;
    if (puVar2[0x20] != 0) return;
    *(unsigned int *)(puVar2 + 0x1c) = 0x0100f2e5;
    puVar2[0x20] = 2;
    __asm__ volatile ("mrs %0, primask" : "=r"(primask));
    __asm__ volatile ("cpsid i" ::: "memory");
    puVar5 = (unsigned int *)(puVar2 + 8);
    *(unsigned int **)(puVar2 + 0x18) = puVar5;
    uVar3 = 0x21000ee0;
    if ((*(int *)(puVar2+8) == 0) || (*(char*)(*(int*)(puVar2+8)+8) != 1)) {
        puVar5 = *(unsigned int **)(puVar2+4);
    }
    *puVar5 = uVar3;
    *(unsigned int *)(puVar2+4) = uVar3;
    if (primask == 0) { __asm__ volatile("cpsie i" ::: "memory"); }
    FUN_0102583c(*puVar2);
}

