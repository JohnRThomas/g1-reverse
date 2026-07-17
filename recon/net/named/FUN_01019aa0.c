/* readable reconstruction; identity: FUN_01019aa0 @ 0x01019aa0
 * public-name: FUN_01019aa0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_work_submit                          <= FUN_0100ef88 @ 0x0100ef88
 *   sdc_buffer_payload_get                   <= FUN_010270d2 @ 0x010270d2
 *   sdc_buffer_descriptor_resolve            <= FUN_0102714a @ 0x0102714a
 * address symbols (name @ address):
 *   g_ll_conn_default_ctx                    @ 0x21001058
 */
/* net-core FUN_01019aa0 @ 0x1019aa0  (parity 32 trials PROVEN) */
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned short ushort;

#define DAT_01019eac 0x21001058
#define DAT_01019eb0 0x01019a9d

extern undefined4 FUN_0100a5a0(void);
extern void sdc_buffer_descriptor_resolve(undefined4, undefined4 *, undefined1 *);
extern int sdc_buffer_payload_get(undefined4);
extern void sdc_assertion_fail(int, int);
extern int FUN_010199f4(int, ushort *, char, int, uint, char);
extern int FUN_0100ca98(char, int);
extern void sdc_work_submit(int, undefined4, int);
extern int FUN_01026d3e(void);
extern int FUN_01026f32(undefined4, undefined2, int);
/* The callee returns a full register word; this caller explicitly narrows it
 * to the controller's 16-bit scheduler token before forwarding it. */
extern undefined4 FUN_0100a5b4(void);

