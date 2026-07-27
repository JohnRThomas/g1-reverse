#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00047ba8 @ 0x00047ba8
 * public-name: send_response_data_to_ble
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   send_response_data_to_ble                <= FUN_00047ba8 @ 0x00047ba8
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_ef736                             @ 0x000ef736   [INLINED -- G6 literal batch]
 *   g_dashboard_response_msgq                @ 0x2000392c
 */
/* Reconstructed FUN_00047ba8 @ 0x47ba8  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void memset_bytes(void*, int, int);
extern unsigned int k_msgq_put(int, unsigned int, int, int);

/* P4 iteration 33 -- UNDERSIZED STACK FRAME FIXED (instance 18 of the class the
 * parity harness is structurally blind to).  Shipped bytes @ 0x47ba8:
 *
 *   push {r0,r1,r2,r3,r4,r5,r6,lr}   ; 32-BYTE frame, 24-byte msg at sp+0
 *   bl get_device_info ; ldrb r3,[r0] ; cmp r3,#2 ; beq -> return 0
 *   movs r2,#23 ; movs r1,#0 ; add r0,sp,#1 ; bl memset_bytes
 *   movs r3,#1 ; strb.w r3,[sp]                       ; msg[0] = 1, msg[1..23] = 0
 *   mov r1,sp ; ldr r0,=0x2000392c ; bl k_msgq_put
 *   add sp,#28 ; ldr.w pc,[sp],#4
 *
 * The previous spelling used four `unsigned int` locals seeded from the four
 * parameters; GCC packed them into a 16-byte `push {r0,r1,r2,lr}` frame, so the
 * 23-byte memset overran to sp+27 and destroyed the saved LR at sp+12.  Once
 * `g_display_msgq` started working and `ui_navigation_task` actually ran, that
 * popped PC = 0 -> UsageFault K_ERR_ARM_USAGE_ILLEGAL_EPSR (reason 35) at our
 * 0x41ffe and rebooted the SoC.  It also leaked param_1's upper three bytes
 * into msg[1..3]; the shipped code zeroes them.  Every caller already declares
 * this function with no parameters (the shipped prologue's r0-r3 are pure spill
 * space that nothing reads), so the signature is `void`. */
unsigned int send_response_data_to_ble(void)
{
  unsigned char msg[24];
  char *pcVar1 = get_device_info();
  if (*pcVar1 != 2) {
    memset_bytes(msg + 1, 0, 0x17);
    msg[0] = 1;
    int iVar2 = k_msgq_put(((unsigned long)&g_dashboard_response_msgq) /*=0x2000392c*/, msg, 0, 0);
    if (iVar2 != 0) {
      log_message(((unsigned long)"message queue send failed %s\r\n") /*=0xef058*/, ((unsigned long)"send_response_data_to_ble") /*=0xef736*/);
      return 0xffffffff;
    }
  }
  return 0;
}
