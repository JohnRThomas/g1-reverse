/* Reconstructed indicate_sc_cb @ 0x18a38  (parity: 300/300 trials, PROVEN) */

extern int FUN_000187e8(unsigned int, int);
extern void debug_print(unsigned long, ...);
extern int FUN_00056a68(unsigned int, int);
extern void DEBUG_PRINT(unsigned long, ...);

void indicate_sc_cb(unsigned int *param_1, unsigned int param_2, int param_3)
{
  unsigned char bVar1;

  if (param_3 != 0) return;
  bVar1 = *(volatile unsigned char*)0x2000ff70UL;
  bVar1 = bVar1 + 1;
  *(volatile unsigned char*)0x2000ff70UL = bVar1;
  if (bVar1 < 5) {
    *(volatile unsigned int*)0x20006ab4UL /* device_info+0x0B8  (ANCS indicate/subscribe flags) */ |= 4;
    FUN_000187e8(*param_1, 1);
    return;
  }
  *(volatile unsigned char*)0x2000ff70UL = 0;
  if (*(int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 0) {
    if (*(int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
      DEBUG_PRINT(0x9a8f9, 0x9b1da);
    } else {
      debug_print(0x9a8f9, 0x9b1da);
    }
  }
  FUN_00056a68(*param_1, 0x13);
}

