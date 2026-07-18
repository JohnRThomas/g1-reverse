/* readable reconstruction; identity: FUN_0103a2f8 @ 0x0103a2f8
 * public-name: FUN_0103a2f8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_log_dropped                            <= FUN_0102de10 @ 0x0102de10
 *   z_log_msg_commit                         <= FUN_0102e1fc @ 0x0102e1fc
 */
/* net-core FUN_0103a2f8 @ 0x103a2f8  (parity 300 trials PROVEN) */
/* net-core FUN_0103a2f8 @ 0x103a2f8  (parity 300 trials PROVEN) */

typedef unsigned int uint32_t;
typedef unsigned long uintptr_t;
extern void z_log_dropped(uint32_t,uint32_t,uint32_t,uint32_t);
extern void FUN_0103b614(uint32_t,uint32_t,uint32_t);
extern void z_log_msg_commit(uint32_t);

void FUN_0103a2f8(uint32_t *param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
  if (param_1 == (uint32_t*)0) {
    z_log_dropped(0, param_4, param_3 >> 20, param_4);
    return;
  }
  if (param_4 != 0) {
    uint32_t off = (param_3 >> 9) & 0x7ffu;
    FUN_0103b614((uint32_t)(uintptr_t)param_1 + 0x10 + off, param_4, param_3 >> 20);
  }
  param_1[0] = param_3;
  param_1[1] = param_2;
  z_log_msg_commit((uint32_t)(uintptr_t)param_1);
}
