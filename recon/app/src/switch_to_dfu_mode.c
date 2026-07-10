/* Reconstructed switch_to_dfu_mode @ 0x158bc  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
typedef unsigned int u32;
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void FUN_00019c70(unsigned int, unsigned int, unsigned int, unsigned int);
extern int FUN_00086406(void);
extern void FUN_0007c038(int);
extern int FUN_0004c0a8(int);
extern void thunk_FUN_00072880(unsigned int);

void switch_to_dfu_mode(unsigned int param_1)
{
    volatile u8 *puVar1 = (volatile u8*)0x2000ff6eUL;
    int iVar2;
    unsigned int r2val;
    typedef int (*fnptr)(unsigned int, void*, int);

    *puVar1 = 1;
    iVar2 = FUN_00086406();
    if (iVar2 != 0) {
        thunk_FUN_00072880(param_1);
        return;
    }
    {
        fnptr f = *(fnptr*)((*(volatile u32*)0x200069fcUL) + 0x1040);
        iVar2 = f(0x990cfU, (void*)puVar1, 1);
    }
    if (iVar2 == 0) {
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile u32*)0x20007554UL != 0) {
                FUN_00019c70(0x99105U, 0x99b2aU, 0, *puVar1);
                goto loop_start;
            } else {
                r2val = 0;
                goto print_lab;
            }
        }
        goto loop_start;
    } else {
        if (*(volatile int*)0x2000230cUL < 1) return;
        if (*(volatile u32*)0x20007554UL != 0) {
            FUN_00019c70(0x990dcU, 0x99b2aU, (unsigned int)iVar2, 0);
            return;
        }
        DEBUG_PRINT(0x990dcU, 0x99b2aU);
        return;
    }
loop_start:
    for (;;) {
        FUN_0007c038(500);
        r2val = (unsigned int)FUN_0004c0a8(1);
print_lab:
        DEBUG_PRINT(0x99105U, 0x99b2aU, r2val);
    }
}

