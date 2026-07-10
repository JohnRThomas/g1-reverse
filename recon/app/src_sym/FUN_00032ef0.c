/* Reconstructed FUN_00032ef0 @ 0x32ef0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int, unsigned int);
extern void debug_print(void);

void FUN_00032ef0(unsigned int param_1)
{
  if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug  (device_info_t+0xB58) */ == 0) {
    DEBUG_PRINT(0x000a756aUL, param_1);
  }
  else {
    debug_print();
  }
  *(volatile unsigned char*)0x20019ef3UL = (unsigned char)param_1;
  return;
}

