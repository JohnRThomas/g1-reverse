/* readable reconstruction; identity: FUN_00086f5a @ 0x00086f5a
 * public-name: libc_stream_write_syscall
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   libc_stream_write_syscall                <= FUN_00086f5a @ 0x00086f5a
 */
/* Reconstructed FUN_00086f5a @ 0x86f5a  (parity: 300/300 trials, PROVEN) */
extern void FUN_00078598(int* a, int b, int c, int d);
extern int tail_77d30(int* a, int b, int c, int d);
void libc_stream_write_syscall(int* param_1, int param_2, int param_3, int param_4){
    unsigned short v = *(unsigned short*)(param_2 + 0xc);
    if ((int)((unsigned)v << 0x17) < 0){
        FUN_00078598(param_1, (int)*(short*)(param_2 + 0xe), 0, 2);
    }
    unsigned short w = *(unsigned short*)(param_2 + 0xc);
    short s = *(short*)(param_2 + 0xe);
    w = w & 0xefff;
    *(unsigned short*)(param_2 + 0xc) = w;
    tail_77d30(param_1, (int)s, param_3, param_4);
}
