/* named: revalidate_whitelist_json */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed revalidate_whitelist_json @ 0x355b4  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(const char *msg, const char *file, unsigned int line);
extern int debug_print(void);
extern int convert_app_whitelist_to_json(int);
extern int malloc(int);
extern int heap_free(int);
extern int memset_bytes(int, int, int);

void revalidate_whitelist_json(void)
{
  int iVar1;

  iVar1 = malloc(0x1800);
  if (iVar1 != 0) {
    memset_bytes(iVar1,0,0x15e3);
    convert_app_whitelist_to_json(iVar1);
    heap_free(iVar1);
    return;
  }
  if (*(volatile unsigned int*)0x20007554UL != 0) {
    debug_print();
    return;
  }
  DEBUG_PRINT((const char*)0xa7c9cUL,(const char*)0xa8a24UL,0x277);
  return;
}

