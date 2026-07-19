#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005f760 @ 0x0005f760
 * public-name: saadc_start_read
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   adc_context_start_sampling               <= FUN_0005f638 @ 0x0005f638
 *   saadc_start_read                         <= FUN_0005f760 @ 0x0005f760
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   z_impl_k_timer_start                     <= FUN_00075174 @ 0x00075174
 * address symbols (name @ address):
 *   rodata_880e0                             @ 0x000880e0
 *   rodata_f4240                             @ 0x000f4240
 *   rodata_f5571                             @ 0x000f5571
 *   rodata_f558f                             @ 0x000f558f
 *   rodata_f55a9                             @ 0x000f55a9
 *   rodata_f55ce                             @ 0x000f55ce
 *   rodata_f5600                             @ 0x000f5600
 *   rodata_f5623                             @ 0x000f5623
 *   adc_context                              @ 0x20002190
 *   g_adc_context_lock                       @ 0x200021d0
 *   g_adc_saadc_ctrl_mutex                   @ 0x200021e8
 *   m_adc_channel_input_cfg                  @ 0x20002230
 *   REG_5000e000                             @ 0x5000e000
 */
/* Reconstructed FUN_0005f760 @ 0x5f760  (parity: 200/200 trials, PROVEN) */
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int undefined4;

extern u64 __aeabi_uldivmod(int a, int b, u32 c, u32 d);
extern void z_log_msg_runtime_create(u32 a, u32 b, void *c, u32 d);
extern u64 adc_context_start_sampling(u32 a);
extern int k_sem_give(u32 a);
extern int z_impl_k_sem_take(u32 a, void *b, u32 c, u32 d);
extern u64 z_impl_k_timer_start(void *a, int b, u32 c, u32 d);

