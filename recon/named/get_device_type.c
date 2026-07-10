/* named: get_device_type */
/* globals referenced:
//   0x200069fc  device_info                  
*/
/* Reconstructed get_device_type @ 0x16568  (parity: 300/300 trials, PROVEN) */

unsigned char get_device_type(void)
{
  return *(volatile unsigned char *)(*(volatile unsigned int *)0x200069fcUL);
}

