/* named: settings_nvs_delete_id */
/* Reconstructed settings_nvs_delete_id @ 0x7e9d4  (parity: 300/300 trials, PROVEN) */

extern void nvs_write(unsigned int, unsigned int, unsigned int);
void settings_nvs_delete_id(unsigned int param_1, unsigned int param_2)
{
    nvs_write(param_1, param_2, 0);
}

