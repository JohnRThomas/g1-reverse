/* readable reconstruction; identity: FUN_00076cc8 @ 0x00076cc8
 * public-name: fprintf_stream
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fprintf_stream                           <= FUN_00076cc8 @ 0x00076cc8
 *   _vfprintf_r                              <= FUN_00076ed4 @ 0x00076ed4
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_00076cc8 @ 0x76cc8  (parity: 300/300 trials, PROVEN) */

extern void _vfprintf_r(unsigned int,unsigned int,unsigned int,void*,unsigned int,void*);
void fprintf_stream(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned int uStack_8;
  unsigned int uStack_4;
  uStack_8 = param_3;
  uStack_4 = param_4;
  _vfprintf_r(*(volatile unsigned int*)0x20002d20UL, param_1, param_2, &uStack_8, param_1, &uStack_8);
  return;
}
