/* Reconstructed master_process_audio_fw_load_req @ 0x2af4c  (parity: 750/750 trials, PROVEN) */
typedef unsigned char byte;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned int uint;
typedef void code;

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_000167a8(void);
extern int FUN_00019ac0(uint);
extern unsigned int FUN_000232b0(void);
extern unsigned int FUN_000232b8(void);
extern int FUN_000269fc(void);
extern int FUN_0002bd4c(int, char*, uint);
extern int FUN_0002efa8(void);
extern int FUN_000340c4(char*, byte*, char*, byte*, byte*, byte*, undefined4);
extern int FUN_0004a424(int, byte*, int);
extern int FUN_0004a46c(int, int, int);
extern int FUN_0004a51c(void);
extern int FUN_0004a568(byte*, int);
extern int FUN_0007c0e2(uint);
extern int FUN_0007ce00(void);
extern int FUN_0007d2f8(int);
extern int FUN_0007d968(byte*, int, byte*);
extern int FUN_00086c04(int, byte*, int);
extern int FUN_00086c78(void*, int, int);
extern int thunk_FUN_00072880(void*);
extern int update_persist_task_status(char*, int, int);
extern int FUN_00033a5c(char*, byte*);

#define DAT_0002b208 ((volatile int*)0x20007554)
#define DAT_0002b20c ((const char*)0x000a243a)
#define DAT_0002b210 ((const char*)0x000a1ca4)
#define DAT_0002b214 ((const char*)0x000a2416)
#define DAT_0002b218 ((const char*)0x000a1ce0)
#define DAT_0002b21c 0x000a1cfc
#define DAT_0002b220 ((int*)0x2000230c)
#define DAT_0002b224 ((const char*)0x000a23ff)
#define DAT_0002b228 ((const char*)0x000a1d06)
#define DAT_0002b22c ((const char*)0x000a1d31)
#define DAT_0002b230 ((const char*)0x000a1d59)
#define DAT_0002b234 ((const char*)0x000a1d8d)
#define DAT_0002b238 ((const char*)0x000a1dbe)
#define DAT_0002b4d4 ((volatile int*)0x20007554)
#define DAT_0002b4d8 ((const char*)0x000a23ff)
#define DAT_0002b4dc ((const char*)0x000a1df5)
#define DAT_0002b4e0 ((const char*)0x000a1e66)
#define DAT_0002b4e4 ((const char*)0x000a1e3a)
#define DAT_0002b4e8 ((const char*)0x000a1ead)
#define DAT_0002b4ec ((int*)0x2000230c)
#define DAT_0002b4f0 ((const char*)0x000a1edb)
#define DAT_0002b4f4 0x000a1f1a
#define DAT_0002b4f8 0x000a1f49
#define DAT_0002b4fc ((const char*)0x000a1f24)
#define DAT_0002b500 ((const char*)0x000a1f35)
#define DAT_0002b504 ((const char*)0x000a1f4e)
#define DAT_0002b508 ((const char*)0x000a1f7d)
#define DAT_0002b50c ((const char*)0x000a1fc7)
#define DAT_0002b510 ((const char*)0x000a1ff2)
#define DAT_0002b7a8 ((int*)0x2000230c)
#define DAT_0002b7ac ((volatile int*)0x20007554)
#define DAT_0002b7b0 ((const char*)0x000a23ff)
#define DAT_0002b7b4 ((const char*)0x000a201b)
#define DAT_0002b7b8 ((const char*)0x000a2041)
#define DAT_0002b7bc ((const char*)0x000a2061)
#define DAT_0002b7c0 ((const char*)0x000a2098)
#define DAT_0002b7c4 ((const char*)0x000a20c2)
#define DAT_0002b7c8 ((const char*)0x000a20e9)
#define DAT_0002b7cc ((const char*)0x000a211e)
#define DAT_0002b7d0 ((const char*)0x000a23e8)
#define DAT_0002b7d4 ((const char*)0x000a2184)
#define DAT_0002b7d8 ((const char*)0x000a21c4)
#define DAT_0002b7dc ((const char*)0x000a21f9)
#define DAT_0002baa0 0x000a23cd
#define DAT_0002baa4 ((int*)0x2000230c)
#define DAT_0002baa8 ((const char*)0x000a23e8)
#define DAT_0002baac ((const char*)0x000a2227)
#define DAT_0002bab0 ((const char*)0x000a22b8)
#define DAT_0002bab4 ((volatile int*)0x20007554)
#define DAT_0002bab8 ((const char*)0x000a2334)
#define DAT_0002babc ((const char*)0x0009b708)
#define DAT_0002bac0 ((const char*)0x0009b729)
#define DAT_0002bac4 ((const char*)0x0009b74b)
#define DAT_0002bc0c ((int*)0x2000230c)
#define DAT_0002bc10 ((volatile int*)0x20007554)
#define DAT_0002bc14 ((const char*)0x000a23d0)
#define DAT_0002bc18 ((const char*)0x000a2364)
#define DAT_0002bc1c ((const char*)0x000a2383)
#define DAT_0002bc20 ((const char*)0x000a245b)
#define DAT_0002bc24 ((const char*)0x000a23a0)
#define DAT_0002bc28 0x000f680e
#define DAT_00033aa8 ((int*)0x2000230c)
#define DAT_00033aac ((volatile int*)0x20007554)
#define DAT_00033ab0 ((const char*)0x000a829f)
#define DAT_00033ab4 ((const char*)0x000a7cd6)
#define DAT_00033ab8 ((const char*)0x000a7cf4)

