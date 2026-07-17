#include "g1_net_symbols.h"
/* net-core FUN_01031928 @ 0x1031928  (parity 300 trials PROVEN) */
/* Platform boundary: implemented by the Zephyr ARM ARCH_EXCEPT(4) primitive.
 * It clears BASEPRI and raises runtime-exception SVC 2 with reason 4. */
extern __attribute__((noreturn)) void g1_arch_runtime_exception(unsigned int reason);

extern void FUN_01008ddc(unsigned int);
extern int FUN_01008e74(int, int, void*);
extern int FUN_01009078(void);
extern int FUN_0100909c(void);
extern int FUN_010090c0(void);
extern int FUN_010090f4(void);
extern int FUN_01009118(void);
extern int FUN_0100913c(void);
extern int FUN_01009160(void);
extern int FUN_01009184(void);
extern int FUN_010091a8(void);
extern void FUN_0102e284(unsigned int, unsigned int, void*, int);
extern void FUN_0102fbac(unsigned int);

#define DAT_01031a54 ((unsigned long)&rodata_103cad0) /*=0x103cad0*/
#define DAT_01031a58 0x0103aecfu
#define DAT_01031a5c 0x0203fbfbu
#define DAT_01031a60 ((unsigned long)&rodata_103e1f4) /*=0x103e1f4*/
#define DAT_01031a64 ((unsigned long)&rodata_103c044) /*=0x103c044*/

int FUN_01031928(void)
{
  int bVar1;
  int iVar2;
  unsigned int local_28;
  unsigned int local_24;
  unsigned int uStack_20;
  int local_1c;
  unsigned int local_14;

  FUN_0102fbac(DAT_01031a54);
  FUN_01008ddc(DAT_01031a58);
  iVar2 = FUN_01009078();
  if ((((((iVar2 == 0) && (iVar2 = FUN_0100909c(), iVar2 == 0)) &&
         (iVar2 = FUN_010090c0(), iVar2 == 0)) &&
        ((iVar2 = FUN_01009118(), iVar2 == 0 && (iVar2 = FUN_010090f4(), iVar2 == 0)))) &&
       ((iVar2 = FUN_0100913c(), iVar2 == 0 &&
         ((iVar2 = FUN_01009184(), iVar2 == 0 && (iVar2 = FUN_010091a8(), iVar2 == 0)))))) &&
      ((iVar2 = FUN_01009160(), iVar2 == 0 &&
        ((iVar2 = FUN_01009184(), iVar2 == 0 && (iVar2 = FUN_010091a8(), iVar2 == 0)))))) {
    local_14 = 1;
    local_1c = FUN_01008e74(0, 1, &local_14);
    if (-1 < local_1c) {
      local_14 = 1;
      local_1c = FUN_01008e74(0, 2, &local_14);
      if (-1 < local_1c) {
        local_14 = 8;
        local_1c = FUN_01008e74(0, 7, &local_14);
        if (-1 < local_1c) {
          local_14 = DAT_01031a5c;
          local_1c = FUN_01008e74(0, 3, &local_14);
          if (-1 < local_1c) {
            local_14 = 1;
            local_1c = FUN_01008e74(0, 4, &local_14);
            if (-1 < local_1c) {
              local_14 = 0x1f;
              local_1c = FUN_01008e74(0, 6, &local_14);
              if (-1 < local_1c) {
                local_14 = 3;
                local_1c = FUN_01008e74(0, 5, &local_14);
                if (-1 < local_1c) {
                  if (local_1c < 0x16c4) {
                    local_1c = 0;
                  } else {
                    local_24 = DAT_01031a60;
                    uStack_20 = 0x16c3;
                    local_28 = 4;
                    FUN_0102e284(DAT_01031a64, 0x2040, &local_28, 0);
                    g1_arch_runtime_exception(4);
                  }
                }
              }
            }
          }
        }
      }
    }
  } else {
    local_1c = -0x86;
  }
  return local_1c;
}
