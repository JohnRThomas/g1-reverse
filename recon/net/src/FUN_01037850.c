/* net-core FUN_01037850 @ 0x1037850  (parity 300 trials PROVEN) */

extern int FUN_0103610c(unsigned int);
extern void FUN_01036144(unsigned int);
extern void FUN_01037814(int);
extern int FUN_01036128(unsigned int);
extern int FUN_01039bbe(int, int, int);
extern void FUN_01039bb0(int, int) __attribute__((noreturn));
extern void FUN_010380d8(int);

void FUN_01037850(int param_1)
{
    unsigned int basepri_save;
    __asm__ volatile (
        "mrs %0, basepri\n"
        "movs r3, #0x40\n"
        "msr basepri_max, r3\n"
        "isb sy\n"
        : "=r"(basepri_save) :: "r3","memory");

    int iVar3 = FUN_0103610c(0x21004b68);
    if (iVar3 == 0) {
        FUN_01039bbe(0x103d2a7, 0x103d3b6, 0x72);
        FUN_01039bb0(0x103d3b6, 0x72);
    }
    FUN_01036144(0x21004b68);
    if (*(int*)(param_1 + 8) != 0) {
        FUN_01037814(param_1);
    }
    iVar3 = FUN_01036128(0x21004b68);
    if (iVar3 == 0) {
        FUN_01039bbe(0x103d2a7, 0x103d3b6, 0xf0);
        FUN_01039bb0(0x103d3b6, 0xf0);
    }
    __asm__ volatile ("msr basepri, %0\nisb sy\n" :: "r"(basepri_save) : "memory");
    FUN_010380d8(param_1 + 0x18);
}

