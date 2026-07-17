/* readable reconstruction; identity: FUN_0002f008 @ 0x0002f008
 * public-name: erase_audio_buffer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_87bf0                             @ 0x00087bf0
 *   g_log_level                              @ 0x2000230c
 *   g_audio_flash_write_offset               @ 0x20002404
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed erase_audio_buffer @ 0x2f008  (parity: 300/300 trials, PROVEN) */

typedef int (*fn3)(int,int,int);
extern int DEBUG_PRINT();
extern void debug_print(void);
int erase_audio_buffer(void){
  int obj = 0x87bf0;
  fn3 f = *(volatile fn3*)((*(volatile int*)(obj+8)) + 8);
  int iVar1 = f(obj, 0x400000, 0x10000);
  if(iVar1==0){
    int iVar2 = *(volatile int*)0x2000230cUL;
    *(volatile int*)0x20002404UL = 0x400000;
    if(2 < iVar2){ if(*(volatile int*)0x20007554UL==0) DEBUG_PRINT(); else debug_print(); }
  } else if(0 < *(volatile int*)0x2000230cUL){
    if(*(volatile int*)0x20007554UL==0) DEBUG_PRINT(); else debug_print();
  }
  return iVar1;
}
