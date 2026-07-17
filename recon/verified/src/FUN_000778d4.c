/* app-core puts @ 0x000778d4.
 * Instructions end at 0x778de and the literal pool ends at 0x778e4;
 * 0x778e4 begins a separate wrapper. Raw backmap: FUN_000778d4. */
#include <stdint.h>
extern int _puts_r(void *reent, const char *text); /* FUN_00077820@0x00077820 */
int puts(const char *text){
    void *reent = *(void * volatile *)0x20002d20u;
    return _puts_r(reent, text);
}
