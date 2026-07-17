#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01030bac @ 0x01030bac
 * public-name: FUN_01030bac
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_z_log_msg_static_create           <= FUN_0102e284 @ 0x0102e284
 * address symbols (name @ address):
 *   rodata_1031555                           @ 0x01031555
 *   rodata_103c094                           @ 0x0103c094
 *   rodata_103e004                           @ 0x0103e004
 *   rodata_103e030                           @ 0x0103e030
 */
/* net-core FUN_01030bac @ 0x1030bac  (parity 300 trials PROVEN) */

extern void FUN_01034d8c(unsigned int, unsigned int);
extern void FUN_0102eb8c(unsigned int, unsigned int, unsigned int);
extern void FUN_0103b62e(void *, unsigned int, unsigned int);
extern void z_impl_z_log_msg_static_create(unsigned int, unsigned int, void *, unsigned int);
extern void FUN_01034dd8(void *);

unsigned int FUN_01030bac(int param_1)
{
  volatile int *outer = (volatile int *)(*(volatile int *)(param_1 + 0x10) + 0x80);
  *outer = param_1;

  FUN_01034d8c(0, ((unsigned long)&rodata_1031555) /*=0x1031555*/);
  FUN_0102eb8c(0x12, 1, 0);

  volatile unsigned int *puVar4 = *(volatile unsigned int **)(param_1 + 4);

  struct {
    unsigned int radio_bits[16];
    unsigned int controller_bits[16];
    unsigned int reserved;
  } local_buf;
  FUN_0103b62e(&local_buf, 0, sizeof(local_buf));

  if (puVar4[1] > 0xffff) {
    unsigned int tmp[2]; tmp[0] = 2; tmp[1] = ((unsigned long)&rodata_103e004) /*=0x103e004*/;
    z_impl_z_log_msg_static_create(((unsigned long)&rodata_103c094) /*=0x103c094*/, 0x1080, tmp, 0);
  }
  if (puVar4[0] > 0xffff) {
    unsigned int tmp[2]; tmp[0] = 2; tmp[1] = ((unsigned long)&rodata_103e030) /*=0x103e030*/;
    z_impl_z_log_msg_static_create(((unsigned long)&rodata_103c094) /*=0x103c094*/, 0x1080, tmp, 0);
  }

  local_buf.reserved = 0;
  for (unsigned int bit = 0; bit != 16; ++bit) {
    unsigned int mask = 1u << bit;
    if ((puVar4[1] & mask) != 0)
      local_buf.radio_bits[bit] = mask;
    if ((puVar4[0] & mask) != 0)
      local_buf.controller_bits[bit] = mask;
  }

  FUN_01034dd8(&local_buf);
  return 0;
}
