#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005d5c0 @ 0x0005d5c0
 * public-name: FUN_0005d5c0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_rand                                  <= FUN_00055cb4 @ 0x00055cb4
 *   smp_auth_get_pairing_method              <= FUN_0005caec @ 0x0005caec
 *   smp_init                                 <= FUN_0005cc30 @ 0x0005cc30
 *   bt_keys_get_addr                         <= FUN_0005e6a8 @ 0x0005e6a8
 *   bt_keys_find_addr                        <= FUN_0005e938 @ 0x0005e938
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 *   send_pairing_rsp                         <= FUN_000830ee @ 0x000830ee
 * address symbols (name @ address):
 *   rodata_88180                             @ 0x00088180
 *   rodata_f4240                             @ 0x000f4240
 *   rodata_f4e7a                             @ 0x000f4e7a
 *   rodata_f4f5c                             @ 0x000f4f5c
 *   rodata_f5248                             @ 0x000f5248
 *   g_smp_pair_method_unbonded               @ 0x2001d533
 *   g_smp_pair_method_bonded                 @ 0x2001d534
 */
/* Full reconstruction of FUN_0005d5c0 @ 0x5d5c0, exact extent 930 bytes. */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned char undefined1;
typedef unsigned int undefined4;

extern int bt_rand(void*,int);
extern int FUN_0005cac0(void);
extern int smp_auth_get_pairing_method(int);
extern uint32_t smp_init(int);
extern int FUN_0005d568(int,uint);
extern int bt_keys_get_addr(uint8_t,int);
extern int bt_keys_find_addr(uint8_t,int);
/* The concrete helper leaves a decision byte in r1 on the feature-test path.
 * Model r1:r0 so the otherwise caller-clobbered value is represented in C. */
extern uint64_t atomic_test_bit(int,int);
extern int FUN_00083002(int,int);
extern int FUN_00083074(uint32_t,uint32_t,void*);
extern int atomic_set_bit(int,int);
extern uint32_t send_pairing_rsp(void);

