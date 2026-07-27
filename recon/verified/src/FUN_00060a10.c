/* Reconstructed FUN_00060a10 @ 0x60a10  (parity: 300/300 trials, PROVEN) */

extern int FUN_00060990(void);
#define g1_recon_nrfx_qspi_init FUN_00066994
extern void g1_recon_nrfx_qspi_init(int,int,int,int,int);
extern void FUN_00072880(int);
extern void FUN_00083906(unsigned long);
extern void FUN_0008392e(int);

int FUN_00060a10(int param_1, int param_2, int param_3, int param_4)
{
    int iVar3 = *(volatile int*)(param_1+0x10);
    int iVar2;
    if (*(volatile char*)(iVar3+0x60) == 0) {
        FUN_00083906(param_1);
        volatile char *pcVar1 = (volatile char*)0x2001d535UL;
        FUN_00072880(iVar3+0x48);
        iVar2 = 0;
        if (*pcVar1 == 0) {
            g1_recon_nrfx_qspi_init(*(volatile int*)(param_1+4), 0x000838cb,
                                    iVar3, 0, param_4);
            iVar2 = FUN_00060990();
            *pcVar1 = (iVar2==0);
        }
        FUN_0008392e(param_1);
    } else {
        iVar2 = 0;
    }
    return iVar2;
}
