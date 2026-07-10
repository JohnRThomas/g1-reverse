/* net-core FUN_0103b14a @ 0x103b14a  (parity 300 trials PROVEN) */

__attribute__((naked)) unsigned int FUN_0103b14a(void)
{
  __asm__ volatile(
    "mrs r0, ipsr\n"
    "subs r0, #0\n"
    "it ne\n"
    "movne r0, #1\n"
    "bx lr\n"
  );
}

