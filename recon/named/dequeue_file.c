/* named: dequeue_file */
/* globals referenced:
//   0x200079a0  g_file_msg_pipe              
*/
/* Reconstructed dequeue_file @ 0x235a4  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(unsigned int, void*, int, int);
extern void memcpy(unsigned int, void*, int);
extern void DEBUG_PRINT(unsigned int);

int dequeue_file(unsigned int param_1)
{
    unsigned char buf[208];
    int iVar1 = k_msgq_get(0x200079a0U, buf, 0, 0);
    if (iVar1 == 0) {
        memcpy(param_1, buf, 0xc9);
    } else {
        DEBUG_PRINT(0x9e85dU);
    }
    return iVar1;
}

