/* Reconstructed FUN_000858ca @ 0x858ca  (parity: 300/300 trials, PROVEN) */

typedef void (*fnptr)(void);
void rpmsg_release_rx_buffer(int param_1,int param_2)
{
  fnptr f;
  if ((param_1 != 0) && (*(int *)(param_1 + 0x20) != 0) && (param_2 != 0) &&
      (f = *(fnptr *)(*(int *)(param_1 + 0x20) + 0x7c), f != (fnptr)0)) {
    f();
  }
}

