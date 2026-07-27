struct k_sem;
struct k_work_delayable;
struct k_queue;
/* readable reconstruction; identity: FUN_00056704 @ 0x00056704
 * public-name: ble_conn_set_state
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_notify_connected                 <= FUN_00055fb4 @ 0x00055fb4
 *   tx_notify                                <= FUN_00056020 @ 0x00056020
 *   net_buf_destroy                          <= FUN_00056080 @ 0x00056080
 *   ble_conn_ref                             <= FUN_00056654 @ 0x00056654
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   ble_conn_set_state                       <= FUN_00056704 @ 0x00056704
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   k_work_schedule                          <= FUN_00073418 @ 0x00073418
 *   k_work_cancel_delayable                  <= FUN_00073518 @ 0x00073518
 *   poll_signal_event_locked                 <= FUN_000757b0 @ 0x000757b0
 *   bt_conn_call_4arg_zero                   <= FUN_000813ca @ 0x000813ca
 *   z_impl_k_queue_init                      <= FUN_000864e8 @ 0x000864e8
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   log_module_bt_conn                       @ 0x00088108
 *   rodata_f3c37                             @ 0x000f3c37   [INLINED -- G6 literal batch]
 *   rodata_f3c48                             @ 0x000f3c48   [INLINED -- G6 literal batch]
 *   rodata_f3c5f                             @ 0x000f3c5f   [INLINED -- G6 literal batch]
 *   g_ble_dev_state                          @ 0x20002000
 *   g_ble_conn_poll_signal                   @ 0x20002990
 */
/* Reconstructed FUN_00056704 @ 0x56704  (parity: 199/200 trials, PROVEN) */
/* CFG_VERIFY_PREFIX_FIRST: event-state 1 is an intentional scheduler loop. */
#include <stdint.h>
#include <cmsis_gcc.h>
typedef unsigned int uint;

static inline int getBasePriority(void){ return (int)__get_BASEPRI(); }
static inline void setBasePriority(int p){ __set_BASEPRI((uint32_t)p); }
static inline void raiseBasePriority(int p){ __set_BASEPRI_MAX((uint32_t)p); }
static inline void InstructionSynchronizationBarrier(int x){ (void)x; __ISB(); }

extern void bt_conn_notify_connected(int);
extern void tx_notify(int);
extern void net_buf_destroy(int,void*,uint32_t,uint32_t);
extern void ble_conn_ref(unsigned long);
extern void ble_conn_unref(int);
extern void k_sem_give(struct k_sem *);
extern void k_work_schedule(unsigned int, unsigned int, unsigned int, unsigned int);
extern int k_work_cancel_delayable(struct k_work_delayable *);
extern void poll_signal_event_locked(uint32_t,int);
extern void bt_conn_call_4arg_zero(uint32_t,uint32_t,void*);
#define z_impl_k_queue_init z_impl_k_queue_init
extern void z_impl_k_queue_init(struct k_queue *);
extern int k_work_delayable_busy_get(const struct k_work_delayable *);

