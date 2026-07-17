/* readable reconstruction; identity: FUN_000755f8 @ 0x000755f8
 * public-name: FUN_000755f8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f53ff                             @ 0x000f53ff
 *   rodata_f801f                             @ 0x000f801f
 *   rodata_f871d                             @ 0x000f871d
 *   rodata_f88dc                             @ 0x000f88dc
 *   rodata_f88f2                             @ 0x000f88f2
 *   rodata_f8901                             @ 0x000f8901
 *   rodata_f8911                             @ 0x000f8911
 *   g_audio_755f8_wait_obj                   @ 0x20002d04
 *   g_current_thread_ptr                     @ 0x2000b450
 *   poll_spinlock                            @ 0x2000b4a0
 */
/* Reconstructed FUN_000755f8 @ 0x755f8  (parity: 300/300 trials, PROVEN) */
extern void assert_post_action(int,int);
extern void printk(int,int,int,int);
extern int  FUN_000751d0(int,int,int,int,int,int,int);
extern void FUN_000753ec(int,int,int);
extern int  z_spin_lock_valid(int);
extern void z_spin_lock_set_owner(int);
extern int  z_spin_unlock_valid(int);
extern int  FUN_00073f6c(int,int,int,int,int,int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))
#define VSC(a) (*(volatile signed char*)(a))

int FUN_000755f8(int param_1,int param_2,unsigned int param_3,unsigned int param_4){
  int iVar5, iVar2, uVar3, uVar6=0, uVar4=0x20;
  iVar5 = VI(0x2000b450);
  VB(iVar5+0x60) = 1;
  VB(iVar5+0x61) = 1;
  unsigned int exception_number;
  __asm__ volatile ("mrs %0, ipsr" : "=r" (exception_number));
  if (exception_number != 0) {
    printk(0x99cbd,0xf801f,0x99cbd,0x12d);
    printk(0xf53ff,0xf801f,0x99cbd,0x12d);
    assert_post_action(0xf871d,0x12d);
    return 0;
  }
  if (param_1 == 0) {
    printk(0x99cbd,0xf88dc,0xf871d,0x12e);
    printk(0xf88f2,0xf88dc,0xf871d,0x12e);
    assert_post_action(0xf871d,0x12e);
    return 0;
  }
  if (param_2 < 0) {
    printk(0x99cbd,0xf8901,0xf871d,0x12f);
    printk(0xf8911,0xf8901,0xf871d,0x12f);
    assert_post_action(0xf871d,0x12f);
    return 0;
  }
  uVar3 = FUN_000751d0(param_1,param_2,iVar5+0x60,(param_3==0&&param_4==0),param_1,param_2,(int)param_3);
  iVar2 = z_spin_lock_valid(0x2000b4a0);
  if (iVar2 == 0) { printk(0x99cbd,0xf0920,0xf08c7,0x72);printk(0xf0935,0x2000b4a0,0xf08c7,0x72); assert_post_action(0xf08c7,0x72); return 0; }
  z_spin_lock_set_owner(0x2000b4a0);
  if (VSC(iVar5+0x60) == 0) {
    FUN_000753ec(param_1,uVar3,uVar6);
    if (z_spin_unlock_valid(0x2000b4a0) != 0) return 0;
  } else {
    VB(iVar5+0x60) = 0;
    if ((param_3|param_4) == 0) {
      if (z_spin_unlock_valid(0x2000b4a0) != 0) return 0xfffffff5;
    } else {
      uVar6 = FUN_00073f6c(0x2000b4a0,uVar6,0x20002d04,(int)(param_3|param_4),(int)param_3,(int)param_4);
      iVar5 = z_spin_lock_valid(0x2000b4a0);
      if (iVar5 == 0) { printk(0x99cbd,0xf0920,0xf08c7,0x72);printk(0xf0935,0x2000b4a0,0xf08c7,0x72); assert_post_action(0xf08c7,0x72); return 0; }
      z_spin_lock_set_owner(0x2000b4a0);
      FUN_000753ec(param_1,uVar3,uVar4);
      if (z_spin_unlock_valid(0x2000b4a0) != 0) return uVar6;
    }
  }
  printk(0x99cbd,0xf08f4,0xf08c7,0xf0);printk(0xf090b,0x2000b4a0,0xf08c7,0xf0); assert_post_action(0xf08c7,0xf0);
  return 0;
}
