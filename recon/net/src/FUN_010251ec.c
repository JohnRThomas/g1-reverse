/* net-core FUN_010251ec @ 0x10251ec  (parity 3 trials PROVEN) */

extern void FUN_010256dc(void);

__attribute__((naked)) int FUN_010251ec(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  __asm__ volatile(
    "cmp r0, #3\n"
    "push {r3, lr}\n"
    "bhi 1f\n"
    "ldr r3, =0x4100c140\n"
    "add.w r0, r3, r0, lsl #2\n"
    "pop {r3, pc}\n"
    "1:\n"
    "subs r0, #4\n"
    "uxtb r0, r0\n"
    "cmp r0, #1\n"
    "bhi 2f\n"
    "ldr r3, =0x41011140\n"
    "add.w r0, r3, r0, lsl #2\n"
    "pop {r3, pc}\n"
    "2:\n"
    "movw r1, #0x3cd\n"
    "movs r0, #0x6c\n"
    "bl FUN_010256dc\n"
  );
}

