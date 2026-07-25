/* Reconstructed FUN_0007cb66 @ 0x7cb66 */

/* Thin forwarding veneer over z_impl_k_thread_create (FUN_00071eac).  It takes
 * the four register arguments plus three of its own stack arguments --
 * p1 at sp+0x00, prio at sp+0x04 and a 64-bit k_timeout_t delay at sp+0x08 --
 * and re-lays them as the callee's ten-argument frame, hard-coding p2, p3 and
 * options to zero:
 *
 *   7cb66  push {r4,r5,lr} ; sub sp,#0x24
 *   7cb6a  ldrd r4,r5,[sp,#0x38]  ; caller delay (its own sp+0x08)
 *   7cb6e  strd r4,r5,[sp,#0x18]  ; callee delay
 *   7cb74  ldr  r5,[sp,#0x34]     ; caller prio  (its own sp+0x04)
 *   7cb76  str  r4,[sp,#0x10]     ; options = 0
 *   7cb78  strd r4,r5,[sp,#0x08]  ; p3 = 0, prio
 *   7cb7c  str  r4,[sp,#0x04]     ; p2 = 0
 *   7cb7e  ldr  r4,[sp,#0x30]     ; caller p1    (its own sp+0x00)
 *   7cb80  str  r4,[sp,#0x00]
 *
 * The previous reconstruction declared BOTH sides as taking no arguments, so
 * it compiled to a bare `b.w FUN_00071eac` that forwarded the caller's own
 * four-word outgoing block verbatim.  Every dispatch thread therefore reached
 * z_impl_k_thread_create with p2=prio, prio=0 and a garbage 64-bit delay. */
extern void FUN_00071eac(void*, void*, unsigned int, void*,
                         void*, void*, void*, int, unsigned int,
                         unsigned long long);

void FUN_0007cb66(void *thread, void *stack, unsigned int stack_size,
                  void *entry, void *p1, int prio, unsigned long long delay)
{
  FUN_00071eac(thread, stack, stack_size, entry, p1, 0, 0, prio, 0, delay);
}
