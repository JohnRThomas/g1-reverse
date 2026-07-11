/* Reconstructed FUN_0007d0e8 @ 0x7d0e8.
 * Complete 56-byte dispatcher; 0x7d120 starts the next function. */
#include <stdint.h>
extern int FUN_000258b4(int, void *, void *);
extern int FUN_00033554(int, void *, void *);

unsigned FUN_0007d0e8(int param_1, int param_2, void *param_3, void *param_4)
{
    if (param_2 == 0 || param_3 == 0 || param_4 == 0 || param_1 == 2)
        return 0xffffffff;
    if (param_1 == 0)
        return (unsigned)FUN_000258b4(param_2, param_3, param_4);
    if (param_1 == 1)
        return (unsigned)FUN_00033554(param_2, param_3, param_4);
    return 0;
}
