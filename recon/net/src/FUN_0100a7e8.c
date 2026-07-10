/* net-core FUN_0100a7e8 @ 0x100a7e8  (parity 300 trials PROVEN) */
/* net-core FUN_0100a7e8 @ 0x100a7e8  (parity 300 trials PROVEN) */

typedef unsigned int uint;
static inline int isCurrentModePrivileged(void){unsigned c;__asm__ volatile("mrs %0, control":"=r"(c));return (c&1)==0;}
static inline int isIRQinterruptsEnabled(void){unsigned p;__asm__ volatile("mrs %0, primask":"=r"(p));return (p&1)==0;}
static inline void disableIRQinterrupts(void){__asm__ volatile("cpsid i":::"memory");}
static inline void enableIRQinterrupts(void){__asm__ volatile("cpsie i":::"memory");}

extern int FUN_0102a1ea(int);
extern void FUN_0102a208(int);
extern void FUN_0102a21e(void);

void FUN_0100a7e8(unsigned int param_1)
{
    volatile unsigned char * const pc6 = (volatile unsigned char *)0x21000bf4; /* DAT_0100a89c */
    volatile unsigned int * const p4  = (volatile unsigned int *)0x4100d000;  /* DAT_0100a8a0 */
    volatile unsigned int * const p_sb = (volatile unsigned int *)0xe000ed00; /* DAT_0100a8a4 */
    volatile unsigned int * const p_ir = (volatile unsigned int *)0xe000e100; /* DAT_0100a8a8 */

    for (;;) {
        int iVar6 = FUN_0102a1ea((int)(long)pc6);
        if (iVar6 != 0) {
            pc6[1] = 0xff;
        }
        for (;;) {
            p4[1] = 1;
            p4[0x40] = 0;
            p4[0x41] = 0;
            p4[0x141] = param_1;
            p4[0] = 1;
            while (p4[0x40] == 0 && p4[0x41] == 0) {
                if ((int)(p_sb[4] << 0x1b) < 0) {
                    p_ir[0x180/4] = 0x2000;
                    int iVar7 = 0;
                    if (isCurrentModePrivileged()) {
                        iVar7 = isIRQinterruptsEnabled();
                    }
                    disableIRQinterrupts();
                    p4[0xc1] = 3;
                    if (p4[0x40] == 0 && p4[0x41] == 0) {
                        FUN_0102a21e();
                    }
                    if (iVar7 == 0) {
                        enableIRQinterrupts();
                    }
                }
            }
            if (p4[0x41] == 0) break;
        }
        if (iVar6 == 0) {
            unsigned char cVar1 = pc6[1];
            pc6[1] = 0;
            p4[0xc2] = 3;
            p4[0x41] = 0;
            p4[0x40] = 0;
            p_ir[0x180/4] = 0x2000;
            FUN_0102a208((int)(long)pc6);
            if (cVar1 == 0) {
                return;
            }
        } else {
            return;
        }
    }
}


