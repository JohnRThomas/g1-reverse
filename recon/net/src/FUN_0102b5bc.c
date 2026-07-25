/* net-core FUN_0102b5bc @ 0x102b5bc  (parity 300 trials PROVEN)
 * CFG_VERIFY_PREFIX_FIRST: the successful submission path busy-waits for an
 * asynchronous completion flag written by hardware/ISR code. */
#define P_0102b640 0x21004628
#define C_0102b644 0xf0000010
#define P_0102b648 0x21004fa2
#define C_0102b64c 0x418c0500
#define P_0102b650 0x21000580
#define P_0102b654 0x0103d18c
#define P_0102b658 0x0103d19e
#define P_0102b65c 0x0103d1b8
/* P4 iteration 23 — CODE pointer: the shipped literal 0x0102bf59 is
 * (analysis 0x0102b758 + 0x800) | 1 = FUN_0102b758, the ESB clock-transition
 * callback.  Parity keeps the literal; the cohesive build must use the
 * linker-resolved address or the callback is never invoked (measured: the whole
 * ESB transport chain ran zero times).  See recon/symbolized/net/FUN_0102b5bc.c. */
#ifdef G1_COHESIVE_BUILD
extern void FUN_0102b758(unsigned int);
#define P_0102b660 ((unsigned long)&FUN_0102b758)
#else
#define P_0102b660 0x0102bf59
#endif

extern int FUN_0103037c(int);
extern int FUN_0102ca80(int, void *);
extern void FUN_01039722(int, int);
extern void FUN_0102bba8(int);

/* P4 iteration 21 - the on-stack `struct onoff_client` must be ONE contiguous
 * 16-byte object.  The shipped prologue is `push {r0, r1, r2, r3, r4, lr}`,
 * i.e. the four incoming arguments ARE the client's initial image, and every
 * later access is an sp-relative field of that same object:
 *     sp+0x00  sys_snode_t node
 *     sp+0x04  sys_notify.method   (str r3,[sp,#4]   with r3 = 0)
 *     sp+0x08  sys_notify.flags    (str r3,[sp,#8]   with r3 = 1 = SPINWAIT)
 *     sp+0x0c  sys_notify.result   (str r3,[sp,#0xc] with r3 = 0)
 * and `mov r1, sp` passes &client to onoff_request.
 * The previous rendering declared four INDEPENDENT locals and took the address
 * of the first one only, so the compiler was free to place `method`, `flags`
 * and `result` anywhere; measured in /private/tmp/g1-i20d-net the client that
 * reached onoff_request had notify.flags = 0x2100C370 (a stack address) and
 * validate_args() returned -EINVAL, which made esb_service_init() fail and
 * CPUNET main() return before it could send the 0x0601 IPC message.
 * The shipped code also reloads `result` from sp+0xc AFTER the spin-wait
 * (0x102b61e `ldr r4,[sp,#0xc]`); Ghidra hoisted that read above the loop. */
struct g1_onoff_client {
    unsigned int node;              /* +0x00 */
    unsigned int method;            /* +0x04 */
    volatile unsigned int flags;    /* +0x08 */
    volatile int result;            /* +0x0c */
};

int FUN_0102b5bc(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  struct g1_onoff_client client;
  int manager;
  int status;
  int result;

  *(volatile unsigned int *)P_0102b640 = param_2;
  *(volatile unsigned char *)P_0102b648 = (unsigned char)param_1;
  *(volatile unsigned int *)(C_0102b64c + 0x18) = C_0102b644;
  *(volatile unsigned int *)(C_0102b64c + 0xc) = 0xf0000000;

  client.node = param_1;
  client.method = param_2;
  client.flags = param_3;
  client.result = (int)param_4;

  manager = FUN_0103037c(0);
  if (manager == 0) {
    if (0 < *(volatile int *)P_0102b650) {
      FUN_01039722(P_0102b654, 0);
    }
    return -6;
  }

  client.method = 0;
  client.result = 0;
  client.flags = 1;
  status = FUN_0102ca80(manager, &client);
  if (status < 0) {
    if (0 < *(volatile int *)P_0102b650) {
      FUN_01039722(P_0102b658, status);
    }
    return status;
  }

  while ((client.flags & 3) != 0) { }
  result = client.result;
  if (result != 0) {
    if (0 < *(volatile int *)P_0102b650) {
      FUN_01039722(P_0102b65c, result);
    }
    if (result < 0) {
      return result;
    }
  }
  FUN_0102bba8(P_0102b660);
  return 0;
}
