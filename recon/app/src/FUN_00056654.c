/* Reconstructed FUN_00056654 @ 0x56654 */
__attribute__((naked)) int FUN_00056654(int param_1)
{
    __asm volatile(
        "push {r4,lr}\n"
        "cbz r0,1f\n"
        "add r2,r0,#0xd0\n"
        "2: lda r3,[r2]\n"
        "cbz r3,5f\n"
        "adds r1,r3,#1\n"
        "3: ldaex r4,[r2]\n"
        "cmp r4,r3\n"
        "bne 4f\n"
        "stlex r12,r1,[r2]\n"
        "cmp r12,#0\n"
        "bne 3b\n"
        "4: bne 2b\n"
        "pop {r4,pc}\n"
        "1: ldr r1,=0x000f3ebd\n"
        "ldr r0,=0x00099cbd\n"
        "movw r3,#0x509\n"
        "ldr r2,=0x000f3a5d\n"
        "bl FUN_0007e2fa\n"
        "movw r1,#0x509\n"
        "ldr r0,=0x000f3a5d\n"
        "bl FUN_0007e2ec\n"
        "5: mov r0,r3\n"
        "pop {r4,pc}\n");
}
