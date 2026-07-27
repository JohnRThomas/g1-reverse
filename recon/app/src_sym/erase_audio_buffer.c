/* Reconstructed erase_audio_buffer @ 0x2f008  (parity: 300/300 trials, PROVEN) */

typedef int (*fn3)(int,int,int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
int erase_audio_buffer(void){
  int obj = 0x87bf0;               /* ext-flash struct device *dev (rodata) */
  /* Zephyr driver-vtable dispatch: dev->api->erase  (api ptr @dev+8, .erase @api+8) */
  fn3 f = *(volatile fn3*)((*(volatile int*)(obj+8)) + 8);
  /* equivalent: flash_erase(dev, 0x400000, 0x10000) */
  int iVar1 = f(obj, 0x400000, 0x10000);
  if(iVar1==0){
    int iVar2 = *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */;
    *(volatile int*)0x20002404UL = 0x400000;
    if(2 < iVar2){ if(*(volatile int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */==0) DEBUG_PRINT(((unsigned long)"%s(): Flash erase ok \n\n"),((unsigned long)"erase_audio_buffer")); else debug_print(((unsigned long)"%s(): Flash erase ok \n\n"),((unsigned long)"erase_audio_buffer")); }
  } else if(0 < *(volatile int*)0x2000230cUL){
    if(*(volatile int*)0x20007554UL==0) DEBUG_PRINT(((unsigned long)"%s(): Flash erase failed! %d\n\n"),((unsigned long)"erase_audio_buffer"),iVar1); else debug_print(((unsigned long)"%s(): Flash erase failed! %d\n\n"),((unsigned long)"erase_audio_buffer"),iVar1);
  }
  return iVar1;
}
