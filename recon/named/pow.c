/* readable reconstruction; identity: FUN_00075acc @ 0x00075acc
 * public-name: pow
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __divdf3                                 <= FUN_0000db4c @ 0x0000db4c
 *   __aeabi_dcmpeq                           <= FUN_0000ddc8 @ 0x0000ddc8
 *   __aeabi_dcmplt                           <= FUN_0000dddc @ 0x0000dddc
 *   double_is_unordered                      <= FUN_0000de2c @ 0x0000de2c
 *   __ieee754_pow                            <= FUN_000133f8 @ 0x000133f8
 *   pow                                      <= FUN_00075acc @ 0x00075acc
 *   rint                                     <= FUN_000767c8 @ 0x000767c8
 *   finite                                   <= FUN_000869dc @ 0x000869dc
 * address symbols (name @ address):
 *   g_libm_ieee_mode_flag                    @ 0x200035af
 */
/* Full hard-float reconstruction FUN_00075acc @ 0x75acc, exact extent 334 bytes. */
#include <stdint.h>
extern double __ieee754_pow(void);
extern int double_is_unordered(uint32_t,uint32_t,uint32_t,uint32_t);
extern int __aeabi_dcmpeq(uint32_t,uint32_t,uint32_t,uint32_t);
extern int __aeabi_dcmplt(uint32_t,uint32_t,uint32_t,uint32_t);
extern uint64_t __divdf3(uint32_t,uint32_t);
extern int finite(double);
extern double rint(double);
extern uint32_t *thunk_FUN_00071678(void);
typedef union { double d; struct { uint32_t lo,hi; }; uint64_t u; } dbits;
static inline int eq(dbits a,dbits b){return double_is_unordered(a.lo,a.hi,b.lo,b.hi);}
static inline int gt(dbits a,dbits b){return __aeabi_dcmpeq(a.lo,a.hi,b.lo,b.hi);}
static inline int lt(dbits a,dbits b){return __aeabi_dcmplt(a.lo,a.hi,b.lo,b.hi);}
double pow(double x, double y)
{
    dbits a={.d=x}, b={.d=y}, result={.d=__ieee754_pow()}, zero={.u=0};
    if(*(volatile int8_t*)0x200035afu==-1) return result.d;
    if(eq(b,b)!=0) return result.d;
    if(eq(a,a)!=0) {
        if(gt(b,zero)!=0) return 1.0;
        return result.d;
    }
    if(gt(a,zero)!=0) {
        if(gt(b,zero)!=0) return 1.0;
        if(!finite(b.d)) return result.d;
        if(!lt(b,zero)) return result.d;
        *thunk_FUN_00071678()=0x21;
        return -1.0/0.0;
    }
    int all_finite=0;
    if(finite(result.d)==0) {
        if(finite(a.d)!=0 && finite(b.d)!=0)
            all_finite=1;
    }
    if(!all_finite) {
        if(!gt(result,zero)) return result.d;
        if(!finite(a.d) || !finite(b.d)) return result.d;
        *thunk_FUN_00071678()=0x22;
        return 0.0;
    }
    if(eq(result,result)!=0) {
        *thunk_FUN_00071678()=0x21;
        dbits n={.u=__divdf3(0,0)};
        return n.d;
    }
    *thunk_FUN_00071678()=0x22;
    if(!lt(a,zero)) return 1.0/0.0;
    dbits magnitude={.d=rint(b.d)};
    return gt(magnitude,b)==0 ? -1.0/0.0 : 1.0/0.0;
}
