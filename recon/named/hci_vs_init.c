/* readable reconstruction; identity: FUN_00012080 @ 0x00012080
 * public-name: hci_vs_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   hci_vs_init                              <= FUN_00012080 @ 0x00012080
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   bt_hci_cmd_send_sync                     <= FUN_00053d70 @ 0x00053d70
 *   bt_id_addr_check_and_enable              <= FUN_000549ec @ 0x000549ec
 *   ble_rng_get_random_bytes                 <= FUN_00055c64 @ 0x00055c64
 *   bt_conn_init                             <= FUN_00057358 @ 0x00057358
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 *   sys_put_le64                             <= FUN_00080eb8 @ 0x00080eb8
 *   hci_vs_setup_stub                        <= FUN_00081158 @ 0x00081158
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 * address symbols (name @ address):
 *   rodata_1253c                             @ 0x0001253c
 *   rodata_12540                             @ 0x00012540
 *   rodata_12544                             @ 0x00012544
 *   rodata_12548                             @ 0x00012548
 *   rodata_1254c                             @ 0x0001254c
 *   rodata_12554                             @ 0x00012554
 *   rodata_12558                             @ 0x00012558
 *   rodata_1255c                             @ 0x0001255c
 *   rodata_1256c                             @ 0x0001256c
 *   rodata_88138                             @ 0x00088138
 *   rodata_f325b                             @ 0x000f325b
 *   rodata_f327f                             @ 0x000f327f
 *   rodata_f32f7                             @ 0x000f32f7
 *   rodata_f3324                             @ 0x000f3324
 *   g_sram_base_word                         @ 0x20000000
 *   g_ble_dev_state                          @ 0x20002000
 *   g_ble_dev_acl_buf_info                   @ 0x20002078
 *   g_ble_dev_le_features                    @ 0x200020d8
 *   g_ble_dev_le_pkts_sem                    @ 0x20002108
 */
/* Reconstructed FUN_00012080 @ 0x12080  (parity: 30/30 trials, PROVEN) */
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

