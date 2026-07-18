/* net-core FUN_0102afbc @ 0x102afbc  (parity 300 trials PROVEN) */
#include <stdint.h>
extern void FUN_0102fcec(int);
extern void FUN_01035fa0(int, int, int, int, int, int, int, int, int);
extern void FUN_0103b156(int, int);
extern int FUN_0102d558(int);
#ifdef G1_COHESIVE_BUILD
#include <zephyr/device.h>
#include <zephyr/ipc/ipc_service.h>
#define FUN_0102d5b4(instance, endpoint, config) \
  ipc_service_register_endpoint((const struct device *)(uintptr_t)(instance), \
                                (struct ipc_ept *)(uintptr_t)(endpoint), \
                                (const struct ipc_ept_cfg *)(uintptr_t)(config))
#else
extern int FUN_0102d5b4(int, int, int);
#endif
extern void FUN_01039722(int, ...);

#define C_0102b058 0x2100095c
#ifdef G1_COHESIVE_BUILD
extern void FUN_0102adac(void);
extern void FUN_0102acf4(void);
extern unsigned char g1_hci_endpoint_config;
#define C_0102b05c ((int)(uintptr_t)&FUN_0102adac) /*=0x0102b5ad*/
#define C_0102b06c ((int)(uintptr_t)&FUN_0102acf4) /*=0x0102b4f5*/
#define C_0102b08c ((int)(uintptr_t)&g1_hci_endpoint_config) /*=0x2100059c*/
#else
#define C_0102b05c 0x0102b5ad
#define C_0102b06c 0x0102b4f5
#define C_0102b08c 0x2100059c
#endif
#define C_0102b060 0x21006cc0
#define C_0102b064 0x21001da0
#define C_0102b068 0x0103d088
#define C_0102b070 0x21006480
#define C_0102b074 0x21001d08
#define C_0102b078 0x0103d095
#define C_0102b07c 0x0103bfac
#define P_0102b080 0x21000580
#define C_0102b084 0x0103d0a2
#define C_0102b088 0x21004608
#define C_0102b090 0x0103d0bf

int FUN_0102afbc(void)
{
  int iVar1;

  FUN_0102fcec(C_0102b058);
  FUN_01035fa0(C_0102b064, C_0102b060, 0x600, C_0102b05c, 0, 0, 0, 0xfffffff7, 0);
  FUN_0103b156(C_0102b064, C_0102b068);
  FUN_01035fa0(C_0102b074, C_0102b070, 0x800, C_0102b06c, 0, 0, 0, 0xfffffff7, 0);
  FUN_0103b156(C_0102b074, C_0102b078);
  iVar1 = FUN_0102d558(C_0102b07c);
  if (iVar1 < 0 && iVar1 != -0x78 && 0 < *(volatile int *)P_0102b080) {
    FUN_01039722(C_0102b084, 0);
  }
  iVar1 = FUN_0102d5b4(C_0102b07c, C_0102b088, C_0102b08c);
  if (iVar1 != 0 && 0 < *(volatile int *)P_0102b080) {
    FUN_01039722(C_0102b090, iVar1);
  }
  return 0;
}
