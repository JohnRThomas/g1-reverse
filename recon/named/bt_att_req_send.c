/* readable reconstruction; identity: FUN_00059a90 @ 0x00059a90
 * public-name: bt_att_req_send
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_get                                  <= FUN_0005858c @ 0x0005858c
 *   bt_att_req_send                          <= FUN_00059a90 @ 0x00059a90
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   att_req_send_process                     <= FUN_000820ae @ 0x000820ae
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f3ebd                             @ 0x000f3ebd
 *   rodata_f4388                             @ 0x000f4388
 *   rodata_f4590                             @ 0x000f4590
 */
/* Reconstructed FUN_00059a90 @ 0x59a90  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
extern int assert_post_action(int, int);
extern int att_get(void);
extern void att_req_send_process(void);
unsigned bt_att_req_send(int param_1, unsigned* param_2){
    unsigned r1;
    if (param_1 != 0){
        r1 = (unsigned)(uintptr_t)param_2;
    } else {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0xf3ebd,0xf4388,0xf38);
        long long r = assert_post_action(0xf4388, 0xf38);
        r1 = (unsigned)((unsigned long long)r >> 32);
    }
L_aae:
    if (r1 != 0) goto L_ac4;
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0xf4590,0xf4388,0xf39);
    { long long r = assert_post_action(0xf4388, 0xf39);
      r1 = (unsigned)((unsigned long long)r >> 32); }
    goto L_aae;
L_ac4:
    {
        int iVar1 = att_get();
        if (iVar1 == 0) return 0xffffff80;
        *param_2 = 0;
        unsigned* r3 = *(unsigned**)(iVar1 + 8);
        if (r3 == 0){
            *(unsigned**)(iVar1 + 4) = param_2;
            *(unsigned**)(iVar1 + 8) = param_2;
        } else {
            *r3 = (unsigned)(uintptr_t)param_2;
            *(unsigned**)(iVar1 + 8) = param_2;
        }
        att_req_send_process();
        return 0;
    }
}