uint FUN_0005d5c0(int param_1, int param_2)
{
  int iVar12 = *(volatile int*)(param_1 + 0xf0);
  int iVar3 = FUN_0005cac0();
  byte *pbVar13 = *(volatile byte**)(param_2 + 0xc);

  if ((uint8_t)(pbVar13[3] - 7) > 9) return 6;

  if (*(volatile int*)(iVar12 + 0xc0) == 0) {
    int iVar4 = bt_keys_get_addr(*(volatile uint8_t*)(iVar12 + 8), iVar12 + 0x90);
    *(volatile int*)(iVar12 + 0xc0) = iVar4;
    if (iVar4 == 0) return 8;
  }

  int iVar11 = param_1 + 4;
  int iVar4 = (int)(uint32_t)atomic_test_bit(iVar11, 0xf);
  if (iVar4 == 0) {
    uint32_t uVar5 = smp_init(param_1);
    if (uVar5 != 0) return uVar5 & 0xff;
  }

  *(volatile uint8_t*)(param_1 + 9) = 1;
  *(volatile uint32_t*)(param_1 + 10) = *(volatile uint32_t*)pbVar13;
  *(volatile uint16_t*)(param_1 + 0xe) = *(volatile uint16_t*)(pbVar13 + 4);
  *(volatile uint8_t*)(param_1 + 0x10) = 2;
  uint8_t uVar2 = FUN_0005d568(param_1, pbVar13[2]);
  *(volatile uint8_t*)(param_1 + 0x13) = uVar2;
  uVar2 = smp_auth_get_pairing_method(param_1);
  *(volatile uint8_t*)(param_1 + 0x11) = uVar2;
  *(volatile uint8_t*)(param_1 + 0x14) = 0x10;
  *(volatile uint8_t*)(param_1 + 0x15) = pbVar13[4] & 3;
  *(volatile uint8_t*)(param_1 + 0x16) = pbVar13[5] & 1;

  if ((*(volatile uint8_t*)(param_1 + 0x13) & 8) != 0 && (pbVar13[2] & 8) != 0) {
    atomic_set_bit(iVar11, 5);
    *(volatile uint8_t*)(param_1 + 0x15) = *(volatile uint8_t*)(param_1 + 0x15) & 2;
    *(volatile uint8_t*)(param_1 + 0x16) = 0;
  }

  iVar4 = (int)(uint32_t)atomic_test_bit(iVar11, 5);
  uint8_t puVar9val;
  if (iVar4 != 0) {
    puVar9val = *(volatile uint8_t*)((unsigned long)&g_smp_pair_method_bonded) /*=0x2001d534*/;
  } else {
    puVar9val = *(volatile uint8_t*)((unsigned long)&g_smp_pair_method_unbonded) /*=0x2001d533*/;
  }
  *(volatile uint8_t*)(param_1 + 0x12) = puVar9val;

  if ((*(volatile uint8_t*)(param_1 + 0x13) & 0x20) != 0 &&
      (pbVar13[2] & 0x20) != 0) {
    atomic_set_bit(iVar11, 0x14);
  }

  if ( ((int32_t)((uint32_t)*(volatile uint8_t*)(param_1 + 0x13) << 0x1f)) < 0 &&
       ((int32_t)((uint32_t)pbVar13[2] << 0x1f)) < 0 ) {
    atomic_set_bit(iVar11, 0xd);
  } else {
    *(volatile uint8_t*)(param_1 + 0x15) = 0;
    *(volatile uint8_t*)(param_1 + 0x16) = 0;
  }

  *(volatile uint8_t*)(param_1 + 0xe8) = *(volatile uint8_t*)(param_1 + 0x16);
  *(volatile uint8_t*)(param_1 + 0xe9) = *(volatile uint8_t*)(param_1 + 0x15);
  int uVar6 = atomic_set_bit(iVar11, 3);
  uint uVar5b = *pbVar13;
  uint64_t feature_result = atomic_test_bit(uVar6, 5);
  iVar4 = (int)(uint32_t)feature_result;
  uint8_t bVar8;
  if (iVar4 == 0) {
    if (uVar5b < 5) {
      if ((int32_t)((uint32_t)(*(volatile uint8_t*)(param_1+0xb) & *(volatile uint8_t*)(param_1+0x12)) << 0x1f) < 0) {
        bVar8 = 6;
      } else {
        uint8_t bVar1 = *(volatile uint8_t*)(param_1+0xc) | *(volatile uint8_t*)(param_1+0x13);
        bVar8 = bVar1 & 4;
        if ((bVar1 & 4) != 0) {
          int iv = smp_auth_get_pairing_method(param_1);
          bVar8 = *(volatile uint8_t*)(uVar5b*5 + ((unsigned long)&rodata_f5248) /*=0xf5248*/ + iv);
          if (bVar8 == 4) {
            if (*(volatile int8_t*)(*(volatile int*)(param_1+0xf0) + 3) == 0) bVar8 = 2;
            else bVar8 = 1;
          }
        }
      }
    } else {
      bVar8 = 0;
    }
  } else if ( ((int32_t)((uint32_t)(*(volatile uint8_t*)(param_1+0xc) & *(volatile uint8_t*)(param_1+0x13)) << 0x1c)) >= 0 ||
              ((int32_t)((uint32_t)(*(volatile uint8_t*)(param_1+0xb) | *(volatile uint8_t*)(param_1+0x12)) << 0x1f)) >= 0 ) {
    if (uVar5b > 4) { bVar8 = 0; }
    else {
      uint8_t bVar1 = *(volatile uint8_t*)(param_1+0xc) | *(volatile uint8_t*)(param_1+0x13);
      bVar8 = bVar1 & 4;
      if ((bVar1 & 4) != 0) {
        int iv = smp_auth_get_pairing_method(param_1);
        bVar8 = *(volatile uint8_t*)(0x000f522fUL + uVar5b*5 + iv);
      }
    }
  } else {
    bVar8 = (uint8_t)(feature_result >> 32);
  }
  *(volatile uint8_t*)(param_1 + 8) = bVar8;

  iVar4 = FUN_00083002(param_1, *(volatile int*)(iVar12 + 0xc0));
  if (iVar4 == 0) return 3;

  uint uVar5c = *(volatile uint8_t*)(*(volatile int*)(param_1+0xf0) + 10);
  if (uVar5c != 3) {
    if (uVar5c > 3) {
      if (uVar5c != 4) return 8;
      uint8_t b1 = *(volatile uint8_t*)(param_1+0x14);
      uint8_t b2 = *(volatile uint8_t*)(param_1+0xd);
      uint8_t bb = (b1 >= b2) ? b2 : b1;
      if (bb != 0x10) return 6;
      iVar4 = (int)(uint32_t)atomic_test_bit(iVar11, 5);
      if (iVar4 == 0) return 3;
      goto LAB_d80e;
    }
    if ((uVar5c - 1) > 1) return 8;
  } else {
LAB_d80e:
    if (*(volatile int8_t*)(param_1 + 8) == 0) return 3;
  }

  iVar4 = (int)(uint32_t)atomic_test_bit(iVar11, 5);
  if (iVar4 != 0) {
    if ( (*(volatile int8_t*)(param_1+8) == 0) &&
         ((uint32_t)atomic_test_bit(iVar11,0xf) == 0) &&
         (iVar3 != 0) && (*(volatile int*)(iVar3+0x14) != 0) ) {
      atomic_set_bit(iVar11, 10);
      int (*pcVar10)(int) = *(volatile void* volatile*)(iVar3+0x14);
      int iv2 = *(volatile int*)(param_1+0xf0);
      pcVar10(iv2);
      return 0;
    }
    int p1 = atomic_set_bit(param_1, 0xc);
    atomic_set_bit(p1, 0xe);
    uint r = send_pairing_rsp();
    return r;
  }

  iVar3 = FUN_0005cac0();
  int iVar4b = *(volatile int*)(param_1 + 0xf0);
  int *piVar7 = (int*)(intptr_t)FUN_0005cac0();
  int iVar12b = bt_keys_find_addr(*(volatile uint8_t*)(iVar4b + 8), iVar4b + 0x90);
  uint uStack_40 = *(volatile uint8_t*)(param_1 + 8);
  if (iVar12b != 0 && (int8_t)(*(volatile uint8_t*)(iVar12b+0xd)) < 0 && uStack_40 == 0) {
    struct { uint32_t a,b; } s = { 2, ((unsigned long)&rodata_f4f5c) /*=0xf4f5c*/ };
    FUN_00083074(((unsigned long)&rodata_88180) /*=0x88180*/, 0x1040, &s);
    return 8;
  }

  switch (uStack_40) {
    case 0: goto caseD0;
    case 1: {
      atomic_set_bit(iVar11, 10);
      int (*fp)(int) = (int(*)(int))(intptr_t)piVar7[1];
      fp(iVar4b);
      break;
    }
    case 2: {
      uint32_t local_38;
      int iv = bt_rand(&local_38, 4);
      if (iv != 0) return 8;
      local_38 = local_38 - ((unsigned long)&rodata_f4240) /*=0xf4240*/ * (local_38 / ((unsigned long)&rodata_f4240) /*=0xf4240*/);
      if (piVar7 != 0 && *piVar7 != 0) {
        atomic_set_bit(iVar11, 0xb);
        void (*fp)(int,uint32_t) = (void(*)(int,uint32_t))(intptr_t)*piVar7;
        fp(iVar4b, local_38);
      }
      *(volatile uint8_t*)(param_1 + 0x47) = (uint8_t)local_38;
      *(volatile uint8_t*)(param_1 + 0x49) = (uint8_t)(local_38 >> 0x10);
      *(volatile uint8_t*)(param_1 + 0x48) = (uint8_t)(local_38 >> 8);
      *(volatile uint8_t*)(param_1 + 0x4a) = (uint8_t)(local_38 >> 0x18);
      break;
    }
    case 6: {
      if (piVar7 == 0 || piVar7[3] == 0) return 2;
      union {
        uint32_t word;
        uint16_t half[2];
      } local_38;
      local_38.half[0] = 0;
      atomic_set_bit(iVar11, 10);
      void (*fp)(int,void*) = (void(*)(int,void*))(intptr_t)piVar7[3];
      fp(*(volatile int*)(param_1+0xf0), &local_38.word);
      break;
    }
    default: {
      struct { uint32_t a,b; } s = { 3, ((unsigned long)&rodata_f4e7a) /*=0xf4e7a*/ };
      FUN_00083074(((unsigned long)&rodata_88180) /*=0x88180*/, 0x1840, &s);
      return 8;
    }
  }

  if (*(volatile int8_t*)(param_1 + 8) == 0) {
caseD0:
    iVar12b = (int)(uint32_t)atomic_test_bit(iVar11, 0xf);
    if (iVar12b == 0 && iVar3 != 0 && *(volatile int*)(iVar3+0x14) != 0) {
      atomic_set_bit(iVar11, 10);
      int (*pcVar10)(int) = *(volatile void* volatile*)(iVar3+0x14);
      int iv2 = *(volatile int*)(param_1+0xf0);
      pcVar10(iv2);
      return 0;
    }
  }
  {
    int p1 = atomic_set_bit(param_1, 3);
    atomic_set_bit(p1, 0xe);
    uint r = send_pairing_rsp();
    return r;
  }
}
