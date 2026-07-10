/* named: get_ambient_light_sensor_ready_flag */
/* globals referenced:
//   0x200069f8  g_ambient_light_sensor_ready 
*/
/* Reconstructed get_ambient_light_sensor_ready_flag @ 0x1655c  (parity: 300/300 trials, PROVEN) */

unsigned int get_ambient_light_sensor_ready_flag(void)
{
    return *(volatile unsigned int *)0x200069f8UL;
}

