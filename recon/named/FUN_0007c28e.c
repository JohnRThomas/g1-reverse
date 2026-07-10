/* named: FUN_0007c28e */
/* Reconstructed FUN_0007c28e @ 0x7c28e  (parity: 300/300 trials, PROVEN) */
extern int is_battery_critical(void);
extern void flash_settings_write_and_verify(int,void*,int);
int FUN_0007c28e(int param_1){
  unsigned char buf[0x20];
  (void)param_1;
  is_battery_critical();
  flash_settings_write_and_verify(0x134000, buf, 0x20);
  return 0;
}

