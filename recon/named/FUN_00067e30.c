/* readable reconstruction; identity: FUN_00067e30 @ 0x00067e30
 * public-name: FUN_00067e30
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f7052                             @ 0x000f7052
 *   rodata_f79c8                             @ 0x000f79c8
 *   rodata_f7a1b                             @ 0x000f7a1b
 *   m_dppi_channels                          @ 0x2000b41c
 */
/* Full reconstruction FUN_00067e30 @ 0x67e30, exact extent 70 bytes. */
#include <stdint.h>
extern void printk(uintptr_t,uintptr_t,uintptr_t,uint32_t,...);
extern __attribute__((noreturn)) void assert_post_action(uintptr_t,uint32_t);
void FUN_00067e30(uintptr_t *device,uint32_t a,uint32_t b,uint32_t context){
 (void)a;(void)b;uint32_t ch=((uint8_t*)device)[4];volatile uint8_t *s=(volatile uint8_t*)(0x2000b41cu+ch*8u);
 if(s[1]==0){printk(0x00099cbdu,0x000f7a1bu,0x000f79c8u,0x8c,context);assert_post_action(0x000f79c8u,0x8c);}
 if(s[0]==1){*(volatile uint32_t*)*device=1;s[0]=2;return;}
 printk(0x00099cbdu,0x000f7052u,0x000f79c8u,0x8d,context);assert_post_action(0x000f79c8u,0x8d);
}
