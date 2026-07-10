#include "g1_app_symbols.h"
/* named: l2cap_recv */
/* Reconstructed l2cap_recv @ 0x57db0  (parity: 30/30 trials, PROVEN) */
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
typedef unsigned char undefined,undefined1,byte,uchar,uint1;
typedef unsigned short undefined2,ushort,uint2,wchar_t;
typedef unsigned int undefined4,uint,uint3,code_t;
typedef unsigned long long undefined8,ulonglong;
typedef long long longlong; typedef unsigned long ulong; typedef signed char sbyte;
typedef long long(*code)();
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
static inline int isCurrentModePrivileged(void){unsigned c;__asm__ volatile("mrs %0, control":"=r"(c));return (c&1)==0;}
static inline int getBasePriority(void){unsigned b;__asm__ volatile("mrs %0, basepri":"=r"(b));return (int)b;}
static inline void setBasePriority(int p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__asm__ volatile("isb":::"memory");}
static inline int CARRY4(unsigned a,unsigned b){return (a+b)<a;}
static inline int CARRY1(unsigned a,unsigned b){return ((a&0xff)+(b&0xff))>0xff;}
static inline int CARRY2(unsigned a,unsigned b){return ((a&((uintptr_t)&tbl_ffc8) /*=0xffff*/)+(b&((uintptr_t)&tbl_ffc8) /*=0xffff*/))>((uintptr_t)&tbl_ffc8) /*=0xffff*/;}
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

