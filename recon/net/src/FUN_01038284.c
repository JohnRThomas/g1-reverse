/* net-core FUN_01038284 @ 0x1038284  (parity 300 trials PROVEN) */

extern int FUN_0103610c(unsigned int);
extern void FUN_01036144(unsigned int);
extern unsigned int FUN_01037f00(void);
extern int FUN_01036128(unsigned int);
extern int FUN_01039bbe(int, int, int);
extern void FUN_01039bb0(int, int) __attribute__((noreturn));

unsigned long long FUN_01038284(void)
{
    unsigned int basepri_save;
    __asm__ volatile (
        "mrs %0, basepri\n"
        "movs r3, #0x40\n"
        "msr basepri_max, r3\n"
        "isb sy\n"
        : "=r"(basepri_save) :: "r3","memory");

    int iVar2 = FUN_0103610c(0x21004b70);
    if (iVar2 == 0) {
        FUN_01039bbe(0x103d2a7, 0x103d3b6, 0x72);
        FUN_01039bb0(0x103d3b6, 0x72);
    }
    FUN_01036144(0x21004b70);
    unsigned int uVar3 = FUN_01037f00();
    volatile unsigned int *p = (volatile unsigned int*)0x210044f0;
    unsigned int uVar4 = p[0];
    unsigned int uVar5 = p[1];
    unsigned int r4 = uVar3 + uVar4;
    unsigned int carry = (r4 < uVar3) ? 1 : 0;
    unsigned int r5 = uVar5 + ((unsigned int)((int)uVar3 >> 31)) + carry;
    iVar2 = FUN_01036128(0x21004b70);
    if (iVar2 == 0) {
        FUN_01039bbe(0x103d2a7, 0x103d3b6, 0xf0);
        FUN_01039bb0(0x103d3b6, 0xf0);
    }
    __asm__ volatile ("msr basepri, %0\nisb sy\n" :: "r"(basepri_save) : "memory");
    return ((unsigned long long)r5 << 32) | r4;
}

