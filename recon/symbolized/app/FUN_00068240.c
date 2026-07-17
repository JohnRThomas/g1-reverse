#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00068240 @ 0x00068240
 * public-name: FUN_00068240
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_metal_generic_bus                      @ 0x2000b424
 */
/* Reconstructed FUN_00068240 @ 0x68240  (parity: 300/300 trials, PROVEN) */

extern void *memset_bytes(void*, int, int);
extern unsigned int FUN_00068298(unsigned int*);

unsigned int FUN_00068240(unsigned int *param_1)
{
  unsigned char *state;

  state = (unsigned char*)memset_bytes((void*)((unsigned long)&g_metal_generic_bus) /*=0x2000b424*/, 0, 0x20);
  *(volatile unsigned int*)(state + 4) = param_1[0];
  state[0] = *((unsigned char*)param_1 + 4);
  *(unsigned char**)(state + 8) = state + 8;
  *(unsigned char**)(state + 12) = state + 8;
  *(unsigned char**)(state + 16) = state + 16;
  *(unsigned char**)(state + 20) = state + 16;
  *(unsigned char**)(state + 24) = state + 24;
  *(unsigned char**)(state + 28) = state + 24;

  return FUN_00068298(param_1);
}
