/* named: log_dropped */
/* globals referenced:
//   0x000882b0  __settings_handler_static_list_start 
*/
/* Reconstructed log_dropped @ 0x4d4a8  (parity: 300/300 trials, PROVEN) */

extern unsigned int z_log_dropped_read_and_clear_0(void);
extern void assert_post_action(void*, int);
extern void printk(void*, void*, void*, int);

void log_dropped(void)
{
  unsigned int uVar2;
  int *r4 = (int*)0x882a0UL;
  int *r6 = (int*)0x882b0UL;

  uVar2 = z_log_dropped_read_and_clear_0();

  for (;;) {
    if ((unsigned int)r4 > (unsigned int)r6) {
      printk((void*)0x99cbdUL,(void*)0xf0cffUL,(void*)0xf0caeUL,0x1d1);
      printk((void*)0xf0d20UL, 0, 0, 0);
      assert_post_action((void*)0xf0caeUL,0x1d1);
    }
    if ((unsigned int)r4 >= (unsigned int)r6) break;
    if (*(char*)(*(int*)((char*)r4+4) + 5) != 0 && *(void**)(*(int*)r4 + 4) != 0) {
      void (*fn)(void*, unsigned int) = *(void**)(*(int*)r4 + 4);
      fn(r4, uVar2);
    }
    r4 = (int*)((char*)r4 + 0x10);
  }
  return;
}

