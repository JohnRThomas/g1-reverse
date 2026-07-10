/* named: post_event_tag5 */
/* Reconstructed post_event_tag5 @ 0x848b0  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *a, int b, int c);
extern void post_event_dispatch(int a, void *b);
void post_event_tag5(int param_1)
{
  unsigned char local_1c[20];
  memset_bytes(local_1c, 0, 0x14);
  local_1c[0] = 5;
  post_event_dispatch(param_1, local_1c);
}

