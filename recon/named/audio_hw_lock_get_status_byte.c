/* named: audio_hw_lock_get_status_byte */
/* Reconstructed audio_hw_lock_get_status_byte @ 0x7ef1c  (parity: 300/300 trials, PROVEN) */

unsigned int audio_hw_lock_get_status_byte(int param_1, unsigned char *param_2)
{
    int p = *(int*)(param_1 + 0x14);
    if (p != 0) {
        *param_2 = *(unsigned char*)(p + 8);
        return 0;
    }
    return 0xffffffa8;
}

