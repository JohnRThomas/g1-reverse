/* named: net_buf_push_le16 */
/* Reconstructed net_buf_push_le16 @ 0x83766  (parity: 300/300 trials, PROVEN) */

extern unsigned char *net_buf_simple_add(unsigned int a, unsigned int b);

void net_buf_push_le16(unsigned int param_1, unsigned int param_2)
{
    unsigned char *puVar1 = net_buf_simple_add(param_1, 2);
    puVar1[0] = (unsigned char)param_2;
    puVar1[1] = (unsigned char)(param_2 >> 8);
}

