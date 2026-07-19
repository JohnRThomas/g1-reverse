#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_libc_FILE_stream__param_0742           [param_0742; library]
 * Raw function identity: 0x00086f5a.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00086f5a @ 0x00086f5a
 * public-name: libc_stream_write_syscall
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lseek_r_capture_errno                    <= FUN_00078598 @ 0x00078598
 *   libc_stream_write_syscall                <= FUN_00086f5a @ 0x00086f5a
 */
/* Reconstructed FUN_00086f5a @ 0x86f5a  (parity: 300/300 trials, PROVEN) */
extern void lseek_r_capture_errno(int* a, int b, int c, int d);
extern int _write_r(int* a, int b, int c, int d);
void libc_stream_write_syscall(int* param_1, int param_2, int param_3, int param_4){
    unsigned short v = *(unsigned short*)(param_2 + 0xc);
    if ((int)((unsigned)v << 0x17) < 0){
        lseek_r_capture_errno(param_1, (int)*(short*)(param_2 + 0xe), 0, 2);
    }
    unsigned short w = *(unsigned short*)(param_2 + 0xc);
    short s = *(short*)(param_2 + 0xe);
    w = w & 0xefff;
    *(unsigned short*)(param_2 + 0xc) = w;
    _write_r(param_1, (int)s, param_3, param_4);
}
