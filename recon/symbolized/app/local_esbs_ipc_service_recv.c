#include "g1_app_symbols.h"
/* named: local_esbs_ipc_service_recv */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x200069fc  device_info                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed local_esbs_ipc_service_recv @ 0x15960  (parity: 40/40 trials, PROVEN) */
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
typedef unsigned char undefined,undefined1,byte,uchar,uint1;
typedef unsigned short undefined2,ushort,uint2,wchar_t;
typedef unsigned int undefined4,uint,uint3,code_t,undefined3,undefined5,undefined6,undefined7;
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

extern long long DEBUG_PRINT();
extern long long switch_to_dfu_mode();
extern long long debug_print();
extern long long find_message_pool_entry_by_id();
extern long long msg_queue_init();
extern long long confirm_message();
extern long long reset_esb_sync_state();
extern long long set_device_sync_timestamp();
extern long long memset_bytes();
extern long long thunk_FUN_00072880();
extern long long update_persist_task_status();
#define DAT_00015b90 ((volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/)
#define DAT_00015b94 ((volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_00015b98 "local_esbs_ipc_service_recv" /*=0x99b89*/
#define DAT_00015bb8 ((volatile int*)((uintptr_t)&device_info) /*=0x200069fc*/)
#define DAT_00015bbc "%s(): slave recv wrong up package\n" /*=0x9924f*/
#define DAT_00015bc0 "%s(): slave recv wrong down package\n" /*=0x99272*/
#define DAT_00015de4 "local_esbs_ipc_service_recv" /*=0x99b89*/
#define DAT_00015de8 "%s(): ##########%s %d SYNC_DISPLAY_CMD_COMFIRM_NOTIFY_FIRST slave before\n" /*=0x99297*/
#define DAT_00015dec "%s(): ##########%s %d SYNC_DISPLAY_CMD_COMFIRM_NOTIFY_END slave before\n" /*=0x992e1*/
#define DAT_00015df0 ((uintptr_t)&g_esb_notify_sync_substate) /*=0x20018d98*/
#define PTR_s__s____slave_recv_same_package_00015b9c (*(volatile int*)((uintptr_t)&tbl_15b90) /*=0x15b9c*/)
#define PTR_s__s___________________loss_packag_00015ba0 (*(volatile int*)((uintptr_t)&tbl_15b90) /*=0x15ba0*/)
#define PTR_s__s____slave_recv_suspend_package_00015ba4 (*(volatile int*)((uintptr_t)&tbl_15b90) /*=0x15ba4*/)
#define PTR_s__s____slave_recv_resume_package_00015ba8 (*(volatile int*)((uintptr_t)&tbl_15b90) /*=0x15ba8*/)
#define PTR_s__s____slave_recv_up_recving_00015bac (*(volatile int*)((uintptr_t)&tbl_15b90) /*=0x15bac*/)
#define PTR_s__s____slave_recv_down_recving_00015bb0 (*(volatile int*)((uintptr_t)&tbl_15b90) /*=0x15bb0*/)
#define PTR_s__s____slave_even_ai_recv_down_re_00015bb4 (*(volatile int*)((uintptr_t)&tbl_15b90) /*=0x15bb4*/)
#define PTR_DAT_00015dd8 (*(volatile int*)((uintptr_t)&tbl_15dd8) /*=0x15dd8*/)
#define PTR_DAT_00015ddc (*(volatile int*)((uintptr_t)&tbl_15dd8) /*=0x15ddc*/)
#define PTR_IS_DEBUG_00015de0 (*(volatile int*)"Tu" /*=0x15de0*/)


undefined4 local_esbs_ipc_service_recv(int param_1,byte *param_2)

