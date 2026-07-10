/* net-core FUN_01036c2c @ 0x1036c2c  (parity 300 trials PROVEN) */

extern void FUN_01039bbe(void*, void*, unsigned int);
extern void FUN_01039bb0(void*, unsigned int);
extern int FUN_0103610c(void*);
extern void FUN_01036144(void*);
extern int FUN_01036128(void*);
extern int FUN_01036b18(int, void*);

__attribute__((naked)) unsigned int FUN_01036c2c(unsigned int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    __asm__ volatile(
        "push {r0, r1, r2, r4, r5, lr}\n"
        "mov r4, r1\n"
        "str r0, [sp, #4]\n"
        "cbnz r1, 1f\n"
        "ldr r1, =0x0103eaed\n"
        "ldr r0, =0x0103d2a7\n"
        "mov.w r2, #0x174\n"
        "bl FUN_01039bbe\n"
        "mov.w r1, #0x174\n"
        "ldr r0, =0x0103eaed\n"
        "bl FUN_01039bb0\n"
        "1:\n"
        "mov.w r3, #0x40\n"
        "mrs r5, basepri\n"
        "msr basepri_max, r3\n"
        "isb sy\n"
        "ldr r0, =0x21004b58\n"
        "bl FUN_0103610c\n"
        "cbnz r0, 2f\n"
        "ldr r1, =0x0103d3b6\n"
        "movs r2, #0x72\n"
        "ldr r0, =0x0103d2a7\n"
        "bl FUN_01039bbe\n"
        "movs r1, #0x72\n"
        "3:\n"
        "ldr r0, =0x0103d3b6\n"
        "b 6f\n"
        "2:\n"
        "ldr r0, =0x21004b58\n"
        "bl FUN_01036144\n"
        "mov r0, r4\n"
        "add r1, sp, #4\n"
        "bl FUN_01036b18\n"
        "mov r4, r0\n"
        "ldr r0, =0x21004b58\n"
        "bl FUN_01036128\n"
        "cbnz r0, 4f\n"
        "ldr r1, =0x0103d3b6\n"
        "movs r2, #0xf0\n"
        "ldr r0, =0x0103d2a7\n"
        "bl FUN_01039bbe\n"
        "movs r1, #0xf0\n"
        "ldr r0, =0x0103d3b6\n"
        "b 3b\n"
        "4:\n"
        "msr basepri, r5\n"
        "isb sy\n"
        "mov r0, r4\n"
        "add sp, #0xc\n"
        "pop {r4, r5, pc}\n"
        "6:\n"
        "bl FUN_01039bb0\n"
    );
}

