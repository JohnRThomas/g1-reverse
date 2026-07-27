/* Full hard-float reconstruction FUN_00075acc @ 0x75acc, exact extent 334 bytes. */
#include <stdint.h>
extern double FUN_000133f8(void);
extern int FUN_0000de2c(uint32_t,uint32_t,uint32_t,uint32_t);
extern int FUN_0000ddc8(uint32_t,uint32_t,uint32_t,uint32_t);
extern int FUN_0000dddc(uint32_t,uint32_t,uint32_t,uint32_t);
extern uint64_t FUN_0000db4c(uint32_t,uint32_t);
extern unsigned int FUN_000869dc(double);
extern double FUN_000767c8(double);
extern int *thunk_FUN_00071678(void);
typedef union { double d; struct { uint32_t lo,hi; }; uint64_t u; } dbits;
static inline int eq(dbits a,dbits b){return FUN_0000de2c(a.lo,a.hi,b.lo,b.hi);}
static inline int gt(dbits a,dbits b){return FUN_0000ddc8(a.lo,a.hi,b.lo,b.hi);}
static inline int lt(dbits a,dbits b){return FUN_0000dddc(a.lo,a.hi,b.lo,b.hi);}
double FUN_00075acc(double x, double y)
{
    dbits a={.d=x}, b={.d=y}, result={.d=FUN_000133f8()}, zero={.u=0};
    if(*(volatile int8_t*)0x200035afu==-1) return result.d;
    if(eq(b,b)!=0) return result.d;
    if(eq(a,a)!=0) {
        if(gt(b,zero)!=0) return 1.0;
        return result.d;
    }
    if(gt(a,zero)!=0) {
        if(gt(b,zero)!=0) return 1.0;
        if(!FUN_000869dc(b.d)) return result.d;
        if(!lt(b,zero)) return result.d;
        *thunk_FUN_00071678()=0x21;
        return -1.0/0.0;
    }
    int all_finite=0;
    if(FUN_000869dc(result.d)==0) {
        if(FUN_000869dc(a.d)!=0 && FUN_000869dc(b.d)!=0)
            all_finite=1;
    }
    if(!all_finite) {
        if(!gt(result,zero)) return result.d;
        if(!FUN_000869dc(a.d) || !FUN_000869dc(b.d)) return result.d;
        *thunk_FUN_00071678()=0x22;
        return 0.0;
    }
    if(eq(result,result)!=0) {
        *thunk_FUN_00071678()=0x21;
        dbits n={.u=FUN_0000db4c(0,0)};
        return n.d;
    }
    *thunk_FUN_00071678()=0x22;
    if(!lt(a,zero)) return 1.0/0.0;
    dbits magnitude={.d=FUN_000767c8(b.d)};
    return gt(magnitude,b)==0 ? -1.0/0.0 : 1.0/0.0;
}
