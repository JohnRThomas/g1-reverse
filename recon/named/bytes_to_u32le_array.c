/* named: bytes_to_u32le_array */
/* Reconstructed bytes_to_u32le_array @ 0x7d8c4  (parity: 300/300 trials, PROVEN) */

__attribute__((naked))
void bytes_to_u32le_array(int param_1, unsigned char *param_2, unsigned int param_3)
{
    __asm__ volatile(
        "push {r4, r5, lr}\n"
        "movs r4, #0\n"
        "1: cmp r4, r2\n"
        "add.w r1, r1, #4\n"
        "blo 2f\n"
        "pop {r4, r5, pc}\n"
        "2: ldrb r3, [r1, #-0x2]\n"
        "ldrb r5, [r1, #-0x3]\n"
        "lsls r3, r3, #0x10\n"
        "orr.w r3, r3, r5, lsl #8\n"
        "ldrb r5, [r1, #-0x4]\n"
        "orrs r3, r5\n"
        "ldrb r5, [r1, #-0x1]\n"
        "orr.w r3, r3, r5, lsl #24\n"
        "str r3, [r0, r4]\n"
        "adds r4, #4\n"
        "b 1b\n"
        ::: "memory"
    );
}

