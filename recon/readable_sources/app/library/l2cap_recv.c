#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_net_buf__param_0224                    [param_0224; library]
 *   local_44         => struct g1_layout_bt_l2cap_le_chan_rx_local__stack_1192  [stack_1192; library]
 * Raw function identity: 0x00057db0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00057db0 @ 0x00057db0
 * public-name: l2cap_recv
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_alloc_pdu_with_hdr                   <= FUN_000573f4 @ 0x000573f4
 *   l2cap_chan_rx_init                       <= FUN_00057484 @ 0x00057484
 *   l2cap_chan_tx_init                       <= FUN_000574ec @ 0x000574ec
 *   l2cap_chan_add                           <= FUN_00057874 @ 0x00057874
 *   l2cap_find_chan_by_id                    <= FUN_000579b4 @ 0x000579b4
 *   l2cap_recv                               <= FUN_00057db0 @ 0x00057db0
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_simple_pull_5f594                <= FUN_0005f594 @ 0x0005f594
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   k_work_cancel_delayable                  <= FUN_00073518 @ 0x00073518
 *   bt_conn_ltk_present                      <= FUN_0008145c @ 0x0008145c
 *   g1_recon_bt_conn_set_security            <= FUN_0008149a @ 0x0008149a
 *   l2cap_lookup_chan_by_ident               <= FUN_00081626 @ 0x00081626
 *   ctx_list_unlink_by_key16                 <= FUN_00081660 @ 0x00081660
 *   atomic_get_word                          <= FUN_000816a2 @ 0x000816a2
 *   conn_ctx_cleanup_if_pending              <= FUN_00081720 @ 0x00081720
 *   log_msg_3arg_thunk                       <= FUN_00081746 @ 0x00081746
 *   atomic_counter_add_and_signal            <= FUN_0008174c @ 0x0008174c
 *   ctx_list_unlink_node                     <= FUN_00081788 @ 0x00081788
 *   context_release_and_notify               <= FUN_000817b6 @ 0x000817b6
 *   bt_conn_create_pdu                       <= FUN_00081820 @ 0x00081820
 *   att_send_simple                          <= FUN_00081940 @ 0x00081940
 *   bt_l2cap_le_lookup_tx_cid                <= FUN_00081a4e @ 0x00081a4e
 *   gatt_send_service_changed_ind            <= FUN_00081b30 @ 0x00081b30
 *   net_buf_simple_add_mem                   <= FUN_00083740 @ 0x00083740
 * address symbols (name @ address):
 *   rodata_582b4                             @ 0x000582b4
 *   rodata_816af                             @ 0x000816af
 *   rodata_88160                             @ 0x00088160
 *   rodata_f41a7                             @ 0x000f41a7
 *   rodata_f41c5                             @ 0x000f41c5
 *   rodata_f41e6                             @ 0x000f41e6
 *   rodata_f4207                             @ 0x000f4207
 *   rodata_f4223                             @ 0x000f4223
 *   rodata_f4245                             @ 0x000f4245
 *   rodata_f426f                             @ 0x000f426f
 *   rodata_f4291                             @ 0x000f4291
 *   rodata_f42b3                             @ 0x000f42b3
 *   rodata_f42d4                             @ 0x000f42d4
 *   rodata_f42f9                             @ 0x000f42f9
 *   rodata_f431a                             @ 0x000f431a
 *   rodata_f4346                             @ 0x000f4346
 */
