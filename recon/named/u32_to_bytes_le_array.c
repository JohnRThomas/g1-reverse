/* named: u32_to_bytes_le_array */
/* Reconstructed u32_to_bytes_le_array @ 0x7d894  (parity: 300/300 trials, PROVEN) */

__attribute__((naked))
void u32_to_bytes_le_array(unsigned char *param_1, int param_2, unsigned int param_3)
{
    __asm__ volatile(
        "mov r3, r0\n"
        "push {r4, lr}\n"
        "subs r1, #4\n"
        "1: adds r4, r3, #4\n"
        "subs r3, r3, r0\n"
        "cmp r2, r3\n"
        "bhi 2f\n"
        "pop {r4, pc}\n"
        "2: ldr r3, [r1, #4]!\n"
        "strb r3, [r4, #-4]\n"
        "ldr r3, [r1]\n"
        "lsrs r3, r3, #8\n"
        "strb r3, [r4, #-3]\n"
        "ldrh r3, [r1, #2]\n"
        "strb r3, [r4, #-2]\n"
        "ldrb r3, [r1, #3]\n"
        "strb r3, [r4, #-1]\n"
        "mov r3, r4\n"
        "b 1b\n"
        ::: "memory"
    );
}

