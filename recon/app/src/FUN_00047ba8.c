/* Reconstructed FUN_00047ba8 @ 0x47ba8  (parity: 300/300 trials, PROVEN)
 *
 * P4 iteration 33 -- UNDERSIZED STACK FRAME FIXED (instance 18 of the class the
 * parity harness is structurally blind to: it compares ABI returns, non-stack
 * memory writes and call order, so a stack buffer that runs off the end of the
 * frame is invisible to it).
 *
 * Shipped bytes (app_update.bin @ 0x47ba8):
 *
 *   47ba8  push {r0,r1,r2,r3,r4,r5,r6,lr}  ; 32-BYTE frame, msg buffer at sp+0
 *   47baa  bl   0x167a8                    ; get_device_info
 *   47bae  ldrb r3,[r0,#0] ; cmp r3,#2 ; beq -> return 0
 *   47bbc  movs r2,#23 ; movs r1,#0 ; add r0,sp,#1 ; bl 0x86c78   ; memset(sp+1,0,23)
 *   47bc8  movs r3,#1  ; strb.w r3,[sp]                            ; msg[0] = 1
 *   47bce  movs r2,#0 ; movs r3,#0 ; mov r1,sp ; ldr r0,=0x2000392c ; bl 0x720d0
 *   47bda  cmp r0,#0 ; beq -> return 0 ; else log + return -1
 *   47bb6  add sp,#28 ; ldr.w pc,[sp],#4
 *
 * The message is 24 bytes and lives at sp+0 inside a 32-byte frame, so the
 * saved LR at sp+28 is never touched.  The previous reconstruction spelled the
 * buffer as four `unsigned int` locals seeded from the four parameters, which
 * GCC laid out in a 16-byte `push {r0,r1,r2,lr}` frame; the 23-byte memset then
 * ran from sp+5 to sp+27 and DESTROYED the return address at sp+12 (and 12
 * bytes of the caller's frame).  Measured consequence, once the display message
 * queue started working (see report iteration 33): `ui_navigation_task` ->
 * `send_response_data_to_ble` -> `ldr.w pc,[sp],#4` popped PC = 0, i.e. a
 * UsageFault `K_ERR_ARM_USAGE_ILLEGAL_EPSR` (reason 35) at our 0x41ffe, which
 * with CONFIG_RESET_ON_FATAL_ERROR rebooted the SoC ~5.9 s into the run.
 *
 * The shipped code also zeroes msg[1..3] BEFORE storing msg[0] = 1, so the
 * first word of the message is exactly 0x00000001; the old spelling leaked the
 * upper three bytes of param_1 into it.  Both are fixed here.
 *
 * The four incoming registers are pure spill space in the shipped prologue --
 * nothing ever reads them -- and every caller already declares this function
 * with no parameters, so the signature is `void`.
 */

extern char* FUN_000167a8(void);
extern void FUN_00086c78(void*, int, int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int);

unsigned int FUN_00047ba8(void)
{
  unsigned char msg[24];
  char *pcVar1 = FUN_000167a8();
  if (*pcVar1 != 2) {
    FUN_00086c78(msg + 1, 0, 0x17);
    msg[0] = 1;
    int iVar2 = FUN_000720d0(0x2000392c, msg, 0, 0);
    if (iVar2 != 0) {
      DEBUG_PRINT(0xef058, 0xef736);
      return 0xffffffff;
    }
  }
  return 0;
}
