/* Reconstructed main @ 0x16eb8  CFG_VERIFY_PREFIX_FIRST CFG_VERIFY_PREFIX_K=500 */
#include <stdint.h>
#pragma GCC diagnostic warning "-Wint-conversion"
#pragma GCC diagnostic warning "-Wimplicit-int"
#pragma GCC diagnostic warning "-Wimplicit-function-declaration"
#pragma GCC diagnostic warning "-Wint-to-pointer-cast"
#pragma GCC diagnostic warning "-Wpointer-to-int-cast"
#pragma GCC diagnostic warning "-Wincompatible-pointer-types"
#pragma GCC diagnostic warning "-Wdiscarded-qualifiers"
typedef uint8_t undefined1; typedef uint8_t byte; typedef uint8_t undefined; typedef uint8_t uchar;
typedef uint16_t undefined2; typedef uint16_t ushort; typedef uint16_t wchar_t;
typedef uint32_t undefined4; typedef uint32_t uint;
typedef long long code(int,...);
typedef uint64_t undefined8; typedef uint64_t ulonglong;
typedef int64_t longlong; typedef int32_t int32; typedef unsigned int uint3;

extern long long DEBUG_PRINT(int, ...);
extern long long FUN_000158bc(int, ...);
extern long long FUN_00015df4(int, ...);
extern long long FUN_00015f80(int, ...);
extern long long FUN_00016110(int, ...);
extern long long FUN_00016268(int, ...);
extern long long FUN_000167b4(int, ...);
extern long long FUN_00017a40(int, ...);
extern long long FUN_00018208(int, ...);
extern long long FUN_00019c70(int, ...);
extern long long FUN_00022518(int, ...);
extern long long FUN_00023230(int, ...);
extern long long FUN_00023acc(int, ...);
extern long long FUN_00023d0c(int, ...);
extern long long FUN_00023df4(int, ...);
extern long long FUN_000243fc(int, ...);
extern long long FUN_00025290(int, ...);
extern long long FUN_00025c54(int, ...);
extern long long FUN_00025d40(int, ...);
extern long long FUN_00026250(int, ...);
extern long long FUN_0002659c(int, ...);
extern long long FUN_0002a65c(int, ...);
extern long long FUN_0002e4e8(int, ...);
extern long long FUN_0002e8fc(int, ...);
extern long long FUN_0002ea28(int, ...);
extern long long FUN_0002ea78(int, ...);
extern long long FUN_0002eaa8(int, ...);
extern long long FUN_0002f080(int, ...);
extern long long FUN_00030c90(int, ...);
extern long long FUN_00032808(int, ...);
extern long long FUN_00034944(int, ...);
extern long long FUN_00036ed8(int, ...);
extern long long FUN_000406e4(int, ...);
extern long long FUN_00047148(int, ...);
extern long long FUN_0004a500(int, ...);
extern long long FUN_0004ab3c(int, ...);
extern long long FUN_0004f564(int, ...);
extern long long FUN_0004f770(int, ...);
extern long long FUN_000622a0(int, ...);
extern long long FUN_00062644(int, ...);
extern long long FUN_00072908(int, ...);
extern long long FUN_00075174(int, ...);
extern long long FUN_00076d6c(int, ...);
extern long long FUN_0007c030(int, ...);
extern long long FUN_0007c038(int, ...);
extern long long FUN_0007c34a(int, ...);
extern long long FUN_0007c360(int, ...);
extern long long FUN_0007cefc(int, ...);
extern long long FUN_0007d0aa(int, ...);
extern long long FUN_0007d230(int, ...);
extern long long FUN_0008638c(int, ...);
extern long long FUN_00086c78(int, ...);
extern long long change_work_mode_to(int, ...);

