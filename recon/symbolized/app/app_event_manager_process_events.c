#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0004f5b0 @ 0x0004f5b0
 * public-name: app_event_manager_process_events
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   app_event_manager_process_events         <= FUN_0004f5b0 @ 0x0004f5b0
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_880f0                             @ 0x000880f0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f1681                             @ 0x000f1681
 *   rodata_f16be                             @ 0x000f16be   [INLINED -- G6 literal batch]
 *   rodata_f1710                             @ 0x000f1710   [INLINED -- G6 literal batch]
 *   rodata_f1722                             @ 0x000f1722   [INLINED -- G6 literal batch]
 *   rodata_f1734                             @ 0x000f1734   [INLINED -- G6 literal batch]
 *   rodata_f5eeb                             @ 0x000f5eeb
 *   rodata_fa9b4                             @ 0x000fa9b4
 *   rodata_faa14                             @ 0x000faa14
 *   g_notify_pending_lock                    @ 0x2000a2c4
 *   g_notify_pending_slist                   @ 0x2000a2c8
 *   g_notify_pending_flags_bitmap            @ 0x2000a2d0
 */
/* Reconstructed FUN_0004f5b0 @ 0x4f5b0  (parity: 300/300 trials, PROVEN) */
extern int  z_spin_lock_valid(int);
extern void z_spin_lock_set_owner(int);
extern int  z_spin_unlock_valid(int);
extern void assert_post_action(int,int) __attribute__((noreturn));
extern void z_log_msg_runtime_create(int,int,void*);
extern void thunk_FUN_000868b4(int);

void app_event_manager_process_events(void){
  volatile int *g2c8=(volatile int*)((unsigned long)&g_notify_pending_slist) /*=0x2000a2c8*/;
  volatile int *g2d0=(volatile int*)((unsigned long)&g_notify_pending_flags_bitmap) /*=0x2000a2d0*/;
  int r4, iVar5, puVar12, iVar6;
  int *piVar13;
  unsigned int uVar8;
  int t;

  if (z_spin_lock_valid(((unsigned long)&g_notify_pending_lock) /*=0x2000a2c4*/) == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72);
    printk(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/,((unsigned long)&g_notify_pending_lock) /*=0x2000a2c4*/,0,0);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72);
  }
L5ea:
  z_spin_lock_set_owner(((unsigned long)&g_notify_pending_lock) /*=0x2000a2c4*/);
  r4 = g2c8[0];
  if (r4 == 0) {
    if (z_spin_unlock_valid(((unsigned long)&g_notify_pending_lock) /*=0x2000a2c4*/) == 0) {
      printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
      printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/,((unsigned long)&g_notify_pending_lock) /*=0x2000a2c4*/,0,0);
      assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
      goto L5ea;
    }
    return;
  }
  /* L624 */
  if (g2c8[1] == 0) r4 = 0;
  g2c8[0] = 0;
  g2c8[1] = 0;
  if (z_spin_unlock_valid(((unsigned long)&g_notify_pending_lock) /*=0x2000a2c4*/) == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
    printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/,((unsigned long)&g_notify_pending_lock) /*=0x2000a2c4*/,0,0);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
    goto L5ea;
  }
  for(;;){
    if (r4 == 0) return;
    iVar5 = *(volatile int*)r4;
    puVar12 = *(volatile int*)(r4+4);
    if (!((unsigned int)puVar12 >= ((unsigned long)&rodata_fa9b4) /*=0xfa9b4*/ && (unsigned int)puVar12 < ((unsigned long)&rodata_faa14) /*=0xfaa14*/)) {
      printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"(aeh->type_id >= _event_type_list_start) && (aeh->type_id < _event_type_list_end)") /*=0xf16be*/,((unsigned long)&rodata_f1681) /*=0xf1681*/,0xa3);
      assert_post_action(((unsigned long)&rodata_f1681) /*=0xf1681*/,0xa3);
      goto L5ea;
    }
    uVar8 = 0xaaaaaaabu * (unsigned int)((puVar12 - ((unsigned long)&rodata_fa9b4) /*=0xfa9b4*/) >> 3);
    t = g2d0[(uVar8 >> 5)];
    if ((int)((unsigned int)((int)t >> (uVar8 & 0x1f)) << 0x1f) < 0) {
      int p3 = *(volatile int*)(puVar12+0xc);
      if (p3 == 0) {
        struct {
          unsigned header;
          unsigned format;
          unsigned value;
          unsigned short flags;
          unsigned short reserved;
        } record;
        record.header = 0x01000003;
        record.format = ((unsigned long)&rodata_f5eeb) /*=0xf5eeb*/;
        record.value = *(volatile unsigned*)puVar12;
        record.flags = 0x200;
        z_log_msg_runtime_create(((unsigned long)&rodata_880f0) /*=0x880f0*/,0x1cc0,&record);
      } else {
        ((void(*)(int))p3)(r4);
      }
    }
    iVar6 = 0;
    piVar13 = (int*)*(volatile int*)(puVar12+4);
    while (*(volatile int*)(puVar12+8) != (int)piVar13 && iVar6 == 0) {
      if (piVar13 == 0) { printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"es != ((void *)0)") /*=0xf1710*/,((unsigned long)&rodata_f1681) /*=0xf1681*/,0xb5); assert_post_action(((unsigned long)&rodata_f1681) /*=0xf1681*/,0xb5); }
      if (*piVar13 == 0) { printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"el != ((void *)0)") /*=0xf1722*/,((unsigned long)&rodata_f1681) /*=0xf1681*/,0xb9); assert_post_action(((unsigned long)&rodata_f1681) /*=0xf1681*/,0xb9); }
      { int pc = *(volatile int*)(*piVar13 + 4);
        if (pc == 0) { printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"el->notification != ((void *)0)") /*=0xf1734*/,((unsigned long)&rodata_f1681) /*=0xf1681*/,0xba); assert_post_action(((unsigned long)&rodata_f1681) /*=0xf1681*/,0xba); }
        iVar6 = ((int(*)(int))pc)(r4);
      }
      piVar13 = piVar13 + 1;
    }
    thunk_FUN_000868b4(r4);
    r4 = iVar5;
  }
}
