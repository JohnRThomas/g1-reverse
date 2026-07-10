/* named: get_box_field_state */
/* globals referenced:
//   0x20007a24  g_box_field_timer            
*/
/* Reconstructed get_box_field_state @ 0x25364  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
unsigned int get_box_field_state(void)
{
  unsigned int uVar2;
  if (*(volatile unsigned int *)0x20007a24UL <= 0x13ec) {
    uVar2 = 2;
  } else {
    int iVar1 = get_device_info();
    if (*(volatile unsigned char *)(iVar1 + 0xfc0) < 100) {
      uVar2 = 0;
    } else {
      uVar2 = 1;
    }
  }
  return uVar2;
}

