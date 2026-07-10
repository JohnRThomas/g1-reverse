/* named: set_change_aware */
/* Reconstructed set_change_aware @ 0x82bb8  (parity: 300/300 trials, PROVEN) */

extern int set_change_aware_no_store(void);
extern void gatt_delayed_store_enqueue(unsigned char,unsigned char*,unsigned int);
void set_change_aware(unsigned char *param_1)
{
  int iVar1 = set_change_aware_no_store();
  if (iVar1 != 0) {
    gatt_delayed_store_enqueue(*(volatile unsigned char *)param_1, param_1 + 1, 1);
  }
}