#define DAT_00017200 (0x000fa9b4UL)
#define DAT_00017204 (0x000faa2cUL)
#define DAT_00017208 ((volatile int*)0x2000230cUL)
#define DAT_0001720c ((volatile int*)0x20007554UL)
#define DAT_00017210 (0x00099830UL)
#define DAT_00017214 (0x00099bb2UL)
#define DAT_00017218 (0x00099835UL)
#define DAT_0001721c (0x20003700UL)
#define DAT_00017234 (0x65920080UL)
#define DAT_00017258 (0x0a090804UL)
#define DAT_0001725c ((volatile int*)0x200069f8UL)
#define DAT_00017260 ((volatile int*)0x200069fcUL)
#define DAT_0001750c ((volatile int*)0x20007554UL)
#define DAT_00017510 (0x00099b4cUL)
#define DAT_00017514 (0x00099942UL)
#define DAT_00017518 (0x00099bb2UL)
#define DAT_0001751c (0x0009985cUL)
#define DAT_00017520 (0x00099919UL)
#define DAT_00017524 (0x200036c8UL)
#define DAT_00017528 (0x00087d58UL)
#define DAT_0001752c (0x00099ba5UL)
#define DAT_00017530 (0x0009995cUL)
#define DAT_00017534 (0x00099b3dUL)
#define DAT_00017538 (0x00099969UL)
#define DAT_0001753c (0x00099976UL)
#define DAT_00017540 (0x0009999cUL)
#define DAT_00017544 (0x000999c2UL)
#define DAT_00017548 ((volatile undefined4*)0x00087cb0UL)
#define DAT_0001754c (0x000999e4UL)
#define DAT_00017550 ((volatile char*)0x2000ff6eUL)
#define DAT_00017554 (0x0009992eUL)
#define DAT_00017558 (0x000999ffUL)
#define DAT_0001755c (0x00087d70UL)
#define DAT_00017560 (0x00099a23UL)
#define DAT_00017564 (0x00099a3eUL)
#define DAT_00017568 (0x00099a60UL)
#define DAT_00017664 (0x00099a7fUL)
#define DAT_00017668 (0x00099a94UL)
#define DAT_0001766c (0x00099aa4UL)
#define DAT_00017670 ((volatile int*)0x20007554UL)
#define DAT_00017674 (0x00099b3dUL)
#define DAT_00017678 (0x00099acfUL)
#define DAT_0001767c (0x00099af4UL)
#define DAT_00017680 (0x00099b1eUL)
#define DAT_00017684 (0x2007fc00UL)
#define PTR_s_2024_12_28_20_20_45_00017220 (0x00099899UL)
#define PTR_s_1b85815_00017224 (0x000998adUL)
#define PTR_s__s_____Build_Info__Ver_v_d__d__d_00017228 (0x0009985cUL)
#define PTR_s_init_context_0001722c (0x00099ba5UL)
#define PTR_s__s_____cpuapp__global_context_in_00017230 (0x000998b5UL)
#define PTR_s_cpuapp_hw_id_00017238 (0x000998daUL)
#define PTR_LAB_000162ec_1_0001723c (0x000162edUL)
#define PTR_s_cpunet_esbm_cpu_sync_00017240 (0x000998e7UL)
#define PTR_LAB_00016bf0_1_00017244 (0x00016bf1UL)
#define PTR_s_cpunet_esbs_00017248 (0x000998fcUL)
#define PTR_FUN_00015960_1_0001724c (0x00015961UL)
#define PTR_s_cpunet_esbs_ctrl_00017250 (0x00099908UL)
#define PTR_LAB_0007c00c_1_00017254 (0x0007c00dUL)

void main(void)

