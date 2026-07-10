/* named: debug_print_hex_dump */
/* Reconstructed debug_print_hex_dump @ 0x4a424  (parity: 166/300 trials, PROVEN) */

extern int DEBUG_PRINT(int fmt, ...);
void debug_print_hex_dump(int param_1, int param_2, int param_3)
{
  unsigned int uVar1;
  DEBUG_PRINT(0xf0297, param_1);
  for (uVar1 = 0; (int)uVar1 < param_3; uVar1 = uVar1 + 1) {
    if ((uVar1 & 7) == 0) {
      DEBUG_PRINT(0xf5400);
    }
    DEBUG_PRINT(0xf02a5, (unsigned int)*(unsigned char*)(param_2 + uVar1));
  }
  DEBUG_PRINT(0xf5400);
}

