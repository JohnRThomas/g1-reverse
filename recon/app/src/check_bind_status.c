/* Reconstructed check_bind_status @ 0x26b88  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
typedef unsigned int u32;
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

void check_bind_status(int param_1, int param_2, int param_3)
{
    volatile char *pcVar2 = (volatile char*)0x20018d83UL;
    char cVar1;
    char *base;

    if (param_2 == 0) {
        cVar1 = *pcVar2;
        if (cVar1 != 0) {
            char nv = (char)(cVar1 - 1);
            *pcVar2 = nv;
            if (nv != 0) return;
        }
        base = (char*)(param_1 + 0x1000);
        if (base[0x71] != 1) return;
        base[0x71] = 0;
        if (*(volatile int*)0x2000230cUL <= 0) return;
        if (*(volatile u32*)0x20007554UL == 0) {
            DEBUG_PRINT(0x9fd02U, 0xa1ad8U);
        } else {
            FUN_00019c70(0x9fd02U, 0xa1ad8U);
        }
        return;
    } else {
        base = (char*)(param_1 + 0x1000);
        if (param_3 == 0) {
            if (base[0x71] == 0) {
                base[0x71] = 1;
                if (*(volatile int*)0x2000230cUL > 0) {
                    if (*(volatile u32*)0x20007554UL == 0) {
                        DEBUG_PRINT(0x9fce4U, 0xa1ad8U);
                    } else {
                        FUN_00019c70(0x9fce4U, 0xa1ad8U);
                    }
                }
            }
        } else {
            base[0x71] = 0;
        }
        *pcVar2 = 3;
    }
}

