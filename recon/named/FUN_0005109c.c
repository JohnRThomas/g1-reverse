/* named: FUN_0005109c */
/* Reconstructed FUN_0005109c @ 0x5109c  (parity: 300/300 trials, PROVEN) */

extern int malloc(int);
extern void assert_post_action(void*, unsigned int);
extern void printk(void*, void*, void*, int);
extern void kmutex_dlist_init(void);

void FUN_0005109c(int *param_1)
{
  int iVar1;
  unsigned int uVar2;

  if (param_1 == 0) {
    printk((void*)0x99cbdUL, (void*)0xf23d4UL, (void*)0xf22d5UL, 0x179);
    uVar2 = 0x179;
    assert_post_action((void*)0xf22d5UL, uVar2);
  }
  iVar1 = malloc(0x14);
  *param_1 = iVar1;
  if (iVar1 != 0) {
    kmutex_dlist_init();
    return;
  }
  printk((void*)0x99cbdUL, (void*)0xf23d3UL, (void*)0xf22d5UL, 0x181);
  printk((void*)0xf240fUL, 0,0,0);
  uVar2 = 0x181;
  assert_post_action((void*)0xf22d5UL, uVar2);
}

