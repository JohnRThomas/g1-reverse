/* named: update_box_field_debounce */
/* globals referenced:
//   0x20007a10  g_box_last_seen_uptime       
*/
/* Reconstructed update_box_field_debounce @ 0x25474  (parity: 300/300 trials, PROVEN) */

extern int is_box_field_timer_expired(void);
extern int thunk_FUN_00074f68(void);

unsigned int update_box_field_debounce(void)
{
  volatile int *piVar1 = (volatile int *)0x20007a10UL;
  int iVar2 = is_box_field_timer_expired();
  unsigned int uVar3;
  if (iVar2 == 0) {
    iVar2 = thunk_FUN_00074f68();
    if (iVar2 - *piVar1 < 0) {
      thunk_FUN_00074f68();
    }
    uVar3 = 0;
  } else {
    iVar2 = thunk_FUN_00074f68();
    *piVar1 = iVar2;
    uVar3 = 1;
  }
  return uVar3;
}

