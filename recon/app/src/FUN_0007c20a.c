/* Reconstructed FUN_0007c20a @ 0x7c20a  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void *a, unsigned int b, unsigned int c);
extern int FUN_00019c44(unsigned int);
extern short FUN_0000ef12(void *a);

unsigned int FUN_0007c20a(int param_1)
{
    short sVar1;
    int iVar2;
    struct queue_frame {
        unsigned char reserved[4];
        unsigned char control;
        unsigned char payload[203];
    } frame;

    while (1) {
        FUN_00086c78(frame.payload, 0, 0xca);
        frame.control = 0xf4;
        iVar2 = FUN_00019c44(frame.payload);
        if (iVar2 != 0) break;
        sVar1 = FUN_0000ef12(&frame.control);
        (*(void (**)(void *, unsigned short))(param_1 + 0xc))
            (&frame.control, (unsigned short)(sVar1 + 1));
    }
    return 0;
}
