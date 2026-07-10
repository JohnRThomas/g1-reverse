/* named: ancs_get_conn_ctx */
/* globals referenced:
//   0x20006a30  g_ble_conn_ctx_ptr           
*/
/* Reconstructed ancs_get_conn_ctx @ 0x181fc  (parity: 300/300 trials, PROVEN) */

unsigned int ancs_get_conn_ctx(void)
{
    return *(volatile unsigned int *)0x20006a30UL;
}

