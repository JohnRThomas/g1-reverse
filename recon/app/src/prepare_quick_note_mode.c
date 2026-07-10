/* Reconstructed prepare_quick_note_mode @ 0x7cdb6  (parity: 300/300 trials, PROVEN) */

extern int FUN_0002bed0(void);
extern void FUN_0002c0e8(void);
extern void FUN_00086c78(void);
extern void send_event_status(void);

void prepare_quick_note_mode(unsigned char *param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1 = FUN_0002bed0();
    if ((iVar1 != 0) && ((param_1[0xd5]==6) || (param_1[0xd5]==4))) {
        if (param_2 != 0) {
            send_event_status();
        }
        FUN_0002c0e8();
        FUN_00086c78();
        return;
    }
    return;
}

