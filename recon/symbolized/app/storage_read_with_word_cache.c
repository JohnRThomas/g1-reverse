#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00061070 @ 0x00061070
 * public-name: storage_read_with_word_cache
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_get_zephyr_ret_code                 <= FUN_00060990 @ 0x00060990
 *   qspi_nor_acquire                         <= FUN_00060a10 @ 0x00060a10
 *   storage_read_with_word_cache             <= FUN_00061070 @ 0x00061070
 *   audio_i2s_stop_and_reset_channels        <= FUN_00083906 @ 0x00083906
 *   audio_i2s_start_channels                 <= FUN_0008392e @ 0x0008392e
 *   nrfx_qspi_read                           <= FUN_00085206 @ 0x00085206
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memmove                                  <= FUN_00086c44 @ 0x00086c44
 * address symbols (name @ address):
 *   rodata_88270                             @ 0x00088270
 */
/* Reconstructed FUN_00061070 @ 0x61070  (parity: 300/300 trials, PROVEN) */
extern int  qspi_get_zephyr_ret_code(int);
extern int  FUN_000609f4(int,int);
extern int  qspi_nor_acquire(void);
extern int  FUN_00060a5c(int);
extern void audio_i2s_stop_and_reset_channels(int);
extern void audio_i2s_start_channels(int);
extern void FUN_000838d6(int,int,void*);
extern int  nrfx_qspi_read(int,int,int);
extern int  memcpy(int,int,int);
extern int  memmove(int,int,int);
#define VI(a) (*(volatile int*)(a))

int storage_read_with_word_cache(int param_1,int param_2,unsigned int param_3,unsigned int param_4){
  int iVar1; unsigned int uVar2,uVar3,uVar4,uVar5,uVar6,uVar7,uVar8,t3;
  int L34,L38;
  unsigned char st[16];
  if (param_3==0) return -0x16;
  if (param_4==0) return 0;
  if ((param_2<0) || ((unsigned int)VI(VI(param_1+4)+0x2c) < (unsigned int)(param_2+param_4))) {
    FUN_000838d6(((unsigned long)&rodata_88270) /*=0x88270*/,0x2040,st);
    return -0x16;
  }
  iVar1 = qspi_nor_acquire();
  if (iVar1 != 0) goto LAB_611cc;
  audio_i2s_stop_and_reset_channels(param_1);
  uVar6 = (unsigned int)(-param_2) & 3u;
  if (param_4 <= uVar6) uVar6 = param_4;
  t3 = ((int)param_3 < 1) ? (unsigned int)(-(int)((unsigned int)(-(int)param_3)&3u))
                          : (param_3 & 3u);
  uVar4 = (unsigned int)(-(int)t3) & 3u;
  if (param_4 <= uVar4) uVar4 = param_4;
  uVar2 = param_4 - uVar6;
  uVar5 = (param_4 - uVar4) & 0xfffffffcu;
  uVar7 = uVar2 & 0xfffffffcu;
  uVar3 = ((int)uVar5 < (int)uVar7) ? uVar5 : uVar7;
  uVar8 = ((int)uVar5 < (int)uVar7) ? (uVar2 - uVar5) : (uVar2 & 3u);
  if (uVar3 == 0) goto LAB_61156;
  L34 = (int)(param_3 + uVar4); L38 = (int)uVar4;
  iVar1 = nrfx_qspi_read(L34, (int)uVar3, param_2 + (int)uVar6);
  FUN_000609f4(VI(param_1+0x10), iVar1);
  if (iVar1 == 0x0bad0000) {
    if (uVar6 != (unsigned int)L38) memmove((int)(param_3+uVar6), L34, (int)uVar3);
    goto LAB_61156;
  }
  goto LAB_611be;
LAB_61156:
  if (uVar6 != 0) {
    L34 = 4 - (int)uVar6;
    iVar1 = nrfx_qspi_read((int)st, 4, param_2 - L34);
    FUN_000609f4(VI(param_1+0x10), iVar1);
    if (iVar1 != 0x0bad0000) goto LAB_611be;
    memcpy((int)param_3, (int)st + L34, (int)uVar6);
  }
  iVar1 = 0x0bad0000;
  if (uVar8 != 0) {
    iVar1 = nrfx_qspi_read((int)st, 8, param_2 + (int)uVar6 + (int)uVar3);
    FUN_000609f4(VI(param_1+0x10), iVar1);
    if (iVar1 == 0x0bad0000) memcpy((int)(uVar3+uVar6+param_3), (int)st, (int)uVar8);
  }
LAB_611be:
  audio_i2s_start_channels(param_1);
  iVar1 = qspi_get_zephyr_ret_code(iVar1);
LAB_611cc:
  FUN_00060a5c(param_1);
  return iVar1;
}
