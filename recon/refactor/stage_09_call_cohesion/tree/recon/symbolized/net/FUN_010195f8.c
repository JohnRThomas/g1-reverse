#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010195f8 @ 0x010195f8
 * public-name: FUN_010195f8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_buffer_payload_get                   <= FUN_010270d2 @ 0x010270d2
 *   sdc_buffer_descriptor_resolve            <= FUN_0102714a @ 0x0102714a
 * address symbols (name @ address):
 *   g_ll_conn_default_ctx                    @ 0x21001058
 */
/* net-core FUN_010195f8 @ 0x10195f8  (parity 300 trials PROVEN) */

extern unsigned int FUN_0100a5a0(void);
extern void sdc_buffer_descriptor_resolve(unsigned int, void *, void *);
extern int sdc_buffer_payload_get(unsigned int);

void FUN_010195f8(void)
{
    unsigned char buf[12];
    unsigned int uVar2;
    int iVar3, iVar1;
    uVar2 = FUN_0100a5a0();
    sdc_buffer_descriptor_resolve(uVar2, (void*)(buf+4), (void*)(buf+2));
    iVar3 = sdc_buffer_payload_get(*(unsigned int*)(buf+4));
    *(volatile unsigned int *)(iVar3+0x1a)=0;
    *(volatile unsigned int *)(iVar3+0x2a)=0;
    *(volatile unsigned char *)(iVar3+0x2c)=0x7f;
    *(volatile unsigned int *)(iVar3+0x12)=0;
    *(volatile unsigned int *)(iVar3+0x1e)=0;
    *(volatile unsigned int *)(iVar3+0x22)=0;
    *(volatile unsigned char *)(iVar3+0x20)=0xff;
    *(volatile unsigned char *)(iVar3+0x13)=0xff;
    *(volatile unsigned char *)(iVar3+0x25)=0xff;
    unsigned char r1b = *(volatile unsigned char *)(iVar3+0x1c);
    r1b = (r1b & 0x9f) | 0x20;
    iVar1 = ((unsigned long)&g_ll_conn_default_ctx) /*=0x21001058*/;
    *(volatile unsigned int *)(iVar3+0x16)=0;
    *(volatile unsigned int *)(iVar3+0x26)=0;
    *(volatile unsigned char *)(iVar3+0x1c)=r1b;
    *(volatile unsigned int *)(iVar1+0x40)=0;
    *(volatile unsigned short *)(iVar1+0x44)=0;
}
