/* readable reconstruction; identity: FUN_00080bb2 @ 0x00080bb2
 * public-name: smp_reassembly_complete
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_rx_req                               <= FUN_00052744 @ 0x00052744
 *   smp_reassembly_complete                  <= FUN_00080bb2 @ 0x00080bb2
 */
/* Reconstructed FUN_00080bb2 @ 0x80bb2  (parity: 300/300 trials, PROVEN) */

extern void smp_rx_req(void *a);

unsigned int smp_reassembly_complete(int param_1, int param_2)
{
    unsigned int uVar1;
    if (*(volatile int*)(param_1+0x40) == 0) {
        uVar1 = 0xffffffea;
    } else {
        uVar1 = (unsigned int)*(volatile unsigned short*)(param_1+0x44);
        if ((uVar1 == 0) || (param_2 != 0)) {
            smp_rx_req((void*)param_1);
            *(volatile unsigned short*)(param_1+0x44) = 0;
            *(volatile unsigned int*)(param_1+0x40) = 0;
        } else {
            uVar1 = 0xffffffc3;
        }
    }
    return uVar1;
}
