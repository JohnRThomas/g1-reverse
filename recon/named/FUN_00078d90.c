/* named: FUN_00078d90 */
/* Reconstructed FUN_00078d90 @ 0x78d90  (parity: 151/300 trials, PROVEN) */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned int undefined4;

extern int _malloc_r(void *a, int b);
extern int FUN_0007712c(void *a, void *b, void *c, u32 d, void *e);
extern int vfprintf_format_engine(void *a, void *b, void *c, u32 d, void *e);
extern int mem_find_byte(u32 a, u32 b, int c);
extern int iobuf_ensure_capacity_and_append(void *a, void *b, void *c, int d);

int FUN_00078d90(undefined4 *param_1, int *param_2, byte *param_3, uint *param_4)
{
  int iVar1, iVar2, iVar8;
  uint local_88, local_7c, local_84;
  int local_74;
  byte local_70;
  byte local_45;
  uint *local_8c;
  byte *pbVar6, *pbVar7, *pbVar3;
  int bVar4;
  uint uVar5;

  if (((int)((uint)*(u16 *)((byte*)param_2+0xc) << 0x18) < 0) && (param_2[4] == 0)) {
    iVar1 = _malloc_r(param_1, 0x40);
    *param_2 = iVar1;
    param_2[4] = iVar1;
    if (iVar1 == 0) {
      *param_1 = 0xc;
      return -1;
    }
    param_2[5] = 0x40;
  }
  iVar1 = 0x000f8b6b;
  local_74 = 0;
  local_8c = param_4;
  pbVar7 = param_3;

LAB_de4:
  pbVar6 = pbVar7;
  while (*pbVar6 != 0 && *pbVar6 != 0x25) {
    pbVar6++;
  }
  pbVar7 = pbVar6 + 1;
  if (*pbVar6 == 0x25) {
    /* fallthrough to LAB_df0 with pbVar6 pointing at '%' */
  }
LAB_df0:
  iVar8 = (int)(long)pbVar6 - (int)(long)param_3;
  if (iVar8 != 0) {
    iVar2 = iobuf_ensure_capacity_and_append(param_1, param_2, param_3, iVar8);
    if (iVar2 == -1) {
      goto LAB_f56;
    }
    local_74 = local_74 + iVar8;
  }
  if (*pbVar6 == 0) {
    goto LAB_f56;
  }
  local_88 = 0;
  local_7c = 0;
  local_45 = 0;
  local_84 = 0xffffffff;
  pbVar7 = pbVar6 + 1;
  while (1) {
    pbVar6 = pbVar7 + 1;
    iVar2 = mem_find_byte(0x000f8b6bu, *pbVar7, 5);
    if (iVar2 == 0) break;
    local_88 = (1u << ((iVar2 - iVar1) & 0xff)) | local_88;
    pbVar7 = pbVar6;
  }
  if ((int)(local_88 << 0x1b) < 0) local_45 = 0x20;
  if ((int)(local_88 << 0x1c) < 0) local_45 = 0x2b;

  if (*pbVar7 == 0x2a) {
    pbVar3 = (byte*)(local_8c + 1);
    local_7c = *local_8c;
    local_8c = (uint*)pbVar3;
    if ((int)local_7c < 0) {
      local_7c = (uint)(-(int)local_7c);
      local_88 = local_88 | 2;
    }
    pbVar6 = pbVar7;
  } else {
    bVar4 = 0;
    uVar5 = local_7c;
    pbVar6 = pbVar7;
    while (1) {
      if (9 < (uint)(*pbVar6 - 0x30)) break;
      uVar5 = uVar5 * 10 + (*pbVar6 - 0x30);
      bVar4 = 1;
      pbVar6 = pbVar6 + 1;
    }
    if (bVar4) local_7c = uVar5;
  }

  if (*pbVar6 == 0x2e) {
    if (pbVar6[1] == 0x2a) {
      pbVar6 = pbVar6 + 2;
      uVar5 = *local_8c;
      local_8c = local_8c + 1;
      local_84 = uVar5;
    } else {
      bVar4 = 0;
      uVar5 = 0;
      local_84 = 0;
      while (1) {
        pbVar6 = pbVar6 + 1;
        if (9 < (uint)(*pbVar6 - 0x30)) break;
        uVar5 = uVar5 * 10 + (*pbVar6 - 0x30);
        bVar4 = 1;
      }
      if (bVar4) local_84 = uVar5;
    }
  }

  iVar2 = mem_find_byte(0x000f8b71u, *pbVar6, 3);
  if (iVar2 != 0) {
    pbVar6 = pbVar6 + 1;
    local_88 = local_88 | (0x40u << ((iVar2 - 0x000f8b71) & 0xff));
  }
  param_3 = pbVar6 + 1;
  local_70 = *pbVar6;
  iVar8 = mem_find_byte(0x000f8b75u, local_70, 6);
  if (iVar8 == 0) {
    iVar2 = vfprintf_format_engine(param_1, &local_88, param_2, 0x00087737u, &local_8c);
  } else {
    iVar2 = FUN_0007712c(param_1, &local_88, param_2, 0x00087737u, &local_8c);
  }
  if (iVar2 == -1) goto LAB_f56;
  local_74 = local_74 + iVar2;
  pbVar7 = param_3;
  goto LAB_de4;

LAB_f56:
  if ((int)((uint)*(u16*)((byte*)param_2+0xc) << 0x19) < 0) {
    return -1;
  }
  return local_74;
}