extern long long bt_hci_cmd_create(int, int);
extern long long bt_hci_cmd_send_sync(int, int, ...);
extern long long bt_id_addr_check_and_enable(void);
extern long long ble_rng_get_random_bytes(void);
extern long long bt_conn_init(void);
extern long long net_buf_unref(int, ...);
extern long long net_buf_simple_add(int, int);
extern long long bt_log_forward_3arg(int, int, ...);
extern long long sys_put_le64(int, int, int);
extern long long hci_vs_setup_stub(void);
extern long long z_impl_k_sem_init(void *, int);
#define DAT_00012388 0x20002000UL
#define DAT_0001238c ((volatile int*)0x20002078UL)
#define DAT_00012390 0xf325bUL
#define DAT_00012394 0x88138UL
#define DAT_00012398 ((volatile int*)0x200020d8UL)
#define DAT_0001239c 0x20002108UL
#define DAT_000123a0 0xf327fUL
#define DAT_00012538 0x2008810UL
#define DAT_00012540 0x88138UL
#define DAT_00012550 0x1000004UL
#define DAT_00012560 0x1000007UL
#define DAT_00012564 0xf3324UL
#define DAT_00012568 0x20002000UL
#define DAT_0001256c (*(volatile int*)0x1256cUL)
#define DAT_00012578 0xf32f7UL
#define _UNK_00012570 (*(volatile int*)0x12570UL)
#define _UNK_00012574 (*(volatile int*)0x12574UL)
#define PTR_s_Vendor_HCI_extensions_not_availa_0001253c (*(volatile int*)0x1253cUL)
#define PTR_s_unknown_00012548 (*(volatile int*)0x12548UL)
#define PTR_PTR_s_reserved_00012544 (*(volatile int*)0x12544UL)
#define PTR_s_HW_Platform___s__0x_04x__0001254c (*(volatile int*)0x1254cUL)
#define PTR_DAT_00012540 (*(volatile int*)0x12540UL)
#define PTR_PTR_s_reserved_00012554 (*(volatile int*)0x12554UL)
#define PTR_s_HW_Variant___s__0x_04x__00012558 (*(volatile int*)0x12558UL)
#define PTR_PTR_s_Standard_Bluetooth_controller_0001255c (*(volatile int*)0x1255cUL)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int hci_vs_init(void)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined **ppuVar10;
  uint *puVar11;
  undefined4 *puVar12;
  undefined *puVar13;
  byte bVar14;
  volatile undefined4 *puVar15;
  undefined8 uVar16;
  undefined4 local_58;
  undefined4 local_54;
  undefined *local_50;
  undefined *local_4c;
  undefined *puStack_48;
  uint local_44;
  undefined4 local_40;
  undefined2 local_3c;
  int local_34;
  int local_30 [4];
  undefined4 local_20;
  undefined *local_1c;

  iVar5 = DAT_00012388;
  if ((*(uint *)(*(int *)(DAT_00012388 + 0x168) + 8) & 1) == 0) {
    uVar16 = bt_hci_cmd_send_sync(0xc03,0,local_30);
    uVar6 = (uint)((ulonglong)uVar16 >> 0x20);
    if ((int)uVar16 != 0) {
      return (int)uVar16;
    }
    if (**(char **)(local_30[0] + 0xc) == '\0') {
      puVar11 = (uint *)(iVar5 + 0xd4);
      uVar6 = *puVar11;
      *puVar11 = *puVar11 & 9;
    }
    net_buf_unref(local_30[0],uVar6);
  }
  iVar1 = bt_hci_cmd_send_sync(0x1003,0,local_30);
  puVar15 = DAT_0001238c;
  if (iVar1 != 0) {
    return iVar1;
  }
  uVar7 = *(undefined4 *)(*(int *)(local_30[0] + 0xc) + 5);
  *DAT_0001238c = *(undefined4 *)(*(int *)(local_30[0] + 0xc) + 1);
  puVar15[1] = uVar7;
  net_buf_unref(local_30[0]);
  iVar1 = bt_hci_cmd_send_sync(0x1001,0,local_30);
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = *(int *)(local_30[0] + 0xc);
  *(undefined1 *)(iVar5 + 0x70) = *(undefined1 *)(iVar1 + 1);
  *(undefined2 *)(iVar5 + 0x72) = *(undefined2 *)(iVar1 + 2);
  *(undefined1 *)(iVar5 + 0x71) = *(undefined1 *)(iVar1 + 4);
  *(undefined2 *)(iVar5 + 0x74) = *(undefined2 *)(iVar1 + 7);
  *(undefined2 *)(iVar5 + 0x76) = *(undefined2 *)(iVar1 + 5);
  net_buf_unref(local_30[0]);
  iVar1 = bt_hci_cmd_send_sync(0x1002,0,local_30);
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = *(int *)(local_30[0] + 0xc);
  puVar12 = (undefined4 *)(iVar1 + 1);
  do {
    uVar7 = *puVar12;
    uVar8 = puVar12[1];
    puVar12 = puVar12 + 2;
    puVar15[2] = uVar7;
    puVar15[3] = uVar8;
    puVar15 = puVar15 + 2;
  } while (puVar12 != (undefined4 *)(iVar1 + 0x41));
  net_buf_unref(local_30[0]);
  iVar1 = ble_rng_get_random_bytes();
  if (iVar1 != 0) {
    return iVar1;
  }
  if (-1 < (int)((uint)*(byte *)(iVar5 + 0x7c) << 0x19)) {
    local_1c = (undefined *)DAT_00012390;
    local_20 = 2;
    bt_log_forward_3arg(DAT_00012394,0x1040,&local_20);
    return -0x13;
  }
  iVar1 = bt_hci_cmd_send_sync(0x2003,0,local_30);
  puVar15 = DAT_00012398;
  if (iVar1 != 0) {
    return iVar1;
  }
  uVar7 = *(undefined4 *)(*(int *)(local_30[0] + 0xc) + 5);
  *DAT_00012398 = *(undefined4 *)(*(int *)(local_30[0] + 0xc) + 1);
  puVar15[1] = uVar7;
  net_buf_unref(local_30[0]);
  iVar2 = bt_hci_cmd_send_sync(0x2002,0,local_30);
  iVar1 = local_30[0];
  if (iVar2 != 0) {
    return iVar2;
  }
  iVar2 = *(int *)(local_30[0] + 0xc);
  if ((*(short *)(iVar2 + 1) != 0) && (*(char *)(iVar2 + 3) != '\0')) {
    *(short *)(iVar5 + 0x104) = *(short *)(iVar2 + 1);
    z_impl_k_sem_init(puVar15 + 0xc,*(undefined1 *)(iVar2 + 3));
  }
  net_buf_unref(iVar1);
  bVar14 = *(byte *)(iVar5 + 0x7c) & 0x20;
  if ((*(byte *)(iVar5 + 0x7c) & 0x20) == 0) {
    iVar1 = bt_hci_cmd_create(0xc6d,2);
    if (iVar1 == 0) {
      return -0x69;
    }
    puVar3 = (undefined1 *)net_buf_simple_add(iVar1 + 0xc,2);
    *puVar3 = 1;
    puVar3[1] = bVar14;
    iVar1 = bt_hci_cmd_send_sync(0xc6d,iVar1,bVar14);
    if (iVar1 != 0) {
      return iVar1;
    }
  }
  if ((int)((uint)*(byte *)(iVar5 + 0x9c) << 0x1c) < 0) {
    iVar1 = bt_hci_cmd_send_sync(0x201c,0,local_30);
    if (iVar1 != 0) {
      return iVar1;
    }
    uVar7 = *(undefined4 *)(*(int *)(local_30[0] + 0xc) + 5);
    *(undefined4 *)(iVar5 + 0xe0) = *(undefined4 *)(*(int *)(local_30[0] + 0xc) + 1);
    *(undefined4 *)(iVar5 + 0xe4) = uVar7;
    net_buf_unref(local_30[0]);
  }
  if ((int)((uint)*(byte *)(iVar5 + 0xd8) << 0x19) < 0) {
    iVar1 = bt_hci_cmd_send_sync(0x202a,0,local_30);
    if (iVar1 != 0) {
      return iVar1;
    }
    *(undefined1 *)(iVar5 + 0x120) = *(undefined1 *)(*(int *)(local_30[0] + 0xc) + 1);
    net_buf_unref(local_30[0]);
  }
  iVar1 = bt_hci_cmd_create(0x2001,8);
  if (iVar1 == 0) {
    return -0x69;
  }
  uVar7 = net_buf_simple_add(iVar1 + 0xc,8);
  uVar9 = (uint)*(byte *)(iVar5 + 0xd8);
  uVar6 = 0x202;
  if ((*(byte *)(iVar5 + 0xd8) & 0x40) == 0) {
    uVar6 = 3;
  }
  if ((int)(uVar9 << 0x1e) < 0) {
    uVar6 = uVar6 | 0x2c;
  }
  else {
    uVar6 = uVar6 | 0xc;
  }
  if ((int)(uVar9 << 0x1a) < 0) {
    uVar6 = uVar6 | 0x40;
  }
  if ((*(byte *)(iVar5 + 0xd9) & 9) != 0) {
    uVar6 = uVar6 | 0x800;
  }
  if ((int)(uVar9 << 0x1f) < 0) {
    uVar6 = uVar6 | 0x10;
  }
  if ((*(byte *)(iVar5 + 0xa2) & 6) == 6) {
    uVar6 = uVar6 | 0x180;
  }
  sys_put_le64(uVar6,0,uVar7);
  iVar1 = bt_hci_cmd_send_sync(0x2001,iVar1,0);
  if (iVar1 != 0) {
    return iVar1;
  }
  if ((int)((uint)*(byte *)(iVar5 + 0x7c) << 0x1a) < 0) {
    if (*(short *)(iVar5 + 0x104) == 0) {
      local_1c = (undefined *)DAT_000123a0;
      local_20 = 2;
      bt_log_forward_3arg(DAT_00012394,0x1040,&local_20);
      return -5;
    }
  }
  else if (*(short *)(iVar5 + 0x104) == 0) {
    iVar1 = bt_hci_cmd_send_sync(0x1005,0,local_30);
    if (iVar1 != 0) {
      return iVar1;
    }
    if (*(short *)(iVar5 + 0x104) == 0) {
      iVar1 = *(int *)(local_30[0] + 0xc);
      *(undefined2 *)(iVar5 + 0x104) = *(undefined2 *)(iVar1 + 1);
      z_impl_k_sem_init(DAT_0001239c,*(undefined2 *)(iVar1 + 4));
    }
    net_buf_unref(local_30[0]);
  }
  iVar1 = bt_hci_cmd_create(0xc01,8);
  if (iVar1 == 0) {
    return -0x69;
  }
  uVar4 = net_buf_simple_add(iVar1 + 0xc,8);
  uVar8 = _UNK_00012570;
  uVar7 = _UNK_00012574;
  if (-1 < (int)((uint)*(byte *)(iVar5 + 0xd8) << 0x1f)) {
    uVar8 = DAT_00012538;
    uVar7 = 0x20000000;
  }
  sys_put_le64(uVar8,uVar7,uVar4);
  iVar5 = bt_hci_cmd_send_sync(0xc01,iVar1,0);
  if (iVar5 != 0) {
    return iVar5;
  }
  iVar5 = bt_hci_cmd_send_sync(0xfc01,0,&local_34);
  puVar13 = PTR_s_Vendor_HCI_extensions_not_availa_0001253c;
  if (iVar5 == 0) {
    iVar5 = *(int *)(local_34 + 0xc);
    local_44 = (uint)*(ushort *)(iVar5 + 1);
    puStack_48 = PTR_s_unknown_00012548;
    if (local_44 < 4) {
      puStack_48 = *(undefined **)(PTR_PTR_s_reserved_00012544 + local_44 * 4);
    }
    local_40 = (local_40 & ~(0xffffULL<<0)) | (((unsigned long long)(0x200) & 0xffffULL)<<0);
    local_4c = PTR_s_HW_Platform___s__0x_04x__0001254c;
    local_50 = DAT_00012550;
    bt_log_forward_3arg(PTR_DAT_00012540,0x24c0,&local_50);
    local_44 = (uint)*(ushort *)(iVar5 + 3);
    puStack_48 = PTR_s_unknown_00012548;
    if ((*(short *)(iVar5 + 1) == 2) && (local_44 < 4)) {
      puStack_48 = *(undefined **)(PTR_PTR_s_reserved_00012554 + local_44 * 4);
    }
    local_40 = CONCAT22(((unsigned long long)(local_40)>>16 & 0xffffULL),0x200);
    local_4c = PTR_s_HW_Variant___s__0x_04x__00012558;
    ppuVar10 = &local_50;
    local_50 = DAT_00012550;
    bt_log_forward_3arg(PTR_DAT_00012540,0x24c0,&local_50);
    local_4c = (undefined *)(uint)*(byte *)(iVar5 + 5);
    puStack_48 = (undefined *)(uint)*(byte *)(iVar5 + 6);
    if (local_4c < 4) {
      ppuVar10 = (undefined **)PTR_PTR_s_Standard_Bluetooth_controller_0001255c;
    }
    local_44 = (uint)*(ushort *)(iVar5 + 7);
    local_40 = *(undefined4 *)(iVar5 + 9);
    local_50 = PTR_s_unknown_00012548;
    if (local_4c < 4) {
      local_50 = ppuVar10[(int)local_4c];
    }
    local_3c = 0x200;
    local_54 = DAT_00012578;
    local_58 = DAT_00012560;
    bt_log_forward_3arg(PTR_DAT_00012540,0x3cc0,&local_58);
    net_buf_unref(local_34);
    iVar1 = bt_hci_cmd_send_sync(0xfc02,0,&local_34);
    iVar5 = DAT_00012568;
    puVar13 = DAT_00012564;
    if (iVar1 == 0) {
      *(undefined2 *)(DAT_00012568 + 0xc1) = *(undefined2 *)(*(int *)(local_34 + 0xc) + 1);
      net_buf_unref(local_34);
      if (-1 < (int)((uint)*(byte *)(iVar5 + 0xc1) << 0x1d)) goto LAB_000123fe;
      iVar1 = bt_hci_cmd_send_sync(0xfc03,0,&local_34);
      puVar13 = DAT_0001256c;
      if (iVar1 == 0) {
        *(undefined1 *)(iVar5 + 0xc0) = *(undefined1 *)(*(int *)(local_34 + 0xc) + 1);
        net_buf_unref(local_34);
        goto LAB_000123fe;
      }
    }
  }
  local_20 = 2;
  local_1c = puVar13;
  bt_log_forward_3arg(PTR_DAT_00012540,0x1080,&local_20);
LAB_000123fe:
  iVar5 = hci_vs_setup_stub();
  if (iVar5 != 0) {
    return iVar5;
  }
  iVar5 = bt_conn_init();
  if (iVar5 == 0) {
    iVar5 = bt_id_addr_check_and_enable();
    return iVar5;
  }
  return iVar5;
}
