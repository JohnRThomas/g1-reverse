/* readable reconstruction; identity: FUN_000332dc @ 0x000332dc
 * public-name: init_serial_port
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   init_serial_port                         <= FUN_000332dc @ 0x000332dc
 *   uart_read_start                          <= FUN_000336a0 @ 0x000336a0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_87bc0                             @ 0x00087bc0
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_a7892                             @ 0x000a7892
 *   rodata_a78b9                             @ 0x000a78b9
 *   rodata_a78d1                             @ 0x000a78d1
 *   rodata_a78eb                             @ 0x000a78eb
 *   g_serial_port_ready                      @ 0x2001a127
 */
/* Reconstructed FUN_000332dc @ 0x332dc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void*);
extern int z_device_is_ready(void*);
extern int uart_read_start(void*);
extern void assert_post_action(void*, int);
extern void printk(void*, void*, void*, int, unsigned int);

unsigned int init_serial_port(void)
{
  volatile unsigned char *pcVar1 = (volatile unsigned char*)0x2001a127UL;
  int iVar2;

  if (*pcVar1 == 0) {
    iVar2 = z_device_is_ready((void*)0x87bc0UL);
    if (iVar2 == 0) {
      printk((void*)0x99cbdUL, (void*)0xa78b9UL, (void*)0xa7892UL, 0x2e, 0);
      printk((void*)0xa78d1UL, 0, 0, 0, 0);
      assert_post_action((void*)0xa7892UL, 0x2e);
    }
    iVar2 = uart_read_start((void*)0x87bc0UL);
    if (iVar2 != 0) {
      *pcVar1 = 0;
      DEBUG_PRINT((void*)0xa78ebUL);
      return 0xffffffff;
    }
    *pcVar1 = 1;
  }
  return 0;
}
