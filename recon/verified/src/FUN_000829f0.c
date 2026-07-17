/* Reconstructed FUN_000829f0 @ 0x829f0  (parity: 300/300 trials, PROVEN) */

extern int FUN_0000ef12(const void *);
extern unsigned int FUN_00054ce0(void);
extern void FUN_00082932(int,int,int,unsigned int,unsigned short);
void FUN_000829f0(int param_1, int param_2, int param_3, int param_4,
                  unsigned short param_5)
{
    unsigned int text = FUN_00054ce0();
    unsigned short length =
        (unsigned short)FUN_0000ef12((const void *)(unsigned long)text);
    FUN_00082932(param_3, param_4, param_5, text, length);
}