undefined4 saadc_start_read(undefined4 param_1, int *param_2)
{
  int iVar7, iVar5, iVar11;
  u32 uVar4, uVar6, uVar10;
  int bVar12;
  undefined4 uVar9;
  u64 r;
  volatile int *puVar3i;
  u32 range_error[2];
  u32 validation_error[3];
  u32 capacity_error[4];

  z_impl_k_sem_take(((unsigned long)&g_adc_context_lock) /*=0x200021d0*/, param_2, 0xffffffffu, 0xffffffffu);
  iVar7 = ((unsigned long)&m_adc_channel_input_cfg) /*=0x20002230*/;
  iVar5 = REG_5000e000 /*=0x5000e000*/;
  uVar10 = (u32)param_2[1];
  uVar9 = ((unsigned long)&rodata_f5571) /*=0xf5571*/;
  iVar11 = REG_5000e000 /*=0x5000e000*/;

  if (uVar10 - 1 < 0xff) {
    uVar4 = 0;
    uVar6 = 0;
    do {
      if (((uVar10 >> (uVar4 & 0xff)) & 1) == 0) {
        *(volatile u32*)(long)(iVar5 + (uVar4 + 0x51) * 0x10) = 0;
      } else {
        u8 bVar1 = *(volatile u8*)(long)(iVar7 + uVar4);
        if (bVar1 == 0) {
          uVar9 = ((unsigned long)&rodata_f558f) /*=0xf558f*/;
          goto LAB_f7c6;
        }
        bVar12 = *(u8*)((long)param_2 + 0x11);
        iVar11 = iVar5 + uVar4 * 0x10;
        if (bVar12 != 0) bVar12 = 1;
        *(volatile u32*)(long)(iVar11 + 0x518) =
            (*(volatile u32*)(long)(iVar11 + 0x518) & 0xfeffffffu) | ((u32)bVar12 << 0x18);
        *(volatile u32*)(long)(iVar5 + (uVar4 + 0x51) * 0x10) = (u32)bVar1;
        uVar6 = (uVar6 + 1) & 0xff;
      }
      iVar11 = REG_5000e000 /*=0x5000e000*/;
      uVar4 = uVar4 + 1;
    } while (uVar4 != 8);

    switch ((u32)*(u8*)(param_2 + 4)) {
      case 8: uVar9 = 0; break;
      default:
        uVar9 = ((unsigned long)&rodata_f55a9) /*=0xf55a9*/;
        uVar4 = (u32)*(u8*)(param_2 + 4);
        goto LAB_f7c6;
      case 10: uVar9 = 1; break;
      case 0xc: uVar9 = 2; break;
      case 0xe: uVar9 = 3; break;
    }
    *(volatile u32*)(REG_5000e000 /*=0x5000e000*/ + 0x5f0) = (u32)uVar9;
    uVar4 = (u32)*(u8*)((long)param_2 + 0x11);
    if (1 < uVar6) {
      uVar9 = ((unsigned long)&rodata_f55ce) /*=0xf55ce*/;
      if (uVar4 != 0) goto LAB_f782;
LAB_f874:
      *(volatile u32*)(long)(iVar11 + 0x5f4) = uVar4;
      puVar3i = (volatile int*)((unsigned long)&adc_context) /*=0x20002190*/;
      iVar5 = REG_5000e000 /*=0x5000e000*/;
      uVar10 = uVar6 * 2;
      if (*param_2 != 0) {
        uVar10 = (u32)(*(volatile u16*)((long)*param_2 + 0xc)) * uVar10 + uVar10;
      }
      if ((u32)param_2[3] < uVar10) {
        capacity_error[0] = 4;
        capacity_error[1] = ((unsigned long)&rodata_f5623) /*=0xf5623*/;
        capacity_error[2] = (u32)param_2[3];
        capacity_error[3] = uVar10;
        z_log_msg_runtime_create(((unsigned long)&rodata_880e0) /*=0x880e0*/, 0x2040u, capacity_error, 0);
        uVar9 = 0xfffffff4u;
        goto LAB_f7d6;
      }
      *(volatile int*)(REG_5000e000 /*=0x5000e000*/ + 0x62c) = param_2[2];
      *(volatile u32*)(long)(iVar5 + 0x630) = uVar6;
      iVar5 = param_2[1];
      iVar7 = param_2[2];
      iVar11 = param_2[3];
      puVar3i[0x1d] = *param_2;
      puVar3i[0x1e] = iVar5;
      puVar3i[0x1f] = iVar7;
      puVar3i[0x20] = iVar11;
      puVar3i[0x21] = param_2[4];
      puVar3i[0x1c] = 0;
      param_2 = (int *)(long)*param_2;
      if (param_2 == 0) {
LAB_f948:
        r = adc_context_start_sampling(((unsigned long)&adc_context) /*=0x20002190*/);
        uVar9 = (u32)(r >> 32);
      } else {
        int iVar8;
        iVar5 = *param_2;
        iVar7 = param_2[1];
        iVar11 = param_2[2];
        iVar8 = param_2[3];
        puVar3i[0x22] = iVar5;
        puVar3i[0x23] = iVar7;
        puVar3i[0x24] = iVar11;
        puVar3i[0x25] = iVar8;
        puVar3i[0x1d] = (int)(long)(puVar3i + 0x22);
        *(volatile u16*)(long)(puVar3i + 0x26) = 0;
        if (iVar5 == 0) goto LAB_f948;
        *puVar3i = 0;
        {
          long long lVar2 = (long long)(u32)puVar3i[0x22] * 0x8000LL + (long long)0x000f423fL;
          r = __aeabi_uldivmod((int)lVar2, (int)(lVar2>>32), ((unsigned long)&rodata_f4240) /*=0xf4240*/, 0);
          r = z_impl_k_timer_start((void*)(puVar3i + 2), (int)(r>>32), 0, 0);
          uVar9 = (u32)(r>>32);
        }
      }
      iVar5 = z_impl_k_sem_take(((unsigned long)&g_adc_saadc_ctrl_mutex) /*=0x200021e8*/, (void*)(long)uVar9, 0xffffffffu, 0xffffffffu);
      if (iVar5 != 0) {
        puVar3i[0x1c] = iVar5;
      }
      uVar9 = (u32)puVar3i[0x1c];
      goto LAB_f7d6;
    }
    uVar9 = ((unsigned long)&rodata_f5600) /*=0xf5600*/;
    if (uVar4 < 9) goto LAB_f874;
LAB_f7c6:
    validation_error[0] = 3;
    validation_error[1] = uVar9;
    validation_error[2] = uVar4;
    z_log_msg_runtime_create(((unsigned long)&rodata_880e0) /*=0x880e0*/, 0x1840u, validation_error, 0);
  } else {
LAB_f782:
    range_error[0] = 2;
    range_error[1] = uVar9;
    z_log_msg_runtime_create(((unsigned long)&rodata_880e0) /*=0x880e0*/, 0x1040u, range_error, 0);
  }
  uVar9 = 0xffffffeau;
LAB_f7d6:
  k_sem_give(((unsigned long)&g_adc_context_lock) /*=0x200021d0*/);
  return uVar9;
}