void ble_conn_set_state(int param_1, uint param_2)
{
  uint uVar7 = *(volatile uint8_t*)(param_1 + 0xd);
  if (uVar7 == param_2) {
    uint32_t local_28 = 0x01000003UL;
    uint32_t local_24 = 0x000f3c37UL;
    uint32_t uStack_20 = (uVar7 < 9) ? *(volatile uint32_t*)(0x0008b220UL + uVar7*4) : 0x000f3c2dUL;
    uint16_t local_1c = 0x200;
    struct { uint32_t a,b,c; uint16_t d; } s = { local_28, local_24, uStack_20, local_1c };
    bt_conn_call_4arg_zero(0x00088108UL, 0x1c80, &s);
    return;
  }
  *(volatile uint8_t*)(param_1 + 0xd) = (uint8_t)param_2;
  if (uVar7 == 0 && *(volatile uint8_t*)(param_1+2) != 8) {
    ble_conn_ref(param_1);
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
          struct { uint32_t a,b,c; } s = { 3, 0x000f3c48UL, param_2 };
          bt_conn_call_4arg_zero(0x00088108UL, 0x1880, &s);
          return;
        }
        case 1: {
          tx_notify(param_1);
          if (*(volatile uint8_t*)(param_1+2) == 1) {
            uint32_t r = k_work_delayable_busy_get(param_1 + 0x60);
            if ((r & 0xc) != 0) k_work_cancel_delayable(param_1 + 0x60);
          }
          volatile uint32_t *p = (volatile uint32_t*)(param_1+4);
          uint32_t v;
          do { v = *p; } while (!__sync_bool_compare_and_swap((uint32_t*)p, v, v | 0x40));
          poll_signal_event_locked(0x20002990UL, 0);
          break;
        }
        case 2: case 5: case 6:
          if (*(volatile uint8_t*)(param_1+0xc) != 0) bt_conn_notify_connected(param_1);
          /* fallthrough */
        case 3: case 4:
          ble_conn_unref(param_1);
          break;
      }
      break;
    }
    case 1: {
      for (;;) {
        int uVar3 = getBasePriority();
        raiseBasePriority(0x20);
        InstructionSynchronizationBarrier(0xf);
        if (*(volatile int*)(param_1+0x1c) == 0) {
          volatile uint32_t *puVar4 = *(volatile uint32_t* volatile*)(param_1+0x14);
          if (puVar4 == 0) {
            setBasePriority(uVar3);
            InstructionSynchronizationBarrier(0xf);
            return;
          }
          uint32_t uVar5 = *puVar4;
          if (puVar4 == *(volatile uint32_t* volatile*)(param_1+0x18)) {
            *(volatile uint32_t*)(param_1+0x18) = uVar5;
          }
          *(volatile uint32_t*)(param_1+0x14) = uVar5;
          setBasePriority(uVar3);
          InstructionSynchronizationBarrier(0xf);
          uVar3 = getBasePriority();
          raiseBasePriority(0x20);
          InstructionSynchronizationBarrier(0xf);
          uVar5 = puVar4[3];
          *(volatile int*)(param_1+0x1c) = uVar5;
          puVar4[3] = 0;
          setBasePriority(uVar3);
          InstructionSynchronizationBarrier(0xf);
          net_buf_destroy(param_1, (void*)puVar4, uVar5, uVar3);
        } else {
          *(volatile int*)(param_1+0x1c) = *(volatile int*)(param_1+0x1c) - 1;
          setBasePriority(uVar3);
          InstructionSynchronizationBarrier(0xf);
        }
        int iVar2;
        if (*(volatile uint16_t*)(0x20002000UL + 0x104) == 0) iVar2 = 0;
        else iVar2 = 0x20002000 + 0x108;
        k_sem_give(iVar2);
      }
    }
    case 2: case 3: case 4: case 5: case 6: case 8:
      break;
    case 7:
      if (*(volatile uint8_t*)(param_1+2) != 4) {
        z_impl_k_queue_init((void *)(param_1+0x38));
        poll_signal_event_locked(0x20002990UL, 0);
        *(volatile uint32_t*)(param_1+0x54) = 0;
        *(volatile uint32_t*)(param_1+0x58) = 0;
        if (*(volatile uint8_t*)(param_1+3) == 1) {
          uint8_t c = *(volatile uint8_t*)(param_1+2);
          int isOne = (c == 1);
          if (isOne) c = 3;
          if (isOne) *(volatile uint8_t*)(param_1+0xb4) = c;
          k_work_schedule(param_1+0x60, 0, 0x28000, 0);
        }
      }
      break;
    default: {
      struct { uint32_t a,b,c; } s = { 3, 0x000f3c5fUL, param_2 };
      bt_conn_call_4arg_zero(0x00088108UL, 0x1880, &s);
      return;
    }
  }
}
