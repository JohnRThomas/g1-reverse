#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102fc30 @ 0x0102fc30
 * public-name: FUN_0102fc30
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_z_log_msg_static_create           <= FUN_0102e284 @ 0x0102e284
 *   net_buf_simple_reserve                   <= FUN_01030014 @ 0x01030014
 *   net_buf_simple_tailroom                  <= FUN_0103a468 @ 0x0103a468
 *   net_buf_simple_add_mem                   <= FUN_0103a478 @ 0x0103a478
 * address symbols (name @ address):
 *   rodata_103c024                           @ 0x0103c024
 *   rodata_103ddcd                           @ 0x0103ddcd
 */
/* net-core FUN_0102fc30 @ 0x102fc30  (parity 300 trials PROVEN) */
#define C_0102fcbc 0x210009c8
#define C_0102fcc0 0x21000994
#define C_0102fcb4 ((unsigned long)&rodata_103ddcd) /*=0x103ddcd*/
#define C_0102fcb8 ((unsigned long)&rodata_103c024) /*=0x103c024*/

extern int FUN_0103a44c(int);
extern void net_buf_simple_reserve(int, int);
extern unsigned int net_buf_simple_tailroom(int);
extern void net_buf_simple_add_mem(int, int, unsigned int);
extern void FUN_0102ff94(int);
extern void z_impl_z_log_msg_static_create(int, int, void *, int);

int FUN_0102fc30(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4,
                  int param_5, unsigned int param_6)
{
  int iVar1;
  unsigned int uVar3;
  int iVar4;
  struct {
    int kind;
    int descriptor;
    int value;
  } diagnostic;
  unsigned int uStack_20;
  unsigned int uVar2;

  uVar2 = C_0102fcbc;
  uStack_20 = param_4;
  if (param_1 == 0 || (uVar2 = C_0102fcc0, param_1 == 2)) {
    iVar1 = FUN_0103a44c((int)uVar2);
    if (iVar1 != 0) {
      iVar4 = iVar1 + 0xc;
      net_buf_simple_reserve(iVar4, 1);
      *(unsigned char *)(iVar1 + 0x18) = (unsigned char)param_1;
      if (param_5 == 0) {
        return iVar1;
      }
      if (param_6 == 0) {
        return iVar1;
      }
      uVar3 = net_buf_simple_tailroom(iVar4);
      if (param_6 <= uVar3) {
        net_buf_simple_add_mem(iVar4, param_5, param_6);
        return iVar1;
      }
      FUN_0102ff94(iVar1);
    }
  } else {
    diagnostic.kind = 3;
    diagnostic.descriptor = C_0102fcb4;
    diagnostic.value = param_1;
    z_impl_z_log_msg_static_create(C_0102fcb8, 0x1840, &diagnostic, 0);
  }
  return 0;
}
