#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086c88 @ 0x00086c88
 * public-name: libc_putc_buffered
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   libc_putc_buffered                       <= FUN_00086c88 @ 0x00086c88
 */
/* Reconstructed FUN_00086c88 @ 0x86c88  (parity: 300/300 trials, PROVEN) */
extern unsigned ext77c8c(int,unsigned,int*);
unsigned libc_putc_buffered(int param_1, unsigned param_2, int *param_3){
  int iVar4 = param_3[2] - 1;
  *(volatile int*)(param_3 + 2) = iVar4;
  if (iVar4 >= 0 || (param_3[6] <= iVar4 && param_2 != 10)){
    unsigned char *p = *(unsigned char**)param_3;
    *(volatile int*)param_3 = (int)(p + 1);
    *(volatile unsigned char*)p = (unsigned char)param_2;
    return param_2;
  }
  return ext77c8c(param_1, param_2, param_3);
}
