/* readable reconstruction; identity: FUN_010171c8 @ 0x010171c8
 * public-name: FUN_010171c8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_010171c8 @ 0x10171c8  (parity 299 trials PROVEN) */
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long long ulonglong;

extern void FUN_01008d00(int,int) __attribute__((noreturn));
extern int FUN_01016430(int,unsigned int);
extern void FUN_01016628(void);
extern int FUN_01016e6c(int,unsigned int);
extern void FUN_0101fca8(void);
extern void FUN_010203d0(void);
extern void FUN_010204d4(int);
extern void FUN_010204e0(unsigned int);
extern void FUN_0102072c(unsigned int);
extern void FUN_01020738(unsigned int);
extern void FUN_01020764(unsigned int);
extern void FUN_010208b0(void);
extern void FUN_01022a50(unsigned char,int,int);
extern void FUN_01025c44(int);

#define IVAR5 0x21000f90
#define MAGIC_RECIP 0xaaaaaaabu
#define MMIO 0x41008000

/* ARM ASR-by-register semantics: shift amount taken mod 256; amounts >=32
   saturate to the sign-extension of the value. v here is always a
   zero-extended byte (0..255), so the saturated result is always 0. */
static unsigned int asr_amt(unsigned int v, unsigned int amt)
{
    amt &= 0xff;
    if (amt >= 32) return 0;
    return v >> amt;
}

unsigned int FUN_010171c8(unsigned int *param_1, unsigned int param_2)
{
    volatile unsigned char *V = (volatile unsigned char*)IVAR5;
    byte bVar1;
    unsigned char uVar2;
    char cVar4;
    int iVar5b, iVar6;
    uint uVar7, uVar8;

    if (V[0x70] > 1 && V[0x70] != 3) {
        return 0xc;
    }

    bVar1 = *(volatile byte*)((int)param_1 + 0xc);
    V[0x98] = bVar1;
    uVar2 = *(volatile unsigned char*)((uint)bVar1 + IVAR5 + 0xbd);
    *(volatile unsigned int*)(IVAR5+0x74) = param_1[2];
    V[0xb9] = uVar2;
    *(volatile unsigned int*)(IVAR5+0x94) = param_1[0];

    if (*(volatile signed char*)((int)param_1+4) == 2) {
        cVar4 = *(volatile signed char*)((int)param_1+0xd);
    } else {
        FUN_010203d0();
        FUN_010208b0();
        FUN_0101fca8();
        FUN_01020738(0x21000344u);
        FUN_0102072c(0x00555555u);
        FUN_010204e0(0x8e89bed6u);
        if (V[0x6c] == 0) FUN_01025c44(1);
        else FUN_01025c44(2);

        if (*(volatile signed char*)((int)param_1+4) != 3) {
            FUN_01020764(param_2);
            if (*(volatile signed char*)((int)param_1+4) != 3) goto LAB_read_cvar4;
        }
        if (*(volatile int*)(IVAR5+0x74) != 0) {
            FUN_01008d00(0x32, 0xa6c);
        }
        iVar6 = FUN_01016e6c(1, param_2);
        if (iVar6 == 0) return 0;
LAB_read_cvar4:
        cVar4 = *(volatile signed char*)((int)param_1+0xd);
    }

    if (cVar4 != 0 && V[0x69] == 0 && *(volatile int*)(IVAR5+100) != 0) {
        FUN_01022a50(V[0x68], *(volatile int*)(IVAR5+100), 1);
    }

    uVar7 = (uint)*(volatile byte*)((int)param_1+4);
    if (uVar7 != 1) {
        if (uVar7 > 1) {
            if (uVar7 - 2 < 2) {
                FUN_010204d4((int)*(volatile signed char*)(IVAR5+0x59));
                V[0x70] = 4;
            }
            goto LAB_end;
        }
        uVar7 = (uint)V[0x7a] + 1;
        uVar8 = (uint)((ulonglong)MAGIC_RECIP * (ulonglong)uVar7 >> 32);
        uVar7 = uVar7 - ((uVar8 & 0x1fe) + (uVar8 >> 1));
        cVar4 = (char)uVar7;
        if ( (asr_amt((uint)V[0x4c], uVar7) & 1u) == 0 ) {
            uVar8 = (uint)((ulonglong)MAGIC_RECIP * (ulonglong)(uVar7+1) >> 32);
            uVar7 = (uVar7+1) - ((uVar8 & 0xfffffffeu) + (uVar8 >> 1));
            cVar4 = (char)uVar7;
            if ( (asr_amt((uint)V[0x4c], uVar7) & 1u) == 0 ) {
                unsigned long long lVar3 = (ulonglong)MAGIC_RECIP * (ulonglong)(uVar7+1);
                cVar4 = (char)(uVar7+1) - (((byte)((ulonglong)lVar3 >> 32) & 0xfe) + (char)(uint)((ulonglong)lVar3 >> 33));
            }
        }
        V[0x7a] = (unsigned char)cVar4;
    }

    FUN_010204d4((int)*(volatile signed char*)(IVAR5+0x59));
    iVar5b = FUN_01016430(1, param_2);
    if (iVar5b == 0) return 0;
    FUN_01016628();

LAB_end:
    if (*(volatile int*)(MMIO+0x550) != 3) {
        return 0;
    }
    FUN_01008d00(0x32, 0xa98);
}
