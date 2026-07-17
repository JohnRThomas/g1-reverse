#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0001655c @ 0x0001655c
 * public-name: get_ambient_light_sensor_ready_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_ambient_light_sensor_ready_flag      <= FUN_0001655c @ 0x0001655c
 * address symbols (name @ address):
 *   g_ambient_light_sensor_ready             @ 0x200069f8
 */
/* Reconstructed FUN_0001655c @ 0x1655c  (parity: 300/300 trials, PROVEN) */

unsigned int get_ambient_light_sensor_ready_flag(void)
{
    return *(volatile unsigned int *)((unsigned long)&g_ambient_light_sensor_ready) /*=0x200069f8*/;
}
