#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00058b78 @ 0x00058b78
 * public-name: att_chan_req_send_checked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_chan_req_send_checked                <= FUN_00058b78 @ 0x00058b78
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   chan_req_send                            <= FUN_00082030 @ 0x00082030
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f4388                             @ 0x000f4388
 *   rodata_f457a                             @ 0x000f457a   [INLINED -- G6 literal batch]
 *   rodata_f457f                             @ 0x000f457f   [INLINED -- G6 literal batch]
 *   rodata_f4589                             @ 0x000f4589   [INLINED -- G6 literal batch]
 *   rodata_f4590                             @ 0x000f4590
 */
/* Full reconstruction FUN_00058b78 @ 0x58b78, exact extent 108 bytes. */
#include <stdint.h>

extern void printk(uintptr_t, ...);
extern void assert_post_action(uintptr_t, uint32_t) __attribute__((noreturn));
extern void chan_req_send(void);

void att_chan_req_send_checked(uint8_t *context, uint32_t *object,
                  uint32_t arg2, uint32_t arg3)
{
    uint32_t line;
    uintptr_t message;
    (void)arg2;
    if (context == 0) {
        line = 0x37c; message = ((unsigned long)"chan") /*=0xf457a*/;
    } else if (object == 0) {
        line = 0x37d; message = ((unsigned long)&rodata_f4590) /*=0xf4590*/;
    } else if (object[1] == 0) {
        line = 0x37e; message = ((unsigned long)"req->func") /*=0xf457f*/;
    } else if (*(uint32_t *)(context + 0x124) != 0) {
        line = 0x37f; message = ((unsigned long)"!chan->req") /*=0xf4589*/;
    } else {
        chan_req_send();
        return;
    }
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, message, ((unsigned long)&rodata_f4388) /*=0xf4388*/, line, arg3);
    assert_post_action(((unsigned long)&rodata_f4388) /*=0xf4388*/, line);
}
