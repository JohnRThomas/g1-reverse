/* named: FUN_00075acc */
/* globals referenced:
//   0x200035af  g_libm_ieee_mode_flag        
*/
/* Reconstructed FUN_00075acc @ 0x75acc  (parity: 200/200 trials, PROVEN) */

#include <stdint.h>
extern long long __divdf3(int,int);
extern int __aeabi_dcmpeq();
extern int __aeabi_dcmplt();
extern int double_is_unordered();
extern long long FUN_000133f8(void);
extern long long FUN_000767c8();
extern int FUN_000869dc();
extern void* thunk_FUN_00071678(void);
long long FUN_00075acc(unsigned p1,unsigned p2,unsigned p3,unsigned p4){
  long long lv = FUN_000133f8();
  if (*(volatile int8_t*)0x200035afUL == -1) return lv;
  if (double_is_unordered()!=0) return lv;
  if (double_is_unordered()==0){
    if (__aeabi_dcmpeq()==0){
      if (FUN_000869dc()!=0 || FUN_000869dc()==0 || FUN_000869dc()==0){
        if (__aeabi_dcmpeq()==0) return lv;
        if (FUN_000869dc()==0) return lv;
        if (FUN_000869dc()==0) return lv;
        *(unsigned*)thunk_FUN_00071678()=0x22; return 0;
      }
      if (double_is_unordered()!=0){ *(unsigned*)thunk_FUN_00071678()=0x21; return __divdf3(0,0);}
      *(unsigned*)thunk_FUN_00071678()=0x22;
      if (__aeabi_dcmplt()!=0){ FUN_000767c8(); if (__aeabi_dcmpeq()==0) return (long long)((unsigned long long)*(volatile unsigned*)0x75c20UL<<32);}
      return (long long)((unsigned long long)*(volatile unsigned*)0x75c24UL<<32);
    }
    if (__aeabi_dcmpeq()==0){
      if (FUN_000869dc()==0) return lv;
      if (__aeabi_dcmplt()==0) return lv;
      *(unsigned*)thunk_FUN_00071678()=0x21;
      return (long long)((unsigned long long)*(volatile unsigned*)0x75c20UL<<32);
    }
  } else {
    if (__aeabi_dcmpeq()==0) return lv;
  }
  return (long long)((unsigned long long)*(volatile unsigned*)0x75c28UL<<32);
}

