#include "g1_app_symbols.h"
/* named: bt_keys_clear */
/* Reconstructed bt_keys_clear @ 0x5ea18  (parity: 300/300 trials, PROVEN) */

extern void printk(int a,int b,int c,int d);
extern unsigned char *assert_post_action(int a,int b);
extern void ble_privacy_id_remove(void);
extern void bt_settings_save_or_delete_key(unsigned char a, unsigned char *b);
extern void memset_bytes(void *a, int b, int c);

void bt_keys_clear(unsigned char *param_1)
{
  unsigned char *r0 = param_1;
  if (param_1 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "keys != ((void *)0)" /*=0xf5298*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/keys.c" /*=0xf5268*/, 0x131);
    r0 = assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/keys.c" /*=0xf5268*/, 0x131);
  }
  unsigned char b8 = *(volatile unsigned char*)(r0 + 8);
  if ((int)((unsigned int)b8 << 0x1d) < 0) {
    ble_privacy_id_remove();
  }
  bt_settings_save_or_delete_key(*param_1, param_1 + 1);
  memset_bytes(param_1, 0, 0x5c);
}

