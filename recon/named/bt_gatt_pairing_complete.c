/* named: bt_gatt_pairing_complete */
/* Reconstructed bt_gatt_pairing_complete @ 0x82fd2  (parity: 300/300 trials, PROVEN) */

extern void bt_gatt_store_ccc(unsigned char,int);
extern void bt_gatt_store_cf(unsigned char,int,unsigned int,unsigned int);
void bt_gatt_pairing_complete(int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  if (param_2 != 0) {
    bt_gatt_store_ccc(*(volatile unsigned char *)(param_1 + 8), param_1 + 0x90);
    bt_gatt_store_cf(*(volatile unsigned char *)(param_1 + 8), param_1 + 0x90, param_3, param_4);
    return;
  }
  return;
}

