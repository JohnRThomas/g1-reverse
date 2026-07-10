/* named: FUN_00053530 */
/* Reconstructed FUN_00053530 @ 0x53530  (parity: 300/300 trials, PROVEN) */

extern void net_buf_slist_put(unsigned int a, unsigned int b);
extern void FUN_00080ea2(unsigned int a, unsigned int b, void *c);
extern int k_work_submit_to_queue(unsigned int a, unsigned int b);

void FUN_00053530(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int local_20;
    unsigned int local_1c;
    int iStack_18;

    net_buf_slist_put(0x20002144UL, param_1);
    iStack_18 = k_work_submit_to_queue(0x20005f08UL, 0x20002980UL);
    if (iStack_18 < 0) {
        local_1c = 0x000f2ddbUL;
        local_20 = 3;
        FUN_00080ea2(0x00088138UL, 0x1840, &local_20);
    }
}

