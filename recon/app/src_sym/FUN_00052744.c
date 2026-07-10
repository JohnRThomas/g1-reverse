/* Reconstructed FUN_00052744 @ 0x52744  (parity: 300/300 trials, PROVEN) */

extern void FUN_0005f200(unsigned int a);
extern void k_work_submit_to_queue(unsigned int a, unsigned int b);

void FUN_00052744(int param_1)
{
    FUN_0005f200(param_1 + 0x10);
    k_work_submit_to_queue(0x20005bb8U, param_1);
}

