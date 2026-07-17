/* readable reconstruction; identity: FUN_00063c14 @ 0x00063c14
 * public-name: FUN_00063c14
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_caf_power_manager_timer                @ 0x200066f0
 *   g_caf_power_manager_system_off_flag      @ 0x2001d563
 */
/* Reconstructed FUN_00063c14 @ 0x63c14  (parity: 300/300 trials, PROVEN) */

extern void FUN_00063be0(void);
extern void FUN_00073518(unsigned int);
void FUN_00063c14(int param_1)
{
  unsigned char b;
  b = *(volatile unsigned char*)0x2001d563UL;
  if (b == 0) {
    if (param_1 != 0) {
      FUN_00073518(0x200066f0UL);
    }
  } else if (param_1 == 0) {
    FUN_00063be0();
  }
  *(volatile unsigned char*)0x2001d563UL = (unsigned char)param_1;
  return;
}
