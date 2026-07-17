/* readable reconstruction; identity: FUN_0100a4d0 @ 0x0100a4d0
 * public-name: FUN_0100a4d0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_timing_quarter_get            <= FUN_01027af2 @ 0x01027af2
 *   controller_timing_delta_clamp            <= FUN_01027b32 @ 0x01027b32
 * address symbols (name @ address):
 *   g_net_storage_area_id                    @ 0x21000bc0
 */
/* net-core FUN_0100a4d0 @ 0x100a4d0  (parity 300 trials PROVEN) */

extern unsigned int controller_timing_quarter_get(unsigned short);
extern unsigned int controller_timing_delta_clamp(unsigned short);
unsigned short FUN_0100a4d0(void)
{
  volatile unsigned short *g = (volatile unsigned short*)0x21000bc0;
  unsigned short uVar1 = (unsigned short)controller_timing_quarter_get(*g);
  unsigned short uVar2 = (unsigned short)controller_timing_delta_clamp(*g);
  if (uVar2 < uVar1) uVar2 = uVar1;
  return uVar2;
}
