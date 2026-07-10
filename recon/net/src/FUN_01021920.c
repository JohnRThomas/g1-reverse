/* net-core FUN_01021920 @ 0x1021920  (parity 300 trials PROVEN) */

typedef void (*code)(void);
void FUN_01021920(void)
{
    ((code)(*(volatile unsigned int*)(*(volatile unsigned int*)0x21000530UL + 4)))();
}

