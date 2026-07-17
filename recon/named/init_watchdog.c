/* readable reconstruction; identity: FUN_0002ace0 @ 0x0002ace0
 * public-name: init_watchdog
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   init_watchdog                            <= FUN_0002ace0 @ 0x0002ace0
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_watchdog_device                        @ 0x00087cc8
 *   rodata_a1b10                             @ 0x000a1b10
 *   rodata_a1b33                             @ 0x000a1b33
 *   rodata_a1b50                             @ 0x000a1b50
 *   rodata_a1b88                             @ 0x000a1b88
 *   rodata_a1bbc                             @ 0x000a1bbc
 *   rodata_a1bf6                             @ 0x000a1bf6
 *   rodata_a1c17                             @ 0x000a1c17
 *   rodata_a1c96                             @ 0x000a1c96
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_wdt_channel_id                         @ 0x20007b50
 */
/* Reconstructed FUN_0002ace0 @ 0x2ace0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(int,...);
extern void debug_print(void);
extern int  FUN_00074844(int,int);
extern int  z_device_is_ready(int);
extern void memset_bytes(void*,int,int);
struct watchdog_window {
  uint32_t min;
  uint32_t max;
};

struct watchdog_timeout_cfg {
  struct watchdog_window window;
  void *callback;
  uint8_t flags;
  uint8_t reserved[3];
};

typedef int (*install_timeout_fn)(void *device,
                                  const struct watchdog_timeout_cfg *config);
typedef int (*setup_watchdog_fn)(void *device, uint8_t options);
typedef int (*feed_watchdog_fn)(void *device, int channel_id);

int init_watchdog(int param_1,int param_2,int param_3,int param_4){
  volatile int *piVar1 = (volatile int*)0x2000230cUL;
  volatile int *g50   = (volatile int*)0x20007554UL;
  volatile int *puVar3= (volatile int*)0x00087cc8UL;
  volatile int *piVar4= (volatile int*)0x20007b50UL;
  int iVar5, uVar6, fmt, iVar7;
  struct watchdog_timeout_cfg timeout;
  (void)param_1;(void)param_2;(void)param_3;(void)param_4;

  if (3 < *piVar1) { if (*g50==0) log_message(0x000a1b10,0x000a1c96); else debug_print(); }
  iVar5 = z_device_is_ready(0x00087cc8);
  if (iVar5 == 0) {
    if (0 < *piVar1) { if (*g50==0) log_message(0x000a1b33,0x000a1c96,*puVar3); else debug_print(); }
    return 0;
  }
  memset_bytes(&timeout,0,sizeof(timeout));
  timeout.window.max = 30000;
  timeout.flags = 2;
  if (3 < *piVar1) { if (*g50==0) log_message(0x000a1b50,0x000a1c96); else debug_print(); }
  iVar7 = puVar3[2];
  iVar5 = ((install_timeout_fn)(*(volatile int*)(iVar7+8)))(
      (void *)0x00087cc8, &timeout);
  *piVar4 = iVar5;
  if (iVar5 == -0x86) {
    if (0 < *piVar1) { if (*g50==0) log_message(0x000a1b88,0x000a1c96); else debug_print(); }
    timeout.callback = 0;
    iVar7 = puVar3[2];
    iVar5 = ((install_timeout_fn)(*(volatile int*)(iVar7+8)))(
        (void *)0x00087cc8, &timeout);
    *piVar4 = iVar5;
  }
  if (*piVar4 < 0) {
    if (*piVar1 < 1) return 0;
    iVar5 = *g50; uVar6 = 0x000a1bbc;
  } else {
    iVar7 = puVar3[2];
    iVar5 = ((setup_watchdog_fn)(*(volatile int*)iVar7))(
        (void *)0x00087cc8, 2);
    if (iVar5 < 0) {
      if (*piVar1 < 1) return 0;
      iVar5 = *g50; uVar6 = 0x000a1bda;
    } else {
      if (3 < *piVar1) { if (*g50==0) log_message(0x000a1bf6,0x000a1c96,5); else debug_print(); }
      fmt = 0x000a1c17;
      iVar5 = 5;
      do {
        if (3 < *piVar1) { if (*g50==0) log_message(fmt,0x000a1c96); else debug_print(); }
        iVar7 = puVar3[2];
        if (((feed_watchdog_fn)(*(volatile int*)(iVar7+0xc)))(
                (void *)0x00087cc8, *piVar4) == 0) break;
        FUN_00074844(0x667,0);
        iVar5 = iVar5 - 1;
      } while (iVar5 != 0);
      if (*piVar1 < 4) return 0;
      iVar5 = *g50; uVar6 = 0x000a1c32;
    }
  }
  if (iVar5 == 0) log_message(uVar6,0x000a1c96); else debug_print();
  return 0;
}
