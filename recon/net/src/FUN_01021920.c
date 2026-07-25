/* net-core FUN_01021920 @ 0x1021920  (parity 300 trials PROVEN)
 *
 * P4 iteration 27 CORRECTION -- byte evidence, not instruction shape.
 * The shipped thunk is
 *
 *     01021920  10b4  push {r4}
 *     01021922  034c  ldr  r4, [pc, #0xc]      ; = 0x21000530
 *     01021924  2468  ldr  r4, [r4]
 *     01021926  6468  ldr  r4, [r4, #4]
 *     01021928  a446  mov  ip, r4
 *     0102192a  10bc  pop  {r4}
 *     0102192c  6047  bx   ip
 *
 * i.e. it saves and restores r4 and tail-calls through ip, leaving r0-r3 and
 * the incoming stack frame untouched.  Its nine sibling thunks at
 * 0x010218b4..0x01021914 use r3 as the scratch register, so they have at most
 * THREE register arguments; this one does not, which is the byte evidence that
 * r3 is a LIVE FOURTH ARGUMENT here.
 *
 * The previous body was `void FUN_01021920(void) { fn(); }`, which GCC turns
 * into `ldr r3,[pc]; ldr r3,[r3]; ldr r3,[r3,#4]; bx r3` -- a tail call that
 * CLOBBERS r3 with the callee address.  The sole live caller FUN_01032ad8
 * passes five arguments, and the callee (ops[1]: shipped 0x01029d10, which
 * jumps to 0x01029cb6 and falls into 0x01029cbc) consumes r3 as `sxtb r1, r3`.
 * This is the documented harness-blind dropped-register-argument class: the
 * differential harness does not compare argument registers at an oracled
 * callee, so the wrong body proved.  Forwarding four register arguments makes
 * GCC emit the original's exact instruction sequence (push {r4} / load / mov ip
 * / pop {r4} / bx ip), which also preserves any stack arguments.
 */

typedef long long (*g1_net_radio_ops_fn)(unsigned long, unsigned long,
                                         unsigned long, unsigned long);

long long FUN_01021920(unsigned long a0, unsigned long a1,
                       unsigned long a2, unsigned long a3)
{
    g1_net_radio_ops_fn *ops =
        *(g1_net_radio_ops_fn *volatile *)0x21000530UL;
    return ops[1](a0, a1, a2, a3);
}
