/* Reconstructed FUN_000355b4 @ 0x355b4  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern int convert_app_whitelist_to_json(int);
extern int FUN_00076d6c(int);
extern int FUN_00076d7c(int);
extern int memset_bytes(int, int, int);

void FUN_000355b4(void)
{
  int iVar1;

  iVar1 = FUN_00076d6c(0x1800);
  if (iVar1 != 0) {
    memset_bytes(iVar1,0,0x15e3);
    convert_app_whitelist_to_json(iVar1);
    FUN_00076d7c(iVar1);
    return;
  }
  if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug */ != 0) {
    debug_print((const char*)0xa7c9cUL,(const char*)0xa8a24UL,0x277);
    return;
  }
  DEBUG_PRINT((const char*)0xa7c9cUL,(const char*)0xa8a24UL,0x277);
  return;
}

