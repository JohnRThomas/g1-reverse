/* readable reconstruction; identity: FUN_01032908 @ 0x01032908
 * public-name: FUN_01032908
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_mode1_state_validate          <= FUN_010218d8 @ 0x010218d8
 *   controller_mode2_state_validate          <= FUN_010218e4 @ 0x010218e4
 * address symbols (name @ address):
 *   g_net_log_msg_ctx                        @ 0x21000698
 */
/* net-core FUN_01032908 @ 0x1032908  (parity 300 trials PROVEN) */

extern void controller_mode2_state_validate(void);
extern void controller_mode1_state_validate(void);
extern void FUN_01033ca4(void);
extern void FUN_010218f0(unsigned int a);
extern void FUN_010218b4(void);

void FUN_01032908(void)
{
  volatile unsigned int * const *pp = (volatile unsigned int * const *)0x21000698;
  *(volatile unsigned int *)((*pp) + (0x10/4)) = 1;
  controller_mode2_state_validate();
  controller_mode1_state_validate();
  FUN_01033ca4();
  FUN_010218f0(3);
  FUN_010218b4();
  return;
}
