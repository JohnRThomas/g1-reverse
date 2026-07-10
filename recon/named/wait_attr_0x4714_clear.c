/* named: wait_attr_0x4714_clear */
/* Reconstructed wait_attr_0x4714_clear @ 0x7cfac  (parity: 300/300 trials, PROVEN) */

extern void attr_store_retry_delay(int a);
extern int attr_store_get(unsigned int a, int *b);

int wait_attr_0x4714_clear(void)
{
    int iVar1;
    int iVar2 = 100;
    int local_c = 0;
    int bVar3;
    do {
        iVar1 = attr_store_get(0x4714, &local_c);
        if (iVar1 != 0) {
            return iVar1;
        }
        if (local_c == 0) break;
        attr_store_retry_delay(1);
        bVar3 = iVar2 != 0;
        iVar2 = iVar2 - 1;
    } while (bVar3);
    iVar1 = -1;
    if (iVar2 != -1) {
        iVar1 = 0;
    }
    return iVar1;
}

