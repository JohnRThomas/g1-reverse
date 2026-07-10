/* Reconstructed FUN_0007c244 @ 0x7c244  (parity: 300/300 trials, PROVEN) */

extern int FUN_000181fc(void);
extern void ble_process_req_dispatch(unsigned int a, void *b, void *c, unsigned int d, void *e);

void FUN_0007c244(unsigned char *param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned char *puVar2 = param_1;
  unsigned int uStack_10 = param_3;
  (void)uStack_10;
  unsigned int uVar1 = FUN_000181fc();
  struct { unsigned char b0; unsigned char b1; unsigned short h; } loc;
  loc.b0 = *param_1;
  loc.b1 = 1;
  loc.h = (unsigned short)param_2;
  ble_process_req_dispatch(uVar1, &loc, param_1, 1, puVar2);
}

