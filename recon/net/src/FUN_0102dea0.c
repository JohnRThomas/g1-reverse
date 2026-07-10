/* net-core FUN_0102dea0 @ 0x102dea0  (parity 300 trials PROVEN) */

extern void FUN_0102cbd8(unsigned int, unsigned int);
void FUN_0102dea0(void)
{
    unsigned int uVar1 = 0x2100086c;
    volatile unsigned int * const p = (volatile unsigned int * const)0x2100465c;
    FUN_0102cbd8(uVar1, 0x103c900);
    *p = uVar1;
}

