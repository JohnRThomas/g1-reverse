#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084d36 @ 0x00084d36
 * public-name: reset_state_and_stop_timer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   reset_state_and_stop_timer               <= FUN_00084d36 @ 0x00084d36
 */
/* Reconstructed FUN_00084d36 @ 0x84d36  (parity: 300/300 trials, PROVEN) */

extern char *FUN_00063bcc(void);
extern void FUN_0004f770(void);
extern void FUN_00063c14(int a);
void reset_state_and_stop_timer(void) {
    char *p = FUN_00063bcc();
    *(volatile unsigned char*)(p + 8) = 0;
    FUN_0004f770();
    FUN_00063c14(5);
}
