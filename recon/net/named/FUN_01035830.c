/* readable reconstruction; identity: FUN_01035830 @ 0x01035830
 * public-name: FUN_01035830
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   rpmsg_register_endpoint                  <= FUN_0103547c @ 0x0103547c
 *   z_impl_k_sem_init                        <= FUN_0103b224 @ 0x0103b224
 * address symbols (name @ address):
 *   rodata_1035f6d                           @ 0x01035f6d
 *   rodata_103b6b3                           @ 0x0103b6b3
 *   rodata_103b6c1                           @ 0x0103b6c1
 *   rodata_103b6d3                           @ 0x0103b6d3
 *   rodata_103b7ad                           @ 0x0103b7ad
 *   rodata_103b7f3                           @ 0x0103b7f3
 *   rodata_103e8cc                           @ 0x0103e8cc
 *   rodata_103e8d2                           @ 0x0103e8d2
 */
/* net-core FUN_01035830 @ 0x1035830  (parity 300 trials PROVEN) */
extern int FUN_0103533c(unsigned int, int, int, void*, void*);
extern void rpmsg_register_endpoint(int, int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void FUN_0103ac98(unsigned int);
extern void z_impl_k_sem_init(int, int);
extern void FUN_0103b62e(int, int, int);

#define DAT_01035950 0x01035f6du
#define DAT_01035954 0x0103b6b3u
#define DAT_01035958 0x0103b7adu
#define DAT_0103595c 0x0103b7f3u
#define DAT_01035960 0x01035dbdu
#define DAT_01035964 0x0103b6d3u
#define DAT_01035968 0x0103e8ccu
#define DAT_0103596c 0x0103e8d2u
#define DAT_01035970 0x0103b6c1u
#define DAT_01035974 0x01035e6du
#define DAT_01035978 0x00000035u
#define DAT_0103597c 0x00000035u

int FUN_01035830(int param_1, int param_2, unsigned int param_3, int param_4)
{
  unsigned int uVar1;
  int iVar2;
  int iVar3;
  unsigned int local_28;
  unsigned int local_24;
  unsigned int local_20;
  unsigned int local_1c;

  iVar3 = 0xfffff82d;
  if (((param_1 != 0) && (param_2 != 0)) && (param_4 != 0)) {
    FUN_0103b62e(param_1, 0, 0x94);
    z_impl_k_sem_init(param_1 + 0x58, 1);
    uVar1 = DAT_01035950;
    *(volatile int *)(param_1 + 0xa0) = param_2;
    *(volatile unsigned int *)(param_1 + 0x70) = param_3;
    *(volatile int *)(param_2 + 0x24) = param_1;
    *(volatile unsigned int *)(param_1 + 0x78) = uVar1;
    *(volatile unsigned int *)(param_1 + 0x7c) = DAT_01035954;
    *(volatile unsigned int *)(param_1 + 0x80) = DAT_01035958;
    *(volatile unsigned int *)(param_1 + 0x84) = DAT_0103595c;
    *(volatile unsigned int *)(param_1 + 0x88) = DAT_01035960;
    *(volatile unsigned int *)(param_1 + 0x8c) = DAT_01035964;
    iVar3 = *(volatile int *)(*(volatile int *)(param_1 + 0xa0) + 0x18);
    if (iVar3 == 1) {
      typedef int (*fp_t)(void);
      typedef void (*fp2_t)(int, int);
      do {
        while (1) {
          int base = *(volatile int *)(*(volatile int *)(param_1 + 0xa0) + 0x20);
          int iVar2b = ((fp_t)(*(volatile unsigned int *)(base + 8)))();
          if (!(iVar2b << 0x19 < 0)) break;
          int base2 = *(volatile int *)(*(volatile int *)(param_1 + 0xa0) + 0x20);
          ((fp2_t)(*(volatile unsigned int *)(base2 + 0xc)))(*(volatile int *)(param_1 + 0xa0), 0);
        }
      } while (0);
    }
    {
      typedef unsigned int (*fp3_t)(int);
      uVar1 = ((fp3_t)(*(volatile unsigned int *)(*(volatile int *)(*(volatile int *)(param_1 + 0xa0) + 0x20) + 0x10)))(param_2);
    }
    *(volatile unsigned int *)(param_2 + 0x10) = uVar1;
    *(volatile unsigned int *)(param_2 + 0x14) = 0;
    *(volatile unsigned char *)(param_1 + 0x90) = (unsigned char)uVar1 & 1;
    if (iVar3 == 1) {
      local_28 = DAT_01035968;
      local_24 = DAT_0103596c;
      local_20 = DAT_01035970;
      local_1c = DAT_01035974;
      *(volatile unsigned int *)(param_1 + 0xa4) = *(volatile unsigned int *)(*(volatile int *)(param_2 + 0x2c) + 0x18);
      *(volatile unsigned int *)(param_1 + 0xa8) = **(volatile unsigned int **)(param_2 + 0x2c);
    }
    *(volatile int *)(param_1 + 0xb4) = param_1 + 0xb4;
    *(volatile int *)(param_1 + 0xb8) = param_1 + 0xb4;
    *(volatile int *)(param_1 + 0xac) = param_4;
    iVar3 = FUN_0103533c(*(volatile unsigned int *)(param_1 + 0xa0), 0, 2, &local_28, &local_20);
    if (iVar3 == 0) {
      FUN_0103ac98(*(volatile unsigned int *)(param_1 + 0xa8));
      *(volatile int *)(**(volatile int **)(param_2 + 0x2c) + 0x28) = param_4;
      *(volatile int *)(*(volatile int *)(*(volatile int *)(param_2 + 0x2c) + 0x18) + 0x28) = param_4;
      *(volatile int *)param_1 = param_1;
      *(volatile int *)(param_1 + 4) = param_1;
      if (*(volatile char *)(param_1 + 0x90) != 0) {
        rpmsg_register_endpoint(param_1, param_1 + 8, DAT_0103597c, 0x35, 0x35, DAT_01035978, 0);
      }
    }
  }
  return iVar3;
}
