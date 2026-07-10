/* named: set_uart_line_ctrl_dtr */
/* Reconstructed set_uart_line_ctrl_dtr @ 0x7c882  (parity: 300/300 trials, PROVEN) */

extern void FUN_00025670(void*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void set_uart_line_ctrl_dtr(void *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    FUN_00025670(param_1, (*(volatile unsigned short*)((char*)param_1 + 8)) | 4, param_2, param_3, param_4, param_2);
}

