/* named: ble_flush_queued_indications */
/* Reconstructed ble_flush_queued_indications @ 0x7c20a  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *a, unsigned int b, unsigned int c);
extern int dequeue_debug(void *a);
extern short strlen(void *a);

unsigned int ble_flush_queued_indications(int param_1)
{
    short sVar1;
    int iVar2;
    unsigned char local_d4;
    unsigned char auStack_d3[203];

    while (1) {
        memset_bytes(auStack_d3, 0, 0xca);
        local_d4 = 0xf4;
        iVar2 = dequeue_debug(auStack_d3);
        if (iVar2 != 0) break;
        sVar1 = strlen(&local_d4);
        (*(void (**)(void *, unsigned short))(param_1 + 0xc))(&local_d4, sVar1 + 1);
    }
    return 0;
}

