#include "g1_app_symbols.h"
/* named: sc_set */
/* Reconstructed sc_set @ 0x59f04  (parity: 300/300 trials, PROVEN) */

typedef int (*codeptr)(int,...);
extern int find_sc_cfg_59bcc(int,void*);
extern int strtol_ascii_scan(int,int,int);
extern int settings_name_next(int,int*);
extern int bt_settings_decode_key(int,void*);
extern int FUN_000828da(void*,void*);
extern int FUN_00082a42(int,int,void*);

int sc_set(int param_1, int param_2, codeptr param_3, int param_4)
{
  int iVar1;
  unsigned int *puVar2;
  unsigned int local_58;
  unsigned int local_54;
  int iStack_50;
  unsigned short local_4c;
  int local_44;
  unsigned char auStack_40[24];
  unsigned int local_28;
  unsigned int local_24;

  if (param_1 == 0) {
    local_24 = "Insufficient number of arguments" /*=0xf2b65*/;
    local_28 = 2;
    FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1040, &local_28);
  } else {
    iVar1 = bt_settings_decode_key(param_1, auStack_40);
    if (iVar1 == 0) {
      settings_name_next(param_1, &local_44);
      if (local_44 == 0 || (iStack_50 = strtol_ascii_scan(local_44, 0, 10), iStack_50 == 0)) {
        puVar2 = (unsigned int*)find_sc_cfg_59bcc(0, auStack_40);
        if (puVar2 == 0) {
          if (param_2 == 0) return 0;
          puVar2 = (unsigned int*)find_sc_cfg_59bcc(0, (void*)((uintptr_t)&rodata_f2b3a) /*=0xf2b3a*/);
          if (puVar2 == 0) {
            local_24 = "Unable to restore SC: no cfg left" /*=0xf4761*/;
            local_28 = 2;
            FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1040, &local_28);
            return -0xc;
          }
          *(unsigned char*)puVar2 = 0;
          FUN_000828da((unsigned char*)puVar2 + 1, auStack_40);
        } else if (param_2 == 0) {
          puVar2[0] = 0; puVar2[1] = 0; puVar2[2] = 0;
          return 0;
        }
        iVar1 = (*param_3)(param_4, puVar2 + 2, 4);
        if (-1 < iVar1) return 0;
        local_54 = "Failed to decode value (err %zd)" /*=0xf4783*/;
        local_58 = 3;
        iStack_50 = iVar1;
        FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1840, &local_58);
        return iVar1;
      }
      local_54 = "Invalid local identity %lu" /*=0xf4746*/;
      local_58 = 3;
      FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1840, &local_58);
    } else {
      local_54 = "Unable to decode address %s" /*=0xf472a*/;
      local_4c = 0x200;
      local_58 = 0x1000003;
      iStack_50 = param_1;
      FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1c40, &local_58);
    }
  }
  return -0x16;
}

