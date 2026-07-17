/* readable reconstruction; identity: FUN_0004ab3c @ 0x0004ab3c
 * public-name: burial_point_record_info_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_f0416                             @ 0x000f0416
 *   rodata_f043b                             @ 0x000f043b
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed burial_point_record_info_init @ 0x4ab3c */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t, uint32_t);
extern void debug_print(uint32_t, uint32_t);
extern uint8_t *get_device_info(void);
extern void *memset_bytes(void *, int, uint32_t);

void burial_point_record_info_init(void)
{
  if (*(volatile int32_t *)0x2000230c > 2) {
    if (*(volatile uint32_t *)0x20007554 == 0) {
      DEBUG_PRINT(0x000f0416, 0x000f043b);
    } else {
      debug_print(0x000f0416, 0x000f043b);
    }
  }

  uint8_t *runtime = get_device_info();
  memset_bytes(runtime + 0x1092, 0, 0x1a);
  runtime = get_device_info();
  memset_bytes(runtime + 0x10ac, 0, 0x1a);
}