/* Reconstructed FUN_00057db0 @ 0x57db0  (parity: 30/30 trials, PROVEN) */
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#include <stdint.h>
#include <cmsis_gcc.h>
typedef unsigned char undefined,undefined1,byte,uchar,uint1;
typedef unsigned short undefined2,ushort,uint2,wchar_t;
typedef unsigned int undefined4,uint,uint3,code_t;
typedef unsigned long long undefined8,ulonglong;
typedef long long longlong; typedef unsigned long ulong; typedef signed char sbyte;
typedef long long(*code0)(void);
typedef long long(*code1)(int);
typedef long long(*code2)(int, void *);
#define bool int
#define false 0
#define true 1
#define NAN(x) __builtin_isnan((double)(x))
#define ABS(x) __builtin_fabs((double)(x))
#define SQRT(x) __builtin_sqrt((double)(x))
#define FPMaxNum(a,b) __builtin_fmaxf((a),(b))
#define FPMinNum(a,b) __builtin_fminf((a),(b))
#define FPMax(a,b) __builtin_fmaxf((a),(b))
#define FPMin(a,b) __builtin_fminf((a),(b))
static inline int isCurrentModePrivileged(void){ return (__get_CONTROL() & 1u) == 0; }
static inline int getBasePriority(void){ return (int)__get_BASEPRI(); }
static inline void setBasePriority(int p){ __set_BASEPRI((uint32_t)p); }
static inline void InstructionSynchronizationBarrier(int x){ (void)x; __ISB(); }
static inline int CARRY4(unsigned a,unsigned b){return (a+b)<a;}
static inline int CARRY1(unsigned a,unsigned b){return ((a&0xff)+(b&0xff))>0xff;}
static inline int CARRY2(unsigned a,unsigned b){return ((a&0xffff)+(b&0xffff))>0xffff;}
static inline int SCARRY4(int a,int b){int r=(int)((unsigned)a+(unsigned)b);return (((a^r)&(b^r))<0);}
static inline int SBORROW4(int a,int b){int r=(int)((unsigned)a-(unsigned)b);return (((a^b)&(a^r))<0);}
static inline int SBORROW1(int a,int b){signed char r=(signed char)(a-b);return ((((signed char)a^(signed char)b)&((signed char)a^r))<0);}
static inline int SBORROW2(int a,int b){short r=(short)(a-b);return ((((short)a^(short)b)&((short)a^r))<0);}

#define CONCAT11(a,b) ((unsigned short)(((unsigned)(unsigned char)(a)<<8)|(unsigned char)(b)))
#define CONCAT21(a,b) (((unsigned)(unsigned short)(a)<<8)|(unsigned char)(b))
#define CONCAT12(a,b) (((unsigned)(unsigned char)(a)<<16)|(unsigned short)(b))
#define CONCAT31(a,b) (((unsigned)(a)<<8)|(unsigned char)(b))
#define CONCAT13(a,b) (((unsigned)(unsigned char)(a)<<24)|((unsigned)(b)&0xffffffu))
#define CONCAT22(a,b) (((unsigned)(unsigned short)(a)<<16)|(unsigned short)(b))
#define CONCAT41(a,b) (((unsigned long long)(unsigned)(a)<<8)|(unsigned char)(b))
#define CONCAT44(a,b) (((unsigned long long)(unsigned)(a)<<32)|(unsigned)(b))
#define CONCAT62(a,b) (((unsigned long long)(a)<<16)|(unsigned short)(b))
#define CONCAT71(a,b) (((unsigned long long)(a)<<8)|(unsigned char)(b))
#define CONCAT53(a,b) (((unsigned long long)(a)<<24)|((unsigned)(b)&0xffffffu))
#define CONCAT61(a,b) (((unsigned long long)(a)<<8)|(unsigned char)(b))
#define SUB41(x,n) ((unsigned char)((unsigned)(x)>>((n)*8)))
#define SUB42(x,n) ((unsigned short)((unsigned)(x)>>((n)*8)))
#define SUB84(x,n) ((unsigned)((unsigned long long)(x)>>((n)*8)))
#define SUB81(x,n) ((unsigned char)((unsigned long long)(x)>>((n)*8)))
#define SUB82(x,n) ((unsigned short)((unsigned long long)(x)>>((n)*8)))
#define SUB83(x,n) ((unsigned)(((unsigned long long)(x)>>((n)*8))&0xffffffu))
#define SUB168(x,n) ((unsigned long long)(x))
#define ZEXT14(a) ((unsigned)(unsigned char)(a))
#define ZEXT18(a) ((unsigned long long)(unsigned char)(a))
#define ZEXT24(a) ((unsigned)(unsigned short)(a))
#define ZEXT28(a) ((unsigned long long)(unsigned short)(a))
#define ZEXT48(a) ((unsigned long long)(unsigned)(a))
#define ZEXT12(a) ((unsigned short)(unsigned char)(a))
#define ZEXT816(a) ((unsigned long long)(a))
#define SEXT14(a) ((unsigned)(int)(signed char)(a))
#define SEXT18(a) ((unsigned long long)(long long)(signed char)(a))
#define SEXT24(a) ((unsigned)(int)(short)(a))
#define SEXT48(a) ((unsigned long long)(long long)(int)(a))
#define __ROL4(x,n) (((unsigned)(x)<<((n)&31))|((unsigned)(x)>>((32-((n)&31))&31)))
#define __ROR4(x,n) (((unsigned)(x)>>((n)&31))|((unsigned)(x)<<((32-((n)&31))&31)))
#define __ROL1(x,n) ((unsigned char)(((unsigned)(unsigned char)(x)<<((n)&7))|((unsigned)(unsigned char)(x)>>((8-((n)&7))&7))))

