/* Reconstructed FUN_00058bfc @ 0x58bfc */
__attribute__((naked)) void FUN_00058bfc(void *param_1)
{
    __asm volatile(
        "push {r4,lr}\n"
        "mov r4,r0\n"
        "add r3,r0,#0x118\n"
        "1: ldaex r1,[r3]\n"
        "orr r1,r1,#4\n"
        "stlex r2,r1,[r3]\n"
        "cmp r2,#0\n"
        "bne 1b\n"
        "sub r0,r4,#8\n"
        "bl FUN_00081c22\n"
        "add r0,r4,#0x158\n"
        "ldr r1,=0x00059921\n"
        "bl FUN_000732d4\n"
        "ldr r0,[r4]\n"
        "pop {r4,lr}\n"
        "b ext5c6c8\n");
}