int FUN_01019aa0(ushort *param_1,int param_2,undefined4 *param_3,uint param_4,undefined1 param_5,
                char param_6,undefined1 param_7,char param_8)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined1 uVar7;
  byte *pbVar8;
  uint uVar9;
  undefined4 *puVar10;
  int iVar11;
  undefined4 uVar12;
  char cVar13;
  uint local_40;
  undefined1 auStack_2e [2];
  undefined4 local_2c [2];

  cVar1 = (char)*param_1;
  uVar3 = FUN_0100a5a0();
  uVar7 = (undefined1)param_4;
  if (param_8 == '\0') {
    sdc_buffer_descriptor_resolve(uVar3,local_2c,auStack_2e);
    iVar4 = sdc_buffer_payload_get(local_2c[0]);
    *(undefined1 *)(iVar4 + 0x1b) = param_7;
    *(undefined1 *)(iVar4 + 0x12) = 1;
    switch(param_4) {
    case 1:
    case 2:
      break;
    default:
switchD_01019af8_caseD_3:
      sdc_assertion_fail(6,0x294); while(1){}
    case 4:
    case 8:
      uVar7 = 3;
    }
    *(undefined1 *)(iVar4 + 0x1e) = uVar7;
    *(undefined1 *)(iVar4 + 0x2d) = param_5;
    local_40 = *(uint *)(param_1 + 10);
    if (local_40 != 0) {
      uVar3 = FUN_0100a5a0();
      sdc_buffer_descriptor_resolve(uVar3,local_2c,auStack_2e);
      sdc_buffer_payload_get(local_2c[0]);
      local_40 = *param_1 & 0x10ff;
      if ((*param_1 & 0x10ff) != 0) {
        local_40 = 0;
LAB_01019b3a:
        pbVar8 = *(byte **)(param_1 + 10);
        *(byte *)(iVar4 + 0x20) = pbVar8[1] >> 4;
        *(ushort *)(iVar4 + 0x21) = (ushort)*pbVar8 | (ushort)((pbVar8[1] & 0xf) << 8);
        goto LAB_01019b56;
      }
    }
LAB_01019b72:
    cVar13 = (char)*param_1;
  }
  else {
    iVar4 = FUN_01026d3e();
    if (iVar4 == 1) {
      return 0;
    }
    if ((char)*param_1 == '\x02') {
      local_40 = 0;
    }
    else {
      local_40 = (uint)(byte)param_1[8];
      uVar9 = *(ushort *)(DAT_01019eac + 0x44) + local_40;
      if (0x672 < uVar9) {
        return 0;
      }
      *(short *)(DAT_01019eac + 0x44) = (short)uVar9;
    }
    sdc_buffer_descriptor_resolve(uVar3,local_2c,auStack_2e);
    iVar4 = sdc_buffer_payload_get(local_2c[0]);
    *(undefined1 *)(iVar4 + 0x1b) = param_7;
    *(undefined1 *)(iVar4 + 0x12) = 1;
    switch(param_4) {
    case 1:
    case 2:
      break;
    default:
      goto switchD_01019af8_caseD_3;
    case 4:
    case 8:
      uVar7 = 3;
    }
    *(undefined1 *)(iVar4 + 0x1f) = uVar7;
    *(undefined1 *)(iVar4 + 0x2d) = param_5;
    if (*(int *)(param_1 + 10) != 0) {
      uVar3 = FUN_0100a5a0();
      sdc_buffer_descriptor_resolve(uVar3,local_2c,auStack_2e);
      iVar5 = sdc_buffer_payload_get(local_2c[0]);
      if ((param_8 != '\x03') || (-1 < (int)((uint)*(byte *)(iVar5 + 0x1c) << 0x1c)))
      goto LAB_01019b3a;
      goto LAB_01019b72;
    }
LAB_01019b56:
    cVar13 = (char)*param_1;
    if (((param_8 == '\x01') && (cVar13 == '\0')) && (*(int *)(param_1 + 0xe) != 0)) {
      *(undefined2 *)(iVar4 + 0x23) = *(undefined2 *)(*(int *)(param_1 + 0xe) + 2);
    }
  }
  uVar9 = ((*(byte *)(iVar4 + 0x1c) & 0xfffffffe) << 0x1e) >> 0x1f;
  if (cVar13 == '\x02') {
    uVar9 = 1;
  }
  *(byte *)(iVar4 + 0x1c) =
       *(byte *)(iVar4 + 0x1c) & 0xf4 | cVar13 == '\x01' | (byte)(uVar9 << 1) |
       (byte)((uVar9 & cVar13 == '\0') << 3);
  if ((*(int *)(param_1 + 4) != 0) && (param_8 != '\x02')) {
    uVar3 = FUN_0100a5a0();
    sdc_buffer_descriptor_resolve(uVar3,local_2c,auStack_2e);
    iVar5 = sdc_buffer_payload_get(local_2c[0]);
    iVar5 = FUN_010199f4(iVar5 + 0x12,param_1,cVar13,1,param_4,param_8);
    if (iVar5 == 0) {
      *(byte *)(iVar4 + 0x1c) = *(byte *)(iVar4 + 0x1c) | 4;
    }
  }
  iVar5 = *(int *)(param_1 + 0xc);
  if ((cVar1 == '\0' || param_8 != '\x01') && (iVar5 != 0)) {
    if (*(char *)(iVar5 + 1) == '\0' && (*(byte *)(iVar5 + 2) & 0x1f) == 0) {
      iVar5 = 2;
    }
    else {
      iVar5 = 1;
    }
    *(byte *)(iVar4 + 0x1c) = *(byte *)(iVar4 + 0x1c) & 0x9f | (byte)(iVar5 << 5);
  }
  else {
    *(byte *)(iVar4 + 0x1c) = *(byte *)(iVar4 + 0x1c) & 0x9f;
  }
  if ((((param_8 != '\0') || ((param_4 & 0xc) == 0)) ||
      (-1 < (int)((uint)*(byte *)((int)param_1 + 1) << 0x1b))) &&
     (*(undefined1 **)(param_1 + 0x10) != (undefined1 *)0x0)) {
    *(undefined1 *)(iVar4 + 0x2c) = **(undefined1 **)(param_1 + 0x10);
  }
  if (*(int *)(param_1 + 2) != 0) {
    uVar3 = FUN_0100a5a0();
    sdc_buffer_descriptor_resolve(uVar3,local_2c,auStack_2e);
    iVar5 = sdc_buffer_payload_get(local_2c[0]);
    iVar5 = FUN_010199f4(iVar5 + 0x12,param_1,cVar1,0,param_4,param_8);
    if (iVar5 == 0) {
      if (param_6 == -1) {
        *(char *)(iVar4 + 0x13) = *(char *)((int)param_1 + 0x11);
        puVar10 = *(undefined4 **)(param_1 + 2);
        *(undefined4 *)(iVar4 + 0x14) = *puVar10;
        *(undefined2 *)(iVar4 + 0x18) = *(undefined2 *)(puVar10 + 1);
      }
      else {
        iVar5 = FUN_0100ca98(param_6,iVar4 + 0x13);
        if (iVar5 == 0) {
          sdc_assertion_fail(0x33,0xe6); while(1){}
        }
        *(byte *)(iVar4 + 0x13) = *(byte *)(iVar4 + 0x13) | 2;
      }
    }
  }
  if (*(int *)(param_1 + 4) != 0) {
    if (param_8 == '\x02') goto LAB_01019c9c;
    uVar3 = FUN_0100a5a0();
    sdc_buffer_descriptor_resolve(uVar3,local_2c,auStack_2e);
    iVar5 = sdc_buffer_payload_get(local_2c[0]);
    iVar5 = FUN_010199f4(iVar5 + 0x12,param_1,cVar1,1,param_4,param_8);
    if (iVar5 == 0) {
      if (param_2 - 2U < 2) {
        *(undefined4 *)(iVar4 + 0x26) = *param_3;
        *(undefined2 *)(iVar4 + 0x2a) = *(undefined2 *)(param_3 + 1);
      }
      else {
        puVar10 = *(undefined4 **)(param_1 + 4);
        *(undefined4 *)(iVar4 + 0x26) = *puVar10;
        *(undefined2 *)(iVar4 + 0x2a) = *(undefined2 *)(puVar10 + 1);
      }
      *(char *)(iVar4 + 0x25) = (char)param_2;
    }
  }
  if (param_8 == '\0') {
    return 1;
  }
