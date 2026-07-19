### FUN_00023eec  @ 0x00023eec  (size=6)

callers (6): imu_fusion_thread, ble_process_put_req, FUN_00027cfe, key_event_thread, process_for_new_task, proxy_thread_handler
callees (0): (none)

```c
/* readable reconstruction; identity: FUN_00023eec @ 0x00023eec
 * public-name: FUN_00023eec
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_ui_mode_flag                           @ 0x20018462
 */
/* Reconstructed FUN_00023eec @ 0x23eec  (parity: 300/300 trials, PROVEN) */

unsigned char FUN_00023eec(void) {
    return *(volatile unsigned char*)(0x20018462UL + 2);
}
```