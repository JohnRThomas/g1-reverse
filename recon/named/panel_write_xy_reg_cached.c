/* named: panel_write_xy_reg_cached */
/* globals referenced:
//   0x2000a058  g_panel_reg_y_cache          
//   0x2000a05c  g_panel_reg_x_cache          
*/
/* Reconstructed panel_write_xy_reg_cached @ 0x47028  (parity: 300/300 trials, PROVEN) */

extern void projector_send_cmd_0x46(int a0);
extern void net_pkt_write_be16(void);

void panel_write_xy_reg_cached(int param_1, int param_2)
{
  volatile int *piVar1;
  piVar1 = (volatile int *)0x2000a05cUL;
  if (param_1 != *piVar1) {
    net_pkt_write_be16();
    *piVar1 = param_1;
  }
  piVar1 = (volatile int *)0x2000a058UL;
  if (param_2 != *piVar1) {
    projector_send_cmd_0x46(param_2);
    *piVar1 = param_2;
  }
}

