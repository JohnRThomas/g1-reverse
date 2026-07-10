/* net-core FUN_01035068 @ 0x1035068  (parity 300 trials PROVEN) */

extern void FUN_0102eb48(int a);
extern void FUN_01035028(int *a);

void FUN_01035068(int *param_1)
{
    FUN_0102eb48((*param_1 << 0xc) >> 0x18);
    *(unsigned int *)(*param_1 + 0x200) = 0;
    *(unsigned int *)(*param_1 + 0x308) = 0xffffffff;
    FUN_01035028(param_1);
    *(unsigned char *)((unsigned int)(*((unsigned char *)param_1 + 4)) * 0xc + 0x21004af8 + 8) = 0;
}

