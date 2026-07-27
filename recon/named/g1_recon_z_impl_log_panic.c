/* readable reconstruction; identity: FUN_0004d678 @ 0x0004d678
 * public-name: g1_recon_z_impl_log_panic
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_msg_process                          <= FUN_0004d334 @ 0x0004d334
 *   log_process                              <= FUN_0004d594 @ 0x0004d594
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_882a0                             @ 0x000882a0
 *   __settings_handler_static_list_start     @ 0x000882b0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0cae                             @ 0x000f0cae
 *   rodata_f0cff                             @ 0x000f0cff   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 *   g_log_initialized_flag                   @ 0x2001d44c
 */
/* Reconstructed g1_recon_z_impl_log_panic @ 0x4d678.
 * Raw/address back-map: g1_recon_z_impl_log_panic <= FUN_0004d678 @ 0x0004d678.
 * Authoritative CFG verification supersedes the legacy 298/300 fuzz receipt.
 */
#include <stdint.h>
#include "../headers/g1_log.h"
extern int log_msg_process(int);
extern int log_process(void);
extern void assert_post_action(const char *, unsigned int);
void g1_recon_z_impl_log_panic(void){
  volatile uint8_t *pcVar1 = (volatile uint8_t*)0x2001d44cUL;
  if(*pcVar1 == 0){
    log_msg_process(1);
    uint32_t piVar4 = 0x000882a0;
    uint32_t piVar2 = 0x000882b0;
    while(1){
      if(piVar4 > piVar2){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"backend <= _log_backend_list_end"), 0x000f0cae, 0x188);
        printk(((unsigned long)"\tunexpected list end location\n"));
        assert_post_action(0x000f0cae, 0x188);
      }
      if(piVar4 == piVar2) break;
      uint32_t e = *(volatile uint32_t*)(piVar4+4);
      if(*(volatile uint8_t*)(e+5) != 0){
        uint32_t f = *(volatile uint32_t*)(*(volatile uint32_t*)piVar4 + 8);
        ((void(*)(uint32_t))(uintptr_t)f)(piVar4);
      }
      piVar4 += 0x10;
    }
    int iVar3;
    do { iVar3 = log_process(); } while(iVar3 != 0);
    *pcVar1 = 1;
  }
}
