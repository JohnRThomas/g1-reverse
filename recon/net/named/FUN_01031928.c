/* readable reconstruction; identity: FUN_01031928 @ 0x01031928
 * public-name: FUN_01031928
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_z_log_msg_static_create           <= FUN_0102e284 @ 0x0102e284
 * address symbols (name @ address):
 *   rodata_103c044                           @ 0x0103c044
 *   rodata_103cad0                           @ 0x0103cad0
 *   rodata_103e1f4                           @ 0x0103e1f4
 */
/* net-core FUN_01031928 @ 0x1031928  (parity 300 trials PROVEN) */
#define G1_ARCH_RUNTIME_EXCEPTION(reason) do { \
    __asm__ volatile("eors.n r0, r0\n\t" \
                     "msr basepri, r0\n\t" \
                     "mov r0, %0\n\t" \
                     "svc 2" \
                     : : "I"(reason) : "r0", "memory"); \
} while (0)

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
extern void z_impl_z_log_msg_static_create(unsigned int, unsigned int, void*, int);
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
                    z_impl_z_log_msg_static_create(DAT_01031a64, 0x2040, &local_28, 0);
                    G1_ARCH_RUNTIME_EXCEPTION(4);
                    local_1c = -12;
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