LAB_01019c9c:
  uVar3 = DAT_01019eb0;
  iVar5 = DAT_01019eac;
  iVar11 = *(int *)(DAT_01019eac + 0x40);
  if (iVar11 != 0) {
    cVar1 = *(char *)(DAT_01019eac + 0x46);
    *(undefined1 *)(iVar11 + 8) = 0;
    sdc_work_submit(iVar11,uVar3,6);
    uVar3 = DAT_01019eb0;
    if (cVar1 != '\0') {
      *(undefined1 *)(iVar11 + 0x11) = 0;
      sdc_work_submit(iVar11 + 9,uVar3,6);
    }
    *(undefined4 *)(iVar5 + 0x40) = 0;
  }
  uVar6 = FUN_0100a5a0();
  uVar3 = DAT_01019eb0;
  if ((*(byte *)(iVar4 + 0x1c) & 0x60) == 0x20) {
    *(int *)(iVar5 + 0x40) = iVar4;
    uVar9 = local_40;
    if (local_40 < 0xe6) {
      uVar9 = 0;
    }
    uVar7 = (undefined1)uVar9;
    if (0xe5 < local_40) {
      uVar7 = 1;
    }
    *(undefined1 *)(iVar5 + 0x46) = uVar7;
  }
  else {
    *(undefined1 *)(iVar4 + 8) = 0;
    sdc_work_submit(iVar4,uVar3,6);
    uVar3 = DAT_01019eb0;
    if (0xe5 < local_40) {
      *(undefined1 *)(iVar4 + 0x11) = 0;
      sdc_work_submit(iVar4 + 9,uVar3,6);
    }
  }
  uVar2 = FUN_0100a5b4();
  iVar5 = FUN_01026f32(uVar6,uVar2,1);
  if (iVar5 != 0) {
    sdc_buffer_descriptor_resolve(uVar6,local_2c,auStack_2e);
    iVar11 = sdc_buffer_payload_get(local_2c[0]);
    uVar3 = *(undefined4 *)(iVar4 + 0x16);
    uVar6 = *(undefined4 *)(iVar4 + 0x1a);
    uVar12 = *(undefined4 *)(iVar4 + 0x1e);
    *(undefined4 *)(iVar11 + 0x12) = *(undefined4 *)(iVar4 + 0x12);
    *(undefined4 *)(iVar11 + 0x16) = uVar3;
    *(undefined4 *)(iVar11 + 0x1a) = uVar6;
    *(undefined4 *)(iVar11 + 0x1e) = uVar12;
    uVar3 = *(undefined4 *)(iVar4 + 0x26);
    uVar6 = *(undefined4 *)(iVar4 + 0x2a);
    *(undefined4 *)(iVar11 + 0x22) = *(undefined4 *)(iVar4 + 0x22);
    *(undefined4 *)(iVar11 + 0x26) = uVar3;
    *(undefined4 *)(iVar11 + 0x2a) = uVar6;
    return iVar5;
  }
  sdc_assertion_fail(0x33,0x212); while(1){}
  return iVar5;
}