{
  byte bVar1;
  undefined4 *puVar2;
  undefined *format_string;
  undefined4 uVar3;
  undefined1 uVar4;
  undefined4 *puVar5;
  byte *pbVar6;
  int iVar7;
  byte *pbVar8;
  undefined1 *puVar9;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  byte local_24 [4];
  byte local_20;
  undefined4 local_1f;
  
  local_30 = 0;
  memset_bytes(&uStack_2c,0,0x12);
  puVar2 = &local_30;
  pbVar6 = param_2 + 0xb;
  do {
    pbVar8 = pbVar6;
    puVar5 = puVar2;
    uVar3 = *(undefined4 *)(pbVar8 + 4);
    pbVar6 = pbVar8 + 8;
    *puVar5 = *(undefined4 *)pbVar8;
    puVar5[1] = uVar3;
    puVar2 = puVar5 + 2;
  } while (pbVar6 != param_2 + 0x1b);
  puVar5[2] = *(undefined4 *)pbVar6;
  *(byte *)(puVar5 + 3) = pbVar8[0xc];
  if (((unsigned long long)(uStack_2c)>>16 & 0xffULL) == *(char *)(param_1 + 0xda)) {
    if (*DAT_00015b90 < 1) {
      return 0;
    }
    iVar7 = *DAT_00015b94;
    format_string = PTR_s__s____slave_recv_same_package_00015b9c;
    goto LAB_000159b4;
  }
  if ((((unsigned long long)(uStack_2c)>>16 & 0xffULL) != (char)(*(char *)(param_1 + 0xda) + '\x01')) && (0 < *DAT_00015b90)) {
    if (*DAT_00015b94 == 0) {
      DEBUG_PRINT(PTR_s__s___________________loss_packag_00015ba0,DAT_00015b98);
    }
    else {
      debug_print(PTR_s__s___________________loss_packag_00015ba0,DAT_00015b98);
    }
  }
  if ((local_30 & 0x3f) == 1) {
    if (*(char *)(param_1 + 0xfe6) == '\x01') {
      *(char *)(param_1 + 0xda) = *(char *)(param_1 + 0xda) + '\x01';
      if (*DAT_00015b90 < 1) {
        return 0;
      }
      iVar7 = *DAT_00015b94;
      format_string = PTR_s__s____slave_recv_suspend_package_00015ba4;
      goto LAB_000159b4;
    }
  }
  else if (((local_30 & 0x3f) == 2) && (*(char *)(param_1 + 0xfe6) == '\0')) {
    *(char *)(param_1 + 0xda) = *(char *)(param_1 + 0xda) + '\x01';
    if (*DAT_00015b90 < 1) {
      return 0;
    }
    iVar7 = *DAT_00015b94;
    format_string = PTR_s__s____slave_recv_resume_package_00015ba8;
    goto LAB_000159b4;
  }
  if (((*(char *)(param_1 + 0xd5) == '\t') || (*(char *)(param_1 + 0xd5) == '\v')) ||
     (*(char *)(param_1 + 0xd5) == '\n')) {
    if ((local_30 & 0xc0) == 0x80) {
      if (*(char *)(param_1 + 0xce) != '\0') {
        *(char *)(param_1 + 0xda) = *(char *)(param_1 + 0xda) + '\x01';
        if (*DAT_00015b90 < 1) {
          return 0;
        }
        iVar7 = *DAT_00015b94;
        format_string = PTR_s__s____slave_recv_up_recving_00015bac;
        goto LAB_000159b4;
      }
    }
    else if (((local_30 & 0xc0) == 0x40) && (*(char *)(param_1 + 0xcf) != '\0')) {
      *(char *)(param_1 + 0xda) = *(char *)(param_1 + 0xda) + '\x01';
      if (*DAT_00015b90 < 1) {
        return 0;
      }
      iVar7 = *DAT_00015b94;
      format_string = PTR_s__s____slave_recv_down_recving_00015bb0;
      goto LAB_000159b4;
    }
  }
  else if ((*(char *)(param_1 + 0xd5) == '\x10') && (*(char *)(param_1 + 0xce) != '\0')) {
    if (0 < *DAT_00015b90) {
      if (*DAT_00015b94 == 0) {
        DEBUG_PRINT(PTR_s__s____slave_even_ai_recv_down_re_00015bb4,DAT_00015b98);
      }
      else {
        debug_print();
      }
    }
    *(char *)(param_1 + 0xda) = *(char *)(param_1 + 0xda) + '\x01';
    return 0;
  }
  if ((((unsigned long long)(local_30)>>8 & 0xffULL) != '\x06') && (((unsigned long long)(local_30)>>8 & 0xffULL) != '\0')) {
    *(byte *)(param_1 + 0xe9) = param_2[3];
    bVar1 = param_2[4];
    *(byte *)(param_1 + 0xea) = bVar1;
    if ((local_30 & 0x3f) == 0) {
      if (((local_30 & 0xc0) == 0x80) ||
         ((((unsigned long long)(local_30)>>8 & 0xffULL) == '\x10' && (**(byte **)(*DAT_00015bb8 + 0x100c) - 6 < 4)))) {
        if ((*(byte *)(param_1 + 0xcc) != param_2[3]) &&
           (*(byte *)(*(int *)(param_1 + 0x1024) + 0x200) != param_2[3])) {
          *(char *)(param_1 + 0xda) = *(char *)(param_1 + 0xda) + '\x01';
          if (*DAT_00015b90 < 1) {
            return 0;
          }
          iVar7 = *DAT_00015b94;
          format_string = DAT_00015bbc;
          goto LAB_000159b4;
        }
      }
      else if ((*(byte *)(param_1 + 0xcd) != bVar1) &&
              (*(byte *)(*(int *)(param_1 + 0x1028) + 0x200) != bVar1)) {
        *(char *)(param_1 + 0xda) = *(char *)(param_1 + 0xda) + '\x01';
        if (*DAT_00015b90 < 1) {
          return 0;
        }
        iVar7 = *DAT_00015b94;
        format_string = DAT_00015bc0;
LAB_000159b4:
        if (iVar7 != 0) {
          debug_print();
          return 0;
        }
        DEBUG_PRINT(format_string,DAT_00015b98);
        return 0;
      }
    }
  }
  *(byte *)(param_1 + 0xc9) = *(byte *)(param_1 + 0xc9) & 0xc0 | *param_2 & 0x3f;
  *(byte *)(param_1 + 0xca) = param_2[1];
  *(byte *)(param_1 + 0xcb) = param_2[2];
  set_device_sync_timestamp(*(undefined4 *)(param_2 + 7));
  uVar4 = *(undefined1 *)(param_1 + 0xd5);
  local_30 = (local_30 & ~(0xffffL /*=0xffff*/<<0)) | (((unsigned long long)(CONCAT11(uVar4,(byte)local_30)) & 0xffffL /*=0xffff*/)<<0);
  puVar2 = (undefined4 *)(param_1 + 0xd4);
  pbVar6 = (byte *)&local_30;
  do {
    pbVar8 = pbVar6;
    puVar5 = puVar2;
    uVar3 = *(undefined4 *)(pbVar8 + 4);
    pbVar6 = pbVar8 + 8;
    *puVar5 = *(undefined4 *)pbVar8;
    puVar5[1] = uVar3;
    puVar2 = puVar5 + 2;
  } while (pbVar6 != &local_20);
  puVar5[2] = *(undefined4 *)pbVar6;
  *(byte *)(puVar5 + 3) = pbVar8[0xc];
  *(byte *)(param_1 + 0xee4) = (byte)local_30 >> 6;
  **(undefined4 **)(param_1 + 0xfec) = *(undefined4 *)(param_2 + 7);
  if (*(int *)(*(int *)(param_1 + 0xff4) + 0x164) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xff4) + 0x164) = **(undefined4 **)(param_1 + 0xfec);
  }
  *(byte *)(param_1 + 0xeb) = (byte)local_30 >> 6;
  *(undefined1 *)(param_1 + 0xec) = uVar4;
  if ((int)((uint)local_20 << 0x1d) < 0) {
    msg_queue_init();
    *(byte *)(param_1 + 0xe4) = *(byte *)(param_1 + 0xe4) & 0xfb;
  }
  switch(local_30 & 0x3f) {
  case 10:
    if ((int)((uint)*(byte *)(*(int *)PTR_DAT_00015dd8 + 0x6de) << 0x1d) < 0) {
      return 0;
    }
    iVar7 = find_message_pool_entry_by_id(local_1f);
    if (0 < *(int *)PTR_DAT_00015ddc) {
      if (*(int *)PTR_IS_DEBUG_00015de0 == 0) {
        DEBUG_PRINT(DAT_00015de8,DAT_00015de4,DAT_00015de4,0x2fd);
      }
      else {
        debug_print(DAT_00015de8,DAT_00015de4,DAT_00015de4,0x2fd);
      }
    }
    if ((iVar7 != 0) && (*(char *)(iVar7 + 0xd) == '\0')) {
      *(undefined1 *)(iVar7 + 0xd) = 2;
    }
    goto switchD_00015c70_caseD_c;
  case 0xb:
    if ((int)((uint)*(byte *)(*(int *)PTR_DAT_00015dd8 + 0x6de) << 0x1d) < 0) {
      return 0;
    }
    iVar7 = find_message_pool_entry_by_id(local_1f);
    if (0 < *(int *)PTR_DAT_00015ddc) {
      if (*(int *)PTR_IS_DEBUG_00015de0 == 0) {
        DEBUG_PRINT(DAT_00015dec,DAT_00015de4,DAT_00015de4,0x30a);
      }
      else {
        debug_print(DAT_00015dec,DAT_00015de4,DAT_00015de4,0x30a);
      }
    }
    if ((iVar7 == 0) || (*(char *)(iVar7 + 0xd) != '\x02')) goto switchD_00015c70_caseD_c;
    *(undefined1 *)(iVar7 + 0xd) = 4;
    confirm_message(local_1f);
    uVar4 = 0;
    puVar9 = DAT_00015df0;
    break;
  case 0xc:
    goto switchD_00015c70_caseD_c;
  case 0xd:
    reset_esb_sync_state(0);
    iVar7 = *(int *)PTR_DAT_00015dd8;
    **(undefined1 **)(iVar7 + 0x100c) = 2;
    if (**(int **)(iVar7 + 0x1054) != 0x10) {
      update_persist_task_status(iVar7,0x10);
    }
    goto switchD_00015c70_caseD_c;
  case 0xe:
    uVar4 = 4;
    puVar9 = *(undefined1 **)(*(int *)PTR_DAT_00015dd8 + 0x100c);
    break;
  case 0xf:
    uVar4 = 6;
    puVar9 = *(undefined1 **)(*(int *)PTR_DAT_00015dd8 + 0x100c);
    break;
  case 0x10:
    iVar7 = *(int *)PTR_DAT_00015dd8;
    **(undefined1 **)(iVar7 + 0x100c) = 0xb;
    *(undefined1 *)(iVar7 + 0xdb) = 8;
    goto switchD_00015c70_caseD_c;
  case 0x11:
    uVar4 = 0xe;
    puVar9 = *(undefined1 **)(*(int *)PTR_DAT_00015dd8 + 0x100c);
    break;
  case 0x12:
    uVar4 = 0x10;
    puVar9 = *(undefined1 **)(*(int *)PTR_DAT_00015dd8 + 0x100c);
    break;
  default:
    thunk_FUN_00072880(param_1 + 0x20);
    goto switchD_00015c70_caseD_c;
  }
  *puVar9 = uVar4;
switchD_00015c70_caseD_c:
  if ((((*(byte *)(param_1 + 0xc9) & 0x3f) == 3) && ((*(byte *)(param_1 + 0xc9) & 0xc0) == 0x80)) &&
     (*(char *)(param_1 + 0xca) == '\x01')) {
    switch_to_dfu_mode(param_1 + 0x68);
  }
  return 0;
}