extern long long att_alloc_pdu_with_hdr(int, ...);
extern long long l2cap_chan_rx_init(int, ...);
extern long long l2cap_chan_tx_init(int, ...);
extern long long l2cap_chan_add(int, ...);
extern long long l2cap_find_chan_by_id(int, ...);
extern long long net_buf_unref(int, ...);
extern long long net_buf_simple_pull_5f594(int, ...);
extern long long net_buf_simple_add(int, ...);
extern long long k_work_cancel_delayable(int, ...);
extern long long bt_conn_ltk_present(int, ...);
extern long long g1_recon_bt_conn_set_security(int, ...);
extern long long l2cap_lookup_chan_by_ident(int, ...);
extern long long ctx_list_unlink_by_key16(int, ...);
extern long long atomic_get_word(int, ...);
extern long long conn_ctx_cleanup_if_pending(int, ...);
extern long long log_msg_3arg_thunk(int, ...);
extern long long atomic_counter_add_and_signal(int, ...);
extern long long ctx_list_unlink_node(int, ...);
extern long long context_release_and_notify(int, ...);
extern long long bt_conn_create_pdu(int, ...);
extern long long att_send_simple(int, ...);
extern long long bt_l2cap_le_lookup_tx_cid(int, ...);
extern long long gatt_send_service_changed_ind(int, ...);
extern long long net_buf_simple_add_mem(int, ...);
#define firmware_data_00058054 ((unsigned long)&rodata_f41a7) /*=0xf41a7*/
#define firmware_data_00058058 ((unsigned long)&rodata_88160) /*=0x88160*/
#define firmware_data_0005805c ((unsigned long)&rodata_f41c5) /*=0xf41c5*/
#define firmware_data_00058060 ((unsigned long)&rodata_f41e6) /*=0xf41e6*/
#define firmware_data_00058064 ((unsigned long)&rodata_f4207) /*=0xf4207*/
#define firmware_data_00058068 ((unsigned long)&rodata_f4223) /*=0xf4223*/
#define firmware_data_0005806c ((unsigned long)&rodata_f4245) /*=0xf4245*/
#define firmware_data_00058070 ((unsigned long)&rodata_f426f) /*=0xf426f*/
#define firmware_data_00058074 ((unsigned long)&rodata_816af) /*=0x816af*/
#define firmware_data_00058078 ((unsigned long)&rodata_f4291) /*=0xf4291*/
#define firmware_data_0005807c ((unsigned long)&rodata_f42b3) /*=0xf42b3*/
#define firmware_data_000582a0 ((unsigned long)&rodata_f42d4) /*=0xf42d4*/
#define firmware_data_000582a4 ((unsigned long)&rodata_f42f9) /*=0xf42f9*/
#define firmware_data_000582a8 ((unsigned long)&rodata_f431a) /*=0xf431a*/
#define firmware_data_000582ac ((unsigned long)&rodata_f4346) /*=0xf4346*/
#define firmware_data_000582b0 ((unsigned long)&rodata_88160) /*=0x88160*/
#define firmware_data_000582b4 (*(volatile int*)((unsigned long)&rodata_582b4) /*=0x582b4*/)


/* WARNING: Removing unreachable block (ram,0x0005811a) */

