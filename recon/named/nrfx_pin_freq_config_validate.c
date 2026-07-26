/* readable reconstruction; identity: FUN_00066d78 @ 0x00066d78
 * public-name: nrfx_pin_freq_config_validate
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_pin_freq_config_validate            <= FUN_00066d78 @ 0x00066d78
 * address symbols (name @ address):
 *   rodata_f4240                             @ 0x000f4240
 */
#include "../headers/g1_nrf_regs.h"
/* Reconstructed FUN_00066d78 @ 0x66d78  (parity: 300/300 trials, PROVEN) */
int nrfx_pin_freq_config_validate(int *param_1, int *param_2){
  unsigned r3 = (unsigned)param_2[5];
  unsigned r2v;
  if (r3 == 0x1e8480) goto L_e18;
  if (r3 > 0x1e8480) goto L_d9e;
  if (r3 == 0x7a120) goto L_e18;
  if (r3 > 0x7a120) { r2v = 0xf4240; goto L_d92; }
  if (r3 == 0x1e848) goto L_e18;
  r2v = 0x3d090;
 L_d92:
  if (r3 == r2v) goto L_e18;
  return 0x0bad0004;
 L_d9e:
  if (r3 == 0xf42400) goto L_db6;
  if (r3 > 0xf42400) { if (r3 != 0x1e84800) return 0x0bad0004; goto L_db6; }
  if (r3 == 0x3d0900) goto L_e18;
  r2v = 0x7a1200;
  goto L_d92;
 L_db6:
  if ((char)param_1[1] == 0) return 0x0bad0003;
  if (*(unsigned char*)((int)param_2+0x23) == 0) goto L_dca;
  goto L_dc2;
 L_dca:
  if (*param_1 != G1_NRF_SPIM4_S_BASE) return 0x0bad0000;
  if (r3 != 0x1e84800) return 0x0bad0000;
  if (*param_2 != -1 && *param_2 != 8) return 0x0bad0004;
  if (param_2[1] != -1 && param_2[1] != 9) return 0x0bad0004;
  if (param_2[2] != -1 && param_2[2] != 0xa) return 0x0bad0004;
  if (*(unsigned char*)((int)param_2+0x21) != 0){
    if (param_2[3] != -1 && param_2[3] != 0xb) return 0x0bad0004;
  }
  if (param_2[7] == -1) return 0x0bad0000;
  return (param_2[7] == 0xc) ? 0x0bad0000 : 0x0bad0004;
 L_e18:
  if (*(unsigned char*)((int)param_2+0x21) != 0){
    if (param_2[3] != -1) goto L_db6;
  }
  if (param_2[7] != -1) goto L_db6;
  if (*(unsigned char*)((int)param_2+0x23) != 0) goto L_dc2;
  return 0x0bad0000;
 L_dc2:
  if (*(unsigned char*)((int)param_2+0x24) != 0) return 0x0bad0000;
  goto L_dca;
}
