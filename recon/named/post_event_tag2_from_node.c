/* named: post_event_tag2_from_node */
/* Reconstructed post_event_tag2_from_node @ 0x8484e  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern void post_event_dispatch(int, void*);

void post_event_tag2_from_node(int param_1, unsigned int param_2)
{
    unsigned int iVar1 = *(volatile unsigned int*)(param_1 + 0x10);
    unsigned char buf[20];
    memset_bytes(buf, 0, 0x14);
    buf[0] = 2;
    unsigned int iVar1_2 = *(volatile unsigned int*)(iVar1 + 0xc);
    *(unsigned int*)(buf+4) = *(volatile unsigned int*)(iVar1_2 + 0x58);
    *(unsigned int*)(buf+8) = *(volatile unsigned int*)(iVar1_2 + 0x60);
    *(unsigned int*)(buf+12) = param_2;
    post_event_dispatch(param_1, buf);
}