int master_process_audio_fw_load_req(char *param_1, byte *param_2, byte *param_3, undefined4 param_4)
{
  byte bVar1;
  undefined2 uVar2;
  byte bVar3;
  int *piVar4;
  uint *puVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  undefined1 uVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  char *pcVar14;
  byte *pbVar15;
  undefined4 *puVar16;
  undefined4 *puVar17;
  undefined4 *puVar18;
  char *pcVar19;
  uint uVar20;
  byte bVar21;
  code *pcVar22;
  byte *pbVar23;
  int iVar24;
  uint uVar25;
  int iVar26;
  uint uVar27;
  undefined4 uVar28;
  undefined1 local_124;
  undefined4 local_123;
  undefined4 local_11f;
  undefined2 local_11b;
  char local_119;
  undefined1 auStack_118 [244];

  piVar9 = DAT_00033aa8;
  piVar8 = DAT_0002bc0c;
  piVar7 = DAT_0002baa4;
  piVar6 = DAT_0002b7a8;
  puVar5 = (uint*)DAT_0002b4ec;
  piVar4 = DAT_0002b220;
  pbVar23 = param_2 + 4;
  if (param_2[1] == 3) {
    uVar28 = *(undefined4 *)(param_2 + 8);
    iVar24 = *(int *)(param_2 + 0xc);
    if (2 < *DAT_0002b220) {
      if (*DAT_0002b208 == 0) {
        DEBUG_PRINT(DAT_0002b210,DAT_0002b20c,*(undefined4 *)(param_2 + 4),uVar28,iVar24);
      }
      else {
        FUN_00019c70(DAT_0002b210,DAT_0002b20c,*(undefined4 *)(param_2 + 4),uVar28,iVar24);
      }
    }
    if (iVar24 - 0x13U < 0x800d) {
      iVar11 = FUN_000167a8();
      if (*(int *)(iVar11 + 0x1030) != 0) {
        iVar11 = FUN_000167a8();
        iVar26 = iVar24 + -0x12;
        pcVar22 = *(code **)(iVar11 + 0x1030);
        uVar12 = FUN_000167a8();
        iVar13 = (*(int(*)(int,undefined4,byte*,int))pcVar22)(uVar12,uVar28,param_3 + 0x12,iVar26);
        iVar11 = iVar26;
        if ((iVar13 != 0) && (iVar11 = iVar13, 0 < *piVar4)) {
          if (*DAT_0002b208 == 0) {
            DEBUG_PRINT(DAT_0002b218,DAT_0002b214,iVar13);
          }
          else {
            FUN_00019c70(DAT_0002b218,DAT_0002b214,iVar13);
          }
        }
        if (iVar26 == iVar11) {
          *param_3 = 0x6f;
          param_3[1] = 0x6b;
          FUN_0007d968(param_3 + 0x12,iVar26,param_3 + 2);
          FUN_0004a424(DAT_0002b21c,param_3 + 2,0x10);
          return iVar24;
        }
      }
    }
    *param_3 = 0x6e;
    param_3[1] = 0x6f;
    return 0;
  }
  uVar20 = (uint)*param_2;
  if (0x26 < (uVar20 - 1 & 0xff)) {
    if (0x1c < (uVar20 - 0x29 & 0xff)) {
      if (9 < uVar20 - 0x47) {
        if (0 < *DAT_0002bc0c) {
          if (*DAT_0002bc10 == 0) {
            DEBUG_PRINT(DAT_0002bc24,DAT_0002bc20);
          }
          else {
            FUN_00019c70(DAT_0002bc24,DAT_0002bc20);
          }
        }
        uVar2 = *(undefined2 *)(DAT_0002bc28 + 1);
        *(undefined4 *)param_3 = *(undefined4*)DAT_0002bc28;
        *(undefined2 *)(param_3 + 4) = uVar2;
        return 6;
      }
      switch(uVar20) {
      case 0x4a:
        uVar20 = (uint)param_2[4];
        if (2 < *DAT_0002bc0c) {
          if (*DAT_0002bc10 == 0) {
            DEBUG_PRINT(DAT_0002bc18,DAT_0002bc14,uVar20);
          }
          else {
            FUN_00019c70(DAT_0002bc18,DAT_0002bc14,uVar20);
          }
        }
        if ((int)(uVar20 << 0x1e) < 0) {
          param_1[0xc9] = -0x7d;
          param_1[0xca] = '\x01';
          FUN_00086c78((char*)&local_123 + 3,0,0xf8);
          local_124 = 2;
          local_123 = *(undefined4 *)(param_1 + 0xc9);
          local_11f = *(undefined4 *)(param_1 + 0xcd);
          local_11b = *(undefined2 *)(param_1 + 0xd1);
          local_119 = param_1[0xd3];
          FUN_00086c78(auStack_118,0,0x15);
          (*(void(**)(void*,int))(param_1 + 0x774))(&local_124,0xfc);
        }
        if ((int)(uVar20 << 0x1f) < 0) {
          if (2 < *piVar8) {
            if (*DAT_0002bc10 == 0) {
              DEBUG_PRINT(DAT_0002bc1c,DAT_0002bc14);
            }
            else {
              FUN_00019c70(DAT_0002bc1c,DAT_0002bc14);
            }
          }
          (*(void(**)(void*))(param_1 + 0x102c))(param_1 + 0x68);
        }
        break;
      case 0x4b:
        iVar24 = FUN_000340c4(param_1,param_2,param_1 + 0xd4,param_2,pbVar23,param_3,param_4);
        return iVar24;
      case 0x4c:
        uVar20 = *(uint *)(param_2 + 4);
        FUN_0007c0e2(uVar20 << 0x18 | (uVar20 >> 8 & 0xff) << 0x10 | (uVar20 >> 0x10 & 0xff) << 8 |
                     uVar20 >> 0x18);
        break;
      case 0x4d:
        iVar24 = FUN_000167a8();
        param_1 = (char *)(iVar24 + 0x9ac);
        goto LAB_0002b188;
      case 0x4e:
        *(undefined1 *)(*(int *)(param_1 + 0x100c) + 0x196) = 0;
        if (*(char *)(*(int *)(param_1 + 0x100c) + 7) == '\0') {
          *(undefined1 *)(*(int *)(param_1 + 0x100c) + 7) = 10;
        }
        *param_3 = 0xc9;
        if (**(int **)(param_1 + 0x1054) == 0x10) {
          return 1;
        }
        uVar28 = 0x10;
        goto LAB_0002b404;
      case 0x4f:
        iVar24 = FUN_000167a8();
        *(byte *)(iVar24 + 0x108f) = param_2[4];
        bVar21 = *param_2;
        iVar24 = FUN_000167a8();
        *(uint *)(iVar24 + 0x104c) = (uint)bVar21;
        iVar24 = FUN_000167a8();
        thunk_FUN_00072880((void*)(iVar24 + 0x80));
        *param_3 = 0xc9;
        param_3[1] = param_2[4];
        return 2;
      default:
        goto switchD_0002b03a_caseD_3;
      }
      goto LAB_0002b1ac;
    }
    switch(uVar20 - 0x29) {
    case 0:
      *param_3 = param_1[0xed5];
      param_3[1] = param_1[0xf98];
      if (*piVar6 < 3) {
        return 2;
      }
      iVar24 = *DAT_0002b7ac;
      uVar28 = (undefined4)DAT_0002b7d0;
      uVar12 = (undefined4)DAT_0002b7dc;
      break;
    case 1:
      bVar21 = param_1[0xf60];
      *param_3 = bVar21;
      if (*piVar6 < 3) {
        return 1;
      }
      if (*DAT_0002b7ac != 0) {
        FUN_00019c70(DAT_0002b7d8,DAT_0002b7d0);
        return 1;
      }
      DEBUG_PRINT(DAT_0002b7d8,DAT_0002b7d0,(uint)bVar21,(uint)param_3[1]);
      return 1;
    case 2:
      *param_3 = param_1[0xfea];
      uVar28 = FUN_000269fc();
      piVar4 = DAT_0002b7a8;
      param_3[1] = (byte)uVar28;
      if (*piVar4 < 3) {
        return 2;
      }
      if (*DAT_0002b7ac != 0) {
        FUN_00019c70(DAT_0002b7d4,DAT_0002b7d0,(uint)*param_3,uVar28,(uint)param_3[2],(uint)param_3[3]);
        return 2;
      }
      DEBUG_PRINT(DAT_0002b7d4,DAT_0002b7d0,(uint)*param_3,uVar28,(uint)param_3[2],(uint)param_3[3]);
      return 2;
    case 3:
      uVar20 = (uint)(byte)param_1[0xfc0];
      uVar25 = (uint)(byte)param_1[0xfc1];
      if (uVar20 == 0x5d) {
        if (param_1[0xfc2] == '\0') {
          if (uVar25 == 0x5d) {
            uVar20 = 0x5e;
            uVar25 = uVar20;
            goto LAB_0002b7fe;
          }
          uVar20 = 0x5e;
          uVar27 = uVar25 - 0x5e & 0xff;
        }
        else {
          if (uVar25 == 0x5d) {
            uVar20 = 0x5f;
            goto LAB_0002b8ee;
          }
          uVar20 = 0x5f;
          uVar27 = uVar25 - 0x5e & 0xff;
        }
      }
      else if (uVar20 == 0x5e) {
        if (param_1[0xfc2] == '\0') {
          if (uVar25 == 0x5d) {
            uVar20 = 0x60;
            uVar25 = 0x5e;
            goto LAB_0002b7fe;
          }
          uVar20 = 0x60;
          uVar27 = uVar25 - 0x5e & 0xff;
        }
        else {
          if (uVar25 == 0x5d) {
            uVar20 = 0x61;
            uVar25 = 0x5e;
            goto LAB_0002b7fe;
          }
          uVar20 = 0x61;
          uVar27 = uVar25 - 0x5e & 0xff;
        }
      }
      else if (uVar20 == 0x5f) {
        if (uVar25 == 0x5d) {
          uVar20 = 0x62;
          goto LAB_0002b8ee;
        }
        uVar20 = 0x62;
        uVar27 = uVar25 - 0x5e & 0xff;
      }
      else if (uVar20 == 0x60) {
        if (uVar25 == 0x5d) {
          uVar20 = 99;
          goto LAB_0002b8ee;
        }
        uVar20 = 99;
        uVar27 = uVar25 - 0x5e & 0xff;
      }
      else if (uVar20 < 0x61) {
        if (uVar25 == 0x5d) goto LAB_0002b8ee;
        uVar27 = uVar25 - 0x5e & 0xff;
      }
      else {
        if (uVar25 == 0x5d) {
          uVar20 = 100;
LAB_0002b8ee:
          uVar25 = 0x5e;
          goto LAB_0002b7fe;
        }
        uVar27 = uVar25 - 0x5e & 0xff;
        uVar20 = 100;
        uVar25 = 100;
      }
      if (uVar27 < 3) {
        uVar25 = (int)*(char *)(DAT_0002baa0 + uVar27);
      }
LAB_0002b7fe:
      *param_3 = (byte)uVar20;
      param_3[1] = (byte)uVar25;
      bVar21 = param_1[0xfc4];
      param_3[2] = bVar21;
      bVar1 = param_1[0xfc5];
      param_3[3] = bVar1;
      bVar3 = param_1[0xfc6];
      param_3[4] = bVar3;
      pbVar23 = param_3 + 5;
      pcVar14 = param_1 + 0xfcc;
      do {
        pcVar19 = pcVar14 + 4;
        pbVar15 = pbVar23 + 4;
        *(undefined4 *)pbVar23 = *(undefined4 *)pcVar14;
        pbVar23 = pbVar15;
        pcVar14 = pcVar19;
      } while (pcVar19 != param_1 + 0xfd8);
      *(undefined2 *)pbVar15 = *(undefined2 *)pcVar19;
      if (2 < *DAT_0002baa4) {
        if (*DAT_0002bab4 == 0) {
          DEBUG_PRINT(DAT_0002baac,DAT_0002baa8,uVar20,uVar25,(uint)bVar21,(uint)bVar1,(uint)bVar3,
                      (uint)param_3[5],(uint)param_3[6],(uint)param_3[7],(uint)param_3[8],
                      (uint)param_3[9],(uint)param_3[10],(uint)param_3[0xb],(uint)param_3[0xc],
                      (uint)param_3[0xd],(uint)param_3[0xe],(uint)param_3[0xf]);
        }
        else {
          FUN_00019c70(DAT_0002baac,DAT_0002baa8,uVar20,uVar25,(uint)bVar21,(uint)bVar1,(uint)bVar3,
                      (uint)param_3[5],(uint)param_3[6],(uint)param_3[7],(uint)param_3[8],
                      (uint)param_3[9],(uint)param_3[10],(uint)param_3[0xb],(uint)param_3[0xc],
                      (uint)param_3[0xd],(uint)param_3[0xe],(uint)param_3[0xf]);
        }
      }
      return 0x13;
    case 4:
      *(undefined4 *)param_3 = *(undefined4 *)(param_1 + 0xfda);
      *(undefined2 *)(param_3 + 4) = *(undefined2 *)(param_1 + 0xfde);
      *(undefined4 *)(param_3 + 6) = *(undefined4 *)(param_1 + 0xfe0);
      *(undefined2 *)(param_3 + 10) = *(undefined2 *)(param_1 + 0xfe4);
      if (2 < *DAT_0002baa4) {
        if (*DAT_0002bab4 == 0) {
          DEBUG_PRINT(DAT_0002bab0,DAT_0002baa8,(uint)*param_3,(uint)param_3[1],(uint)param_3[2],
                      (uint)param_3[3],(uint)param_3[4],(uint)param_3[5],(uint)param_3[6],
                      (uint)param_3[7],(uint)param_3[8],(uint)param_3[9],(uint)param_3[10],
                      (uint)param_3[0xb]);
        }
        else {
          FUN_00019c70(DAT_0002bab0,DAT_0002baa8,(uint)*param_3,(uint)param_3[1],(uint)param_3[2],
                      (uint)param_3[3],(uint)param_3[4],(uint)param_3[5],(uint)param_3[6],
                      (uint)param_3[7],(uint)param_3[8],(uint)param_3[9],(uint)param_3[10],
                      (uint)param_3[0xb]);
        }
      }
      return 0xc;
    default:
      goto switchD_0002b03a_caseD_3;
    case 9:
      *param_3 = param_1[0xef4];
      param_3[1] = param_1[0xef5];
      if (*piVar7 < 3) {
        return 2;
      }
      iVar24 = *DAT_0002bab4;
      uVar28 = (undefined4)DAT_0002baa8;
      uVar12 = (undefined4)DAT_0002bab8;
      break;
    case 10:
      puVar16 = (undefined4 *)FUN_000232b8();
      puVar18 = puVar16;
      pbVar23 = param_3;
      do {
        puVar17 = puVar18 + 1;
        *(undefined4 *)pbVar23 = *puVar18;
        puVar18 = puVar17;
        pbVar23 = pbVar23 + 4;
      } while (puVar17 != puVar16 + 4);
      if (*DAT_0002baa4 < 3) {
        return 0x10;
      }
      iVar24 = *DAT_0002bab4;
      uVar28 = (undefined4)DAT_0002bac0;
      goto LAB_0002b9d8;
    case 0xb:
      puVar16 = (undefined4 *)FUN_000232b0();
      puVar18 = puVar16;
      pbVar23 = param_3;
      do {
        puVar17 = puVar18 + 1;
        *(undefined4 *)pbVar23 = *puVar18;
        puVar18 = puVar17;
        pbVar23 = pbVar23 + 4;
      } while (puVar17 != puVar16 + 4);
      if (*DAT_0002baa4 < 3) {
        return 0x10;
      }
      iVar24 = *DAT_0002bab4;
      uVar28 = (undefined4)DAT_0002babc;
LAB_0002b9d8:
      if (iVar24 == 0) {
        DEBUG_PRINT((const char*)uVar28,DAT_0002baa8,param_3);
      }
      else {
        FUN_00019c70((const char*)uVar28,DAT_0002baa8,param_3);
      }
      return 0x10;
    case 0xc:
      *param_3 = param_1[2];
      if (*piVar7 < 3) {
        return 1;
      }
      if (*DAT_0002bab4 != 0) {
        FUN_00019c70(DAT_0002bac4,DAT_0002baa8);
        return 1;
      }
      DEBUG_PRINT(DAT_0002bac4,DAT_0002baa8);
      return 1;
    case 0xd:
      return FUN_00033a5c(param_1, param_3);
    case 0xe:
      uVar28 = FUN_0004a51c();
      FUN_0004a568(param_3,uVar28);
      if (param_1[0xae3] == '\0') {
        iVar24 = *(int *)(param_1 + 0x9b4);
        if (iVar24 != 0) {
          iVar24 = 1;
        }
        bVar21 = (byte)iVar24;
      }
      else {
        bVar21 = 0;
      }
      goto LAB_0002b31a;
    }
    if (iVar24 == 0) {
      DEBUG_PRINT((const char*)uVar28,(const char*)uVar12,uVar20);
    }
    else {
      FUN_00019c70((const char*)uVar28,(const char*)uVar12,uVar20);
    }
    return 2;
  }
  switch(uVar20 - 1) {
  case 0:
    uVar20 = (uint)param_2[4];
    if (((byte)param_1[0xed5] == uVar20) && (param_1[0xf98] == param_2[5])) {
      if (2 < *DAT_0002b220) {
        if (*DAT_0002b208 == 0) {
          DEBUG_PRINT(DAT_0002b22c,DAT_0002b224);
        }
        else {
          FUN_00019c70(DAT_0002b22c,DAT_0002b224);
        }
      }
    }
    else {
      if (2 < *DAT_0002b220) {
        if (*DAT_0002b208 == 0) {
          DEBUG_PRINT(DAT_0002b228,DAT_0002b224,uVar20);
        }
        else {
          FUN_00019c70(DAT_0002b228,DAT_0002b224,uVar20);
        }
      }
      (*(void(**)(void*,uint))(param_1 + 0xb8c))(param_1 + 0xb6c,uVar20);
      param_1[0xf98] = param_2[5];
      *(uint *)(param_1 + 0x104c) = (uint)*param_2;
      thunk_FUN_00072880(param_1 + 0x80);
    }
    *param_3 = param_2[4];
    param_3[1] = param_2[5];
    param_3[2] = 0xc9;
    return 3;
  case 1:
    bVar21 = param_2[4];
    uVar20 = (uint)(byte)param_1[0xf60];
    if (uVar20 != bVar21) {
      if (2 < *DAT_0002b220) {
        if (*DAT_0002b208 == 0) {
          DEBUG_PRINT(DAT_0002b230,DAT_0002b224,(uint)bVar21);
        }
        else {
          FUN_00019c70(DAT_0002b230,DAT_0002b224,(uint)bVar21);
        }
      }
      param_1[0xf60] = bVar21;
      goto LAB_0002b17c;
    }
    if (2 < *DAT_0002b220) {
      iVar24 = *DAT_0002b208;
      uVar28 = (undefined4)DAT_0002b234;
      uVar12 = (undefined4)DAT_0002b224;
LAB_0002b1a0:
      if (iVar24 == 0) {
        DEBUG_PRINT((const char*)uVar28,(const char*)uVar12,uVar20);
      }
      else {
        FUN_00019c70((const char*)uVar28,(const char*)uVar12,uVar20);
      }
    }
    goto LAB_0002b1ac;
  case 2:
    bVar21 = param_2[4];
    uVar20 = (uint)bVar21;
    uVar25 = (uint)param_2[5];
    if (2 < *DAT_0002b220) {
      if (*DAT_0002b208 == 0) {
        DEBUG_PRINT(DAT_0002b238,DAT_0002b224,uVar20,uVar25);
      }
      else {
        FUN_00019c70(DAT_0002b238,DAT_0002b224,uVar20,uVar25);
      }
    }
    if (2 < uVar20 - 10) {
      if (2 < *piVar4) {
        if (*DAT_0002b4d4 == 0) {
          DEBUG_PRINT(DAT_0002b4e8,DAT_0002b4d8,uVar20);
        }
        else {
          FUN_00019c70(DAT_0002b4e8,DAT_0002b4d8,uVar20);
        }
      }
      bVar21 = 0xca;
      goto LAB_0002b2d8;
    }
    if (uVar20 != (byte)param_1[0xfea]) {
      if (*param_1 == '\x01') {
        if ((byte)param_1[0xfea] == 0xc) {
          if ((uVar20 != 0xc) && (uVar10 = 1, uVar25 != 1)) goto LAB_0002b1f2;
        }
        else if (uVar20 == 0xc) {
          uVar10 = 0;
LAB_0002b1f2:
          FUN_0007d2f8(uVar10);
        }
      }
      param_1[0xfea] = bVar21;
      *(uint *)(param_1 + 0x104c) = (uint)*param_2;
      thunk_FUN_00072880(param_1 + 0x80);
      if (param_1[0xb0c] == '\0') {
        iVar24 = *piVar4;
        if (uVar20 == 0xb) {
          if (2 < iVar24) {
            if (*DAT_0002b4d4 == 0) {
              DEBUG_PRINT(DAT_0002b4dc,DAT_0002b4d8);
            }
            else {
              FUN_00019c70(DAT_0002b4dc,DAT_0002b4d8);
            }
          }
          pcVar14 = param_1 + 0xaf4;
          param_1[0xfe9] = '\x03';
LAB_0002b282:
          thunk_FUN_00072880(pcVar14);
          return 0;
        }
      }
      else {
        iVar24 = *piVar4;
        if (uVar20 == 0xc) {
          if (2 < iVar24) {
            if (*DAT_0002b4d4 == 0) {
              DEBUG_PRINT(DAT_0002b4e0,DAT_0002b4d8);
            }
            else {
              FUN_00019c70(DAT_0002b4e0,DAT_0002b4d8);
            }
          }
          goto LAB_0002b1ac;
        }
      }
      if (2 < iVar24) {
        iVar24 = *DAT_0002b4d4;
        uVar28 = (undefined4)DAT_0002b4e4;
        uVar12 = (undefined4)DAT_0002b4d8;
        goto LAB_0002b1a0;
      }
    }
    goto LAB_0002b1ac;
  default:
    goto switchD_0002b03a_caseD_3;
  case 4:
    uVar25 = (uint)param_2[4];
    bVar21 = param_2[5];
    uVar20 = (uint)bVar21;
    if (2 < (int)*DAT_0002b4ec) {
      if (*DAT_0002b4d4 == 0) {
        DEBUG_PRINT(DAT_0002b4f0,DAT_0002b4d8,uVar25,uVar20);
      }
      else {
        FUN_00019c70(DAT_0002b4f0,DAT_0002b4d8,uVar25,uVar20);
      }
    }
    uVar28 = (undefined4)DAT_0002b4fc;
    if (uVar25 == 1) {
      if (uVar20 != 0) {
        uVar20 = 1;
      }
      FUN_0002bd4c(DAT_0002b4f4,param_1,uVar20);
    }
    else if (uVar25 == 2) {
      *puVar5 = uVar20;
      DEBUG_PRINT((const char*)uVar28,(const char*)uVar20);
    }
    else if ((uVar25 == 3) && (uVar25 = *puVar5, param_1[0xd5] = bVar21, 2 < (int)uVar25)) {
      if (*DAT_0002b4d4 == 0) {
        DEBUG_PRINT(DAT_0002b500,DAT_0002b4d8,uVar20);
      }
      else {
        FUN_00019c70(DAT_0002b500,DAT_0002b4d8,uVar20);
      }
    }
    bVar21 = *(byte *)(DAT_0002b4f8 + 1);
    *(undefined4 *)param_3 = *(undefined4*)DAT_0002b4f8;
LAB_0002b31a:
    param_3[4] = bVar21;
    return 5;
  case 6:
    bVar21 = param_2[8];
    if (2 < (int)*DAT_0002b4ec) {
      if (*DAT_0002b4d4 == 0) {
        DEBUG_PRINT(DAT_0002b504,DAT_0002b4d8,(uint)param_2[4],(uint)param_2[5],(uint)param_2[6],
                    (uint)param_2[7],(uint)bVar21,(uint)param_2[9]);
      }
      else {
        FUN_00019c70(DAT_0002b504,DAT_0002b4d8,(uint)param_2[4],(uint)param_2[5],(uint)param_2[6],
                    (uint)param_2[7],(uint)bVar21,(uint)param_2[9]);
      }
    }
    uVar20 = *(uint *)(param_2 + 4);
    *(byte *)(*(int *)(param_1 + 0xff0) + 5) = bVar21;
    **(uint **)(param_1 + 0xff0) = uVar20;
    *(undefined1 *)(*(int *)(param_1 + 0xff0) + 6) = 1;
    if (2 < (int)*puVar5) {
      if (*DAT_0002b4d4 == 0) {
        DEBUG_PRINT(DAT_0002b508,DAT_0002b4d8,**(undefined4 **)(param_1 + 0xff0),uVar20 / 0xe10,
                    (uVar20 % 0xe10) / 0x3c,(uVar20 % 0xe10) % 0x3c,(uint)bVar21);
      }
      else {
        FUN_00019c70(DAT_0002b508,DAT_0002b4d8,**(undefined4 **)(param_1 + 0xff0),uVar20 / 0xe10,
                    (uVar20 % 0xe10) / 0x3c,(uVar20 % 0xe10) % 0x3c,(uint)bVar21);
      }
    }
    *(uint *)(param_1 + 0x104c) = (uint)*param_2;
    thunk_FUN_00072880(param_1 + 0x80);
    *param_3 = 0xc9;
    if (*(char *)(*(int *)(param_1 + 0xff0) + 5) == '\0') {
      return 1;
    }
    uVar28 = 2;
    goto LAB_0002b404;
  case 7:
    if (2 < *DAT_0002b7a8) {
      if (*DAT_0002b7ac == 0) {
        DEBUG_PRINT(DAT_0002b7b4,DAT_0002b7b0);
      }
      else {
        FUN_00019c70(DAT_0002b7b4,DAT_0002b7b0);
      }
    }
    FUN_00086c04(*(undefined4 *)(param_1 + 0xff4),pbVar23,0x16a);
    **(undefined4 **)(param_1 + 0xfec) = *(undefined4 *)(*(int *)(param_1 + 0xff4) + 0x164);
    FUN_0004a46c(*(undefined4 *)(param_1 + 0xfec),0,1);
    if (2 < *piVar6) {
      if (*DAT_0002b7ac == 0) {
        DEBUG_PRINT(DAT_0002b7b8,DAT_0002b7b0);
      }
      else {
        FUN_00019c70(DAT_0002b7b8,DAT_0002b7b0);
      }
    }
LAB_0002b17c:
    *(uint *)(param_1 + 0x104c) = (uint)*param_2;
    param_1 = param_1 + 0x80;
LAB_0002b188:
    thunk_FUN_00072880(param_1);
    goto LAB_0002b1ac;
  case 8:
    if (2 < (int)*DAT_0002b4ec) {
      if (*DAT_0002b4d4 == 0) {
        DEBUG_PRINT(DAT_0002b50c,DAT_0002b4d8);
      }
      else {
        FUN_00019c70(DAT_0002b50c,DAT_0002b4d8);
      }
    }
    FUN_00086c04(*(undefined4 *)(param_1 + 0xffc),pbVar23,0x217);
    if ((param_2[5] == 0) &&
       (FUN_00086c78(*(void**)(param_1 + 0xffc),0,0x217), param_2[5] == 0)) {
      return 0;
    }
    uVar28 = 9;
    goto LAB_0002b446;
  case 9:
    if ((int)*DAT_0002b4ec < 3) {
      return 0;
    }
    if (*DAT_0002b4d4 != 0) {
      FUN_00019c70(DAT_0002b510,DAT_0002b4d8);
      return 0;
    }
    DEBUG_PRINT(DAT_0002b510,DAT_0002b4d8);
    return 0;
  case 10:
    bVar21 = param_2[4];
    uVar27 = (uint)bVar21;
    uVar20 = (uint)(byte)param_1[0xef4];
    bVar1 = param_2[5];
    uVar25 = (uint)bVar1;
    if ((uVar20 != uVar27) || ((byte)param_1[0xef5] != uVar25)) {
      if (2 < *DAT_0002b7a8) {
        if (*DAT_0002b7ac == 0) {
          DEBUG_PRINT(DAT_0002b7bc,DAT_0002b7b0,uVar27,uVar25);
        }
        else {
          FUN_00019c70(DAT_0002b7bc,DAT_0002b7b0,uVar27,uVar25);
        }
      }
      param_1[0xef4] = bVar21;
      param_1[0xef5] = bVar1;
      goto LAB_0002b17c;
    }
    if (2 < *DAT_0002b7a8) {
      iVar24 = *DAT_0002b7ac;
      uVar28 = (undefined4)DAT_0002b7c0;
      uVar12 = (undefined4)DAT_0002b7b0;
      goto LAB_0002b1a0;
    }
    goto LAB_0002b1ac;
  case 0xc:
    iVar24 = FUN_0002efa8();
    if (iVar24 != 0) {
      return 0;
    }
    *(undefined1 *)(*(int *)(param_1 + 0x1004) + 0x195) = 0;
    iVar24 = *(int *)(param_1 + 0x1004);
    goto LAB_0002b4a0;
  case 0xe:
    iVar24 = FUN_0002efa8();
    if (iVar24 != 0) {
      return 0;
    }
    *(undefined1 *)(*(int *)(param_1 + 0x1008) + 0x195) = 0;
    iVar24 = *(int *)(param_1 + 0x1008);
LAB_0002b4a0:
    if (*(char *)(iVar24 + 6) == '\0') {
      *(undefined1 *)(iVar24 + 6) = 10;
    }
    *param_3 = 0xc9;
    if (**(int **)(param_1 + 0x1054) == 0xb) {
      return 1;
    }
    uVar28 = 0xb;
LAB_0002b404:
    update_persist_task_status(param_1,uVar28,2);
    return 1;
  case 0x10:
    *(undefined4 *)(param_1 + 0x104c) = 7;
    pcVar14 = param_1 + 0x80;
    goto LAB_0002b282;
  case 0x13:
    bVar21 = param_2[4];
    if (0 < *DAT_0002b7a8) {
      if (*DAT_0002b7ac == 0) {
        DEBUG_PRINT(DAT_0002b7c4,DAT_0002b7b0,(uint)bVar21);
      }
      else {
        FUN_00019c70(DAT_0002b7c4,DAT_0002b7b0,(uint)bVar21);
      }
    }
    FUN_00019ac0((uint)bVar21);
    goto LAB_0002b1ac;
  case 0x25:
    if (2 < *DAT_0002b7a8) {
      if (*DAT_0002b7ac == 0) {
        DEBUG_PRINT(DAT_0002b7c8,DAT_0002b7b0,(uint)param_2[8]);
      }
      else {
        FUN_00019c70(DAT_0002b7c8,DAT_0002b7b0,(uint)param_2[8]);
      }
    }
    if (param_2[8] != 2) {
      return 0;
    }
    if (1 < *piVar6) {
      if (*DAT_0002b7ac == 0) {
        DEBUG_PRINT(DAT_0002b7cc,DAT_0002b7b0,(uint)param_2[9],(uint)param_2[10],(uint)param_2[0xb]);
      }
      else {
        FUN_00019c70(DAT_0002b7cc,DAT_0002b7b0,(uint)param_2[9],(uint)param_2[10],(uint)param_2[0xb]);
      }
    }
    if (param_2[9] != 1) {
      **(undefined1 **)(param_1 + 0x1018) = 0;
      return 0;
    }
    **(undefined1 **)(param_1 + 0x1018) = 1;
    param_1[0xec0] = param_2[10];
    param_1[0xec1] = param_2[0xb];
    iVar24 = FUN_0007ce00();
    if (iVar24 == 0) {
      return 0;
    }
    uVar28 = 0xf;
LAB_0002b446:
    update_persist_task_status(param_1,uVar28,2);
switchD_0002b03a_caseD_3:
    return 0;
  }
LAB_0002b1ac:
  bVar21 = 0xc9;
LAB_0002b2d8:
  *param_3 = bVar21;
  return 1;
}