undefined4 l2cap_recv(int *param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  byte *pbVar7;
  undefined4 *puVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  undefined1 *puVar12;
  undefined4 uVar13;
  uint uVar14;
  undefined2 *puVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  uint *puVar19;
  short sVar20;
  int iVar21;
  undefined4 local_60;
  undefined4 local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  int local_44;
  undefined2 local_40;
  undefined2 local_3e;
  undefined4 local_30;
  undefined4 local_2c;
  struct { uint count, format, value0, value1; } log4;
  struct { uint count, format, value; } log3;

  uVar13 = firmware_data_00058054;
  if (*(ushort *)(param_2 + 0x10) < 4) goto control_label_00057dc4;
  pbVar7 = (byte *)net_buf_simple_pull_5f594(param_2 + 0xc,4);
  uVar17 = (uint)*(ushort *)(param_2 + 0x10);
  local_54 = (uint)*(ushort *)(pbVar7 + 2);
  if (uVar17 != local_54) {
    local_5c = firmware_data_0005805c;
    local_58 = uVar17;
control_label_00057e04:
    log4.count = 4;
    log4.format = local_5c;
    log4.value0 = local_58;
    log4.value1 = local_54;
    log_msg_3arg_thunk(firmware_data_00058058,0x2040,&log4);
    return 0;
  }
  uVar18 = (uint)pbVar7[1];
  uVar13 = firmware_data_00058060;
  if (uVar18 == 0) goto control_label_00057dc4;
  uVar14 = (uint)*pbVar7;
  if (uVar14 == 1) {
    piVar10 = (int *)l2cap_lookup_chan_by_ident(*param_1,uVar18);
control_label_000581ee:
    if (piVar10 == (int *)0x0) {
      return 0;
    }
    goto control_label_00058136;
  }
  if ((uVar14 - 6 & 0xff) < 0x11) {
    uVar13 = firmware_data_00058068;
    switch(uVar14 - 6) {
    case 0:
      iVar21 = *param_1;
      puVar15 = *(undefined2 **)(param_2 + 0xc);
      if (uVar17 < 4) break;
      iVar16 = ctx_list_unlink_by_key16(iVar21,*puVar15);
      if (iVar16 == 0) {
        local_40 = puVar15[1];
        local_3e = *puVar15;
        iVar11 = att_alloc_pdu_with_hdr(1,uVar18,6);
        if (iVar11 == 0) {
          return 0;
        }
        puVar12 = (undefined1 *)net_buf_simple_add(iVar11 + 0xc,2);
        puVar12[1] = 0;
        *puVar12 = 2;
        net_buf_simple_add_mem(iVar11 + 0xc,&local_40,4);
      }
      else {
        iVar11 = att_alloc_pdu_with_hdr(7,uVar18,4);
        if (iVar11 == 0) {
          return 0;
        }
        puVar15 = (undefined2 *)net_buf_simple_add(iVar11 + 0xc,4);
        *puVar15 = *(undefined2 *)(iVar16 + 0x14);
        puVar15[1] = *(undefined2 *)(iVar16 + 0x24);
        context_release_and_notify(iVar16);
      }
      goto control_label_000581ac;
    case 1:
      uVar13 = firmware_data_000582a0;
      if (3 < uVar17) {
        piVar10 = (int *)ctx_list_unlink_by_key16(*param_1,*(undefined2 *)(*(int *)(param_2 + 0xc) + 2));
        goto control_label_000581ee;
      }
      break;
    default:
      goto switchD_00057e38_caseD_2;
    case 0xd:
      uVar13 = firmware_data_00058064;
      if (1 < uVar17) {
        return 0;
      }
      break;
    case 0xe:
      iVar21 = *param_1;
      puVar15 = *(undefined2 **)(param_2 + 0xc);
      if (9 < uVar17) {
        local_58 = (uint)(ushort)puVar15[2];
        uVar2 = puVar15[1];
        uVar3 = puVar15[3];
        uVar4 = *puVar15;
        local_50 = (uint)(ushort)puVar15[4];
        local_54 = (uint)uVar3;
        local_4c = local_58;
        if ((local_58 < 0x17) || (local_54 < 0x17)) {
          local_5c = firmware_data_0005806c;
          goto control_label_00057e04;
        }
        iVar11 = att_alloc_pdu_with_hdr(0x15,uVar18,10);
        if (iVar11 == 0) {
          return 0;
        }
        puVar8 = (undefined4 *)net_buf_simple_add(iVar11 + 0xc,10);
        *puVar8 = 0;
        puVar8[1] = 0;
        *(undefined2 *)(puVar8 + 2) = 0;
        puVar15 = (undefined2 *)l2cap_find_chan_by_id(uVar4);
        if (puVar15 == (undefined2 *)0x0) {
control_label_00057ed4:
          sVar20 = 2;
          goto control_label_00057ed6;
        }
        if (*(byte *)(iVar21 + 9) < *(byte *)(puVar15 + 1)) {
          if ((*(byte *)(iVar21 + 9) < 2) && (iVar16 = bt_conn_ltk_present(iVar21), iVar16 != 0)) {
            sVar20 = 8;
          }
          else {
            sVar20 = 5;
          }
          goto control_label_00057ed6;
        }
        if (0x3f < uVar2 - 0x40) {
          sVar20 = 9;
          goto control_label_00057ed6;
        }
        local_44 = bt_l2cap_le_lookup_tx_cid(iVar21,(uint)uVar2);
        if (local_44 != 0) {
          sVar20 = 10;
          goto control_label_00057ed6;
        }
        iVar9 = (**(code2 **)(puVar15 + 2))(iVar21,&local_44);
        iVar16 = local_44;
        uVar13 = firmware_data_00058074;
        if (iVar9 < 0) {
          if (iVar9 == -0xc) {
control_label_00057f58:
            sVar20 = 4;
            goto control_label_00057ed6;
          }
          if (iVar9 + 0xb < 0 == SCARRY4(iVar9,0xb)) {
            if (iVar9 == -1) {
              sVar20 = 7;
              goto control_label_00057ed6;
            }
          }
          else {
            if (iVar9 == -0x86) goto control_label_00057ed4;
            if (iVar9 == -0xd) {
              sVar20 = 6;
              goto control_label_00057ed6;
            }
          }
        }
        else {
          if (*(int *)(*(int *)(local_44 + 4) + 0x14) != 0) {
            *(undefined1 *)(local_44 + 0xb9) = *(undefined1 *)(puVar15 + 1);
            iVar9 = l2cap_chan_add(iVar21,local_44,uVar13);
            if (iVar9 != 0) {
              l2cap_chan_tx_init(iVar16);
              *(undefined2 *)(iVar16 + 0x26) = (undefined2)local_4c;
              *(ushort *)(iVar16 + 0x24) = uVar2;
              *(ushort *)(iVar16 + 0x28) = uVar3;
              atomic_counter_add_and_signal(iVar16,local_50);
              l2cap_chan_rx_init(iVar16);
              sVar20 = 0;
              *(undefined2 *)(iVar16 + 0xb6) = *puVar15;
              *(undefined1 *)(local_44 + 0xb4) = 3;
              *(undefined2 *)puVar8 = *(undefined2 *)(local_44 + 0x14);
              *(undefined2 *)(puVar8 + 1) = *(undefined2 *)(local_44 + 0x18);
              *(undefined2 *)((int)puVar8 + 2) = *(undefined2 *)(local_44 + 0x16);
              *(short *)((int)puVar8 + 6) = (short)*(undefined4 *)(local_44 + 0x1c);
              goto control_label_00057ed6;
            }
            goto control_label_00057f58;
          }
          local_2c = firmware_data_00058070;
          local_30 = 2;
          log_msg_3arg_thunk(firmware_data_00058058,0x1040,&local_30);
        }
        sVar20 = 0xb;
control_label_00057ed6:
        *(short *)(puVar8 + 2) = sVar20;
        local_58 = 0;
        iVar21 = bt_conn_create_pdu(iVar21,5,iVar11);
        if (iVar21 != 0) {
          net_buf_unref(iVar11);
          return 0;
        }
        if (sVar20 != 0) {
          return 0;
        }
        if ((code0 *)**(undefined4 **)(local_44 + 4) == (code0 *)0x0) {
          return 0;
        }
        (*(code0 *)**(undefined4 **)(local_44 + 4))();
        return 0;
      }
      break;
    case 0xf:
      iVar21 = *param_1;
      puVar15 = *(undefined2 **)(param_2 + 0xc);
      uVar13 = firmware_data_00058078;
      if (9 < uVar17) {
        local_4c = (uint)(ushort)puVar15[3];
        uVar4 = puVar15[1];
        uVar5 = puVar15[2];
        uVar2 = puVar15[4];
        uVar6 = *puVar15;
        if (((uVar2 & 0xfff7) == 0) || (uVar2 == 5)) {
          piVar10 = (int *)l2cap_lookup_chan_by_ident(iVar21,uVar18,0);
          if (piVar10 == (int *)0x0) goto control_label_00058032;
          k_work_cancel_delayable(piVar10 + 0x30);
          *(undefined1 *)(piVar10 + 0x2e) = 0;
          if (uVar2 != 5) goto control_label_0005809c;
          puVar19 = (uint *)(piVar10 + 4);
          iVar16 = *piVar10;
          iVar11 = atomic_get_word(puVar19);
          if (-1 < iVar11 << 0x1d) {
            bVar1 = *(byte *)(iVar16 + 9);
            if (bVar1 < 2) goto control_label_00058142;
            if (bVar1 == 2) {
              uVar13 = 3;
            }
            else {
              if (bVar1 != 3) goto control_label_0005812c;
              uVar13 = 4;
            }
            goto control_label_000580fc;
          }
        }
        else {
          piVar10 = (int *)l2cap_lookup_chan_by_ident(iVar21,uVar18,1);
          if (piVar10 == (int *)0x0) {
control_label_00058032:
            log3.count = 3;
            log3.format = firmware_data_0005807c;
            log3.value = uVar18;
            log_msg_3arg_thunk(firmware_data_00058058,0x1840,&log3);
            return 0;
          }
          k_work_cancel_delayable(piVar10 + 0x30);
          *(undefined1 *)(piVar10 + 0x2e) = 0;
control_label_0005809c:
          if (uVar2 != 8) {
            if (uVar2 == 0) {
              *(undefined1 *)(piVar10 + 0x2d) = 3;
              *(undefined2 *)(piVar10 + 9) = uVar6;
              *(undefined2 *)((int)piVar10 + 0x26) = uVar4;
              *(undefined2 *)(piVar10 + 10) = uVar5;
              if (*(code1 **)piVar10[1] != (code1 *)0x0) {
                (**(code1 **)piVar10[1])((int)piVar10);
              }
              atomic_counter_add_and_signal(piVar10,local_4c);
              return 0;
            }
            goto control_label_00058136;
          }
          puVar19 = (uint *)(piVar10 + 4);
          iVar16 = *piVar10;
          iVar11 = atomic_get_word(puVar19);
          if ((-1 < iVar11 << 0x1d) && (*(byte *)(iVar16 + 9) < 2)) {
control_label_00058142:
            uVar13 = 2;
control_label_000580fc:
            iVar11 = g1_recon_bt_conn_set_security(*piVar10,uVar13);
            if (-1 < iVar11) {
              *puVar19 = *puVar19 | 4;
              return 0;
            }
          }
        }
control_label_0005812c:
        ctx_list_unlink_node(iVar21,piVar10);
control_label_00058136:
        context_release_and_notify(piVar10);
        return 0;
      }
      break;
    case 0x10:
      uVar13 = firmware_data_000582a4;
      if (3 < uVar17) {
        uVar17 = (uint)(ushort)(*(undefined2 **)(param_2 + 0xc))[1];
        iVar21 = bt_l2cap_le_lookup_tx_cid(*param_1,**(undefined2 **)(param_2 + 0xc));
        uVar13 = firmware_data_000582a8;
        if (iVar21 != 0) {
          iVar11 = atomic_get_word(iVar21 + 0x2c);
          if (0xffff < (int)(iVar11 + uVar17)) {
            local_2c = firmware_data_000582ac;
            local_30 = 2;
            log_msg_3arg_thunk(firmware_data_000582b0,0x1040,&local_30);
            gatt_send_service_changed_ind(iVar21);
            return 0;
          }
          atomic_counter_add_and_signal(iVar21,uVar17);
          conn_ctx_cleanup_if_pending(iVar21);
          return 0;
        }
      }
    }
control_label_00057dc4:
    local_30 = 2;
    local_2c = uVar13;
    log_msg_3arg_thunk(firmware_data_00058058,0x1040,&local_30);
  }
  else {
switchD_00057e38_caseD_2:
    log3.count = 3;
    log3.format = firmware_data_000582b4;
    log3.value = uVar14;
    log_msg_3arg_thunk(firmware_data_000582b0,0x1880,&log3);
    iVar21 = *param_1;
    iVar11 = att_alloc_pdu_with_hdr(1,pbVar7[1],2);
    if (iVar11 == 0) {
      return 0;
    }
    puVar12 = (undefined1 *)net_buf_simple_add(iVar11 + 0xc,2);
    *puVar12 = 0;
    puVar12[1] = 0;
control_label_000581ac:
    att_send_simple(iVar21,iVar11);
  }
  return 0;
}
