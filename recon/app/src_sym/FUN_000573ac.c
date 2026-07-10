/* Reconstructed FUN_000573ac @ 0x573ac  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(unsigned int, unsigned int, unsigned int);
extern void net_pkt_skip(unsigned int, unsigned int);

void FUN_000573ac(unsigned int param_1)
{
    memset_bytes(param_1, 0, 0x10);
    net_pkt_skip(0x20003a44UL, param_1);
}

