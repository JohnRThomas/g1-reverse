/* net-core FUN_0101f680 @ 0x101f680  (parity 300 trials PROVEN) */

extern void FUN_0101f894(int);
extern void FUN_0101dbe8(void);
#define DAT_0101f694 ((unsigned int)0x21001208)
#define DAT_0101f698 ((unsigned int)0x0101ec69)

void FUN_0101f680(void)
{
    FUN_0101f894(5);
    FUN_0101dbe8();
    *(volatile unsigned int *)(DAT_0101f694 + 0x24) = DAT_0101f698;
    return;
}

