#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_net_buf__param_0276                    [param_0276; library]
 * Raw function identity: 0x00080830.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00080830 @ 0x00080830
 * public-name: cbor_nb_writer_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_reset                            <= FUN_0005ee6c @ 0x0005ee6c
 *   cbor_nb_writer_init                      <= FUN_00080830 @ 0x00080830
 *   net_buf_simple_tailroom                  <= FUN_00083730 @ 0x00083730
 */
/* Reconstructed FUN_00080830 @ 0x80830  (parity: 300/300 trials, PROVEN) */

extern void net_buf_reset(unsigned int);
extern int net_buf_simple_tailroom(int *);
extern void thunk_FUN_00085cf2(int *, int, int, int, int, int, unsigned int);

void cbor_nb_writer_init(int *param_1, unsigned int param_2, unsigned int param_3)
{
  int uVar1;
  int iVar2;
  unsigned int iVar3;
  iVar3 = param_2;
  net_buf_reset(param_2);
  *param_1 = param_2;
  *(unsigned short *)(param_2 + 0x10) = 8;
  iVar2 = *(int *)(param_2 + 0xc);
  uVar1 = net_buf_simple_tailroom((int *)(param_2 + 0xc));
  thunk_FUN_00085cf2(param_1 + 1, 2, iVar2 + 8, uVar1, 0, iVar3, param_3);
}
