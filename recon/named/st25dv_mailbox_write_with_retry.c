/* named: st25dv_mailbox_write_with_retry */
/* Reconstructed st25dv_mailbox_write_with_retry @ 0x24fe8  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007c3d0(unsigned short, unsigned int);
extern unsigned int st25dv_mailbox_send_message(void);

unsigned int st25dv_mailbox_write_with_retry(unsigned int param_1, unsigned short param_2)
{
    int iVar1;
    unsigned int uVar2;
    iVar1 = FUN_0007c3d0(param_2, param_1);
    if (iVar1 == -1) {
        *(volatile unsigned int*)0x20007a14UL = 0x014040e1U;
        uVar2 = st25dv_mailbox_send_message();
        FUN_0007c3d0(param_2, param_1);
    } else {
        uVar2 = 0;
    }
    return uVar2;
}

