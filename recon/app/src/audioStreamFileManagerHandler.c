/* Reconstructed audioStreamFileManagerHandler @ 0x2f94c  (parity: 20/20 trials, PROVEN) */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t a, uint32_t b, ...);
extern uintptr_t FUN_000167a8(void);
extern void FUN_00019c70(uint32_t a, uint32_t b, uint32_t c, ...);
extern void FUN_0002360c(void);
extern int32_t FUN_0002f460(void *a);
extern void FUN_0002f4a8(uint8_t a);
extern void FUN_0002f688(void);
extern int32_t FUN_0002f940(void);
extern void FUN_00048840(void);
extern void FUN_000498c0(void);
extern void FUN_0007d224(void);
extern int32_t FUN_0008638c(void *a);
extern void FUN_00086c04(void *a, void *b, int32_t c);
extern void FUN_00086c78(void *a, int32_t b, int32_t c);
extern int32_t sync_to_slave(void *a, uint32_t b, uint32_t c);

uint32_t audioStreamFileManagerHandler(void)
{
  volatile uint8_t *pcVar2;
  char local_f4[2];
  uint8_t local_f0[204];

  pcVar2 = (volatile uint8_t *)0x20019dabUL;
  if (*pcVar2 == 0) {
    if (*(volatile int32_t *)(0x20003890UL + 0x24) == 0) {
      return 0;
    }
    int32_t iVar8 = FUN_0002f460(local_f4);
    if (iVar8 != 0) {
      return 0;
    }
    if (local_f4[0] != '\x01') {
      if (local_f4[0] != '\x03') {
        if (local_f4[0] == '\x04') {
          FUN_0002f4a8(local_f0[0]);
          return 0;
        }
        if (local_f4[0] != '\x02') {
          return 0;
        }
      }
      FUN_0002f688();
      return 0;
    }
    if (2 < *(volatile int32_t *)0x2000230cUL) {
      if (*(volatile int32_t *)0x20007554UL == 0) {
        DEBUG_PRINT(0, 0);
      }
      else {
        FUN_00019c70(0, 0, 0);
      }
    }
    return 0;
  }
  return 0;
}

