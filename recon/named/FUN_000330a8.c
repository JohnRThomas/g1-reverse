/* named: FUN_000330a8 */
/* globals referenced:
//   0x20002424  g_fuel_gauge_dev             
*/
/* Reconstructed FUN_000330a8 @ 0x330a8  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_000330a8(unsigned int param_1)
{
    if (param_1 == 0) {
        return 0xffffffff;
    }
    if (*(volatile unsigned int*)0x20002424UL != param_1) {
        *(volatile unsigned int*)0x20002424UL = param_1;
    }
    *(volatile unsigned char*)0x2000242cUL = 0;
    return 0;
}

