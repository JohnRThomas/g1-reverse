/* net-core FUN_0100886c @ 0x100886c  (parity 300 trials PROVEN) */

__attribute__((naked)) void FUN_0100886c(int *param_1, unsigned int *param_2, unsigned int *param_3)
{
    __asm__ volatile(
        "push.w {r4, r5, r6, r7, r8, sb, sl}\n"
        "ldm.w r1, {r3, r4, r5, r6, r7, r8, sb, sl}\n"
        "ldm.w r2!, {r1, ip}\n"
        "adds r3, r3, r1\n"
        "adcs.w r4, r4, ip\n"
        "ldm.w r2!, {r1, ip}\n"
        "adcs r5, r1\n"
        "adcs.w r6, r6, ip\n"
        "ldm.w r2!, {r1, ip}\n"
        "adcs r7, r1\n"
        "adcs.w r8, r8, ip\n"
        "ldm.w r2!, {r1, ip}\n"
        "adcs.w sb, sb, r1\n"
        "adcs.w sl, sl, ip\n"
        "sbcs r1, r1\n"
        "subs.w r3, r3, #-1\n"
        "sbcs r4, r4, #-1\n"
        "sbcs r5, r5, #-1\n"
        "sbcs r6, r6, #0\n"
        "sbcs r7, r7, #0\n"
        "sbcs r8, r8, #0\n"
        "sbcs sb, sb, #1\n"
        "sbcs sl, sl, #-1\n"
        "adcs r1, r1, #0\n"
        "adds r3, r3, r1\n"
        "adcs r4, r1\n"
        "adcs r5, r1\n"
        "adcs r6, r6, #0\n"
        "adcs r7, r7, #0\n"
        "adcs r8, r8, #0\n"
        "adcs.w sb, sb, r1, lsr #31\n"
        "adcs.w sl, sl, r1\n"
        "stm.w r0, {r3, r4, r5, r6, r7, r8, sb, sl}\n"
        "pop.w {r4, r5, r6, r7, r8, sb, sl}\n"
        "bx lr\n"
    );
}

