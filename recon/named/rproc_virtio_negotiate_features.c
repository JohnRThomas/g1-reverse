/* readable reconstruction; identity: FUN_0007c34a @ 0x0007c34a
 * public-name: rproc_virtio_negotiate_features
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   build_and_send_device_status_report      <= FUN_00022b00 @ 0x00022b00
 *   save_usr_setting                         <= FUN_0007c28e @ 0x0007c28e
 *   rproc_virtio_negotiate_features          <= FUN_0007c34a @ 0x0007c34a
 */
/* Reconstructed FUN_0007c34a @ 0x7c34a  (parity: 300/300 trials, PROVEN) */

extern void build_and_send_device_status_report(unsigned long);
extern void save_usr_setting(unsigned int, unsigned int);

unsigned int rproc_virtio_negotiate_features(unsigned int param_1, unsigned int param_2)
{
    build_and_send_device_status_report(param_1);
    save_usr_setting(param_1, param_2);
    return 0;
}
