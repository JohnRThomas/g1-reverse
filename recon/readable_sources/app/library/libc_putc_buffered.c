#include "g1_app_symbols.h"
struct _reent;
#include <stdio.h>
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_3          => struct g1_layout___sFILE__param_0417                    [param_0417; library]
 *   param_1          => struct g1_layout_libc_FILE__param_0418                  [param_0418; library]
 * Raw function identity: 0x00086c88.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00086c88 @ 0x00086c88
 * public-name: libc_putc_buffered
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   libc_putc_buffered                       <= FUN_00086c88 @ 0x00086c88
 */
/* Reconstructed FUN_00086c88 @ 0x86c88  (parity: 300/300 trials, PROVEN) */
extern int __swbuf_r(struct _reent *, int,  FILE *);
unsigned libc_putc_buffered(int param_1, unsigned param_2, int *param_3){
  int iVar4 = param_3[2] - 1;
  *(volatile int*)(param_3 + 2) = iVar4;
  if (iVar4 >= 0 || (param_3[6] <= iVar4 && param_2 != 10)){
    unsigned char *p = *(unsigned char**)param_3;
    *(volatile int*)param_3 = (int)(p + 1);
    *(volatile unsigned char*)p = (unsigned char)param_2;
    return param_2;
  }
  return __swbuf_r(param_1, param_2, param_3);
}
