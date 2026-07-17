/* readable reconstruction; identity: FUN_0007d05e @ 0x0007d05e
 * public-name: attr_configure_mode3_readback
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_set                           <= FUN_00030178 @ 0x00030178
 *   attr_store_get                           <= FUN_000302f8 @ 0x000302f8
 *   wait_attr_0x4714_clear                   <= FUN_0007cfac @ 0x0007cfac
 *   attr_configure_mode3_readback            <= FUN_0007d05e @ 0x0007d05e
 */
/* Reconstructed FUN_0007d05e @ 0x7d05e  (parity: 300/300 trials, PROVEN) */

extern int attr_store_set(unsigned int a, ...);
extern int attr_store_get(unsigned int a, unsigned int b);
extern int wait_attr_0x4714_clear(void);

int attr_configure_mode3_readback(unsigned int param_1)
{
  int iVar1;

  iVar1 = attr_store_set(0x4704);
  if ((((iVar1 == 0) && (iVar1 = attr_store_set(0x4710,3), iVar1 == 0)) &&
      (iVar1 = attr_store_set(0x4714,1), iVar1 == 0)) && (iVar1 = wait_attr_0x4714_clear(), iVar1 == 0)) {
    iVar1 = attr_store_get(0x470c,param_1);
    if (iVar1 != 0) {
      iVar1 = 1;
    }
    iVar1 = -iVar1;
  } else {
    iVar1 = -1;
  }
  return iVar1;
}
