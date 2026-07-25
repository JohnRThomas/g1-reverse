/* net-core FUN_01032a3c @ 0x1032a3c  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB RX FIFO push @ 0x01032a3c (Ghidra gap, extent 0x88).  Stores one
 * received payload into the RX FIFO at 0x21004a34 -- length byte, pipe, RSSI
 * (RADIO RSSISAMPLE & 0x7f), the inverted no-ack bit and the PID -- copying the
 * body from the staging buffer 0x21006260 with __memcpy_chk.  Returns 0 when a
 * DPL length exceeds 251.
 */
extern void FUN_0103b614(unsigned int dst, unsigned int src, unsigned int n);

unsigned int FUN_01032a3c(unsigned int pipe, unsigned int pid)
{
    volatile unsigned char *cfg = (volatile unsigned char *)0x21004a94u;
    volatile unsigned char *hdr = (volatile unsigned char *)0x2100625eu;
    volatile unsigned int *fifo = (volatile unsigned int *)0x21004a34u;
    volatile unsigned char *buf;
    unsigned int idx, len, rssi, h;

    if (cfg[0] == 1u) {
        len = hdr[0];
        if (len > 0xfbu)
            return 0u;
        buf = (volatile unsigned char *)fifo[fifo[0x20u / 4u]];
        buf[0] = (unsigned char)len;
    } else {
        buf = (volatile unsigned char *)fifo[fifo[0x20u / 4u]];
        if (cfg[1] != 0u)
            buf[0] = cfg[0x11];
        else
            buf[0] = 0u;
    }

    idx = fifo[0x20u / 4u];
    buf = (volatile unsigned char *)fifo[idx];
    idx = idx + 1u;
    len = buf[0];
    FUN_0103b614((unsigned int)buf + 5u, 0x21006260u, len);
    buf[1] = (unsigned char)pipe;
    rssi = *(volatile unsigned int *)(0x41008000u + 0x548u);
    buf[4] = (unsigned char)pid;
    buf[2] = (unsigned char)(rssi & 0x7fu);
    h = hdr[1];
    if (idx >= 8u)
        idx = 0u;
    buf[3] = (unsigned char)((~h) & 1u);
    fifo[0x20u / 4u] = idx;
    fifo[0x28u / 4u] = fifo[0x28u / 4u] + 1u;
    return 1u;
}