{
  int *piVar1;
  int *piVar2;
  undefined *puVar3;
  char *pcVar4;
  char cVar5;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  undefined8 uVar64;
  undefined4 *puVar9;
  undefined1 *puVar10;
  undefined2 *puVar11;
  undefined4 extraout_r1 = 0;
  undefined4 extraout_r1_00 = 0;
  undefined4 extraout_r1_01 = 0;
  byte bVar12;
  uint uVar13;
  char *pcVar14;

  ((long long (*)(void))FUN_0004a500)();
  iVar6 = FUN_0004f564(0x10);
  if (iVar6 != 0) {
    *(volatile undefined4 *)(iVar6 + 4) = DAT_00017200;
  }
  piVar1 = DAT_00017208;
  *(volatile undefined4 *)(iVar6 + 8) = DAT_00017204;
  *(volatile undefined1 *)(iVar6 + 0xc) = 0;
  ((long long (*)(void))FUN_0004f770)();
  if (0 < *piVar1) {
    if (*DAT_0001720c == 0) {
      DEBUG_PRINT(DAT_00017218,DAT_00017214,DAT_00017210);
    }
    else {
      ((long long (*)(void))FUN_00019c70)();
    }
  }
  FUN_00075174(DAT_0001721c);
  ((long long (*)(void))FUN_00025c54)();
  piVar2 = DAT_0001720c;
  if (1 < *piVar1) {
    if (*DAT_0001720c == 0) {
      DEBUG_PRINT(DAT_0001751c,DAT_00017518,1,4,5,PTR_s_1b85815_00017224,
                  PTR_s_2024_12_28_20_20_45_00017220);
    }
    else {
      FUN_00019c70(PTR_s__s_____Build_Info__Ver_v_d__d__d_00017228,DAT_00017214);
    }
    if (1 < *piVar1) {
      if (*piVar2 == 0) {
        DEBUG_PRINT(PTR_s__s_____cpuapp__global_context_in_00017230,PTR_s_init_context_0001722c);
      }
      else {
        ((long long (*)(void))FUN_00019c70)();
      }
    }
  }
  pcVar7 = (char *)FUN_00076d6c(0x1188);
  FUN_00086c78(pcVar7,0,0x1188);
  piVar2 = DAT_00017260;
  *(volatile undefined4 *)(pcVar7 + 0xfda) = 0xffffffff;
  *(volatile undefined2 *)(pcVar7 + 0xfde) = 0xffff;
  *(volatile undefined4 *)(pcVar7 + 0xfe0) = 0xffffffff;
  *(volatile undefined2 *)(pcVar7 + 0xfe4) = 0xffff;
  *(volatile char *)pcVar7 = '\x01';
  *piVar2 = (int)pcVar7;
  FUN_0007c030(pcVar7 + 8,1);
  FUN_0007c030(pcVar7 + 0x20,10);
  FUN_0007c030(pcVar7 + 0x38,1);
  FUN_0007c030(pcVar7 + 0x50,1);
  pcVar14 = pcVar7 + 0x68;
  FUN_0007c030(pcVar7 + 0xaf4,1);
  FUN_0007c030(pcVar14,1);
  FUN_0007c030(pcVar7 + 0x80,1);
  FUN_0007c030(pcVar7 + 0x98,1);
  FUN_0007c030(pcVar7 + 0xb0,1);
  iVar6 = *piVar2;
  *(undefined1 *)(iVar6 + 1) = 0xff;
  *(undefined2 *)(iVar6 + 0x105c) = 0;
  change_work_mode_to(0);
  iVar6 = FUN_00076d6c(0x6a);
  *(int *)(pcVar7 + 0xfec) = iVar6;
  if (iVar6 != 0) {
    FUN_00086c78(iVar6,0,0x6a);
  }
  FUN_0007d230(DAT_00017234);
  uVar8 = FUN_00076d6c(7);
  *(undefined4 *)(pcVar7 + 0xff0) = uVar8;
  puVar9 = (undefined4 *)FUN_00076d6c(5);
  *(undefined4 **)(pcVar7 + 0x1054) = puVar9;
  if (puVar9 != (undefined4 *)0x0) {
    *puVar9 = 0;
    *(undefined1 *)(puVar9 + 1) = 0;
  }
  iVar6 = FUN_00076d6c(0x217);
  *(int *)(pcVar7 + 0xffc) = iVar6;
  if (iVar6 != 0) {
    FUN_00086c78(iVar6,0,0x217);
  }
  uVar8 = FUN_00076d6c(0xf5);
  *(undefined4 *)(pcVar7 + 0x1000) = uVar8;
  uVar8 = FUN_00076d6c(0x198);
  *(undefined4 *)(pcVar7 + 0x1004) = uVar8;
  uVar8 = FUN_00076d6c(0x198);
  *(undefined4 *)(pcVar7 + 0x1008) = uVar8;
  uVar8 = FUN_00076d6c(0x199);
  *(undefined4 *)(pcVar7 + 0x100c) = uVar8;
  iVar6 = FUN_00076d6c(0x50f);
  *(int *)(pcVar7 + 0x1020) = iVar6;
  if (iVar6 != 0) {
    FUN_00086c78(iVar6,0,0x50f);
  }
  iVar6 = FUN_00076d6c(0x201);
  *(int *)(pcVar7 + 0x1024) = iVar6;
  if (iVar6 != 0) {
    FUN_00086c78(iVar6,0,0x201);
  }
  iVar6 = FUN_00076d6c(0x201);
  *(int *)(pcVar7 + 0x1028) = iVar6;
  if (iVar6 != 0) {
    FUN_00086c78(iVar6,0,0x201);
  }
  iVar6 = FUN_00076d6c(0x16a);
  *(int *)(pcVar7 + 0xff4) = iVar6;
  if (iVar6 != 0) {
    *(undefined1 *)(iVar6 + 0x168) = 0;
    *(undefined4 *)(iVar6 + 0x164) = 0;
  }
  uVar8 = FUN_00076d6c(0xaf);
  *(undefined4 *)(pcVar7 + 0xff8) = uVar8;
  puVar9 = (undefined4 *)FUN_00076d6c(0xb);
  *(undefined4 **)(pcVar7 + 0x1010) = puVar9;
  if (puVar9 != (undefined4 *)0x0) {
    *puVar9 = 0;
    puVar9[1] = 0;
    *(undefined4 *)((int)puVar9 + 7) = 0;
  }
  uVar8 = FUN_00076d6c(0x21);
  *(undefined4 *)(pcVar7 + 0x1014) = uVar8;
  ((long long (*)(void))FUN_000406e4)();
  puVar10 = (undefined1 *)FUN_00076d6c(1);
  *(undefined1 **)(pcVar7 + 0x1018) = puVar10;
  if (puVar10 != (undefined1 *)0x0) {
    *puVar10 = 0;
  }
  puVar11 = (undefined2 *)FUN_00076d6c(2);
  *(undefined2 **)(pcVar7 + 0x101c) = puVar11;
  if (puVar11 != (undefined2 *)0x0) {
    *puVar11 = 0;
  }
  *(volatile undefined4 *)(pcVar7 + 0x1069) = 0xffffffff;
  *(volatile undefined4 *)(pcVar7 + 0x106c) = 0xffffffff;
  *(volatile undefined2 *)(pcVar7 + 0x1070) = 0;
  FUN_00025d40(pcVar7 + 0x714);
  puVar3 = (undefined *)PTR_s_cpuapp_hw_id_00017238;
  pcVar7[0x6e4] = '\x01';
  *(undefined **)(pcVar7 + 0x6e8) = puVar3;
  *(undefined **)(pcVar7 + 0x6ec) = (undefined *)PTR_LAB_000162ec_1_0001723c;
  (**(code **)(pcVar7 + 0x778))(pcVar7 + 0x6e4);
  pcVar7[0x6f0] = '\x06';
  *(undefined **)(pcVar7 + 0x6f4) = (undefined *)PTR_s_cpunet_esbm_cpu_sync_00017240;
  *(undefined **)(pcVar7 + 0x6f8) = (undefined *)PTR_LAB_00016bf0_1_00017244;
  pcVar7[0x6fc] = '\x04';
  *(undefined **)(pcVar7 + 0x700) = (undefined *)PTR_s_cpunet_esbs_00017248;
  *(undefined **)(pcVar7 + 0x704) = (undefined *)PTR_FUN_00015960_1_0001724c;
  pcVar7[0x708] = '\x05';
  *(undefined **)(pcVar7 + 0x70c) = (undefined *)PTR_s_cpunet_esbs_ctrl_00017250;
  *(undefined **)(pcVar7 + 0x710) = (undefined *)PTR_LAB_0007c00c_1_00017254;
  (**(code **)(pcVar7 + 0x778))(pcVar7 + 0x6f0);
  (**(code **)(pcVar7 + 0x778))(pcVar7 + 0x6fc);
  (**(code **)(pcVar7 + 0x778))(pcVar7 + 0x708);
  uVar8 = DAT_00017258;
  *(volatile undefined4 *)(pcVar7 + 0xb24) = 0;
  *(volatile undefined4 *)(pcVar7 + 0xb28) = uVar8;
  *(volatile undefined2 *)(pcVar7 + 0xb2c) = 0x200b;
  FUN_0002659c(pcVar7 + 0xb10);
  iVar6 = ((long long (*)(void))FUN_00017a40)();
  *DAT_0001725c = iVar6;
  cVar5 = FUN_0002e4e8(pcVar7 + 0x1030,pcVar7 + 0x1034,pcVar7 + 0x1038);
  pcVar7[0x1089] = cVar5;
  pcVar7[1] = '\0';
  FUN_00022518(pcVar7 + 0x103c);
  FUN_0007c360(pcVar7);
  if (*DAT_0001725c == 0) {
    iVar6 = *piVar1;
    *pcVar7 = '\x01';
    if (0 < iVar6) {
      iVar6 = *DAT_0001750c;
      uVar8 = DAT_00017520;
LAB_000172a6:
      if (iVar6 == 0) {
        DEBUG_PRINT(uVar8,DAT_00017510);
      }
      else {
        ((long long (*)(void))FUN_00019c70)();
      }
    }
  }
  else if (*DAT_0001725c == 1) {
    *pcVar7 = '\x02';
    if (0 < *piVar1) {
      iVar6 = *DAT_0001750c;
      uVar8 = DAT_00017554;
      goto LAB_000172a6;
    }
  }
  else if (0 < *piVar1) {
    if (*DAT_0001750c == 0) {
      DEBUG_PRINT(DAT_00017514,DAT_00017510);
    }
    else {
      ((long long (*)(void))FUN_00019c70)();
    }
  }
  uVar64 = FUN_00016268(pcVar7);
  if (*pcVar7 == '\x01') {
    *(volatile undefined2 *)(pcVar7 + 0xfcc) = 0x0401;
    *(volatile undefined1 *)(pcVar7 + 0xfce) = 5;
    pcVar7[0xe4] = pcVar7[0xe4] | 4;
  }
  else if (*pcVar7 == '\x02') {
    *(volatile undefined1 *)(pcVar7 + 0xfcf) = 1;
    *(volatile undefined2 *)(pcVar7 + 0xfd0) = 0x0504;
    pcVar7[0x6de] = pcVar7[0x6de] | 4;
  }
  FUN_00072908(pcVar7 + 8,(uint)(uVar64 >> 32),0xffffffff,0xffffffff);
  if (pcVar7[1] == '\x01') {
LAB_00017372:
    if (1 < *piVar1) {
      if (*DAT_0001750c == 0) {
        DEBUG_PRINT(DAT_00017538,DAT_00017534);
      }
      else {
        ((long long (*)(void))FUN_00019c70)();
      }
    }
  }
  else {
    FUN_00018208(pcVar7 + 0x77c);
    ((long long (*)(void))FUN_00015df4)();
    if (*pcVar7 == '\x01') {
      ((long long (*)(void))FUN_0004ab3c)();
      FUN_00075174(DAT_00017524);
      ((long long (*)(void))FUN_00015f80)();
      *(undefined4 *)(pcVar7 + 0xf00) = DAT_00017528;
      FUN_000622a0(DAT_00017528);
      FUN_00026250(pcVar7 + 0xee4);
      FUN_0002e8fc(pcVar7 + 0xf80);
    }
    else if (*pcVar7 == '\x02') {
      ((long long (*)(void))FUN_00015f80)();
      *(undefined4 *)(pcVar7 + 0xf00) = DAT_00017528;
      FUN_000622a0(DAT_00017528);
    }
    FUN_00047148(pcVar7 + 0xb6c);
    ((long long (*)(void))FUN_00025290)();
    FUN_00036ed8(*(undefined4 *)(*piVar2 + 0xfec));
    ((long long (*)(void))FUN_00023df4)();
    ((long long (*)(void))FUN_00023d0c)();
    ((long long (*)(void))FUN_00023acc)();
    ((long long (*)(void))FUN_000243fc)();
    pcVar7[0x108e] = '\0';
    *(undefined2 *)(pcVar7 + 0xed8) = *(undefined2 *)(pcVar7 + 0xede);
    pcVar7[0x108c] = '\0';
    if (1 < *piVar1) {
      if (*DAT_0001750c == 0) {
        DEBUG_PRINT(DAT_00017530,DAT_0001752c);
      }
      else {
        ((long long (*)(void))FUN_00019c70)();
      }
      goto LAB_00017372;
    }
  }
  FUN_00023230(pcVar7);
  iVar6 = (**(code **)(pcVar7 + 0x77c))(pcVar7 + 0x77c);
  if ((iVar6 != 0) && (1 < *piVar1)) {
    if (*DAT_0001750c == 0) {
      DEBUG_PRINT(DAT_0001753c,DAT_00017534,iVar6);
    }
    else {
      ((long long (*)(void))FUN_00019c70)();
    }
  }
  if (*pcVar7 == '\x01') {
    iVar6 = (**(code **)(pcVar7 + 0xf70))(pcVar7 + 0xee4);
    if ((iVar6 != 0) && (1 < *piVar1)) {
      if (*DAT_0001750c == 0) {
        DEBUG_PRINT(DAT_00017540,DAT_00017534,iVar6);
      }
      else {
        ((long long (*)(void))FUN_00019c70)();
      }
    }
    iVar6 = (**(code **)(pcVar7 + 0xf80))(pcVar7 + 0xf80);
    if ((iVar6 != 0) && (1 < *piVar1)) {
      if (*DAT_0001750c == 0) {
        DEBUG_PRINT(DAT_00017544,DAT_00017534,iVar6);
      }
      else {
        ((long long (*)(void))FUN_00019c70)();
      }
    }
  }
  puVar9 = DAT_00017548;
  iVar6 = FUN_0008638c(DAT_00017548);
  uVar8 = DAT_0001754c;
  if (iVar6 != 0) {
    DEBUG_PRINT(DAT_00017558,*puVar9);
    iVar6 = FUN_0008638c(DAT_0001755c);
    uVar8 = DAT_00017560;
    if (((iVar6 != 0) && (iVar6 = FUN_0002ea28(DAT_0001755c), uVar8 = DAT_00017564, -1 < iVar6)) &&
       (iVar6 = FUN_00062644(DAT_0001755c), uVar8 = DAT_00017568, -1 < iVar6)) {
      DEBUG_PRINT(DAT_00017664);
      DEBUG_PRINT(DAT_00017668);
      ((long long (*)(void))FUN_00016110)();
      iVar6 = ((long long (*)(void))FUN_0007cefc)();
      if (iVar6 != 0) {
        DEBUG_PRINT(DAT_0001766c);
        ((long long (*)(void))FUN_0002ea78)();
      }
      iVar6 = (**(code **)(pcVar7 + 0xb10))(pcVar7 + 0xb10);
      if ((iVar6 != 0) && (1 < *piVar1)) {
        if (*DAT_00017670 == 0) {
          DEBUG_PRINT(DAT_00017678,DAT_00017674,iVar6);
        }
        else {
          ((long long (*)(void))FUN_00019c70)();
        }
      }
      iVar6 = (**(code **)(pcVar7 + 0xb6c))(pcVar7 + 0xb6c);
      if ((iVar6 != 0) && (1 < *piVar1)) {
        if (*DAT_00017670 == 0) {
          DEBUG_PRINT(DAT_0001767c,DAT_00017674,iVar6);
        }
        else {
          ((long long (*)(void))FUN_00019c70)();
        }
      }
      ((long long (*)(void))FUN_00030c90)();
      ((long long (*)(void))FUN_00034944)();
      if (1 < *piVar1) {
        if (*DAT_00017670 == 0) {
          DEBUG_PRINT(DAT_00017680,DAT_00017674);
        }
        else {
          ((long long (*)(void))FUN_00019c70)();
        }
      }
      *(volatile undefined4 *)(pcVar7 + 0x1078) = 0;
      FUN_0007d0aa(pcVar7 + 0x1078);
      FUN_00032808(*(undefined1 *)(DAT_00017684 + 0x70));
      goto LAB_00017414;
    }
  }
  DEBUG_PRINT(uVar8);
LAB_00017414:
  FUN_0002a65c(pcVar7);
  uVar64 = ((long long (*)(void))FUN_0002eaa8)();
  pcVar4 = DAT_00017550;
  uVar8 = (uint)(uVar64 >> 32);
  do {
    FUN_00072908(pcVar14,uVar8,0xffffffff,0xffffffff);
    if (*pcVar4 == '\x01') {
      FUN_000158bc(pcVar14);
    }
    while( true ) {
      uVar13 = (uint)(byte)pcVar7[0x1059];
      if (uVar13 == 0) break;
      if ((int)(uVar13 << 0x1f) < 0) {
        FUN_0007c34a(pcVar7,0);
        bVar12 = pcVar7[0x1059] & 0xfe;
        goto LAB_0001762a;
      }
      if ((int)(uVar13 << 0x1e) < 0) {
        pcVar7[0xfea] = '\v';
        bVar12 = pcVar7[0x1059] & 0xfd;
        goto LAB_0001762a;
      }
      if ((int)(uVar13 << 0x1d) < 0) {
        ((long long (*)(void))FUN_0002f080)();
        bVar12 = pcVar7[0x1059] & 0xfb;
        goto LAB_0001762a;
      }
      if ((int)(uVar13 << 0x1c) < 0) {
        ((long long (*)(void))FUN_000167b4)();
        bVar12 = pcVar7[0x1059] & 0xf7;
LAB_0001762a:
        pcVar7[0x1059] = bVar12;
      }
    }
    uVar64 = FUN_0007c038(1);
    uVar8 = (uint)(uVar64 >> 32);
  } while( true );
}
