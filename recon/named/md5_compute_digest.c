/* readable reconstruction; identity: FUN_0007d968 @ 0x0007d968
 * public-name: md5_compute_digest
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   md5_init                                 <= FUN_00049aa0 @ 0x00049aa0
 *   md5_final                                <= FUN_0004a16c @ 0x0004a16c
 *   md5_update                               <= FUN_0007d8f4 @ 0x0007d8f4
 *   md5_compute_digest                       <= FUN_0007d968 @ 0x0007d968
 */
/* Reconstructed FUN_0007d968 @ 0x7d968 */
#include <stdint.h>
extern void md5_init(void *workspace,uint32_t a,uint32_t b);
extern void md5_update(void);
extern void md5_final(int *, void *);
uint32_t md5_compute_digest(uint32_t a,uint32_t b,uint32_t *out){
  uint32_t result[4]; uint32_t workspace[22];
  md5_init(workspace,a,b); md5_update(); md5_final(workspace,result);
  for(unsigned i=0;i<4;i++)out[i]=result[i];
  return 0;
}
