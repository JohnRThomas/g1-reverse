/* net-core FUN_01031928 @ 0x1031928  (parity 300 trials PROVEN) */
static inline int isCurrentModePrivileged(void){unsigned c;__asm__ volatile("mrs %0, control":"=r"(c));return (c&1)==0;}
static inline void setBasePriority(int p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void software_interrupt(int n){(void)n;__asm__ volatile("movs r0,#4\nsvc #2\n":::"r0","memory");}

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

#define DAT_01031a54 0x0103cad0u
#define DAT_01031a58 0x0103aecfu
#define DAT_01031a5c 0x0203fbfbu
#define DAT_01031a60 0x0103e1f4u
#define DAT_01031a64 0x0103c044u

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
                    bVar1 = isCurrentModePrivileged();
                    if (bVar1) {
                      setBasePriority(0);
                    }
                    software_interrupt(2);
                    local_1c = -0xc;
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

