/* named: FUN_00072674 */
/* Reconstructed FUN_00072674 @ 0x72674  (parity: 300/300 trials, PROVEN) */

static inline int isCurrentModePrivileged(void){unsigned c;__asm__ volatile("mrs %0, control":"=r"(c));return (c&1)==0;}
static inline int getBasePriority(void){unsigned b;__asm__ volatile("mrs %0, basepri":"=r"(b));return (int)b;}
static inline void setBasePriority(int p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__asm__ volatile("isb":::"memory");}

extern int z_spin_lock_valid(unsigned int*);
extern int z_spin_unlock_valid(unsigned int*);
extern int z_spin_lock_set_owner(unsigned int*);
extern int z_ready_thread_locked();
extern int z_reschedule(unsigned int*,int);
extern int z_unpend_first_thread(unsigned int*);
extern unsigned int* k_aligned_alloc(int,int);
extern int assert_post_action(int,int);
extern int printk(int,...);
extern int z_handle_obj_poll_events(unsigned int*,int);

unsigned int FUN_00072674(unsigned int *param_1, unsigned int *param_2, unsigned int *param_3, int param_4, char param_5)
{
  int bVar1;
  int iVar2;
  unsigned int *puVar3;
  unsigned int uVar4;
  unsigned int *puVar5;
  unsigned int uVar6;

  puVar5 = param_1 + 2;
  uVar6 = 0;
  bVar1 = isCurrentModePrivileged();
  if (bVar1) {
    uVar6 = getBasePriority();
  }
  bVar1 = isCurrentModePrivileged();
  if (bVar1 && (uVar4 = getBasePriority(), uVar4 == 0 || 0x20 < uVar4)) {
    setBasePriority(0x20);
  }
  InstructionSynchronizationBarrier(0xf);
  iVar2 = z_spin_lock_valid(puVar5);
  if (iVar2 == 0) {
    printk(0x99cbd, 0xf0920, 0xf08c7, 0x72);
    printk(0xf0935, puVar5);
    uVar6 = 0x72;
LAB_726b6:
    assert_post_action(0xf08c7, uVar6);
  }
  z_spin_lock_set_owner(puVar5);
  if (param_5 != 0) {
    param_2 = (unsigned int*)param_1[1];
  }
  iVar2 = (int)z_unpend_first_thread(param_1 + 3);
  if (iVar2 != 0) {
    *(unsigned int**)(iVar2 + 0x14) = param_3;
    *(unsigned int*)(iVar2 + 0x90) = 0;
    z_ready_thread_locked();
    goto LAB_726e2;
  }
  if (param_4 == 0) {
    *param_3 = 0;
  } else {
    puVar3 = k_aligned_alloc(0, 8);
    if (puVar3 == 0) {
      iVar2 = z_spin_unlock_valid(puVar5);
      if (iVar2 != 0) {
        bVar1 = isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(uVar6);
        }
        InstructionSynchronizationBarrier(0xf);
        return 0xfffffff4;
      }
      printk(0x99cbd, 0xf08f4, 0xf08c7, 0xf0);
      printk(0xf090b, puVar5);
      uVar6 = 0xf0;
      goto LAB_726b6;
    }
    puVar3[1] = (unsigned int)(unsigned long)param_3;
    *puVar3 = 1;
    param_3 = puVar3;
  }
  uVar4 = *param_3 & 3;
  if (param_2 == 0) {
    *param_3 = *param_1 | uVar4;
    *param_1 = (unsigned int)(unsigned long)param_3;
    if (param_1[1] == 0) {
LAB_72748:
      param_1[1] = (unsigned int)(unsigned long)param_3;
    }
  } else if (*param_2 < 4) {
    *param_3 = uVar4;
    puVar3 = (unsigned int*)param_1[1];
    if (puVar3 != 0) {
      *puVar3 = (*puVar3 & 3) | (unsigned int)(unsigned long)param_3;
      goto LAB_72748;
    }
    *param_1 = (unsigned int)(unsigned long)param_3;
    param_1[1] = (unsigned int)(unsigned long)param_3;
  } else {
    *param_3 = (*param_2 & 0xfffffffc) | uVar4;
    *param_2 = (unsigned int)(unsigned long)param_3 | (*param_2 & 3);
  }
  z_handle_obj_poll_events(param_1 + 5, 4);
LAB_726e2:
  z_reschedule(puVar5, uVar6);
  return 0;
}

