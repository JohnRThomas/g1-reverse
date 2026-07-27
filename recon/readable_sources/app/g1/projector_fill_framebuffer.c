#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d6ae @ 0x0007d6ae
 * public-name: projector_fill_framebuffer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_transfer_pixel_chunk           <= FUN_000476b4 @ 0x000476b4
 *   get_projector_controller                 <= FUN_0007d4ec @ 0x0007d4ec
 *   projector_fill_framebuffer               <= FUN_0007d6ae @ 0x0007d6ae
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_f000                              @ 0x0000f000
 */
/* Reconstructed FUN_0007d6ae @ 0x7d6ae  (parity: 300/300 trials, PROVEN) */

extern int get_projector_controller(void);
extern void memset_bytes(void*, int, int);
extern void projector_transfer_pixel_chunk(unsigned short, unsigned short, unsigned long, long);

void projector_fill_framebuffer(unsigned int param_1)
{
  int iVar1;
  unsigned int uVar2;

  iVar1 = get_projector_controller();
  uVar2 = *(unsigned int*)(iVar1+0x24);
  memset_bytes(uVar2, param_1, 64000);
  projector_transfer_pixel_chunk(0,0,uVar2,((unsigned long)&rodata_f000) /*=0xf000*/);
  projector_transfer_pixel_chunk(0,0xc0,uVar2,((unsigned long)&rodata_f000) /*=0xf000*/);
  projector_transfer_pixel_chunk(0,0x180,uVar2,0x7800);
  return;
}
