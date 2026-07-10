/* named: vdprintf_to_fd */
/* Reconstructed vdprintf_to_fd @ 0x86f00  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern long long FUN_00051164(void);
extern int vsnprintf_impl(int,int,int,int);
extern int vsprintf_impl(int,int,int);
extern int write_r_capture_errno(int,int);
void vdprintf_to_fd(int param_1, int param_2, int param_3, int param_4){
  if(param_3 < 0){
    vsprintf_impl(param_1, param_4, 0);
    return;
  }
  int uVar1 = vsnprintf_impl(param_1, param_3, param_4, 0);
  if(uVar1 < 0) return;
  if((uint32_t)uVar1 < (uint32_t)param_3) return;
  long long v = FUN_00051164();
  int high = (int)(uint32_t)((unsigned long long)v >> 32);
  int lo = (int)(uint32_t)v;
  int iVar2 = write_r_capture_errno(lo, *(volatile int16_t*)(high+0xe));
  if(iVar2 >= 0){
    *(volatile uint32_t*)(high+0x54) = *(volatile uint32_t*)(high+0x54) + iVar2;
  } else {
    *(volatile uint16_t*)(high+0xc) = *(volatile uint16_t*)(high+0xc) & ~0x1000;
  }
}

