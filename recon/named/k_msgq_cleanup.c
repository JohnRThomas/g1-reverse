/* readable reconstruction; identity: FUN_00086480 @ 0x00086480
 * public-name: k_msgq_cleanup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_msgq_cleanup                           <= FUN_00086480 @ 0x00086480
 */
/* Reconstructed FUN_00086480 @ 0x86480  (parity: 300/300 trials, PROVEN) */

extern void FUN_000868b4(int);

int k_msgq_cleanup(int *param_1)
{
    int v0 = *(volatile int*)param_1;
    if (param_1 == (int*)v0 || v0 == 0) {
        unsigned char flag = *(volatile unsigned char*)((char*)param_1 + 0x30);
        if ((int)((unsigned int)flag << 31) < 0) {
            int arg = *(volatile int*)((char*)param_1 + 0x14);
            FUN_000868b4(arg);
            unsigned char flag2 = *(volatile unsigned char*)((char*)param_1 + 0x30);
            *(volatile unsigned char*)((char*)param_1 + 0x30) = flag2 & 0xfe;
        }
        return 0;
    } else {
        return (int)0xfffffff0;
    }
}
