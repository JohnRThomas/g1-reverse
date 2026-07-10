/* named: FUN_00025448 */
/* globals referenced:
//   0x20007a24  g_box_field_timer            
*/
/* Reconstructed FUN_00025448 @ 0x25448  (parity: 300/300 trials, PROVEN) */

extern void refresh_box_field_timer(void);
unsigned int FUN_00025448(void)
{
  refresh_box_field_timer();
  return *(volatile unsigned int *)0x20007a24UL;
}

