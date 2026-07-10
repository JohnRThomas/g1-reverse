#include "g1_app_symbols.h"
/* named: ble_conn_set_state */
/* globals referenced:
//   0x00088108  log_module_bt_conn           
//   0x20002000  g_ble_dev_state              
*/
/* Reconstructed ble_conn_set_state @ 0x56704  (parity: 199/200 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;

static inline int isCurrentModePrivileged(void){unsigned c;__asm__ volatile("mrs %0, control":"=r"(c));return (c&1)==0;}
static inline int getBasePriority(void){unsigned b;__asm__ volatile("mrs %0, basepri":"=r"(b));return (int)b;}
static inline void setBasePriority(int p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__asm__ volatile("isb":::"memory");}

extern void FUN_00055fb4(int);
extern void tx_notify(int);
extern void net_buf_destroy(int,void*,uint32_t,uint32_t);
extern void ble_conn_ref(void);
extern uint32_t ble_conn_unref(int);
extern void FUN_00072880(int);
extern void FUN_00073418(int,uint32_t,uint32_t,uint32_t);
extern uint32_t FUN_00073518(int);
extern void FUN_000757b0(uint32_t,int);
extern void FUN_000813ca(uint32_t,uint32_t,void*);
extern void z_impl_k_queue_init(int);
extern uint32_t thunk_FUN_00072e9c(int);

void ble_conn_set_state(int param_1, uint param_2)
{
  uint uVar7 = *(volatile uint8_t*)(param_1 + 0xd);
  if (uVar7 == param_2) {
    uint32_t local_28 = 0x01000003UL;
    uint32_t local_24 = "no transition %s" /*=0xf3c37*/;
    uint32_t uStack_20 = (uVar7 < 9) ? *(volatile uint32_t*)(((uintptr_t)&rodata_8b220) /*=0x8b220*/ + uVar7*4) : "(unknown)" /*=0xf3c2d*/;
    uint16_t local_1c = 0x200;
    struct { uint32_t a,b,c; uint16_t d; } s = { local_28, local_24, uStack_20, local_1c };
    FUN_000813ca(((uintptr_t)&log_module_bt_conn) /*=0x88108*/, 0x1c80, &s);
    return;
  }
  *(volatile uint8_t*)(param_1 + 0xd) = (uint8_t)param_2;
  if (uVar7 == 0 && *(volatile uint8_t*)(param_1+2) != 8) {
    ble_conn_ref();
  }
  uint8_t newv = *(volatile uint8_t*)(param_1 + 0xd);
  switch (newv) {
    case 0: {
      if (*(volatile uint8_t*)(param_1+2) == 4) {
        ble_conn_unref(param_1);
        break;
      }
      switch (uVar7) {
        case 0: case 7: case 8: {
          struct { uint32_t a,b,c; } s = { 3, "Invalid (%u) old state" /*=0xf3c48*/, param_2 };
          FUN_000813ca(((uintptr_t)&log_module_bt_conn) /*=0x88108*/, 0x1880, &s);
          return;
        }
        case 1: {
          tx_notify(param_1);
          if (*(volatile uint8_t*)(param_1+2) == 1) {
            uint32_t r = thunk_FUN_00072e9c(param_1 + 0x60);
            if ((r & 0xc) != 0) FUN_00073518(param_1 + 0x60);
          }
          volatile uint32_t *p = (volatile uint32_t*)(param_1+4);
          uint32_t v;
          do { v = *p; } while (!__sync_bool_compare_and_swap((uint32_t*)p, v, v | 0x40));
          FUN_000757b0(((uintptr_t)&g_ble_conn_poll_signal) /*=0x20002990*/, 0);
          break;
        }
        case 2: case 5: case 6:
          if (*(volatile uint8_t*)(param_1+0xc) != 0) FUN_00055fb4(param_1);
          /* fallthrough */
        case 3: case 4:
          ble_conn_unref(param_1);
          break;
      }
      break;
    }
    case 1: {
      for (;;) {
        int uVar3 = 0;
        if (isCurrentModePrivileged()) uVar3 = getBasePriority();
        if (isCurrentModePrivileged()) {
          int b = getBasePriority();
          if (b == 0 || b > 0x20) setBasePriority(0x20);
        }
        InstructionSynchronizationBarrier(0xf);
        if (*(volatile int*)(param_1+0x1c) == 0) {
          volatile uint32_t *puVar4 = *(volatile uint32_t* volatile*)(param_1+0x14);
          if (puVar4 == 0) {
            if (isCurrentModePrivileged()) setBasePriority(uVar3);
            InstructionSynchronizationBarrier(0xf);
            return;
          }
          uint32_t uVar5 = *puVar4;
          if (puVar4 == *(volatile uint32_t* volatile*)(param_1+0x18)) {
            *(volatile uint32_t*)(param_1+0x18) = uVar5;
          }
          *(volatile uint32_t*)(param_1+0x14) = uVar5;
          if (isCurrentModePrivileged()) setBasePriority(uVar3);
          InstructionSynchronizationBarrier(0xf);
          uVar3 = 0;
          if (isCurrentModePrivileged()) uVar3 = getBasePriority();
          if (isCurrentModePrivileged()) {
            int b = getBasePriority();
            if (b == 0 || b > 0x20) setBasePriority(0x20);
          }
          InstructionSynchronizationBarrier(0xf);
          uVar5 = puVar4[3];
          *(volatile int*)(param_1+0x1c) = uVar5;
          puVar4[3] = 0;
          if (isCurrentModePrivileged()) setBasePriority(uVar3);
          InstructionSynchronizationBarrier(0xf);
          net_buf_destroy(param_1, (void*)puVar4, uVar5, uVar3);
        } else {
          *(volatile int*)(param_1+0x1c) = *(volatile int*)(param_1+0x1c) - 1;
          if (isCurrentModePrivileged()) setBasePriority(uVar3);
          InstructionSynchronizationBarrier(0xf);
        }
        int iVar2;
        if (*(volatile uint16_t*)(((uintptr_t)&g_ble_dev_state) /*=0x20002000*/ + 0x104) == 0) iVar2 = 0;
        else iVar2 = ((uintptr_t)&g_ble_dev_state) /*=0x20002000*/ + 0x108;
        FUN_00072880(iVar2);
      }
    }
    case 2: case 3: case 4: case 5: case 6: case 8:
      break;
    case 7:
      if (*(volatile uint8_t*)(param_1+2) != 4) {
        z_impl_k_queue_init(param_1+0x38);
        FUN_000757b0(((uintptr_t)&g_ble_conn_poll_signal) /*=0x20002990*/, 0);
        *(volatile uint32_t*)(param_1+0x54) = 0;
        *(volatile uint32_t*)(param_1+0x58) = 0;
        if (*(volatile uint8_t*)(param_1+3) == 1) {
          uint8_t c = *(volatile uint8_t*)(param_1+2);
          int isOne = (c == 1);
          if (isOne) c = 3;
          if (isOne) *(volatile uint8_t*)(param_1+0xb4) = c;
          FUN_00073418(param_1+0x60, 0, ((uintptr_t)&rodata_28000) /*=0x28000*/, 0);
        }
      }
      break;
    default: {
      struct { uint32_t a,b,c; } s = { 3, "no valid (%u) state was set" /*=0xf3c5f*/, param_2 };
      FUN_000813ca(((uintptr_t)&log_module_bt_conn) /*=0x88108*/, 0x1880, &s);
      return;
    }
  }
}

