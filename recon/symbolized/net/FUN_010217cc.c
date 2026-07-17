#include "g1_net_symbols.h"
/* Reconstructed internal net function FUN_010217cc @ 0x010217cc.
 * Code [0x010217cc,0x010217fc), 48 bytes; one literal occupies
 * [0x010217fc,0x01021800), before FUN_01021800. */
#include <stdint.h>
void FUN_010217cc(void)
{
    volatile uint8_t *state=(volatile uint8_t *)0x21001670u;
    unsigned divisor=state[10];
    if(divisor==0){state[11]=0;return;}
    unsigned total=state[12];
    unsigned quotient=total/divisor;
    if(quotient<1) quotient=1;
    if(divisor<total && total-divisor*(total/divisor)!=0) ++quotient;
    state[11]=(uint8_t)quotient;
}
