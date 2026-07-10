/* named: sensor_channel_get_trampoline */
/* Reconstructed sensor_channel_get_trampoline @ 0x7cef6  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(void);
void sensor_channel_get_trampoline(int param_1)
{
    fn_t f = *(fn_t*)(*(int*)(param_1 + 8) + 0x10);
    f();
}

