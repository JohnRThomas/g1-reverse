/* net-core FUN_0102c470 @ 0x102c470  (parity 300 trials PROVEN) */
/* net-core FUN_0102c470 @ 0x102c470  (parity 300 trials PROVEN) */

extern int FUN_010397ac(void*, int, int);
extern int FUN_0103973c(void*, int);
extern int FUN_01039768(void*, int);
extern void* FUN_01039774(void*, int);
extern void FUN_010399f6(void*, int);
extern void FUN_01039bbe(void*, void*, unsigned int);
extern void FUN_01039bb0(void*, unsigned int);

__attribute__((naked)) void FUN_0102c470(unsigned int *param_1, int param_2)
{
    __asm__ volatile(
        "push {r4, r5, r6, lr}\n"
        "cbz r1, 5f\n"
        "ldr r6, [r0]\n"
        "movs r2, #1\n"
        "mov r0, r6\n"
        "bl FUN_010397ac\n"
        "mov r1, r0\n"
        "mov r4, r0\n"
        "mov r0, r6\n"
        "bl FUN_0103973c\n"
        "lsls r3, r0, #0x1f\n"
        "bmi 1f\n"
        "ldr r1, =0x0103d373\n"
        "movs r2, #0xaf\n"
        "ldr r0, =0x0103d2a7\n"
        "bl FUN_01039bbe\n"
        "movs r1, #0xaf\n"
        "3:\n"
        "ldr r0, =0x0103d373\n"
        "bl FUN_01039bb0\n"
        "1:\n"
        "mov r1, r4\n"
        "mov r0, r6\n"
        "bl FUN_01039768\n"
        "adds r5, r4, r0\n"
        "mov r1, r5\n"
        "movs r2, #0\n"
        "mov r0, r6\n"
        "bl FUN_0103973c\n"
        "subs r5, r5, r0\n"
        "cmp r4, r5\n"
        "beq 2f\n"
        "ldr r1, =0x0103d373\n"
        "movs r2, #0xb7\n"
        "ldr r0, =0x0103d2a7\n"
        "bl FUN_01039bbe\n"
        "movs r1, #0xb7\n"
        "b 3b\n"
        "2:\n"
        "mov r1, r4\n"
        "mov r0, r6\n"
        "bl FUN_01039774\n"
        "mov r1, r4\n"
        "pop.w {r4, r5, r6, lr}\n"
        "b.w FUN_010399f6\n"
        "5:\n"
        "pop {r4, r5, r6, pc}\n"
    );
}


