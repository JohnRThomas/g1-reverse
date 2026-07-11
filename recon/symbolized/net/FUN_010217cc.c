/* Reconstructed internal net function FUN_010217cc @ 0x010217cc, 48 bytes. */
#include <stdint.h>
void FUN_010217cc(void){volatile uint8_t*s=(volatile uint8_t*)0x21001670u;unsigned d=s[10];if(!d){s[11]=0;return;}unsigned t=s[12],q=t/d;if(q<1)q=1;if(d<t&&t-d*(t/d))++q;s[11]=(uint8_t)q;}
