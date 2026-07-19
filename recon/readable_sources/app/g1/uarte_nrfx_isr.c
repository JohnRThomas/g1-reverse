#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_uarte_driver_ctx__param_0314           [param_0314; G1-original]
 *   local_2c         => struct g1_layout_uarte_isr_scratch__stack_1278          [stack_1278; G1-original]
 * Raw function identity: 0x0006312c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0006312c @ 0x0006312c
 * public-name: uarte_nrfx_isr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   uarte_nrfx_isr                           <= FUN_0006312c @ 0x0006312c
 *   z_impl_k_timer_start                     <= FUN_00075174 @ 0x00075174
 *   transport_notify_callback                <= FUN_00084840 @ 0x00084840
 *   post_event_tag2_from_node                <= FUN_0008484e @ 0x0008484e
 *   post_event_tag4_and_clear                <= FUN_00084880 @ 0x00084880
 *   post_event_tag5                          <= FUN_000848b0 @ 0x000848b0
 *   nvs_timer_arm_and_mark_dirty             <= FUN_000849da @ 0x000849da
 *   ringbuf_flush_chunk                      <= FUN_00084a24 @ 0x00084a24
 *   uarte_blocking_transfer                  <= FUN_00084a54 @ 0x00084a54
 *   uarte_nrfx_tx_complete                   <= FUN_00084ade @ 0x00084ade
 *   flowctl_release_credit_and_kick          <= FUN_00084b32 @ 0x00084b32
 *   z_impl_k_timer_stop                      <= FUN_0008673e @ 0x0008673e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_f4240                             @ 0x000f4240
 */
/* Reconstructed FUN_0006312c @ 0x6312c  (parity: 150/150 trials, PROVEN) */
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
typedef unsigned char undefined,undefined1,byte,uchar,uint1;
typedef unsigned short undefined2,ushort,uint2,wchar_t;
typedef unsigned int undefined4,uint,uint3,code_t;
typedef unsigned long long undefined8,ulonglong;
typedef long long longlong; typedef unsigned long ulong; typedef signed char sbyte;
typedef long long(*code)();
#define bool int
#define false 0
#define true 1
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

