/* readable reconstruction; identity: FUN_00071f38 @ 0x00071f38
 * public-name: z_init_static_threads
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   z_setup_new_thread                       <= FUN_00071df8 @ 0x00071df8
 *   z_init_static_threads                    <= FUN_00071f38 @ 0x00071f38
 *   sched_thread_ready                       <= FUN_00073a78 @ 0x00073a78
 *   k_sched_unlock                           <= FUN_00073b1c @ 0x00073b1c
 *   k_sched_lock                             <= FUN_00073bf4 @ 0x00073bf4
 *   z_add_timeout                            <= FUN_00074bf4 @ 0x00074bf4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_86661                             @ 0x00086661
 *   rodata_87fc8                             @ 0x00087fc8
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f0d20                             @ 0x000f0d20
 *   rodata_f7f4b                             @ 0x000f7f4b
 *   rodata_f8056                             @ 0x000f8056
 */
/* Reconstructed FUN_00071f38 @ 0x71f38  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef long long i64; typedef unsigned long long u64;
extern u64 __aeabi_uldivmod(int,int,int,int);
extern void z_setup_new_thread(int,int,int,int,int,int,int,int,int,int);
extern void sched_thread_ready(int);
extern void k_sched_unlock(void);
extern void k_sched_lock(void);
extern void z_add_timeout(int,unsigned,int,int);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,unsigned,unsigned,unsigned);
void z_init_static_threads(void)
{
  i64 lVar1; u64 uVar8;
  int *piVar2, *piVar6;
  unsigned uVar3, uVar5; int iVar4, iVar7;
  piVar2 = (int*)0x00087fc8;
  piVar6 = (int*)0x00087fc8;
  do {
    if (piVar2 < piVar6) {
      printk(0x00099cbd,0x000f8056,0x000f7f4b,0x2f3);
      printk(0x000f0d20,0,0,0);
      uVar3 = 0x2f3;
LAB:
      assert_post_action(0x000f7f4b,uVar3);
    }
    if (piVar2 <= piVar6) {
      k_sched_unlock();
      uVar3 = 0x00086661;
      for (piVar6 = (int*)0x00087fc8; piVar6 <= piVar2; piVar6 = piVar6 + 0xb) {
        if (piVar2 <= piVar6) {
          k_sched_lock();
          return;
        }
        uVar5 = piVar6[9];
        if (uVar5 != 0xffffffff) {
          uVar5 = uVar5 & ~((int)uVar5 >> 0x1f);
          lVar1 = (i64)(int)uVar5 * 0x8000 + 999;
          iVar4 = (int)((u64)lVar1 >> 0x20);
          iVar7 = *piVar6;
          if (iVar4 == 0 && (uVar5 & 0x1ffff) == 0) {
            sched_thread_ready(iVar7);
          } else {
            uVar8 = __aeabi_uldivmod((int)lVar1,iVar4,1000,0);
            z_add_timeout(iVar7 + 0x18,uVar3,(int)uVar8,(int)((u64)uVar8 >> 0x20));
          }
        }
      }
      printk(0x00099cbd,0x000f8056,0x000f7f4b,0x312);
      printk(0x000f0d20,0,0,0);
      uVar3 = 0x312;
      goto LAB;
    }
    z_setup_new_thread(*piVar6,piVar6[1],piVar6[2],piVar6[3],piVar6[4],piVar6[5],piVar6[6],piVar6[7],piVar6[8],piVar6[10]);
    *(int **)(*piVar6 + 0x54) = piVar6;
    piVar6 = piVar6 + 0xb;
  } while(1);
}
