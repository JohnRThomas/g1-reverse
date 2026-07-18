/* Reconstructed FUN_0004ea28 @ 0x4ea28  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c04(int,void*,int);
extern int FUN_0004e8e8(int);
extern int FUN_0004e98c(int);
extern void FUN_0007f406(int,int,void*);

#define get_uuid_size FUN_0004e98c
#define user_data_alloc FUN_0004e8e8
#define memcpy FUN_00086c04

int uuid_store(unsigned char *param_1)
{
    /* This is one two-word log argument record.  Keeping the words in a
     * single object preserves the firmware ABI: the logger receives the
     * address of word 0 (severity), followed immediately by the message ID. */
    int log_args[2];
    int uVar1, iVar2;
    if (param_1 == 0) {
        log_args[1] = 0x000f1270;
    } else {
        uVar1 = get_uuid_size(*param_1);
        iVar2 = user_data_alloc(uVar1);
        if (iVar2 != 0) {
            memcpy(iVar2, param_1, uVar1);
            return iVar2;
        }
        log_args[1] = 0x000f1284;
    }
    log_args[0] = 2;
    FUN_0007f406(0x00088130, 0x1040, log_args);
    return 0;
}