extern uint64_t __aeabi_uldivmod(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint64_t z_impl_k_timer_start(uint32_t, uint32_t, uint32_t, uint32_t, uint64_t);
extern uint64_t transport_notify_callback(uint32_t, const void *);
extern uint64_t post_event_tag2_from_node(uint32_t);
extern uint64_t post_event_tag4_and_clear(uint32_t, uint32_t);
extern uint64_t post_event_tag5(uint32_t);
extern uint64_t nvs_timer_arm_and_mark_dirty(uint32_t);
extern int32_t ringbuf_flush_chunk(uint32_t);
extern uint64_t uarte_blocking_transfer(uint32_t, uint32_t, uint32_t);
extern uint64_t uarte_nrfx_tx_complete(uint32_t, uint32_t);
extern uint64_t flowctl_release_credit_and_kick(uint32_t, uint32_t);
extern uint64_t z_impl_k_timer_stop(uint32_t);
extern uint64_t memset_bytes(void *, uint32_t, uint32_t, ...);
#define firmware_data_00063494 0xf423fUL
#define firmware_data_00063498 ((unsigned long)&rodata_f4240) /*=0xf4240*/


void uarte_nrfx_isr(int param_1)

{
  longlong lVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  byte bVar7;
  int iVar8;
  undefined4 *puVar9;
  bool bVar10;
  undefined8 uVar11;
  undefined1 local_2c [4];
  undefined4 local_28;
  int iStack_24;

  iVar6 = **(int **)(param_1 + 4);
  iVar4 = *(int *)(param_1 + 0x10);
  if (*(int *)(iVar6 + 0x108) != 0) {
    *(undefined4 *)(iVar6 + 0x108) = 0;
    iVar4 = *(int *)(iVar4 + 0xc);
    *(int *)(iVar4 + 0xb8) = *(int *)(iVar4 + 0xb8) + 1;
    return;
  }
  if (*(int *)(iVar6 + 0x124) != 0) {
    *(undefined4 *)(iVar6 + 0x124) = 0;
    iVar4 = *(int *)(**(int **)(param_1 + 4) + 0x480);
    *(int *)(**(int **)(param_1 + 4) + 0x480) = iVar4;
    memset_bytes(local_2c,0,0x14);
    local_2c[0] = 6;
    if (iVar4 << 0x1f < 0) {
      bVar7 = 1;
    }
    else if (iVar4 << 0x1e < 0) {
      bVar7 = 2;
    }
    else if (iVar4 << 0x1d < 0) {
      bVar7 = 4;
    }
    else {
      bVar7 = (byte)iVar4 & 8;
    }
    local_28 = CONCAT31(((unsigned long long)(local_28)>>8 & 0xffffffULL),bVar7);
    transport_notify_callback(param_1,local_2c);
    nvs_timer_arm_and_mark_dirty(param_1);
  }
  if ((*(int *)(iVar6 + 0x110) != 0) && (*(int *)(iVar6 + 0x304) << 0x1b < 0)) {
    *(undefined4 *)(iVar6 + 0x110) = 0;
    iVar8 = *(int *)(param_1 + 0x10);
    puVar9 = (undefined4 *)**(undefined4 **)(param_1 + 4);
    *(undefined1 *)(*(int *)(iVar8 + 0xc) + 0xce) = 1;
    z_impl_k_timer_stop(*(int *)(iVar8 + 0xc) + 0x80);
    iVar4 = puVar9[0x14f];
    bVar7 = *(byte *)(*(int *)(iVar8 + 0xc) + 0xc9);
    *(undefined1 *)(*(int *)(iVar8 + 0xc) + 0xc9) = 0;
    iVar2 = *(int *)(iVar8 + 0xc);
    uVar5 = ((uint)bVar7 - *(int *)(iVar2 + 0x60)) + iVar4;
    *(uint *)(iVar2 + 0x70) = *(int *)(iVar2 + 0x70) + (uVar5 & ~((int)uVar5 >> 0x1f));
    if (0 < (int)uVar5) {
      post_event_tag2_from_node(param_1);
    }
    iVar4 = *(int *)(iVar8 + 0xc);
    if (*(char *)(iVar4 + 0xca) == '\0') {
      *(undefined1 *)(iVar4 + 0xce) = 0;
    }
    else {
      post_event_tag4_and_clear(param_1,iVar4 + 0x58);
      uVar3 = 0;
      bVar10 = (bool)isCurrentModePrivileged();
      if (bVar10) {
        uVar3 = getBasePriority();
      }
      bVar10 = (bool)isCurrentModePrivileged();
      if ((bVar10) && (uVar5 = getBasePriority(), uVar5 == 0 || 0x20 < uVar5)) {
        setBasePriority(0x20);
      }
      InstructionSynchronizationBarrier(0xf);
      iVar4 = *(int *)(*(int *)(iVar8 + 0xc) + 100);
      if (iVar4 == 0) {
        puVar9[1] = 1;
      }
      else {
        *(int *)(*(int *)(iVar8 + 0xc) + 0x58) = iVar4;
        *(undefined4 *)(*(int *)(iVar8 + 0xc) + 0x5c) =
             *(undefined4 *)(*(int *)(iVar8 + 0xc) + 0x68);
        *(undefined4 *)(*(int *)(iVar8 + 0xc) + 100) = 0;
        *(undefined4 *)(*(int *)(iVar8 + 0xc) + 0x68) = 0;
        *(undefined4 *)(*(int *)(iVar8 + 0xc) + 0x60) = 0;
        if (puVar9[0x53] == 0) {
          *puVar9 = 1;
        }
        puVar9[0x80] = puVar9[0x80] & 0xffffffdf;
      }
      bVar10 = (bool)isCurrentModePrivileged();
      if (bVar10) {
        setBasePriority(uVar3);
      }
      InstructionSynchronizationBarrier(0xf);
      *(undefined1 *)(*(int *)(iVar8 + 0xc) + 0xce) = 0;
    }
  }
  if ((*(int *)(iVar6 + 0x14c) != 0) && (*(int *)(iVar6 + 0x110) == 0)) {
    *(undefined4 *)(iVar6 + 0x14c) = 0;
    iVar8 = *(int *)(param_1 + 0x10);
    memset_bytes(local_2c,0,0x14,*(undefined4 *)(iVar6 + 0x14c));
    local_2c[0] = 3;
    transport_notify_callback(param_1,local_2c);
    iVar2 = *(int *)(iVar8 + 0xc);
    iVar4 = *(int *)(iVar2 + 0x74);
    if (iVar4 != -1) {
      *(int *)(iVar2 + 0x7c) = iVar4;
      iVar4 = *(int *)(iVar8 + 0xc);
      uVar5 = *(uint *)(iVar4 + 0x78);
      lVar1 = (longlong)(int)(uVar5 & ~((int)uVar5 >> 0x1f)) * 0x8000 + (ulonglong)firmware_data_00063494;
      uVar11 = __aeabi_uldivmod((int)lVar1,(int)((ulonglong)lVar1 >> 0x20),firmware_data_00063498,0);
      uVar3 = (undefined4)((ulonglong)uVar11 >> 0x20);
      z_impl_k_timer_start(iVar4 + 0x80,uVar3,(int)uVar11,uVar3,uVar11);
    }
  }
  if ((*(int *)(iVar6 + 0x144) != 0) && (*(int *)(iVar6 + 0x110) == 0)) {
    *(undefined4 *)(iVar6 + 0x144) = 0;
    iVar4 = *(int *)(param_1 + 0x10);
    iVar2 = *(int *)(param_1 + 4);
    post_event_tag4_and_clear(param_1,*(int *)(iVar4 + 0xc) + 0x58);
    post_event_tag4_and_clear(param_1,*(int *)(iVar4 + 0xc) + 100);
    *(undefined1 *)(*(int *)(iVar4 + 0xc) + 0xca) = 0;
    if (*(char *)(*(int *)(iVar4 + 0xc) + 0xcb) != '\0') {
      *(undefined1 *)(*(int *)(iVar4 + 0xc) + 0xcb) = 0;
      uarte_blocking_transfer(*(undefined4 *)(param_1 + 4),0,0);
    }
    if (*(int *)(iVar2 + 4) << 0x1b < 0) {
      flowctl_release_credit_and_kick(param_1,2);
    }
    post_event_tag5(param_1);
  }
  if ((*(int *)(iVar6 + 0x120) != 0) && (*(int *)(iVar6 + 0x304) << 0x17 < 0)) {
    iVar4 = **(int **)(param_1 + 4);
    uVar3 = 0;
    bVar10 = (bool)isCurrentModePrivileged();
    if (bVar10) {
      uVar3 = getBasePriority();
    }
    bVar10 = (bool)isCurrentModePrivileged();
    if ((bVar10) && (uVar5 = getBasePriority(), uVar5 == 0 || 0x20 < uVar5)) {
      setBasePriority(0x20);
    }
    InstructionSynchronizationBarrier(0xf);
    if (*(int *)(iVar4 + 0x120) != 0) {
      *(undefined4 *)(iVar4 + 0x120) = 0;
      *(undefined4 *)(iVar4 + 0xc) = 1;
    }
    bVar10 = (bool)isCurrentModePrivileged();
    if (bVar10) {
      setBasePriority(uVar3);
    }
    InstructionSynchronizationBarrier(0xf);
  }
  if (*(int *)(iVar6 + 0x158) == 0) {
    return;
  }
  if (-1 < *(int *)(iVar6 + 0x304) << 9) {
    return;
  }
  iVar4 = *(int *)(param_1 + 0x10);
  iVar6 = **(int **)(param_1 + 4);
  if ((*(int **)(param_1 + 4))[1] << 0x1b < 0) {
    *(undefined4 *)(iVar6 + 0x308) = 0x400000;
    flowctl_release_credit_and_kick(param_1,1);
    if (*(int *)(*(int *)(iVar4 + 0xc) + 0xc) == 0) {
      return;
    }
  }
  if (*(int *)(*(int *)(iVar4 + 0xc) + 8) == 0) {
    return;
  }
  uVar3 = 0;
  bVar10 = (bool)isCurrentModePrivileged();
  if (bVar10) {
    uVar3 = getBasePriority();
  }
  bVar10 = (bool)isCurrentModePrivileged();
  if ((bVar10) && (uVar5 = getBasePriority(), uVar5 == 0 || 0x20 < uVar5)) {
    setBasePriority(0x20);
  }
  InstructionSynchronizationBarrier(0xf);
  if (*(int *)(*(int *)(iVar4 + 0xc) + 0xbc) < 0) {
    iStack_24 = *(int *)(iVar6 + 0x54c);
  }
  else {
    iStack_24 = *(int *)(*(int *)(iVar4 + 0xc) + 0xbc);
  }
  bVar10 = (bool)isCurrentModePrivileged();
  if (bVar10) {
    setBasePriority(uVar3);
  }
  InstructionSynchronizationBarrier(0xf);
  iVar2 = *(int *)(iVar4 + 0xc);
  if (*(char *)(iVar2 + 0xcd) == '\0') {
    if ((*(int *)(iVar2 + 8) != *(int *)(iVar2 + 0x10)) &&
       (bVar10 = *(int *)(iVar2 + 0x14) == iStack_24, iStack_24 = *(int *)(iVar2 + 0x1c) + iStack_24
       , bVar10)) {
      *(int *)(iVar2 + 0x1c) = iStack_24;
      iVar2 = ringbuf_flush_chunk(iVar4);
      if (iVar2 != 0) goto control_label_00063380;
      iStack_24 = *(int *)(*(int *)(iVar4 + 0xc) + 0x1c);
    }
    z_impl_k_timer_stop(*(int *)(iVar4 + 0xc) + 0x20);
    memset_bytes(local_2c,0,0x14);
    local_28 = *(undefined4 *)(*(int *)(iVar4 + 0xc) + 8);
    if (iStack_24 != *(int *)(*(int *)(iVar4 + 0xc) + 0xc)) {
      local_2c[0] = 1;
    }
    *(undefined4 *)(iVar6 + 0x308) = 0x400000;
    *(undefined4 *)(*(int *)(iVar4 + 0xc) + 8) = 0;
    *(undefined4 *)(*(int *)(iVar4 + 0xc) + 0xc) = 0;
    transport_notify_callback(param_1,local_2c);
  }
  else {
control_label_00063380:
    uVar3 = 0;
    bVar10 = (bool)isCurrentModePrivileged();
    if (bVar10) {
      uVar3 = getBasePriority();
    }
    bVar10 = (bool)isCurrentModePrivileged();
    if ((bVar10) && (uVar5 = getBasePriority(), uVar5 == 0 || 0x20 < uVar5)) {
      setBasePriority(0x20);
    }
    InstructionSynchronizationBarrier(0xf);
    uarte_nrfx_tx_complete(param_1,iVar4);
    bVar10 = (bool)isCurrentModePrivileged();
    if (bVar10) {
      setBasePriority(uVar3);
    }
    InstructionSynchronizationBarrier(0xf);
  }
  return;
}
