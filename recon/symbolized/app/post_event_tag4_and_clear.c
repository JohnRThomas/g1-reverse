#include "g1_app_symbols.h"
/* named: post_event_tag4_and_clear */
/* Reconstructed post_event_tag4_and_clear @ 0x84880  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *a, int b, unsigned int c);
extern void post_event_dispatch(unsigned int a, void *b);

void post_event_tag4_and_clear(unsigned int param_1, int *param_2)
{
    unsigned char local_24[20];
    int iVar1 = *param_2;
    if (iVar1 != 0) {
        memset_bytes(local_24, 0, 0x14);
        local_24[0] = 4;
        *(int*)(local_24+4) = iVar1;
        post_event_dispatch(param_1, local_24);
        *param_2 = 0;
    }
}

