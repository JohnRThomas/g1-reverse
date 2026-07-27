/* readable reconstruction; identity: FUN_0005a724 @ 0x0005a724
 * public-name: gatt_cf_settings_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_cf_cfg_by_addr                      <= FUN_00059b5c @ 0x00059b5c
 *   find_cf_cfg                              <= FUN_00059c04 @ 0x00059c04
 *   gatt_cf_cfg_clear                        <= FUN_0005a39c @ 0x0005a39c
 *   gatt_cf_settings_set                     <= FUN_0005a724 @ 0x0005a724
 *   strtoul                                  <= FUN_00077c1c @ 0x00077c1c
 *   settings_name_next                       <= FUN_0007f1e8 @ 0x0007f1e8
 *   bt_settings_decode_key                   <= FUN_00080cf2 @ 0x00080cf2
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   set_change_aware_no_store                <= FUN_00082b98 @ 0x00082b98
 *   set_change_aware                         <= FUN_00082bb8 @ 0x00082bb8
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f2b65                             @ 0x000f2b65
 *   rodata_f472a                             @ 0x000f472a
 *   rodata_f4746                             @ 0x000f4746
 *   rodata_f4783                             @ 0x000f4783
 *   rodata_f48b5                             @ 0x000f48b5
 *   rodata_f48d7                             @ 0x000f48d7
 *   rodata_f492b                             @ 0x000f492b
 */
/* Reconstructed FUN_0005a724 @ 0x5a724  (parity: 300/300 trials, PROVEN) */
extern int  find_cf_cfg_by_addr(int,void*);
extern int  find_cf_cfg(void);
extern int  gatt_cf_cfg_clear(int);
extern int  strtoul(int,int,int);
extern int settings_name_next(int, int);
extern int  bt_settings_decode_key(int,void*);
extern void bt_addr_le_copy_828da(unsigned long*, unsigned long*);
extern void log_msg_create_3arg(int,int,void*);
extern void set_change_aware_no_store(int,int);
extern void set_change_aware(int,int);
#define VB(a) (*(volatile unsigned char*)(a))

struct discovery_frame {
  unsigned char decoded[2];
  unsigned char decoded_pad[2];
  int identity;
  unsigned char address[24];
  struct { unsigned level, message; } log;
  unsigned char compiler_frame_pad[8];
};

int gatt_cf_settings_set(int param_1,int param_2,int param_3,int param_4){
  int iVar1, puVar2;
  struct discovery_frame frame;
  if (param_1 == 0) {
    frame.log.level = 2;
    frame.log.message = 0x000f2b65;
    log_msg_create_3arg(0x00088128, 0x1040, &frame.log);
    return -0x16;
  }
  iVar1 = bt_settings_decode_key(param_1, frame.address);
  if (iVar1 != 0) {
    struct { unsigned type, message; int value; unsigned short flags; } log = {
      0x01000003, 0x000f472a, param_1, 0x200
    };
    log_msg_create_3arg(0x00088128, 0x1c40, &log);
    return -0x16;
  }
  settings_name_next(param_1, &frame.identity);
  if (frame.identity != 0 && (iVar1 = strtoul(frame.identity, 0, 10)) != 0) {
    struct { unsigned level, message; int error; } log = { 3, 0x000f4746, iVar1 };
    log_msg_create_3arg(0x00088128, 0x1840, &log);
    return -0x16;
  }
  puVar2 = find_cf_cfg_by_addr(0, frame.address);
  if (puVar2 == 0) {
    puVar2 = find_cf_cfg();
    if (puVar2 == 0) {
      frame.log.level = 2;
      frame.log.message = 0x000f48b5;
      log_msg_create_3arg(0x00088128, 0x1040, &frame.log);
      return -0xc;
    }
    VB(puVar2) = 0;
    bt_addr_le_copy_828da(puVar2+1, frame.address);
  }
  if (param_2 != 0) {
    iVar1 = ((int(*)(int,void*,int))param_3)(param_4, frame.decoded, 2);
    if (iVar1 < 0) {
      struct { unsigned level, message; int error; } log = { 3, 0x000f4783, iVar1 };
      log_msg_create_3arg(0x00088128, 0x1840, &log);
      return iVar1;
    }
    VB(puVar2+8) = frame.decoded[0];
    if (iVar1 == 2) {
      unsigned int u = frame.decoded[1];
      if (u < 2) { set_change_aware_no_store(puVar2, u & 1); return 0; }
      struct { unsigned level, message, value; } log = { 3, 0x000f492b, u };
      log_msg_create_3arg(0x00088128, 0x1880, &log);
    } else {
      frame.log.level = 2;
      frame.log.message = 0x000f48d7;
      log_msg_create_3arg(0x00088128, 0x1080, &frame.log);
    }
    set_change_aware(puVar2, 0);
    return 0;
  }
  gatt_cf_cfg_clear(puVar2);
  return 0;
}