extern long long FUN_000573f4();
extern long long l2cap_chan_rx_init();
extern long long l2cap_chan_tx_init();
extern long long l2cap_chan_add();
extern long long bt_l2cap_le_lookup_tx_cid();
extern long long net_buf_unref();
extern long long net_buf_simple_pull_5f594();
extern long long net_buf_simple_add();
extern long long FUN_00073518();
extern long long bt_conn_ltk_present();
extern long long bt_conn_set_security();
extern long long FUN_00081626();
extern long long ctx_list_unlink_by_key16();
extern long long FUN_000816a2();
extern long long conn_ctx_cleanup_if_pending();
extern long long FUN_00081746();
extern long long atomic_counter_add_and_signal();
extern long long ctx_list_unlink_node();
extern long long context_release_and_notify();
extern long long bt_conn_create_pdu();
extern long long att_send_simple();
extern long long bt_l2cap_le_lookup_tx_cid();
extern long long gatt_send_service_changed_ind();
extern long long net_buf_simple_push_mem();
#define DAT_00058054 "Too small L2CAP signaling PDU" /*=0xf41a7*/
#define DAT_00058058 ((uintptr_t)&tbl_880d8) /*=0x88160*/
#define DAT_0005805c "L2CAP length mismatch (%u != %u)" /*=0xf41c5*/
#define DAT_00058060 "Invalid ident value in L2CAP PDU" /*=0xf41e6*/
#define DAT_00058064 "Too small LE conn param rsp" /*=0xf4207*/
#define DAT_00058068 "Too small LE conn req packet size" /*=0xf4223*/
#define DAT_0005806c "Invalid LE-Conn Req params: mtu %u mps %u" /*=0xf4245*/
#define DAT_00058070 "Mandatory callback 'recv' missing" /*=0xf426f*/
#define DAT_00058074 ((uintptr_t)&tbl_81699) /*=0x816af*/
#define DAT_00058078 "Too small LE conn rsp packet size" /*=0xf4291*/
#define DAT_0005807c "Cannot find channel for ident %u" /*=0xf42b3*/
#define DAT_000582a0 "Too small LE disconn rsp packet size" /*=0xf42d4*/
#define DAT_000582a4 "Too small LE Credits packet size" /*=0xf42f9*/
#define DAT_000582a8 "Unable to find channel of LE Credits packet" /*=0xf431a*/
#define DAT_000582ac "Credits overflow" /*=0xf4346*/
#define DAT_000582b0 ((uintptr_t)&tbl_880d8) /*=0x88160*/
#define DAT_000582b4 (*(volatile int*)((uintptr_t)&tbl_582a0) /*=0x582b4*/)


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
  
  uVar13 = DAT_00058054;
  if (*(ushort *)(param_2 + 0x10) < 4) goto LAB_00057dc4;
  pbVar7 = (byte *)net_buf_simple_pull_5f594(param_2 + 0xc,4);
  uVar17 = (uint)*(ushort *)(param_2 + 0x10);
  local_54 = (uint)*(ushort *)(pbVar7 + 2);
  if (uVar17 != local_54) {
    local_5c = DAT_0005805c;
    local_58 = uVar17;
LAB_00057e04:
    local_60 = 4;
    FUN_00081746(DAT_00058058,0x2040,&local_60);
    return 0;
  }
  uVar18 = (uint)pbVar7[1];
  uVar13 = DAT_00058060;
  if (uVar18 == 0) goto LAB_00057dc4;
  uVar14 = (uint)*pbVar7;
  if (uVar14 == 1) {
    piVar10 = (int *)FUN_00081626(*param_1,uVar18);
LAB_000581ee:
    if (piVar10 == (int *)0x0) {
      return 0;
    }
    goto LAB_00058136;
  }
  if ((uVar14 - 6 & 0xff) < 0x11) {
    uVar13 = DAT_00058068;
    switch(uVar14 - 6) {
    case 0:
      iVar21 = *param_1;
      puVar15 = *(undefined2 **)(param_2 + 0xc);
      if (uVar17 < 4) break;
      iVar16 = ctx_list_unlink_by_key16(iVar21,*puVar15);
      if (iVar16 == 0) {
        local_40 = puVar15[1];
        local_3e = *puVar15;
        iVar11 = FUN_000573f4(1,uVar18,6);
        if (iVar11 == 0) {
          return 0;
        }
        puVar12 = (undefined1 *)net_buf_simple_add(iVar11 + 0xc,2);
        puVar12[1] = 0;
        *puVar12 = 2;
        net_buf_simple_push_mem(iVar11 + 0xc,&local_40,4);
      }
      else {
        iVar11 = FUN_000573f4(7,uVar18,4);
        if (iVar11 == 0) {
          return 0;
        }
        puVar15 = (undefined2 *)net_buf_simple_add(iVar11 + 0xc,4);
        *puVar15 = *(undefined2 *)(iVar16 + 0x14);
        puVar15[1] = *(undefined2 *)(iVar16 + 0x24);
        context_release_and_notify(iVar16);
      }
      goto LAB_000581ac;
    case 1:
      uVar13 = DAT_000582a0;
      if (3 < uVar17) {
        piVar10 = (int *)ctx_list_unlink_by_key16(*param_1,*(undefined2 *)(*(int *)(param_2 + 0xc) + 2));
        goto LAB_000581ee;
      }
      break;
    default:
      goto switchD_00057e38_caseD_2;
    case 0xd:
      uVar13 = DAT_00058064;
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
          local_5c = DAT_0005806c;
          goto LAB_00057e04;
        }
        iVar11 = FUN_000573f4(0x15,uVar18,10);
        if (iVar11 == 0) {
          return 0;
        }
        puVar8 = (undefined4 *)net_buf_simple_add(iVar11 + 0xc,10);
        *puVar8 = 0;
        puVar8[1] = 0;
        *(undefined2 *)(puVar8 + 2) = 0;
        puVar15 = (undefined2 *)bt_l2cap_le_lookup_tx_cid(uVar4);
        if (puVar15 == (undefined2 *)0x0) {
LAB_00057ed4:
          sVar20 = 2;
          goto LAB_00057ed6;
        }
        if (*(byte *)(iVar21 + 9) < *(byte *)(puVar15 + 1)) {
          if ((*(byte *)(iVar21 + 9) < 2) && (iVar16 = bt_conn_ltk_present(iVar21), iVar16 != 0)) {
            sVar20 = 8;
          }
          else {
            sVar20 = 5;
          }
          goto LAB_00057ed6;
        }
        if (0x3f < uVar2 - 0x40) {
          sVar20 = 9;
          goto LAB_00057ed6;
        }
        local_44 = bt_l2cap_le_lookup_tx_cid(iVar21,(uint)uVar2);
        if (local_44 != 0) {
          sVar20 = 10;
          goto LAB_00057ed6;
        }
        iVar9 = (**(code **)(puVar15 + 2))(iVar21,&local_44);
        iVar16 = local_44;
        uVar13 = DAT_00058074;
        if (iVar9 < 0) {
          if (iVar9 == -0xc) {
LAB_00057f58:
            sVar20 = 4;
            goto LAB_00057ed6;
          }
          if (iVar9 + 0xb < 0 == SCARRY4(iVar9,0xb)) {
            if (iVar9 == -1) {
              sVar20 = 7;
              goto LAB_00057ed6;
            }
          }
          else {
            if (iVar9 == -0x86) goto LAB_00057ed4;
            if (iVar9 == -0xd) {
              sVar20 = 6;
              goto LAB_00057ed6;
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
              goto LAB_00057ed6;
            }
            goto LAB_00057f58;
          }
          local_2c = DAT_00058070;
          local_30 = 2;
          FUN_00081746(DAT_00058058,0x1040,&local_30);
        }
        sVar20 = 0xb;
LAB_00057ed6:
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
        if ((code *)**(undefined4 **)(local_44 + 4) == (code *)0x0) {
          return 0;
        }
        (*(code *)**(undefined4 **)(local_44 + 4))();
        return 0;
      }
      break;
    case 0xf:
      iVar21 = *param_1;
      puVar15 = *(undefined2 **)(param_2 + 0xc);
      uVar13 = DAT_00058078;
      if (9 < uVar17) {
        local_4c = (uint)(ushort)puVar15[3];
        uVar4 = puVar15[1];
        uVar5 = puVar15[2];
        uVar2 = puVar15[4];
        uVar6 = *puVar15;
        if (((uVar2 & ((uintptr_t)&tbl_ffc8) /*=0xfff7*/) == 0) || (uVar2 == 5)) {
          piVar10 = (int *)FUN_00081626(iVar21,uVar18,0);
          if (piVar10 == (int *)0x0) goto LAB_00058032;
          FUN_00073518(piVar10 + 0x30);
          *(undefined1 *)(piVar10 + 0x2e) = 0;
          if (uVar2 != 5) goto LAB_0005809c;
          puVar19 = (uint *)(piVar10 + 4);
          iVar16 = *piVar10;
          iVar11 = FUN_000816a2(puVar19);
          if (-1 < iVar11 << 0x1d) {
            bVar1 = *(byte *)(iVar16 + 9);
            if (bVar1 < 2) goto LAB_00058142;
            if (bVar1 == 2) {
              uVar13 = 3;
            }
            else {
              if (bVar1 != 3) goto LAB_0005812c;
              uVar13 = 4;
            }
            goto LAB_000580fc;
          }
        }
        else {
          piVar10 = (int *)FUN_00081626(iVar21,uVar18,1);
          if (piVar10 == (int *)0x0) {
LAB_00058032:
            local_5c = DAT_0005807c;
            local_60 = 3;
            local_58 = uVar18;
            FUN_00081746(DAT_00058058,0x1840,&local_60);
            return 0;
          }
          FUN_00073518(piVar10 + 0x30);
          *(undefined1 *)(piVar10 + 0x2e) = 0;
LAB_0005809c:
          if (uVar2 != 8) {
            if (uVar2 == 0) {
              *(undefined1 *)(piVar10 + 0x2d) = 3;
              *(undefined2 *)(piVar10 + 9) = uVar6;
              *(undefined2 *)((int)piVar10 + 0x26) = uVar4;
              *(undefined2 *)(piVar10 + 10) = uVar5;
              if (*(code **)piVar10[1] != (code *)0x0) {
                (**(code **)piVar10[1])(piVar10);
              }
              atomic_counter_add_and_signal(piVar10,local_4c);
              return 0;
            }
            goto LAB_00058136;
          }
          puVar19 = (uint *)(piVar10 + 4);
          iVar16 = *piVar10;
          iVar11 = FUN_000816a2(puVar19);
          if ((-1 < iVar11 << 0x1d) && (*(byte *)(iVar16 + 9) < 2)) {
LAB_00058142:
            uVar13 = 2;
LAB_000580fc:
            iVar11 = bt_conn_set_security(*piVar10,uVar13);
            if (-1 < iVar11) {
              *puVar19 = *puVar19 | 4;
              return 0;
            }
          }
        }
LAB_0005812c:
        ctx_list_unlink_node(iVar21,piVar10);
LAB_00058136:
        context_release_and_notify(piVar10);
        return 0;
      }
      break;
    case 0x10:
      uVar13 = DAT_000582a4;
      if (3 < uVar17) {
        uVar17 = (uint)(ushort)(*(undefined2 **)(param_2 + 0xc))[1];
        iVar21 = bt_l2cap_le_lookup_tx_cid(*param_1,**(undefined2 **)(param_2 + 0xc));
        uVar13 = DAT_000582a8;
        if (iVar21 != 0) {
          iVar11 = FUN_000816a2(iVar21 + 0x2c);
          if (((uintptr_t)&tbl_ffc8) /*=0xffff*/ < (int)(iVar11 + uVar17)) {
            local_2c = DAT_000582ac;
            local_30 = 2;
            FUN_00081746(DAT_000582b0,0x1040,&local_30);
            gatt_send_service_changed_ind(iVar21);
            return 0;
          }
          atomic_counter_add_and_signal(iVar21,uVar17);
          conn_ctx_cleanup_if_pending(iVar21);
          return 0;
        }
      }
    }
LAB_00057dc4:
    local_30 = 2;
    local_2c = uVar13;
    FUN_00081746(DAT_00058058,0x1040,&local_30);
  }
  else {
switchD_00057e38_caseD_2:
    local_5c = DAT_000582b4;
    local_60 = 3;
    local_58 = uVar14;
    FUN_00081746(DAT_000582b0,0x1880,&local_60);
    iVar21 = *param_1;
    iVar11 = FUN_000573f4(1,pbVar7[1],2);
    if (iVar11 == 0) {
      return 0;
    }
    puVar12 = (undefined1 *)net_buf_simple_add(iVar11 + 0xc,2);
    *puVar12 = 0;
    puVar12[1] = 0;
LAB_000581ac:
    att_send_simple(iVar21,iVar11);
  }
  return 0;
}


