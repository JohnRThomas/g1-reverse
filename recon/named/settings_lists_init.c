/* named: settings_lists_init */
/* globals referenced:
//   0x2000a10c  g_settings_handlers          
*/
/* Reconstructed settings_lists_init @ 0x4e484  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef struct { unsigned int a; unsigned int b; } S;
extern void FUN_0004e474(void);

void settings_lists_init(void)
{
    volatile S *p1 = (volatile S *)0x2000a10cUL;
    p1->a = 0;
    p1->b = 0;
    FUN_0004e474();
}

