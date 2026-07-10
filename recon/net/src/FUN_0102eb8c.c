/* net-core FUN_0102eb8c @ 0x102eb8c  (parity 300 trials PROVEN) */
/* net-core FUN_0102eb8c @ 0x102eb8c  (parity 300 trials PROVEN) */
/* net-core FUN_0102eb8c @ 0x102eb8c  (parity 300 trials PROVEN) */
/* net-core FUN_0102eb8c @ 0x102eb8c  (parity 300 trials PROVEN) */

extern void FUN_01039bbe(int,int,int,int,int);
extern void FUN_01039bb0(int,int);
__attribute__((naked)) void FUN_0102eb8c(void)
{
    __asm__ volatile(
        "push {r3,lr}\n"
        "lsls r3, r2, #0x1f\n"
        "bmi 1f\n"
        "adds r1, #2\n"
        "cmp r1, #7\n"
        "bls 2f\n"
        "ldr r1, =0x0103d8c5\n"
        "ldr r0, =0x0103d2a7\n"
        "movs r2, #0x5c\n"
        "bl FUN_01039bbe\n"
        "movs r1, #0x5c\n"
        "ldr r0, =0x0103d8c5\n"
        "bl FUN_01039bb0\n"
        "1:\n"
        "movs r1, #0\n"
        "2:\n"
        "sxtb r0, r0\n"
        "cmp r0, #0\n"
        "ite ge\n"
        "addge.w r0, r0, #-0x20000000\n"
        "ldrlt r3, =0xe000ed14\n"
        "lsl.w r1, r1, #5\n"
        "uxtb r1, r1\n"
        "itete ge\n"
        "addge.w r0, r0, #0xe100\n"
        "andlt r0, r0, #0xf\n"
        "strbge.w r1, [r0, #0x300]\n"
        "strblt r1, [r3, r0]\n"
        "pop {r3,pc}\n"
    );
}




