/* named: gatt_cf_settings_set */
/* Reconstructed gatt_cf_settings_set @ 0x5a724  (parity: 300/300 trials, PROVEN) */
extern int  find_cf_cfg_by_addr(int,void*);
extern int  find_cf_cfg(void);
extern int  FUN_0005a39c(int);
extern int  strtol_ascii_scan(int,int,int);
extern void settings_name_next(int,int*);
extern int  bt_settings_decode_key(int,void*);
extern void FUN_000828da(int,void*);
extern void FUN_00082a42(int,int,void*);
extern void set_change_aware_no_store(int,int);
extern void set_change_aware(int,int);
#define VB(a) (*(volatile unsigned char*)(a))

int gatt_cf_settings_set(int param_1,int param_2,int param_3,int param_4){
  int iVar1, puVar2, local_44;
  unsigned char st40[24];
  struct { unsigned char local_48; unsigned char local_47; } S;
  int stkargs[8];
  if (param_1 == 0) {
    FUN_00082a42(0x00088128, 0x1040, stkargs);
    return -0x16;
  }
  iVar1 = bt_settings_decode_key(param_1, st40);
  if (iVar1 != 0) {
    FUN_00082a42(0x00088128, 0x1c40, stkargs);
    return -0x16;
  }
  settings_name_next(param_1, &local_44);
  if (local_44 != 0 && (iVar1 = strtol_ascii_scan(local_44, 0, 10)) != 0) {
    FUN_00082a42(0x00088128, 0x1840, stkargs);
    return -0x16;
  }
  puVar2 = find_cf_cfg_by_addr(0, st40);
  if (puVar2 == 0) {
    puVar2 = find_cf_cfg();
    if (puVar2 == 0) {
      FUN_00082a42(0x00088128, 0x1040, stkargs);
      return -0xc;
    }
    VB(puVar2) = 0;
    FUN_000828da(puVar2+1, st40);
  }
  if (param_2 != 0) {
    iVar1 = ((int(*)(int,void*,int))param_3)(param_4, &S.local_48, 2);
    if (iVar1 < 0) {
      FUN_00082a42(0x00088128, 0x1840, stkargs);
      return iVar1;
    }
    VB(puVar2+8) = S.local_48;
    if (iVar1 == 2) {
      unsigned int u = S.local_47;
      if (u < 2) { set_change_aware_no_store(puVar2, u & 1); return 0; }
      FUN_00082a42(0x00088128, 0x1880, stkargs);
    } else {
      FUN_00082a42(0x00088128, 0x1080, stkargs);
    }
    set_change_aware(puVar2, 0);
    return 0;
  }
  FUN_0005a39c(puVar2);
  return 0;
}

