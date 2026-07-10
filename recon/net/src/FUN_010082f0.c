/* net-core FUN_010082f0 @ 0x10082f0  (parity 300 trials PROVEN) */
unsigned long long FUN_010082f0(unsigned int *param_1, unsigned int *param_2, int param_3)
{
    volatile unsigned int *out = (volatile unsigned int *)param_1;
    unsigned int mask = (unsigned int)(-param_3);

    unsigned int s0 = param_1[0], s1 = param_1[1], s2 = param_1[2], s3 = param_1[3];
    unsigned int b0 = param_2[0] & mask, b1 = param_2[1] & mask,
                 b2 = param_2[2] & mask, b3 = param_2[3] & mask;
    unsigned int r0v = s0 + b0;
    unsigned int c0 = r0v < s0;
    unsigned int r1v = s1 + b1 + c0;
    unsigned int c1 = (s1 + b1 < s1) || (r1v < c0);
    unsigned int r2v = s2 + b2 + c1;
    unsigned int c2 = (s2 + b2 < s2) || (r2v < c1);
    unsigned int r3v = s3 + b3 + c2;
    unsigned int c3 = (s3 + b3 < s3) || (r3v < c2);
    out[0] = r0v; out[1] = r1v; out[2] = r2v; out[3] = r3v;

    unsigned int s4 = param_1[4], s5 = param_1[5], s6 = param_1[6], s7 = param_1[7];
    unsigned int b4 = param_2[4] & mask, b5 = param_2[5] & mask,
                 b6 = param_2[6] & mask, b7 = param_2[7] & mask;
    unsigned int r4v = s4 + b4 + c3;
    unsigned int c4 = (s4 + b4 < s4) || (r4v < c3);
    unsigned int r5v = s5 + b5 + c4;
    unsigned int c5 = (s5 + b5 < s5) || (r5v < c4);
    unsigned int r6v = s6 + b6 + c5;
    unsigned int c6 = (s6 + b6 < s6) || (r6v < c5);
    unsigned int r7v = s7 + b7 + c6;
    unsigned int c7 = (s7 + b7 < s7) || (r7v < c6);
    out[4] = r4v; out[5] = r5v; out[6] = r6v; out[7] = r7v;

    return ((unsigned long long)(unsigned int)(unsigned long)(param_2 + 8) << 32) |
           (unsigned long long)c7;
}


